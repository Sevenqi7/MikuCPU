package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.JumpOpType._
import miku.frontend.BranchPredictorUpdate
import miku.frontend.BranchPredictorResult

class BranchUnitInput extends BaseFuInput {
    val br_pred = new BranchPredictorResult
}

class BranchUnitOutput extends BaseFuOutput {
    val result = new BranchPredictorUpdate()
}

class BranchUnitIO extends MkBundle {
    val in  = Flipped(Decoupled(new BranchUnitInput))
    val out = ValidIO(new BranchUnitOutput)
}

class BranchUnit extends MkModule {
    val io = IO(new BranchUnitIO)

    io.in.ready := true.B // mis-prediction check could complete within 1 cycle

    val pc    = io.in.bits.pc
    val rj    = io.in.bits.operand_a
    val rd    = io.in.bits.operand_b
    val imm16 = io.in.bits.operand_c

    // generate target address of branch
    val pred_taken = io.in.bits.br_pred.taken
    val taken      = MuxLookup(io.in.bits.optype, false.B)(
        Seq(
            beq  -> (rj === rd),
            bne  -> (rj =/= rd),
            blt  -> (rj.asSInt <= rd.asSInt),
            bltu -> (rj <= rd),
            bge  -> (rj.asSInt >= rd.asSInt),
            bgeu -> (rj >= rd),
            jirl -> true.B
        )
    )

    val br_target = Mux(taken, pc + SEXT(imm16, VADDR_WIDTH), pc + 4.U)

    // check if there is a mis-prediction
    io.out.bits.result.pc       := pc
    io.out.bits.result.redirect := taken ^ pred_taken
    io.out.bits.result.target   := br_target
    io.out.valid                := io.in.valid
}
