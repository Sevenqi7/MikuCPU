package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._

class BaseFuInput extends MkBundle {
    val id        = UInt(TRANS_ID_BITS.W)
    val pc        = UInt(VADDR_WIDTH.W)
    val optype    = FuOpType()
    val exception = LA32ExceptionType()
    val operand_a = UInt(WORD_WIDTH.W) // rj or pc
    val operand_b = UInt(WORD_WIDTH.W) // rk or imms
    val operand_c = UInt(WORD_WIDTH.W) // rd for branch and store insts or src3 for some insts
}

class BaseFuOutput extends MkBundle {
    val id        = UInt(TRANS_ID_BITS.W)
    val result    = UInt(WORD_WIDTH.W)
    val exception = LA32ExceptionType()
    val mispred   = Bool()
}

class WriteBackResult extends BaseFuOutput {}

abstract class BaseFunctionUnit extends MkModule {
    lazy val io = IO(new Bundle {
        val in    = Flipped(Decoupled(new BaseFuInput))
        val out   = Decoupled(new BaseFuOutput)
        val flush = Flipped(new FlushReason)
    })
}

class EXUIO extends MkBundle {
    val in         = Flipped(Decoupled(new BaseFuInput))
    val out        = new Bundle {
        val flu_out = Decoupled(new BaseFuOutput)
        val lsu_out = Decoupled(new BaseFuOutput)
    }
    val futype     = Input(FuType())
    val flush      = Flipped(new FlushReason)
    val pred_check = new BranchUnitIO
    val lsu_io     = new LSUIO
    val csr_io     = new CSRBufferIO
    val misc_io    = new MiscFuIO
}

class EXU extends MkModule {
    val io = IO(new EXUIO)

    val alu  = Module(new MkALU)
    val lsu  = Module(new LSU)
    val mul  = Module(new FakeMultiplier)
    val bru  = Module(new BranchUnit)
    val csr  = Module(new CSRBuffer)
    val misc = Module(new MiscFunctionUnit)

    val function_units = Seq(
        FuType.bru  -> bru,
        FuType.alu  -> alu,
        FuType.mul  -> mul,
        FuType.lsu  -> lsu,
        FuType.csr  -> csr,
        FuType.misc -> misc
    )

    val fixed_latency_units = Seq(
        FuType.bru  -> bru,
        FuType.alu  -> alu,
        FuType.misc -> misc,
        FuType.csr  -> csr,
        FuType.mul  -> mul
    )

    val fu_base_in = RegInit(0.U.asTypeOf(ValidIO(new BaseFuInput)))
    val futype_r   = RegInit(0.U.asTypeOf(FuType()))
    val inst_excp  = (fu_base_in.bits.exception =/= LA32ExceptionType.NONE.enum_no)

    when(io.in.ready) {
        fu_base_in.bits  := io.in.bits
        fu_base_in.valid := io.in.valid
        futype_r         := io.futype
    }

    io.in.ready                             := false.B // default
    function_units.foreach(_._2.io.in.valid := false.B)
    function_units.foreach(_._2.io.in.bits  := fu_base_in.bits)
    for (fu <- function_units) {
        fu._2.io.flush := io.flush
        when(futype_r === fu._1) {
            fu._2.io.in.valid := fu_base_in.valid & !inst_excp
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

    val fu_excp_out = Wire(new BaseFuOutput)
    fu_excp_out           := DontCare
    fu_excp_out.id        := fu_base_in.bits.id
    fu_excp_out.exception := fu_base_in.bits.exception
    fu_excp_out.result    := fu_base_in.bits.pc

    io.out.lsu_out <> lsu.io.out
    when(fu_base_in.valid & inst_excp) {
        io.out.flu_out.valid    := true.B
        io.out.flu_out.bits     := fu_excp_out
        result_arb.io.out.ready := false.B
    }.otherwise {
        io.out.flu_out <> result_arb.io.out
    }

    io.pred_check <> bru.bru_io
    io.lsu_io     <> lsu.lsu_io
    io.csr_io     <> csr.csr_io
    io.misc_io    <> misc.misc_io
}
