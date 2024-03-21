package miku

import chisel3._
import chisel3.util._
import chisel3.internal.firrtl.Width

import miku.utils._

abstract class LA32CSRBundle extends MkBundle {
    def initData: UInt = 0.U(32.W)
    def rdata: UInt
    def getRealWdata(wdata: UInt): UInt
    def wmask = ~0.U(this.getWidth.W)
    def write(wdata: UInt): Unit = {
        val real_wdata = getRealWdata(wdata)
        val bools      = VecInit(this.asUInt.asBools)
        require(real_wdata.getWidth == this.getWidth)
        // println(this.className)
        for (i <- 0 until this.getWidth) {
            when(wmask(i)) {
                bools(i) := real_wdata(i)
            }
        }
        this := bools.asTypeOf(this)
    }
}

// all reserved bits are directly assigned to 0.U and not stated in the Bundle

// 0x0: CRMD
class LA32CSR_Crmd extends LA32CSRBundle {
    // RESERVED BITS (31, 19)

    val WE   = Bool()
    val DATM = UInt(2.W)
    val DATF = UInt(2.W)
    val PG   = Bool()
    val DA   = Bool()
    val IE   = Bool()
    val PLV  = UInt(2.W)

    override def initData: UInt = {
        val init = 0.U.asTypeOf(this)
        init.DA := true.B
        init.asUInt
    }
    def rdata = Cat(0.U(22.W), this.asUInt)
    def getRealWdata(wdata: UInt) = wdata(9, 0)
}

// 0x1: PRMD
class LA32CSR_Prmd extends LA32CSRBundle {
    // RESERVED BTIS (31, 4)
    val PWE  = Bool()
    val PIE  = Bool()
    val PPLV = UInt(2.W)

    def rdata                     = Cat(0.U(28.W), this.asUInt)
    def getRealWdata(wdata: UInt) = wdata(3, 0)
}

// 0x4: ECFG
class LA32CSR_Ecfg extends LA32CSRBundle {
    // RESERVED BITS (31, 19)
    val VS  = UInt(3.W)
    // RESERVED BITS (15, 13)
    val LIE = UInt(13.W)

    def rdata                     = Cat(Seq(0.U(13.W), VS, 0.U(3.W), LIE))
    def getRealWdata(wdata: UInt) = Cat(wdata(18, 16), wdata(12, 0))
}

// 0x5: ESTAT
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

// 0x6: ERA
class LA32CSR_Era extends LA32CSRBundle {
    val PC                        = UInt(VADDR_WIDTH.W)
    def rdata                     = PC
    def getRealWdata(wdata: UInt) = wdata
}

// 0x7: BADV
class LA32CSR_Badv extends LA32CSRBundle {
    val VAddr                     = UInt(VADDR_WIDTH.W)
    def rdata                     = VAddr
    def getRealWdata(wdata: UInt) = wdata
}

// 0xc: EENTRY
class LA32CSR_Eentry extends LA32CSRBundle {
    val VPN                       = UInt((VADDR_WIDTH - 12).W)
    // RESERVED BITS (11, 0)
    def rdata                     = VPN << 12.U
    def getRealWdata(wdata: UInt) = wdata(VADDR_WIDTH - 1, 12)
}

// 0x10: TLBIDX
class LA32CSR_Tlbidx(index_wd: Int) extends LA32CSRBundle {
    require(index_wd <= 16)

    val NE    = Bool()
    // RESERVED BITS (30, 30)
    val PS    = UInt(6.W)
    // RESERVED BITS (23, 16)
    // RESERVED BITS (15, index_wd - 1)
    val Index = UInt(index_wd.W)

    def rdata                     = Cat(NE, 0.B, PS, 0.U(8.W), UEXT(Index, 16))
    def getRealWdata(wdata: UInt) = Cat(Seq(wdata(31), wdata(29, 24), wdata(index_wd - 1, 0)))
}

// 0x11: TLBEHI
class LA32CSR_Tlbehi extends LA32CSRBundle {
    val VPPN = UInt(19.W)
    // RESERVED BITS (12, 0)

    def rdata                     = VPPN << 13.U
    def getRealWdata(wdata: UInt) = wdata(31, 13)
}

// 0x12: TLBELO0
// 0x13: TLBELO1
class LA32CSR_Tlbelo extends LA32CSRBundle {
    // RESERVED BITS (31, VADDR_WIDTH - 4)
    val PPN = UInt((VADDR_WIDTH - 12).W)
    // RESERVED BITS (7, 7)
    val G   = Bool()
    val MAT = UInt(2.W)
    val PLV = UInt(2.W)
    val D   = Bool()
    val V   = Bool()

    def rdata                     = Cat(UEXT(PPN, 24), 0.B, G, MAT, PLV, D, V)
    def getRealWdata(wdata: UInt) = Cat(wdata(VADDR_WIDTH - 5, 8), wdata(6, 0))
}

// 0x18: ASID
class LA32CSR_Asid extends LA32CSRBundle {
    // RESERVED BITS (31, 24)
    val ASIDBITS = UInt(8.W)
    // RESERVED BITS (15, 10)
    val ASID     = UInt(10.W)

    override def initData         = Cat(0.U(8.W), 10.U(10.W))
    def rdata                     = Cat(UEXT(ASIDBITS, 16), UEXT(ASID, 16))
    def getRealWdata(wdata: UInt) = Cat(wdata(23, 16), wdata(9, 0))
}

// 0x18: PGDL, 0x19: PGDH
class LA32CSR_Pgdlh extends LA32CSRBundle {
    val Base                      = UInt(20.W)
    // RESERVED BITS (11, 0)
    def rdata                     = Base << 12.U
    def getRealWdata(wdata: UInt) = wdata(31, 12)
}

class LA32CSR_Pgd extends LA32CSRBundle {
    val Base = UInt(20.W) // read-only

    override def wmask = 0.U
    def rdata          = Base
    def getRealWdata(wdata: UInt): UInt = wdata(31, 12)
}

// 0x20: CPUID
class LA32CSR_Cpuid extends LA32CSRBundle {
    // RESERVED BITS (31, 9)
    val CoreID = UInt(9.W) // read-only

    override def wmask            = 0.U
    def rdata                     = UEXT(CoreID, 32)
    def getRealWdata(wdata: UInt) = wdata(8, 0)
}

// 0x30: SAVE0, 0x31: SAVE1, 0x32: SAVE2, 0x33: SAVE3
class LA32CSR_Save extends LA32CSRBundle {
    val Data = UInt(32.W)

    def rdata                     = Data
    def getRealWdata(wdata: UInt) = wdata
}

// 0x40: TID
class LA32CSR_Tid extends LA32CSRBundle {
    val TID = UInt(32.W)

    def rdata                     = TID
    def getRealWdata(wdata: UInt) = wdata
}

// 0x41: TCFG
class LA32CSR_Tcfg(timer_wd: Int) extends LA32CSRBundle {
    // RESERVED BITS (31, timer_wd)
    val InitVal  = UInt((timer_wd - 2).W)
    val Periodic = Bool()
    val En       = Bool()

    def rdata                     = Cat(0.U(timer_wd.W), this.asUInt)
    def getRealWdata(wdata: UInt) = wdata(timer_wd - 1, 0)
}

// 0x42: TVAL
class LA32CSR_Tval(timer_wd: Int) extends LA32CSRBundle {
    // RESERVED BITS (31, timer_wd)
    val TimeVal = UInt(timer_wd.W) // read-only

    override def wmask            = 0.U
    def rdata                     = UEXT(TimeVal, 32)
    def getRealWdata(wdata: UInt) = wdata(timer_wd - 1, 0)
}

// 0x44: TICLR
class LA32CSR_Ticlr extends LA32CSRBundle {
    // RESERVED BITS (31, 1)
    val CLR = Bool() // always return zero

    def rdata                     = 0.U
    def getRealWdata(wdata: UInt) = wdata(0)
}

// 0X60: LLBCTL
class LA32CSR_Llbctl extends LA32CSRBundle {
    // RESERVED BITS (31, 3)
    val KLO   = Bool()
    val WCLLB = Bool() // always return zero
    val ROLLB = Bool() // read-only

    override def wmask            = Cat(1.B, 0.U(2.W))
    def rdata                     = Cat(Seq(KLO, 0.B, KLO))
    def getRealWdata(wdata: UInt) = Cat(Seq(KLO, 0.B, ROLLB))
}

// 0x88: TLBRENTRY
class LA32CSR_Tlbrentry extends LA32CSRBundle {
    val PA = UInt(26.W)
    // RESERVED BITS (5, 0)

    def rdata                     = PA << 6.U
    def getRealWdata(wdata: UInt) = wdata(31, 6)
}

// 0x180: DMW0
class LA32CSR_Dmw extends LA32CSRBundle {
    val VSEG = UInt(3.W)
    // RESERVED BITS (28, 28)
    val PSEG = UInt(3.W)
    // RESERVED BITS (24, 6)
    val MAT  = UInt(2.W)
    val PLV3 = Bool()
    // RESERVED BITS (2, 1)
    val PLV0 = Bool()

    def rdata: UInt = Cat(VSEG, 0.B, PSEG, 0.U(19.W), MAT, PLV3, 0.U(2.W), PLV0)
    def getRealWdata(wdata: UInt) = Cat(Seq(wdata(31, 29), wdata(27, 25), wdata(5, 3), wdata(0)))
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
    // val CNTC      = 0x43.U
    val TICLR     = 0x44.U
    val LLBCTL    = 0x60.U
    val TLBRENTRY = 0x88.U
    val DMW0      = 0x180.U

    val csr_defns = Seq(
        (CRMD, () => new LA32CSR_Crmd),
        (PRMD, () => new LA32CSR_Prmd),
        (ECFG, () => new LA32CSR_Ecfg),
        (ESTAT, () => new LA32CSR_Estat),
        (ERA, () => new LA32CSR_Era),
        (BADV, () => new LA32CSR_Badv),
        (EENTRY, () => new LA32CSR_Eentry),
        (TLBIDX, () => new LA32CSR_Tlbidx(log2Ceil(TLB_NUM))),
        (TLBEHI, () => new LA32CSR_Tlbehi),
        (TLBELO0, () => new LA32CSR_Tlbelo),
        (TLBELO1, () => new LA32CSR_Tlbelo),
        (ASID, () => new LA32CSR_Asid),
        (PGDL, () => new LA32CSR_Pgdlh),
        (PGDH, () => new LA32CSR_Pgdlh),
        (PGD, () => new LA32CSR_Pgd),
        (CPUID, () => new LA32CSR_Cpuid),
        (SAVE0, () => new LA32CSR_Save),
        (SAVE1, () => new LA32CSR_Save),
        (SAVE2, () => new LA32CSR_Save),
        (SAVE3, () => new LA32CSR_Save),
        (TID, () => new LA32CSR_Tid),
        (TCFG, () => new LA32CSR_Tcfg(TIMER_WD)),
        (TVAL, () => new LA32CSR_Tval(TIMER_WD)),
        // (CNTC, () => new LA32CSR_Cntc),
        (TICLR, () => new LA32CSR_Ticlr),
        (LLBCTL, () => new LA32CSR_Llbctl),
        (TLBRENTRY, () => new LA32CSR_Tlbrentry),
        (DMW0, () => new LA32CSR_Dmw)
    )
}
