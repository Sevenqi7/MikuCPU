package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

trait BPUConfigs {
    val BPUEnable: Boolean
    val BHTEnable: Boolean
    val RASEnable: Boolean
}

class BranchPredictorResult extends MkBundle {
    // raw prediction result of predictor
    // !NOTE: Use predTaken and predTarget in BranchPredictor to get prediction result
    val taken  = Bool()
    val target = UInt(VADDR_WIDTH.W)
}

class BranchPredictorUpdate extends MkBundle {
    val pc       = UInt(VADDR_WIDTH.W)
    val is_taken = Bool()
    val target   = UInt(VADDR_WIDTH.W)
}

class BranchPredictorIO extends MkBundle {
    val s1     = Flipped(ValidIO(new PCInstBundle(VADDR_WIDTH, INST_BITS)))
    val resp   = new BranchPredictorResult
    val update = Flipped(ValidIO(new BranchPredictorUpdate))
}

abstract class BranchPredictor extends MkModule {
    val io = IO(new BranchPredictorIO)

    // function that generate real prediction result
    // since some predictors' prediction depends not only depends on their own status
    // but also other modules such as BTB, we use independent function to access correct result
    def predTaken:  Bool = io.resp.taken
    def predTarget: UInt = io.resp.target
}

class EmptyPredictor extends BranchPredictor {
    io.resp.taken  := false.B
    io.resp.target := DEBUG_MAGICNUM.U
}

class BTFNPredictor(implicit val btb: MkBTB) extends BTBBasedPredictor {
    io.resp.taken := DontCare

    override def predTaken: Bool = (btb.io.rdata.valid & (predTarget < io.s1.bits.pc))
}

class BranchPredictorWrapper extends BranchPredictor with BPUConfigs {
    override val BPUEnable: Boolean = true
    override val BHTEnable: Boolean = false
    override val RASEnable: Boolean = false

    val s1_inst_br = io.s1.valid && (io.s1.bits.inst(31, 30) === "b01".U)

    implicit val btb = Module(new MkBTB)
    btb.io.s1     := io.s1
    btb.io.update := io.update

    val bht  = Module(if (BHTEnable) new MkBHT else new EmptyPredictor) // TODO:
    val ras  = Module(if (RASEnable) new MkRAS else new EmptyPredictor) // TODO:
    val btfn = Module(new BTFNPredictor)

    val priority_predictor_list = List[BranchPredictor](bht, ras, btfn)
    val priority_predtarget_list: Seq[(Bool, UInt)] = priority_predictor_list.map(i => (i.predTaken, i.predTarget))

    for (i <- priority_predictor_list) {
        i.io.s1.bits.pc   := io.s1.bits.pc
        i.io.s1.bits.inst := io.s1.bits.inst
        i.io.s1.valid     := io.s1.valid
        i.io.update       := io.update
    }

    io.resp.taken  := priority_predictor_list.map(_.predTaken).reduce(_ || _) & s1_inst_br
    io.resp.target := PriorityMux(priority_predtarget_list)
}
