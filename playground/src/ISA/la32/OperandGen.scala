package miku.isa.la32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.utils._
import miku.issue._
import miku.backend._

class LA32OperandGen extends OperandGenerator {
    // src(2), src(1), src(0) seperately represent rk, rj, rd if there value is reg
    def needRk  = io.decoded_inst.src(2) === SrcType.reg
    def needRj  = io.decoded_inst.src(1) === SrcType.reg
    def needRd  = io.decoded_inst.src(0) === SrcType.reg
    def needImm = io.decoded_inst.src.map(s => s === SrcType.imm).reduce(_ || _)

    val rk_gpr_data = io.gpr_rdatas(0)
    val rk_fwd_data = io.sb_forward.rs2_fwd_data
    val rk_num      = io.raw_inst(14, 10)
    val rj_gpr_data = io.gpr_rdatas(1)
    val rj_fwd_data = io.sb_forward.rs1_fwd_data
    val rj_num      = io.raw_inst(9, 5)
    val rd_gpr_data = io.gpr_rdatas(2)
    val rd_fwd_data = io.sb_forward.rd_fwd_data
    val rd_num      = io.raw_inst(4, 0)

    val rk_data = Mux(rk_fwd_data.valid && (rk_num > 0.U), rk_fwd_data.bits, io.gpr_rdatas(0))
    val rj_data = Mux(rj_fwd_data.valid && (rj_num > 0.U), rj_fwd_data.bits, io.gpr_rdatas(1))
    val rd_data = Mux(rd_fwd_data.valid && (rd_num > 0.U), rd_fwd_data.bits, io.gpr_rdatas(2))

    val imm_sel   = io.decoded_inst.selImm
    val imm_table = Seq[(UInt, UInt)](
        SelImm.IMM_U8  -> UEXT(io.raw_inst(17, 10), WORD_WIDTH),
        SelImm.IMM_S12 -> SEXT(io.raw_inst(21, 10), WORD_WIDTH),
        SelImm.IMM_U12 -> UEXT(io.raw_inst(21, 10), WORD_WIDTH),
        SelImm.IMM_S14 -> SEXT(io.raw_inst(23, 10), WORD_WIDTH),
        SelImm.IMM_S16 -> SEXT(io.raw_inst(25, 10), WORD_WIDTH),
        SelImm.IMM_S20 -> SEXT(io.raw_inst(24, 5), WORD_WIDTH),
        SelImm.IMM_S26 -> SEXT(Cat(io.raw_inst(9, 0), io.raw_inst(25, 10)), WORD_WIDTH)
    )
    val imm       = MuxLookup(imm_sel, DEBUG_MAGICNUM.U)(imm_table)
    val need_imm5 = (io.decoded_inst.futype === FuType.misc && io.decoded_inst.fuoptype === MiscOpType.cacop) ||
        (io.decoded_inst.futype === FuType.csr && io.decoded_inst.fuoptype === CSROpType.invtlb)

    io.operand_a := Mux(needRj, rj_data, io.pc)
    io.operand_b := MuxCase(
        DEBUG_MAGICNUM.U,
        Seq(
            (needRk, rk_data),
            (needImm, imm)
        )
    )
    io.operand_c := Mux(need_imm5, io.raw_inst(4, 0), rd_data)

    val opr_a_valid = !needRj || (needRj & !io.sb_forward.rs1_raw_hazard)
    val opr_b_valid = !needRk || (needRk & !io.sb_forward.rs2_raw_hazard)
    val opr_c_valid = !needRd || (needRd & !io.sb_forward.rd_raw_hazard)

    // TODO: advance decoding of imm5 to IDU

    io.operand_rdy := opr_a_valid & opr_b_valid & opr_c_valid
}
