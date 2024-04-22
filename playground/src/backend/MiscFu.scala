package miku.backend

import chisel3._
import chisel3.util._
import chisel3.experimental.BundleLiterals._

import miku._
import miku.MiscOpType._
import miku.frontend._

// Handling some funtional instruction like CACOP
// Besides it also handle all instructions which does not need a function unit, such as SYSCALL
// and in this situation it will do noting.

class MiscFuIO extends MkBundle {
    val timer64     = Input(UInt(64.W)) // stable counter
    val tid         = Flipped(new LA32CSR_Tid)
    val crmd        = Flipped(new LA32CSR_Crmd)
    val cacop_trans = Flipped(new AddrTransChannel)
    val cacop_inter = new Bundle {
        val req  = DecoupledIO(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
        val dest = UInt(3.W)
    }
}

class MiscFunctionUnit extends BaseFunctionUnit {
    val misc_io = IO(new MiscFuIO)

    // cacop info
    val rj    = io.in.bits.operand_a
    val rk    = io.in.bits.operand_b
    val imm   = io.in.bits.operand_b
    val code  = io.in.bits.operand_c
    val vaddr = rj + imm

    val cacop_valid  = io.in.valid &&
        (io.in.bits.optype === MiscOpType.cacop) && (io.in.bits.exception === LA32ExceptionType.NONE.enum_no)
    val cacop_result = code
    val handshake    = misc_io.cacop_inter.req.ready & misc_io.cacop_inter.req.valid
    misc_io.cacop_trans.valid               := handshake
    misc_io.cacop_trans.vaddr               := vaddr
    misc_io.cacop_trans.tlbsrch_en          := false.B
    misc_io.cacop_inter.req.bits            := 0.U.asTypeOf(misc_io.cacop_inter.req.bits) // initialise
    misc_io.cacop_inter.req.valid           := cacop_valid
    misc_io.cacop_inter.dest                := code(2, 0)
    misc_io.cacop_inter.req.bits.cacop_func := code(4, 3)
    misc_io.cacop_inter.req.bits.cacop_en   := cacop_valid
    misc_io.cacop_inter.req.bits.vaddr      := vaddr
    misc_io.cacop_inter.req.bits.paddr      := misc_io.cacop_trans.paddr

    val pg_mode        = !misc_io.crmd.DA & misc_io.crmd.PG
    val dmw_total_hits = misc_io.cacop_trans.dmw_hits
    val dmw_hit        = dmw_total_hits.reduce(_ || _)
    val tlb_resp       = misc_io.cacop_trans.tlb_resp

    val cacop_unmatch  = cacop_valid && (code(4, 3) === 2.U) && pg_mode && !dmw_hit && !tlb_resp.found
    val cacop_page_inv =
        cacop_valid && (code(4, 3) === 2.U) && pg_mode && !dmw_hit && tlb_resp.found && !tlb_resp.result.v
    val cacop_excp     = cacop_unmatch | cacop_page_inv

    // TODO: TLB exceptions caused by cacop

    // stable_counter
    val rdcnt_valid  = (io.in.bits.optype === MiscOpType.rdcntid) ||
        (io.in.bits.optype === MiscOpType.rdcntvl) ||
        (io.in.bits.optype === MiscOpType.rdcntvh)
    val rdcnt_result = MuxLookup(io.in.bits.optype, 0.U)(
        Seq(
            rdcntid -> misc_io.tid.TID,
            rdcntvl -> misc_io.timer64(31, 0),
            rdcntvh -> misc_io.timer64(63, 32)
        )
    )

    // syscall, break, unknown
    val syscall_valid = io.in.valid && (io.in.bits.optype === syscall)
    val unknown_inst  = io.in.valid && (io.in.bits.optype === unknown)
    val break_valid   = io.in.valid && (io.in.bits.optype === break)
    val idle_valid    = io.in.valid && (io.in.bits.optype === idle)
    val ertn_valid    = io.in.valid && (io.in.bits.optype === ertn)

    val ipe_excp =
        (misc_io.crmd.PLV === 3.U) && (idle_valid || ertn_valid || (cacop_valid && code =/= 2.U))

    io.out.bits.id := io.in.bits.id

    io.out.bits.exception := MuxCase(
        io.in.bits.exception,
        Seq(
            (ipe_excp, LA32ExceptionType.IPE.enum_no),
            (cacop_unmatch, LA32ExceptionType.TLBR.enum_no),
            (cacop_page_inv, LA32ExceptionType.PIL.enum_no),
            (syscall_valid, LA32ExceptionType.SYS.enum_no),
            (break_valid, LA32ExceptionType.BRK.enum_no),
            (unknown_inst, LA32ExceptionType.INE.enum_no)
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
