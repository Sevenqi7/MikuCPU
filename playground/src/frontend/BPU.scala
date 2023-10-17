package miku.frontend

import chisel3._
import chisel3.util._

import miku._

trait BPUParams {
    val BPUEnable : Boolean
    val BTBEnable : Boolean
    val BHTEnable : Boolean
    val RASEnable : Boolean
}

class BranchPredictorResp extends MkBundle{
    val taken = Bool()               
    val target = UInt(VADDR_WIDTH.W)
}

class BranchPredictorIO extends MkBundle{
    val resp = new BranchPredictorResp
}

class BranchPredictor extends MkBundle {
    
}

class BranchPredictorWrapper extends MkModule with BPUParams{
    override val BPUEnable: Boolean = true
    override val BHTEnable: Boolean = true
    override val BTBEnable: Boolean = true
    override val RASEnable: Boolean = false

    assert(BPUEnable == BTBEnable)

}
