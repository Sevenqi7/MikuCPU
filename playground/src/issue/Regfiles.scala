package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class RegfileReadIO extends MkBundle {
    // rs is read stage
    // rf is regfile
    val rf_rs_i = Input(UInt(REG_ADDR_WD.W))
    val rf_rs_o = Output(UInt(WORD_WIDTH.W))
}

class RegfileWriteIO extends MkBundle {
    // ws is write stage
    // rf is regfile
    val rf_ws_en   = Input(Bool())
    val rf_ws_i    = Input(UInt(REG_ADDR_WD.W))
    val rf_ws_data = Input(UInt(WORD_WIDTH.W))
}

class Regfiles extends MkModule {
    val read_io  = IO(Vec(REG_RD_PORTS, new RegfileReadIO))
    val write_io = IO(new RegfileWriteIO)

    for (i <- 0 until REG_RD_PORTS) {
        read_io(i).rf_rs_o := 0.U
    }

    val registers = RegInit(VecInit(Seq.fill(REG_ADDR_WIDTH)(0.U(WORD_WIDTH.W))))
    for (i <- 0 until REG_RD_PORTS) {
        read_io(i).rf_rs_o := registers(read_io(i).rf_rs_i)
    }
    when(write_io.rf_ws_en) {
        registers(write_io.rf_ws_i) := write_io.rf_ws_data
    }
}
