package miku

import chisel3._
import chisel3.util._
import chisel3.internal.firrtl.Width

import miku.utils.UEXT
import miku.issue.RegfileReadIO
import miku.issue.RegfileWriteIO
import LA32CSRRegisters._
import LA32ExceptionType._
import miku.utils.ReadyValidBundle
import chisel3.util.random.LFSR

class LA32CSRReadIO extends RegfileReadIO(14, 32) {}
class LA32CSRWriteIO extends RegfileWriteIO(14, 32) {}

class LA32CSR_RawData extends MkBundle {

    val csr_vec = MixedVec(csr_defns.map(csr => UInt(csr._2().getWidth.W)))

    def getTargetCSR[T <: LA32CSRBundle](target_info: (UInt, () => T)): T = {
        var index = csr_defns.indexOf(target_info)
        if (index == -1) {
            println("Error: target CSR doesn't exist in csr_defns")
            throw new IllegalArgumentException
        }
        csr_vec(index).asTypeOf(target_info._2())
    }
}

class LA32CSRRegfiles extends MkModule {
    val io = IO(new Bundle {
        val read_io        = new LA32CSRReadIO
        val write_io       = new LA32CSRWriteIO
        val raw_datas      = new LA32CSR_RawData
        val timer64_o      = UInt(64.W)
        val excp_commit    = Flipped(ValidIO(new LA32ExceptionInfo))
        val ertn_commit    = Input(Bool())
        val tlbrd_commit   = Input(Bool())
        val tlbwr_commit   = Input(Bool())
        val tlbfill_commit = Input(Bool())
        val ll_commit      = Input(Bool())
        val sc_commit      = Input(Bool())
        val tlbwr_wdata    = new TLBWritePort(TLB_NUM)
        val tlbrd_result   = Input(new TLBEntry)
        val interrupt      = Input(UInt(8.W))
        val int_flag       = Bool()
    })

    val la32_csrs = csr_defns.map { case (addr, csr_type) => (addr, RegInit(csr_type().initData.asTypeOf(csr_type()))) }
    def csr_table[T <: LA32CSRBundle](csr_info: (UInt, () => T)):    T    = {
        var retval = csr_info._2()
        var found  = false
        for ((addr, csr) <- la32_csrs) {
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
    def isWritingCSR[T <: LA32CSRBundle](csr_info: (UInt, () => T)): Bool = {
        io.write_io.wen && (io.write_io.waddr === csr_info._1)
    }

    io.raw_datas.csr_vec.zip(la32_csrs.map(_._2)).foreach(i => i._1 := i._2.asUInt)

    io.read_io.rdata := 0.U

    for ((addr, csr) <- la32_csrs) {
        when(io.read_io.raddr === addr) {
            io.read_io.rdata := csr.rdata
        }
        when(io.write_io.wen && (io.write_io.waddr === addr)) {
            csr.write(io.write_io.wdata)
        }
    }

    val stable_cnt = RegInit(0.U(64.W))
    stable_cnt   := stable_cnt + 1.U
    io.timer64_o := stable_cnt

    // TIMER
    val tcfg  = csr_table(TCFG)
    val tval  = csr_table(TVAL)
    val ticlr = csr_table(TICLR)

    val timer_en   = RegInit(0.B)
    val timer_int  = Wire(Bool())
    val tcfg_wdata = tcfg.getRealWdata(io.write_io.wdata).asTypeOf(tcfg)
    timer_int := (tval.TimeVal === 0.U) && tcfg.En
    timer_en  := MuxCase(
        timer_en,
        Seq(
            isWritingCSR(TCFG) -> tcfg_wdata.En,
            timer_int          -> tcfg.Periodic
        )
    )

    tval.TimeVal := MuxCase(
        tval.TimeVal,
        Seq(
            isWritingCSR(TCFG)                                     -> (tcfg_wdata.InitVal << 2),
            (timer_en && (tval.TimeVal > 0.U))                     -> (tval.TimeVal - 1.U),
            (timer_en && (tval.TimeVal === 0.U) && tcfg.Periodic)  -> (tcfg.InitVal << 2.U),
            (timer_en && (tval.TimeVal === 0.U) && !tcfg.Periodic) -> 0xffffffffL.U
        )
    )

    // Exception & Interrupt handle
    val badv_update_v = io.excp_commit.valid &
        Seq(TLBR, ADEF, ALE, PIL, PIS, PIF, PME, PPI)
            .map(_.enum_no === io.excp_commit.bits.extype)
            .reduce(_ || _)

    val era  = csr_table(ERA)
    val badv = csr_table(BADV)
    val crmd = csr_table(CRMD)
    val prmd = csr_table(PRMD)
    when(io.excp_commit.valid) {
        era.PC    := io.excp_commit.bits.pc
        when(io.excp_commit.bits.extype === TLBR.enum_no) {
            crmd.DA := 1.B
            crmd.PG := 0.B
        }
        crmd.IE   := 0.B
        crmd.PLV  := 0.U
        prmd.PPLV := crmd.PLV
        prmd.PIE  := crmd.IE
        // update badv
        when(badv_update_v) {
            badv.write(io.excp_commit.bits.badv)
        }
    }

    val estat = csr_table(ESTAT)
    val ecfg  = csr_table(ECFG)

    estat.IS.HWI := VecInit(io.interrupt.asBools)
    estat.IS.TI  := MuxCase(
        estat.IS.TI,
        Seq(
            (isWritingCSR(TICLR) && io.write_io.wdata(0)) -> false.B,
            timer_int                                     -> true.B
        )
    )
    when(isWritingCSR(TICLR) && io.write_io.wdata(0)) {
        estat.IS.TI := 0.B
    }
    io.int_flag  := ((ecfg.LIE & estat.IS.asUInt) =/= 0.U) && crmd.IE

    when(io.excp_commit.valid) {
        estat.Ecode    := getEcodeByExcpNo(io.excp_commit.bits.extype)
        estat.EsubCode := getEsubCodeByExcpNo(io.excp_commit.bits.extype)
    }

    // ERTN & LLBIT handle
    val llbctl = csr_table(LLBCTL)
    when(io.ertn_commit) {
        crmd.PLV := prmd.PPLV
        crmd.IE  := prmd.PIE
        when(estat.Ecode === 0x3f.U) {
            crmd.PG := 1.B
            crmd.DA := 0.B
        }

        llbctl.KLO := 0.B
        when(!llbctl.KLO) {
            llbctl.ROLLB := 0.B
        }
    }

    when(io.ll_commit) {
        llbctl.ROLLB := 1.B
    }.elsewhen(io.sc_commit) {
        llbctl.ROLLB := 0.B
    }

    val llbctl_wdata = llbctl.getRealWdata(io.write_io.wdata).asTypeOf(llbctl)
    when(isWritingCSR(LLBCTL) && llbctl_wdata.WCLLB) {
        llbctl.ROLLB := 0.B
    }

    // PGD read/write
    // TODO: replace currently critical badv_msb signal
    val badv_msb = Mux(!isWritingCSR(BADV), csr_table(BADV).rdata(VADDR_WIDTH - 1), io.write_io.wdata(VADDR_WIDTH - 1))
    val pgdl     = csr_table(PGDL)
    val pgdh     = csr_table(PGDH)
    when(io.read_io.raddr === PGD._1) {
        io.read_io.rdata := Mux(badv_msb, pgdh.rdata, pgdl.rdata)
    }
    // when(isWritingCSR(PGD)) {
    //     when(badv_msb) {
    //         pgdh.write(io.write_io.wdata)
    //     }.otherwise {
    //         pgdl.write(io.write_io.wdata)
    //     }
    // }

    // TLB-related CSR
    val tlbehi = csr_table(TLBEHI)
    val tlblo0 = csr_table(TLBELO0)
    val tlblo1 = csr_table(TLBELO1)
    val tlbidx = csr_table(TLBIDX)
    val asid   = csr_table(ASID)

    val excp_tlb = io.excp_commit.valid && MuxLookup(io.excp_commit.bits.extype, false.B)(
        Seq(
            LA32ExceptionType.TLBR.enum_no -> true.B,
            LA32ExceptionType.PIL.enum_no  -> true.B,
            LA32ExceptionType.PIS.enum_no  -> true.B,
            LA32ExceptionType.PPI.enum_no  -> true.B,
            LA32ExceptionType.PME.enum_no  -> true.B,
            LA32ExceptionType.PIF.enum_no  -> true.B
        )
    )

    // TLB-related exception
    when(excp_tlb) {
        tlbehi.write(io.excp_commit.bits.badv)
    }

    // tlbrd
    when(io.tlbrd_commit) {
        val tlb_v = io.tlbrd_result.e
        tlbidx.NE   := !tlb_v
        tlbidx.PS   := Mux(tlb_v, io.tlbrd_result.ps, 0.U)
        tlbehi.VPPN := Mux(tlb_v, io.tlbrd_result.vppn, 0.U)
        tlblo0.writeFromTlb(Mux(tlb_v, io.tlbrd_result, 0.U.asTypeOf(new TLBEntry)), odd_page = 0)
        tlblo1.writeFromTlb(Mux(tlb_v, io.tlbrd_result, 0.U.asTypeOf(new TLBEntry)), odd_page = 1)
        asid.ASID := Mux(tlb_v, io.tlbrd_result.asid, 0.U)
    }

    // tlbwr
    io.tlbwr_wdata := 0.U.asTypeOf(io.tlbwr_wdata)
    when(io.tlbwr_commit | io.tlbfill_commit) {
        val wr_entry = Wire(new TLBEntry)
        wr_entry.asid := asid.ASID
        wr_entry.e    := Mux(estat.Ecode === 0x3f.U, true.B, !tlbidx.NE)
        wr_entry.g    := tlblo0.G && tlblo1.G
        wr_entry.ps   := tlbidx.PS
        wr_entry.vppn := tlbehi.VPPN
        for ((page, tlblo) <- wr_entry.page_table.zip(Seq(tlblo0, tlblo1))) {
            page.d   := tlblo.D
            page.mat := tlblo.MAT
            page.plv := tlblo.PLV
            page.ppn := tlblo.PPN
            page.v   := tlblo.V
        }

        val random_index = stable_cnt(log2Ceil(TLB_NUM) - 1, 0)
        io.tlbwr_wdata.index := Mux(io.tlbwr_commit, tlbidx.Index, random_index)
        io.tlbwr_wdata.wdata := wr_entry
        io.tlbwr_wdata.wen   := true.B
    }

}
