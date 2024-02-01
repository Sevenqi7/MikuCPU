package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.backend._
import miku.MulDivOpType._

//This is a fake multiplier that use '*' operator to generate result
//and delay the output for 5 cycles
class FakeMultiplierInput extends BaseFuInput {}

class FakeMultiplierOutput extends BaseFuOutput {
    val result = UInt(WORD_WIDTH.W)
}

class FakeMultiplierIO extends MkBundle {
    val in  = Flipped(Decoupled(new FakeMultiplierInput()))
    val out = ValidIO(new FakeMultiplierOutput())
}

class FakeMultiplier extends MkModule {
    val io = IO(new FakeMultiplierIO)

    val operand_a = io.in.bits.operand_a
    val operand_b = io.in.bits.operand_b

    val result_sel_table = Seq(
        mulw   -> (operand_a * operand_b),
        mulhw  -> (operand_a.asSInt * operand_b.asSInt).asUInt(63, 32),
        mulhwu -> (operand_a * operand_b)(63, 32),
        divwu  -> (operand_a / operand_b),
        divw   -> (operand_a.asSInt / operand_a.asSInt).asUInt,
        modwu  -> (operand_a % operand_b),
        modw   -> (operand_a.asSInt % operand_b.asSInt).asUInt
    )

    val result = MuxLookup(io.in.bits.optype, 0.U)(result_sel_table)

    val ready_r = RegInit(true.B)
    io.in.ready := ready_r
    when(io.in.valid & io.in.ready) {
        ready_r := false.B
    }.otherwise {
        ready_r := DelayN(true.B, 4)
    }

    // delay 5 cycles
    io.out.valid       := DelayN(io.in.valid, 5)
    io.out.bits.result := DelayN(result, 5)
}
