package miku.isa.la32

import chisel3._
import chisel3.util._

import miku._
import miku.isa.CSROpType._
import miku.backend._

class LA32CSRBufferIO extends CSRBufferIO {
    val tlbsrch        = Flipped(new AddrTransChannel)
    val tlbrd          = Flipped(new TLBReadPort(TLB_NUM))
    val tlbrd_commit   = Bool()
    val tlbrd_result   = new TLBEntry
    val tlbwr_commit   = Bool()
    val tlbfill_commit = Bool()
    val invtlb_inter   = new TLBInvalidPort(TLB_NUM)
}

class LA32CSRBuffer extends CSRBuffer {
    // def CSR_ADDR_WD     = 14
    override lazy val csr_io = IO(new LA32CSRBufferIO)

    val rd_data = io.in.bits.operand_c
    val rj_data = io.in.bits.operand_a

    val crmd     = csr_vec.getTargetCSR(LA32CSRRegisters.CRMD)
    val ipe_excp = (crmd.PLV =/= 0.U)

    /*        TLB instructions       */

    val tlbehi = csr_vec.getTargetCSR(LA32CSRRegisters.TLBEHI)
    val tlbidx = csr_vec.getTargetCSR(LA32CSRRegisters.TLBIDX)

    // 1. tlbsrch -- reuse datapath of csrwr
    val tlbsrch_en      = io.in.valid && io.in.ready && !inst_excp && !ipe_excp && (io.in.bits.optype === tlbsrch)
    val tlbsrch_ongoing = RegInit(false.B)
    val tlbsrch_found   = csr_io.tlbsrch.resp.tlb_resp.found
    val tlbsrch_index   = csr_io.tlbsrch.resp.tlb_resp.index
    csr_io.tlbsrch.req.valid := tlbsrch_en
    csr_io.tlbsrch.req.vaddr := Cat(tlbehi.VPPN, 0.U(13.W))
    when(!tlbsrch_ongoing | (tlbsrch_ongoing & commit_ack)) {
        tlbsrch_ongoing := tlbsrch_en
    }

    // 2. tlbrd
    val tlbrd_en       = io.in.valid && io.in.ready && !inst_excp && !ipe_excp && (io.in.bits.optype === tlbrd)
    val tlbrd_ongoing  = RegInit(false.B)
    val tlbrd_result_r = RegEnable(csr_io.tlbrd.rdata, tlbrd_en)
    csr_io.tlbrd.index  := tlbidx.Index
    csr_io.tlbrd_commit := commit_ack & tlbrd_ongoing
    csr_io.tlbrd_result := tlbrd_result_r
    when(!tlbrd_ongoing | (tlbrd_ongoing & commit_ack)) {
        tlbrd_ongoing := tlbrd_en
    }

    // 3. tlbwr
    val tlbwr_en      = io.in.valid && io.in.ready && !inst_excp && !ipe_excp && (io.in.bits.optype === tlbwr)
    val tlbwr_ongoing = RegInit(false.B)
    csr_io.tlbwr_commit := commit_ack & tlbwr_ongoing
    when(!tlbwr_ongoing | (tlbwr_ongoing & commit_ack)) {
        tlbwr_ongoing := tlbwr_en
    }

    // 4. tlbfill
    val tlbfill_en      = io.in.valid && io.in.ready && !inst_excp && !ipe_excp && (io.in.bits.optype === tlbfill)
    val tlbfill_ongoing = RegInit(false.B)
    csr_io.tlbfill_commit := commit_ack & tlbfill_ongoing
    when(!tlbfill_ongoing | (tlbfill_ongoing & commit_ack)) {
        tlbfill_ongoing := tlbfill_en
    }

    // 5. invtlb

    val invtlb_en         = io.in.valid && io.in.ready && !inst_excp && !ipe_excp && (io.in.bits.optype === invtlb)
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
    io_tlb_busy_stall := (tlbwr_ongoing | tlbfill_ongoing | invtlb_ongoing) && (crmd.PG & !crmd.DA)

    csr_addr := MuxCase(
        io.in.bits.operand_b(CSR_ADDR_WD - 1, 0),
        Seq(
            tlbsrch_en -> 0x10.U // tlbidx
        )
    )

    val wmask      = rj_data
    val xchg_wdata = VecInit(VecInit(csr_rdata.asBools).zipWithIndex.map {
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

    // csr write logic
    csr_wdata  := MuxLookup(io.in.bits.optype, DEBUG_MAGICNUM.U)(
        Seq(
            csrwr   -> rd_data,
            csrxchg -> xchg_wdata
        )
    )
    csr_wvalid := !inst_excp && !ipe_excp && MuxLookup(io.in.bits.optype, false.B)(
        Seq(
            csrrd   -> false.B,
            csrwr   -> true.B,
            csrxchg -> true.B,
            tlbsrch -> true.B
        )
    )

    csr_io.write_io.wdata := Mux(!tlbsrch_ongoing, csr_wdata_r, tlbsrch_wdata.rdata)

    // exception check
    csr_excp := MuxCase(
        io.in.bits.exception,
        Seq(
            ipe_excp          -> LA32ExceptionDefns.IPE.enum_no,
            invtlb_op_invalid -> LA32ExceptionDefns.INE.enum_no
        )
    )

    val csr_busy_seq = Seq(csr_wvalid_r, tlbrd_ongoing, tlbwr_ongoing, tlbfill_ongoing, invtlb_ongoing)
    csr_busy := csr_busy_seq.reduce(_ || _)
    assert(!csr_busy_seq.reduce(_ & _)) // there must be only one operation that will wirte csr or tlb in a time
    when(io.flush.ertn | io.flush.exception) {
        csr_busy_seq.foreach(v => v := false.B)
    }
}
