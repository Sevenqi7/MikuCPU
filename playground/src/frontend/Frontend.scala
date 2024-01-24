package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class FrontendIO extends MkBundle {
    val s1         = ValidIO(new PCInstBundle(VADDR_WIDTH, INST_BITS))
    val pred_check = Flipped(new BranchPredictorUpdate())
    val exception  = Input(Bool())
    val icache_msg = new IFUICacheIO()
}

class MkFrontend extends MkModule {
    val io = IO(new FrontendIO())

    val ifu = Module(new IFU())
    val bpu = Module(new BranchPredictorWrapper())

    val npc_set = Wire(new NpcSelInfo())
    npc_set.mispredict  := io.pred_check
    npc_set.pred_result := bpu.io.resp
    npc_set.excepetion  := io.exception

    io.s1               := ifu.io.stage_info.s1
    io.icache_msg       <> ifu.io.icache_msg
    bpu.io.s0           := ifu.io.stage_info.s0
    bpu.io.update       := io.pred_check
    ifu.io.npc_sel_info := npc_set
}
