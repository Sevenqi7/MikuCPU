import miku.frontend._
import miku.utils._
object Elaborate extends App {
  (new chisel3.stage.ChiselStage).execute(
    args,
    Seq(chisel3.stage.ChiselGeneratorAnnotation(
      () => new ICache(20, 4, 2, 128)
    ))
  )
}
