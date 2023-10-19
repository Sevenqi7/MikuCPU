import chisel3._

import miku.frontend._
import miku.utils._
object Elaborate extends App {
  (new chisel3.stage.ChiselStage).execute(
    args,
    Seq(chisel3.stage.ChiselGeneratorAnnotation(
      () => new CircularQueue(UInt(2.W), 5)
    ))
  )
}
