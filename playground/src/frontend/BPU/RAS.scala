package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

trait RASUtils {
    def isCall(inst: UInt): Bool = {
        inst === LA32Instructions.BL
    }

    def isRet(inst: UInt): Bool = {
        val rd = inst(4, 0)
        val rj = inst(9, 5)
        inst === LA32Instructions.JIRL && rd === 0.U && rj === 1.U
    }
}

class MkRAS extends BranchPredictor with RASUtils {

    val ras = Module(new Stack(UInt(VADDR_WIDTH.W), RAS_SIZE))

    // initialise
    io.resp.taken     := false.B
    io.resp.target    := 0.U
    ras.io.in.op      := 0.B
    ras.io.in.data_in := 0.U
    ras.io.in.clear   := false.B
    ras.io.in.valid   := false.B

    when(io.s1.valid) {
        when(isCall(io.s1.bits.inst)) {
            ras.io.in.valid := true.B
            ras.pushData(io.s1.bits.pc + instBytes.U)
        }.elsewhen(isRet(io.s1.bits.inst)) {
            io.resp.taken  := true.B
            io.resp.target := ras.popData
        }
    }
}
