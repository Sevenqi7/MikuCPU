package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.frontend._
import miku.isa.MiscOpType._
import miku.backend.MiscFunctionUnit

// TODO: implement miscellaneous instruction in riscv32, ECALL for example.
class RV32MiscFu extends MiscFunctionUnit {
    val misc_io = IO(new Bundle {})

    val priv = io.csr_vec.getTargetCSR(RV32CSRRegisters.PRIV)

    val ecall_valid = io.in.valid && (io.in.bits.optype === ecall)
    val u_mode      = priv.priv === 0.U
    val m_mode      = priv.priv === 3.U

    io.out.bits.id        := io.in.bits.id
    io.out.bits.exception := MuxCase(
        io.in.bits.exception,
        Seq(
            (ecall_valid & m_mode) -> RV32ExceptionDefns.MECALL.enum_no,
            (ecall_valid & u_mode) -> RV32ExceptionDefns.UECALL.enum_no
        )
    )
    io.out.bits.result    := DEBUG_MAGICNUM.U
    io.out.valid          := io.in.valid
    io.out.bits.mispred   := false.B
    io.in.ready           := true.B
}
