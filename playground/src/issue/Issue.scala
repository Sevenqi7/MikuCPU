package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._

class IssueEntry extends MkBundle {
    val pc = UInt(VADDR_WIDTH.W)
    val inst = UInt(INST_BITS.W)
    val decoded_inst = new DecodedInst()
}
class IssueStage extends MkModule {}
