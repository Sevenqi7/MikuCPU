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

    //IFU-ICache
    val fromICache = io.icacheMsg.cacheResp
    val toICache = io.icacheMsg.cacheReq

    val s0_pc = RegInit(0.U(VADDR_WIDTH.W))    
    val s0_valid = toICache.ready

    val s1_pc = RegEnable(s0_pc, s0_valid)
    val s1_valid = fromICache.valid
}
