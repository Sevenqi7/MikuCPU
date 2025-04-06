package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.isa.FuType.lsu

class MkRV32Top extends MkTop {
    val diff = if (DIFFTEST_MODE) Some(IO(new RV32DifftestIO)) else None
    // frontend
    frontend.io.inst_trans.resp         := 0.U.asTypeOf(new AddrTransResp)
    frontend.io.inst_trans.resp.paddr   := RegNext(frontend.io.inst_trans.req.vaddr)
    excute.lsu_io.data_trans.resp       := 0.U.asTypeOf(new AddrTransResp)
    excute.lsu_io.data_trans.resp.paddr := RegNext(excute.lsu_io.data_trans.req.vaddr)

    val lrbit   = RegInit(false.B)
    val lr_addr = RegInit(0.U(VADDR_WIDTH.W))
    lrbit := MuxCase(
        lrbit,
        Seq(
            issue.io.ll_commit -> true.B,
            issue.io.sc_commit -> false.B
        )
    )
    val sc_success = issue.io.sc_commit && (issue.io.lr_sc_addr === lr_addr) && lrbit
    when(issue.io.ll_commit) {
        lr_addr := issue.io.lr_sc_addr
    }

    issue.io.llbit        := !sc_success
    excute.lsu_io.llbit   := lrbit
    excute.lsu_io.lr_addr := lr_addr
 
    if (DIFFTEST_MODE) {
        diff.get.commit_inst    := issue.io.diff.get.commit_inst
        diff.get.is_commit_excp := issue.io.diff.get.is_commit_excp
        diff.get.gpr            := issue.io.diff.get.gpr
        issue.io.lsu_diff.get   := excute.lsu_io.lsu_diff.get

        // val csr_types = LA32CSRRegisters.csr_defns.map(_._2)
        diff.get.csr := csr.io.raw_datas
    }
}
