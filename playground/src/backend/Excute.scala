package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._

class BaseFuInput extends MkBundle {
    // val id        = UInt(TRANS_ID_BITS.W)
    val flush     = Bool()
    val optype    = FuOpType()
    val operand_a = UInt(WORD_WIDTH.W) // rj or imm20 in lui12w
    val operand_b = UInt(WORD_WIDTH.W) // rk or imm
    val operand_c = UInt(WORD_WIDTH.W) // imm5 in INVTLB or fk in floating instructions
}

class BaseFuOutput extends MkBundle {
    val result = UInt(WORD_WIDTH.W)
}

class EXU extends MkModule {}
