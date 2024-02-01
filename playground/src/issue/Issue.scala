package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._

class IssueEntry extends MkBundle {
    val pc           = UInt(VADDR_WIDTH.W)
    val inst         = UInt(INST_BITS.W)
    val decoded_inst = new DecodedInst()
    val valid        = Bool()
}

class IssueOutput extends MkBundle {
    val alu_valid   = Bool()
    val lsu_valid   = Bool() // load store
    val bru_valid   = Bool() // branch
    val mdu_valid   = Bool() // mul and div
    val issue_valid = Bool()
}

class IssueQueueBundle extends MkBundle {
    class Status extends MkBundle {
        val num   = UInt(REG_ADDR_SIZE.W) // reg number
        val valid = Bool()                // is reg valid?
    }
    val rj        = new Status
    val rk        = new Status
    val rd        = new Status
    val imm       = UInt(WORD_WIDTH.W)
    val sel_imm   = UInt(SEL_IMM_WIDTH.W)
    val imm_valid = Bool()
    val fuoptype  = UInt(MAX_OP_WIDTH.W)
    val futype    = UInt(FU_STATUS_SIZE.W)
}

class IssueStage extends MkModule {
    val io = IO(new Bundle {
        val in  = Input(new IssueEntry)
        val out = Output(new IssueOutput)
    })

    val alu :: load_store :: branch :: mul_div :: Nil = Enum(4)
    val alu_hot                                       = UIntToOH(alu)
    val lsu_hot                                       = UIntToOH(load_store)
    val bru_hot                                       = UIntToOH(branch)
    val mdu_hot                                       = UIntToOH(mul_div)

    val scoreboard    = Module(new ScoreBoard)
    val issue_queue   = Module(new CircularQueue(new IssueQueueBundle, NR_ENTRIES))
    val unissued_inst = new IssueQueueBundle

    
    

    val q_imm_type = io.in.decoded_inst.selImm
    val q_reg_type = io.in.decoded_inst.src1
    val inst       = io.in.inst
    val is_issue   = scoreboard.io.out.sb_issue_en

    // 入队
    unissued_inst.rd.valid := ~((q_imm_type === SelImm.IMM_S20) || (q_imm_type === SelImm.IMM_S26))
    unissued_inst.rj.valid := ~(q_imm_type === SelImm.IMM_S26)
    unissued_inst.rk.valid := ((q_reg_type === SrcType.reg) || (q_reg_type === SrcType.reg))
    unissued_inst.rd.num   := inst(4, 0)
    unissued_inst.rj.num   := inst(9, 5)
    unissued_inst.rk.num   := inst(14, 10)
    unissued_inst.sel_imm  := q_imm_type
    unissued_inst.imm_valid := (io.in.decoded_inst.src1 === SrcType.none) && (io.in.decoded_inst.src2 === SrcType.none) && (io.in.decoded_inst.src3 === SrcType.none)
    unissued_inst.futype   := io.in.decoded_inst.futype
    unissued_inst.fuoptype := io.in.decoded_inst.fuoptype // TODO: 'UInt<14>' must be hardware, not a bare Chisel type.

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

}
