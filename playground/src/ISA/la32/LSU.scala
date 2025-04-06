package miku.isa.la32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.isa.LSUOpType._
import miku.utils._
import miku.backend.MkLSU

class LA32LSU extends MkLSU {

    val is_sc_ll = io.in.bits.optype === scw || io.in.bits.optype === llw
    val rj       = io.in.bits.operand_a
    val rd       = io.in.bits.operand_c
    val imm      = io.in.bits.operand_b

    vaddr := Mux(!is_sc_ll, rj + imm, rj + (imm << 2))
    wdata := rd

    val load_unmatch  = Wire(Bool())
    val load_page_pi  = Wire(Bool())
    val load_page_inv = Wire(Bool())
    load_excp := load_unalign | load_unmatch | load_page_inv | load_page_pi

    switch(lstate) {
        is(lReq) {
            val paddr_v = (RegNext(lstate) =/= lReq)
            when(paddr_v) {
                when(load_excp) {
                    load_buf.exception := MuxCase(
                        LA32ExceptionDefns.INT.enum_no, // error
                        Seq(
                            load_unalign  -> LA32ExceptionDefns.ALE.enum_no,
                            load_unmatch  -> LA32ExceptionDefns.TLBR.enum_no,
                            load_page_inv -> LA32ExceptionDefns.PIL.enum_no,
                            load_page_pi  -> LA32ExceptionDefns.PPI.enum_no
                        )
                    )
                }
            }
        }
        is(lWriteback) {
            val badv_cond = RegNext(load_excp)
            load_wb.bits.result := Mux(badv_cond, load_buf.addr, load_buf.rdata)
        }
    }

    val store_unmatch    = Wire(Bool())
    val store_page_inv   = Wire(Bool())
    val store_page_pi    = Wire(Bool())
    val store_page_modfy = Wire(Bool())
    store_wb_exception := MuxCase(
        ArchExceptionType.NONE.enum_no,
        Seq(
            DelayN(store_unalign, 1) -> LA32ExceptionDefns.ALE.enum_no,
            store_unmatch            -> LA32ExceptionDefns.TLBR.enum_no,
            store_page_inv           -> LA32ExceptionDefns.PIS.enum_no,
            store_page_pi            -> LA32ExceptionDefns.PPI.enum_no,
            store_page_modfy         -> LA32ExceptionDefns.PME.enum_no
        )
    )

    // store-commit
    val is_commit_sc = front_store_inst.wtype === scw
    when(lsu_io.store_commit.valid) {
        // val llbit = io.csr_vec.getTargetCSR(LA32CSRRegisters.LLBCTL).ROLLB
        val llbit = lsu_io.llbit
        assert(!store_queue.io.out.empty)
        store_req.valid := Mux(!is_commit_sc, true.B, llbit)
    }
    store_req.bits.wtype := Mux(!is_commit_sc, front_store_inst.wtype, stw)

    // TLB
    val crmd = io.csr_vec.getTargetCSR(LA32CSRRegisters.CRMD)
    val dmw0 = io.csr_vec.getTargetCSR(LA32CSRRegisters.DMW0)
    val dmw1 = io.csr_vec.getTargetCSR(LA32CSRRegisters.DMW1)
    val dmw  = VecInit(Seq(dmw0, dmw1))

    val pg_mode        = !crmd.DA & crmd.PG
    val da_mode        = crmd.DA & !crmd.PG
    val dmw_total_hits = lsu_io.data_trans.resp.dmw_hits
    val dmw_hit        = dmw_total_hits.reduce(_ || _)
    val dmw_hit_idx    = OHToUInt(dmw_total_hits)
    val tlb_resp       = lsu_io.data_trans.resp.tlb_resp
    val crmd_plv       = crmd.PLV

    load_unmatch  := pg_mode && (lstate === lReq) && !dmw_hit && !tlb_resp.found
    load_page_inv := pg_mode && (lstate === lReq) && !dmw_hit && tlb_resp.found && !tlb_resp.result.v
    load_page_pi := pg_mode && (lstate === lReq) && !dmw_hit && tlb_resp.found && tlb_resp.result.v && (crmd_plv > tlb_resp.result.plv)
    store_unmatch  := pg_mode && store_wb.valid && !dmw_hit && !tlb_resp.found
    store_page_inv := pg_mode && store_wb.valid && !dmw_hit && tlb_resp.found && !tlb_resp.result.v
    store_page_pi := pg_mode && store_wb.valid && !dmw_hit && tlb_resp.found && tlb_resp.result.v && (crmd_plv > tlb_resp.result.plv)
    store_page_modfy := pg_mode && store_wb.valid && !dmw_hit && tlb_resp.found && tlb_resp.result.v && (crmd_plv <= tlb_resp.result.plv) && !tlb_resp.result.d

    uncached := Mux1H(
        Seq(
            (da_mode              -> (crmd.DATM === 0.U)),
            ((pg_mode & dmw_hit)  -> (dmw(dmw_hit_idx).MAT === 0.U)),
            ((pg_mode & !dmw_hit) -> (tlb_resp.result.mat === 0.U))
        )
    )

}
