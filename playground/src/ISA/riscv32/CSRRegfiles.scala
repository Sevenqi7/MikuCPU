package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.backend._

class RV32CSRRegfiles extends CSRRegfiles {
    io.int_flag := false.B
}
