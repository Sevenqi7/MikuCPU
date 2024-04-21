package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import chisel3.util.random.LFSR

class CacheReqIO(addr_wd: Int, data_wd: Int) extends MkBundle {
    val wr         = Bool()    // 0:read 1:write
    val vaddr      = UInt(addr_wd.W)
    val paddr      = UInt(addr_wd.W)
    val wtype      = UInt(2.W) // 2'b00:byte, 2'b01:half-word 2'b10: word
    val wdata      = UInt(data_wd.W)
    val uncached   = Bool()
    val cacop_en   = Bool()
    val cacop_func = UInt(2.W)
}

class CacheRespIO(data_wd: Int) extends MkBundle {
    val done  = Bool()
    val rdata = UInt(data_wd.W)
}

class CacheIO(addr_wd: Int, data_wd: Int) extends MkBundle {
    val req  = Flipped(Decoupled(new CacheReqIO(addr_wd, data_wd)))
    val resp = ValidIO(new CacheRespIO(data_wd))
    // val trans = nep

    val axi = new AXIMasterIF(VADDR_WIDTH, WORD_WIDTH, 4)

    def reqFromIfu(inter: MkFrontend): Unit = {
        inter.io.icache_inter.resp <> resp
        req                        <> inter.io.icache_inter.req
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

        // TODO: move writeResp handshake into Cache
        axi.writeResp.ready := 1.B
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

// write-back, write-alloc cache
// TODO: add support of CACOP instruction
class MkCache(tagWidth: Int, offsetWidth: Int, wayNum: Int, lineWidth: Int, readOnly: Boolean = false)
    extends MkModule {
    val indexWidth = VADDR_WIDTH - tagWidth - offsetWidth
    val io         = IO(new CacheIO(tagWidth + indexWidth + offsetWidth, WORD_WIDTH))
    require(lineWidth % WORD_WIDTH == 0)

    val WORDS_PER_LINE = lineWidth / WORD_WIDTH
    val setNum         = 1 << indexWidth

    val cache_ready   = io.req.ready
    val tagv_ram      = VecInit.fill(wayNum)(Module(new SRAMTemplate(indexWidth, new TagvBundle(tagWidth))).io)
    val data_ram      =
        VecInit.fill(wayNum, WORDS_PER_LINE)(Module(new SRAMTemplate(indexWidth, UInt(WORD_WIDTH.W), true)).io)
    val dirty_bits_it = if (!readOnly) Some(RegInit(VecInit.fill(wayNum, setNum)(false.B))) else None

    def this(params: (Int, Int, Int, Int, Boolean)) = {
        this(params._1, params._2, params._3, params._4, params._5)
    }

    def dirty_bits: Vec[Vec[Bool]] = {
        if (readOnly) {
            print("Warning! A dirty field is used in a read-only cache")
        }
        dirty_bits_it.get
    }

    def getLineData(way: UInt): Vec[UInt] = {
        VecInit((0 until WORDS_PER_LINE).map(i => data_ram(way)(i.U).dout))
    }
    def toWriteMask(optype: UInt) = ~0.U(4.W) >> (3.U - optype(1, 0))

    def getWstrbFromWtype(wtype: UInt, offset: UInt): UInt = {
        ~0.U(4.W) >> (4.U - (1.U << wtype)) << offset(log2Ceil(wordBytes) - 1, 0)
    }

    /*              main FSM              */
    val sIdle :: sLookup :: sMiss :: sReplace :: sRefill :: Nil = Enum(5)

    val state = RegInit(sIdle)

    // handle request
    val req_valid      = RegEnable(io.req.valid, cache_ready)
    // val req_addr       = RegEnable(io.req.bits.vaddr, io.req.valid & cache_ready)
    val req_wtype      = RegEnable(io.req.bits.wtype, io.req.valid & cache_ready)
    val req_uncached   = RegEnable(io.req.bits.uncached, io.req.valid & cache_ready)
    val req_wr         = RegEnable(io.req.bits.wr, io.req.valid & cache_ready)
    val req_wdata      = RegEnable(io.req.bits.wdata, io.req.valid & cache_ready)
    val req_cacop_en   = RegEnable(io.req.bits.cacop_en, io.req.valid & cache_ready)
    val req_cacop_func = RegEnable(io.req.bits.cacop_func, io.req.valid & cache_ready)

    val vtag            = io.req.bits.vaddr(VADDR_WIDTH - 1, VADDR_WIDTH - tagWidth)
    val ptag            = io.req.bits.paddr(VADDR_WIDTH - 1, VADDR_WIDTH - tagWidth)
    val index           = io.req.bits.vaddr(VADDR_WIDTH - tagWidth - 1, offsetWidth)
    val offset          = io.req.bits.vaddr(offsetWidth - 1, 0)
    val req_tag         = RegEnable(vtag, io.req.valid & io.req.ready)
    val req_idx         = RegEnable(index, io.req.valid & io.req.ready)
    val req_offset      = RegEnable(offset, io.req.valid & io.req.ready)
    val req_addr        = Cat(Seq(req_tag, req_idx, req_offset))
    val cacop_store_tag = (req_cacop_func === "b00".U) & req_cacop_en
    val cacop_idx_inv   = (req_cacop_func === "b01".U) & req_cacop_en
    val cacop_hit_inv   = (req_cacop_func === "b10".U) & req_cacop_en
    val cacop_inv_way   = req_addr(log2Ceil(wayNum) - 1, 0)

    // val replace_way  = RegEnable(LFSR(8)(log2Ceil(wayNum) - 1, 0), state === sReplace)
    // SRAM output

    // initialise
    for (i <- 0 until wayNum) {
        tagv_ram(i).addr := Mux(cache_ready, index, req_idx)
        tagv_ram(i).wen  := 0.B
        tagv_ram(i).din  := DontCare
        for (j <- 0 until (WORDS_PER_LINE)) {
            data_ram(i)(j).addr := Mux(cache_ready, index, req_idx)
            data_ram(i)(j).din  := DontCare
            data_ram(i)(j).wen  := 0.U
        }
    }
    io.initAXIInterfaces()
    io.resp.valid      := false.B
    io.resp.bits.done  := false.B
    io.resp.bits.rdata := 0x7777.U // Magic Number for debug

    val tagv_out    = VecInit((0 until wayNum).map(tagv => tagv_ram(tagv).dout.asTypeOf(new TagvBundle(tagWidth))))
    // val real_tag    = req_tag
    val cache_miss  = RegInit(false.B)
    val war_stall   = Wire(Bool())
    val paddr_v     = RegNext(io.req.valid & io.req.ready)
    // val real_tag    = Mux((req_cacop_en | cache_miss | RegNext(war_stall)) && !req_uncached, req_tag, ptag)
    val real_tag    = Mux(!paddr_v, req_tag, ptag)
    val total_hits  = VecInit((0 until wayNum).map(i => tagv_out(i).valid && (tagv_out(i).tag === real_tag)))
    val hit         = total_hits.reduce(_ || _) && (state === sLookup) && !req_cacop_en & !req_uncached
    val hit_way     = OHToUInt(total_hits)
    val hit_way_r   = RegNext(hit_way)
    val recv_data   = RegInit(VecInit(Seq.fill(WORDS_PER_LINE)(0.U(WORD_WIDTH.W))))
    val recv_cnt    = RegInit(0.U(log2Ceil(lineWidth).W))
    val dstate_idle = Wire(Bool())
    war_stall   := false.B
    dstate_idle := false.B

    val replace_way      = RegInit(0.U(log2Ceil(wayNum).W))
    val total_way_valids = VecInit(tagv_out.map(_.valid))
    val idle_way_exist   = !total_way_valids.reduce(_ & _)
    val idle_way         = PriorityEncoder(total_way_valids)
    when((state === sLookup) && !req_uncached) {
        replace_way := Mux(idle_way_exist, idle_way, LFSR(4)(log2Ceil(wayNum) - 1, 0))
    }

    val data_ram_sel = req_offset(offsetWidth - log2Ceil(WORDS_PER_LINE) + 1, offsetWidth - log2Ceil(WORDS_PER_LINE))

    val wreq_way = RegInit(0.U(log2Ceil(wayNum).W))

    cache_ready := (state === sIdle) || ((state === sLookup) && hit && !war_stall && !req_uncached)

    switch(state) {
        // sIdle:
        // wait and store valid request
        is(sIdle) {
            state      := sIdle
            cache_miss := false.B
            when(io.req.valid) {
                state := sLookup
            }
        }
        // sLookup:
        // tag comparison and generate rdata, wline & hit_way
        is(sLookup) {
            io.resp.bits.rdata := getLineData(hit_way)(data_ram_sel)
            io.resp.valid      := hit & !war_stall & !req_uncached & !req_cacop_en
            io.resp.bits.done  := hit & !war_stall & !req_uncached & !req_cacop_en
            wreq_way           := hit_way
            val next_state = MuxCase(
                sIdle,
                Seq(
                    /*
                      Pri              Description
                       1. uncached request need further handle.
                       2. write-after_read stall detected, stall 1 cycle
                       3. receive another valid cached request, keep looking up in cache
                       4. cache miss
                     */

                    (req_uncached | req_cacop_en, sMiss),
                    (hit & war_stall, sLookup),
                    (hit & io.req.valid, sLookup),
                    (!hit, sMiss)
                )
            )
            state      := next_state
            cache_miss := !hit
            when((next_state =/= sLookup) | war_stall) {
                req_tag := real_tag
            }
        }

        // sMiss:
        // wait for axi bus idle and send read request
        is(sMiss) {
            when(req_uncached && req_wr) {
                assert(!req_cacop_en)
                state             := Mux(dstate_idle, sIdle, sMiss)
                io.resp.bits.done := dstate_idle
                io.resp.valid     := dstate_idle
            }.otherwise {
                when(req_cacop_en) {
                    state := sReplace
                }.otherwise {
                    val araddr    = Mux(
                        req_uncached,
                        req_addr(VADDR_WIDTH - 1, 2) << 2,
                        req_addr(VADDR_WIDTH - 1, offsetWidth) << offsetWidth
                    )
                    val arlen     = Mux(req_uncached, 0.U, (WORDS_PER_LINE - 1).U)
                    val handshake =
                        io.sendReadReq(
                            araddr,
                            "b010".U,
                            arlen,
                            0.U
                        )
                    state := Mux(handshake, sReplace, sMiss)
                }
            }
            recv_cnt := 0.U
        }

        // sReplace:
        // receive data from mem
        is(sReplace) {
            when(req_cacop_en) {
                state := sRefill
            }.otherwise {
                val (rvalid, rlast, rdata) = io.readFromMem()
                // state := Mux(rlast & rvalid, sRefill, sReplace)
                when(rvalid) {
                    recv_data(recv_cnt) := rdata
                    recv_cnt            := recv_cnt + 1.U
                }
                val cacheline_wr_flag      = if (readOnly) 0.B else dirty_bits(replace_way)(req_idx)
                when(req_uncached & !req_wr) {
                    io.resp.bits.rdata := rdata
                    io.resp.bits.done  := rlast & rvalid
                    io.resp.valid      := rlast & rvalid
                    state              := Mux(rlast & rvalid, sIdle, sReplace)
                }.otherwise {
                    val rdata_all_recv = (rvalid & rlast) || (recv_cnt === WORDS_PER_LINE.U)
                    state := MuxCase(
                        sReplace,
                        Seq(
                            (cacheline_wr_flag & dstate_idle & rdata_all_recv) -> sRefill,
                            (!cacheline_wr_flag & rdata_all_recv)              -> sRefill
                        )
                    )
                }
            }
            // TODO: check whether dstate is dsIdle when a dirty cache line need written back
        }

        // sRefill:
        // refill data into Cache bank
        is(sRefill) {
            when(!req_cacop_en) {
                state                     := sLookup
                for (i <- 0 until WORDS_PER_LINE) {
                    data_ram(replace_way)(i).wen := ~0.U(WORD_WIDTH.W)
                    data_ram(replace_way)(i).din := recv_data(i)
                }
                tagv_ram(replace_way).din := Cat(true.B, req_tag)
                tagv_ram(replace_way).wen := true.B
            }.otherwise {
                state        := sIdle
                when(cacop_store_tag || cacop_idx_inv) {
                    tagv_ram(cacop_inv_way).din := 0.U
                    tagv_ram(cacop_inv_way).wen := true.B
                    // if (!readOnly) {
                    //     when(cacop_store_tag) {
                    //         dirty_bits(way)(req_idx) := 0.B
                    //     }
                    // }
                }
                when(cacop_hit_inv) {
                    tagv_ram(hit_way_r).din := 0.U
                    tagv_ram(hit_way_r).wen := true.B
                }
                req_cacop_en := false.B
            }
        }
    }

    if (!readOnly) {

        // cache-write statemachine
        val wsIdle :: wsWrite :: wsCleanup :: Nil = Enum(3)
        val wstate                                = RegInit(wsIdle)

        val wreq_wdata    = RegEnable(req_wdata, hit & req_wr)
        val wreq_addr     = RegEnable(req_addr, hit & req_wr)
        val wreq_wtype    = RegEnable(req_wtype, hit & req_wr)
        val wreq_tag      = WireInit(wreq_addr(VADDR_WIDTH - 1, VADDR_WIDTH - tagWidth))
        val wreq_idx      = WireInit(wreq_addr(VADDR_WIDTH - tagWidth - 1, offsetWidth))
        val wreq_offset   = WireInit(wreq_addr(offsetWidth - 1, 0))
        val wdata_ram_sel =
            wreq_offset(offsetWidth - log2Ceil(WORDS_PER_LINE) + 1, offsetWidth - log2Ceil(WORDS_PER_LINE))

        val war_case_1 =
            (RegNext(wstate) === wsWrite) && (hit_way === RegNext(wreq_way)) && (data_ram_sel === RegNext(
                wdata_ram_sel
            ))
        val war_case_2 = (wstate === wsWrite) && (hit_way === wreq_way) && (data_ram_sel === wdata_ram_sel)
        war_stall := (war_case_1 | war_case_2) & !req_wr & req_valid & !req_uncached

        switch(wstate) {
            is(wsIdle) {
                when(hit & req_wr & !req_uncached) {
                    wstate := wsWrite
                }
            }
            is(wsWrite) {
                data_ram(wreq_way)(wdata_ram_sel).addr := wreq_idx
                data_ram(wreq_way)(wdata_ram_sel).din  := wreq_wdata
                data_ram(wreq_way)(wdata_ram_sel).wen  := getWstrbFromWtype(wreq_wtype, wreq_offset)
                dirty_bits(wreq_way)(wreq_idx)         := true.B

                wstate := Mux(hit & req_wr & !req_uncached, wsWrite, wsIdle)
            }
            // is(wsCleanup) {
            //     wstate := Mux(hit & req_wr, wsWrite, wsIdle)
            // }
        }

        // write-back of dirty cache line
        val dsIdle :: dsReq :: dsWrite :: Nil = Enum(3)
        val dstate                            = RegInit(dsIdle)

        val dreq_data     = RegInit(VecInit.fill(WORDS_PER_LINE)(0.U(WORD_WIDTH.W)))
        val dreq_addr     = RegInit(0.U(VADDR_WIDTH.W))
        val dreq_wtype    = RegInit(0.U(2.W))
        val dreq_uncached = RegInit(false.B)
        val send_cnt      = RegInit(0.U(log2Ceil(lineWidth).W))

        val dirty_way   = MuxCase(
            replace_way,
            Seq(
                cacop_hit_inv -> hit_way_r,
                cacop_idx_inv -> cacop_inv_way
            )
        )
        val dirty_way_v = tagv_ram(dirty_way).dout.asTypeOf(new TagvBundle(tagWidth)).valid

        val cacheline_wr_en = ((state === sReplace) && dirty_bits(dirty_way)(req_idx) && dirty_way_v && !req_uncached)
        val uncached_wr_en  = ((state === sMiss) && req_uncached && req_wr && dstate_idle)

        dstate_idle := (dstate === dsIdle)
        when(cacheline_wr_en && dstate_idle) {
            for (i <- 0 until WORDS_PER_LINE) {
                dreq_data(i) := data_ram(dirty_way)(i).dout
            }
            dreq_addr     := Cat(Seq(tagv_ram(dirty_way).dout, req_idx, 0.U(4.W)))
            dreq_wtype    := "b10".U
            dreq_uncached := false.B
            when(dstate_idle) {
                dirty_bits(dirty_way)(req_idx) := 0.B
            }
        }.elsewhen(uncached_wr_en) {
            dreq_data(0)  := req_wdata
            dreq_addr     := req_addr
            dreq_wtype    := req_wtype
            dreq_uncached := req_uncached
        }

        switch(dstate) {
            is(dsIdle) {
                when(uncached_wr_en | cacheline_wr_en) {
                    dstate := dsReq
                }
            }
            is(dsReq) {
                val awaddr    = Mux(
                    dreq_uncached,
                    dreq_addr,
                    dreq_addr(VADDR_WIDTH - 1, offsetWidth) << offsetWidth
                )
                val awsize    = Mux(dreq_uncached, dreq_wtype, "b010".U)
                val awlen     = Mux(dreq_uncached, 0.U, (WORDS_PER_LINE - 1).U)
                val handshake = io.sendWriteReq(awaddr, awsize, awlen, 0.U)

                send_cnt := 0.U
                dstate   := Mux(handshake, dsWrite, dsReq)
            }
            is(dsWrite) {
                val wstrb     = getWstrbFromWtype(dreq_wtype, dreq_addr(1, 0))
                val wlast     = Mux(dreq_uncached, true.B, (send_cnt === (WORDS_PER_LINE - 1).U))
                val wdata     = dreq_data(send_cnt)
                val handshake = io.writeToMem(wstrb, wlast, wdata)

                send_cnt := Mux(handshake, send_cnt + 1.U, send_cnt)
                dstate   := Mux(handshake & wlast, dsIdle, dsWrite)
                // when(handshake & wlast) {
                //     when(!req_uncached) {
                //         printf("write dirty cacheline to addr:0x%x\n", dreq_addr)
                //     }.otherwise {
                //         printf("uncached write:\n")
                //         printf("wstrb: 0x%x wdata: 0x%x waddr: 0x%x\n\n", wstrb, wdata, dreq_addr)
                //     }
                // }
            }
        }
    }
}
