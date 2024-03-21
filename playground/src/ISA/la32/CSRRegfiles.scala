package miku

import chisel3._
import chisel3.util._
import chisel3.internal.firrtl.Width
import miku.utils.UEXT

import miku.LA32CSRRegisters.csr_defns
import miku.issue.RegfileReadIO
import miku.issue.RegfileWriteIO

// class foobar extends MkModule {
//     val io = IO(new Bundle {
//         val in  = Input(UInt(5.W))
//         val out = Output(UInt(2.W))
//     })

//     class zerobundle extends Bundle {
//         val zero = UInt(5.W)
//     }
//     val test = LA32CSRRegisters.csr_defns(LA32CSRRegisters.CRMD._1)
//     val aa   = RegInit(10.U.asTypeOf(test))
//     io.out := Cat(aa.asUInt(4, 3), io.in & aa.asUInt(1, 0))
// }

class LA32CSRReadIO extends RegfileReadIO(14, 32) {}
class LA32CSRWriteIO extends RegfileWriteIO(14, 32) {}

class LA32CSRRegfiles extends MkModule {
    val io = IO(new Bundle {
        val read_io   = new LA32CSRReadIO
        val write_io  = new LA32CSRWriteIO
        val csr_datas = Vec(csr_defns.length, UInt(32.W))
        val timer64_o = UInt(64.W)
    })

    val la32_csrs = csr_defns.map {
        case (addr, csr) => {
            (addr, RegInit(csr().initData.asTypeOf(csr())))
        }
    }
    io.csr_datas.zip(la32_csrs.map(_._2)).foreach(i => i._1 := i._2.rdata)

    io.read_io.rdata := 0.U

    for ((addr, csr) <- la32_csrs) {
        when(io.read_io.raddr === addr) {
            io.read_io.rdata := csr.rdata
        }
        when(io.write_io.wen && io.write_io.waddr === addr) {
            csr.write(io.write_io.wdata)
        }
    }

    val stable_counter = RegInit(0.U(64.W))
    stable_counter := stable_counter + 1.U
    io.timer64_o   := stable_counter

    // pgh

}
