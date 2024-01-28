package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class ScoreBoardOutput extends MkBundle {

    // sb is scoreboard
    val sb_full      = Bool()
    val sb_issue_en  = Bool()
    val sb_issue_way = UInt(FU_STATUS_SIZE.W)

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

    val sb_way        = UInt(FU_STATUS_SIZE.W)
    val sb_commit_way = UInt(FU_STATUS_SIZE.W)
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
class FUStatusTable extends MkBundle {
    class FU extends MkBundle {
        class RegStatus extends MkBundle {
            // F
            val num       = UInt(REG_ADDR_SIZE.W)  // reg destination
            // R
            val ready     = Bool()                 // reg number is ready
            // Q
            val fu_number = UInt(FU_STATUS_SIZE.W) // when reg isnt ready, which FU number should get
        }
        val busy = Bool()
        val op   = UInt(FU_STATUS_SIZE.W)
        val rj   = new RegStatus
        val rk   = new RegStatus
        val rd   = new RegStatus
        val time = UInt(FU_TIME_SIZE.W)
    }
    val alu_fu        = new FU
    val load_store_fu = new FU
    val branch_fu     = new FU
    val mul_div_fu    = new FU
}

//这个table表示寄存器将被几号FU改写
class RegResultTable extends MkBundle {
    val status = Vec(REG_ADDR_WD, UInt(FU_STATUS_SIZE.W))
}

//这个table记录着每一条指令所抵达的流水线位置
class InstStatus extends MkBundle {
    val op              = UInt(FU_STATUS_SIZE.W)
    val rd              = UInt(REG_ADDR_SIZE.W)
    val rj              = UInt(REG_ADDR_SIZE.W)
    val rk              = UInt(REG_ADDR_SIZE.W)
    val now_inst_status = UInt(BACKEND_STATUS.W)
}

abstract class ScoreBoardIO extends MkModule {
    val in  = Input(new ScoreBoardInput)
    val out = Output(new ScoreBoardOutput)
}

class ScoreBoard extends ScoreBoardIO {
    val fu_status                                     = new FUStatusTable
    val alu :: load_store :: branch :: mul_div :: Nil = Enum(4)

    val reg_result        = RegInit(0.U.asTypeOf(new RegResultTable))
    val inst_status_table = RegInit(VecInit(Seq.fill(NR_ENTRIES)(0.U.asTypeOf(new InstStatus))))
}
