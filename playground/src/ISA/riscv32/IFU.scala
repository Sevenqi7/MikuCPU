package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.frontend._

class RV32IFU extends MkIFU {
    s0_excp     := DontCare
    s1_excp     := ArchExceptionType.NONE.enum_no
    s0_uncached := true.B
}
