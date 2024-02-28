package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class BranchInstInfo extends MkBundle {
    val pc         = UInt(WORD_WIDTH.W)
    val pred       = new BranchPredictorResult
    val mispredict = Bool()
    // val br_type = JumpOpType()
}

class FrontendIO extends MkBundle {
    val s1         = ValidIO(new PCInstBundle(VADDR_WIDTH, INST_BITS))
    val update     = Flipped(ValidIO(new BranchPredictorUpdate))
    val br_pred    = new BranchPredictorResult
    // val exception  = Input(Bool())
    val icache_msg = new IFUICacheIO()
}

class MkFrontend extends MkModule {
    val io = IO(new FrontendIO())

    val ifu = Module(new IFU())
    val bpu = Module(new BranchPredictorWrapper())

    val npc_set = 0.U.asTypeOf(new NpcSelInfo())
    npc_set.mispredict  := io.update
    npc_set.pred_result := bpu.io.resp
    // npc_set.excepetion  := io.exception

    io.s1               := ifu.io.stage_info.s1
    io.icache_msg       <> ifu.io.icache_msg
    io.br_pred          := bpu.io.resp
    bpu.io.s0           := ifu.io.stage_info.s0
    bpu.io.update       := io.update
    ifu.io.npc_sel_info := npc_set
}
