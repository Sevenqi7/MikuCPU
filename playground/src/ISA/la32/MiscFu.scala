package miku.isa.la32

import chisel3._
import chisel3.util._

import miku._
import miku.isa._
import miku.frontend._
import miku.isa.MiscOpType._
import miku.backend.MiscFunctionUnit

class LA32MiscFuIO extends MkBundle {
    val cacop_trans = Flipped(new AddrTransChannel)
    val cacop_inter = new Bundle {
        val req  = DecoupledIO(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
        val dest = UInt(3.W)
    }
}

class LA32MiscFu extends MiscFunctionUnit {
    override val misc_io = IO(new LA32MiscFuIO)

    // cacop info
    val rj    = io.in.bits.operand_a
    val rk    = io.in.bits.operand_b
    val imm   = io.in.bits.operand_b
    val code  = io.in.bits.operand_c
    val vaddr = rj + imm

    val cacop_valid  = io.in.valid &&
        (io.in.bits.optype === MiscOpType.cacop) && (io.in.bits.exception === ArchExceptionType.NONE.enum_no)
    val cacop_result = code
    val handshake    = misc_io.cacop_inter.req.ready & misc_io.cacop_inter.req.valid
    misc_io.cacop_trans.req.valid           := handshake
    misc_io.cacop_trans.req.vaddr           := vaddr
    misc_io.cacop_inter.req.bits            := 0.U.asTypeOf(misc_io.cacop_inter.req.bits) // initialise
    misc_io.cacop_inter.req.valid           := cacop_valid
    misc_io.cacop_inter.dest                := code(2, 0)
    misc_io.cacop_inter.req.bits.cacop_func := code(4, 3)
    misc_io.cacop_inter.req.bits.cacop_en   := cacop_valid
    misc_io.cacop_inter.req.bits.vaddr      := vaddr
    misc_io.cacop_inter.req.bits.paddr      := misc_io.cacop_trans.resp.paddr

    val crmd           = io.csr_vec.getTargetCSR(LA32CSRRegisters.CRMD)
    val pg_mode        = !crmd.DA & crmd.PG
    val dmw_total_hits = misc_io.cacop_trans.resp.dmw_hits
    val dmw_hit        = dmw_total_hits.reduce(_ || _)
    val tlb_resp       = misc_io.cacop_trans.resp.tlb_resp

    val cacop_unmatch  = cacop_valid && (code(4, 3) === 2.U) && pg_mode && !dmw_hit && !tlb_resp.found
    val cacop_page_inv =
        cacop_valid && (code(4, 3) === 2.U) && pg_mode && !dmw_hit && tlb_resp.found && !tlb_resp.result.v
    val cacop_excp     = cacop_unmatch | cacop_page_inv

    // TODO: TLB exceptions caused by cacop

    // stable_counter
    val tid          = io.csr_vec.getTargetCSR(LA32CSRRegisters.TID)
    val rdcnt_valid  = (io.in.bits.optype === MiscOpType.rdcntid) ||
        (io.in.bits.optype === MiscOpType.rdcntvl) ||
        (io.in.bits.optype === MiscOpType.rdcntvh)
    val rdcnt_result = MuxLookup(io.in.bits.optype, 0.U)(
        Seq(
            rdcntid -> tid.TID,
            rdcntvl -> io.csr_vec.timer_cycle(31, 0),
            rdcntvh -> io.csr_vec.timer_cycle(63, 32)
        )
    )

    // syscall, break, unknown
    val unknown_inst  = io.in.valid && (io.in.bits.optype === unknown)
    val break_valid   = io.in.valid && (io.in.bits.optype === break)
    val idle_valid    = io.in.valid && (io.in.bits.optype === idle)
    val syscall_valid = io.in.valid && (io.in.bits.optype === syscall)
    val ertn_valid    = io.in.valid && (io.in.bits.optype === ertn)

    val ipe_excp =
        (crmd.PLV === 3.U) && (idle_valid || ertn_valid || (cacop_valid && code =/= 2.U))

    io.out.bits.id        := io.in.bits.id
    io.out.bits.exception := MuxCase(
        io.in.bits.exception,
        Seq(
            (ipe_excp, LA32ExceptionDefns.IPE.enum_no),
            (cacop_unmatch, LA32ExceptionDefns.TLBR.enum_no),
            (cacop_page_inv, LA32ExceptionDefns.PIL.enum_no),
            (syscall_valid, LA32ExceptionDefns.SYS.enum_no),
            (break_valid, LA32ExceptionDefns.BRK.enum_no),
            (unknown_inst, LA32ExceptionDefns.INE.enum_no)
        )
    )
    io.out.bits.result    := MuxCase(
        0.U,
        Seq(
            (cacop_excp, vaddr),
            (rdcnt_valid, rdcnt_result),
            (cacop_valid, cacop_result)
        )
    )
    io.out.valid          := Mux(!cacop_valid, io.in.valid, RegNext(handshake))
    io.out.bits.mispred   := false.B
    io.in.ready           := Mux(!cacop_valid, true.B, RegNext(handshake))
}
