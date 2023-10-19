package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

trait RASUtils{
    def isCall(inst: UInt) : Bool = {
        true.B
    }

    def isRet(inst: UInt) : Bool = {
        true.B
    }
}

class MkRAS extends BranchPredictor with RASUtils{

    val ras = Module(new CircularQueue(UInt(VADDR_WIDTH.W), RAS_SIZE))    
    
    when(isCall(io.s1_inst)){
        ras.enqData(io.s1_pc + instBytes.U)
    }
    .elsewhen(isRet(io.s1_inst)){
        io.resp.valid := true.B
        io.resp.bits.taken := true.B
        io.resp.bits.target := ras.deqData
    }
}
