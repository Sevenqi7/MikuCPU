package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import chisel3.util.random.LFSR

class CacheReqIO(addr_wd: Int, data_wd: Int) extends MkBundle {
    val wr       = Bool()    // 0:read 1:write
    val addr     = UInt(addr_wd.W)
    val wtype    = UInt(2.W) // 2'b00:byte, 2'b01:half-word 2'b10: word
    val wdata    = UInt(data_wd.W)
    val uncached = Bool()
}

class CacheRespIO(data_wd: Int) extends MkBundle {
    val done  = Bool()
    val rdata = UInt(data_wd.W)
}

class CacheIO(addr_wd: Int, data_wd: Int) extends MkBundle {
    val req  = Flipped(Decoupled(new CacheReqIO(addr_wd, data_wd)))
    val resp = ValidIO(new CacheRespIO(data_wd))

    val axi = new AXIMasterIF(VADDR_WIDTH, WORD_WIDTH, 4)

    def reqFromIfu(inter: IFU): Unit = {
        inter.io.icache_msg.cache_resp <> resp
        req                            <> inter.io.icache_msg.cache_req
    }

    // initialise all signals of axi interfaces
    def initAXIInterfaces(): Unit = {
        axi.readAddr.valid      := 0.U
        axi.readAddr.bits.addr  := 0.U
        axi.readAddr.bits.burst := 0.U
        axi.readAddr.bits.id    := 0.U
        axi.readAddr.bits.len   := 0.U
        axi.readAddr.bits.cache := 0.U
        axi.readAddr.bits.prot  := 0.U
        axi.readAddr.bits.lock  := 0.U
        axi.readAddr.bits.size  := 0.U

        axi.readData.ready := 0.U

        axi.writeAddr.valid      := 0.U
        axi.writeAddr.bits.addr  := 0.U
        axi.writeAddr.bits.burst := 0.U
        axi.writeAddr.bits.id    := 0.U
        axi.writeAddr.bits.len   := 0.U
        axi.writeAddr.bits.cache := 0.U
        axi.writeAddr.bits.prot  := 0.U
        axi.writeAddr.bits.lock  := 0.U
        axi.writeAddr.bits.size  := 0.U

        axi.writeData.valid     := 0.U
        axi.writeData.bits.data := 0.U
        axi.writeData.bits.id   := 0.U
        axi.writeData.bits.last := 0.U
        axi.writeData.bits.strb := 0.U

        axi.writeResp.ready := 0.U
    }

    // send axi read request. return true when handshake of address-read channel is done
    def sendReadReq(araddr: UInt, arsize: UInt, arlen: UInt, arid: UInt): Bool = {
        axi.readAddr.valid      := 1.B
        axi.readAddr.bits.id    := arid
        axi.readAddr.bits.addr  := araddr
        axi.readAddr.bits.len   := arlen
        axi.readAddr.bits.size  := arsize
        axi.readAddr.bits.burst := "b01".U
        axi.readAddr.bits.prot  := 0.U
        axi.readAddr.bits.cache := 0.U
        axi.readAddr.bits.lock  := 0.U

        axi.readAddr.valid & axi.readAddr.ready
    }

    // send axi read request. return true when handshake of address-read channel is done
    def sendWriteReq(awaddr: UInt, awsize: UInt, awlen: UInt, awid: UInt): Bool = {
        axi.writeAddr.valid      := 1.B
        axi.writeAddr.bits.id    := awid
        axi.writeAddr.bits.addr  := awaddr
        axi.writeAddr.bits.len   := awlen
        axi.writeAddr.bits.size  := awsize
        axi.writeAddr.bits.burst := "b01".U
        axi.writeAddr.bits.prot  := 0.U
        axi.writeAddr.bits.cache := 0.U
        axi.writeAddr.bits.lock  := 0.U

        axi.writeAddr.valid & axi.writeAddr.ready
    }

    // read data from axi-bus
    // return value: (rvalid, rlast, rdata)
    def readFromMem(): (Bool, Bool, UInt) = {
        axi.readData.ready := 1.B
        (axi.readData.valid, axi.readData.bits.last, axi.readData.bits.data)
    }

    // write data through axi-bus
    // return true when handshake of data-write channel is done
    def writeToMem(wstrb: UInt, wlast: Bool, wdata: UInt): Bool = {
        require(wdata.getWidth == data_wd)
        axi.writeData.valid     := 1.B
        axi.writeData.bits.data := wdata
        axi.writeData.bits.strb := wstrb
        axi.writeData.bits.last := wlast

        axi.writeData.ready & axi.writeData.valid
    }
}

class TagvBundle(tagWidth: Int) extends MkBundle {
    val valid = Bool()
    val tag   = UInt(tagWidth.W)
}

//TODO: add write logic
// write-back, write-alloc cache
class MkCache(tagWidth: Int, offsetWidth: Int, wayNum: Int, lineWidth: Int, readOnly: Boolean = false)
    extends MkModule {
    val indexWidth = VADDR_WIDTH - tagWidth - offsetWidth
    val io         = IO(new CacheIO(tagWidth + indexWidth + offsetWidth, WORD_WIDTH))
    require(lineWidth % WORD_WIDTH == 0)

    val WORDS_PER_LINE = lineWidth / WORD_WIDTH
    val setNum         = 1 << indexWidth

    val cache_ready = io.req.ready
    val tagv_ram    = VecInit.fill(wayNum)(Module(new SRAMTemplate(indexWidth, new TagvBundle(tagWidth))).io)
    val data_ram    = VecInit.fill(wayNum, WORDS_PER_LINE)(Module(new SRAMTemplate(indexWidth, UInt(WORD_WIDTH.W))).io)
    val dirty_bits_it = if (!readOnly) Some(RegInit(VecInit.fill(wayNum, setNum)(false.B))) else None

    def dirty_bits: Vec[Vec[Bool]] = {
        if (readOnly) {
            printf("Warning! A dirty field is used in a read-only cache")
        }
        dirty_bits_it.get
    }

    def getLineData(way: UInt): Vec[UInt] = {
        VecInit((0 until WORDS_PER_LINE).map(i => data_ram(way)(i.U).dout))
    }
    // val dirty = RegInit(VecInit.fill(setNum, wayNum)(0.B))

    /*              main FSM              */
    val sIdle :: sLookup :: sMiss :: sReplace :: sRefill :: Nil = Enum(5)

    val state = RegInit(sIdle)

    // handle request
    val req_valid = RegEnable(io.req.valid, cache_ready)
    val req_addr  = RegEnable(io.req.bits.addr, io.req.valid & cache_ready)
    val req_wstrb = RegEnable(io.req.bits.wtype, io.req.valid & cache_ready)
    val req_wr    = RegEnable(io.req.bits.wr, io.req.valid & cache_ready)
    val req_wdata = RegEnable(io.req.bits.wdata, io.req.valid & cache_ready)

    val tag        = io.req.bits.addr(VADDR_WIDTH - 1, VADDR_WIDTH - tagWidth)
    val index      = io.req.bits.addr(VADDR_WIDTH - tagWidth - 1, offsetWidth)
    val offset     = io.req.bits.addr(offsetWidth - 1, 0)
    val req_tag    = WireInit(req_addr(VADDR_WIDTH - 1, VADDR_WIDTH - tagWidth))
    val req_idx    = WireInit(req_addr(VADDR_WIDTH - tagWidth - 1, offsetWidth))
    val req_offset = WireInit(req_addr(offsetWidth - 1, 0))

    val replace_way  = RegEnable(LFSR(8)(log2Ceil(wayNum), 0), state === sMiss)
    val data_ram_sel = req_offset(offsetWidth - log2Ceil(WORDS_PER_LINE) + 1, offsetWidth - log2Ceil(WORDS_PER_LINE))
    // SRAM output

    // initialise
    for (i <- 0 until wayNum) {
        tagv_ram(i).addr := Mux(cache_ready, index, req_idx)
        tagv_ram(i).wen  := 0.B
        tagv_ram(i).din  := DontCare
        for (j <- 0 until (WORDS_PER_LINE)) {
            data_ram(i)(j).addr := Mux(cache_ready, index, req_idx)
            data_ram(i)(j).din  := DontCare
            data_ram(i)(j).wen  := 0.B
        }
    }
    io.initAXIInterfaces()
    io.resp.valid      := 0.B
    io.resp.bits.done  := 0.B
    io.resp.bits.rdata := 0x7777.U // Magic Number for debug

    val tagv_out   = VecInit((0 until wayNum).map(tagv => tagv_ram(tagv).dout.asTypeOf(new TagvBundle(tagWidth))))
    val total_hits = VecInit((0 until wayNum).map(i => tagv_out(i).valid && (tagv_out(i).tag === req_tag)))
    val hit        = total_hits.reduce(_ || _)
    val hitWay     = OHToUInt(total_hits)
    val recv_data  = RegInit(VecInit(Seq.fill(WORDS_PER_LINE)(0.U(WORD_WIDTH.W))))
    val recv_cnt   = RegInit(0.U(log2Ceil(lineWidth).W))

    val wreq_way = RegInit(0.U(lineWidth.W))

    cache_ready := (state === sIdle) || ((state === sLookup) && hit)

    switch(state) {
        // sIdle:
        // wait for request, store request
        is(sIdle) {
            when(req_valid) {
                state := sLookup
            }
        }
        // sLookup:
        // tag comparison and generate rdata, wline & hit_way
        is(sLookup) {
            io.resp.bits.rdata := getLineData(hitWay)(data_ram_sel)
            io.resp.valid      := hit
            io.resp.bits.done  := hit
            wreq_way           := hitWay
            state              := MuxCase(
                sIdle,
                Seq(
                    (hit & io.req.valid, sLookup),
                    (!hit, sMiss)
                )
            )
        }

        // sMiss:
        // wait for axi bus idle and send read request
        is(sMiss) {
            val handshake =
                io.sendReadReq(
                    req_addr(VADDR_WIDTH - 1, offsetWidth) << offsetWidth,
                    "b010".U,
                    (WORDS_PER_LINE - 1).U,
                    0.U
                )
            state    := Mux(handshake, sReplace, sMiss)
            recv_cnt := 0.U
        }

        // sReplace:
        // receive data from mem
        is(sReplace) {
            val (rvalid, rlast, rdata) = io.readFromMem()
            state := Mux(rlast & rvalid, sRefill, sReplace)
            when(rvalid) {
                recv_data(recv_cnt) := rdata
                recv_cnt            := recv_cnt + 1.U
            }
        }

        // sRefill:
        // refill data into Cache bank
        is(sRefill) {
            state                     := sLookup
            for (i <- 0 until WORDS_PER_LINE) {
                data_ram(replace_way)(i).wen := 1.B
                data_ram(replace_way)(i).din := recv_data(i)
            }
            tagv_ram(replace_way).din := Cat(true.B, req_tag)
            tagv_ram(replace_way).wen := 1.B
        }
    }

    if (!readOnly) {

        // cache-write statemachine
        val wsIdle :: wsWrite :: wsCleanup :: Nil = Enum(3)
        val wstate                                = RegInit(wsIdle)

        val wreq_wdata    = RegEnable(req_wdata, hit & req_wr)
        val wreq_addr     = RegEnable(req_addr, hit & req_wr)
        val wreq_wstrb    = RegEnable(req_wstrb, hit & req_wr)
        val wreq_tag      = WireInit(wreq_addr(VADDR_WIDTH - 1, VADDR_WIDTH - tagWidth))
        val wreq_idx      = WireInit(wreq_addr(VADDR_WIDTH - tagWidth - 1, offsetWidth))
        val wreq_offset   = WireInit(wreq_addr(offsetWidth - 1, 0))
        val wdata_ram_sel =
            wreq_offset(offsetWidth - log2Ceil(WORDS_PER_LINE) + 1, offsetWidth - log2Ceil(WORDS_PER_LINE))

        switch(wstate) {
            is(wsIdle) {
                when(hit & req_wr) {
                    wstate := wsWrite
                }
            }
            is(wsWrite) {
                data_ram(wreq_way)(wdata_ram_sel).addr := wreq_idx
                data_ram(wreq_way)(wdata_ram_sel).din  := wreq_wdata
                data_ram(wreq_way)(wdata_ram_sel).wen  := wreq_wstrb

                wstate := Mux(hit & req_wr, wsWrite, wsIdle)
            }
        }

        // write-back of dirty cache line
        val dsIdle :: dsReq :: dsWrite :: Nil = Enum(3)
        val dstate                            = RegInit(dsIdle)

        io.axi.writeResp.ready := true.B
        val dreq_data = RegInit(VecInit.fill(WORDS_PER_LINE)(0.U(WORD_WIDTH.W)))
        val send_cnt  = RegInit(0.U(log2Ceil(lineWidth).W))
        for (i <- 0 until WORDS_PER_LINE) {
            when((state === sReplace) && dirty_bits(replace_way)(req_idx)) {
                dreq_data(i) := data_ram(replace_way)(i).dout
            }
        }

        switch(dstate) {
            is(dsIdle) {
                when((state === sReplace) && dirty_bits(replace_way)(req_idx)) {
                    dstate := dsWrite
                }
            }
            is(dsReq) {
                val awaddr    = req_addr(VADDR_WIDTH - 1, offsetWidth) << offsetWidth
                val awsize    = "b010".U
                val awlen     = (WORDS_PER_LINE - 1).U
                val handshake = io.sendWriteReq(awaddr, awsize, awlen, 0.U)

                dstate := Mux(handshake, dsWrite, dsReq)
            }
            is(dsWrite) {
                val wstrb     = VecInit.fill(wordBytes)(1.B).asUInt
                val wlast     = (send_cnt === (WORDS_PER_LINE - 1).U)
                val wdata     = dreq_data(send_cnt)
                val handshake = io.writeToMem(wstrb, wlast, wdata)

                dstate := Mux(handshake & wlast, dsIdle, dsWrite)
            }
        }
    }
}
