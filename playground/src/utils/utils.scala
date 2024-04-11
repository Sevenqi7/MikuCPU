package miku.utils

import chisel3._
import chisel3.util._
import scala.language.implicitConversions
import dataclass.data

object util {
    implicit def uintToBitPat(x: UInt): BitPat = BitPat(x)
}

class ReadyValidBundle extends Bundle {
    val valid = Output(Bool())
    val ready = Input(Bool())
}

class PCInstBundle(pc_width: Int, inst_width: Int) extends Bundle {
    val pc   = UInt(pc_width.W)
    val inst = UInt(inst_width.W)
}

object SEXT {
    def apply(in: Data, width: Int): UInt = {
        val highest = in.asUInt(in.getWidth - 1).asUInt
        Cat(Seq.fill(width - in.getWidth)(highest) :+ in.asUInt)
    }
}

object UEXT {
    def apply(in: Data, width: Int): UInt = {
        val highest = in.asUInt(in.getWidth - 1).asUInt
        Cat(0.U((width - in.getWidth).W), in.asUInt)
    }
}

class DelayN[T <: Data](gen: T, n: Int) extends Module {
    val io  = IO(new Bundle() {
        val in  = Input(gen)
        val out = Output(gen)
    })
    var out = io.in
    for (i <- 0 until n) {
        out = RegNext(out)
    }
    io.out := out
}

object DelayN {
    def apply[T <: Data](in: T, n: Int): T = {
        val delay = Module(new DelayN(in.cloneType, n))
        delay.io.in := in
        delay.io.out
    }
}

object HoldUnless {
    def apply[T <: Data](x: T, en: Bool, init: Option[T] = None): T = {
        val hold_data = if (init.isDefined) RegEnable(x, init.get, en) else RegEnable(x, en)
        Mux(en, x, hold_data)
    }
}

// // class ZeroUInt(width: Int) extends UInt(width) {
// //     override def :=(that: Data): Unit = {
// //         this.:=(0.U)
// //     }
// // }
