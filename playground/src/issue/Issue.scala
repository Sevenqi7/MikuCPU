package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._
import miku.backend._
import miku.FuType._
import java.util.concurrent.Future

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
    val store_commit = new ReadyValidBundle
    val csr_commit   = new ReadyValidBundle
    val diff         =
        if (DIFFTEST_MODE) Some(new Bundle {
            val gpr         = Vec(32, UInt(WORD_WIDTH.W))
            val commit_inst = ValidIO(new IssuedInst)
            val is_CNTinst  = Bool()
        })
        else None
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
    gpr.read_io(0).raddr := issued_inst.bits.sbe.rk_num
    gpr.read_io(1).raddr := issued_inst.bits.sbe.rj_num
    gpr.read_io(2).raddr := issued_inst.bits.sbe.rd_num

    val rk_gpr_data = gpr.read_io(0).rdata
    val rk_fwd_data = scoreboard.io.forward_msg.rk_fwd_data
    val rj_gpr_data = gpr.read_io(1).rdata
    val rj_fwd_data = scoreboard.io.forward_msg.rj_fwd_data
    val rd_gpr_data = gpr.read_io(2).rdata
    val rd_fwd_data = scoreboard.io.forward_msg.rd_fwd_data

    val rk_data = Mux(rk_fwd_data.valid && (issued_inst.bits.sbe.rk_num > 0.U), rk_fwd_data.bits, rk_gpr_data)
    val rj_data = Mux(rj_fwd_data.valid && (issued_inst.bits.sbe.rj_num > 0.U), rj_fwd_data.bits, rj_gpr_data)
    val rd_data = Mux(rd_fwd_data.valid && (issued_inst.bits.sbe.rd_num > 0.U), rd_fwd_data.bits, rd_gpr_data)

    // immdiate number selection
    val imm_sel   = decoded_inst.selImm
    val raw_inst  = io.from_decoder.bits.inst
    val imm_table = Seq[(UInt, UInt)](
        SelImm.IMM_U8  -> UEXT(raw_inst(17, 10), WORD_WIDTH),
        SelImm.IMM_S12 -> SEXT(raw_inst(21, 10), WORD_WIDTH),
        SelImm.IMM_U12 -> UEXT(raw_inst(21, 10), WORD_WIDTH),
        SelImm.IMM_S14 -> SEXT(raw_inst(23, 10), WORD_WIDTH),
        SelImm.IMM_S16 -> SEXT(raw_inst(25, 10), WORD_WIDTH),
        SelImm.IMM_S20 -> SEXT(raw_inst(24, 5), WORD_WIDTH),
        SelImm.IMM_S26 -> SEXT(Cat(raw_inst(9, 0), raw_inst(25, 10)), WORD_WIDTH)
    )
    val imm       = MuxLookup(imm_sel, DEBUG_MAGICNUM.U)(imm_table)

    io.trans.valid                  := issued_inst.valid
    io.trans.bits.fuinput.id        := issued_inst.bits.id
    io.trans.bits.fuinput.pc        := io.from_decoder.bits.pc
    io.trans.bits.fuinput.flush     := false.B // TODO: add conditon
    io.trans.bits.fuinput.operand_a := Mux(decoded_inst.needRj, rj_data, io.from_decoder.bits.pc)
    io.trans.bits.fuinput.operand_b := MuxCase(
        DEBUG_MAGICNUM.U,
        Seq(
            (decoded_inst.needRk, rk_data),
            (decoded_inst.needImm, imm)
        )
    )
    val need_imm5 = (decoded_inst.futype === FuType.misc && decoded_inst.fuoptype === MiscOpType.cacop)
    io.trans.bits.fuinput.operand_c := Mux(need_imm5, issued_inst.bits.sbe.rd_num, rd_data)
    io.trans.bits.fuinput.optype    := decoded_inst.fuoptype
    io.trans.bits.futype            := decoded_inst.futype

    val opr_a_valid = !decoded_inst.needRj || (decoded_inst.needRj & !scoreboard.io.forward_msg.rj_raw_hazard)
    val opr_b_valid = !decoded_inst.needRk || (decoded_inst.needRk & !scoreboard.io.forward_msg.rk_raw_hazard)
    val opr_c_valid = !decoded_inst.needRd || (decoded_inst.needRd & !scoreboard.io.forward_msg.rd_raw_hazard)
    scoreboard.io.operands_rdy := opr_a_valid & opr_b_valid & opr_c_valid

    // commit logic
    val commit_inst     = scoreboard.io.commit_inst
    val commit_inst_sbe = commit_inst.bits.sbe

    // check whether we are committing a store inst
    val is_commit_store =
        (commit_inst_sbe.decoded_inst.futype === FuType.lsu) &&
            LSUOpType.isStoreType(commit_inst_sbe.decoded_inst.fuoptype)
    val is_commit_csr   = (commit_inst_sbe.decoded_inst.futype === FuType.csr)
    io.csr_commit.valid   := is_commit_csr & commit_inst.valid
    io.store_commit.valid := is_commit_store & commit_inst.valid
    commit_inst.ready     := MuxCase(
        true.B,
        Seq(
            (is_commit_store, io.store_commit.ready),
            (is_commit_csr, io.csr_commit.ready)
        )
    )

    gpr.write_io.waddr := commit_inst.bits.sbe.rd_num
    gpr.write_io.wen   := commit_inst.valid && commit_inst_sbe.decoded_inst.regwen
    gpr.write_io.wdata := commit_inst.bits.sbe.result

    if (DIFFTEST_MODE) {
        io.diff.get.commit_inst.bits  := commit_inst.bits
        io.diff.get.commit_inst.valid := commit_inst.valid & commit_inst.ready
        io.diff.get.gpr               := gpr.diff_gpr.get
        io.diff.get.is_CNTinst        := commit_inst.valid &&
            (commit_inst_sbe.decoded_inst.futype === FuType.misc) &&
            ((commit_inst_sbe.decoded_inst.fuoptype === MiscOpType.rdcntid) ||
                (commit_inst_sbe.decoded_inst.fuoptype === MiscOpType.rdcntvh) ||
                (commit_inst_sbe.decoded_inst.fuoptype === MiscOpType.rdcntvl))
    }
}
