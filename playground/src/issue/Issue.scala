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
    val exception    = LA32ExceptionType()
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
    val excp_commit  = Bool()
    val ertn_commit  = Bool()
    val ll_commit    = Bool()
    val sc_commit    = Bool()
    val excp_info    = ValidIO(new LA32ExceptionInfo)
    val int_flag     = Input(Bool())
    val llbit        = Input(Bool())

    // DIFFTEST
    val diff     =
        if (DIFFTEST_MODE) Some(new Bundle {
            val gpr            = Vec(32, UInt(WORD_WIDTH.W))
            val commit_inst    = ValidIO(new IssuedInst)
            val is_CNTinst     = Bool()
            val is_commit_excp = Bool()
        })
        else None
    val lsu_diff =
        if (DIFFTEST_MODE) Some(Flipped(new Bundle {
            val paddr = UInt(PADDR_WIDTH.W)
            val vaddr = UInt(VADDR_WIDTH.W)
            val wdata = UInt(WORD_WIDTH.W)
        }))
        else None
}

class IssueStage extends MkModule {
    val io = IO(new IssueStageIO)

    val scoreboard   = Module(new Scoreboard)
    //  Both below two are the same instruction with the input one from deconder, just different representation
    val issued_inst  = scoreboard.io.issue_inst
    val decoded_inst = io.from_decoder.bits.decoded_inst
    scoreboard.io.wb_data          <> io.wb_data
    scoreboard.io.from_decoder     <> io.from_decoder
    scoreboard.io.issue_inst.ready := io.trans.ready
    scoreboard.io.int_flag         := io.int_flag
    io.excp_info                   := scoreboard.io.excp_info

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
    io.trans.bits.fuinput.operand_a := Mux(decoded_inst.needRj, rj_data, io.from_decoder.bits.pc)
    io.trans.bits.fuinput.operand_b := MuxCase(
        DEBUG_MAGICNUM.U,
        Seq(
            (decoded_inst.needRk, rk_data),
            (decoded_inst.needImm, imm)
        )
    )

    // TODO: advance decoding of imm5 to IDU
    val need_imm5 = (decoded_inst.futype === FuType.misc && decoded_inst.fuoptype === MiscOpType.cacop) ||
        (decoded_inst.futype === FuType.csr && decoded_inst.fuoptype === CSROpType.invtlb)
    io.trans.bits.fuinput.operand_c := Mux(need_imm5, issued_inst.bits.sbe.rd_num, rd_data)
    io.trans.bits.fuinput.exception := io.from_decoder.bits.exception
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
    val inst_excp = io.int_flag | (commit_inst_sbe.exception =/= LA32ExceptionType.NONE.enum_no)

    val is_commit_store =
        (commit_inst_sbe.decoded_inst.futype === FuType.lsu) &&
            LSUOpType.isStoreType(commit_inst_sbe.decoded_inst.fuoptype)
    val is_commit_csr   = (commit_inst_sbe.decoded_inst.futype === FuType.csr)
    val is_commit_ertn  =
        (commit_inst_sbe.decoded_inst.futype === FuType.misc) && (commit_inst_sbe.decoded_inst.fuoptype === MiscOpType.ertn)
    val is_commit_idle  =
        (commit_inst_sbe.decoded_inst.futype === FuType.misc) && (commit_inst_sbe.decoded_inst.fuoptype === MiscOpType.idle)
    val is_commit_ll    =
        (commit_inst_sbe.decoded_inst.futype === FuType.lsu) && (commit_inst_sbe.decoded_inst.fuoptype === LSUOpType.llw)
    val is_commit_sc    =
        (commit_inst_sbe.decoded_inst.futype === FuType.lsu) && (commit_inst_sbe.decoded_inst.fuoptype === LSUOpType.scw)
    io.csr_commit.valid   := is_commit_csr & commit_inst.valid & !inst_excp
    io.store_commit.valid := is_commit_store & commit_inst.valid & !inst_excp
    io.ertn_commit        := is_commit_ertn & commit_inst.valid & !inst_excp
    io.ll_commit          := is_commit_ll & commit_inst.valid & !inst_excp
    io.excp_commit        := scoreboard.io.excp_info.valid
    io.sc_commit          := is_commit_sc & commit_inst.valid & commit_inst.ready & !inst_excp

    commit_inst.ready := MuxCase(
        true.B,
        Seq(
            (is_commit_idle, io.int_flag),
            (is_commit_store, io.store_commit.ready),
            (is_commit_csr, io.csr_commit.ready)
        )
    )

    val dest_reg = Mux(commit_inst_sbe.decoded_inst.dest_rj, commit_inst_sbe.rj_num, commit_inst_sbe.rd_num)

    gpr.write_io.waddr := dest_reg
    gpr.write_io.wen   := commit_inst.valid && commit_inst_sbe.decoded_inst.regwen && !io.excp_commit
    gpr.write_io.wdata := Mux(!is_commit_sc, commit_inst.bits.sbe.result, io.llbit)

    if (DIFFTEST_MODE) {
        scoreboard.io.lsu_diff.get    := io.lsu_diff.get
        io.diff.get.commit_inst.bits  := commit_inst.bits
        io.diff.get.commit_inst.valid := commit_inst.valid & commit_inst.ready & !io.excp_commit
        io.diff.get.gpr               := gpr.diff_gpr.get
        io.diff.get.is_commit_excp    := io.excp_commit
        io.diff.get.is_CNTinst        := commit_inst.valid &&
            (commit_inst_sbe.decoded_inst.futype === FuType.misc) &&
            ((commit_inst_sbe.decoded_inst.fuoptype === MiscOpType.rdcntid) ||
                (commit_inst_sbe.decoded_inst.fuoptype === MiscOpType.rdcntvh) ||
                (commit_inst_sbe.decoded_inst.fuoptype === MiscOpType.rdcntvl))
    }
}
