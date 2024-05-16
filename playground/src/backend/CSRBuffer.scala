package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.isa.la32._
import miku.isa.CSROpType._
import miku.utils.ReadyValidBundle
import miku.issue.RegfileReadIO
import miku.issue.RegfileWriteIO
import miku.utils.DelayN

class CSRBufferIO extends MkBundle {
    val csr_commit = Flipped(new ReadyValidBundle)
    val read_io    = Flipped(new RegfileReadIO(CSR_ADDR_WD, 32))
    val write_io   = Flipped(new RegfileWriteIO(CSR_ADDR_WD, 32))
}

// Access unit for CSR
abstract class CSRBuffer extends BaseFunctionUnit {
    lazy val csr_io = IO(new CSRBufferIO)

    val csr_vec           = io.csr_vec
    // inform LSU that TLB is currently being accessed and modified by CSRBuffer(tlbwr, tlbfill or invtlb)
    val io_tlb_busy_stall = IO(Output(Bool()))
    val commit_ack        = csr_io.csr_commit.valid & csr_io.csr_commit.ready

    val inst_excp = (io.in.bits.exception =/= ArchExceptionType.NONE.enum_no)

    val csr_addr   = Wire(UInt(CSR_ADDR_WD.W))
    val csr_addr_r = RegEnable(csr_addr, io.in.valid & io.in.ready)

    // csr read logic
    val csr_wr_bypass = csr_io.write_io.wen && (csr_io.write_io.waddr === csr_io.read_io.raddr)
    val csr_rdata     = Mux(!csr_wr_bypass, csr_io.read_io.rdata, csr_io.write_io.wdata)
    csr_io.read_io.raddr := csr_addr

    // csr write logic
    val csr_wdata_r  = RegInit(0.U(WORD_WIDTH.W))
    val csr_wvalid_r = RegInit(false.B)

    val csr_wdata  = Wire(UInt(WORD_WIDTH.W))
    val csr_wvalid = Wire(Bool())

    when(io.in.valid & io.in.ready) {
        csr_wdata_r  := csr_wdata
        csr_wvalid_r := csr_wvalid
    }.elsewhen(commit_ack) {
        csr_wvalid_r := false.B
    }

    csr_io.write_io.waddr := csr_addr_r
    csr_io.write_io.wen   := csr_wvalid_r & commit_ack
    csr_io.write_io.wdata := csr_wdata_r

    // exception check
    val csr_excp = Wire(ArchExceptionType())

    io.out.bits.id        := io.in.bits.id
    io.out.bits.mispred   := false.B
    io.out.bits.exception := csr_excp
    io.out.bits.result    := csr_rdata
    io.out.valid          := io.in.valid

    val csr_busy = Wire(Bool()) // stall CSR Buffer when current instrcution is under execute

    // flush
    when(io.flush.ertn | io.flush.exception) {
        csr_wvalid_r := false.B
    }

    csr_io.csr_commit.ready := true.B
    io.in.ready             := !csr_busy || (csr_busy && csr_io.csr_commit.valid && csr_io.csr_commit.ready)
}
