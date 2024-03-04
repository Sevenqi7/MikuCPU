package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.backend._
import miku.frontend._

class LSUIO extends MkBundle {
    val cache_req    = Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
    val cache_resp   = Flipped(ValidIO(new CacheRespIO(WORD_WIDTH)))
    val store_commit = Flipped(new ReadyValidBundle)
}

class StoreQueueEntry extends MkBundle {
    val id    = UInt(TRANS_ID_BITS.W)
    val addr  = UInt(VADDR_WIDTH.W)
    val wstrb = UInt(wordBytes.W)
    val wdata = UInt(WORD_WIDTH.W)
    // val commit_en = Bool()
}

class LSU extends BaseFunctionUnit {
    val lsu_io = IO(new LSUIO)

    val rj      = io.in.bits.operand_a
    val rd      = io.in.bits.operand_c
    val imm_s12 = io.in.bits.operand_b
    val vaddr   = rj + imm_s12
    val wdata   = rd
    val wstrb   = LSUOpType.toWriteMask(io.in.bits.optype)

    // LSU-DCache
    val to_dcache   = lsu_io.cache_req
    val from_dcache = lsu_io.cache_resp

    // load request bufffer

    val lIdle :: lReq :: lWait :: lWriteback :: Nil = Enum(4)
    val lstate                                      = RegInit(lIdle)

    val load_buf   = RegInit(0.U.asTypeOf(new Bundle {
        val id    = UInt(TRANS_ID_BITS.W)
        val vaddr = UInt(VADDR_WIDTH.W)
        val valid = Bool()
        val rdata = UInt(WORD_WIDTH.W)
    }))
    val load_req   = Wire(Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH)))
    val load_resp  = lsu_io.cache_resp
    val load_ready = Wire(Bool())
    val load_wb    = Wire(Decoupled(new BaseFuOutput))

    // initialise
    load_ready     := false.B
    load_req.bits  := 0.U.asTypeOf(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
    load_req.valid := false.B
    load_wb.bits   := 0.U.asTypeOf(new BaseFuOutput)
    load_wb.valid  := false.B

    // format: off
    when(lstate === lIdle) {
        load_ready := true.B
        when(io.in.valid & LSUOpType.isLoadType(io.in.bits.optype)) {
            load_buf.id     := io.in.bits.id
            load_buf.vaddr  := vaddr
            load_buf.valid  := true.B
            lstate          := lReq
        }
    }.elsewhen(lstate === lReq) {
        load_req.valid         := true.B
        load_req.bits.addr     := load_buf.vaddr
        load_req.bits.uncached := false.B
        load_req.bits.wr       := false.B
        load_req.bits.wtype    := 0.U
        load_req.bits.wdata    := 0.U
        when(load_req.ready) {
            lstate := lWait
        }
    }.elsewhen(lstate === lWait) {
        when(load_resp.valid & load_resp.bits.done){    
            load_buf.rdata  := load_resp.bits.rdata
            lstate          := lWriteback
        }
    }.elsewhen(lstate === lWriteback){
        lstate := lIdle
        load_wb.valid           := true.B
        load_wb.bits.id         := load_buf.id
        load_wb.bits.exception  := false.B
        load_wb.bits.result     := load_buf.rdata
    }
    // format: on

    // store request queue
    val store_queue      = Module(new CircularQueue(new StoreQueueEntry, 8, true))
    val front_store_inst = store_queue.io.out.front_data
    val new_store_inst   = Wire(new StoreQueueEntry)
    val store_ready      = !store_queue.io.out.full
    new_store_inst.id    := io.in.bits.id
    new_store_inst.addr  := vaddr
    new_store_inst.wstrb := wstrb
    new_store_inst.wdata := wdata

    val store_req  = Wire(Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH)))
    val store_resp = lsu_io.cache_resp
    val store_wb   = Wire(Decoupled(new BaseFuOutput))

    store_wb.bits.exception     := false.B
    store_wb.bits.result        := DEBUG_MAGICNUM.U
    store_wb.bits.id            := DelayN(io.in.bits.id, 1)
    store_wb.valid              := DelayN(LSUOpType.isStoreType(io.in.bits.optype) & io.in.valid, 1)
    store_queue.io.in.clear     := false.B
    store_queue.io.in.enq_data  := new_store_inst
    store_queue.io.in.enq_valid := LSUOpType.isStoreType(io.in.bits.optype) & io.in.valid
    store_queue.io.in.deq_valid := lsu_io.store_commit.valid & lsu_io.store_commit.ready
    lsu_io.store_commit.ready   := store_req.ready

    // store-commit
    val sIdle :: sReq :: Nil = Enum(2)
    val sstate               = RegInit(sIdle)

    store_req.valid := false.B
    when(lsu_io.store_commit.valid) {
        assert(!store_queue.io.out.empty)
        store_req.valid := true.B
    }

    store_req.bits.addr     := front_store_inst.addr
    store_req.bits.wdata    := front_store_inst.wdata
    store_req.bits.wtype    := front_store_inst.wstrb
    store_req.bits.uncached := false.B
    store_req.bits.wr       := true.B

    val req_arb = Module(new Arbiter(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH), 2))
    req_arb.io.in(0) <> store_req
    req_arb.io.in(1) <> load_req
    to_dcache        <> req_arb.io.out

    val wb_arb = Module(new Arbiter(new BaseFuOutput, 2))
    wb_arb.io.in(0) <> store_wb
    wb_arb.io.in(1) <> load_wb

    io.out <> wb_arb.io.out

    io.in.ready := MuxCase(
        false.B,
        Seq(
            (LSUOpType.isLoadType(io.in.bits.optype), load_ready),
            (LSUOpType.isStoreType(io.in.bits.optype), store_ready)
        )
    )
}
