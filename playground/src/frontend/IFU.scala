package miku.frontend

import chisel3._
import chisel3.util._

import miku._

class IFUICacheIO extends MkBundle{
    val cacheReq = Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
    val cacheResp = Flipped(ValidIO(new CacheRespIO(WORD_WIDTH)))
}

class IFUIO extends MkBundle{
    val icacheMsg = new IFUICacheIO()
}

class IFU extends MkModule{
    val io = IO(new IFUIO)

    val s0_pc = RegInit(0.U(VADDR_WIDTH.W))    

    //IFU-ICache
    val fromICache = io.icacheMsg.cacheResp
    val toICache = io.icacheMsg.cacheReq
   
}