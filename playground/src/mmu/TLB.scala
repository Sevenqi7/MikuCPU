package miku

import chisel3._
import chisel3.util._

class TLBPageInfo extends MkBundle {
    val ppn = UInt((PADDR_WIDTH - 12).W)
    val plv = UInt(2.W)
    val mat = UInt(2.W)
    val d   = Bool()
    val v   = Bool()
}

class TLBEntry extends MkBundle {
    val vppn = UInt((VADDR_WIDTH - 13).W)
    val ps   = UInt(6.W)
    val g    = Bool()
    val asid = UInt(10.W)
    val e    = Bool()

    val page_table = Vec(2, new TLBPageInfo)
}

class TLBSearchReq extends MkBundle {
    val valid    = Bool()
    val vppn     = UInt((VADDR_WIDTH - 13).W)
    val odd_page = Bool()
    val asid     = UInt(10.W)
}

class TLBSearchResp(tlb_num: Int) extends MkBundle {
    val index  = UInt(log2Ceil(tlb_num).W)
    val found  = Bool()
    val ps     = UInt(6.W)
    val result = new TLBPageInfo
}

class TLBSearchPort(tlb_num: Int) extends MkBundle {
    val req  = Flipped(new TLBSearchReq)
    val resp = new TLBSearchResp(tlb_num)
}

class TLBReadPort(tlb_num: Int) extends MkBundle {
    val index = Input(UInt(log2Ceil(tlb_num).W))
    val rdata = Output(new TLBEntry)
}

class TLBWritePort(tlb_num: Int) extends MkBundle {
    val wen   = Bool()
    val index = UInt(log2Ceil(tlb_num).W)
    val wdata = new TLBEntry
}

class TLBInvalidPort(tlb_num: Int) extends MkBundle {
    val valid = Bool()
    val op    = UInt(5.W)
    val asid  = UInt(10.W)
    val vppn  = UInt((VADDR_WIDTH - 13).W)
}

class TLBIO(tlb_num: Int, search_port_num: Int) extends MkBundle {
    val search_port = Vec(search_port_num, new TLBSearchPort(tlb_num))
    val read_port   = new TLBReadPort(tlb_num)
    val write_port  = Flipped(new TLBWritePort(tlb_num))
    val inv_port    = Flipped(new TLBInvalidPort(tlb_num))
}

class MkTLB(tlb_num: Int, page_offset: Int) extends MkModule {
    val SEARCH_PORT_NUM = 2

    val io = IO(new TLBIO(TLB_NUM, SEARCH_PORT_NUM))

    val tlb = RegInit(VecInit(Seq.fill(tlb_num)(0.U.asTypeOf(new TLBEntry))))

    def do_invtlb(tlb_entry: TLBEntry): Unit = {
        val va_match = (((tlb_entry.ps === 12.U) && (tlb_entry.vppn === io.inv_port.vppn)) ||
            ((tlb_entry.ps === 21.U) && (tlb_entry.vppn(18, 9) === io.inv_port.vppn(18, 9))))
        val cond     = io.inv_port.valid && MuxLookup(io.inv_port.op, false.B)(
            Seq(
                0.U -> true.B,
                1.U -> true.B,
                2.U -> tlb_entry.g,
                3.U -> !tlb_entry.g,
                4.U -> (!tlb_entry.g && (tlb_entry.asid === io.inv_port.asid)),
                5.U -> ((!tlb_entry.g && (tlb_entry.asid === io.inv_port.asid)) && va_match),
                6.U -> ((tlb_entry.g || (tlb_entry.asid === io.inv_port.asid)) && va_match)
            )
        )
        when(cond) {
            tlb_entry.e := 0.B
        }
    }

    val search_req_r = RegInit(VecInit(Seq.fill(SEARCH_PORT_NUM)(0.U.asTypeOf(new TLBSearchReq))))
    search_req_r.zipWithIndex.foreach { case (req_r, index) => req_r := io.search_port(index).req }

    // tlb-search
    for ((req, resp) <- search_req_r.zip(io.search_port.map(_.resp))) {
        val total_hits = VecInit(
            (0 until tlb_num).map(i =>
                tlb(i).e && Mux(
                    (tlb(i).ps === 12.U),
                    req.vppn === tlb(i).vppn,
                    req.vppn(18, 9) === tlb(i).vppn(18, 9)
                ) && ((req.asid === tlb(i).asid) || tlb(i).g)
            )
        )
        val hit        = total_hits.reduce(_ || _)
        val hit_index  = OHToUInt(total_hits)
        // val odd_page   = VecInit((0 until tlb_num).map(i => (Mux(tlb(i).ps === 12.U, req.odd_page, req.vppn(8)))))
        val odd_page   = Mux(tlb(hit_index).ps === 12.U, req.odd_page, req.vppn(8))
        resp.index  := OHToUInt(total_hits)
        resp.found  := req.valid & hit
        resp.ps     := tlb(hit_index).ps
        resp.result := tlb(hit_index).page_table(odd_page)
    }

    // tlb-read
    io.read_port.rdata := tlb(io.read_port.index)

    // tlb-write
    when(io.write_port.wen) {
        tlb(io.write_port.index) := io.write_port.wdata
    }

    // invtlb
    tlb.foreach(do_invtlb(_))

}
