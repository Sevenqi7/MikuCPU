package miku.utils

import chisel3._
import chisel3.util._
import scala.math

import miku._

class SRAMTemplate[T <: Data](addrWidth: Int, data: T, wmask_en: Boolean = false) extends Module {
    val io       = IO(new Bundle {
        val addr = Input(UInt(addrWidth.W))
        val din  = Input(UInt(data.getWidth.W)) 
        val dout = Output(UInt(data.getWidth.W))
        val wen  = if (!wmask_en) Input(Bool()) else Input(UInt((data.getWidth / 8).W))
    })
    if (wmask_en) require((data.getWidth % 8) == 0)
    val mem_size = 1 << addrWidth
    if (!wmask_en) {
        val mem = SyncReadMem(mem_size, UInt(data.getWidth.W))
        when(io.wen.asBool) {
            mem.write(io.addr, io.din.asUInt)
        }
        io.dout := mem.read(io.addr)
    } else {
        val mem = SyncReadMem(mem_size, Vec(data.getWidth / 8, UInt(8.W)))
        when(io.wen > 0.U) {
            mem.write(io.addr, io.din.asTypeOf(Vec(data.getWidth / 8, UInt(8.W))), io.wen.asBools)
        }
        io.dout := mem.read(io.addr).asUInt
    }
}
