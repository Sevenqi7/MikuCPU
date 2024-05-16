package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.isa.ALUOpType
import miku.isa.ALUOpType._

// abstract class MkALU extends MkModule {
//     val io = IO(new MkBundle {
//         val op        = Input(ALUOpType())
//         val operand_a = Input(UInt(WORD_WIDTH.W)) // rk or imms
//         val operand_b = Input(UInt(WORD_WIDTH.W)) // rj
//         val result    = Output(UInt(WORD_WIDTH.W))
//     })
// }

class ALUResultSelector extends MkModule {
    val io = IO(new MkBundle {
        val op        = Input(ALUOpType())
        val operand_a = Input(UInt(WORD_WIDTH.W)) // rk or imms
        val operand_b = Input(UInt(WORD_WIDTH.W)) // rj
        val result    = Output(UInt(WORD_WIDTH.W))
    })

    val slt_result  = io.operand_a.asSInt < io.operand_b.asSInt
    val sltu_result = io.operand_a < io.operand_b

    val result_table = Seq[(UInt, UInt)](
        add   -> (io.operand_a + io.operand_b),
        sub   -> (io.operand_a - io.operand_b),
        lui   -> SEXT(io.operand_b(19, 0) << 12, WORD_WIDTH),
        slt   -> slt_result,
        sltu  -> sltu_result,
        and   -> (io.operand_a & io.operand_b),
        or    -> (io.operand_a | io.operand_b),
        nor   -> ~(io.operand_a | io.operand_b),
        xor   -> (io.operand_a ^ io.operand_b),
        sll   -> (io.operand_a << io.operand_b(4, 0)),
        srl   -> (io.operand_a >> io.operand_b(4, 0)),
        sra   -> (io.operand_a.asSInt >> io.operand_b(4, 0)).asUInt,
        auipc -> (io.operand_a + SEXT(io.operand_b << 12, WORD_WIDTH))
    )

    val la32_alu_op = Wire(ALUOpType())
    la32_alu_op := io.op

    io.result := MuxLookup(la32_alu_op, 0.U)(result_table)
}

class MkALUWrapper extends BaseFunctionUnit {
    io.in.ready  := true.B // all operation in ALU complete in 1 cycle
    io.out.valid := io.in.valid

    // generate result
    val result_gen = Module(new ALUResultSelector)
    result_gen.io.op        := io.in.bits.optype
    result_gen.io.operand_a := io.in.bits.operand_a
    result_gen.io.operand_b := io.in.bits.operand_b

    io.out.bits.exception := io.in.bits.exception
    io.out.bits.mispred   := false.B
    io.out.bits.id        := io.in.bits.id
    io.out.bits.result    := result_gen.io.result
}
