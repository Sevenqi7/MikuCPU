package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.backend._
import miku.frontend._
import miku.LSUOpType._

class LSUIO extends MkBundle {
    val cache_req    = Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
    val cache_resp   = Flipped(ValidIO(new CacheRespIO(WORD_WIDTH)))
    val store_commit = Flipped(new ReadyValidBundle)
    val data_trans   = Flipped(new AddrTransChannel)
    val from_csr     = Flipped(new Bundle {
        val crmd   = new LA32CSR_Crmd
        val dwm    = Vec(2, new LA32CSR_Dmw)
        val llbctl = new LA32CSR_Llbctl
    })

    val lsu_diff =
        if (DIFFTEST_MODE) Some(new Bundle {
            val paddr = UInt(PADDR_WIDTH.W)
            val vaddr = UInt(VADDR_WIDTH.W)
            val wdata = UInt(WORD_WIDTH.W)
        })
        else None
}

class StoreQueueEntry extends MkBundle {
    val id       = UInt(TRANS_ID_BITS.W)
    val addr     = UInt(VADDR_WIDTH.W)
    val wtype    = UInt(2.W)
    val wdata    = UInt(WORD_WIDTH.W)
    val uncached = Bool()
}

class LSU extends BaseFunctionUnit {
    val lsu_io            = IO(new LSUIO)
    val io_tlb_busy_stall = IO(Input(Bool())) // from CSRBuffer

    def getWstrbFromWtype(wtype: UInt, offset: UInt): UInt = {
        ~0.U(4.W) >> (4.U - (1.U << wtype)) << offset(log2Ceil(wordBytes) - 1, 0)
    }
    val is_sc_ll = io.in.bits.optype === scw || io.in.bits.optype === llw
    val rj       = io.in.bits.operand_a
    val rd       = io.in.bits.operand_c
    val imm      = io.in.bits.operand_b
    val vaddr    = Mux(!is_sc_ll, rj + imm, rj + (imm << 2))
    val wdata    = rd
    val wtype    = io.in.bits.optype(1, 0)
    val uncached = Wire(Bool())

    val store_queue = Module(new CircularQueue(new StoreQueueEntry, 8, true))

    // LSU-DCache
    val to_dcache   = lsu_io.cache_req
    val from_dcache = lsu_io.cache_resp

    // load request bufffer

    val lIdle :: lReq :: lWait :: lWriteback :: Nil = Enum(4)
    val lstate                                      = RegInit(lIdle)

    val load_buf   = RegInit(0.U.asTypeOf(new Bundle {
        val id        = UInt(TRANS_ID_BITS.W)
        val addr      = UInt(VADDR_WIDTH.W)
        val ldtype    = LSUOpType()
        val uncached  = Bool()
        val rdata     = UInt(WORD_WIDTH.W)
        val exception = LA32ExceptionType()
        val valid     = Bool()
    }))
    val load_req   = Wire(Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH)))
    val load_resp  = lsu_io.cache_resp
    val load_ready = Wire(Bool())
    val load_vaddr = RegEnable(vaddr, lstate === lIdle)
    val load_wb    = Wire(Decoupled(new BaseFuOutput))

    // TODO: need parameterise
    val real_rdata  = Wire(UInt(32.W))
    val ldbu_result = MuxLookup(load_buf.addr(1, 0), DEBUG_MAGICNUM.U)(
        Seq(
            "b00".U -> real_rdata(7, 0),
            "b01".U -> real_rdata(15, 8),
            "b10".U -> real_rdata(23, 16),
            "b11".U -> real_rdata(31, 24)
        )
    )
    val ldhu_result = Mux(load_buf.addr(1), real_rdata(31, 16), real_rdata(15, 0))
    val ldw_result  = real_rdata

    // initialise
    load_ready          := false.B
    load_req.bits       := 0.U.asTypeOf(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH))
    load_req.valid      := false.B
    load_wb.bits        := 0.U.asTypeOf(new BaseFuOutput)
    load_wb.valid       := false.B
    load_req.bits.paddr := DontCare
    val load_unalign  = MuxLookup(load_buf.ldtype, false.B)(
        Seq(
            ldh  -> load_buf.addr(0),
            ldhu -> load_buf.addr(0),
            ldw  -> (load_buf.addr(0) | load_buf.addr(1))
        )
    )
    val load_unmatch  = Wire(Bool())
    val load_page_pi  = Wire(Bool())
    val load_page_inv = Wire(Bool())
    val load_excp     = load_unalign | load_unmatch | load_page_inv | load_page_pi

    // search in store queue
    val stq_items      = store_queue.io.out.element_vec.get
    val stq_total_hits =
        stq_items.map(st => st.valid && st.bits.addr(VADDR_WIDTH - 1, 2) === load_buf.addr(VADDR_WIDTH - 1, 2))
    val stq_hit_en     = (lstate === lReq) && (RegNext(lstate) =/= lReq)
    val stq_hit        = RegEnable(stq_total_hits.reduce(_ || _), stq_hit_en)
    val stq_hit_item   = RegEnable(stq_items(OHToUInt(stq_total_hits)), stq_hit_en)
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
            load_ready := !io_tlb_busy_stall
            when(io.in.valid & io.in.ready & LSUOpType.isLoadType(io.in.bits.optype)) {
                load_buf.id        := io.in.bits.id
                load_buf.addr      := vaddr
                load_buf.ldtype    := io.in.bits.optype
                load_buf.valid     := true.B
                load_buf.exception := LA32ExceptionType.NONE.enum_no
                lstate             := lReq
            }
        }
        is(lReq) {
            val paddr_v = (RegNext(lstate) =/= lReq)
            load_req.valid         := !load_unalign
            load_req.bits.vaddr    := load_buf.addr
            load_req.bits.wr       := false.B
            load_req.bits.wtype    := 0.U
            load_req.bits.wdata    := 0.U
            load_req.bits.uncached := Mux(paddr_v, uncached, load_buf.uncached)
            when(load_req.ready) {
                lstate := lWait
            }
            when(paddr_v) {
                load_buf.addr     := lsu_io.data_trans.paddr
                load_buf.uncached := uncached
                when(load_excp) {
                    load_buf.addr      := load_buf.addr
                    lstate             := lWriteback
                    load_buf.exception := MuxCase(
                        LA32ExceptionType.INT.enum_no, // error
                        Seq(
                            load_unalign  -> LA32ExceptionType.ALE.enum_no,
                            load_unmatch  -> LA32ExceptionType.TLBR.enum_no,
                            load_page_inv -> LA32ExceptionType.PIL.enum_no,
                            load_page_pi  -> LA32ExceptionType.PPI.enum_no
                        )
                    )
                }
            }
        }
        is(lWait) {
            load_req.bits.paddr := load_buf.addr
            when(load_resp.valid & load_resp.bits.done) { // TODO: parameterise this state by cache parameters
                load_buf.rdata := MuxLookup(load_buf.ldtype, DEBUG_MAGICNUM.U)(
                    Seq(
                        ldb  -> SEXT(ldbu_result, WORD_WIDTH),
                        ldbu -> UEXT(ldbu_result, WORD_WIDTH),
                        ldh  -> SEXT(ldhu_result, WORD_WIDTH),
                        ldhu -> UEXT(ldhu_result, WORD_WIDTH),
                        ldw  -> ldw_result,
                        llw  -> ldw_result
                    )
                )
                lstate         := lWriteback
            }
        }
        is(lWriteback) {
            val badv_cond = RegNext(load_excp)
            lstate                 := Mux(load_wb.ready, lIdle, lWriteback)
            load_wb.valid          := true.B
            load_wb.bits.id        := load_buf.id
            load_wb.bits.exception := load_buf.exception
            load_wb.bits.mispred   := false.B
            load_wb.bits.result    := Mux(badv_cond, load_buf.addr, load_buf.rdata)
            // TODO: search in the store queue
        }
    }

    // store request queue
    val store_req        = Wire(Decoupled(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH)))
    val store_resp       = lsu_io.cache_resp
    val store_wb         = Wire(Decoupled(new BaseFuOutput))
    val store_unalign    = MuxLookup(io.in.bits.optype, false.B)(
        Seq(
            sth -> vaddr(0),
            stw -> (vaddr(0) | vaddr(1))
        )
    )
    val store_unmatch    = Wire(Bool())
    val store_page_inv   = Wire(Bool())
    val store_page_pi    = Wire(Bool())
    val store_page_modfy = Wire(Bool())

    val front_store_inst = store_queue.io.out.front_data
    val new_store_inst   = Wire(new StoreQueueEntry)
    val store_ready      = !store_queue.io.out.full & !io_tlb_busy_stall
    new_store_inst.id       := DelayN(io.in.bits.id, 1)
    new_store_inst.addr     := lsu_io.data_trans.paddr
    new_store_inst.uncached := uncached
    new_store_inst.wtype    := DelayN(wtype, 1)
    new_store_inst.wdata    := DelayN(wdata << (vaddr(1, 0) << 3.U), 1)

    store_wb.bits.exception := MuxCase(
        LA32ExceptionType.NONE.enum_no,
        Seq(
            DelayN(store_unalign, 1) -> LA32ExceptionType.ALE.enum_no,
            store_unmatch            -> LA32ExceptionType.TLBR.enum_no,
            store_page_inv           -> LA32ExceptionType.PIS.enum_no,
            store_page_pi            -> LA32ExceptionType.PPI.enum_no,
            store_page_modfy         -> LA32ExceptionType.PME.enum_no
        )
    )
    val store_en =
        LSUOpType.isStoreType(io.in.bits.optype) & io.in.valid & io.in.ready & !(io.flush.ertn | io.flush.exception)

    store_wb.bits.mispred       := false.B
    store_wb.bits.result        := DelayN(vaddr, 1)
    store_wb.bits.id            := DelayN(io.in.bits.id, 1)
    store_wb.valid              := DelayN(store_en, 1)
    store_queue.io.in.clear     := io.flush.ertn | io.flush.exception
    store_queue.io.in.enq_data  := new_store_inst
    store_queue.io.in.enq_valid := DelayN(store_en, 1)
    store_queue.io.in.deq_valid := lsu_io.store_commit.valid & lsu_io.store_commit.ready

    lsu_io.store_commit.ready := store_req.ready

    // store-commit
    val sIdle :: sReq :: Nil = Enum(2)
    val sstate               = RegInit(sIdle)

    val is_commit_sc = front_store_inst.wtype === scw
    store_req.valid           := false.B
    when(lsu_io.store_commit.valid) {
        val llbit = lsu_io.from_csr.llbctl.ROLLB
        assert(!store_queue.io.out.empty)
        store_req.valid := Mux(!is_commit_sc, true.B, llbit)
    }
    store_req.bits.vaddr      := front_store_inst.addr
    store_req.bits.paddr      := DelayN(front_store_inst.addr, 1)
    store_req.bits.wdata      := front_store_inst.wdata
    store_req.bits.wtype      := Mux(!is_commit_sc, front_store_inst.wtype, stw)
    store_req.bits.uncached   := front_store_inst.uncached
    store_req.bits.cacop_en   := false.B
    store_req.bits.cacop_func := 0.U
    store_req.bits.wr         := true.B

    val req_arb = Module(new Arbiter(new CacheReqIO(VADDR_WIDTH, WORD_WIDTH), 2))
    req_arb.io.in(0)             <> store_req
    req_arb.io.in(1)             <> load_req
    lsu_io.data_trans.valid      := io.in.valid
    lsu_io.data_trans.vaddr      := vaddr
    lsu_io.data_trans.tlbsrch_en := false.B
    to_dcache                    <> req_arb.io.out
    to_dcache.bits.paddr         := req_arb.io.in(DelayN(req_arb.io.chosen, 1)).bits.paddr

    // TLB
    val pg_mode        = !lsu_io.from_csr.crmd.DA & lsu_io.from_csr.crmd.PG
    val da_mode        = lsu_io.from_csr.crmd.DA & !lsu_io.from_csr.crmd.PG
    val dmw_total_hits = lsu_io.data_trans.dmw_hits
    val dmw_hit        = dmw_total_hits.reduce(_ || _)
    val dmw_hit_idx    = OHToUInt(dmw_total_hits)
    val tlb_resp       = lsu_io.data_trans.tlb_resp
    val crmd_plv       = lsu_io.from_csr.crmd.PLV

    load_unmatch  := pg_mode && (lstate === lReq) && !dmw_hit && !tlb_resp.found
    load_page_inv := pg_mode && (lstate === lReq) && !dmw_hit && tlb_resp.found && !tlb_resp.result.v
    load_page_pi := pg_mode && (lstate === lReq) && !dmw_hit && tlb_resp.found && tlb_resp.result.v && (crmd_plv > tlb_resp.result.plv)
    store_unmatch  := pg_mode && store_wb.valid && !dmw_hit && !tlb_resp.found
    store_page_inv := pg_mode && store_wb.valid && !dmw_hit && tlb_resp.found && !tlb_resp.result.v
    store_page_pi := pg_mode && store_wb.valid && !dmw_hit && tlb_resp.found && tlb_resp.result.v && (crmd_plv > tlb_resp.result.plv)
    store_page_modfy := pg_mode && store_wb.valid && !dmw_hit && tlb_resp.found && tlb_resp.result.v && (crmd_plv <= tlb_resp.result.plv) && !tlb_resp.result.d

    uncached := Mux1H(
        Seq(
            (da_mode              -> (lsu_io.from_csr.crmd.DATM === 0.U)),
            ((pg_mode & dmw_hit)  -> (lsu_io.from_csr.dwm(dmw_hit_idx).MAT === 0.U)),
            ((pg_mode & !dmw_hit) -> (tlb_resp.result.mat === 0.U))
        )
    )

    val wb_arb = Module(new Arbiter(new BaseFuOutput, 2))
    wb_arb.io.in(0) <> store_wb
    wb_arb.io.in(1) <> load_wb
    if (DIFFTEST_MODE) {
        val store_vaddr = store_wb.bits.result
        lsu_io.lsu_diff.get.paddr := Mux(store_wb.valid, lsu_io.data_trans.paddr, load_buf.addr)
        lsu_io.lsu_diff.get.vaddr := Mux(store_wb.valid, store_vaddr, load_vaddr)
        lsu_io.lsu_diff.get.wdata := MuxLookup(new_store_inst.wtype, DEBUG_MAGICNUM.U)(
            Seq(
                scw -> new_store_inst.wdata,
                stw -> new_store_inst.wdata,
                sth -> (Mux(store_vaddr(1), new_store_inst.wdata, new_store_inst.wdata(15, 0))),
                stb -> (new_store_inst.wdata & (0xffffffffL.U >> ((3.U - store_vaddr(1, 0)) << 3.U)))
            )
        )

    }

    io.out <> wb_arb.io.out

    io.in.ready := MuxCase(
        false.B,
        Seq(
            (LSUOpType.isLoadType(io.in.bits.optype), load_ready),
            (LSUOpType.isStoreType(io.in.bits.optype), store_ready)
        )
    )
}
