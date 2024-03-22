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

    // cacop
    val cacop_inter = excute.io.misc_io.cacop_inter
    val icacop_en   = cacop_inter.req.valid && (cacop_inter.dest === 0.U)
    val dcacop_en   = cacop_inter.req.valid && (cacop_inter.dest === 1.U)
    val cacop_req   = cacop_inter.req
    cacop_req.ready := false.B

    when(icacop_en && icache.io.req.ready) {
        frontend.io.icache_msg.cache_req.ready := false.B
        icache.io.req                          <> cacop_req
    }.otherwise {
        icache.io.req <> frontend.io.icache_msg.cache_req
    }
    icache.io.resp <> frontend.io.icache_msg.cache_resp

    decode.io.ifu_s1     := frontend.io.s1
    decode.io.exception  := false.B
    decode.io.pred_check := excute.io.pred_check.update
    decode.io.to_issue   <> issue.io.from_decoder

    frontend.io.update          := excute.io.pred_check.update
    frontend.io.inst_queue_full := decode.io.inst_queue_full

    issue.io.trans.ready := excute.io.in.ready
    issue.io.wb_data(0)  <> excute.io.out.flu_out
    issue.io.wb_data(1)  <> excute.io.out.lsu_out

    excute.io.in.bits             := issue.io.trans.bits.fuinput
    excute.io.in.valid            := issue.io.trans.valid
    excute.io.futype              := issue.io.trans.bits.futype
    excute.io.pred_check.br_pred  := 0.U.asTypeOf(new BranchPredictorResult)
    excute.io.lsu_io.store_commit <> issue.io.store_commit
    excute.io.csr_io.csr_commit   <> issue.io.csr_commit
    excute.io.misc_io.timer64     := csr.io.timer64_o

    csr.io.read_io  <> excute.io.csr_io.read_io
    csr.io.write_io <> excute.io.csr_io.write_io

    when(dcacop_en && dcache.io.req.ready) {
        excute.io.lsu_io.cache_req.ready := false.B
        dcache.io.req                    <> cacop_req
    }.otherwise {
        dcache.io.req <> excute.io.lsu_io.cache_req
    }
    dcache.io.resp <> excute.io.lsu_io.cache_resp

    val axi_arb = Module(new PriorityAXIArbiter(2, 32, 32, 5))
    axi_arb.io.in(0) <> icache.io.axi
    axi_arb.io.in(1) <> dcache.io.axi
    io.axi           <> axi_arb.io.out

    if (DIFFTEST_MODE) {
        io.diff.get.commit_inst := issue.io.diff.get.commit_inst
        io.diff.get.gpr         := issue.io.diff.get.gpr
        io.diff.get.is_CNTinst  := issue.io.diff.get.is_CNTinst
        io.diff.get.csr         := csr.io.csr_datas
        io.diff.get.timer_64    := csr.io.timer64_o
    }
}
