package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.backend._
import miku.utils.SEXT
import miku.isa.JumpOpType._

// import
class RV32BranchUnit extends MkBRU {
    val imm_IJ = io.in.bits.operand_b
    val imm_B  = io.in.bits.operand_c
    val rs1    = io.in.bits.operand_a
    val rs2    = io.in.bits.operand_b

    lval := rs1
    rval := rs2

    val is_jal  = (io.in.bits.optype === jal)
    val is_jalr = (io.in.bits.optype === jalr)

    val imm = Mux(is_jal | is_jalr, imm_IJ, imm_B)

    link_flag   := is_jal | is_jalr
    jtype_taken := is_jal | is_jalr

    br_target := MuxCase(
        pc + 4.U,
        Seq(
            (taken & is_jalr) -> (rs1 + imm),
            taken             -> (pc + (SEXT(imm(19, 0), WORD_WIDTH) << 1))
        )
    )
}
