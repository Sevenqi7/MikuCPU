package miku

import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.issue._
import miku.backend._
import miku.frontend._

class DifftestIO extends MkBundle {
    val gpr         = Vec(32, UInt(WORD_WIDTH.W))
    val commit_inst = ValidIO(new IssuedInst)
}

class core_top extends RawModule with HasMkParams {
    val pc          = IO(Input(UInt(64.W)))
    val aclk        = IO(Input(Clock()))
    val aresetn     = IO(Input(Bool()))
    val intrpt      = IO(Input(UInt(8.W)))
    // ar
    val arid        = IO(Output(UInt(4.W)))
    val araddr      = IO(Output(UInt(32.W)))
    val arlen       = IO(Output(UInt(8.W)))
    val arsize      = IO(Output(UInt(3.W)))
    val arburst     = IO(Output(UInt(2.W)))
    val arlock      = IO(Output(UInt(2.W)))
    val arcache     = IO(Output(UInt(4.W)))
    val arprot      = IO(Output(UInt(3.W)))
    val arvalid     = IO(Output(Bool()))
    val arready     = IO(Input(Bool()))
    // r
    val rid         = IO(Input(UInt(4.W)))
    val rdata       = IO(Input(UInt(64.W)))
    val rresp       = IO(Input(UInt(2.W)))
    val rlast       = IO(Input(Bool()))
    val rvalid      = IO(Input(Bool()))
    val rready      = IO(Output(Bool()))
    // aw
    val awid        = IO(Output(UInt(4.W)))
    val awaddr      = IO(Output(UInt(32.W)))
    val awlen       = IO(Output(UInt(8.W)))
    val awsize      = IO(Output(UInt(3.W)))
    val awburst     = IO(Output(UInt(2.W)))
    val awlock      = IO(Output(UInt(2.W)))
    val awcache     = IO(Output(UInt(4.W)))
    val awprot      = IO(Output(UInt(3.W)))
    val awvalid     = IO(Output(Bool()))
    val awready     = IO(Input(Bool()))
    // w
    val wid         = IO(Output(UInt(4.W)))
    val wdata       = IO(Output(UInt(64.W)))
    val wstrb       = IO(Output(UInt(8.W)))
    val wlast       = IO(Output(Bool()))
    val wvalid      = IO(Output(Bool()))
    val wready      = IO(Input(Bool()))
    // b
    val bid         = IO(Input(UInt(4.W)))
    val bresp       = IO(Input(UInt(2.W)))
    val bvalid      = IO(Input(Bool()))
    val bready      = IO(Output(Bool()))
    // debug
    val break_point = IO(Input(Bool()))
    val infor_flag  = IO(Input(Bool()))
    val reg_num     = IO(Input(UInt(5.W)))
    val ws_valid    = IO(Output(Bool()))
    val rf_rdata    = IO(Output(UInt(32.W)))

    val debug0_wb_pc       = IO(Output(UInt(31.W)))
    val debug0_wb_rf_wen   = IO(Output(UInt(3.W)))
    val debug0_wb_rf_wnum  = IO(Output(UInt(4.W)))
    val debug0_wb_rf_wdata = IO(Output(UInt(31.W)))
    val debug0_wb_ins      = IO(Output(UInt(31.W)))

    val mkcpu =
        withClockAndReset(aclk, !aresetn.asBool) {
            Module(new MkTop)
        }

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

    if (DIFFTEST_MODE) {
        val diff_info = mkcpu.io.diff.get
        rf_rdata           := DEBUG_MAGICNUM.U
        ws_valid           := diff_info.commit_inst.valid
        debug0_wb_ins      := DEBUG_MAGICNUM.U
        debug0_wb_pc       := diff_info.commit_inst.bits.sbe.br_info.bits.pc
        debug0_wb_rf_wdata := diff_info.commit_inst.bits.sbe.result
        debug0_wb_rf_wen   := diff_info.commit_inst.bits.sbe.decoded_inst.regwen
        debug0_wb_rf_wnum  := diff_info.commit_inst.bits.sbe.rd_num

        val DifftestInstrCommit = Module(new DifftestInstrCommit)
        withClockAndReset(aclk, !aresetn) {
            val delay_cycles = 1
            DifftestInstrCommit.io.clock         := aclk
            DifftestInstrCommit.io.coreid        := 0.U
            DifftestInstrCommit.io.index         := 0.U
            DifftestInstrCommit.io.skip          := false.B
            DifftestInstrCommit.io.valid         := DelayN(diff_info.commit_inst.valid, delay_cycles)
            DifftestInstrCommit.io.pc            := DelayN(diff_info.commit_inst.bits.sbe.br_info.bits.pc, delay_cycles)
            DifftestInstrCommit.io.instr         := DelayN(diff_info.commit_inst.bits.sbe.raw_inst.get, delay_cycles)
            DifftestInstrCommit.io.is_TLBFILL    := DelayN(false.B, delay_cycles)
            DifftestInstrCommit.io.TLBFILL_index := DelayN(0.U, delay_cycles)
            DifftestInstrCommit.io.is_CNTinst    := DelayN(false.B, delay_cycles)
            DifftestInstrCommit.io.timer_64_value := DelayN(0.U, delay_cycles)
            DifftestInstrCommit.io.wen       := DelayN(diff_info.commit_inst.bits.sbe.decoded_inst.regwen, delay_cycles)
            DifftestInstrCommit.io.wdest     := DelayN(diff_info.commit_inst.bits.sbe.rd_num, delay_cycles)
            DifftestInstrCommit.io.wdata     := DelayN(diff_info.commit_inst.bits.sbe.result, delay_cycles)
            DifftestInstrCommit.io.csr_rstat := DelayN(false.B, delay_cycles)
            DifftestInstrCommit.io.csr_data  := DelayN(0.U, delay_cycles)
        }

        val DifftestGRegState = Module(new DifftestGRegState)
        DifftestGRegState.io.clock  := aclk
        DifftestGRegState.io.coreid := 0.U
        DifftestGRegState.connect_gpr_vec(diff_info.gpr)

        // CSRs is not implemented now, so we assign all of them to a magic number.
        // the only exception is the estat, with its ecode field signifies the last happned exception
        // and since there is a TLB refill exception at the start of the simulation we should mannually
        // set its value becaust TLB is also implemented yet.
        val DifftestCSRRegState = Module(new DifftestCSRRegState)
        DifftestCSRRegState.io.clock     := aclk
        DifftestCSRRegState.io.coreid    := 0.U
        DifftestCSRRegState.io.crmd      := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.prmd      := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.euen      := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.ecfg      := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.estat     := (0x3f.U << 16)
        DifftestCSRRegState.io.era       := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.badv      := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.eentry    := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.tlbidx    := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.tlbehi    := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.tlbelo0   := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.tlbelo1   := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.asid      := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.pgdl      := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.pgdh      := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.save0     := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.save1     := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.save2     := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.save3     := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.tid       := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.tcfg      := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.tval      := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.ticlr     := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.llbctl    := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.tlbrentry := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.dmw0      := DEBUG_MAGICNUM.U
        DifftestCSRRegState.io.dmw1      := DEBUG_MAGICNUM.U
    } else {
        ws_valid           := false.B
        rf_rdata           := DEBUG_MAGICNUM.U
        debug0_wb_pc       := DEBUG_MAGICNUM.U
        debug0_wb_ins      := DEBUG_MAGICNUM.U
        debug0_wb_rf_wdata := DEBUG_MAGICNUM.U
        debug0_wb_rf_wen   := false.B
        debug0_wb_rf_wnum  := 0.U
    }
}

class DifftestInstrCommit extends BlackBox {
    val io = IO(new Bundle {
        val clock          = Input(Clock())
        val coreid         = Input(UInt(8.W))
        val index          = Input(UInt(8.W))
        val valid          = Input(Bool())
        val pc             = Input(UInt(64.W))
        val instr          = Input(UInt(32.W))
        val skip           = Input(Bool())
        val is_TLBFILL     = Input(Bool())
        val TLBFILL_index  = Input(UInt(5.W))
        val is_CNTinst     = Input(Bool())
        val timer_64_value = Input(UInt(64.W))
        val wen            = Input(Bool())
        val wdest          = Input(UInt(8.W))
        val wdata          = Input(UInt(64.W))
        val csr_rstat      = Input(Bool())
        val csr_data       = Input(UInt(32.W))
    })
}

class DifftestGRegState extends BlackBox {
    val io = IO(new Bundle {
        val clock  = Input(Clock())
        val coreid = Input(UInt(8.W))
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

class DifftestCSRRegState extends BlackBox {
    val io = IO(new Bundle {
        val clock     = Input(Clock())
        val coreid    = Input(UInt(8.W))
        val crmd      = Input(UInt(63.W))
        val prmd      = Input(UInt(63.W))
        val euen      = Input(UInt(63.W))
        val ecfg      = Input(UInt(63.W))
        val estat     = Input(UInt(63.W))
        val era       = Input(UInt(63.W))
        val badv      = Input(UInt(63.W))
        val eentry    = Input(UInt(63.W))
        val tlbidx    = Input(UInt(63.W))
        val tlbehi    = Input(UInt(63.W))
        val tlbelo0   = Input(UInt(63.W))
        val tlbelo1   = Input(UInt(63.W))
        val asid      = Input(UInt(63.W))
        val pgdl      = Input(UInt(63.W))
        val pgdh      = Input(UInt(63.W))
        val save0     = Input(UInt(63.W))
        val save1     = Input(UInt(63.W))
        val save2     = Input(UInt(63.W))
        val save3     = Input(UInt(63.W))
        val tid       = Input(UInt(63.W))
        val tcfg      = Input(UInt(63.W))
        val tval      = Input(UInt(63.W))
        val ticlr     = Input(UInt(63.W))
        val llbctl    = Input(UInt(63.W))
        val tlbrentry = Input(UInt(63.W))
        val dmw0      = Input(UInt(63.W))
        val dmw1      = Input(UInt(63.W))
    })
}
