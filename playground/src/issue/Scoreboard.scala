package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class ScoreBoardOutput extends MkBundle {
    // sb is scoreboard
    val sb_full     = Bool()
    val sb_issue_en = Bool()

}

class ScoreBoardInput extends MkBundle {
    // sb is scoreboard
    val sb_flush             = Bool()
    val flush_unissued_instr = Bool()
    val sb_new_inst          = Bool() // scoreboard received a new unissued inst

    val sb_way = UInt(FU_STATUS_SIZE.W)

    val sb_rd = UInt(REG_ADDR_SIZE.W)
    val sb_rj = UInt(REG_ADDR_SIZE.W)
    val sb_rk = UInt(REG_ADDR_SIZE.W)

    val sb_rd_en = Bool()
    val sb_rj_en = Bool()
    val sb_rk_en = Bool()

    // val sb_inst_time = UInt(FU_TIME_SIZE.W)
    val sb_commit_way = UInt(FU_STATUS_SIZE.W)
    val sb_commit_rd  = UInt(REG_ADDR_SIZE.W)
    val sb_commit_en  = Bool()
}

//FU is Functional Status
//这个table记录着每个FU的状态
class FUStatusTable extends MkBundle {
    class RegStatus extends MkBundle {
        // F
        val num       = UInt(REG_ADDR_SIZE.W)  // reg destination
        // R
        val ready     = Bool()                 // reg number is ready
        // Q
        val fu_number = UInt(FU_STATUS_SIZE.W) // when reg isnt ready, which FU number should get
    }
    val busy = Bool()
    val rj   = new RegStatus
    val rk   = new RegStatus
    val rd   = new RegStatus
    // val time = UInt(FU_TIME_SIZE.W)
}

//这个table表示寄存器将被几号FU改写
class RegResultTable extends MkBundle {
    val status = Vec(REG_ADDR_WD, UInt(FU_STATUS_SIZE.W))
}

//这个table记录着每一条指令所抵达的流水线位置,cva6中可以不存在这个结构
class InstStatus extends MkBundle {
    val valid           = Bool() // 指令空位=false，存在指令=true
    val op              = UInt(FU_STATUS_SIZE.W)
    val rd              = UInt(REG_ADDR_SIZE.W)
    val rj              = UInt(REG_ADDR_SIZE.W)
    val rk              = UInt(REG_ADDR_SIZE.W)
    val now_inst_status = Bool() // 没发射=false，发射后=True
}

class ScoreBoard extends MkModule {

    val io = IO(new Bundle {
        val in  = Input(new ScoreBoardInput)
        val out = Output(new ScoreBoardOutput)
    })

    val fu_status         = RegInit(VecInit(Seq.fill(FU_STATUS_SIZE)(0.U.asTypeOf(new FUStatusTable))))
    val reg_result        = RegInit(0.U.asTypeOf(new RegResultTable))
    // val inst_status_table = RegInit(VecInit(Seq.fill(NR_ENTRIES)(0.U.asTypeOf(new InstStatus))))
    val inst_full         = RegInit(0.B)

    io.out.sb_full     := inst_full
    io.out.sb_issue_en := 0.U

    when(io.in.sb_commit_en){
        fu_status(io.in.sb_commit_way).busy := false.B
        fu_status(io.in.sb_commit_way).rd.num := 0.U
        fu_status(io.in.sb_commit_way).rj.num := 0.U
        fu_status(io.in.sb_commit_way).rk.num := 0.U
        reg_result.status(io.in.sb_commit_rd) := 0.U
    }

    // when(io.in.sb_new_inst) {
    //     for (i <- 0 until NR_ENTRIES) {
    //         when(inst_status_table(i).valid === false.B) {
    //             inst_status_table(i).valid := true.B
    //             inst_status_table(i).op    := io.in.sb_way
    //             inst_status_table(i).rd    := io.in.sb_rd
    //             inst_status_table(i).rj    := io.in.sb_rj
    //             inst_status_table(i).rk    := io.in.sb_rk
    //         }.otherwise {
    //             inst_full := true.B
    //         }
    //     }
    // }

    when(reg_result.status(io.in.sb_rj) === 0.U && reg_result.status(io.in.sb_rk) === 0.U) {
        io.out.sb_issue_en := ~fu_status(io.in.sb_way).busy
    }

    when(io.out.sb_issue_en) {
        fu_status(io.in.sb_way).busy := true.B
        when(io.in.sb_rd_en) {
            fu_status(io.in.sb_way).rd.num := io.in.sb_rd
            reg_result.status(io.in.sb_rd) := io.in.sb_way
        }
        when(io.in.sb_rj_en) { fu_status(io.in.sb_way).rj.num := io.in.sb_rj }
        when(io.in.sb_rk_en) { fu_status(io.in.sb_way).rk.num := io.in.sb_rk }
    }
    
}
