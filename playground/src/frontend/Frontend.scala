package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class BranchInstInfo extends MkBundle {
    val pc      = UInt(WORD_WIDTH.W)
    val pred    = new BranchPredictorResult
    val mispred = Bool()
    // val br_type = JumpOpType()
}

class FrontendIO extends MkBundle {
    val s1              = ValidIO(new PCInstBundle(VADDR_WIDTH, INST_BITS))
    val update          = Flipped(ValidIO(new BranchPredictorUpdate))
    val br_pred         = new BranchPredictorResult
    // val exception  = Input(Bool())
    val icache_msg      = new IFUICacheIO()
    val inst_queue_full = Input(Bool())
}

class MkFrontend extends MkModule {
    val io = IO(new FrontendIO())

    val ifu = Module(new IFU())
    val bpu = Module(new BranchPredictorWrapper())

    // A slot that temporarily storage branch update information from branch unit.
    // Since PC we used to fetch the instruction is a Wire not Reg, this slot is designed
    // to ensure that IFU can use the correct address to fetch even if the branch inst in EXU has retired.
    val update_slot = Module(new CircularQueue(new BranchPredictorUpdate, 1))
    update_slot.io.in.clear     := false.B
    update_slot.io.in.enq_data  := io.update.bits
    update_slot.io.in.enq_valid := update_slot.io.out.empty & io.update.valid & io.update.bits.redirect
    update_slot.io.in.deq_valid := !update_slot.io.out.empty & ifu.io.stage_info.s0.valid

    val npc_set = 0.U.asTypeOf(new NpcSelInfo())
    npc_set.pred_result      := bpu.io.resp
    npc_set.pred_check.bits  := update_slot.io.out.front_data
    npc_set.pred_check.valid := !update_slot.io.out.empty
    // npc_set.excepetion  := io.exception

    io.s1                  := ifu.io.stage_info.s1
    io.icache_msg          <> ifu.io.icache_msg
    io.br_pred             := bpu.io.resp
    bpu.io.s0              := ifu.io.stage_info.s0
    bpu.io.update          := io.update
    ifu.io.npc_sel_info    := npc_set
    ifu.io.inst_queue_full := io.inst_queue_full
}
