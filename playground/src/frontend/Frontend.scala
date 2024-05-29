package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.isa.la32._
import chisel3.internal.firrtl.MemPortDirection
import miku.isa.CSRVecBundle

class BranchInstInfo extends MkBundle {
    val pc      = UInt(WORD_WIDTH.W)
    val pred    = new BranchPredictorResult
    val mispred = Bool()
    // val br_type = JumpOpType()
}

class FrontendIO extends MkBundle {
    val s1              = ValidIO(new FetchResult)
    val update          = Flipped(ValidIO(new BranchPredictorUpdate))
    val br_pred         = new BranchPredictorResult
    val icache_inter    = new Bundle {
        val req  = Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
        val resp = Flipped(ValidIO(new CacheRespIO(WORD_WIDTH)))
    }
    val inst_queue_full = Input(Bool())
    val inst_trans      = Flipped(new AddrTransChannel)
    val excp_commit     = Flipped(ValidIO(ArchExceptionInfo()))
    val ertn_commit     = Input(Bool())

    // CSR
    val csr_vec = Flipped(new CSRVecBundle)
}

class MkFrontend extends MkModule {
    val io = IO(new FrontendIO())

    val ifu = Module(ArchFetchUnit())
    val bpu = Module(new BranchPredictorWrapper())

    val from_icache = io.icache_inter.resp
    val to_icache   = io.icache_inter.req
    val addr_ok     = to_icache.ready
    val data_ok     = from_icache.valid & from_icache.bits.done

    val npc_set   = 0.U.asTypeOf(new NpcSelInfo())
    npc_set.pred_result          := bpu.io.resp
    npc_set.pred_check.bits      := io.update.bits
    npc_set.pred_check.valid     := io.update.valid
    npc_set.exception.valid      := io.excp_commit.valid
    npc_set.exception.bits.entry := io.csr_vec.getExcpEntry(io.excp_commit.bits.extype)
    npc_set.ertn_target.valid    := io.ertn_commit
    npc_set.ertn_target.bits.era := io.csr_vec.getExcpRetAddr()
    io.inst_trans.req.vaddr      := ifu.io.stage_info.s0.bits.pc
    io.inst_trans.req.valid      := true.B // keep translating s0_pc to ensure we can catch all tlb-related exceptions

    to_icache.bits.wr         := 0.B
    to_icache.bits.vaddr      := ifu.io.stage_info.s0.bits.pc
    to_icache.bits.paddr      := io.inst_trans.resp.paddr
    to_icache.bits.wdata      := 0.U
    to_icache.bits.wtype      := 0.U
    to_icache.bits.uncached   := ifu.io.s0_uncached
    to_icache.bits.cacop_en   := false.B
    to_icache.bits.cacop_func := 0.U
    to_icache.valid           := (ifu.io.stage_info.s0.bits.pc(1, 0) === 0.U)

    io.s1                     := ifu.io.stage_info.s1
    ifu.io.icache_msg.addr_ok := addr_ok
    ifu.io.icache_msg.data_ok := data_ok
    ifu.io.icache_msg.rdata   := from_icache.bits.rdata
    io.br_pred                := bpu.io.resp
    bpu.io.s1                 := ifu.io.stage_info.s1
    bpu.io.update             := io.update
    ifu.io.npc_sel_info       := npc_set
    ifu.io.inst_queue_full    := io.inst_queue_full
    ifu.io.inst_trans_resp    := io.inst_trans.resp
    ifu.io.csr_vec            := io.csr_vec
}
