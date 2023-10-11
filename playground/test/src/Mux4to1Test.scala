import chisel3._
import chisel3.tester._
import org.scalatest.flatspec._
import org.scalatest.matchers.should._

class Mux4to1Test extends AnyFlatSpec with ChiselScalatestTester with Matchers {
  behavior of "my first test"

  it should "success" in {
    test(new Mux4to1) { c =>
      c.io.a0.poke(0.U)
      c.io.a1.poke(1.U)
      c.io.a2.poke(2.U)
      c.io.a3.poke(3.U)

      for (i <- 0 to 3) { // to: [0,3]; until [0,3)
//        println("i = " + i)
        c.io.s.poke(i.U)
        c.io.o.expect(i.U)
        c.clock.step()
      }

//      c.io.s.poke("b00".U)
//      c.io.o.expect(1.U)
//      c.clock.step()
//
//      c.io.s.poke("b01".U)
//      c.io.o.expect(2.U)
//      c.clock.step()
//
//      c.io.s.poke("b10".U)
//      c.io.o.expect(3.U)
//      c.clock.step()
//
//      c.io.s.poke("b11".U)
//      c.io.o.expect(4.U)
//      c.clock.step()
    }
  }

}

