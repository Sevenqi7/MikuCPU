package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.isa.la32.LA32ExceptionType

class RV32ExceptionType extends ExceptionType {
    def this(params: Any) = {
        this()
        this.enum_no = RV32ExceptionDefns.num.U
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
    val NONE = new RV32ExceptionType(1)
    val INT = new RV32ExceptionType(2)

    def num     = extype_map.size
    def apply() = UInt(log2Ceil(num).W)
}

class RV32ExceptionInfo extends ExceptionInfo {}
