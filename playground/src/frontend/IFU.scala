package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.isa.CSRVecBundle

class IFUICacheIO extends MkBundle {
    val addr_ok = Bool()
    val data_ok = Bool()
    val rdata   = UInt(VADDR_WIDTH.W)
}

class NpcSelInfo extends MkBundle {
    val pred_result = new BranchPredictorResult
    val pred_check  = ValidIO(new BranchPredictorUpdate)
    val exception   = ValidIO(new Bundle {
        val entry = UInt(VADDR_WIDTH.W)
    })
    val ertn_target = ValidIO(new Bundle {
        val era = UInt(VADDR_WIDTH.W)
    })
}

class FetchResult extends MkBundle {
    val pc        = UInt(VADDR_WIDTH.W)
    val inst      = UInt(INST_BITS.W)
    val exception = ArchExceptionType()
}

class IFUStageInfo extends MkBundle {
    val s0 = ValidIO(new FetchResult)
    val s1 = ValidIO(new FetchResult)
}

class IFUIO extends MkBundle {
    val icache_msg      = Flipped(new IFUICacheIO())
    val s0_uncached     = Output(Bool())
    val stage_info      = new IFUStageInfo()
    val npc_sel_info    = Flipped(new NpcSelInfo)
    val inst_queue_full = Input(Bool())
    val inst_trans_resp = Flipped(new AddrTransResp)
    val csr_vec         = Flipped(new CSRVecBundle)
}

abstract class MkIFU extends MkModule {
    val io = IO(new IFUIO)

    // IFU-ICache

    // ifu stage 0:
    val s0_pc    = Wire(UInt(WORD_WIDTH.W))
    val s0_valid = Wire(Bool())

    // ifu stage 1:
    val s1_pc    = RegInit(RESET_VECTOR.U(VADDR_WIDTH.W))
    val s1_valid = Wire(Bool())
    val s1_inst  = io.icache_msg.rdata
    //                  cond   npc
    // npc-gen           |      |
    val npc_src  = io.npc_sel_info
    val mispred  = npc_src.pred_check.valid

    val flush_slot = Module(new CircularQueue(UInt(VADDR_WIDTH.W), 1))
    val npc_flush: Seq[(Bool, UInt)] = Seq(
        (npc_src.exception.valid   -> npc_src.exception.bits.entry),
        (npc_src.ertn_target.valid -> npc_src.ertn_target.bits.era),
        (mispred                   -> npc_src.pred_check.bits.target),
        (npc_src.pred_result.taken -> npc_src.pred_result.target),
        (io.inst_queue_full        -> s1_pc)
    )
    flush_slot.io.in.clear := false.B
    flush_slot.io.in.enq_data  := MuxCase(DontCare, npc_flush)
    flush_slot.io.in.enq_valid := npc_flush.map(_._1).reduce(_ || _) && !s0_valid
    flush_slot.io.in.deq_valid := !flush_slot.io.out.empty & s0_valid

    val npc_gen     = npc_flush :+ (!flush_slot.io.out.empty -> flush_slot.io.out.front_data)
    val next_pc     = MuxCase(s1_pc + 4.U, npc_gen)
    val s0_uncached = Wire(Bool())
    val s0_excp     = Wire(ArchExceptionType())
    val s1_excp     = Wire(ArchExceptionType())

    s0_pc    := next_pc
    s0_valid := io.icache_msg.addr_ok & !io.inst_queue_full
    when(s0_valid) {
        s1_pc := s0_pc
    }

    s1_valid := (io.icache_msg.data_ok || (s1_excp =/= ArchExceptionType.NONE.enum_no)) &&
        !(io.inst_queue_full | npc_src.exception.valid & npc_src.ertn_target.valid & mispred) & flush_slot.io.out.empty

    io.s0_uncached                  := s0_uncached
    io.stage_info.s0.bits.pc        := s0_pc
    io.stage_info.s0.bits.inst      := DEBUG_MAGICNUM.U
    io.stage_info.s0.bits.exception := s0_excp
    io.stage_info.s0.valid          := s0_valid
    io.stage_info.s1.bits.pc        := s1_pc
    io.stage_info.s1.bits.inst      := s1_inst
    io.stage_info.s1.bits.exception := s1_excp
    io.stage_info.s1.valid          := s1_valid
}
