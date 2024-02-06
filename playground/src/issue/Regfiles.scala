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

abstract class RegfileIO extends MkModule {
    val read_io  = VecInit(Seq.fill(3)(IO(new RegfileReadIO)))
    val write_io = IO(new RegfileWriteIO)
}

class Regfiles extends RegfileIO {
    val registers = RegInit(VecInit(Seq.fill(32)(0.U(32.W))))
    for (i <- 0 until 3) {
        read_io(i).rf_rs_o := registers(read_io(i).rf_rs_i)
    }
    when(write_io.rf_ws_en) {
        registers(write_io.rf_ws_i) := write_io.rf_ws_data
    }
}
