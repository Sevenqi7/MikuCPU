package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._
import miku.backend._

class IssueSrc extends BaseFuInput {}

class IssueEntry extends MkBundle {
    val pc           = UInt(VADDR_WIDTH.W)
    val inst         = UInt(INST_BITS.W)
    val decoded_inst = new DecodedInst()
    val valid        = Bool()

    // commit
    val commit_way = FuType()
    val commit_rd  = UInt(REG_ADDR_WD.W)
    val commit_en  = Bool()
    val commit_wd  = UInt(WORD_WIDTH.W) // input regfile
}

class IssueOutput extends MkBundle {
    // 是否发射到这几个单元
    val alu_valid = Bool()
    val lsu_valid = Bool() // load store
    val bru_valid = Bool() // branch
    val mdu_valid = Bool() // mul and div

    // 是否发射
    val issue_valid = Bool()

    // 传入给EXU的值
    val src = new IssueSrc()
}

// 队列中每条指令的Bundle
class IssueQueueBundle extends MkBundle {
    class Status extends MkBundle {
        val num   = UInt(REG_ADDR_WD.W) // reg number
        val valid = Bool()              // is reg valid?
    }
    val rj        = new Status
    val rk        = new Status
    val rd        = new Status
    val imm       = UInt(WORD_WIDTH.W)
    val sel_imm   = SelImm()
    val imm_valid = Bool()
    val fuoptype  = FuOpType()
    val futype    = FuType()
    val pc        = UInt(VADDR_WIDTH.W)
}

class IssueStageIO extends MkBundle {}

class IssueStage extends MkModule {
    val io = IO(new Bundle {
        val in  = Input(new IssueEntry)
        val out = Output(new IssueOutput)
    })

    val alu_hot = FuType.alu
    val lsu_hot = FuType.lsu
    val bru_hot = FuType.bru
    val mdu_hot = FuType.mul

    val scoreboard    = Module(new ScoreBoard)
    val issue_queue   = Module(new CircularQueue(new IssueQueueBundle, NR_ENTRIES))
    val unissued_inst = Wire(new IssueQueueBundle)

    val q_imm_type   = io.in.decoded_inst.selImm
    val q_reg_type   = io.in.decoded_inst.src
    val inst         = io.in.inst
    val decoded_inst = io.in.decoded_inst

    val is_issue = scoreboard.io.out.sb_issue_en
    io.out.issue_valid := is_issue

    // 入队
    unissued_inst.rd.valid  := decoded_inst.needRd
    unissued_inst.rj.valid  := decoded_inst.needRj
    unissued_inst.rk.valid  := decoded_inst.needRk
    unissued_inst.rd.num    := inst(4, 0)
    unissued_inst.rj.num    := inst(9, 5)
    unissued_inst.rk.num    := inst(14, 10)
    unissued_inst.sel_imm   := q_imm_type
    unissued_inst.imm_valid := decoded_inst.src.map(s => s === SrcType.imm).reduce(_ | _)
    unissued_inst.futype    := decoded_inst.futype
    unissued_inst.fuoptype  := decoded_inst.fuoptype
    unissued_inst.pc        := io.in.pc

    val imm_table = Seq[(UInt, UInt)](
        SelImm.IMM_U8  -> UEXT(inst(17, 10), WORD_WIDTH),
        SelImm.IMM_S12 -> SEXT(inst(21, 10), WORD_WIDTH),
        SelImm.IMM_U12 -> UEXT(inst(21, 10), WORD_WIDTH),
        SelImm.IMM_S14 -> SEXT(inst(23, 10), WORD_WIDTH),
        SelImm.IMM_S16 -> SEXT(inst(25, 10), WORD_WIDTH),
        SelImm.IMM_S20 -> SEXT(Cat(inst(4, 0), inst(21, 10)), WORD_WIDTH),
        SelImm.IMM_S26 -> SEXT(Cat(inst(9, 0), inst(21, 10)), WORD_WIDTH)
    )
    unissued_inst.imm := MuxLookup(q_imm_type, 0.U)(imm_table)
    issue_queue.enqData(unissued_inst, io.in.valid)

    // 出队
    val issue_inst = issue_queue.deqData(is_issue)
    io.out.alu_valid          := (alu_hot & is_issue).asBools.reduce(_ | _)
    io.out.lsu_valid          := (lsu_hot & is_issue).asBools.reduce(_ | _)
    io.out.bru_valid          := (bru_hot & is_issue).asBools.reduce(_ | _)
    io.out.mdu_valid          := (mdu_hot & is_issue).asBools.reduce(_ | _)
    scoreboard.io.in.sb_rd_en := issue_inst.rd.valid
    scoreboard.io.in.sb_rj_en := issue_inst.rj.valid
    scoreboard.io.in.sb_rk_en := issue_inst.rk.valid
    scoreboard.io.in.sb_rd    := issue_inst.rd
    scoreboard.io.in.sb_rj    := issue_inst.rj
    scoreboard.io.in.sb_rk    := issue_inst.rk
    scoreboard.io.in.sb_way   := issue_inst.futype

    scoreboard.io.in.sb_flush             := 0.U // TODO: branch predict failed flush
    scoreboard.io.in.flush_unissued_instr := 0.U // TODO: unissued flush

    // 寄存器获取值
    val regfile = new Regfiles
    when(is_issue) {
        when(issue_inst.rd.valid) {
            regfile.read_io(0).rf_rs_i := issue_inst.rd
            io.out.src.operand_c       := regfile.read_io(0).rf_rs_o
        }
        when(issue_inst.rj.valid) {
            regfile.read_io(1).rf_rs_i := issue_inst.rj
            io.out.src.operand_c       := regfile.read_io(1).rf_rs_o
        }
        when(issue_inst.rk.valid) {
            regfile.read_io(2).rf_rs_i := issue_inst.rk
            io.out.src.operand_c       := regfile.read_io(2).rf_rs_o
        }.elsewhen(issue_inst.imm_valid) {
            io.out.src.operand_b := issue_inst.imm
        }
        io.out.src.pc    := issue_inst.pc
        io.out.src.flush := 0.U // TODO: issued flush
    }

    // commit
    scoreboard.io.in.sb_commit_en  := io.in.commit_en
    scoreboard.io.in.sb_commit_way := io.in.commit_way
    scoreboard.io.in.sb_commit_rd  := io.in.commit_rd

    regfile.write_io.rf_ws_data := io.in.commit_wd
    regfile.write_io.rf_ws_i    := io.in.commit_rd
    regfile.write_io.rf_ws_en   := io.in.commit_en
}
