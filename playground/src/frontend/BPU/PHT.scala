package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class MkBHT(implicit btb: MkBTB) extends BTBBasedPredictor {
    val nrBHTs = 1024
    val bht = RegInit(VecInit(Seq.fill(nrBHTs)("b10".U(2.W))))

    def updateSaturateCnt(addr: UInt, taken: Bool): Unit = {
        val pre_val = bht(addr)
        when(taken) {
            when(pre_val < "b11".U) {
                pre_val := pre_val + 1.U
            }
        }.otherwise {
            when(pre_val > "b00".U) {
                pre_val := pre_val - 1.U
            }
        }
    }

    io.resp.taken := bht(io.s1.bits.pc(11, 2))(1)

    when(io.update.valid) {
        val update_pc = io.update.bits.pc
        updateSaturateCnt(update_pc(11, 2), io.update.bits.is_taken)
    }
}
