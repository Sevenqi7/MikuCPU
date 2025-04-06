import circt.stage._

import chisel3._

import miku._
import miku.utils._
import miku.frontend._
import miku.backend._
import miku.issue._
import miku.isa.riscv32.MkRV32Top

object Elaborate extends App {
    if (args.contains("rv32")) {
        HasMkParams.setRV32()
        def top       = new npc_core
        val generator = Seq(chisel3.stage.ChiselGeneratorAnnotation(() => top))
        (new ChiselStage).execute(args, generator :+ CIRCTTargetAnnotation(CIRCTTarget.Verilog))
    } else if (args.contains("la32")) {
        HasMkParams.setLA32()
        def top       = new core_top
        val generator = Seq(chisel3.stage.ChiselGeneratorAnnotation(() => top))
        (new ChiselStage).execute(args, generator :+ CIRCTTargetAnnotation(CIRCTTarget.Verilog))
    } else {
        println("Error: Need argument \"<rv32/la32>\"")
    }
}
