package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.issue._
import miku.utils._
import miku.backend._
import miku.isa.SelImm.IMM_B

class RV32OperandGen extends OperandGenerator {
    def needRs2 = io.decoded_inst.src(2) === SrcType.reg
    def needRs1 = io.decoded_inst.src(1) === SrcType.reg
    def needRd  = io.decoded_inst.src(0) === SrcType.reg
    def needImm = io.decoded_inst.src.map(s => s === SrcType.imm).reduce(_ || _)

    val rs2_gpr_data = io.gpr_rdatas(0)
    val rs2_fwd_data = io.sb_forward.rs2_fwd_data
    val rs2_num      = io.raw_inst(24, 20)
    val rs1_gpr_data = io.gpr_rdatas(1)
    val rs1_fwd_data = io.sb_forward.rs1_fwd_data
    val rs1_num      = io.raw_inst(19, 15)
    val rd_gpr_data  = io.gpr_rdatas(2)
    val rd_fwd_data  = io.sb_forward.rd_fwd_data
    val rd_num       = io.raw_inst(11, 7)

    val rs2_data = Mux(rs2_fwd_data.valid && (rs2_num > 0.U), rs2_fwd_data.bits, io.gpr_rdatas(0))
    val rs1_data = Mux(rs1_fwd_data.valid && (rs1_num > 0.U), rs1_fwd_data.bits, io.gpr_rdatas(1))
    val rd_data  = Mux(rd_fwd_data.valid && (rd_num > 0.U), rd_fwd_data.bits, io.gpr_rdatas(2))

    val imm_I     = SEXT(io.raw_inst(31, 20), WORD_WIDTH)
    val imm_S     = SEXT(Cat(io.raw_inst(31, 25), io.raw_inst(11, 7)), WORD_WIDTH)
    val imm_B     = SEXT(Cat(io.raw_inst(31), io.raw_inst(7), io.raw_inst(30, 25), io.raw_inst(11, 8)), WORD_WIDTH)
    val imm_U     = SEXT(io.raw_inst(31, 12), WORD_WIDTH)
    val imm_J     = SEXT(
        (io.raw_inst(30, 21) | (io.raw_inst(20) << 10) | (io.raw_inst(19, 12) << 11) | (io.raw_inst(31) << 19)),
        WORD_WIDTH
    )
    val imm_table = Seq[(UInt, UInt)](
        SelImm.IMM_I -> imm_I,
        SelImm.IMM_B -> imm_B,
        SelImm.IMM_U -> imm_U,
        SelImm.IMM_J -> imm_J,
        SelImm.IMM_S -> imm_S
    )
    val imm_sel   = io.decoded_inst.selImm
    val imm       = MuxLookup(imm_sel, DEBUG_MAGICNUM.U)(imm_table)
    io.operand_a := Mux(needRs1, rs1_data, io.pc)
    io.operand_b := Mux(needRs2, rs2_data, imm)
    io.operand_c := Mux(needRd, rd_data, imm)

    val opr_a_valid = !needRs1 || (needRs1 & !io.sb_forward.rs1_raw_hazard)
    val opr_b_valid = !needRs2 || (needRs2 & !io.sb_forward.rs2_raw_hazard)
    val opr_c_valid = !needRd || (needRd & !io.sb_forward.rd_raw_hazard)

    io.operand_rdy := opr_a_valid & opr_b_valid & opr_c_valid
}
