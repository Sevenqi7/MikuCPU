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
    val addr  = UInt(VADDR_WIDTH.W)
    val wstrb = UInt(wordBytes.W)
    val wdata = UInt(WORD_WIDTH.W)
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

    // store queue
    val trans_id         = RegEnable(io.in.bits.id, io.in.valid & io.in.ready)
    val store_queue      = Module(new CircularQueue(new StoreQueueEntry, 8, true))
    val front_store_inst = store_queue.io.out.front_data
    val new_store_inst   = Wire(new StoreQueueEntry)
    new_store_inst.addr  := vaddr
    new_store_inst.wstrb := wstrb
    new_store_inst.wdata := wdata

    val load_valid  = LSUOpType.isLoadType(io.in.bits.optype)
    val store_valid = lsu_io.store_commit.valid

    store_queue.io.in.clear     := false.B
    store_queue.io.in.enq_data  := new_store_inst
    store_queue.io.in.enq_valid := LSUOpType.isStoreType(io.in.bits.optype)
    store_queue.io.in.deq_valid := store_valid & to_dcache.ready
    lsu_io.store_commit.ready   := !store_queue.io.out.empty & lsu_io.cache_req.ready

    to_dcache.valid         := load_valid | store_valid
    to_dcache.bits.addr     := Mux(store_valid, front_store_inst.addr, vaddr)
    to_dcache.bits.wdata    := front_store_inst.wdata
    to_dcache.bits.wtype    := front_store_inst.wstrb
    to_dcache.bits.wr       := store_valid
    to_dcache.bits.uncached := false.B

    io.out.bits.id        := trans_id
    io.out.bits.exception := false.B // TODO: add unalign exception
    io.out.bits.result    := from_dcache.bits.rdata
    io.out.valid          := from_dcache.bits.done & from_dcache.valid
    io.in.ready           := !store_valid
}
