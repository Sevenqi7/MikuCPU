package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class ScoreBoardOutput extends MkBundle {

    // sb is scoreboard
    val sb_full      = Bool()
    val sb_issue_en  = Bool()
    val sb_issue_way = UInt(FU_STATUS.W)

    val sb_issue_rd = UInt(REG_ADDR_SIZE.W)
    val sb_issue_rj = UInt(REG_ADDR_SIZE.W)
    val sb_issue_rk = UInt(REG_ADDR_SIZE.W)

    val sb_issue_rd_en = Bool()
    val sb_issue_rj_en = Bool()
    val sb_issue_rk_en = Bool()

    val sb_issue_imm    = UInt(WORD_WIDTH.W)
    val sb_issue_imm_en = Bool()
}

class ScoreBoardInput extends MkBundle {
    // sb is scoreboard
    val sb_flush             = Bool()
    val flush_unissued_instr = Bool()
    // val flush_unresolved_branch = Bool() // we have an unresolved branch

    val sb_way        = UInt(FU_STATUS.W)
    val sb_commit_way = UInt(FU_STATUS.W)
    val sb_rd         = UInt(REG_ADDR_SIZE.W)
    val sb_rj         = UInt(REG_ADDR_SIZE.W)
    val sb_rk         = UInt(REG_ADDR_SIZE.W)

    val sb_rd_en = Bool()
    val sb_rj_en = Bool()
    val sb_rk_en = Bool()

    val sb_inst_time = UInt(FU_TIME_SIZE.W)
    val sb_imm       = UInt(WORD_WIDTH.W)
    val sb_imm_en    = Bool()
}

//FU is Functional Status
//这个table记录着每个FU的状态
class FUStatusTable extends MkModule {
    class FU {
        class RegStatus {
            // F
            val num       = RegInit(UInt(REG_ADDR_SIZE.W), 0.U)  // reg destination
            // R
            val ready     = RegInit(Bool(), 0.U)                 // reg number is ready
            // Q
            val fu_number = RegInit(UInt(FU_STATUS_SIZE.W), 0.U) // when reg isnt ready, which FU number should get
        }
        val busy = RegInit(Bool(), 0.U)
        val op   = RegInit(UInt(FU_STATUS_SIZE.W), 0.U)
        val rj   = new RegStatus
        val rk   = new RegStatus
        val rd   = new RegStatus
        val time = RegInit(UInt(FU_TIME_SIZE.W), 0.U)
    }
    val alu_fu        = new FU
    val load_store_fu = new FU
    val branch_fu     = new FU
    val mul_div_fu    = new FU
}

//这个table表示寄存器将被几号FU改写
class RegResultTable extends MkModule {
    val status = RegInit(Vec(REG_ADDR_WD.W, UInt(FU_STATUS_SIZE.W)), 0.U)
}

//这个table记录着每一条指令所抵达的流水线位置
class InstStatusTable extends MkModule {
    class InstStatus extends MkModule {
        val op              = RegInit(UInt(FU_STATUS_SIZE.W), 0.U)
        val rd              = RegInit(UInt(REG_ADDR_SIZE.W), 0.U)
        val rj              = RegInit(UInt(REG_ADDR_SIZE.W), 0.U)
        val rk              = RegInit(UInt(REG_ADDR_SIZE.W), 0.U)
        val now_inst_status = RegInit(UInt(BACKEND_STATUS.W), 0.U)
    }
    val status = Vec(NR_ENTRIES.W, new InstStatus)
}

abstract class ScoreBoardIO extends MkModule {
    val in  = Input(new ScoreBoardInput)
    val out = Output(new ScoreBoardOutput)
}

class ScoreBoard extends ScoreBoardIO {
    val fu_status                                     = new FUStatusTable
    val reg_result                                    = new RegResultTable
    val inst_status                                   = new InstStatusTable
    val alu :: load_store :: branch :: mul_div :: Nil = Enum(4)
}
