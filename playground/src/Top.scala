package miku

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._
import miku.backend._
import miku.issue.IssueStage
import miku.issue.IssuedInst

class TopIO extends MkBundle {
    val axi  = new AXIMasterIF(VADDR_WIDTH, WORD_WIDTH, 4)
    val diff = if (DIFFTEST_MODE) Some(new DifftestIO) else None
}

class MkTop extends MkModule {
    val io = IO(new TopIO)

    // frontend
    val frontend = Module(new MkFrontend)

    // backend
    val decode = Module(new IDU)
    val issue  = Module(new IssueStage)
    val excute = Module(new EXU)

    // csr
    val csr = Module(new LA32CSRRegfiles)

    // cache
    val icache = Module(new MkCache(ICACHE_PARAMS))
    val dcache = Module(new MkCache(DCACHE_PARAMS))

    // mmu
    val mmu = Module(new LA32AddrTransUnit)

    // cacop
    val cacop_inter = excute.io.misc_io.cacop_inter
    val icacop_en   = cacop_inter.req.valid && (cacop_inter.dest === 0.U)
    val dcacop_en   = cacop_inter.req.valid && (cacop_inter.dest === 1.U)
    val cacop_req   = cacop_inter.req
    cacop_req.ready := false.B

    when(icacop_en && icache.io.req.ready) {
        frontend.io.icache_inter.req.ready := false.B
        icache.io.req                      <> cacop_req
    }.otherwise {
        icache.io.req <> frontend.io.icache_inter.req
    }
    icache.io.req.bits.paddr := frontend.io.icache_inter.req.bits.paddr //
    icache.io.resp           <> frontend.io.icache_inter.resp

    val flush = 0.U.asTypeOf(new FlushReason)
    flush.ertn      := issue.io.ertn_commit
    flush.exception := issue.io.excp_info.valid
    flush.mispred   := excute.io.pred_check.update.valid & excute.io.pred_check.update.bits.redirect

    decode.io.ifu_s1           := frontend.io.s1
    decode.io.inst_queue_flush := flush
    decode.io.to_issue         <> issue.io.from_decoder

    frontend.io.update             := excute.io.pred_check.update
    frontend.io.inst_queue_full    := decode.io.inst_queue_full
    frontend.io.excp_info          := issue.io.excp_info
    frontend.io.from_csr.eentry    := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.EENTRY)
    frontend.io.from_csr.tlbrentry := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.TLBRENTRY)
    frontend.io.from_csr.era       := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.ERA)
    frontend.io.from_csr.dwm(0)    := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.DMW0)
    frontend.io.from_csr.dwm(1)    := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.DMW1)
    frontend.io.from_csr.crmd      := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.CRMD)
    frontend.io.excp_commit        <> issue.io.excp_commit
    frontend.io.ertn_commit        <> issue.io.ertn_commit

    issue.io.trans.ready := excute.io.in.ready
    issue.io.wb_data(0)  <> excute.io.out.flu_out
    issue.io.wb_data(1)  <> excute.io.out.lsu_out
    issue.io.int_flag    := csr.io.int_flag

    excute.io.in.bits                := issue.io.trans.bits.fuinput
    excute.io.in.valid               := issue.io.trans.valid
    excute.io.futype                 := issue.io.trans.bits.futype
    // ! turn off branch prediction during correctness test
    excute.io.pred_check.br_pred     := 0.U.asTypeOf(new BranchPredictorResult)
    excute.io.lsu_io.store_commit    <> issue.io.store_commit
    excute.io.lsu_io.from_csr.crmd   := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.CRMD)
    excute.io.lsu_io.from_csr.dwm(0) := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.DMW0)
    excute.io.lsu_io.from_csr.dwm(1) := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.DMW1)
    excute.io.csr_io.csr_commit      <> issue.io.csr_commit
    excute.io.misc_io.timer64        := csr.io.timer64_o
    excute.io.misc_io.tid            := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.TID)
    excute.io.flush                  := flush

    mmu.io.inst_trans      <> frontend.io.inst_trans
    mmu.io.data_trans      <> excute.io.lsu_io.data_trans
    // mmu.io.inst_trans      <> DontCare
    mmu.io.from_csr.asid   := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.ASID)
    mmu.io.from_csr.crmd   := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.CRMD)
    mmu.io.from_csr.dmw(0) := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.DMW0)
    mmu.io.from_csr.dmw(1) := csr.io.raw_datas.getTargetCSR(LA32CSRRegisters.DMW1)

    csr.io.read_io     <> excute.io.csr_io.read_io
    csr.io.write_io    <> excute.io.csr_io.write_io
    csr.io.excp_info   := issue.io.excp_info
    csr.io.ertn_commit := issue.io.ertn_commit
    csr.io.interrupt   := 0.U // TODO: connect with external interrupt

    when(dcacop_en && dcache.io.req.ready) {
        excute.io.lsu_io.cache_req.ready := false.B
        dcache.io.req                    <> cacop_req
    }.otherwise {
        dcache.io.req <> excute.io.lsu_io.cache_req
    }
    dcache.io.req.bits.paddr := excute.io.lsu_io.cache_req.bits.paddr
    dcache.io.resp           <> excute.io.lsu_io.cache_resp

    val axi_arb = Module(new PriorityAXIArbiter(2, 32, 32, 5))
    axi_arb.io.in(0) <> icache.io.axi
    axi_arb.io.in(1) <> dcache.io.axi
    io.axi           <> axi_arb.io.out

    if (DIFFTEST_MODE) {
        io.diff.get.commit_inst    := issue.io.diff.get.commit_inst
        io.diff.get.gpr            := issue.io.diff.get.gpr
        io.diff.get.is_CNTinst     := issue.io.diff.get.is_CNTinst
        io.diff.get.is_commit_excp := issue.io.diff.get.is_commit_excp
        io.diff.get.timer_64       := csr.io.timer64_o

        val csr_types = LA32CSRRegisters.csr_defns.map(_._2)
        io.diff.get.csr := csr.io.raw_datas
    }
}
