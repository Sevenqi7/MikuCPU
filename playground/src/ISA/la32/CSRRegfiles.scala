package miku

import chisel3._
import chisel3.util._
import chisel3.internal.firrtl.Width
import miku.utils.UEXT

import miku.issue.RegfileReadIO
import miku.issue.RegfileWriteIO
import LA32CSRRegisters._

class LA32CSRReadIO extends RegfileReadIO(14, 32) {}
class LA32CSRWriteIO extends RegfileWriteIO(14, 32) {}

class LA32CSR_RawData extends MkBundle {

    val csr_vec = MixedVec(csr_defns.map(csr => UInt(csr._2().getWidth.W)))

    def getTargetCSR[T <: LA32CSRBundle](target_info: (UInt, () => T)): T = {
        var index = csr_defns.indexOf(target_info)
        if (index == -1) {
            println("Error: target CSR doesn't exist in csr_defns")
            throw new IllegalStateException
        }
        csr_vec(index).asTypeOf(target_info._2())
    }
}

class LA32CSRRegfiles extends MkModule {
    val io        = IO(new Bundle {
        val read_io   = new LA32CSRReadIO
        val write_io  = new LA32CSRWriteIO
        val raw_datas = new LA32CSR_RawData
        // val csr_rdatas = Vec(csr_defns.length, UInt(32.W))
        val timer64_o = UInt(64.W)
    })
    val la32_csrs = csr_defns.map { case (addr, csr_type) => (addr, RegInit(csr_type().initData.asTypeOf(csr_type()))) }
    def csr_table[T <: LA32CSRBundle](csr_info: (UInt, () => T)): T = {
        var retval = csr_info._2()
        var found  = false
        for ((addr, csr) <- la32_csrs) {
            if (addr == csr_info._1) {
                retval = csr.asInstanceOf[T]
                found  = true
            }
        }
        if (!found) throw new IllegalArgumentException
        retval
    }

    io.raw_datas.csr_vec.zip(la32_csrs.map(_._2)).foreach(i => i._1 := i._2.asUInt)

    io.read_io.rdata := 0.U

    for ((addr, csr) <- la32_csrs) {
        when(io.read_io.raddr === addr) {
            io.read_io.rdata := csr.rdata
        }
        when(io.write_io.wen && io.write_io.waddr === addr) {
            csr.write(io.write_io.wdata)
        }
    }

    // PGD read/write
    val badv_msb = csr_table(BADV).asUInt(VADDR_WIDTH - 1)
    val pgdl     = csr_table(PGDL)
    val pgdh     = csr_table(PGDH)
    when(io.read_io.raddr === PGD._1) {
        io.read_io.rdata := Mux(badv_msb, pgdh.rdata, pgdl.rdata)
    }
    when(io.write_io.wen && (io.write_io.waddr === PGD._1)) {
        when(badv_msb) {
            pgdh.write(io.write_io.wdata)
        }.otherwise {
            pgdl.write(io.write_io.wdata)
        }
    }

    val stable_cnt = RegInit(0.U(64.W))
    // stable_cnt.asUInt :=  stable_cnt + 1.U
    stable_cnt   := stable_cnt + 1.U
    io.timer64_o := stable_cnt
}
