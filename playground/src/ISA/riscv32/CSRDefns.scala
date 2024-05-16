package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku.isa._
import miku.utils._

class FakeRV32CSR extends MkCSRBundle {
    val fakedata = UInt(WORD_WIDTH.W)
    def rdata:                     UInt = DEBUG_MAGICNUM.U
    def getRealWdata(wdata: UInt): UInt = DEBUG_MAGICNUM.U(31, 0)
}

object RV32CSRRegisters extends CSRRegistersDefns {
    def getExcpEntry(csr: CSRVecBundle, excp_enum: UInt): UInt = DEBUG_MAGICNUM.U
    def getExcpRetAddr(csr: CSRVecBundle):                UInt = DEBUG_MAGICNUM.U

    val FAKECSR = (0xffff.U, () => new FakeRV32CSR)
    val csr_defns: Seq[(UInt, () => MkCSRBundle)] = Seq(FAKECSR)
}
