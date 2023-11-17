package miku.frontend

import chisel3._
import chisel3.util._

import miku._

object SrcType {
    def reg = "b00".U
    def pc  = "b01".U
    def imm = "b10".U

    def X = BitPat("b??".U)

    def apply() = UInt(2.W)
}

// Function Unit Type
object FuType {
    def num = 5

    def alu = "b000".U
    def lsu = "b001".U
    def mul = "b010".U
    def div = "b011".U
    def jmp = "b100".U

    def X = BitPat("b???".U)

    def apply() = UInt(log2Up(num).W)
}

object ALUOpType {
    def X = BitPat("b??".U)
}

object JumpOpType {
    def X = BitPat("b??".U)
}

object LSUOpType {
    def X = BitPat("b??".U)
}

object SelImm {
def IMM_X  = "b0111".U
def IMM_S  = "b0000".U
def IMM_U  = "b0010".U
def IMM_UJ = "b0011".U
def IMM_I  = "b0100".U
def IMM_Z  = "b0101".U
def INVALID_INSTR = "b0110".U
def IMM_B6 = "b1000".U

def X      = BitPat("b????")

def apply() = UInt(4.W)
}