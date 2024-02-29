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

    val fu_in = RegInit(0.U.asTypeOf(ValidIO(new BaseFuInput)))
    when(io.in.valid & io.in.ready) {
        fu_in.bits  := io.in.bits
        fu_in.valid := io.in.valid
    }

    val operand_a = fu_in.bits.operand_a
    val operand_b = fu_in.bits.operand_b

    val result_sel_table = Seq(
        mulw   -> (operand_a * operand_b),
        mulhw  -> (operand_a.asSInt * operand_b.asSInt).asUInt(63, 32),
        mulhwu -> (operand_a * operand_b)(63, 32),
        divwu  -> (operand_a / operand_b),
        divw   -> (operand_a.asSInt / operand_a.asSInt).asUInt,
        modwu  -> (operand_a % operand_b),
        modw   -> (operand_a.asSInt % operand_b.asSInt).asUInt
    )

    val result = MuxLookup(fu_in.bits.optype, 0.U)(result_sel_table)

    val ready_r      = RegInit(true.B)
    val result_buf   = RegInit(0.U.asTypeOf(new BaseFuOutput))
    val result_valid = RegInit(false.B)
    io.in.ready := ready_r
    when(fu_in.valid & !result_valid) {
        ready_r              := false.B
        result_buf.id        := fu_in.bits.id
        result_buf.result    := result
        result_buf.exception := false.B
        result_valid         := true.B
    }

    when(io.out.valid & io.out.ready) {
        ready_r      := true.B
        result_valid := false.B
    }

    // delay 5 cycles
    io.out.valid := DelayN(result_valid, 5)
    io.out.bits  := DelayN(result_buf, 5)

}
