package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import chisel3.util.random.LFSR

class CacheReqIO(addrWidth: Int, dataWidth: Int) extends MkBundle{
    val wr = Bool()
    val addr  = UInt(addrWidth.W)
    val wtype = UInt(2.W)
    val wdata = UInt(dataWidth.W)
    val uncached = Bool()
}

class CacheRespIO(dataWidth: Int) extends MkBundle{
    val done = Bool()
    val rdata = UInt(dataWidth.W)
}

class CacheIO(addrWidth: Int, dataWidth: Int) extends MkBundle{
    val req = Flipped(Decoupled(new CacheReqIO(addrWidth, dataWidth)))
    val resp = ValidIO(new CacheRespIO(dataWidth))
    
    val axi = new AXIMasterIF(VADDR_WIDTH, WORD_WIDTH, 4)

    def reqFromIfu(inter: IFUICacheIO): Unit = {
        req := inter.cacheReq
        inter.cacheResp := resp
    }

    //initialise all signals of axi interfaces
    def initAXIInterfaces() : Unit ={
        axi.readAddr.valid := 0.U
        axi.readAddr.bits.addr := 0.U    
        axi.readAddr.bits.burst := 0.U
        axi.readAddr.bits.id := 0.U
        axi.readAddr.bits.len := 0.U
        axi.readAddr.bits.cache := 0.U
        axi.readAddr.bits.prot := 0.U
        axi.readAddr.bits.lock := 0.U
        axi.readAddr.bits.size := 0.U

        axi.readData.ready := 0.U

        axi.writeAddr.valid := 0.U
        axi.writeAddr.bits.addr := 0.U    
        axi.writeAddr.bits.burst := 0.U
        axi.writeAddr.bits.id := 0.U
        axi.writeAddr.bits.len := 0.U
        axi.writeAddr.bits.cache := 0.U
        axi.writeAddr.bits.prot := 0.U
        axi.writeAddr.bits.lock := 0.U
        axi.writeAddr.bits.size := 0.U

        axi.writeData.valid := 0.U
        axi.writeData.bits.data := 0.U
        axi.writeData.bits.id := 0.U
        axi.writeData.bits.last := 0.U
        axi.writeData.bits.strb := 0.U

        axi.writeResp.ready := 0.U
    }
    
    //send axi read request. return true when handshake of address-read channel is done
    def sendReadReq(araddr: UInt, arsize: UInt, arlen: UInt, arid: UInt): Bool = {
        axi.readAddr.valid := 1.B
        axi.readAddr.bits.id := arid
        axi.readAddr.bits.addr := araddr
        axi.readAddr.bits.len := arlen
        axi.readAddr.bits.size := arsize
        axi.readAddr.bits.burst := "b01".U
        axi.readAddr.bits.prot := 0.U
        axi.readAddr.bits.cache := 0.U
        axi.readAddr.bits.lock := 0.U

        axi.readAddr.valid & axi.readAddr.ready
    }

    // read data from axi-bus
    // return value: (rvalid, rlast, rdata)
    def readFromMem() : (Bool, Bool, UInt) = {
        axi.readData.ready := 1.B
        (axi.readData.valid, axi.readData.bits.last, axi.readData.bits.data)
    }
}

class TagvBundle(tagWidth: Int) extends MkBundle{
    val valid = Bool()
    val tag = UInt(tagWidth.W)
}

class ICache(tagWidth: Int, offsetWidth: Int, wayNum: Int, lineWidth: Int) extends MkModule{
    val indexWidth = VADDR_WIDTH - tagWidth - offsetWidth
    val io = IO(new CacheIO(tagWidth + indexWidth + offsetWidth, WORD_WIDTH))
    require(lineWidth % WORD_WIDTH == 0)

    val WORDS_PER_LINE = lineWidth / WORD_WIDTH
    val setNum = 1 << indexWidth

    val cache_ready = io.req.ready
    val tagv_ram = VecInit.fill(wayNum)(Module(new SRAMTemplate(VADDR_WIDTH, new TagvBundle(tagWidth))).io)
    val data_ram = VecInit.fill(wayNum, WORDS_PER_LINE)(Module(new SRAMTemplate(VADDR_WIDTH, UInt(WORD_WIDTH.W))).io)
    def getLineData(way: UInt): Vec[UInt] = {
        VecInit((0 until WORDS_PER_LINE).map(i => data_ram(way)(i.U).dout))
    }
    // val dirty = RegInit(VecInit.fill(setNum, wayNum)(0.B))

    /*              main FSM              */
    val sIdle :: sLookup :: sMiss :: sReplace :: sRefill :: Nil = Enum(5)
    val state = RegInit(sIdle)

    //handle request
    val req_valid = RegEnable(io.req.valid, cache_ready)
    val req_addr = RegEnable(io.req.bits.addr, io.req.valid & cache_ready)
    val req_tag = WireInit(req_addr(VADDR_WIDTH - 1, VADDR_WIDTH - tagWidth))
    val req_idx = WireInit(req_addr(VADDR_WIDTH - tagWidth - 1, offsetWidth))
    val req_offset = WireInit(req_addr(offsetWidth -1, 0))

    val replace_way = RegEnable(LFSR(8)(log2Ceil(wayNum), 0), state === sMiss)    
    val data_ram_sel = req_offset(log2Ceil(WORDS_PER_LINE) - 1, log2Ceil(WORDS_PER_LINE) - 2)
    //SRAM output
    
    //initialise
    for(i <- 0 until wayNum){
        tagv_ram(i).addr := req_idx
        tagv_ram(i).wen := 0.B
        tagv_ram(i).din := DontCare
        for(j <- 0 until (WORDS_PER_LINE)){
            data_ram(i)(j).addr := req_idx
            data_ram(i)(j).din := DontCare
            data_ram(i)(j).wen := 0.B
        }
    }
    io.initAXIInterfaces()
    io.resp.valid := 0.B
    io.resp.bits.done := 0.B
    io.resp.bits.rdata := 0x7777.U  //Magic Number for debug

    val tagv_out = VecInit((0 until wayNum).map(tagv => tagv_ram(tagv).dout.asTypeOf(new TagvBundle(tagWidth))))
    val totalHits = VecInit((0 until wayNum).map(i => tagv_out(i).valid && tagv_out(i).tag === req_tag))
    val hit = totalHits.reduce(_ || _)
    val hitWay = OHToUInt(totalHits)
    val recv_data = RegInit(VecInit(Seq.fill(WORDS_PER_LINE)(0.U(WORD_WIDTH.W))))
    val recv_cnt = RegInit(0.U(log2Ceil(lineWidth).W))
    cache_ready := state === sIdle || (state === sLookup && hit) 
    
    //sIdle: 
    //wait for request, store request
    when(state === sIdle){
        when(req_valid){
            state := sLookup
        }    
    }

    //sLookup:
    //tag comparison and generate rdata & hit_way
    .elsewhen(state === sLookup){
        io.resp.bits.rdata := getLineData(hitWay)(data_ram_sel)
        io.resp.valid := 1.B
        state := MuxCase(sIdle, Seq(
            (hit & io.req.valid, sLookup),
            (!hit, sMiss)
        ))
    }   

    //sMiss:
    //wait for axi bus idle and send read request 
    .elsewhen(state === sMiss){
        val handshake = io.sendReadReq(req_addr(VADDR_WIDTH - 1, offsetWidth) << offsetWidth, 
                        "b010".U, 
                        WORDS_PER_LINE.U, 0.U
        )
        state := Mux(handshake, sReplace, sMiss)
        recv_cnt := 0.U
    }

    //sReplace:
    //receive data from mem
    .elsewhen(state === sReplace){
        val (rvalid, rlast, rdata) = io.readFromMem()
        state := Mux(rlast & rvalid, sRefill, sReplace)
        when(rvalid){
            recv_data(recv_cnt) := rdata
            recv_cnt := recv_cnt + 1.U
        }
    }

    //sRefill:
    //refill data into Cache bank
    .elsewhen(state === sRefill){
        state := sLookup
        for(i <- 0 until WORDS_PER_LINE){
            data_ram(replace_way)(i).wen := 1.B
            data_ram(replace_way)(i).din := recv_data(i)
        }
        tagv_ram(replace_way).din := req_tag
        tagv_ram(replace_way).wen := 1.B
    }

}   
