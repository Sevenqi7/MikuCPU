package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.isa.LSUOpType._
import miku.utils._
import miku.backend.MkLSU

class RV32LSU extends MkLSU {
    def in_mmio(addr: UInt) : Bool = (addr > 0xa0000000L.U)

    val rs1 = io.in.bits.operand_a
    val rs2 = io.in.bits.operand_b

    val imm_I = io.in.bits.operand_b
    val imm_S = io.in.bits.operand_c
    vaddr := rs1 + Mux(isStoreType(io.in.bits.optype), imm_S, imm_I)
    wdata := rs2

    uncached  := DelayN(in_mmio(vaddr), 1)
    load_excp := false.B
}
