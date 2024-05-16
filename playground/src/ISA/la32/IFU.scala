package miku.isa.la32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.frontend._

class LA32IFU extends MkIFU {
    val crmd = io.csr_vec.getTargetCSR(LA32CSRRegisters.CRMD)
    val dmw0 = io.csr_vec.getTargetCSR(LA32CSRRegisters.DMW0)
    val dmw1 = io.csr_vec.getTargetCSR(LA32CSRRegisters.DMW1)
    val dmw  = VecInit(Seq(dmw0, dmw1))

    val pg_mode        = !crmd.DA & crmd.PG
    val da_mode        = crmd.DA & !crmd.PG
    val dmw_total_hits = io.inst_trans_resp.dmw_hits
    val dmw_hit        = dmw_total_hits.reduce(_ || _)
    val dmw_hit_idx    = OHToUInt(dmw_total_hits)
    val tlb_resp       = io.inst_trans_resp.tlb_resp
    val tlb_resp_v     = pg_mode & !dmw_hit

    s0_uncached := Mux1H(
        Seq(
            (da_mode              -> (crmd.DATF === 0.U)),
            ((pg_mode & dmw_hit)  -> (dmw(dmw_hit_idx).MAT === 0.U)),
            ((pg_mode & !dmw_hit) -> (tlb_resp.result.mat === 0.U))
        )
    )

    s0_excp := DontCare
    s1_excp := MuxCase(
        ArchExceptionType.NONE.enum_no,
        Seq(
            (s1_pc(0) | s1_pc(1))                                -> LA32ExceptionDefns.ADEF.enum_no,
            (tlb_resp_v && !tlb_resp.found)                      -> LA32ExceptionDefns.TLBR.enum_no,
            (tlb_resp_v && tlb_resp.found && !tlb_resp.result.v) -> LA32ExceptionDefns.PIF.enum_no,
            (tlb_resp_v && tlb_resp.found && tlb_resp.result.v && (crmd.PLV > tlb_resp.result.plv)) -> LA32ExceptionDefns.PPI.enum_no
        )
    )

}
