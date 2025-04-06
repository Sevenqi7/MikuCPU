package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.isa.la32.LA32ExceptionType

class RV32ExceptionType extends ExceptionType {
    var interrput: Bool = false.B
    var code:      UInt = 0xf.U
    def this(intr: Bool, code: UInt) = {
        this()
        this.enum_no   = RV32ExceptionDefns.num.U
        this.interrput = intr
        this.code      = code
        RV32ExceptionDefns.addExtype(this)
    }
}

object RV32ExceptionDefns extends ExceptionDefns {
    private var extype_map = Seq[(UInt, RV32ExceptionType)]()
    def addExtype(extype: RV32ExceptionType): Unit = {
        if (extype_map.contains(extype.enum_no)) {
            println("Error: Duplicate exception type defined.")
            throw new IllegalArgumentException
        }
        extype_map = extype_map :+ (extype.enum_no -> extype)
    }

    def getExcpCodeByExcpNo(enum_no: UInt): UInt = {
        val code_map = extype_map.map { case (enum_no, extype) =>
            (enum_no, extype.code)
        }
        MuxLookup(enum_no, 0.U)(code_map)
    }

    def getIntrExcpNo(enum_no: UInt): Bool = {
        val intr_map = extype_map.map { case (enum_no, extype) =>
            (enum_no, extype.interrput)
        }
        MuxLookup(enum_no, 0.B)(intr_map)
    }
    val NONE = new RV32ExceptionType(false.B, 0xffffff.U)
    val INT    = new RV32ExceptionType(true.B, 7.U)
    val UECALL = new RV32ExceptionType(false.B, 8.U)
    val MECALL = new RV32ExceptionType(false.B, 11.U)

    def num     = extype_map.size
    def apply() = UInt(log2Ceil(num).W)
}

class RV32ExceptionInfo extends ExceptionInfo {}
