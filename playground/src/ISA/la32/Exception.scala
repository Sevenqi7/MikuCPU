package miku.isa.la32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._

class LA32ExceptionType extends ExceptionType {
    var ecode:    UInt = 0xf.U
    var esubCode: UInt = 0xf.U
    def this(ecode: UInt, esubCode: UInt) = {
        this()
        this.enum_no  = LA32ExceptionDefns.num.U // hint priority
        this.ecode    = ecode
        this.esubCode = esubCode
        LA32ExceptionDefns.addExtype(this)
    }
}

object LA32ExceptionDefns extends ExceptionDefns {
    private var extype_map = Seq[(UInt, LA32ExceptionType)]()
    def addExtype(extype: LA32ExceptionType): Unit = {
        if (extype_map.contains(extype.enum_no)) {
            println("Error: Duplicate exception type defined.")
            throw new IllegalArgumentException
        }
        extype_map = extype_map :+ (extype.enum_no -> extype)
    }
    def getEcodeByExcpNo(enum_no: UInt):      UInt = {
        val ecode_map = extype_map.map { case (enum_no, extype) =>
            (enum_no -> extype.ecode)
        }
        MuxLookup(enum_no, 0.U)(ecode_map)
    }
    def getEsubCodeByExcpNo(enum_no: UInt):   UInt = {
        val subcode_map = extype_map.map { case (enum_no, extype) =>
            (enum_no -> extype.esubCode)
        }
        MuxLookup(enum_no, 0.U)(subcode_map)
    }

//                                  ecode esubcode
//                                    |     |
    val INT  = new LA32ExceptionType(0x0.U, 0.B)
    val PIL  = new LA32ExceptionType(0x1.U, 0.B)
    val PIS  = new LA32ExceptionType(0x2.U, 0.B)
    val PIF  = new LA32ExceptionType(0x3.U, 0.B)
    val PME  = new LA32ExceptionType(0x4.U, 0.B)
    val PPI  = new LA32ExceptionType(0x7.U, 0.B)
    val ADEF = new LA32ExceptionType(0x8.U, 0.B)
    val ADEM = new LA32ExceptionType(0x8.U, 1.B)
    val ALE  = new LA32ExceptionType(0x9.U, 0.B)
    val SYS  = new LA32ExceptionType(0xb.U, 0.B)
    val BRK  = new LA32ExceptionType(0xc.U, 0.B)
    val INE  = new LA32ExceptionType(0xd.U, 0.B)
    val IPE  = new LA32ExceptionType(0xe.U, 0.B)
    val FPD  = new LA32ExceptionType(0xf.U, 0.B)
    val FPE  = new LA32ExceptionType(0x12.U, 0.B)
    val TLBR = new LA32ExceptionType(0x3f.U, 0.B)
    val NONE = new LA32ExceptionType(0xfffff.U, 0.B)

    def num     = extype_map.size
    def apply() = UInt(log2Ceil(num).W)
}

class LA32ExceptionInfo extends ExceptionInfo {}
