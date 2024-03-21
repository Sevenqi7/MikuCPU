package miku.frontend

import chisel3._
import chisel3.util._
import chisel3.util.experimental.decode._

import miku._
import miku.utils._
import miku.frontend._
import miku.issue.IssueEntry

class IDUIO extends MkBundle {
    val ifu_s1          = Flipped(ValidIO(new PCInstBundle(VADDR_WIDTH, INST_BITS)))
    val inst_queue_full = Output(Bool())
    val pred_check      = Flipped(ValidIO(new BranchPredictorUpdate()))
    val exception       = Input(Bool())
    val to_issue        = Decoupled(new IssueEntry()) // TODO: need a better name
}

class IDU extends MkModule {
    val io = IO(new IDUIO)

    val inst_queue = Module(new CircularQueue(new PCInstBundle(VADDR_WIDTH, INST_BITS), INST_QUEUE_SIZE))
    val mispred    = (io.pred_check.bits.redirect & io.pred_check.valid)
    inst_queue.io.in.clear := mispred | io.exception
    inst_queue.enqData(io.ifu_s1.bits, io.ifu_s1.valid)
    inst_queue.deqData(
        io.to_issue.ready & !inst_queue.io.out.empty
    ) // TODO: replace this with a ready signal from issue stage

    val decoder = Module(new LA32DecoderUnit)
    decoder.io.raw_inst := inst_queue.io.out.front_data.inst

    val issue_entry_r = RegInit(0.U.asTypeOf(ValidIO(new IssueEntry))) // TODO: need a better name
    when(mispred) {
        issue_entry_r := 0.U.asTypeOf(ValidIO(new IssueEntry))
    }.elsewhen(io.to_issue.ready) {
        issue_entry_r.bits.decoded_inst := decoder.io.decoded_inst
        issue_entry_r.bits.inst         := inst_queue.io.out.front_data.inst
        issue_entry_r.bits.pc           := inst_queue.io.out.front_data.pc
        issue_entry_r.valid             := !inst_queue.io.out.empty
    }

    io.to_issue.bits   := issue_entry_r.bits
    io.to_issue.valid  := issue_entry_r.valid & !mispred
    io.inst_queue_full := inst_queue.io.out.full
}
