package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.isa.JumpOpType._
import miku.frontend.BranchPredictorUpdate
import miku.frontend.BranchPredictorResult

class BranchUnitIO extends MkBundle {
    val br_pred = Flipped(new BranchPredictorResult)
    val update  = ValidIO(new BranchPredictorUpdate)
}

abstract class MkBRU extends BaseFunctionUnit {
    val bru_io = IO(new BranchUnitIO)
    io.in.ready := true.B // mis-prediction check could complete within 1 cycle

    val pc   = io.in.bits.pc
    val lval = io.in.bits.operand_a
    val rval = io.in.bits.operand_c

    // generate target address of branch
    val pred_taken  = bru_io.br_pred.taken
    val pred_target = bru_io.br_pred.target

    val btype_list  = Seq(
        beq  -> (lval === rval),
        bne  -> (lval =/= rval),
        blt  -> (lval.asSInt < rval.asSInt),
        bltu -> (lval < rval),
        bge  -> (lval.asSInt >= rval.asSInt),
        bgeu -> (lval >= rval)
    )
    val btype_taken = MuxLookup(io.in.bits.optype, false.B)(btype_list)
    val jtype_taken = Wire(Bool())

    // unconditional jump like jal/bl is in ISA-specified implementation
    // of this abstract class

    val taken = btype_taken | jtype_taken

    val link_flag = Wire(Bool())
    val br_target = Wire(UInt(VADDR_WIDTH.W))

    val mispred     = (taken ^ pred_taken) || (taken & pred_taken & (br_target =/= pred_target))
    val update_flag = io.in.valid & taken & !pred_taken

    // check if there is a misprediction
    bru_io.update.bits.pc       := pc
    bru_io.update.bits.is_taken := taken
    bru_io.update.bits.target   := br_target
    bru_io.update.valid         := io.in.valid & mispred
    io.out.bits.exception       := io.in.bits.exception
    io.out.bits.mispred         := mispred
    io.out.bits.result          := Mux(link_flag, pc + 4.U, 0.U)
    io.out.bits.id              := io.in.bits.id
    io.out.valid                := io.in.valid
}
