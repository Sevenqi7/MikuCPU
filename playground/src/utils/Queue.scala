package miku.utils

import chisel3._
import chisel3.util._

import miku._
import miku.frontend._

class CircularQueueInput[T <: Data](data: T) extends Bundle{
    val op = UInt(2.W)  //op(1): valid, op(0): operation, 0 is enq, 1 is deq
    val enq_data = UInt((data.getWidth).W)
    val clear = Bool()

    def enq_valid = op(1) & !op(0)
    def deq_valid = op(1) & op(0)
}

class CircularQueueOutput[T <: Data](data: T) extends Bundle{
    val top_data = UInt((data.getWidth).W)
    val empty = Bool()
}

class CircularQueue[T <: Data](element: T, size: Int) extends Module{
    val io = IO(new Bundle{
        val in = Input(new CircularQueueInput(element))
        val out = Output(new CircularQueueOutput(element))
    })

    def enqData(data: T): Unit = {
        io.in.op := "b10".U
        io.in.enq_data := data
    }

    def deqData: T = {
        io.in.op := "b11".U
        io.out.top_data.asTypeOf(element)    
    }
    
    val queue = RegInit(VecInit.fill(size)(0.U.asTypeOf(ValidIO(element))))
    val rear = RegInit(0.U(log2Ceil(size).W))       //point to the end of queue
    val rear_plus_one = rear + 1.U
    val rear_minus_one = rear - 1.U

    io.out.empty := !queue.map(q => q.valid).reduce(_ || _)
    io.out.top_data := queue(rear).bits
    
    when(io.in.clear){
        for(i <- 0 until size){
            queue(i).valid := false.B
        }
    }
    .elsewhen(io.in.enq_valid){
        queue(rear).bits := io.in.enq_data
        queue(rear).valid := true.B
        rear := Mux(rear === (size-1).U, 0.U, rear_plus_one)
    }
    .elsewhen(io.in.deq_valid){
        queue(rear).valid := false.B
        rear := Mux(rear === 0.U, (size-1).U, rear_minus_one)
    }
}