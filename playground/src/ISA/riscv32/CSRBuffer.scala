package miku.isa.riscv32

import chisel3._
import chisel3.util._

import miku.isa._
import miku.utils._
import miku.backend._
import CSROpType._

class RV32CSRBuffer extends CSRBuffer {
    val rs1_data = io.in.bits.operand_a

    csr_busy := csr_wvalid_r
    csr_excp := ArchExceptionType.NONE.enum_no
    csr_addr := io.in.bits.operand_b(CSR_ADDR_WD - 1, 0)

    val csrrs_wdata = rs1_data | csr_rdata

    csr_wdata := MuxLookup(io.in.bits.optype, DEBUG_MAGICNUM.U)(
        Seq(
            csrrw -> rs1_data,
            csrrs -> csrrs_wdata
        )
    )

    csr_wvalid        := MuxLookup(io.in.bits.optype, false.B)(
        Seq(
            csrrw -> true.B,
            csrrs -> true.B,
            csrrc -> true.B
        )
    )
    io_tlb_busy_stall := false.B

    when(io.flush.ertn | io.flush.exception) {
        csr_wvalid_r := false.B
    }
}
