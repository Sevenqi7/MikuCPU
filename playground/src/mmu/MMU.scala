package miku

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.isa.la32._

// address transform channel
class AddrTransReq extends MkBundle {
    val valid = Bool()
    val vaddr = UInt(PADDR_WIDTH.W)
}

class AddrTransResp extends MkBundle {
    val paddr    = UInt(PADDR_WIDTH.W)
    val dmw_hits = Vec(2, Bool())
    val tlb_resp = new TLBSearchResp(TLB_NUM)
}

class AddrTransChannel extends MkBundle {
    val req  = Flipped(new AddrTransReq)
    val resp = new AddrTransResp

    def genTLBSearchReq(asid: UInt, tlb_en: Bool): TLBSearchReq = {
        val sreq = Wire(new TLBSearchReq)
        sreq.asid     := asid
        sreq.vppn     := req.vaddr(VADDR_WIDTH - 1, 13)
        sreq.odd_page := req.vaddr(12)
        sreq.valid    := req.valid & tlb_en
        sreq
    }
}

class LA32AddrTransUnit extends MkModule {
    val io = IO(new Bundle {
        val inst_trans  = new AddrTransChannel
        val data_trans  = new AddrTransChannel
        val invtlb_port = Flipped(new TLBInvalidPort(TLB_NUM))
        val tlbrd_port  = new TLBReadPort(TLB_NUM)
        val tlbwr_port  = Flipped(new TLBWritePort(TLB_NUM))
        val from_csr    = Flipped(new Bundle {
            val dmw  = Vec(2, new LA32CSR_Dmw)
            val crmd = new LA32CSR_Crmd
            val asid = new LA32CSR_Asid
        })
    })

    assert(!(io.from_csr.crmd.DA & io.from_csr.crmd.PG), "Error: DA and PG field of CRMD are set in the same time.\n")
    val da_mode = io.from_csr.crmd.DA & !io.from_csr.crmd.PG
    val pg_mode = !io.from_csr.crmd.DA & io.from_csr.crmd.PG

    val la32_tlb = Module(new MkTLB(TLB_NUM, 0))
    la32_tlb.io.inv_port   := io.invtlb_port
    la32_tlb.io.read_port  <> io.tlbrd_port
    la32_tlb.io.write_port := io.tlbwr_port

    val vaddr_r  = RegInit(VecInit(Seq.fill(2)(0.U(VADDR_WIDTH.W))))
    // address transform
    val channels = Seq(io.inst_trans, io.data_trans)
    for ((ch, idx) <- channels.zipWithIndex) {
        require(la32_tlb.SEARCH_PORT_NUM == channels.length)
        val plv      = io.from_csr.crmd.PLV
        val dmw_hits = io.from_csr.dmw.map(dmw =>
            ((dmw.PLV0 && plv === 0.U) || (dmw.PLV3 && plv === 3.U)) && (vaddr_r(idx)(31, 29) === dmw.VSEG)
        )
        la32_tlb.io.search_port(idx).req := ch.genTLBSearchReq(
            io.from_csr.asid.ASID,
            ch.req.valid
        )

        val tlb_resp = la32_tlb.io.search_port(idx).resp
        vaddr_r(idx)     := ch.req.vaddr
        ch.resp.paddr    := DEBUG_MAGICNUM.U
        ch.resp.tlb_resp := tlb_resp
        ch.resp.dmw_hits := dmw_hits

        when(da_mode) {
            ch.resp.paddr := vaddr_r(idx)
        }.elsewhen(pg_mode) {
            val dmw_hit_idx    = OHToUInt(dmw_hits)
            val dmw_paddr      = Cat(io.from_csr.dmw(dmw_hit_idx).PSEG, vaddr_r(idx)(28, 0))
            // ps == 12
            val page_4kb_paddr = Cat(tlb_resp.result.ppn, vaddr_r(idx)(11, 0))
            // ps == 21
            val page_4mb_paddr = Cat(tlb_resp.result.ppn(PADDR_WIDTH - 13, 10), vaddr_r(idx)(20, 0))
            ch.resp.paddr    := MuxCase(
                DEBUG_MAGICNUM.U,
                Seq(
                    (dmw_hits.reduce(_ || _), dmw_paddr),
                    (tlb_resp.ps === 12.U, page_4kb_paddr),
                    (tlb_resp.ps === 21.U, page_4mb_paddr)
                )
            )
            ch.resp.dmw_hits := dmw_hits
            ch.resp.tlb_resp := tlb_resp
        }
    }
}
