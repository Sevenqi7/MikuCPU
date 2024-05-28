package miku

import chisel3._
import chisel3.util._

import miku.isa._
import miku.utils._
import miku.issue._
import miku.isa.riscv32._

class RV32DifftestIO extends MkBundle {
    val gpr         = Vec(32, UInt(WORD_WIDTH.W))
    // val csr         = Vec(LA32CSRRegisters.csr_defns.length, UInt(32.W))
    // val csr         = new CSRVecBundle
    val commit_inst = ValidIO(new IssuedInst)
    // val is_commit_excp    = Bool()
    // val is_commit_tlbfill = Bool()
}

class npc_core extends RawModule with HasMkParams {
    val pc      = IO(Output(UInt(64.W)))
    val aclk    = IO(Input(Clock()))
    val aresetn = IO(Input(Bool()))
    val intrpt  = IO(Input(UInt(8.W)))
    // ar
    val arid    = IO(Output(UInt(4.W)))
    val araddr  = IO(Output(UInt(32.W)))
    val arlen   = IO(Output(UInt(8.W)))
    val arsize  = IO(Output(UInt(3.W)))
    val arburst = IO(Output(UInt(2.W)))
    val arlock  = IO(Output(UInt(2.W)))
    val arcache = IO(Output(UInt(4.W)))
    val arprot  = IO(Output(UInt(3.W)))
    val arvalid = IO(Output(Bool()))
    val arready = IO(Input(Bool()))
    // r
    val rid     = IO(Input(UInt(4.W)))
    val rdata   = IO(Input(UInt(64.W)))
    val rresp   = IO(Input(UInt(2.W)))
    val rlast   = IO(Input(Bool()))
    val rvalid  = IO(Input(Bool()))
    val rready  = IO(Output(Bool()))
    // aw
    val awid    = IO(Output(UInt(4.W)))
    val awaddr  = IO(Output(UInt(32.W)))
    val awlen   = IO(Output(UInt(8.W)))
    val awsize  = IO(Output(UInt(3.W)))
    val awburst = IO(Output(UInt(2.W)))
    val awlock  = IO(Output(UInt(2.W)))
    val awcache = IO(Output(UInt(4.W)))
    val awprot  = IO(Output(UInt(3.W)))
    val awvalid = IO(Output(Bool()))
    val awready = IO(Input(Bool()))
    // w
    val wid     = IO(Output(UInt(4.W)))
    val wdata   = IO(Output(UInt(64.W)))
    val wstrb   = IO(Output(UInt(8.W)))
    val wlast   = IO(Output(Bool()))
    val wvalid  = IO(Output(Bool()))
    val wready  = IO(Input(Bool()))
    // b
    val bid     = IO(Input(UInt(4.W)))
    val bresp   = IO(Input(UInt(2.W)))
    val bvalid  = IO(Input(Bool()))
    val bready  = IO(Output(Bool()))

    val mkcpu = withClockAndReset(aclk, !aresetn.asBool) {
        Module(new MkRV32Top)
    }
    // mkcpu.io.
    // ar
    arid                        := mkcpu.io.axi.readAddr.bits.id
    araddr                      := mkcpu.io.axi.readAddr.bits.addr
    arlen                       := mkcpu.io.axi.readAddr.bits.len
    arsize                      := mkcpu.io.axi.readAddr.bits.size
    arburst                     := mkcpu.io.axi.readAddr.bits.burst
    arlock                      := mkcpu.io.axi.readAddr.bits.lock
    arcache                     := mkcpu.io.axi.readAddr.bits.cache
    arprot                      := mkcpu.io.axi.readAddr.bits.prot
    arvalid                     := mkcpu.io.axi.readAddr.valid
    mkcpu.io.axi.readAddr.ready := arready

    // r
    mkcpu.io.axi.readData.bits.id   := rid
    mkcpu.io.axi.readData.bits.data := rdata
    mkcpu.io.axi.readData.bits.resp := rresp
    mkcpu.io.axi.readData.bits.last := rlast
    mkcpu.io.axi.readData.valid     := rvalid
    rready                          := mkcpu.io.axi.readData.ready

    // aw
    awid                         := mkcpu.io.axi.writeAddr.bits.id
    awaddr                       := mkcpu.io.axi.writeAddr.bits.addr
    awlen                        := mkcpu.io.axi.writeAddr.bits.len
    awsize                       := mkcpu.io.axi.writeAddr.bits.size
    awburst                      := mkcpu.io.axi.writeAddr.bits.burst
    awlock                       := mkcpu.io.axi.writeAddr.bits.lock
    awcache                      := mkcpu.io.axi.writeAddr.bits.cache
    awprot                       := mkcpu.io.axi.writeAddr.bits.prot
    awvalid                      := mkcpu.io.axi.writeAddr.valid
    mkcpu.io.axi.writeAddr.ready := awready

    // w
    wid                          := mkcpu.io.axi.writeData.bits.id
    wdata                        := mkcpu.io.axi.writeData.bits.data
    wstrb                        := mkcpu.io.axi.writeData.bits.strb
    wlast                        := mkcpu.io.axi.writeData.bits.last
    wvalid                       := mkcpu.io.axi.writeData.valid
    mkcpu.io.axi.writeData.ready := wready

    // b
    mkcpu.io.axi.writeResp.bits.id   := bid
    mkcpu.io.axi.writeResp.bits.resp := bresp
    mkcpu.io.axi.writeResp.valid     := bvalid
    bready                           := mkcpu.io.axi.writeResp.ready

    mkcpu.io.ext_int := intrpt

    val diff_info    = mkcpu.diff.get
    val cmt_inst     = diff_info.commit_inst
    val cmt_valid    = cmt_inst.valid
    val cmt_pc       = cmt_inst.bits.sbe.br_info.bits.pc
    val cmt_raw_inst = cmt_inst.bits.sbe.raw_inst.get
    pc := cmt_pc

    val DifftestInstrCommit = Module(new DifftestInstrCommit)
    val dest_reg            = Mux(
        diff_info.commit_inst.bits.sbe.decoded_inst.dest_rs1,
        diff_info.commit_inst.bits.sbe.rs1,
        diff_info.commit_inst.bits.sbe.rd
    )

    withClockAndReset(aclk, !aresetn) {
        val delay_cycles = 1
        DifftestInstrCommit.io.clock := aclk
        DifftestInstrCommit.io.index := 0.U
        DifftestInstrCommit.io.skip  := false.B
        DifftestInstrCommit.io.valid := DelayN(cmt_valid, delay_cycles)
        DifftestInstrCommit.io.pc    := DelayN(cmt_pc, delay_cycles)
        DifftestInstrCommit.io.instr := DelayN(cmt_raw_inst, delay_cycles)
        DifftestInstrCommit.io.wen   := DelayN(diff_info.commit_inst.bits.sbe.decoded_inst.regwen, delay_cycles)
        DifftestInstrCommit.io.wdest := DelayN(dest_reg, delay_cycles)
        DifftestInstrCommit.io.wdata := DelayN(diff_info.commit_inst.bits.sbe.result, delay_cycles)
    }

    val DifftestGRegState = Module(new DifftestGRegState)
    DifftestGRegState.io.clock := aclk
    DifftestGRegState.connect_gpr_vec(diff_info.gpr)

}

class DifftestInstrCommit extends BlackBox {
    val io = IO(new Bundle {
        val clock = Input(Clock())
        val index = Input(UInt(8.W))
        val valid = Input(Bool())
        val pc    = Input(UInt(64.W))
        val instr = Input(UInt(32.W))
        val skip  = Input(Bool())
        val wen   = Input(Bool())
        val wdest = Input(UInt(8.W))
        val wdata = Input(UInt(64.W))
    })
}

class DifftestGRegState extends BlackBox {
    val io = IO(new Bundle {
        val clock  = Input(Clock())
        val gpr_0  = Input(UInt(64.W))
        val gpr_1  = Input(UInt(64.W))
        val gpr_2  = Input(UInt(64.W))
        val gpr_3  = Input(UInt(64.W))
        val gpr_4  = Input(UInt(64.W))
        val gpr_5  = Input(UInt(64.W))
        val gpr_6  = Input(UInt(64.W))
        val gpr_7  = Input(UInt(64.W))
        val gpr_8  = Input(UInt(64.W))
        val gpr_9  = Input(UInt(64.W))
        val gpr_10 = Input(UInt(64.W))
        val gpr_11 = Input(UInt(64.W))
        val gpr_12 = Input(UInt(64.W))
        val gpr_13 = Input(UInt(64.W))
        val gpr_14 = Input(UInt(64.W))
        val gpr_15 = Input(UInt(64.W))
        val gpr_16 = Input(UInt(64.W))
        val gpr_17 = Input(UInt(64.W))
        val gpr_18 = Input(UInt(64.W))
        val gpr_19 = Input(UInt(64.W))
        val gpr_20 = Input(UInt(64.W))
        val gpr_21 = Input(UInt(64.W))
        val gpr_22 = Input(UInt(64.W))
        val gpr_23 = Input(UInt(64.W))
        val gpr_24 = Input(UInt(64.W))
        val gpr_25 = Input(UInt(64.W))
        val gpr_26 = Input(UInt(64.W))
        val gpr_27 = Input(UInt(64.W))
        val gpr_28 = Input(UInt(64.W))
        val gpr_29 = Input(UInt(64.W))
        val gpr_30 = Input(UInt(64.W))
        val gpr_31 = Input(UInt(64.W))
    })

    def connect_gpr_vec(gpr_vec: Vec[UInt]): Unit = {
        val port_seq =
            Seq(
                io.gpr_0,
                io.gpr_1,
                io.gpr_2,
                io.gpr_3,
                io.gpr_4,
                io.gpr_5,
                io.gpr_6,
                io.gpr_7,
                io.gpr_8,
                io.gpr_9,
                io.gpr_10,
                io.gpr_11,
                io.gpr_12,
                io.gpr_13,
                io.gpr_14,
                io.gpr_15,
                io.gpr_16,
                io.gpr_17,
                io.gpr_18,
                io.gpr_19,
                io.gpr_20,
                io.gpr_21,
                io.gpr_22,
                io.gpr_23,
                io.gpr_24,
                io.gpr_25,
                io.gpr_26,
                io.gpr_27,
                io.gpr_28,
                io.gpr_29,
                io.gpr_30,
                io.gpr_31
            )
        port_seq.zip(gpr_vec).foreach(i => i._1 := i._2)
    }
}
