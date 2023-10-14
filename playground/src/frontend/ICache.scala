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
}

class TagvBundle(tagWidth: Int) extends MkBundle{
    val valid = Bool()
    val tag = UInt(tagWidth.W)
}

class ICache(tagWidth: Int, offsetWidth: Int, wayNum: Int, dataWidth: Int) extends MkModule{
    val io = IO(new CacheIO(tagWidth, dataWidth))
    val indexWidth = VADDR_WIDTH - tagWidth - offsetWidth

    val tagv_ram = Vec(wayNum, new SRAMTemplate(VADDR_WIDTH, new TagvBundle(tagWidth)).io)
    val data_ram = Vec(wayNum, new SRAMTemplate(VADDR_WIDTH, UInt(dataWidth.W)).io)

    /*              main FSM              */
    val sIdle :: sLoopup :: sMiss :: sReplace :: sRefill :: Nil = Enum(5)
    val state = RegInit(sIdle)

    //sIdle: 
    //wait for request, store request

    //sLookup:
    //tag comparison and generate rdata & hit_way

    //sMiss:
    //wait for axi bus idle 

    //sReplace:
    //send axi transaction

    //sRefill:
    //refill data in Cache set
}   
