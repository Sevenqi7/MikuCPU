// import chisel3._
// import chisel3.util._
// import chisel3.experimental._
// import AXILiteDefs._

// class AXI_Arbiter(val n: Int) extends Module{
//     val in = IO(Flipped(Vec(n, new AXILiteMasterIF(32, 64))))
//     val req = IO(Flipped(Vec(n, new MyReadyValidIO)))
//     val out = IO(new AXILiteMasterIF(32, 64))

//     out <> in(n-1)
//     for(i <- n - 1 to 0 by -1){
//         req(i).ready                := 0.U
//         in(i).readAddr.ready        := 0.U
//         in(i).readData.valid        := 0.U
//         in(i).readData.bits.data    := 0x77.U       //MAGIC NUMBER FOR DEBUG
//         in(i).readData.bits.resp    := 0.U
//         in(i).writeAddr.ready       := 0.U
//         in(i).writeData.ready       := 0.U
//         in(i).writeResp.valid       := 0.U
//         in(i).writeResp.bits.resp   := 0.U
//         when(req(i).valid){
//             out <> in(i)
//             req(i).ready := 1.U
//             for(j <- i+1 to n-1){
//                 req(j).ready := 0.U
//             }
//         }
//     }
// }

// class RAMU extends Module{
//     val axi_lite = IO(Flipped(new AXILiteMasterIF(32, 64)))
//     val data_ram = Module(new sim_sram)

//     //data ram
//     data_ram.io.pc                          := 0.U

//     data_ram.io.aclk                        := clock
//     data_ram.io.aresetn                     := !reset.asBool
//     //ar
//     data_ram.io.araddr                      := axi_lite.readAddr.bits.addr
//     data_ram.io.arvalid                     := axi_lite.readAddr.valid
//     axi_lite.readAddr.ready                 := data_ram.io.arready
//     //r
//     axi_lite.readData.bits.data             := data_ram.io.rdata
//     axi_lite.readData.bits.resp             := data_ram.io.rresp
//     axi_lite.readData.valid                 := data_ram.io.rvalid
//     data_ram.io.rready                      := axi_lite.readData.ready
//     //aw
//     data_ram.io.awaddr                      := axi_lite.writeAddr.bits.addr
//     data_ram.io.awvalid                     := axi_lite.writeAddr.valid
//     axi_lite.writeAddr.ready                := data_ram.io.awready
//     //w
//     data_ram.io.wdata                       := axi_lite.writeData.bits.data
//     data_ram.io.wstrb                       := axi_lite.writeData.bits.strb
//     data_ram.io.wvalid                      := axi_lite.writeData.valid
//     axi_lite.writeData.ready                := data_ram.io.wready
//     //b
//     axi_lite.writeResp.bits.resp            := data_ram.io.bresp
//     axi_lite.writeResp.valid                := data_ram.io.bvalid
//     data_ram.io.bready                      := axi_lite.writeResp.ready

// }