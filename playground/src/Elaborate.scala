import circt.stage._

import chisel3._

import miku._
import miku.utils._
import miku.frontend._
import miku.backend._
import miku.issue._

object Elaborate extends App {
    def top       = new core_top
    val generator = Seq(chisel3.stage.ChiselGeneratorAnnotation(() => top))
    (new ChiselStage).execute(args, generator :+ CIRCTTargetAnnotation(CIRCTTarget.Verilog))
}
