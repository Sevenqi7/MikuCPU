package miku.backend

import chisel3._
import chisel3.util._

import miku._
import miku.frontend._

//a fake data cache for debugging
//it writes and returns data both immediately when receive relative request
class FakeDCache(addr_wd: Int, data_wd: Int) extends MkModule {
    val io = IO(new CacheIO(addr_wd, data_wd))

    // axi-state
    val rIdle :: rBusy :: Nil = Enum(2)
    val wIdle :: wBusy :: Nil = Enum(2)
    val sIdle :: sBusy :: Nil = Enum(2)

    val state  = RegInit(sIdle)
    val wState = RegInit(wIdle)
    val rState = RegInit(rIdle)

    val req_valid = RegEnable(io.req.valid, io.req.ready)
    val req_addr  = RegEnable(io.req.bits.addr, io.req.ready)
    val req_wr    = RegEnable(io.req.bits.wr, io.req.ready)
    val req_wstrb = RegEnable(io.req.bits.wtype, io.req.ready)
    val req_wdata = RegEnable(io.req.bits.wdata, io.req.ready)

    io.req.ready       := false.B
    io.resp.bits.done  := false.B
    io.resp.valid      := false.B
    io.resp.bits.rdata := 0x7777.U
    io.initAXIInterfaces()

    when(state === sIdle) {
        state        := sIdle
        io.req.ready := true.B
        when(req_valid) {
            io.req.ready := false.B
            when(req_wr & io.sendWriteReq(req_addr, 0.U, 0.U, 1.U)) {
                state := sBusy
            }.elsewhen(!req_wr & io.sendReadReq(req_addr, 0.U, 0.U, 1.U)) {
                state := sBusy
            }
        }
    }
        .elsewhen(state === sBusy) {
            state := sIdle
            when(req_wr & io.writeToMem(req_wstrb, 1.B, req_wdata)) {
                state             := sBusy
                io.resp.bits.done := true.B
            }.elsewhen(!req_wr) {
                val (rvalid, rlast, rdata) = io.readFromMem()
                when(rvalid & rlast) {
                    state              := sBusy
                    io.resp.bits.rdata := rdata
                    io.resp.bits.done  := true.B
                }
            }
        }

}
