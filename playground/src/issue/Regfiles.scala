package miku.issue

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class RegfileReadIO(addr_wd: Int, data_wd: Int) extends MkBundle {
    val raddr = Input(UInt(addr_wd.W))
    val rdata = Output(UInt(data_wd.W))
}

class RegfileWriteIO(addr_wd: Int, data_wd: Int) extends MkBundle {
    val wen   = Input(Bool())
    val waddr = Input(UInt(addr_wd.W))
    val wdata = Input(UInt(data_wd.W))
}

class MkRegfiles extends MkModule {
    val read_io  = IO(Vec(REG_RD_PORTS, new RegfileReadIO(REG_ADDR_WD, WORD_WIDTH)))
    val write_io = IO(new RegfileWriteIO(REG_ADDR_WD, WORD_WIDTH))
    val diff_gpr = if (DIFFTEST_MODE) Some(IO(Vec(REG_ADDR_NUM, UInt(WORD_WIDTH.W)))) else None

    val registers = RegInit(VecInit(Seq.fill(REG_ADDR_NUM)(0.U(WORD_WIDTH.W))))
    for (i <- 0 until REG_RD_PORTS) {
        read_io(i).rdata := Mux(read_io(i).raddr =/= 0.U, registers(read_io(i).raddr), 0.U)
    }

    when(write_io.wen && (write_io.waddr =/= 0.U)) {
        registers(write_io.waddr) := write_io.wdata
    }

    if (DIFFTEST_MODE) {
        for (i <- 0 until REG_ADDR_NUM) {
            diff_gpr.get(i) := registers(i)
        }
    }
}
