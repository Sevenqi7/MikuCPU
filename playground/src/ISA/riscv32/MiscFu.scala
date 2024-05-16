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

    io.out.bits.id        := io.in.bits.id
    io.out.bits.exception := io.in.bits.exception
    io.out.bits.result    := DEBUG_MAGICNUM.U
    io.out.valid          := io.in.valid
    io.out.bits.mispred   := false.B
    io.in.ready           := true.B
}
