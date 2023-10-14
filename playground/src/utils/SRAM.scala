package miku.utils


import chisel3._
import chisel3.util._
import scala.math

import miku._


class SRAMTemplate[T <: Data](addrWidth: Int, 
    data: T, writeFirst: Boolean = true) extends Module{
    val io = IO(new Bundle{
        val addr = Input(UInt(addrWidth.W))
        val din = Input(UInt(data.getWidth.W))
        val dout = Output(UInt(data.getWidth.W))        
        val wen = Input(Bool())
    })

    val mem_size = 1 << addrWidth
    val mem = SyncReadMem(addrWidth, UInt(data.getWidth.W))

    io.dout := mem.read(io.addr)
    when(io.wen){
        mem.write(io.addr, io.din)
    }
}
