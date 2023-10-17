package miku.utils

import chisel3._
import chisel3.util._

import miku._
import miku.frontend._
import miku.utils._

//A Priority AXI-bus Arbiter. It will select the least significant input bus to connect with the slaves
//!?: how to react when the raddr and waddr are same?
class PriorityAXIArbiter(num: Int, addrWidth: Int, dataWidth: Int, idBits:Int) extends MkModule{
    val io = IO(new Bundle{
        val in = Vec(num, Flipped(new AXIMasterIF(addrWidth, dataWidth, idBits)))
        val out = new AXIMasterIF(addrWidth, dataWidth, idBits)
    })

    //select the least significant input
    val rreq_set = VecInit((0 until num).map(i => io.in(i).readAddr.valid))
    val wreq_set = VecInit((0 until num).map(i => io.in(i).writeAddr.valid))

    // rreq_ongoing: set when a transaction is ongoing
    val rreq_ongoing = RegNext(MuxCase(0.B, Seq(
        (io.out.readAddr.valid & io.out.readAddr.ready, 1.B),
        (io.out.readData.valid & io.out.readAddr.valid, 0.B)
    )))

    val wreq_ongoing = RegNext(MuxCase(0.B, Seq(
        (io.out.writeAddr.valid & io.out.writeAddr.ready, 1.B),
        (io.out.writeResp.valid & io.out.writeResp.ready, 0.B)
    )))

    //src1 is the latest filtering result. src2 is the bus that has a ongoiung transaction. 
    val rreq_idx_src1 = PriorityEncoder(rreq_set)
    val rreq_idx_src2 = RegEnable(rreq_idx_src1, io.out.readAddr.valid & io.out.readAddr.ready & !rreq_ongoing)
    val selected_rreq_idx = Mux(rreq_ongoing, rreq_idx_src2, rreq_idx_src1) 

    val wreq_idx_src1 = PriorityEncoder(wreq_set)
    val wreq_idx_src2 = RegEnable(wreq_idx_src1, io.out.readAddr.valid & io.out.readAddr.ready & !wreq_ongoing)
    val selected_wreq_idx = Mux(wreq_ongoing, wreq_idx_src2, wreq_idx_src1)

    // read-after-write advernture
    val raw_adventure = selected_wreq_idx === selected_rreq_idx

    for(i <- 0 until num){  
        io.in(i).readAddr.ready := 0.B
        io.in(i).readData.valid := 0.B
        io.in(i).readData.bits.id := 0.B
        io.in(i).readData.bits.last := 0.B
        io.in(i).readData.bits.data := 0x7777.U
        io.in(i).readData.bits.resp := 0.U
        io.in(i).writeAddr.ready := 0.B
        io.in(i).writeData.ready := 0.B
        io.in(i).writeResp.valid := 0.B
        io.in(i).writeResp.bits.id := 0.U
        io.in(i).writeResp.bits.resp := 0.U
    }    
    
    io.out.readAddr <> io.in(selected_rreq_idx).readAddr
    io.out.readData <> io.in(selected_rreq_idx).readData
    io.out.writeAddr <> io.in(selected_wreq_idx).writeAddr
    io.out.writeData <> io.in(selected_wreq_idx).writeData
    io.out.writeResp <> io.in(selected_wreq_idx).writeResp
}   
