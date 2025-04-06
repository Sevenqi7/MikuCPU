package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._

class MkCLINT extends MkModule {
    val io = IO(new Bundle {
        val addr      = Input(UInt(16.W))  
        val wdata     = Input(UInt(32.W))  
        val wen       = Input(Bool())      
        val rdata     = Output(UInt(32.W)) 
        val mtime_irq = Output(Bool())     
    })

    val mtime    = RegInit(0.U(64.W))
    val mtimecmp = RegInit(0xffffffffffffffffL.U(64.W))

    mtime := mtime + 1.U

    io.rdata := 0.U
    when(io.wen) {
        switch(io.addr & 0xFFFF.U) {
            is(0xbff8.U) { mtime := io.wdata } 
            is(0x4000.U) { mtimecmp := io.wdata }
        }
    }.otherwise {
        switch(io.addr & 0xFFFF.U) {
            is(0xbff8.U) { io.rdata := mtime } 
            is(0x4000.U) { io.rdata := mtimecmp }
        }
    }

    io.mtime_irq := mtime >= mtimecmp
}
