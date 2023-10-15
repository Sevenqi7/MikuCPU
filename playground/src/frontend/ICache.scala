package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

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

    def reqFromIfu(inter: IFUICacheIO){
        req := inter.cacheReq
        inter.cacheResp := resp
    }

    // return true when read transaction finish
    def axiRead(raddr: UInt, arsize: UInt){
        //to be done
    }
}

class TagvBundle(tagWidth: Int) extends MkBundle{
    val valid = Bool()
    val tag = UInt(tagWidth.W)
}

class ICache(tagWidth: Int, offsetWidth: Int, wayNum: Int, dataWidth: Int) extends MkModule{
    val io = IO(new CacheIO(tagWidth, dataWidth))
    
    val indexWidth = VADDR_WIDTH - tagWidth - offsetWidth
    val setNum = 1 << indexWidth

    val tagv_ram = Vec(wayNum, new SRAMTemplate(VADDR_WIDTH, new TagvBundle(tagWidth)).io)
    val data_ram = Vec(wayNum, new SRAMTemplate(VADDR_WIDTH, UInt(dataWidth.W)).io)
    
    //handle request
    val req_valid = RegNext(io.req.valid)
    val req_addr = RegEnable(io.req.bits.addr, io.req.valid)
    val req_tag = WireInit(req_addr(VADDR_WIDTH - 1, VADDR_WIDTH - tagWidth))
    val req_idx = WireInit(req_addr(VADDR_WIDTH - tagWidth - 1, offsetWidth))
    val req_offset = WireInit(req_addr(offsetWidth -1, 0))
    
    //SRAM output

    for(i <- 0 until wayNum){
        tagv_ram(i).addr := req_idx
        data_ram(i).addr := req_idx
    }

    val tagv_out = VecInit((0 until wayNum).map(tagv => tagv_ram(tagv).dout.asTypeOf(new TagvBundle(tagWidth))))
    val data_out = VecInit((0 until wayNum).map(data => data_ram(data).dout))

    /*              main FSM              */
    val sIdle :: sLookup :: sMiss :: sReplace :: sRefill :: Nil = Enum(5)
    val state = RegInit(sIdle)
    
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
        val totalHits = VecInit((0 until wayNum).map(i => tagv_out(i).valid && tagv_out(i).tag === req_tag))
        val hit = totalHits.reduce(_ || _)
        val hitWay = OHToUInt(totalHits)
        io.resp.bits.rdata := data_out(hitWay)
        
        state := Mux(hit, sIdle, sMiss)
    }   

    //sMiss:
    //wait for axi bus idle 
    .elsewhen(state === sMiss){
        
    }

    //sReplace:
    //send axi transaction

    //sRefill:
    //refill data in Cache set
}   
