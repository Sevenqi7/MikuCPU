package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.backend._
import miku.ALUOpType._
import miku.utils.SEXT

class ALUResulutSelector extends MkModule {
    val io = IO(new MkBundle {
        val op        = Input(ALUOpType())
        val operand_a = Input(UInt(WORD_WIDTH.W)) // rk or imms
        val operand_b = Input(UInt(WORD_WIDTH.W)) // rj
        val result    = Output(UInt(WORD_WIDTH.W))
    })

    val slt_result  = io.operand_a.asSInt < io.operand_b.asSInt
    val sltu_result = io.operand_a < io.operand_b

    val result_table = Seq[(UInt, UInt)](
        addw      -> (io.operand_a + io.operand_b),
        subw      -> (io.operand_a - io.operand_b),
        lu12iw    -> SEXT(io.operand_b(19, 0) << 12, WORD_WIDTH),
        slt       -> slt_result,
        sltu      -> sltu_result,
        and       -> (io.operand_a & io.operand_b),
        or        -> (io.operand_a | io.operand_b),
        nor       -> ~(io.operand_a | io.operand_b),
        xor       -> (io.operand_a ^ io.operand_b),
        sllw      -> (io.operand_a << io.operand_b(4, 0)),
        srlw      -> (io.operand_a >> io.operand_b(4, 0)),
        sraw      -> (io.operand_a.asSInt >> io.operand_b(4, 0)).asUInt,
        pcaddu12i -> (io.operand_a + SEXT(io.operand_b << 12, WORD_WIDTH))
    )

    io.result := MuxLookup(io.op, 0.U)(result_table)
}

class MkALU extends BaseFunctionUnit {
    io.in.ready  := true.B // all operation in ALU complete in 1 cycle
    io.out.valid := io.in.valid

    // generate result
    val result_gen = Module(new ALUResulutSelector)
    result_gen.io.op        := io.in.bits.optype
    result_gen.io.operand_a := io.in.bits.operand_a
    result_gen.io.operand_b := io.in.bits.operand_b

    io.out.bits.exception := false.B
    io.out.bits.id        := io.in.bits.id
    io.out.bits.result    := result_gen.io.result
}
