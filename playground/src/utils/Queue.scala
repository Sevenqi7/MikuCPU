package miku.utils

import chisel3._
import chisel3.util._

import miku._
import miku.frontend._
import miku.utils.util.uintToBitPat
import miku.frontend.LA32Instructions._
class CircularQueueInput[T <: Data](data: T) extends Bundle {
    val clear     = Bool()
    val enq_data  = UInt((data.getWidth).W)
    val enq_valid = Bool()
    val deq_valid = Bool()
}

class CircularQueueOutput[T <: Data](data: T) extends Bundle {
    val front_data = UInt((data.getWidth).W)
    val empty      = Bool()
}

// ? is a "full" signal needed?
class CircularQueue[T <: Data](element: T, size: Int) extends Module {
    val io = IO(new Bundle {
        val in  = Input(new CircularQueueInput(element))
        val out = Output(new CircularQueueOutput(element))
    })

    def enqData(data: T): Unit = {
        io.in.enq_valid := true.B
        io.in.enq_data  := data.asUInt
    }

    def enqData(data: T, cond: Bool): Unit = { //TODO: need a better name
        io.in.enq_valid := cond
        io.in.enq_data  := data.asUInt
    }

    def deqData: T = {
        io.in.deq_valid := true.B
        io.out.front_data.asTypeOf(element)
    }

    def deqData(cond: Bool): T = {  //TODO: need a better name
        io.in.deq_valid := true.B
        io.out.front_data.asTypeOf(element)
    }
    val queue = RegInit(VecInit.fill(size)(0.U.asTypeOf(ValidIO(element))))

    val rear           = RegInit(0.U(log2Ceil(size).W)) // point to the end of queue
    val front          = RegInit(0.U(log2Ceil(size).W))
    val rear_plus_one  = rear + 1.U
    val front_plus_one = front + 1.U

    io.out.empty      := (rear === front)
    io.out.front_data := queue(front).bits.asUInt
    when(io.in.clear) {
        for (i <- 0 until size) {
            queue(i).valid := false.B
        }
    }.otherwise {
        when(io.in.enq_valid) {
            queue(rear).bits  := io.in.enq_data.asTypeOf(element)
            queue(rear).valid := true.B
            rear              := Mux(rear === 0.U, (size - 1).U, rear_plus_one)
        }
        when(io.in.deq_valid) {
            queue(front).valid := false.B
            front              := Mux(front === (size - 1).U, 0.U, front_plus_one)
        }
    }
}
