package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.backend._
import miku.frontend.DecodedInst
import miku.frontend.BranchPredictorResult
import miku.frontend.BranchInstInfo
import miku.frontend.BranchPredictorUpdate
import java.util.concurrent.Future

class ScoreboardEntry extends MkBundle {
    val decoded_inst = new DecodedInst
    val raw_inst     = if (DIFFTEST_MODE) Some(UInt(WORD_WIDTH.W)) else None
    val rj_num       = UInt(REG_ADDR_WD.W)
    val rk_num       = UInt(REG_ADDR_WD.W)
    val rd_num       = UInt(REG_ADDR_WD.W)
    val exception    = Bool()
    val result       = UInt(WORD_WIDTH.W)
    val br_info      = ValidIO(new BranchInstInfo)
    val executed     = Bool()
}

class ScoreboardFowardInfo extends MkBundle {
    val rj_fwd_data   = ValidIO(UInt(WORD_WIDTH.W))
    val rj_raw_hazard = Bool()
    val rk_fwd_data   = ValidIO(UInt(WORD_WIDTH.W))
    val rk_raw_hazard = Bool()
    val rd_fwd_data   = ValidIO(UInt(WORD_WIDTH.W))
    val rd_raw_hazard = Bool()
}

class IssuedInst extends MkBundle {
    val id  = UInt(log2Ceil(NR_ENTRIES).W) // unique id for each issued instruction
    val sbe = new ScoreboardEntry
}

class ScoreboardIO extends MkBundle {
    val from_decoder = Flipped(Decoupled(new IssueEntry)) // decoded inst from IDU
    val issue_inst   = Decoupled(new IssuedInst)          // issued inst to EXU
    val commit_inst  = Decoupled(new IssuedInst)          // instruction to be committed
    val flush        = Input(Bool())
    val operands_rdy = Input(Bool())
    val wb_data      = Flipped(Vec(NR_WB_PORTS, Decoupled(new WriteBackResult)))
    val forward_msg  = new ScoreboardFowardInfo
}

class Scoreboard extends MkModule {
    val io = IO(new ScoreboardIO)

    val sb_mem = RegInit(VecInit.fill(NR_ENTRIES)(0.U.asTypeOf(ValidIO(new ScoreboardEntry))))

    val commit_ptr = RegInit(0.U(log2Ceil(NR_ENTRIES).W))
    val issue_ptr  = RegInit(0.U(log2Ceil(NR_ENTRIES).W))
    val issued_cnt = RegInit(0.U(log2Ceil(NR_ENTRIES).W))

    val commit_ack = io.commit_inst.valid & io.commit_inst.ready
    val issue_ack  = io.issue_inst.valid & io.issue_inst.ready

    // update the counter of issued insts
    issued_cnt := MuxCase(
        issued_cnt,
        Seq(
            (issue_ack & !commit_ack, issued_cnt + 1.U),
            (!issue_ack & commit_ack, issued_cnt - 1.U)
        )
    )

    val decoded_inst = io.from_decoder.bits.decoded_inst
    val sb_full      = issued_cnt === NR_ENTRIES.U
    val sb_empty     = issued_cnt === 0.U
    val is_bl        = (decoded_inst.futype === FuType.bru) && (decoded_inst.fuoptype === JumpOpType.bl)

    // issue inst when respective function unit is ready
    when(issue_ack) {
        issue_ptr                           := issue_ptr + 1.U
        sb_mem(issue_ptr).valid             := true.B // set valid bit as true when successfully issue this instruction
        sb_mem(issue_ptr).bits.rk_num       := io.from_decoder.bits.inst(14, 10)
        sb_mem(issue_ptr).bits.rj_num       := io.from_decoder.bits.inst(9, 5)
        // BL has a fixed destination register R1
        sb_mem(issue_ptr).bits.rd_num       := Mux(is_bl, 1.U, io.from_decoder.bits.inst(4, 0))
        sb_mem(issue_ptr).bits.decoded_inst := decoded_inst
        if (DIFFTEST_MODE) {
            sb_mem(issue_ptr).bits.raw_inst.get := io.from_decoder.bits.inst
        }

        sb_mem(issue_ptr).bits.br_info.bits.pc      := io.from_decoder.bits.pc
        sb_mem(issue_ptr).bits.br_info.bits.pred    := io.from_decoder.bits.br_pred
        sb_mem(issue_ptr).bits.br_info.bits.mispred := false.B
        sb_mem(issue_ptr).bits.br_info.valid        := (decoded_inst.futype === FuType.bru)
    }

    // default - initialise all fieled with zero
    val init_sbe = 0.U.asTypeOf(new ScoreboardEntry)
    io.issue_inst.bits.sbe := init_sbe

    io.issue_inst.bits.id := issue_ptr
    // issue an instruction when operands are ready and there
    // are no other currently issued instruction to write the same destination register
    val waw_hazard = decoded_inst.regwen && sb_mem.zipWithIndex
        .map { case (sbe, id) =>
            sbe.valid && sbe.bits.decoded_inst.regwen &&
            (sbe.bits.rd_num === io.issue_inst.bits.sbe.rd_num) &&
            (id.U =/= commit_ptr)
        }.reduce(_ || _)

    // only issue an branch instruction when no other unresolved branch inst in scoreboard
    val unresolved_branch =
        sb_mem
            .map(sbe =>
                sbe.valid &&
                    sbe.bits.br_info.valid
            ).reduce(_ || _)

    io.issue_inst.valid := io.from_decoder.valid && io.operands_rdy && !waw_hazard &&
        ((decoded_inst.futype =/= FuType.bru) || ((decoded_inst.futype === FuType.bru) && !unresolved_branch))

    io.issue_inst.bits.sbe.rk_num := io.from_decoder.bits.inst(14, 10)
    io.issue_inst.bits.sbe.rj_num := io.from_decoder.bits.inst(9, 5)
    io.issue_inst.bits.sbe.rd_num := io.from_decoder.bits.inst(4, 0)
    io.from_decoder.ready         := (io.operands_rdy && io.issue_inst.ready && !sb_full & !waw_hazard) &&
        ((decoded_inst.futype =/= FuType.bru) || ((decoded_inst.futype === FuType.bru) && !unresolved_branch))

    // commit inst
    when(commit_ack) {
        commit_ptr                       := commit_ptr + 1.U
        sb_mem(commit_ptr).valid         := false.B
        sb_mem(commit_ptr).bits.executed := false.B
    }

    // write-back from exu
    for (wb <- io.wb_data) {
        val wb_id  = wb.bits.id
        val wb_sbe = sb_mem(wb_id).bits
        when(wb.valid) {
            wb_sbe.br_info.bits.mispred := wb.bits.mispred
            wb_sbe.result               := wb.bits.result
            wb_sbe.exception            := wb.bits.exception
            wb_sbe.executed             := true.B
            // misprediction flush
            when(wb_sbe.br_info.valid & wb_sbe.br_info.bits.mispred) {
                issue_ptr := commit_ptr + 1.U
                for (i <- 0 until NR_ENTRIES) {
                    when((commit_ptr + i.U)(TRANS_ID_BITS - 1, 0) < issue_ptr) {
                        sb_mem(i) := 0.U.asTypeOf(ValidIO(new ScoreboardEntry))
                    }
                }
            }
        }
        wb.ready := true.B
    }

    // flush
    when(io.flush) {
        commit_ptr := 0.U
        issue_ptr  := 0.U
        issued_cnt := 0.U
        for (i <- 0 until NR_ENTRIES) {
            sb_mem(i).valid         := false.B
            sb_mem(i).bits.executed := false.B
        }
    }

    io.commit_inst.bits.id  := commit_ptr
    io.commit_inst.bits.sbe := sb_mem(commit_ptr).bits
    io.commit_inst.valid    := sb_mem(commit_ptr).bits.executed & sb_mem(commit_ptr).valid

    // bypass arbiter
    // this priority arbiter choose the most up-to-date reg data
    // from all the sb_mem entry and write-back data from EXU.
    // Further selection such as selecting immediate result from EXU will be processed
    // during GPR's accessing

    // rj arbibter
    val rj_arb = Module(new Arbiter(UInt(WORD_WIDTH.W), NR_ENTRIES + NR_WB_PORTS))
    for (i <- 0 until NR_WB_PORTS) {
        val wb_id = io.wb_data(i).bits.id
        rj_arb.io.in(i).valid := io.wb_data(i).valid &&
            (io.issue_inst.bits.sbe.rj_num === sb_mem(wb_id).bits.rd_num) &&
            sb_mem(wb_id).bits.decoded_inst.regwen
        rj_arb.io.in(i).bits  := io.wb_data(i).bits.result
    }
    rj_arb.io.out.ready := true.B

    for (i <- 0 until NR_ENTRIES) {
        val result_valid = sb_mem(i).valid &&
            (io.issue_inst.bits.sbe.rj_num === sb_mem(i).bits.rd_num) &&
            sb_mem(i).bits.executed &&
            sb_mem(i).bits.decoded_inst.regwen
        rj_arb.io.in(i + NR_WB_PORTS).valid := result_valid
        rj_arb.io.in(i + NR_WB_PORTS).bits  := sb_mem(i).bits.result
    }

    // rk arbiter
    val rk_arb = Module(new Arbiter(UInt(WORD_WIDTH.W), NR_ENTRIES + NR_WB_PORTS))
    for (i <- 0 until NR_WB_PORTS) {
        val wb_id = io.wb_data(i).bits.id
        rk_arb.io.in(i).valid := io.wb_data(i).valid &&
            (io.issue_inst.bits.sbe.rk_num === sb_mem(wb_id).bits.rd_num) &&
            sb_mem(wb_id).bits.decoded_inst.regwen
        rk_arb.io.in(i).bits  := io.wb_data(i).bits.result
        rk_arb.io.out.ready   := true.B
    }

    for (i <- 0 until NR_ENTRIES) {
        val result_valid = sb_mem(i).valid &&
            (io.issue_inst.bits.sbe.rk_num === sb_mem(i).bits.rd_num) &&
            sb_mem(i).bits.executed &&
            sb_mem(i).bits.decoded_inst.regwen
        rk_arb.io.in(i + NR_WB_PORTS).valid := result_valid
        rk_arb.io.in(i + NR_WB_PORTS).bits  := sb_mem(i).bits.result
    }

    // rd arbiter
    val rd_arb = Module(new Arbiter(UInt(WORD_WIDTH.W), NR_ENTRIES + NR_WB_PORTS))
    for (i <- 0 until NR_WB_PORTS) {
        val wb_id = io.wb_data(i).bits.id
        rd_arb.io.in(i).valid := io.wb_data(i).valid &&
            (io.issue_inst.bits.sbe.rd_num === sb_mem(wb_id).bits.rd_num) &&
            sb_mem(wb_id).bits.decoded_inst.regwen
        rd_arb.io.in(i).bits  := io.wb_data(i).bits.result
        rd_arb.io.out.ready   := true.B
    }

    for (i <- 0 until NR_ENTRIES) {
        val result_valid = sb_mem(i).valid &&
            (io.issue_inst.bits.sbe.rd_num === sb_mem(i).bits.rd_num) &&
            sb_mem(i).bits.executed &&
            sb_mem(i).bits.decoded_inst.regwen
        rd_arb.io.in(i + NR_WB_PORTS).valid := result_valid
        rd_arb.io.in(i + NR_WB_PORTS).bits  := sb_mem(i).bits.result
    }

    io.forward_msg.rj_fwd_data := rj_arb.io.out
    io.forward_msg.rk_fwd_data := rk_arb.io.out
    io.forward_msg.rd_fwd_data := rd_arb.io.out

    io.forward_msg.rj_raw_hazard := sb_mem
        .map(sbe =>
            sbe.valid && !sbe.bits.executed
                && sbe.bits.decoded_inst.regwen
                && (sbe.bits.rd_num === io.issue_inst.bits.sbe.rj_num)
                && !Range(0, NR_WB_PORTS).map(i => rj_arb.io.in(i).valid).reduce(_ || _)
        )
        .reduce(_ || _)
    io.forward_msg.rk_raw_hazard := sb_mem
        .map(sbe =>
            sbe.valid && !sbe.bits.executed
                && sbe.bits.decoded_inst.regwen
                && (sbe.bits.rd_num === io.issue_inst.bits.sbe.rk_num)
                && !Range(0, NR_WB_PORTS).map(i => rk_arb.io.in(i).valid).reduce(_ || _)
        )
        .reduce(_ || _)
    io.forward_msg.rd_raw_hazard := sb_mem
        .map(sbe =>
            sbe.valid && !sbe.bits.executed
                && sbe.bits.decoded_inst.regwen
                && (sbe.bits.rd_num === io.issue_inst.bits.sbe.rd_num)
                && !Range(0, NR_WB_PORTS).map(i => rd_arb.io.in(i).valid).reduce(_ || _)
        )
        .reduce(_ || _)
}
