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

class ConstantValCSR(constant: BigInt) extends MkCSRBundle {
    val fakedata = UInt(WORD_WIDTH.W)

    def rdata:                     UInt = constant.U
    def getRealWdata(wdata: UInt): UInt = wdata(WORD_WIDTH - 1, 0)
    // override def wmask:            UInt = 0.U`
}

// Not a real CSR
class RV32CSR_Priv extends MkCSRBundle {
    val priv = UInt(3.W)
    def rdata:                     UInt = priv
    def getRealWdata(wdata: UInt): UInt = wdata(2, 0)
    override def wmask:            UInt = 0.U
}

class RV32CSR_Mscratch extends MkCSRBundle {
    val mscratch = UInt(WORD_WIDTH.W)

    def rdata:                     UInt = mscratch
    def getRealWdata(wdata: UInt): UInt = wdata
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
    val MPP  = UInt(2.W)
    // Unimplement VS BITS(10, 9)
    // Unimplement SPP BITS(8)
    val MPIE = Bool()
    // Unimplement UBE BITS(6)
    // Unimplement SPIE BITS(5)
    // RESERVED BITS (4)
    val MIE  = Bool()
    // RESERVED BITS (2)
    // Unimplement SIE BITS(1)
    // RESERVED BITS (0)

    def rdata:                     UInt = Cat(Seq(0.U(19.W), MPP, 0.U(3.W), MPIE, 0.U(3.W), MIE, 0.U(3.W)))
    def getRealWdata(wdata: UInt): UInt = Cat(wdata(12, 11), wdata(7), wdata(3))
    // override def initData:         UInt = Cat("b11".U(2.W), 0.U(2.W))
}

class RV32CSR_Mtvec extends MkCSRBundle {
    val BASE = UInt((WORD_WIDTH - 2).W)
    val MODE = UInt(2.W)

    def rdata:                     UInt = this.asUInt
    def getRealWdata(wdata: UInt): UInt = wdata
}

class RV32CSR_Mtval extends MkCSRBundle {
    val mtval = UInt(WORD_WIDTH.W)

    def rdata:                     UInt = mtval
    def getRealWdata(wdata: UInt): UInt = wdata
}

// currently only support timer interrput
class RV32CSR_Mip extends MkCSRBundle {
    val mtip = Bool() // read-only

    def rdata:                     UInt = mtip << 7.U
    def getRealWdata(wdata: UInt): UInt = wdata(7)
    override def wmask:            UInt = 0.U
}

class RV32CSR_Mie extends MkCSRBundle {
    val mtie = Bool()
    val msie = Bool()

    def rdata:                     UInt = (mtie << 7.U) | (msie << 3.U)
    def getRealWdata(wdata: UInt): UInt = Cat(wdata(7), wdata(3))
}

object RV32CSRRegisters extends CSRRegistersDefns {
    def getExcpEntry(csr: CSRVecBundle, excp_enum: UInt): UInt = {
        val mtvec = csr.getTargetCSR(MTVEC)
        assert(mtvec.MODE === 0.U) // other modes is not implemented yet
        mtvec.BASE << 2.U
    }
    def getExcpRetAddr(csr: CSRVecBundle):                UInt = csr.getTargetCSR(MEPC).mepc

    val PRIV = (0x777.U, () => new RV32CSR_Priv)

    val FAKECSR  = (0xffff.U, () => new FakeRV32CSR)
    val MSTATUS  = (0x300.U, () => new RV32CSR_Mstatus)
    val MIE      = (0x304.U, () => new RV32CSR_Mie)
    val MTVEC    = (0x305.U, () => new RV32CSR_Mtvec)
    val MSCRATCH = (0x340.U, () => new RV32CSR_Mscratch)
    val MEPC     = (0x341.U, () => new RV32CSR_Mepc)
    val MCAUSE   = (0x342.U, () => new RV32CSR_Mcause)
    val MTVAL    = (0x343.U, () => new RV32CSR_Mtval)
    val MIP      = (0x344.U, () => new RV32CSR_Mip)

    // csr that implemented as constant
    val PMPCFG0   = (0x3a0.U, () => new ConstantValCSR(0x0))
    val PMPADDR0  = (0x3b0.U, () => new ConstantValCSR(0x0))
    val MVENDORID = (0xf11.U, () => new ConstantValCSR(0xff0ff0ffL))
    val MARCHID   = (0xf12.U, () => new ConstantValCSR(0x0))
    val MIMPID    = (0xf13.U, () => new ConstantValCSR(0x0))
    val MHARTID   = (0xf14.U, () => new ConstantValCSR(0x0))

    val csr_defns: Seq[(UInt, () => MkCSRBundle)] = Seq(
        MSTATUS,
        MIE,
        MTVEC,
        MSCRATCH,
        MEPC,
        MCAUSE,
        MTVAL,
        MIP,
        PMPCFG0,
        PMPADDR0,
        MVENDORID,
        MARCHID,
        MIMPID,
        MHARTID,
        PRIV
    )
}
