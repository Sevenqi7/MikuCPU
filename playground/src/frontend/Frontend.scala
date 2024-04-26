package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import chisel3.internal.firrtl.MemPortDirection

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
    val excp_commit     = Flipped(ValidIO(new LA32ExceptionInfo))
    val ertn_commit     = Input(Bool())

    // CSR
    val from_csr = Flipped(new Bundle {
        val crmd      = new LA32CSR_Crmd
        val eentry    = new LA32CSR_Eentry
        val tlbrentry = new LA32CSR_Tlbrentry
        val era       = new LA32CSR_Era
        val dwm       = Vec(2, new LA32CSR_Dmw)
    })
}

class MkFrontend extends MkModule {
    val io = IO(new FrontendIO())

    val ifu = Module(new IFU())
    val bpu = Module(new BranchPredictorWrapper())

    val from_icache = io.icache_inter.resp
    val to_icache   = io.icache_inter.req
    val addr_ok     = to_icache.ready
    val data_ok     = from_icache.valid & from_icache.bits.done

    val npc_set   = 0.U.asTypeOf(new NpcSelInfo())
    val excp_tlbr = io.excp_commit.valid & (io.excp_commit.bits.extype === LA32ExceptionType.TLBR.enum_no)
    npc_set.pred_result          := bpu.io.resp
    npc_set.pred_check.bits      := io.update.bits
    npc_set.pred_check.valid     := io.update.valid
    npc_set.exception.valid      := io.excp_commit.valid
    npc_set.exception.bits.entry := Mux(excp_tlbr, io.from_csr.tlbrentry.rdata, io.from_csr.eentry.rdata)
    npc_set.ertn_target.valid    := io.ertn_commit
    npc_set.ertn_target.bits.era := io.from_csr.era.rdata

    // fetch unit doesn't write cache
    val pg_mode        = !io.from_csr.crmd.DA & io.from_csr.crmd.PG
    val da_mode        = io.from_csr.crmd.DA & !io.from_csr.crmd.PG
    val dmw_total_hits = io.inst_trans.dmw_hits
    val dmw_hit        = dmw_total_hits.reduce(_ || _)
    val dmw_hit_idx    = OHToUInt(dmw_total_hits)
    val tlb_resp       = io.inst_trans.tlb_resp
    io.inst_trans.vaddr      := ifu.io.stage_info.s0.bits.pc
    io.inst_trans.valid      := true.B // keep translating s0_pc to ensure we can catch all tlb-related exceptions
    io.inst_trans.tlbsrch_en := false.B

    to_icache.bits.wr         := 0.B
    to_icache.bits.vaddr      := ifu.io.stage_info.s0.bits.pc
    to_icache.bits.paddr      := io.inst_trans.paddr
    to_icache.bits.wdata      := 0.U
    to_icache.bits.wtype      := 0.U
    // to_icache.bits.uncached   := 0.B
    to_icache.bits.uncached   := Mux1H(
        Seq(
            (da_mode              -> (io.from_csr.crmd.DATF === 0.U)),
            ((pg_mode & dmw_hit)  -> (io.from_csr.dwm(dmw_hit_idx).MAT === 0.U)),
            ((pg_mode & !dmw_hit) -> (tlb_resp.result.mat === 0.U))
        )
    )
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
    ifu.io.tlb_resp           := io.inst_trans.tlb_resp
    ifu.io.tlb_resp_v         := pg_mode & !dmw_hit
    ifu.io.crmd_plv           := io.from_csr.crmd.PLV
}
