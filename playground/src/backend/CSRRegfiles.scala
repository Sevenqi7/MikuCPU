package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.issue._

class CSRRegfilesIO extends MkBundle {
    val read_io     = new RegfileReadIO(CSR_ADDR_WD, 32)
    val write_io    = new RegfileWriteIO(CSR_ADDR_WD, 32)
    val raw_datas   = new CSRVecBundle
    val timer64_o   = UInt(64.W)
    val excp_commit = Flipped(ValidIO(ArchExceptionInfo()))
    val ertn_commit = Input(Bool())
    val idle_commit = Input(Bool())
    val interrupt   = Input(UInt(8.W))
    val int_flag    = Bool()
}

abstract class CSRRegfiles extends MkModule {
    lazy val io   = IO(new CSRRegfilesIO)
    val csr_defns = ArchCSRDefns.csr_defns

    val csr_list = csr_defns.map { case (addr, csr_type) => (addr, RegInit(csr_type().initData.asTypeOf(csr_type()))) }
    def csr_table[T <: MkCSRBundle](csr_info: (UInt, () => T)):    T    = {
        var retval = csr_info._2()
        var found  = false
        for ((addr, csr) <- csr_list) {
            if (addr == csr_info._1) {
                retval = csr.asInstanceOf[T]
                found  = true
            }
        }
        if (!found) {
            println("Error: target CSR doesn't exist in csr_defns")
            throw new IllegalArgumentException
        }
        retval
    }
    def isWritingCSR[T <: MkCSRBundle](csr_info: (UInt, () => T)): Bool = {
        io.write_io.wen && (io.write_io.waddr === csr_info._1)
    }

    io.read_io.rdata := 0.U


    // val csr_list : Seq[MkCSRBundle]
    for ((addr, csr) <- csr_list) {
        when(io.read_io.raddr === addr) {
            io.read_io.rdata := csr.rdata
        }
        when(io.write_io.wen && (io.write_io.waddr === addr)) {
            csr.write(io.write_io.wdata)
        }
    }

    val cycles     = RegInit(0.U(64.W))
    val stable_cnt = cycles
    stable_cnt   := stable_cnt + 1.U
    io.timer64_o := stable_cnt

    io.raw_datas.csr_vec.zip(csr_list.map(_._2)).foreach(i => i._1 := i._2.asUInt)
    io.raw_datas.timer_cycle := stable_cnt
}
