package miku.utils

import chisel3._
import chisel3.util._
import scala.language.implicitConversions

object util {
    implicit def uintToBitPat(x: UInt): BitPat = BitPat(x)
}

class PCInstBundle(pc_width: Int, inst_width: Int) extends Bundle {
    val pc   = UInt(pc_width.W)
    val inst = UInt(inst_width.W)
}
