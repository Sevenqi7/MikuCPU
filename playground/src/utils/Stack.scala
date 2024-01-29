package miku.utils

import chisel3._
import chisel3.util._

class StackInput[T <: Data](element: T) extends Bundle {
    val op      = Bool() // 0:push 1:pop
    val data_in = UInt(element.getWidth.W)
    val clear   = Bool()
    val valid   = Bool()

}

class StackOutput[T <: Data](element: T) extends Bundle {
    val top_data = UInt(element.getWidth.W)
    val empty    = Bool()
}

class Stack[T <: Data](element: T, size: Int) extends Module {
    val io = IO(new Bundle {
        val in  = Flipped(new StackInput(element))
        val out = new StackOutput(element)
    })

    def pushData(element: T): Unit = {
        io.in.op      := 0.B
        io.in.valid   := true.B
        io.in.data_in := element
    }

    def popData: T = {
        io.in.op    := 1.B
        io.in.valid := true.B
        io.out.top_data.asTypeOf(element)
    }

    val stack         = RegInit(VecInit(Seq.fill(size)(0.U.asTypeOf(ValidIO(element)))))
    val top           = RegInit(log2Ceil(size).U)
    val top_plus_one  = top + 1.U
    val top_minus_one = top - 1.U

    io.out.empty    := stack.forall(!_.valid)
    io.out.top_data := stack(top).asTypeOf(element)

    when(io.in.valid) {
        when(!io.in.op) {
            stack(top).bits  := io.in.data_in
            stack(top).valid := true.B
            top              := Mux(top === (size - 1).U, 0.U, top_plus_one)
        }.otherwise {
            stack(top).valid := false.B
            top              := Mux(top === 0.U, (size - 1).U, top_minus_one)
        }
    }
}
