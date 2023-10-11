import chisel3._
import chisel3.tester._
import org.scalatest.flatspec._
import org.scalatest.matchers.should._

class Mux2to1Test extends AnyFlatSpec with ChiselScalatestTester with Matchers {
  behavior of "my first test"

  it should "success" in {
    test(new Mux2to1) { c =>
      c.io.a0.poke(1.U)
      c.io.a1.poke(2.U)
      c.io.s.poke(false.B) // or input '0.U', it will choose a0
      c.io.o.expect(1.U)

      c.clock.step()

      c.io.a0.poke(1.U)
      c.io.a1.poke(2.U)
      c.io.s.poke(true.B)
      c.io.o.expect(2.U)
    }
  }
}

