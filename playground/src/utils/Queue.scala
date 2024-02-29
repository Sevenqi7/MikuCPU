package miku.utils

import chisel3._
import chisel3.util._

import miku._
import miku.frontend._
import miku.LA32Instructions._
import miku.utils.util.uintToBitPat
class CircularQueueInput[T <: Data](datatype: T) extends Bundle {
    val clear     = Bool()
    // port direction need to be stated, otherwise a "unable to clone" error will occur
    val enq_data  = Input(datatype)
    val enq_valid = Bool()
    val deq_valid = Bool()
}

class CircularQueueOutput[T <: Data](datatype: T) extends Bundle {
    // port direction need to be stated, otherwise a "unable to clone" error will occur
    val front_data = Output(datatype)
    val empty      = Bool()
    val full       = Bool()
}

class CircularQueue[T <: Data](element: T, size: Int, enable_contents_output: Boolean = false) extends Module {
    val io = IO(new Bundle {
        val in  = Input(new CircularQueueInput(element))
        val out = Output(new CircularQueueOutput(element) {
            val element_vec = if (enable_contents_output) Some(Vec(size, ValidIO(element))) else None
        })
    })

    def enqData(data: T): Unit = {
        io.in.enq_valid := true.B
        io.in.enq_data  := data
    }

    def enqData(data: T, cond: Bool): Unit = { // TODO: need a better name
        io.in.enq_valid := cond
        io.in.enq_data  := data
    }

    def deqData: T = {
        io.in.deq_valid := true.B
        io.out.front_data
    }

    def deqData(cond: Bool): T = { // TODO: need a better name
        io.in.deq_valid := cond
        io.out.front_data
    }
    val queue = RegInit(VecInit.fill(size)(0.U.asTypeOf(ValidIO(element))))
    if (enable_contents_output) {
        io.out.element_vec.get := queue
    }

    val rear           = RegInit(0.U(log2Ceil(size).W)) // point to the end of queue
    val front          = RegInit(0.U(log2Ceil(size).W))
    val rear_plus_one  = rear + 1.U
    val front_plus_one = front + 1.U

    io.out.full       := queue.map(q => q.valid).reduce(_ & _)
    io.out.empty      := !queue.map(q => q.valid).reduce(_ || _)
    io.out.front_data := queue(front).bits

    when(io.in.clear) {
        for (i <- 0 until size) {
            queue(i).valid := false.B
        }
    }.otherwise {
        when(io.in.enq_valid) {
            queue(rear).bits  := io.in.enq_data.asTypeOf(element)
            queue(rear).valid := true.B
            rear              := Mux(rear === (size - 1).U, 0.U, rear_plus_one)
        }
        when(io.in.deq_valid) {
            queue(front).valid := false.B
            front              := Mux(front === (size - 1).U, 0.U, front_plus_one)
        }
    }
}
