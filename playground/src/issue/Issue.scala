package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._
import miku.backend._
import miku.FuType._

class IssueEntry extends MkBundle {
    val pc           = UInt(VADDR_WIDTH.W)
    val inst         = UInt(INST_BITS.W)
    val decoded_inst = new DecodedInst()
    val br_pred      = new BranchPredictorResult
}

class IssueStageIO extends MkBundle {
    val from_decoder = Flipped(Decoupled(new IssueEntry))
    val wb_data      = Flipped(Vec(NR_WB_PORTS, Decoupled(new WriteBackResult)))
    val trans        = Decoupled(new Bundle {
        val fuinput = new BaseFuInput {}
        val futype  = FuType()
    })
    // transcation that will be excuted in function unit
}

class IssueStage extends MkModule {
    val io = IO(new IssueStageIO)

    val scoreboard   = Module(new Scoreboard)
    //  Both below two are the same instruction with the input one from deconder, just different representation
    val issued_inst  = scoreboard.io.issue_inst
    val decoded_inst = io.from_decoder.bits.decoded_inst
    scoreboard.io.wb_data          <> io.wb_data
    scoreboard.io.flush            := false.B // TODO: add condition
    scoreboard.io.from_decoder     <> io.from_decoder
    scoreboard.io.issue_inst.ready := io.trans.ready

    // read operands of the issued instruction from scoreboard
    val gpr = Module(new MkRegfiles)
    gpr.read_io(0).rf_rs_i := issued_inst.bits.sbe.rk_num
    gpr.read_io(1).rf_rs_i := issued_inst.bits.sbe.rj_num
    gpr.read_io(2).rf_rs_i := issued_inst.bits.sbe.rd_num

    val rk_gpr_data = gpr.read_io(0).rf_rs_o
    val rk_fwd_data = scoreboard.io.forward_msg.rk_fwd_data
    val rj_gpr_data = gpr.read_io(1).rf_rs_o
    val rj_fwd_data = scoreboard.io.forward_msg.rj_fwd_data
    val rd_gpr_data = gpr.read_io(2).rf_rs_o
    val rd_fwd_data = scoreboard.io.forward_msg.rd_fwd_data

    val rk_data = Mux(rk_fwd_data.valid, rk_fwd_data.bits, rk_gpr_data)
    val rj_data = Mux(rj_fwd_data.valid, rj_fwd_data.bits, rj_gpr_data)
    val rd_data = Mux(rd_fwd_data.valid, rd_fwd_data.bits, rd_gpr_data)

    // immdiate number selection

    val imm_sel   = decoded_inst.selImm
    val imm_table = Seq[(UInt, UInt)](
        SelImm.IMM_U8  -> UEXT(io.from_decoder.bits.inst(17, 10), WORD_WIDTH),
        SelImm.IMM_S12 -> SEXT(io.from_decoder.bits.inst(21, 10), WORD_WIDTH),
        SelImm.IMM_U12 -> UEXT(io.from_decoder.bits.inst(21, 10), WORD_WIDTH),
        SelImm.IMM_S14 -> SEXT(io.from_decoder.bits.inst(23, 10), WORD_WIDTH),
        SelImm.IMM_S16 -> SEXT(io.from_decoder.bits.inst(25, 10), WORD_WIDTH),
        SelImm.IMM_S20 -> SEXT(Cat(io.from_decoder.bits.inst(4, 0), io.from_decoder.bits.inst(21, 10)), WORD_WIDTH),
        SelImm.IMM_S26 -> SEXT(Cat(io.from_decoder.bits.inst(9, 0), io.from_decoder.bits.inst(21, 10)), WORD_WIDTH)
    )
    val imm       = MuxLookup(imm_sel, DEBUG_MAGICNUM.U)(imm_table)

    io.trans.valid                  := issued_inst.valid
    io.trans.bits.fuinput.id        := issued_inst.bits.id
    io.trans.bits.fuinput.pc        := io.from_decoder.bits.pc
    io.trans.bits.fuinput.flush     := false.B // TODO: add conditon
    io.trans.bits.fuinput.operand_a := rj_data
    io.trans.bits.fuinput.operand_b := MuxCase(
        DEBUG_MAGICNUM.U,
        Seq(
            (decoded_inst.needRk, rk_data),
            (decoded_inst.needImm, imm)
        )
    )
    io.trans.bits.fuinput.operand_c := rd_data
    io.trans.bits.fuinput.optype    := decoded_inst.fuoptype
    io.trans.bits.futype            := decoded_inst.futype

    val opr_a_valid = decoded_inst.needRj & !scoreboard.io.forward_msg.rj_raw_hazard
    val opr_b_valid = decoded_inst.needRk & !scoreboard.io.forward_msg.rk_raw_hazard
    val opr_c_valid = decoded_inst.needRd & !scoreboard.io.forward_msg.rd_raw_hazard
    scoreboard.io.operands_rdy := opr_a_valid & opr_b_valid & opr_c_valid

    // commit logic
    val commit_inst = scoreboard.io.commit_inst
    commit_inst.ready       := true.B // ?: correctness need checked
    gpr.write_io.rf_ws_i    := commit_inst.bits.sbe.rd_num
    gpr.write_io.rf_ws_en   := commit_inst.valid && commit_inst.bits.sbe.decoded_inst.regwen
    gpr.write_io.rf_ws_data := commit_inst.bits.sbe.result
}
