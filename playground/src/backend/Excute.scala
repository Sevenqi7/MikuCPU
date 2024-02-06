package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._

abstract class BaseFuInput extends MkBundle {
    // val id        = UInt(TRANS_ID_BITS.W)
    val pc        = UInt(VADDR_WIDTH.W)
    val flush     = Bool()
    val optype    = FuOpType()
    val operand_a = UInt(WORD_WIDTH.W) // rj
    val operand_b = UInt(WORD_WIDTH.W) // rk or imms
    val operand_c = UInt(WORD_WIDTH.W) // rd for branch and store insts or src3 for some floating insts
}


abstract class BaseFuOutput extends MkBundle {
    val result: Data
}


class EXUIO extends MkBundle {
    
}

class EXU extends MkModule {
    val io = IO(new EXUIO)

}
