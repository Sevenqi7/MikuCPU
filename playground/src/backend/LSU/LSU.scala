package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.backend._
import miku.frontend._

class LSUInput extends BaseFuInput {}

class LSUOutput extends BaseFuOutput {
    val result = UInt(WORD_WIDTH.W)
}

class LSUIO extends MkBundle {
    val in           = Flipped(Decoupled(new LSUInput))
    val out          = ValidIO(new LSUOutput)
    val cache_req    = Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
    val cache_resp   = Flipped(new CacheRespIO(WORD_WIDTH))
    val store_commit = Flipped(new ReadyValidBundle)
}

class StoreQueueEntry extends MkBundle {
    val addr  = UInt(VADDR_WIDTH.W)
    val wstrb = UInt(wordBytes.W)
    val wdata = UInt(WORD_WIDTH.W)
}

class LSU extends MkModule {
    val io = IO(new LSUIO)

    val rj      = io.in.bits.operand_a
    val rd      = io.in.bits.operand_c
    val imm_s12 = io.in.bits.operand_b
    val vaddr   = rj + imm_s12
    val wdata   = rd
    val wstrb   = LSUOpType.toWriteMask(io.in.bits.optype)

    // LSU-DCache
    val to_dcache   = io.cache_req
    val from_dcache = io.cache_resp

    // store queue
    val store_queue      = Module(new CircularQueue(new StoreQueueEntry, 8, true))
    val front_store_inst = store_queue.io.out.front_data
    val new_store_inst   = Wire(new StoreQueueEntry)
    new_store_inst.addr  := vaddr
    new_store_inst.wstrb := wstrb
    new_store_inst.wdata := wdata

    val load_valid  = LSUOpType.isLoadType(io.in.bits.optype)
    val store_valid = io.store_commit.valid

    store_queue.io.in.clear     := false.B
    store_queue.io.in.enq_data  := new_store_inst
    store_queue.io.in.enq_valid := LSUOpType.isStoreType(io.in.bits.optype)
    store_queue.io.in.deq_valid := store_valid & to_dcache.ready
    io.store_commit.ready       := !store_queue.io.out.empty & io.cache_req.ready

    to_dcache.valid         := load_valid | store_valid
    to_dcache.bits.addr     := Mux(store_valid, front_store_inst.addr, vaddr)
    to_dcache.bits.wdata    := front_store_inst.wdata
    to_dcache.bits.wtype    := front_store_inst.wstrb
    to_dcache.bits.wr       := store_valid
    to_dcache.bits.uncached := false.B

    io.out.bits.result := from_dcache.rdata
    io.out.valid       := from_dcache.done
    io.in.ready        := !store_valid
}
