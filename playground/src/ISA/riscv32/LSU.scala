package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.isa.LSUOpType._
import miku.utils._
import miku.backend.MkLSU

class RV32LSU extends MkLSU {
    def in_mmio(addr: UInt): Bool = (addr > 0xa0000000L.U)

    val rs1 = io.in.bits.operand_a
    val rs2 = io.in.bits.operand_b

    val imm_I = io.in.bits.operand_b
    val imm_S = io.in.bits.operand_c
    val imm   = Mux(isStoreType(io.in.bits.optype), imm_S, imm_I)
    vaddr := Mux(isAtomType(io.in.bits.optype), rs1, rs1 + imm)
    wdata := rs2

    // RV32A inst
    switch(lstate) {
        is(lIdle) {
            when(io.in.valid & io.in.ready & isAtomType(io.in.bits.optype)) {
                load_buf.id        := io.in.bits.id
                load_buf.addr      := vaddr
                load_buf.ldtype    := LSUOpType.ldw
                load_buf.valid     := true.B
                load_buf.exception := ArchExceptionType.NONE.enum_no
                lstate             := lReq
            }
        }
    }

    val amo_ongoing = RegInit(false.B)
    val amo_rs2     = RegInit(0.U(WORD_WIDTH.W))
    when(isAtomType(io.in.bits.optype)) {
        when(io.in.valid & io.in.ready) {
            amo_ongoing := true.B
            amo_rs2     := rs2
        }
    }.elsewhen(amo_ongoing && (lstate === lWriteback) && load_wb.ready) {
        amo_ongoing := false.B
    }

    val amo_wdata = MuxLookup(io.in.bits.optype, DEBUG_MAGICNUM.U)(
        Seq(
            amoor  -> (load_buf.rdata | amo_rs2),
            amoadd -> (load_buf.rdata + amo_rs2)
        )
    )

    when(amo_ongoing) {
        io.in.ready             := false.B
        new_store_inst.id       := io.in.bits.id
        new_store_inst.addr     := load_buf.addr
        new_store_inst.uncached := in_mmio(load_buf.addr)
        new_store_inst.wtype    := LSUOpType.stw
        new_store_inst.wdata    := amo_wdata
        when(lstate === lWriteback) {
            assert(!store_queue.io.out.full)
            store_queue.io.in.enq_valid := true.B
            store_queue.io.in.enq_data  := new_store_inst
        }
    }

    uncached  := DelayN(in_mmio(vaddr), 1)
    load_excp := false.B
}
