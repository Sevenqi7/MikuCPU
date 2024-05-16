package miku.backend

import chisel3._
import chisel3.util._
import chisel3.experimental.BundleLiterals._

import miku._
import miku.isa._
import miku.isa.MiscOpType._
import miku.frontend._

// Handling some funtional instruction like CACOP
// Besides it also handle all instructions which does not need a function unit, such as SYSCALL

// Function unit that excute miscellaneous instruction such as syscall, break.
abstract class MiscFunctionUnit extends BaseFunctionUnit {
    val misc_io: Data
}
