package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.backend._
import RV32CSRRegisters._
import RV32ExceptionDefns._

class RV32CSRRegfiles extends CSRRegfiles {
    val mtimer_irq = io.interrupt(7)

    // Reset to M_MODE
    val priv = RegInit(3.U(2.W))

    val mepc    = csr_table(MEPC)
    val mcause  = csr_table(MCAUSE)
    val mstatus = csr_table(MSTATUS)
    val mtval   = csr_table(MTVAL)
    val mie     = csr_table(MIE)
    val mip     = csr_table(MIP)

    io.int_flag := mtimer_irq & mie.mtie & mstatus.MIE

    mip.mtip := mtimer_irq

    when(io.excp_commit.valid) {
        mepc.mepc        := io.excp_commit.bits.pc
        mstatus.MIE      := 0.B
        mstatus.MPIE     := mstatus.MIE
        mstatus.MPP      := priv
        mcause.interrupt := io.int_flag
        mcause.code      := getExcpCodeByExcpNo(io.excp_commit.bits.extype)
        priv             := "b11".U

        mtval.mtval := Mux(io.excp_commit.bits.extype =/= RV32ExceptionDefns.INT.enum_no, io.excp_commit.bits.pc, 0.U)
    }

    // MRET COMMIT
    when(io.ertn_commit) {
        priv        := mstatus.MPP
        mstatus.MIE := mstatus.MPIE
        mstatus.MPP := 0.U
    }

}
