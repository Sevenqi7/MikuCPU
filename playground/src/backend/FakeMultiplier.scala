package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.backend._
import miku.MulDivOpType._

//This is a fake multiplier that use '*' operator to generate result
//and delay the output for 5 cycles

class FakeMultiplier extends BaseFunctionUnit {

    val rj = io.in.bits.operand_a
    val rk = io.in.bits.operand_b

    val result_sel_table = Seq(
        mulw   -> (rj * rk),
        mulhw  -> (rj.asSInt * rk.asSInt).asUInt(63, 32),
        mulhwu -> (rj * rk)(63, 32),
        divw   -> (rj.asSInt / rk.asSInt).asUInt(31, 0),
        divwu  -> (rj / rk)(31, 0),
        modw   -> (rj.asSInt - (rj.asSInt / rk.asSInt) * rk.asSInt).asUInt(31, 0),
        modwu  -> (rj - (rj / rk) * rk)(31, 0)
        // modw   -> (rj.asSInt % rk.asSInt).asUInt(31, 0),
        // modwu  -> (rj % rk)(31, 0)
    )

    val result = MuxLookup(io.in.bits.optype, 0.U)(result_sel_table)

    val ready_r      = RegInit(true.B)
    val result_buf   = RegInit(0.U.asTypeOf(new BaseFuOutput))
    val result_valid = RegInit(false.B)
    io.in.ready := ready_r
    when(io.in.valid & io.in.ready & (!result_valid)) {
        ready_r              := false.B
        result_buf.id        := io.in.bits.id
        result_buf.result    := result
        result_buf.exception := false.B
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
