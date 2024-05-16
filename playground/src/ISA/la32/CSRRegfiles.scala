package miku.isa.la32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.backend._
import miku.utils.UEXT
import LA32CSRRegisters._
import LA32ExceptionDefns._
import chisel3.util.random.LFSR

class LA32CSRRegfilesIO extends CSRRegfilesIO {
    val tlbrd_commit   = Input(Bool())
    val tlbwr_commit   = Input(Bool())
    val tlbfill_commit = Input(Bool())
    val ll_commit      = Input(Bool())
    val sc_commit      = Input(Bool())
    val tlbwr_wdata    = new TLBWritePort(TLB_NUM)
    val tlbrd_result   = Input(new TLBEntry)
}

class LA32CSRRegfiles extends CSRRegfiles {
    override lazy val io = IO(new LA32CSRRegfilesIO)

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
        val badv_from_pc = Seq(LA32ExceptionDefns.ADEF, LA32ExceptionDefns.PIF)
            .map(_.enum_no === io.excp_commit.bits.extype).reduce(_ || _)

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
            val vaddr = Mux(badv_from_pc, io.excp_commit.bits.pc, io.excp_commit.bits.mem_addr)
            badv.write(vaddr)
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

    // TLB-related CSR
    val tlbehi = csr_table(TLBEHI)
    val tlblo0 = csr_table(TLBELO0)
    val tlblo1 = csr_table(TLBELO1)
    val tlbidx = csr_table(TLBIDX)
    val asid   = csr_table(ASID)

    val excp_tlb = io.excp_commit.valid && MuxLookup(io.excp_commit.bits.extype, false.B)(
        Seq(
            LA32ExceptionDefns.TLBR.enum_no -> true.B,
            LA32ExceptionDefns.PIL.enum_no  -> true.B,
            LA32ExceptionDefns.PIS.enum_no  -> true.B,
            LA32ExceptionDefns.PPI.enum_no  -> true.B,
            LA32ExceptionDefns.PME.enum_no  -> true.B,
            LA32ExceptionDefns.PIF.enum_no  -> true.B
        )
    )

    // TLB-related exception
    when(excp_tlb) {
        tlbehi.write(io.excp_commit.bits.mem_addr)
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
