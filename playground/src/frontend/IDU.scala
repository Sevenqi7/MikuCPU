package miku.frontend

import chisel3._
import chisel3.util._
import chisel3.util.experimental.decode._

import miku._
import miku.utils._
import miku.frontend._
import miku.issue.IssueEntry

class FlushReason extends MkBundle {
    val mispred   = Bool()
    val exception = Bool()
    val ertn      = Bool()
}

class IDUIO extends MkBundle {
    val ifu_s1           = Flipped(ValidIO(new InstQueueEntry))
    val inst_queue_full  = Output(Bool())
    val inst_queue_flush = Flipped(new FlushReason)
    val to_issue         = Decoupled(new IssueEntry) // TODO: need a better name
}

class InstQueueEntry extends MkBundle {
    val pc        = UInt(VADDR_WIDTH.W)
    val inst      = UInt(INST_BITS.W)
    val excp_adef = Bool()
}

class IDU extends MkModule {
    val io = IO(new IDUIO)

    val inst_queue  = Module(new CircularQueue(new InstQueueEntry, INST_QUEUE_SIZE))
    val flush_valid = io.inst_queue_flush.asUInt.asBools.reduce(_ || _)
    inst_queue.io.in.clear := flush_valid
    inst_queue.enqData(io.ifu_s1.bits, io.ifu_s1.valid)
    inst_queue.deqData(
        io.to_issue.ready & !inst_queue.io.out.empty
    ) // TODO: replace this with a ready signal from issue stage

    val decoder = Module(new LA32DecoderUnit)
    decoder.io.raw_inst := inst_queue.io.out.front_data.inst

    val issue_entry_r = RegInit(0.U.asTypeOf(ValidIO(new IssueEntry))) // TODO: need a better name
    when(flush_valid) {
        issue_entry_r := 0.U.asTypeOf(ValidIO(new IssueEntry))
    }.elsewhen(io.to_issue.ready) {
        import LA32ExceptionType._
        issue_entry_r.bits.decoded_inst := decoder.io.decoded_inst
        issue_entry_r.bits.inst         := inst_queue.io.out.front_data.inst
        issue_entry_r.bits.pc           := inst_queue.io.out.front_data.pc
        issue_entry_r.bits.exception    := MuxCase(
            NONE.enum_no,
            Seq(
                inst_queue.io.out.front_data.excp_adef -> ADEF.enum_no
            )
        )
        issue_entry_r.valid             := !inst_queue.io.out.empty
    }

    io.to_issue.bits   := issue_entry_r.bits
    io.to_issue.valid  := issue_entry_r.valid & !flush_valid
    io.inst_queue_full := inst_queue.io.out.full
}
