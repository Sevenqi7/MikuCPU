package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class MkRV32Top extends MkTop {
    // frontend
    frontend.io.inst_trans.resp         := 0.U.asTypeOf(new AddrTransResp)
    frontend.io.inst_trans.resp.paddr   := RegNext(frontend.io.inst_trans.req.vaddr)
    issue.io.llbit                      := false.B
    excute.lsu_io.data_trans.resp       := 0.U.asTypeOf(new AddrTransResp)
    excute.lsu_io.data_trans.resp.paddr := RegNext(excute.lsu_io.data_trans.req.vaddr)
}
