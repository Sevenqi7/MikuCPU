package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.CSROpType._
import miku.utils.ReadyValidBundle
import miku.issue.RegfileReadIO
import miku.issue.RegfileWriteIO

class CSRBufferIO extends MkBundle {
    val csr_commit = Flipped(new ReadyValidBundle)
    val read_io    = Flipped(new LA32CSRReadIO)
    val write_io   = Flipped(new LA32CSRWriteIO)
}

// Access unit for CSR
class CSRBuffer extends BaseFunctionUnit {
    val csr_io = IO(new CSRBufferIO)

    val rd_data = io.in.bits.operand_c
    val rj_data = io.in.bits.operand_a

    val csr_addr   = io.in.bits.operand_b(13, 0)
    val csr_addr_r = RegEnable(csr_addr, io.in.valid & io.in.ready)
    val wmask      = rj_data

    // read logic
    val csr_rdata = csr_io.read_io.rdata
    csr_io.read_io.raddr := csr_addr

    // write logic
    val csr_wdata_r  = RegInit(0.U(WORD_WIDTH.W))
    val csr_wvalid_r = RegInit(false.B)
    val xchg_wdata   = VecInit(VecInit(csr_rdata.asBools).zipWithIndex.map {
        case (bit, i) => {
            when(wmask(i)) {
                bit := rd_data(i)
            }
            bit
        }
    }).asUInt

    csr_wdata_r  := MuxLookup(io.in.bits.optype, DEBUG_MAGICNUM.U)(
        Seq(
            csrwr   -> rd_data,
            csrxchg -> xchg_wdata
        )
    )
    csr_wvalid_r := io.in.valid && MuxLookup(io.in.bits.optype, false.B)(
        Seq(
            csrrd   -> false.B,
            csrwr   -> true.B,
            csrxchg -> true.B
        )
    )

    csr_io.write_io.waddr := csr_addr_r
    csr_io.write_io.wen   := csr_wvalid_r & csr_io.csr_commit.valid
    csr_io.write_io.wdata := csr_wdata_r

    io.out.bits.id        := io.in.bits.id
    io.out.bits.mispred   := false.B
    io.out.bits.exception := false.B
    io.out.bits.result    := csr_rdata
    io.out.valid          := io.in.valid

    csr_io.csr_commit.ready := true.B
    io.in.ready             := !csr_wvalid_r || (csr_wvalid_r && csr_io.csr_commit.valid && csr_io.csr_commit.ready)
}
