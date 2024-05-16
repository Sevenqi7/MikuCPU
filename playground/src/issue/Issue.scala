package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._
import miku.backend._
import miku.isa._
import miku.isa.la32._

class IssueEntry extends MkBundle {
    val pc           = UInt(VADDR_WIDTH.W)
    val inst         = UInt(INST_BITS.W)
    val decoded_inst = ArchDecodedInst()
    val br_pred      = new BranchPredictorResult
    val exception    = ArchExceptionType()
}

abstract class OperandGenerator extends MkModule {
    val io = IO(new Bundle {
        val pc           = Input(UInt(VADDR_WIDTH.W))
        val raw_inst     = Input(UInt(INST_BITS.W))
        val decoded_inst = Input(ArchDecodedInst())
        val gpr_rdatas   = Input(Vec(3, UInt(WORD_WIDTH.W)))
        val sb_forward   = Flipped(new ScoreboardFowardInfo)
        val operand_a    = Output(UInt(WORD_WIDTH.W))
        val operand_b    = Output(UInt(WORD_WIDTH.W))
        val operand_c    = Output(UInt(WORD_WIDTH.W))
        val operand_rdy  = Output(Bool())
    })
}

class CommitInfo extends MkBundle {
    val csr_cmt   = new ReadyValidBundle
    val store_cmt = new ReadyValidBundle
    val excp_cmt  = ArchExceptionInfo()
    val ertn_cmt  = Bool()
    val ll_cmt    = Bool()
    val sc_cmt    = Bool()
}

class IssueStageIO extends MkBundle {
    val from_decoder = Flipped(Decoupled(new IssueEntry))
    val wb_data      = Flipped(Vec(NR_WB_PORTS, Decoupled(new WriteBackResult)))
    val trans        = Decoupled(new Bundle {
        val fuinput = new BaseFuInput {}
        val futype  = FuType()
        val br_pred = new BranchPredictorResult
    })
    // val cmt_info     = new CommitInfo
    val store_commit = new ReadyValidBundle
    val csr_commit   = new ReadyValidBundle
    val excp_commit  = ValidIO(ArchExceptionInfo())
    val ertn_commit  = Bool()
    val ll_commit    = Bool()
    val sc_commit    = Bool()
    val int_flag     = Input(Bool())
    val llbit        = Input(Bool())
    val timer64      = Input(UInt(64.W))

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
    scoreboard.io.llbit            := io.llbit
    scoreboard.io.timer64_val      := io.timer64
    io.excp_commit                 := scoreboard.io.excp_info

    // read operands of the issued instruction from scoreboard
    val gpr = Module(new MkRegfiles)
    gpr.read_io(0).raddr := issued_inst.bits.sbe.rs2
    gpr.read_io(1).raddr := issued_inst.bits.sbe.rs1
    gpr.read_io(2).raddr := issued_inst.bits.sbe.rd

    val opr_gen = Module(isaFactory.getOperandGen())
    opr_gen.io.decoded_inst := io.from_decoder.bits.decoded_inst
    opr_gen.io.gpr_rdatas   := gpr.read_io.map(_.rdata)
    opr_gen.io.sb_forward   := scoreboard.io.forward_msg
    opr_gen.io.raw_inst     := io.from_decoder.bits.inst
    opr_gen.io.pc           := io.from_decoder.bits.pc

    io.trans.valid                  := issued_inst.valid
    io.trans.bits.fuinput.id        := issued_inst.bits.id
    io.trans.bits.fuinput.pc        := io.from_decoder.bits.pc
    io.trans.bits.br_pred           := io.from_decoder.bits.br_pred
    io.trans.bits.fuinput.operand_a := opr_gen.io.operand_a
    io.trans.bits.fuinput.operand_b := opr_gen.io.operand_b
    io.trans.bits.fuinput.operand_c := opr_gen.io.operand_c
    io.trans.bits.fuinput.exception := io.from_decoder.bits.exception
    io.trans.bits.fuinput.optype    := decoded_inst.fuoptype
    io.trans.bits.futype            := decoded_inst.futype

    scoreboard.io.operands_rdy := opr_gen.io.operand_rdy

    /*                  COMMIT LOGIC                    */

    val commit_inst     = scoreboard.io.commit_inst
    val commit_inst_sbe = commit_inst.bits.sbe

    // check whether we are committing a store inst

    val inst_excp = (commit_inst_sbe.exception =/= ArchExceptionType.NONE.enum_no)

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
    io.csr_commit.valid   := is_commit_csr & commit_inst.valid & !inst_excp & !io.int_flag
    io.store_commit.valid := is_commit_store & commit_inst.valid & !inst_excp & !io.int_flag
    io.ertn_commit        := is_commit_ertn & commit_inst.valid & !inst_excp & !io.int_flag
    io.ll_commit          := is_commit_ll & commit_inst.valid & !inst_excp & !io.int_flag
    io.sc_commit          := is_commit_sc & commit_inst.valid & commit_inst.ready & !inst_excp & !io.int_flag

    commit_inst.ready := MuxCase(
        true.B,
        Seq(
            (is_commit_idle & !inst_excp, io.int_flag),
            (is_commit_store, io.store_commit.ready),
            (is_commit_csr, io.csr_commit.ready)
        )
    )

    val dest_reg = Mux(commit_inst_sbe.decoded_inst.dest_rs1, commit_inst_sbe.rs1, commit_inst_sbe.rd)

    gpr.write_io.waddr := dest_reg
    gpr.write_io.wen   := commit_inst.valid && commit_inst_sbe.decoded_inst.regwen && !io.excp_commit.valid
    gpr.write_io.wdata := Mux(!is_commit_sc, commit_inst.bits.sbe.result, io.llbit)

    if (DIFFTEST_MODE) {
        scoreboard.io.lsu_diff.get    := io.lsu_diff.get
        io.diff.get.commit_inst.bits  := commit_inst.bits
        io.diff.get.commit_inst.valid := commit_inst.valid & commit_inst.ready & !io.excp_commit.valid
        io.diff.get.gpr               := gpr.diff_gpr.get
        io.diff.get.is_commit_excp    := io.excp_commit.valid
        io.diff.get.is_CNTinst        := commit_inst.valid &&
            (commit_inst_sbe.decoded_inst.futype === FuType.misc) &&
            ((commit_inst_sbe.decoded_inst.fuoptype === MiscOpType.rdcntid) ||
                (commit_inst_sbe.decoded_inst.fuoptype === MiscOpType.rdcntvh) ||
                (commit_inst_sbe.decoded_inst.fuoptype === MiscOpType.rdcntvl))
    }
}
