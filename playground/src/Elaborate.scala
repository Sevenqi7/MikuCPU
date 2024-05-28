import circt.stage._

import chisel3._

import miku._
import miku.utils._
import miku.frontend._
import miku.backend._
import miku.issue._
import miku.isa.riscv32.MkRV32Top

object Elaborate extends App {
    def top       = new npc_core
    val generator = Seq(chisel3.stage.ChiselGeneratorAnnotation(() => top))
    (new ChiselStage).execute(args, generator :+ CIRCTTargetAnnotation(CIRCTTarget.Verilog))
}
// crmd_type
// prmd_type
// ecfg_type
// estattype
// era_ttype
// badv_type
// eentrtype
// tlbidtype
// tlbehtype
// tlbeltype
// tlbeltype
// asid_type
// pgdl_type
// pgdh_type
// pgd_ttype
// cpuidtype
// save0type
// save1type
// save2type
// save3type
// tid_ttype
// tcfg_type
// tval_type
// cntc_type
// ticlrtype
// llbcttype
// tlbretype
// dmw0_type
