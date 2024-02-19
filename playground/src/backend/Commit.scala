package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._
import miku.issue._

class CommitInput extends MkBundle {
    val pc           = UInt(VADDR_WIDTH.W)
    class CommitUnit extends MkBundle{
        val valid   = Bool()
        val result  = UInt(WORD_WIDTH.W)
        val reg_num = UInt(REG_ADDR_WD.W)
    }
    val alu_commit   = new CommitUnit
    val mdu_commit   = new CommitUnit
    val lsu_commit   = new CommitUnit
    val branch_valid = Bool()
}

class CommitOutput extends MkBundle {
    // commit
    val commit_way = FuType()
    val commit_rd  = UInt(REG_ADDR_WD.W)
    val commit_en  = Bool()
    val commit_wd  = UInt(WORD_WIDTH.W) // input regfile
}

class CommitStage extends MkModule {
    val io = IO(new Bundle {
        val in  = Input(new CommitInput)
        val out = Output(new CommitOutput)
    })

    val alu_hot = FuType.alu
    val lsu_hot = FuType.lsu
    val bru_hot = FuType.bru
    val mdu_hot = FuType.mul

    io.out.commit_en := false.B
    io.out.commit_way := 0.U
    io.out.commit_wd := 0.U
    io.out.commit_rd := 0.U


    when(io.in.alu_commit.valid){
        io.out.commit_en := true.B
        io.out.commit_rd := io.in.alu_commit.reg_num
        io.out.commit_wd := io.in.alu_commit.result
        io.out.commit_way := alu_hot
    } .elsewhen(io.in.mdu_commit.valid){
        io.out.commit_en := true.B
        io.out.commit_rd := io.in.mdu_commit.reg_num
        io.out.commit_wd := io.in.mdu_commit.result
        io.out.commit_way := mdu_hot
    } .elsewhen(io.in.lsu_commit.valid){
        io.out.commit_en := true.B
        io.out.commit_rd := io.in.lsu_commit.reg_num
        io.out.commit_wd := io.in.lsu_commit.result
        io.out.commit_way := lsu_hot
    } .elsewhen(io.in.branch_valid){
        io.out.commit_en := true.B
        io.out.commit_way := bru_hot
    }
}
