import chisel3._
import chisel3.util._
import chisel3.experimental._
import AXIDefs._

class sim_sram extends BlackBox with HasBlackBoxPath{
    val io = IO(new Bundle{
        val pc = Input(UInt(64.W))
        val aclk = Input(Clock())
        val aresetn = Input(Reset())
        //ar
        val arid    = Input(UInt(4.W))
        val araddr  = Input(UInt(32.W))
        val arlen   = Input(UInt(8.W))
        val arsize  = Input(UInt(3.W))
        val arburst = Input(UInt(2.W))
        val arlock  = Input(UInt(2.W))
        val arcache = Input(UInt(4.W))
        val arprot  = Input(UInt(3.W))
        val arvalid = Input(Bool())
        val arready = Output(Bool())
        //r
        val rid     = Output(UInt(4.W))
        val rdata   = Output(UInt(64.W))
        val rresp   = Output(UInt(2.W))
        val rlast   = Output(Bool())
        val rvalid  = Output(Bool())
        val rready  = Input(Bool())
        //aw
        val awid    = Input(UInt(4.W))
        val awaddr  = Input(UInt(32.W))
        val awlen   = Input(UInt(8.W))
        val awsize  = Input(UInt(3.W))
        val awburst = Input(UInt(2.W))
        val awlock  = Input(UInt(2.W))
        val awcache = Input(UInt(4.W))
        val awprot  = Input(UInt(3.W))
        val awvalid = Input(Bool())
        val awready = Output(Bool())
        //w
        val wid     = Input(UInt(4.W))
        val wdata   = Input(UInt(64.W)) 
        val wstrb   = Input(UInt(8.W))
        val wlast   = Input(Bool())
        val wvalid  = Input(Bool())
        val wready  = Output(Bool())
        //b
        val bid     = Output(UInt(4.W))
        val bresp   = Output(UInt(2.W))
        val bvalid  = Output(Bool())
        val bready  = Input(Bool())
    })
    addPath("/home/seven7/Documents/学业/一生一芯/ysyx-workbench/npc/playground/verilog/sim_sram.v")
}

class AXI_Arbiter(val n: Int) extends Module{
    val in = IO(Flipped(Vec(n, new AXIMasterIF(32, 64, 4))))
    val req = IO(Flipped(Vec(n, new MyReadyValidIO)))
    val out = IO(new AXIMasterIF(32, 64, 4))

    val last = RegInit(0.U((n-1).W))

    when(req(last).valid){
        for(i <- n - 1 to 0 by -1){
            req(i).ready                := 0.U
            in(i).readAddr.ready        := 0.U
            in(i).readData.bits.id      := 0.U
            in(i).readData.bits.data    := 0x77.U       //MAGIC NUMBER FOR DEBUG
            in(i).readData.bits.resp    := 0.U
            in(i).readData.bits.last    := 0.U
            in(i).readData.valid        := 0.U
            in(i).writeAddr.ready       := 0.U
            in(i).writeData.ready       := 0.U
            in(i).writeResp.bits.id     := 0.U
            in(i).writeResp.bits.resp   := 0.U
            in(i).writeResp.valid       := 0.U   
        }
        out                 <> in(last)
        out.readData.ready  := in(last).readData.ready
        out.writeResp.ready := in(last).writeResp.ready
        req(last).ready     := 1.U
    }
    .otherwise{
        out     <> in(n-1)
        out.readData.ready  := in(n-1).readData.ready
        out.writeResp.ready := in(n-1).writeResp.ready
        for(i <- n - 1 to 0 by -1){
            when(req(i).valid){             
                req(i).ready := 1.U
                for(j <- i+1 to n-1){
                    req(j).ready := 0.U
                }
                out <> in(i)
                out.readData.ready  := in(i).readData.ready
                out.writeResp.ready := in(i).writeResp.ready
                last                := i.U
            }.otherwise{
                req(i).ready                := 0.U
                in(i).readAddr.ready        := 0.U
                in(i).readData.bits.id      := 0.U
                in(i).readData.bits.data    := 0x77.U       //MAGIC NUMBER FOR DEBUG
                in(i).readData.bits.resp    := 0.U
                in(i).readData.bits.last    := 0.U
                in(i).readData.valid        := 0.U
                in(i).writeAddr.ready       := 0.U
                in(i).writeData.ready       := 0.U
                in(i).writeResp.bits.id     := 0.U
                in(i).writeResp.bits.resp   := 0.U
                in(i).writeResp.valid       := 0.U
            }
        }
    }
}

class RAMU extends Module{
    val axi      = IO(Flipped(new AXIMasterIF(32, 64, 4)))
    val axi_busy = IO(Output(UInt(2.W)))
    val data_ram = Module(new sim_sram)

    axi_busy                                := (data_ram.io.arready << 1) | data_ram.io.awready 

    //data ram
    data_ram.io.pc                          := 0.U

    data_ram.io.aclk                        := clock
    data_ram.io.aresetn                     := !reset.asBool
    //ar
    data_ram.io.arid                        := axi.readAddr.bits.id
    data_ram.io.araddr                      := axi.readAddr.bits.addr
    data_ram.io.arlen                       := axi.readAddr.bits.len
    data_ram.io.arsize                      := axi.readAddr.bits.size
    data_ram.io.arburst                     := axi.readAddr.bits.burst
    data_ram.io.arlock                      := axi.readAddr.bits.lock
    data_ram.io.arcache                     := axi.readAddr.bits.cache
    data_ram.io.arprot                      := axi.readAddr.bits.prot
    data_ram.io.arvalid                     := axi.readAddr.valid
    axi.readAddr.ready                      := data_ram.io.arready
    //r
    axi.readData.bits.id                    := data_ram.io.rid
    axi.readData.bits.data                  := data_ram.io.rdata
    axi.readData.bits.resp                  := data_ram.io.rresp
    axi.readData.bits.last                  := data_ram.io.rlast
    axi.readData.valid                      := data_ram.io.rvalid
    data_ram.io.rready                      := axi.readData.ready
    //aw
    data_ram.io.awid                        := axi.writeAddr.bits.id
    data_ram.io.awaddr                      := axi.writeAddr.bits.addr
    data_ram.io.awlen                       := axi.writeAddr.bits.len                      
    data_ram.io.awsize                      := axi.writeAddr.bits.size
    data_ram.io.awburst                     := axi.writeAddr.bits.burst
    data_ram.io.awlock                      := axi.writeAddr.bits.lock 
    data_ram.io.awcache                     := axi.writeAddr.bits.cache
    data_ram.io.awprot                      := axi.writeAddr.bits.prot
    data_ram.io.awvalid                     := axi.writeAddr.valid
    axi.writeAddr.ready                     := data_ram.io.awready
    //w
    data_ram.io.wid                         := axi.writeData.bits.id
    data_ram.io.wdata                       := axi.writeData.bits.data
    data_ram.io.wstrb                       := axi.writeData.bits.strb
    data_ram.io.wlast                       := axi.writeData.bits.last
    data_ram.io.wvalid                      := axi.writeData.valid
    axi.writeData.ready                     := data_ram.io.wready
    //b
    axi.writeResp.bits.id                   := data_ram.io.bid
    axi.writeResp.bits.resp                 := data_ram.io.bresp
    axi.writeResp.valid                     := data_ram.io.bvalid
    data_ram.io.bready                      := axi.writeResp.ready

}