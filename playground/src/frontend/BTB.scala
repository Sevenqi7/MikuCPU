package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.utils._

trait BTBConst {
    val TAG_WIDTH = 16
    val IDX_WIDTH = 10
    val WAY_NUM   = 2
}

class BTBEntry extends MkBundle with BTBConst {
    require(TAG_WIDTH <= 30)
    val tag     = UInt(TAG_WIDTH.W)
    val target  = UInt((WORD_WIDTH - 2).W)
    val is_call = Bool()
    val is_ret  = Bool()

    def init(tag: UInt, target: UInt, is_call: Bool = false.B, is_ret: Bool = false.B) = {
        this.tag     := tag
        this.target  := target
        this.is_call := is_call
        this.is_ret  := is_ret
    }
}

abstract class BTBBasedPredictor(implicit btb: MkBTB) extends BranchPredictor {
    io.resp.target := DontCare // Use function predTarget to get prediction target
    override def predTaken:  Bool = btb.io.rdata.valid & io.resp.taken
    override def predTarget: UInt = btb.io.rdata.bits.target << 2.U
}

class BTBIO extends MkBundle {
    val s1     = Flipped(ValidIO(new PCInstBundle(VADDR_WIDTH, INST_BITS)))
    val update = Flipped(ValidIO(new BranchPredictorUpdate))
    val rdata  = ValidIO(new BTBEntry)
}

class MkBTB extends MkModule with BTBConst {
    val io       = IO(new BTBIO)
    val WAY_SIZE = 2 << IDX_WIDTH

    val init_btb_entry = 0.U.asTypeOf(ValidIO(new BTBEntry))
    val btb            = Seq.fill(WAY_NUM)(Mem(WAY_SIZE, ValidIO(new BTBEntry)))
    // val btb            = RegInit(VecInit.fill(WAY_NUM, WAY_SIZE)(init_btb_entry))

    val index         = io.s1.bits.pc(IDX_WIDTH + 1, 2)
    val tag           = io.s1.bits.pc(TAG_WIDTH + IDX_WIDTH - 1, IDX_WIDTH)
    val btb_way_datas = VecInit(btb.map(_.read(index)))

    io.rdata := {
        val total_hits = btb_way_datas.map(i => (i.valid && i.bits.tag === tag))
        val hit_way    = OHToUInt(total_hits)
        val hit        = total_hits.reduce(_ | _)
        Mux(hit, btb_way_datas(hit_way), init_btb_entry)
    }

    val update_flag = io.update.valid && io.update.bits.is_taken
    when(update_flag) {
        val update_tag       = io.update.bits.pc(TAG_WIDTH - 1, IDX_WIDTH)
        val update_index     = io.update.bits.pc(IDX_WIDTH + 1, 2)
        val update_way_datas = btb.map(_.read(update_index))
        val update_hits      = update_way_datas.map(i => i.valid && (i.bits.tag === update_tag))
        val update_way       = OHToUInt(update_hits)

        val new_entry = Wire(ValidIO(new BTBEntry))
        new_entry.bits.init(update_tag, io.update.bits.target(WORD_WIDTH - 1, 2))
        new_entry.valid := true.B

        (0 until WAY_NUM).foreach { i =>
            when(i.U === update_way) {
                btb(i).write(update_index, new_entry)
            }
        }

        // btb(update_way)(index).valid       := true.B
        // btb(update_way)(index).bits.tag    := update_tag
        // btb(update_way)(index).bits.target := update_target
    }
}
