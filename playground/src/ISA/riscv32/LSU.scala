package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.isa.LSUOpType._
import miku.utils._
import miku.backend.MkLSU

class RV32LSU extends MkLSU {
    val rs1 = io.in.bits.operand_a
    val rs2 = io.in.bits.operand_b
    val imm = io.in.bits.operand_c
    vaddr    := rs1 + imm
    wdata    := rs2
    uncached := false.B

    load_excp := false.B
}
