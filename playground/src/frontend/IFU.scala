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
    val mispredict  = ValidIO(new BranchPredictorUpdate)
    val excepetion  = Bool()
}

class IFUStageInfo extends MkBundle {
    val s0 = ValidIO(new PCInstBundle(VADDR_WIDTH, INST_BITS))
    val s1 = ValidIO(new PCInstBundle(VADDR_WIDTH, INST_BITS))
}

class IFUIO extends MkBundle {
    val icache_msg   = new IFUICacheIO()
    val stage_info   = new IFUStageInfo()
    val npc_sel_info = Flipped(new NpcSelInfo)
}

class IFU extends MkModule {
    val io = IO(new IFUIO)

    // IFU-ICache
    val from_icache = io.icache_msg.cache_resp
    val to_icache   = io.icache_msg.cache_req
    val addr_ok     = to_icache.valid & to_icache.ready
    val data_ok     = from_icache.valid & from_icache.bits.done

    val npc_src   = io.npc_sel_info
    val s0_pc     = RegInit(RESET_VECTOR.U(VADDR_WIDTH.W))
    val s0_valid  = RegInit(false.B) // TODO: set stall condition
    val pc_plus_4 = s0_pc + 4.U
    //                  cond   npc
    // npc-gen           |      |
    val npc_gen: Seq[(Bool, UInt)] = Seq(
        (npc_src.mispredict.valid & npc_src.mispredict.bits.redirect, npc_src.mispredict.bits.target),
        (npc_src.pred_result.taken, npc_src.pred_result.target),
        (true.B, s0_pc + 4.U)
    )
    val npc = PriorityMux(npc_gen)
    s0_valid := addr_ok
    s0_pc    := Mux(addr_ok, npc, s0_pc)

    val s1_pc    = RegEnable(s0_pc, data_ok)
    val s1_inst  = RegEnable(from_icache.bits.rdata, data_ok)
    val s1_valid = RegNext(data_ok)

    // fetch unit doesn't write cache
    to_icache.bits.wr       := 0.B
    to_icache.bits.addr     := npc
    to_icache.bits.wdata    := 0.U
    to_icache.bits.wtype    := 0.U
    to_icache.bits.uncached := false.B
    to_icache.valid         := true.B

    io.stage_info.s0.bits.pc   := s0_pc
    io.stage_info.s0.bits.inst := from_icache.bits.rdata
    io.stage_info.s0.valid     := s0_valid
    io.stage_info.s1.bits.pc   := s1_pc
    io.stage_info.s1.bits.inst := s1_inst
    io.stage_info.s1.valid     := s1_valid
}
