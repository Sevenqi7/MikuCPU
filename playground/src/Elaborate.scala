import chisel3._
import chisel3.util.BitPat

import miku.frontend._
import miku.utils._
object Elaborate extends App {
 	(new chisel3.stage.ChiselStage).execute(
    args,
    Seq(chisel3.stage.ChiselGeneratorAnnotation(
      () => new LA32DecoderUnit
    ))
  )
}
