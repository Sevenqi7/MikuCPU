package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.backend._
import miku.frontend._
import miku.LSUOpType._
import dataclass.data

class LSUIO extends MkBundle {
    val cache_req    = Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
    val cache_resp   = Flipped(ValidIO(new CacheRespIO(WORD_WIDTH)))
    val store_commit = Flipped(new ReadyValidBundle)
    val data_trans   = Flipped(new AddrTransChannel)
    val from_csr     = Flipped(new Bundle {
        val crmd = new LA32CSR_Crmd
        val dwm  = Vec(2, new LA32CSR_Dmw)
    })
}

class StoreQueueEntry extends MkBundle {
    val id    = UInt(TRANS_ID_BITS.W)
    val addr  = UInt(VADDR_WIDTH.W)
    val wtype = UInt(2.W)
    val wdata = UInt(WORD_WIDTH.W)
    // val commit_en = Bool()
}

class LSU extends BaseFunctionUnit {
    val lsu_io = IO(new LSUIO)

    def getWstrbFromWtype(wtype: UInt, offset: UInt): UInt = {
        ~0.U(4.W) >> (4.U - (1.U << wtype)) << offset(log2Ceil(wordBytes) - 1, 0)
    }

    val rj      = io.in.bits.operand_a
    val rd      = io.in.bits.operand_c
    val imm_s12 = io.in.bits.operand_b
    val vaddr   = rj + imm_s12
    val wdata   = rd
    // val wtype   = LSUOpType.toWriteMask(io.in.bits.optype)
    val wtype   = io.in.bits.optype(1, 0)

    val store_queue = Module(new CircularQueue(new StoreQueueEntry, 8, true))

    // LSU-DCache
    val to_dcache   = lsu_io.cache_req
    val from_dcache = lsu_io.cache_resp

    // load request bufffer

    val lIdle :: lReq :: lWait :: lWriteback :: Nil = Enum(4)
    val lstate                                      = RegInit(lIdle)

    val load_buf   = RegInit(0.U.asTypeOf(new Bundle {
        val id     = UInt(TRANS_ID_BITS.W)
        val vaddr  = UInt(VADDR_WIDTH.W)
        val ldtype = LSUOpType()
        val valid  = Bool()
        val rdata  = UInt(WORD_WIDTH.W)
    }))
    val load_req   = Wire(Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH)))
    val load_resp  = lsu_io.cache_resp
    val load_ready = Wire(Bool())
    val load_wb    = Wire(Decoupled(new BaseFuOutput))

    // TODO: need parameterise
    val real_rdata  = Wire(UInt(32.W))
    val ldbu_result = MuxLookup(load_buf.vaddr(1, 0), DEBUG_MAGICNUM.U)(
        Seq(
            "b00".U -> real_rdata(7, 0),
            "b01".U -> real_rdata(15, 8),
            "b10".U -> real_rdata(23, 16),
            "b11".U -> real_rdata(31, 24)
        )
    )
    val ldhu_result = Mux(load_buf.vaddr(1), real_rdata(31, 16), real_rdata(15, 0))
    val ldw_result  = real_rdata

    // initialise
    load_ready          := false.B
    load_req.bits       := 0.U.asTypeOf(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
    load_req.valid      := false.B
    load_wb.bits        := 0.U.asTypeOf(new BaseFuOutput)
    load_wb.valid       := false.B
    load_req.bits.paddr := DontCare
    val load_unalign = MuxLookup(load_buf.ldtype, false.B)(
        Seq(
            ldh  -> load_buf.vaddr(0),
            ldhu -> load_buf.vaddr(0),
            ldw  -> (load_buf.vaddr(0) | load_buf.vaddr(1))
        )
    )

    // search in store queue
    val stq_items      = store_queue.io.out.element_vec.get
    val stq_total_hits =
        stq_items.map(st => st.valid && st.bits.addr(VADDR_WIDTH - 1, 2) === load_buf.vaddr(VADDR_WIDTH - 1, 2))
    val stq_hit        = stq_total_hits.reduce(_ || _)
    val stq_hit_item   = stq_items(OHToUInt(stq_total_hits))
    real_rdata := Mux(
        !stq_hit,
        load_resp.bits.rdata, {
            val wstrb = getWstrbFromWtype(stq_hit_item.bits.wtype, wordBytes.U)
            val wmask = Cat((0 until wordBytes).map(i => Cat(Seq.fill(8)(wstrb(i)))))
            val wdata = stq_hit_item.bits.wdata
            val bools = VecInit(load_resp.bits.rdata.asBools)
            for (i <- 0 until bools.length) {
                assert(wmask.getWidth == bools.getWidth)
                when(wmask(i)) {
                    bools(i) := wdata(i)
                }
            }
            bools.asUInt
        }
    )

    switch(lstate) {
        is(lIdle) {
            load_ready := true.B
            when(io.in.valid & LSUOpType.isLoadType(io.in.bits.optype)) {
                load_buf.id     := io.in.bits.id
                load_buf.vaddr  := vaddr
                load_buf.ldtype := io.in.bits.optype
                load_buf.valid  := true.B
                lstate          := lReq
            }
        }
        is(lReq) {
            load_req.valid      := !load_unalign
            load_req.bits.vaddr := load_buf.vaddr
            load_req.bits.wr    := false.B
            load_req.bits.wtype := 0.U
            load_req.bits.wdata := 0.U
            lstate              := MuxCase(
                lReq,
                Seq(
                    load_unalign   -> lWriteback,
                    load_req.ready -> lWait
                )
            )
        }
        is(lWait) {
            when(load_resp.valid & load_resp.bits.done) { // TODO: parameterise this state by cache parameters
                load_buf.rdata := MuxLookup(load_buf.ldtype, DEBUG_MAGICNUM.U)(
                    Seq(
                        ldb  -> SEXT(ldbu_result, WORD_WIDTH),
                        ldbu -> UEXT(ldbu_result, WORD_WIDTH),
                        ldh  -> SEXT(ldhu_result, WORD_WIDTH),
                        ldhu -> UEXT(ldhu_result, WORD_WIDTH),
                        ldw  -> ldw_result
                    )
                )
                lstate         := lWriteback
            }
        }
        is(lWriteback) {
            lstate                 := Mux(load_wb.ready, lIdle, lWriteback)
            load_wb.valid          := true.B
            load_wb.bits.id        := load_buf.id
            load_wb.bits.exception := Mux(!load_unalign, LA32ExceptionType.NONE.enum_no, LA32ExceptionType.ALE.enum_no)
            load_wb.bits.mispred   := false.B
            load_wb.bits.result    := Mux(!load_unalign, load_buf.rdata, load_buf.vaddr)
            // TODO: search in the store queue
        }
    }

    // store request queue
    val front_store_inst = store_queue.io.out.front_data
    val new_store_inst   = Wire(new StoreQueueEntry)
    val store_ready      = !store_queue.io.out.full
    new_store_inst.id    := io.in.bits.id
    new_store_inst.addr  := vaddr
    new_store_inst.wtype := wtype
    new_store_inst.wdata := wdata << (vaddr(1, 0) << 3.U)

    val store_req     = Wire(Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH)))
    val store_resp    = lsu_io.cache_resp
    val store_wb      = Wire(Decoupled(new BaseFuOutput))
    val store_unalign = MuxLookup(io.in.bits.optype, false.B)(
        Seq(
            sth -> vaddr(0),
            stw -> (vaddr(0) | vaddr(1))
        )
    )

    store_wb.bits.exception     := Mux(
        !DelayN(store_unalign, 1),
        LA32ExceptionType.NONE.enum_no,
        LA32ExceptionType.ALE.enum_no
    )
    store_wb.bits.mispred       := false.B
    store_wb.bits.result        := DelayN(vaddr, 1)
    store_wb.bits.id            := DelayN(io.in.bits.id, 1)
    store_wb.valid              := DelayN(LSUOpType.isStoreType(io.in.bits.optype) & io.in.valid, 1)
    store_queue.io.in.clear     := io.flush.ertn | io.flush.exception
    store_queue.io.in.enq_data  := new_store_inst
    store_queue.io.in.enq_valid := LSUOpType.isStoreType(io.in.bits.optype) & io.in.valid & !store_unalign
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

    store_req.bits.vaddr      := front_store_inst.addr
    store_req.bits.paddr      := DontCare
    store_req.bits.wdata      := front_store_inst.wdata
    store_req.bits.wtype      := front_store_inst.wtype
    store_req.bits.uncached   := DontCare
    store_req.bits.cacop_en   := false.B
    store_req.bits.cacop_func := 0.U
    store_req.bits.wr         := true.B

    val req_arb = Module(new Arbiter(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH), 2))
    req_arb.io.in(0)        <> store_req
    req_arb.io.in(1)        <> load_req
    lsu_io.data_trans.valid := req_arb.io.out.valid
    lsu_io.data_trans.vaddr := req_arb.io.out.bits.vaddr
    to_dcache               <> req_arb.io.out

    // TLB
    val pg_mode        = !lsu_io.from_csr.crmd.DA & lsu_io.from_csr.crmd.PG
    val da_mode        = lsu_io.from_csr.crmd.DA & !lsu_io.from_csr.crmd.PG
    val dmw_total_hits = lsu_io.data_trans.dmw_hits
    val dmw_hit        = dmw_total_hits.reduce(_ || _)
    val dmw_hit_idx    = OHToUInt(dmw_total_hits)
    val tlb_resp       = lsu_io.data_trans.tlb_resp
    to_dcache.bits.uncached := Mux1H(
        Seq(
            (da_mode              -> (lsu_io.from_csr.crmd.DATM === 0.U)),
            ((pg_mode & dmw_hit)  -> (lsu_io.from_csr.dwm(dmw_hit_idx).MAT === 0.U)),
            ((pg_mode & !dmw_hit) -> (tlb_resp.result.mat === 0.U))
        )
    )
    to_dcache.bits.paddr    := lsu_io.data_trans.paddr

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
