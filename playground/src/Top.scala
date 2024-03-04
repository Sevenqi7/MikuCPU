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
    val icache   = Module(new MkCache(20, 4, 2, 128, true))

    // backend
    val decode = Module(new IDU)
    val issue  = Module(new IssueStage)
    val dcache = Module(new MkCache(20, 4, 2, 128, false))
    val excute = Module(new EXU)

    icache.io.req                 <> frontend.io.icache_msg.cache_req
    icache.io.resp                <> frontend.io.icache_msg.cache_resp
    decode.io.ifu_s1              := frontend.io.s1
    decode.io.exception           := false.B
    frontend.io.update            := excute.io.pred_check.update
    frontend.io.inst_queue_full   := decode.io.inst_queue_full
    decode.io.pred_check          := excute.io.pred_check.update
    // decode.io.to_issue.ready := false.B
    decode.io.to_issue            <> issue.io.from_decoder
    excute.io.in.bits             := issue.io.trans.bits.fuinput
    excute.io.in.valid            := issue.io.trans.valid
    issue.io.trans.ready          := excute.io.in.ready
    excute.io.futype              := issue.io.trans.bits.futype
    excute.io.pred_check.br_pred  := 0.U.asTypeOf(new BranchPredictorResult)
    excute.io.lsu_io.store_commit <> issue.io.store_commit
    excute.io.lsu_io.cache_req    <> dcache.io.req
    excute.io.lsu_io.cache_resp   <> dcache.io.resp
    issue.io.wb_data(0)           <> excute.io.out.flu_out
    issue.io.wb_data(1)           <> excute.io.out.lsu_out

    val axi_arb = Module(new PriorityAXIArbiter(2, 32, 32, 5))
    axi_arb.io.in(0) <> icache.io.axi
    axi_arb.io.in(1) <> dcache.io.axi
    io.axi           <> axi_arb.io.out

    if (DIFFTEST_MODE) {
        io.diff.get := issue.io.diff.get
    }
}
