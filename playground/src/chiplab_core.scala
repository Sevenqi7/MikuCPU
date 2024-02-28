import chisel3._
import chisel3.util._

import miku._
import miku.utils._
import miku.frontend._
import miku.backend._

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

    ws_valid           := false.B
    rf_rdata           := DEBUG_MAGICNUM.U
    debug0_wb_pc       := DEBUG_MAGICNUM.U
    debug0_wb_ins      := DEBUG_MAGICNUM.U
    debug0_wb_rf_wdata := DEBUG_MAGICNUM.U
    debug0_wb_rf_wen   := false.B
    debug0_wb_rf_wnum  := 0.U
}
