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

class RV32CSR_Mepc extends MkCSRBundle {
    val mepc = UInt(WORD_WIDTH.W) // read-only

    def rdata:                     UInt = mepc
    def getRealWdata(wdata: UInt): UInt = wdata
}

class RV32CSR_Mcause extends MkCSRBundle {
    val interrupt = Bool()
    val code      = UInt((WORD_WIDTH - 1).W)

    def rdata:                     UInt = Cat(interrupt, code)
    def getRealWdata(wdata: UInt): UInt = wdata
}

class RV32CSR_Mstatus extends MkCSRBundle {
    // Unimplemented SD BITS(31)
    // RESERVED BITS (30, 23)
    // Unimplemented TSR BITS(22)
    // Unimplemented TW BITS(21)
    // Unimplemented TVM BITS(20)
    // Unimplemented MXR BITS(19)
    // Unimplemented SUM BITS(18)
    // Unimplemented MPRV BITS(17)
    // Unimplemented XS BITS(16, 15)
    // Unimplemented FS BITS(14, 13)
    val MPP  = UInt(2.W) // read-only
    // Unimplement VS BITS(10, 9)
    // Unimplement SPP BITS(8)
    val MPIE = Bool()    // read-only
    // Unimplement UBE BITS(6)
    // Unimplement SPIE BITS(5)
    // RESERVED BITS (4)
    val MIE  = Bool()
    // RESERVED BITS (2)
    // Unimplement SIE BITS(1)
    // RESERVED BITS (0)

    def rdata:                     UInt = Cat(Seq(0.U(19.W), MPP, 0.U(3.W), MPIE, 0.U(3.W), MIE, 0.U(3.W)))
    def getRealWdata(wdata: UInt): UInt = Cat(wdata(14, 13), wdata(7), wdata(3))
    override def wmask:            UInt = "b0001".U(this.getWidth.W)
    override def initData:         UInt = Cat("b11".U(2.W), 0.U(2.W))
}

class RV32CSR_Mtvec extends MkCSRBundle {
    val BASE = UInt((WORD_WIDTH - 2).W)
    val MODE = UInt(2.W)

    def rdata:                     UInt = this.asUInt
    def getRealWdata(wdata: UInt): UInt = wdata
}

object RV32CSRRegisters extends CSRRegistersDefns {
    def getExcpEntry(csr: CSRVecBundle, excp_enum: UInt): UInt = {
        val mtvec = csr.getTargetCSR(MTVEC)
        assert(mtvec.MODE === 0.U) // other modes is not implemented yet
        mtvec.BASE << 2.U
    }
    def getExcpRetAddr(csr: CSRVecBundle):                UInt = csr.getTargetCSR(MEPC).mepc

    val FAKECSR = (0xffff.U, () => new FakeRV32CSR)
    val MSTATUS = (0x300.U, () => new RV32CSR_Mstatus)
    val MTVEC   = (0x305.U, () => new RV32CSR_Mtvec)
    val MEPC    = (0x341.U, () => new RV32CSR_Mepc)
    val MCAUSE  = (0x342.U, () => new RV32CSR_Mcause)

    val csr_defns: Seq[(UInt, () => MkCSRBundle)] = Seq(
        MSTATUS,
        MTVEC,
        MEPC,
        MCAUSE
    )
}
