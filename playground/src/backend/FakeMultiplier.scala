package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.backend._
import miku.isa.MulDivOpType._

//This is a fake multiplier that use '*' operator to generate result
//and delay the output for 5 cycles

class FakeMultiplier extends BaseFunctionUnit {
    val rs1 = io.in.bits.operand_a
    val rs2 = io.in.bits.operand_b

    val result_sel_table = Seq(
        mul   -> (rs1 * rs2),
        mulh  -> (rs1.asSInt * rs2.asSInt).asUInt(63, 32),
        mulhu -> (rs1 * rs2)(63, 32),
        div   -> (rs1.asSInt / rs2.asSInt).asUInt(31, 0),
        divu  -> (rs1 / rs2)(31, 0),
        mod   -> (rs1.asSInt - (rs1.asSInt / rs2.asSInt) * rs2.asSInt).asUInt(31, 0),
        modu  -> (rs1 - (rs1 / rs2) * rs2)(31, 0)
        // modw   -> (rs1.asSInt % rs2.asSInt).asUInt(31, 0),
        // modwu  -> (rs1 % rs2)(31, 0)
    )

    val result = MuxLookup(io.in.bits.optype, 0.U)(result_sel_table)

    val ready_r      = RegInit(true.B)
    val result_buf   = RegInit(0.U.asTypeOf(new BaseFuOutput))
    val result_valid = RegInit(false.B)
    io.in.ready := ready_r
    when(io.flush.ertn | io.flush.exception) {
        ready_r      := true.B
        result_valid := false.B
    }.elsewhen(io.in.valid & io.in.ready & (!result_valid)) {
        ready_r              := false.B
        result_buf.id        := io.in.bits.id
        result_buf.result    := result
        result_buf.exception := io.in.bits.exception
        result_buf.mispred   := false.B
        result_valid         := DelayN(true.B, 5)
    }

    when(io.out.valid & io.out.ready) {
        ready_r      := true.B
        result_valid := false.B
    }

    // delay 5 cycles
    io.out.valid := result_valid
    io.out.bits  := result_buf
}
