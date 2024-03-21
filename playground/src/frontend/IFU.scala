package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class IFUICacheIO extends MkBundle {
    val cache_req  = Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
    val cache_resp = Flipped(ValidIO(new CacheRespIO(WORD_WIDTH)))
}

class NpcSelInfo extends MkBundle {
    val pred_result = new BranchPredictorResult
    val pred_check  = ValidIO(new BranchPredictorUpdate)
    val excepetion  = Bool()
}

class IFUStageInfo extends MkBundle {
    val s0 = ValidIO(new PCInstBundle(VADDR_WIDTH, INST_BITS))
    val s1 = ValidIO(new PCInstBundle(VADDR_WIDTH, INST_BITS))
}

class IFUIO extends MkBundle {
    val icache_msg      = new IFUICacheIO()
    val stage_info      = new IFUStageInfo()
    val npc_sel_info    = Flipped(new NpcSelInfo)
    val inst_queue_full = Input(Bool())
}

class IFU extends MkModule {
    val io = IO(new IFUIO)

    // IFU-ICache
    val from_icache = io.icache_msg.cache_resp
    val to_icache   = io.icache_msg.cache_req
    val addr_ok     = to_icache.valid & to_icache.ready
    val data_ok     = from_icache.valid & from_icache.bits.done

    // ifu stage 0:
    val s0_pc    = Wire(UInt(WORD_WIDTH.W))
    val s0_valid = Wire(Bool())

    // ifu stage 1:
    val s1_pc    = RegEnable(s0_pc, RESET_VECTOR.U(VADDR_WIDTH.W), addr_ok)
    val s1_valid = Wire(Bool())
    val s1_inst  = from_icache.bits.rdata
    //                  cond   npc
    // npc-gen           |      |
    val npc_src  = io.npc_sel_info
    val mispred  = npc_src.pred_check.valid & npc_src.pred_check.bits.redirect
    val npc_gen: Seq[(Bool, UInt)] = Seq(
        (mispred, npc_src.pred_check.bits.target),
        (npc_src.pred_result.taken, npc_src.pred_result.target),
        (true.B, s1_pc + 4.U)
    )
    s0_valid := addr_ok
    s0_pc    := PriorityMux(npc_gen)

    s1_valid := data_ok & !mispred
    s1_pc    := Mux(addr_ok, s0_pc, s1_pc)

    // fetch unit doesn't write cache
    to_icache.bits.wr         := 0.B
    to_icache.bits.addr       := s0_pc
    to_icache.bits.wdata      := 0.U
    to_icache.bits.wtype      := 0.U
    to_icache.bits.uncached   := false.B
    to_icache.bits.cacop_en   := false.B
    to_icache.bits.cacop_func := 0.U
    to_icache.valid           := !io.inst_queue_full

    io.stage_info.s0.bits.pc   := s0_pc
    io.stage_info.s0.bits.inst := from_icache.bits.rdata
    io.stage_info.s0.valid     := s0_valid
    io.stage_info.s1.bits.pc   := s1_pc
    io.stage_info.s1.bits.inst := s1_inst
    io.stage_info.s1.valid     := s1_valid
}
