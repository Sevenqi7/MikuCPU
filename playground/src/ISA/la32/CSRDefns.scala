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
    // RESERVED BITS (31, 4)
    val PWE  = Bool()
    val PIE  = Bool()
    val PPLV = UInt(2.W)

    def rdata                     = Cat(0.U(28.W), this.asUInt)
    def getRealWdata(wdata: UInt) = wdata(3, 0)
}

// 0x2: EUEN
class LA32CSR_Euen extends LA32CSRBundle {
    // RESERVED BITS (31m 1)
    val FPE = Bool()

    def rdata                     = FPE
    def getRealWdata(wdata: UInt) = wdata(0)
}

// 0x4: ECFG
class LA32CSR_Ecfg extends LA32CSRBundle {
    // RESERVED BITS (31, 19)
    // val VS  = UInt(3.W) -- unimplemented field
    // RESERVED BITS (15, 13)
    val LIE = UInt(13.W) // Since PMI is unimplemented, LIE(10) is assigned to 0

    def rdata                     = UEXT(LIE, WORD_WIDTH)
    def getRealWdata(wdata: UInt) = Cat(Seq(wdata(12, 11), 0.B, wdata(9, 0)))
}

// 0x5: ESTAT
class LA32CSR_Estat extends LA32CSRBundle {
    // RESERVED BITS (31)
    val EsubCode = UInt(9.W) // read-only
    val Ecode    = UInt(6.W) // read-only
    // RESERVED BITS (15, 15)
    // Unimplemented MsgInt (14, 14)
    // Reserved Bits (13, 13)
    val IS       = new Bundle {
        val IPI = Bool()
        val TI  = Bool()
        val PMI = Bool()
        val HWI = Vec(8, Bool())
        val SWI = Vec(2, Bool())
    }

    def rdata                     = Cat(Seq(0.B, EsubCode, Ecode, 0.U(3.W), IS.asUInt))
    def getRealWdata(wdata: UInt) = UEXT(wdata(1, 0), this.getWidth)
    override def wmask            = UEXT(~0.U(2.W), this.getWidth)
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
    val VA                        = UInt((VADDR_WIDTH - 6).W)
    // RESERVED BITS (11, 0)
    def rdata                     = VA << 6.U
    def getRealWdata(wdata: UInt) = wdata(VADDR_WIDTH - 1, 6)
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
    def writeFromTlb(entry: TLBEntry, odd_page: Int): Unit = {
        this.G   := entry.g
        this.PPN := entry.page_table(odd_page).ppn
        this.MAT := entry.page_table(odd_page).mat
        this.PLV := entry.page_table(odd_page).plv
        this.D   := entry.page_table(odd_page).d
        this.V   := entry.page_table(odd_page).v
    }
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

// CSR type used for debug
class FakeLA32CSR extends LA32CSRBundle {
    val fakedata = UInt(WORD_WIDTH.W)
    def rdata:                     UInt = DEBUG_MAGICNUM.U
    def getRealWdata(wdata: UInt): UInt = DEBUG_MAGICNUM.U
}

// list of implemented (or to be implemented) csr registers
object LA32CSRRegisters extends MkParams {
    //               addr       () => new <csr_type>
    //                |                 |
    val CRMD      = (0x0.U, () => new LA32CSR_Crmd)
    val PRMD      = (0x1.U, () => new LA32CSR_Prmd)
    val EUEN      = (0x2.U, () => new LA32CSR_Euen)
    val ECFG      = (0x4.U, () => new LA32CSR_Ecfg)
    val ESTAT     = (0x5.U, () => new LA32CSR_Estat)
    val ERA       = (0x6.U, () => new LA32CSR_Era)
    val BADV      = (0x7.U, () => new LA32CSR_Badv)
    val EENTRY    = (0xc.U, () => new LA32CSR_Eentry)
    val TLBIDX    = (0x10.U, () => new LA32CSR_Tlbidx(log2Ceil(TLB_NUM)))
    val TLBEHI    = (0x11.U, () => new LA32CSR_Tlbehi)
    val TLBELO0   = (0x12.U, () => new LA32CSR_Tlbelo)
    val TLBELO1   = (0x13.U, () => new LA32CSR_Tlbelo)
    val ASID      = (0x18.U, () => new LA32CSR_Asid)
    val PGDL      = (0x19.U, () => new LA32CSR_Pgdlh)
    val PGDH      = (0x1a.U, () => new LA32CSR_Pgdlh)
    val PGD       = (0x1b.U, () => new LA32CSR_Pgd)
    val CPUID     = (0x20.U, () => new LA32CSR_Cpuid)
    val SAVE0     = (0x30.U, () => new LA32CSR_Save)
    val SAVE1     = (0x31.U, () => new LA32CSR_Save)
    val SAVE2     = (0x32.U, () => new LA32CSR_Save)
    val SAVE3     = (0x33.U, () => new LA32CSR_Save)
    val TID       = (0x40.U, () => new LA32CSR_Tid)
    val TCFG      = (0x41.U, () => new LA32CSR_Tcfg(TIMER_WD))
    val TVAL      = (0x42.U, () => new LA32CSR_Tval(TIMER_WD))
    val TICLR     = (0x44.U, () => new LA32CSR_Ticlr)
    val LLBCTL    = (0x60.U, () => new LA32CSR_Llbctl)
    val TLBRENTRY = (0x88.U, () => new LA32CSR_Tlbrentry)
    val DMW0      = (0x180.U, () => new LA32CSR_Dmw)
    val DMW1      = (0x181.U, () => new LA32CSR_Dmw)

    //format: off
    val csr_defns = Seq(
        CRMD     ,
        PRMD     ,
        EUEN     ,
        ECFG     ,
        ESTAT    ,
        ERA      ,
        BADV     ,
        EENTRY   ,
        TLBIDX   ,
        TLBEHI   ,
        TLBELO0  ,
        TLBELO1  ,
        ASID     ,
        PGDL     ,
        PGDH     ,
        SAVE0    ,
        SAVE1    ,
        SAVE2    ,
        SAVE3    ,
        TID      ,
        TCFG     ,
        TVAL     ,
        TICLR    ,
        LLBCTL   ,
        TLBRENTRY,
        DMW0     ,
        DMW1     ,
    )
    //format: on
}
