package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.JumpOpType._
import miku.frontend.BranchPredictorUpdate
import miku.frontend.BranchPredictorResult

class BranchUnitIO extends MkBundle {
    val br_pred = Flipped(new BranchPredictorResult)
    val update  = ValidIO(new BranchPredictorUpdate)
}

class BranchUnit extends BaseFunctionUnit {
    val bru_io = IO(new BranchUnitIO)

    io.in.ready := true.B // mis-prediction check could complete within 1 cycle

    val pc    = io.in.bits.pc
    val rj    = io.in.bits.operand_a
    val rd    = io.in.bits.operand_b
    val imm16 = io.in.bits.operand_c

    // generate target address of branch
    val pred_taken = bru_io.br_pred.taken
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
    bru_io.update.bits.pc       := pc
    bru_io.update.bits.redirect := taken ^ pred_taken
    bru_io.update.bits.target   := br_target
    bru_io.update.valid         := io.in.valid
    io.out.bits.exception       := false.B
    io.out.bits.result          := DEBUG_MAGICNUM.U
    io.out.bits.id              := io.in.bits.id
    io.out.valid                := io.in.valid

}
