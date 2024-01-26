package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class RegfileReadIO extends MkBundle {
    // rs is read stage
    // rf is regfile
    val rf_rs_i = Input(UInt(REG_ADDR_SIZE.W))
    val rf_rs_o = Output(UInt(WORD_WIDTH.W))
}

class RegfileWriteIO extends MkBundle {
    // ws is write stage
    // rf is regfile
    val rf_ws_en = Input(Bool())
    val rf_ws_i  = Input(UInt(REG_ADDR_SIZE.W))
}

abstract class RegfileIO extends MkModule {
    val read_io         = IO(new RegfileReadIO)
    val write_io        = VecInit(Seq.fill(4)(IO(new RegfileWriteIO)))
}

class Regfiles extends RegfileIO {
    val registers = RegInit(VecInit(Seq.fill(32)(0.U(32.W))))

}
