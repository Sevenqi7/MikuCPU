package miku

import chisel3._
import chisel3.util._
import chisel3.internal.firrtl.Width

import miku.utils._

abstract class LA32CSRBundle extends MkBundle {
    def initData: UInt = 0.U(32.W)
    def rdata: UInt
    def getRealWdata(wdata: UInt): UInt
    def wmask              = ~0.U(this.getWidth.W)
    def write(wdata: UInt) = {
        val real_wdata = getRealWdata(wdata)
        val bools      = VecInit(this.asUInt.asBools)
        for (i <- 0 until this.getWidth) {
            when(wmask(i)) {
                bools(i) := real_wdata(i)
            }
        }
        this := bools.asTypeOf(this)
    }
}

// all reserved bits are directly assigned to 0.U and not stated in the Bundle

class LA32CSR_Crmd extends LA32CSRBundle {
    // RESERVED BITS (31, 19)

    val WE   = Bool()
    val DATM = UInt(2.W)
    val DATF = UInt(2.W)
    val PG   = Bool()
    val DA   = Bool()
    val IE   = Bool()
    val PLV  = UInt(2.W)

    // def initdata: UInt = 0.U(this.getWidth.W)
    def rdata                     = Cat(0.U(22.W), this.asUInt)
    def getRealWdata(wdata: UInt) = wdata(9, 0)
}

class LA32CSR_Prmd extends LA32CSRBundle {
    // RESERVED BTIS (31, 4)
    val PWE  = Bool()
    val PIE  = Bool()
    val PPLV = UInt(2.W)

    def rdata                     = Cat(0.U(28.W), this.asUInt)
    def getRealWdata(wdata: UInt) = wdata(3, 0)
}

class LA32CSR_Ecfg extends LA32CSRBundle {
    // RESERVED BITS (31, 19)
    val VS  = UInt(3.W)
    // RESERVED BITS (15, 13)
    val LIE = UInt(13.W)

    def rdata                     = Cat(Seq(0.U(13.W), VS, 0.U(3.W), LIE))
    def getRealWdata(wdata: UInt) = Cat(wdata(18, 16), wdata(12, 0))
}

class LA32CSR_Estat extends LA32CSRBundle {
    // RESERVED BITS (31)
    val EsubCode = UInt(9.W) // read-only
    val Ecode    = UInt(6.W) // read-only
    // RESERVED BITS (15, 15)
    // Unimplemented MsgInt (14, 14)
    // Reserved Bits (13, 13)
    val IS       = MixedVec(Seq(UInt(11.W), UInt(2.W)))

    def rdata                     = Cat(Seq(0.B, EsubCode, Ecode, 0.U(3.W), IS.asUInt))
    def getRealWdata(wdata: UInt) = UEXT(wdata(1, 0), this.getWidth)
    override def wmask            = Cat(0.U(26.W), ~0.U(2.W))
}

class LA32CSR_Era extends LA32CSRBundle {
    val PC                        = UInt(VADDR_WIDTH.W)
    def rdata                     = PC
    def getRealWdata(wdata: UInt) = wdata
}

class LA32CSR_Badv extends LA32CSRBundle {
    val VAddr                     = UInt(VADDR_WIDTH.W)
    def rdata                     = VAddr
    def getRealWdata(wdata: UInt) = wdata
}

class LA32CSR_Eentry extends LA32CSRBundle {
    val VPN                       = UInt((VADDR_WIDTH - 12).W)
    // RESERVED BITS (11, 0)
    def rdata                     = VPN << 12.U
    def getRealWdata(wdata: UInt) = wdata(VADDR_WIDTH - 1, 12)
}

// list of implemented (or to be implemented) csr registers
object LA32CSRRegisters extends MkParams {
    val CRMD      = 0x0.U
    val PRMD      = 0x1.U
    val ECFG      = 0x4.U
    val ESTAT     = 0x5.U
    val ERA       = 0x6.U
    val BADV      = 0x7.U
    val EENTRY    = 0xc.U
    val TLBIDX    = 0x10.U
    val TLBEHI    = 0x11.U
    val TLBELO0   = 0x12.U
    val TLBELO1   = 0x13.U
    val ASID      = 0x18.U
    val PGDL      = 0x19.U
    val PGDH      = 0x1a.U
    val PGD       = 0x1b.U
    val CPUID     = 0x20.U
    val SAVE0     = 0x30.U
    val SAVE1     = 0x31.U
    val SAVE2     = 0x32.U
    val SAVE3     = 0x33.U
    val TID       = 0x40.U
    val TCFG      = 0x41.U
    val TVAL      = 0x42.U
    val CNTC      = 0x43.U
    val TICLR     = 0x44.U
    val LLBCTL    = 0x60.U
    val TLBRENTRY = 0x88.U
    val DMW0      = 0x180.U

    val csr_defns = Seq(
        (CRMD   , () => new LA32CSR_Crmd),
        (PRMD   , () => new LA32CSR_Prmd),
        (ECFG   , () => new LA32CSR_Ecfg),
        (ESTAT  , () => new LA32CSR_Estat),
        (ERA    , () => new LA32CSR_Era),
        (BADV   , () => new LA32CSR_Badv),
        (EENTRY , () => new LA32CSR_Eentry)
    )
    // TLBIDX -- TO BE COMPLETED
    // TLBEHI -- TO BE COMPLETED
    // TLBELO0 -- TO BE COMPLETED
    // TLBEL01 -- TO BE COMPLETED
    // ASID -- TO BE COMPLETED
    // PGDL -- TO BE COMPLETED
    // PGDH -- TO BE COMPLETED
    // PGD -- TO BE COMPLETED
}
