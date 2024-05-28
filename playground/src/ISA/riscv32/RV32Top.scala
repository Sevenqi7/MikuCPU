package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class MkRV32Top extends MkTop {
    val diff = if (DIFFTEST_MODE) Some(IO(new RV32DifftestIO)) else None
    // frontend
    frontend.io.inst_trans.resp         := 0.U.asTypeOf(new AddrTransResp)
    frontend.io.inst_trans.resp.paddr   := RegNext(frontend.io.inst_trans.req.vaddr)
    issue.io.llbit                      := false.B
    excute.lsu_io.data_trans.resp       := 0.U.asTypeOf(new AddrTransResp)
    excute.lsu_io.data_trans.resp.paddr := RegNext(excute.lsu_io.data_trans.req.vaddr)

    if (DIFFTEST_MODE) {
        diff.get.commit_inst  := issue.io.diff.get.commit_inst
        diff.get.gpr          := issue.io.diff.get.gpr
        issue.io.lsu_diff.get := excute.lsu_io.lsu_diff.get

        // val csr_types = LA32CSRRegisters.csr_defns.map(_._2)
        // diff.get.csr := csr_rf_io.raw_datass
    }
}
