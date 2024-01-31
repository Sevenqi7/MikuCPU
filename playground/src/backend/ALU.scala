package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.backend._
import miku.frontend.ALUOpType._
import miku.frontend.ALUOpType

class ALUInput extends BaseFuInput {}

class ALUOutput extends BaseFuOutput {}

class ALUIO extends MkBundle {
    val in  = Flipped(Decoupled(new ALUInput))
    val out = ValidIO(new ALUOutput)
}

class ALUResulutSelector extends MkModule {
    val io = IO(new MkBundle {
        val op        = Input(ALUOpType())
        val operand_a = Input(UInt(WORD_WIDTH.W))
        val operand_b = Input(UInt(WORD_WIDTH.W))
        val result    = Output(UInt(WORD_WIDTH.W))
    })

    val result_table = Seq[(UInt, UInt)](
        addw   -> (io.operand_a + io.operand_b),
        subw   -> (io.operand_a - io.operand_b),
        lu12iw -> Cat(io.operand_b(19, 0), 0.U(12.W)),
        slt    -> (io.operand_a.asSInt < io.operand_b.asSInt),
        sltu   -> (io.operand_a < io.operand_b),
        and    -> (io.operand_a & io.operand_b),
        or     -> (io.operand_a | io.operand_b),
        nor    -> ~(io.operand_a | io.operand_b),
        xor    -> (io.operand_a ^ io.operand_b),
        sllw   -> (io.operand_a << io.operand_b(4, 0)),
        srlw   -> (io.operand_a >> io.operand_b(4, 0)),
        sraw   -> (io.operand_a.asSInt >> io.operand_b(4, 0)).asUInt
    )

    io.result := MuxLookup(io.op, 0.U)(result_table)
}

class MkALU extends MkModule {
    val io = IO(new ALUIO)

    io.in.ready  := true.B // all operation in ALU complete in 1 cycle
    io.out.valid := io.in.valid

    // generate result
    val result_gen = Module(new ALUResulutSelector)
    result_gen.io.op        := io.in.bits.optype
    result_gen.io.operand_a := io.in.bits.operand_a
    result_gen.io.operand_b := io.in.bits.operand_b

    io.out.bits.result := result_gen.io.result
}
