package miku

import chisel3._
import chisel3.util._
import chisel3.internal.firrtl.Width
import miku.utils.UEXT

import miku.LA32CSRRegisters._

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

class LA32CSRRegfiles extends MkModule {
    val io = IO(new Bundle {
        val raddr = Input(UInt(14.W))
        val rdata = Output(UInt(WORD_WIDTH.W))
        val waddr = Input(UInt(14.W))
        val wdata = Input(UInt(WORD_WIDTH.W))
        val wen   = Input(Bool())
    })

    val la32_csrs = LA32CSRRegisters.csr_defns.map {
        case (addr, csr) => {
            (addr, RegInit(0.U.asTypeOf(csr())))
        }
    }
    io.rdata := 0.U

    for ((addr, csr) <- la32_csrs) {
        when(io.raddr === addr) {
            io.rdata := csr.rdata
        }
        when(io.wen && io.waddr === addr) {
            csr.write(io.wdata)
        }
    }
}
