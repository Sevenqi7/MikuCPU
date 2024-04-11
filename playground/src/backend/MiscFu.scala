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
    val timer64     = Input(UInt(64.W))
    val tid         = Flipped(new LA32CSR_Tid)
    val cacop_inter = new Bundle {
        val req  = DecoupledIO(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
        val dest = UInt(3.W)
    }
}

class MiscFunctionUnit extends BaseFunctionUnit {
    val misc_io = IO(new MiscFuIO)

    // cacop info
    val rj    = io.in.bits.operand_a
    val imm   = io.in.bits.operand_b
    val code  = io.in.bits.operand_c
    val vaddr = rj + imm

    val cacop_valid  = (io.in.bits.optype === MiscOpType.cacop) && io.in.valid
    val cacop_result = code
    val handshake    = misc_io.cacop_inter.req.ready & misc_io.cacop_inter.req.valid
    // assert(!cacop_valid)
    misc_io.cacop_inter.req.bits            := 0.U.asTypeOf(misc_io.cacop_inter.req.bits) // initialise
    misc_io.cacop_inter.req.valid           := cacop_valid
    misc_io.cacop_inter.dest                := code(4, 2)
    misc_io.cacop_inter.req.bits.cacop_func := code(1, 0)
    misc_io.cacop_inter.req.bits.cacop_en   := cacop_valid
    misc_io.cacop_inter.req.bits.vaddr      := vaddr
    misc_io.cacop_inter.req.bits.paddr      := RegNext(vaddr)

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

    // syscall
    val syscall_valid =
        (io.in.bits.optype === MiscOpType.syscall) && (LA32ExceptionType.SYS.enum_no < io.in.bits.exception)
    val unknown_inst  =
        (io.in.bits.optype === MiscOpType.unknown) && (LA32ExceptionType.INE.enum_no < io.in.bits.exception)
    val break_valid = (io.in.bits.optype === MiscOpType.break) && (LA32ExceptionType.BRK.enum_no < io.in.bits.exception)

    io.out.bits.id := io.in.bits.id

    io.out.bits.exception := MuxCase(
        io.in.bits.exception,
        Seq(
            (syscall_valid, LA32ExceptionType.SYS.enum_no),
            (break_valid, LA32ExceptionType.BRK.enum_no),
            (unknown_inst, LA32ExceptionType.INE.enum_no)
        )
    )
    io.out.bits.result    := MuxCase(
        0.U,
        Seq(
            (rdcnt_valid, rdcnt_result),
            (cacop_valid, cacop_result)
        )
    )
    io.out.valid          := Mux(!cacop_valid, io.in.valid, handshake)
    io.out.bits.mispred   := false.B
    io.in.ready           := Mux(!cacop_valid, true.B, handshake)
}
