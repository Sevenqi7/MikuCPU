package miku.isa.la32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.utils._
import miku.backend.MkBRU
import miku.isa.JumpOpType._

// import miku.isa.la32.

class LA32BranchUnit extends MkBRU {
    def isBr(optype: UInt)    = ((optype <= bgeu))
    def isBorBl(optype: UInt) = ((optype === b) || (optype === bl))
    def isJirl(optype: UInt)  = (optype === jirl)

    val rj = lval
    val rd = rval

    val imm16 = io.in.bits.operand_b(15, 0)
    val imm26 = io.in.bits.operand_b(25, 0)

    link_flag := isJirl(io.in.bits.optype) || (io.in.bits.optype === bl)

    val jtype_list = Seq(
        bl   -> true.B,
        b    -> true.B,
        jirl -> true.B
    )
    jtype_taken := MuxLookup(io.in.bits.optype, false.B)(jtype_list)

    br_target := MuxCase(
        pc + 4.U,
        Seq(
            (taken & isBr(io.in.bits.optype), pc + SEXT(imm16 << 2, VADDR_WIDTH)),
            (taken & isBorBl(io.in.bits.optype), pc + SEXT(imm26 << 2, VADDR_WIDTH)),
            (taken & isJirl(io.in.bits.optype), rj + SEXT(imm16 << 2, VADDR_WIDTH))
        )
    )
}
