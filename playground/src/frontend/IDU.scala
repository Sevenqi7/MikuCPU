package miku.frontend

import chisel3._
import chisel3.util._
import chisel3.util.experimental.decode._

import miku._
import miku.utils._
import miku.frontend._

class IDUIO extends MkBundle {}

class IDU extends MkModule {
    val io = IO(new IDUIO)
    
    val instQueue = Module(new CircularQueue(UInt(INST_BITS.W), INST_QUEUE_SIZE))
	val decoder = Module(new LA32DecoderUnit)
}
