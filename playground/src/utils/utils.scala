package miku.utils

import chisel3._
import chisel3.util._
import scala.language.implicitConversions

object util{
    implicit def uintToBitPat(x: UInt): BitPat = BitPat(x)
}
