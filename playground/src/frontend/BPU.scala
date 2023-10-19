package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.frontend._

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

class BranchPredictorUpdate extends MkBundle{
    val pc = UInt(VADDR_WIDTH.W)
    val redirect = Bool() 
    val target = UInt(VADDR_WIDTH.W)
}

class BranchPredictorIO extends MkBundle{
    val s1_pc = Input(UInt(VADDR_WIDTH.W))
    val s1_inst = Input(UInt(INST_BITS.W))
    val resp = ValidIO(new BranchPredictorResp)
    val update = Flipped(new BranchPredictorUpdate)
}

abstract class BranchPredictor extends MkModule{
    val io = IO(new BranchPredictorIO)
}

class BranchPredictorWrapper extends BranchPredictor with BPUParams{
    // these parameters are unused now. currently all predictor is enable defaultly.
    override val BPUEnable: Boolean = true
    override val BHTEnable: Boolean = false
    override val BTBEnable: Boolean = false
    override val RASEnable: Boolean = true

    //BHT must be enabled with BTB
    assert(BHTEnable == BTBEnable)

    val ras = new MkRAS()
    
}
