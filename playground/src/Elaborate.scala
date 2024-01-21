import circt.stage._

import miku.frontend._
import miku.utils._
object Elaborate extends App {
    def top       = new LA32DecoderUnit()
    val generator = Seq(chisel3.stage.ChiselGeneratorAnnotation(() => top))
    (new ChiselStage).execute(args, generator :+ CIRCTTargetAnnotation(CIRCTTarget.Verilog))
}
