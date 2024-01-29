package miku.frontend

import chisel3._
import chisel3.util._
import chisel3.util.experimental.decode._

import miku._
import miku.utils._
import miku.frontend._
import miku.issue.IssueEntry

class IDUIO extends MkBundle {
    val ifu_s1     = Flipped(ValidIO(new PCInstBundle(VADDR_WIDTH, INST_BITS)))
    val pred_check = Flipped(new BranchPredictorUpdate())
    val exception  = Input(Bool())
    val to_issue   = ValidIO(new IssueEntry()) // TODO: need a better name
}

class IDU extends MkModule {
    val io = IO(new IDUIO)

    val inst_queue = Module(new CircularQueue(new PCInstBundle(VADDR_WIDTH, INST_BITS), INST_QUEUE_SIZE))
    inst_queue.io.in.clear := io.pred_check.redirect | io.exception
    inst_queue.enqData(io.ifu_s1.bits, io.ifu_s1.valid)
    inst_queue.deqData(true.B) // TODO: replace this with a ready signal from issue stage

    val decoder = Module(new LA32DecoderUnit)
    decoder.raw_inst := inst_queue.io.out.front_data

    val issue_entry_r = RegInit(0.U.asTypeOf(new IssueEntry)) // TODO: need a better name
    issue_entry_r.decoded_inst := decoder.decoded_inst
    issue_entry_r.inst         := io.ifu_s1.bits.inst
    issue_entry_r.pc           := io.ifu_s1.bits.pc

    io.to_issue.bits  := issue_entry_r
    io.to_issue.valid := true.B // TODO: need condition
}
