package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku.isa._
import miku.utils._
import miku.backend._

class RV32CSRBuffer extends CSRBuffer {
    csr_busy := false.B
    csr_excp := ArchExceptionType.NONE.enum_no
    csr_addr := 0.U

    csr_wdata         := DEBUG_MAGICNUM.U
    csr_wvalid        := false.B
    io_tlb_busy_stall := false.B
}
