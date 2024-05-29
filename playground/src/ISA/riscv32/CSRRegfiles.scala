package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.backend._
import RV32CSRRegisters._
import RV32ExceptionDefns._

class RV32CSRRegfiles extends CSRRegfiles {
    io.int_flag := false.B

    val mepc    = csr_table(MEPC)
    val mcause  = csr_table(MCAUSE)
    val mstatus = csr_table(MSTATUS)
    when(io.excp_commit.valid) {
        mepc.mepc        := io.excp_commit.bits.pc
        mstatus.MIE      := 0.B
        mstatus.MPIE     := mstatus.MIE
        // mstatus.MPP      := "b11".U
        mcause.interrupt := io.int_flag
        mcause.code      := getExcpCodeByExcpNo(io.excp_commit.bits.extype)
    }
}
