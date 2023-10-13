package miku.frontend

import chisel3._
import chisel3.util._

import miku._

trait CacheParams{
    val WAY_NUM : Int
    val TAG_WIDTH : Int
    val OFFSET_WIDTH : Int
    val REPLACE_POLICY: Int 
}

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
        
    def fromIfu(inter: IFUICacheIO){
        req := inter.cacheReq
        inter.cacheResp := resp
    }
}

class ICache(tagWidth: Int, offsetWidth: Int, wayNum: Int, dataWidth: Int) extends MkModule with CacheParams {
    val io = IO(new CacheIO(tagWidth, dataWidth))
           
}   
