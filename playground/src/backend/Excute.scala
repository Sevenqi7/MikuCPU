package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._

class BaseFuInput extends MkBundle {
    val id        = UInt(TRANS_ID_BITS.W)
    val pc        = UInt(VADDR_WIDTH.W)
    val flush     = Bool()
    val optype    = FuOpType()
    val operand_a = UInt(WORD_WIDTH.W) // rj or pc
    val operand_b = UInt(WORD_WIDTH.W) // rk or imms
    val operand_c = UInt(WORD_WIDTH.W) // rd for branch and store insts or src3 for some floating insts
}

class BaseFuOutput extends MkBundle {
    val id        = UInt(TRANS_ID_BITS.W)
    val result    = UInt(WORD_WIDTH.W)
    val exception = Bool()
    val mispred   = Bool()
}

class WriteBackResult extends BaseFuOutput {}

abstract class BaseFunctionUnit extends MkModule {
    lazy val io = IO(new Bundle {
        val in  = Flipped(Decoupled(new BaseFuInput))
        val out = Decoupled(new BaseFuOutput)
    })
}

// Do nothing
class FakeFunctionUnit extends BaseFunctionUnit {
    io.out.bits.id        := io.in.bits.id
    io.out.bits.exception := false.B
    io.out.bits.result    := DEBUG_MAGICNUM.U
    io.out.valid          := io.in.valid
    io.out.bits.mispred   := false.B
    io.in.ready           := true.B
}

class EXUIO extends MkBundle {
    val in         = Flipped(Decoupled(new BaseFuInput))
    val out        = new Bundle {
        val flu_out = Decoupled(new BaseFuOutput)
        val lsu_out = Decoupled(new BaseFuOutput)
    }
    val futype     = Input(FuType())
    val pred_check = new BranchUnitIO
    val lsu_io     = new LSUIO
}

class EXU extends MkModule {
    val io = IO(new EXUIO)

    val alu  = Module(new MkALU)
    val lsu  = Module(new LSU)
    val mul  = Module(new FakeMultiplier)
    val bru  = Module(new BranchUnit)
    val none = Module(new FakeFunctionUnit)

    val function_units = Seq(
        FuType.bru  -> bru,
        FuType.alu  -> alu,
        FuType.mul  -> mul,
        FuType.lsu  -> lsu,
        FuType.none -> none
    )

    val fixed_latency_units = Seq(
        FuType.bru  -> bru,
        FuType.alu  -> alu,
        FuType.mul  -> mul,
        FuType.none -> none
    )

    val fu_base_in = RegInit(0.U.asTypeOf(ValidIO(new BaseFuInput)))
    val futype_r   = RegNext(io.futype)

    fu_base_in.bits  := io.in.bits
    fu_base_in.valid := io.in.valid

    io.in.ready                             := false.B // default
    function_units.foreach(_._2.io.in.valid := false.B)
    function_units.foreach(_._2.io.in.bits  := fu_base_in.bits)
    for (fu <- function_units) {
        when(futype_r === fu._1) {
            fu._2.io.in.valid := fu_base_in.valid
            io.in.ready       := fu._2.io.in.ready
        }
    }

    // result MUX from fixed latency function unit
    // alu, bru complete operation within 1 cycle, so they two don't need
    // a buffer to store write-back result since there is only 1 write-back port
    // and 1 issue port.
    val result_arb = Module(new Arbiter(new BaseFuOutput, fixed_latency_units.length))
    for ((arb_i, fu_o) <- result_arb.io.in.zip(fixed_latency_units.map(_._2.io.out))) {
        arb_i <> fu_o
    }
    io.pred_check <> bru.bru_io
    io.out.flu_out <> result_arb.io.out
    io.out.lsu_out <> lsu.io.out

    io.lsu_io <> lsu.lsu_io
}
