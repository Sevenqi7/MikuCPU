package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._

trait BPUParams {
    val BPUEnable: Boolean
    val BHTEnable: Boolean
    val RASEnable: Boolean
}

class BranchPredictorResult extends MkBundle {
    val taken  = Bool()
    val target = UInt(VADDR_WIDTH.W)
}

class BranchPredictorUpdate extends MkBundle {
    val pc       = UInt(VADDR_WIDTH.W)
    val redirect = Bool()
    val target   = UInt(VADDR_WIDTH.W)
}

class BranchPredictorIO extends MkBundle {
    val s0     = Flipped(ValidIO(new PCInstBundle(VADDR_WIDTH, INST_BITS)))
    val resp   = new BranchPredictorResult
    val update = Flipped(ValidIO(new BranchPredictorUpdate))
}

abstract class BranchPredictor extends MkModule {
    val io              = IO(new BranchPredictorIO)
    // val target_from_btb = false
}

class EmptyPredictor extends BranchPredictor {
    io.resp.taken  := false.B
    io.resp.target := 0.U
}

class BranchPredictorWrapper extends BranchPredictor with BPUParams {
    override val BPUEnable: Boolean = true
    override val BHTEnable: Boolean = false
    override val RASEnable: Boolean = true

    val bht = Module(new EmptyPredictor())
    val ras = Module(if (RASEnable) new MkRAS() else new EmptyPredictor)

    val priority_predictor_list = List[BranchPredictorIO](bht.io, ras.io)
    val priority_predtarget_list: Seq[(Bool, UInt)] = priority_predictor_list.map(i => (i.resp.taken, i.resp.target))

    for (i <- priority_predictor_list) {
        i.s0.bits.pc   := io.s0.bits.pc
        i.s0.bits.inst := io.s0.bits.inst
        i.s0.valid     := io.s0.valid
        i.update       := io.update
    }

    io.resp.taken  := priority_predictor_list.map(_.resp.taken).reduce(_ || _)
    io.resp.target := PriorityMux(priority_predtarget_list)
}
