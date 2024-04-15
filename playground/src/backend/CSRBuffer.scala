package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.CSROpType._
import miku.utils.ReadyValidBundle
import miku.issue.RegfileReadIO
import miku.issue.RegfileWriteIO
import miku.utils.DelayN

class CSRBufferIO extends MkBundle {
    val csr_commit     = Flipped(new ReadyValidBundle)
    val read_io        = Flipped(new LA32CSRReadIO)
    val write_io       = Flipped(new LA32CSRWriteIO)
    val tlbsrch        = Flipped(new AddrTransChannel)
    val tlbrd          = Flipped(new TLBReadPort(TLB_NUM))
    val tlbrd_commit   = Bool()
    val tlbrd_result   = new TLBEntry
    val tlbwr_commit   = Bool()
    val tlbfill_commit = Bool()
    val from_csr       = Flipped(new Bundle {
        val asid   = new LA32CSR_Asid
        val tlbehi = new LA32CSR_Tlbehi
        val tlbidx = new LA32CSR_Tlbidx(log2Ceil(TLB_NUM))
    })
    val invtlb_inter   = new TLBInvalidPort(TLB_NUM)
}

// Access unit for CSR
class CSRBuffer extends BaseFunctionUnit {
    val csr_io = IO(new CSRBufferIO)

    val inst_excp = io.in.bits.exception =/= LA32ExceptionType.NONE.enum_no

    /*        TLB instructions       */

    val tlbehi     = csr_io.from_csr.tlbehi
    val tlbidx     = csr_io.from_csr.tlbidx
    val commit_ack = csr_io.csr_commit.valid & csr_io.csr_commit.ready

    // 1. tlbsrch -- reuse datapath of csrwr
    val tlbsrch_en      = io.in.valid && io.in.ready && !inst_excp && (io.in.bits.optype === tlbsrch)
    val tlbsrch_ongoing = RegInit(false.B)
    val tlbsrch_found   = csr_io.tlbsrch.tlb_resp.found
    val tlbsrch_index   = csr_io.tlbsrch.tlb_resp.index
    csr_io.tlbsrch.valid      := tlbsrch_en
    csr_io.tlbsrch.vaddr      := Cat(tlbehi.VPPN, 0.U(13.W))
    csr_io.tlbsrch.tlbsrch_en := tlbsrch_en
    when(!tlbsrch_ongoing | (tlbsrch_ongoing & commit_ack)) {
        tlbsrch_ongoing := tlbsrch_en
    }

    // 2. tlbrd
    val tlbrd_en       = io.in.valid && io.in.ready && !inst_excp && (io.in.bits.optype === tlbrd)
    val tlbrd_ongoing  = RegInit(false.B)
    val tlbrd_result_r = RegEnable(csr_io.tlbrd.rdata, tlbrd_en)
    csr_io.tlbrd.index  := tlbidx.Index
    csr_io.tlbrd_commit := commit_ack & tlbrd_ongoing
    csr_io.tlbrd_result := tlbrd_result_r
    when(!tlbrd_ongoing | (tlbrd_ongoing & commit_ack)) {
        tlbrd_ongoing := tlbrd_en
    }

    // 3. tlbwr
    val tlbwr_en      = io.in.valid && io.in.ready && !inst_excp && (io.in.bits.optype === tlbwr)
    val tlbwr_ongoing = RegInit(false.B)
    csr_io.tlbwr_commit := commit_ack & tlbwr_ongoing
    when(!tlbwr_ongoing | (tlbwr_ongoing & commit_ack)) {
        tlbwr_ongoing := tlbwr_en
    }

    // 4. tlbfill
    val tlbfill_en      = io.in.valid && io.in.ready && !inst_excp && (io.in.bits.optype === tlbfill)
    val tlbfill_ongoing = RegInit(false.B)
    csr_io.tlbfill_commit := commit_ack & tlbfill_ongoing
    when(!tlbfill_ongoing | (tlbfill_ongoing & commit_ack)) {
        tlbfill_ongoing := tlbfill_en
    }

    // 5. invtlb

    val invtlb_en         = io.in.valid && io.in.ready && !inst_excp && (io.in.bits.optype === CSROpType.invtlb)
    val invtlb_op         = RegEnable(io.in.bits.operand_c(4, 0), invtlb_en)
    val invtlb_asid       = RegEnable(io.in.bits.operand_a(9, 0), invtlb_en)                // rj(9, 0)
    val invtlb_vaddr      = RegEnable(io.in.bits.operand_b(VADDR_WIDTH - 1, 13), invtlb_en) // rk
    val invtlb_op_invalid = invtlb_en && (io.in.bits.operand_c(4, 0) > 6.U)
    val invtlb_ongoing    = RegInit(false.B)
    csr_io.invtlb_inter.valid := invtlb_ongoing & commit_ack
    csr_io.invtlb_inter.op    := invtlb_op
    csr_io.invtlb_inter.vppn  := invtlb_vaddr
    csr_io.invtlb_inter.asid  := invtlb_asid
    when(!invtlb_ongoing | (invtlb_ongoing & commit_ack)) {
        invtlb_ongoing := invtlb_en & !invtlb_op_invalid
    }

    /*      TLB instructions end    */

    val rd_data    = io.in.bits.operand_c
    val rj_data    = io.in.bits.operand_a
    val csr_addr   = MuxCase(
        io.in.bits.operand_b(13, 0),
        Seq(
            tlbsrch_en -> 0x10.U // tlbidx
        )
    )
    val csr_addr_r = RegEnable(csr_addr, io.in.valid & io.in.ready)
    val wmask      = rj_data

    // csr read logic
    val csr_rdata = csr_io.read_io.rdata
    csr_io.read_io.raddr := csr_addr

    // csr write logic
    val csr_wdata_r   = RegInit(0.U(WORD_WIDTH.W))
    val csr_wvalid_r  = RegInit(false.B)
    val xchg_wdata    = VecInit(VecInit(csr_rdata.asBools).zipWithIndex.map {
        case (bit, i) => {
            when(wmask(i)) {
                bit := rd_data(i)
            }
            bit
        }
    }).asUInt
    val tlbsrch_wdata = WireInit(tlbidx)
    when(tlbsrch_found) {
        tlbsrch_wdata.Index := tlbsrch_index
        tlbsrch_wdata.NE    := 0.B
    }.otherwise {
        tlbsrch_wdata.NE := 1.B
    }

    csr_wdata_r  := MuxLookup(io.in.bits.optype, DEBUG_MAGICNUM.U)(
        Seq(
            csrwr   -> rd_data,
            csrxchg -> xchg_wdata
        )
    )
    csr_wvalid_r := io.in.valid && io.in.ready && !inst_excp && MuxLookup(io.in.bits.optype, false.B)(
        Seq(
            csrrd   -> false.B,
            csrwr   -> true.B,
            csrxchg -> true.B,
            tlbsrch -> true.B
        )
    )

    csr_io.write_io.waddr := csr_addr_r
    csr_io.write_io.wen   := csr_wvalid_r & commit_ack
    csr_io.write_io.wdata := Mux(!tlbsrch_ongoing, csr_wdata_r, tlbsrch_wdata.rdata)

    io.out.bits.id        := io.in.bits.id
    io.out.bits.mispred   := false.B
    io.out.bits.exception := Mux(!invtlb_op_invalid, io.in.bits.exception, LA32ExceptionType.INE.enum_no)
    io.out.bits.result    := csr_rdata
    io.out.valid          := io.in.valid

    val csr_busy_seq = Seq(csr_wvalid_r, tlbrd_ongoing, tlbwr_ongoing, tlbfill_ongoing, invtlb_ongoing)
    val csr_busy     = csr_busy_seq.reduce(_ || _)
    assert(!csr_busy_seq.reduce(_ & _)) // there must be only one operation that will wirte csr or tlb in a time

    csr_io.csr_commit.ready := true.B
    io.in.ready             := !csr_busy || (csr_busy && csr_io.csr_commit.valid && csr_io.csr_commit.ready)
}
