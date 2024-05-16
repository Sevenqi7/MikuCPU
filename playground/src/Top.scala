package miku

import chisel3._
import chisel3.util._

import miku.utils._
import miku.isa.la32._
import miku.frontend._
import miku.backend._
import miku.issue.IssueStage
import miku.issue.IssuedInst

class TopIO extends MkBundle {
    val axi     = new AXIMasterIF(VADDR_WIDTH, WORD_WIDTH, 4)
    val ext_int = Input(UInt(8.W))
}

abstract class MkTop extends MkModule {
    val io = IO(new TopIO)

    // frontend
    val frontend = Module(new MkFrontend)

    // backend
    val decode = Module(new IDU)
    val issue  = Module(new IssueStage)
    val excute = Module(new EXU)
    // csr
    val csr    = Module(ArchCSRRegfiles())
    // cache
    val icache = Module(new MkCache(ICACHE_PARAMS))
    val dcache = Module(new MkCache(DCACHE_PARAMS))

    icache.io.req  <> frontend.io.icache_inter.req
    icache.io.resp <> frontend.io.icache_inter.resp

    val frontend_flush = 0.U.asTypeOf(new FlushReason)
    frontend_flush.ertn      := issue.io.ertn_commit
    frontend_flush.exception := issue.io.excp_commit.valid
    frontend_flush.mispred   := excute.io.br_update.valid

    val backend_flush = WireInit(frontend_flush)

    decode.io.ifu_s1           := frontend.io.s1
    decode.io.br_pred          := frontend.io.br_pred
    decode.io.inst_queue_flush := frontend_flush
    decode.io.to_issue         <> issue.io.from_decoder

    frontend.io.update          := excute.io.br_update
    frontend.io.inst_queue_full := decode.io.inst_queue_full
    frontend.io.csr_vec         := csr.io.raw_datas
    frontend.io.excp_commit     := issue.io.excp_commit
    frontend.io.excp_commit     <> issue.io.excp_commit
    frontend.io.ertn_commit     <> issue.io.ertn_commit

    issue.io.trans.ready := excute.io.in.ready
    issue.io.wb_data(0)  <> excute.io.out.flu_out
    issue.io.wb_data(1)  <> excute.io.out.lsu_out
    issue.io.int_flag    := csr.io.int_flag
    issue.io.timer64     := csr.io.timer64_o

    excute.io.in.bits          := issue.io.trans.bits.fuinput
    excute.io.in.valid         := issue.io.trans.valid
    excute.io.futype           := issue.io.trans.bits.futype
    excute.io.csr_vec          := csr.io.raw_datas
    // ! turn off branch prediction during correctness test
    excute.io.br_pred          := issue.io.trans.bits.br_pred
    excute.lsu_io.store_commit <> issue.io.store_commit
    excute.csr_io.csr_commit   <> issue.io.csr_commit
    excute.io.flush            := backend_flush

    dcache.io.req  <> excute.lsu_io.cache_req
    dcache.io.resp <> excute.lsu_io.cache_resp

    csr.io.read_io     <> excute.csr_io.read_io
    csr.io.write_io    <> excute.csr_io.write_io
    csr.io.excp_commit := issue.io.excp_commit
    csr.io.ertn_commit := issue.io.ertn_commit
    csr.io.interrupt   := io.ext_int

    val axi_arb = Module(new PriorityAXIArbiter(2, 32, 32, 5))
    axi_arb.io.in(1) <> icache.io.axi
    axi_arb.io.in(0) <> dcache.io.axi
    io.axi           <> axi_arb.io.out

    if (DIFFTEST_MODE) {
        issue.io.lsu_diff.get := excute.lsu_io.lsu_diff.get
    }
}
