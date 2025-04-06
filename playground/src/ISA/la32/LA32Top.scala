package miku.isa.la32

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._
import miku.backend._
import miku.isa.FuType.lsu

class MkLA32Top extends MkTop {
    val diff = if (DIFFTEST_MODE) Some(IO(new LA32DifftestIO)) else None

    // mmu
    val mmu = Module(new LA32AddrTransUnit)

    val csr_io      = excute.csr_io.asInstanceOf[LA32CSRBufferIO]
    val misc_io     = excute.misc_io.asInstanceOf[LA32MiscFuIO]
    val csr_rf_io   = csr.io.asInstanceOf[LA32CSRRegfilesIO]
    // cacop
    val cacop_inter = misc_io.cacop_inter

    val icacop_en = cacop_inter.req.valid && (cacop_inter.dest === 0.U)
    val dcacop_en = cacop_inter.req.valid && (cacop_inter.dest === 1.U)
    // assert(invalid_dest)
    val cacop_req = cacop_inter.req
    cacop_req.ready := false.B

    when(icacop_en && icache.io.req.ready) {
        frontend.io.icache_inter.req.ready := false.B
        icache.io.req                      <> cacop_req
    }.otherwise {
        icache.io.req <> frontend.io.icache_inter.req
    }
    icache.io.req.bits.paddr := frontend.io.icache_inter.req.bits.paddr //

    val llbit = csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.LLBCTL).ROLLB
    issue.io.llbit        := llbit
    excute.lsu_io.llbit   := llbit
    excute.lsu_io.lr_addr := DontCare

    mmu.io.inst_trans     <> frontend.io.inst_trans
    mmu.io.data_trans     <> csr_io.tlbsrch
    mmu.io.data_trans     <> excute.lsu_io.data_trans
    mmu.io.data_trans     <> misc_io.cacop_trans
    // TODO: 整理、封装tlbsrch端口选择的代码
    mmu.io.data_trans.req := Mux1H(
        Seq(
            csr_io.tlbsrch.req.valid           -> csr_io.tlbsrch.req,
            excute.lsu_io.data_trans.req.valid -> excute.lsu_io.data_trans.req,
            misc_io.cacop_trans.req.valid      -> misc_io.cacop_trans.req
        )
    )

    assert(!(csr_io.tlbsrch.req.valid & excute.lsu_io.data_trans.req.valid & misc_io.cacop_trans.req.valid))
    mmu.io.invtlb_port     := csr_io.invtlb_inter
    mmu.io.tlbrd_port      <> csr_io.tlbrd
    mmu.io.tlbwr_port      := csr_rf_io.tlbwr_wdata
    mmu.io.from_csr.asid   := csr_rf_io.raw_datas.getTargetCSR(LA32CSRRegisters.ASID)
    mmu.io.from_csr.crmd   := csr_rf_io.raw_datas.getTargetCSR(LA32CSRRegisters.CRMD)
    mmu.io.from_csr.dmw(0) := csr_rf_io.raw_datas.getTargetCSR(LA32CSRRegisters.DMW0)
    mmu.io.from_csr.dmw(1) := csr_rf_io.raw_datas.getTargetCSR(LA32CSRRegisters.DMW1)

    csr_rf_io.tlbrd_commit   := csr_io.tlbrd_commit
    csr_rf_io.tlbrd_result   := csr_io.tlbrd_result
    csr_rf_io.tlbwr_commit   := csr_io.tlbwr_commit
    csr_rf_io.tlbfill_commit := csr_io.tlbfill_commit
    csr_rf_io.ll_commit      := issue.io.ll_commit
    csr_rf_io.sc_commit      := issue.io.sc_commit

    when(dcacop_en && dcache.io.req.ready) {
        excute.lsu_io.cache_req.ready := false.B
        dcache.io.req                 <> cacop_req
    }.otherwise {
        dcache.io.req <> excute.lsu_io.cache_req
    }
    dcache.io.req.bits.paddr := excute.lsu_io.cache_req.bits.paddr

    if (DIFFTEST_MODE) {
        diff.get.commit_inst       := issue.io.diff.get.commit_inst
        diff.get.gpr               := issue.io.diff.get.gpr
        diff.get.is_CNTinst        := issue.io.diff.get.is_CNTinst
        diff.get.is_commit_excp    := issue.io.diff.get.is_commit_excp
        diff.get.is_commit_tlbfill := csr_io.tlbfill_commit
        diff.get.tlbfill_index     := mmu.io.tlbwr_port.index
        diff.get.timer_64          := csr_rf_io.timer64_o
        issue.io.lsu_diff.get      := excute.lsu_io.lsu_diff.get

        val csr_types = LA32CSRRegisters.csr_defns.map(_._2)
        diff.get.csr := csr_rf_io.raw_datas
    }
}
