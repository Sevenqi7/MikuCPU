import chisel3._
import chisel3.util._
import AXIDefs._
import utils._


class IF_to_ID_Message extends Bundle{
    val PC = UInt(64.W)
    val Inst = UInt(32.W)
}

class IFU extends Module{
    val io = IO(new Bundle{
        val IF_to_ID_bus = Decoupled(new IF_to_ID_Message)
        val bp_stall = Input(Bool())
        val bp_flush = Input(Bool())
        val bp_taken = Input(Bool())
        val bp_npc   = Input(UInt(64.W))
        //for npc to trap
        val PF_npc  = Output(UInt(64.W))
        val PF_pc   = Output(UInt(64.W))
        val PF_Inst = Output(UInt(32.W))
        val PF_valid = Output(Bool())
        val cache_hit = Output(Bool())
        val cache_state = Output(UInt(3.W))
        val cache_rvalid = Output(Bool())
        val cache_tag    = Output(UInt(21.W))
        val cache_set    = Output(UInt(2.W))
        val cache_offset = Output(UInt(4.W))
        val cache_miss_cnt = Output(UInt(32.W))
        val lineBuf      = Output(UInt(128.W))

        val axidata = Output(UInt(64.W))
    })
    val axi      = IO(new AXIMasterIF(32, 64, 4))
    val axi_req  = IO(new MyReadyValidIO)

    val pre_fetch = Module(new IF_pre_fetch)
    val flush   = Wire(Bool())

    axi                                     <> pre_fetch.axi
    axi_req                                 <> pre_fetch.axi_req

    io.PF_npc                               := pre_fetch.io.PF_npc
    io.PF_pc                                := pre_fetch.io.PF_pc
    io.PF_Inst                              := pre_fetch.io.inst
    io.PF_valid                             := pre_fetch.io.inst_valid
    io.axidata                              := pre_fetch.axi.readData.bits.data
    io.cache_hit                            := pre_fetch.io.cache_hit
    io.cache_state                          := pre_fetch.io.cache_state
    io.cache_rvalid                         := pre_fetch.io.cache_rvalid
    io.cache_tag                            := pre_fetch.io.cache_tag
    io.cache_set                            := pre_fetch.io.cache_set
    io.cache_offset                         := pre_fetch.io.cache_offset
    io.cache_miss_cnt                       := pre_fetch.io.cache_miss_cnt
    io.lineBuf                              := pre_fetch.io.lineBuf

    pre_fetch.io.IF_pc                      := io.IF_to_ID_bus.bits.PC
    pre_fetch.io.IF_valid                   := io.IF_to_ID_bus.valid
    pre_fetch.io.bp_flush                   := io.bp_flush
    pre_fetch.io.bp_npc                     := io.bp_npc
    pre_fetch.io.bp_taken                   := io.bp_taken
    pre_fetch.io.stall                      := !io.IF_to_ID_bus.ready | io.bp_stall

    flush                                   := (reset.asBool | io.bp_flush)
    //pipeline
    val IF_pc    = Wire(UInt(64.W))
    val IF_Inst  = Wire(UInt(32.W))
    val IF_valid = Wire(Bool())

    IF_pc := MuxCase(pre_fetch.io.PF_pc, Seq(
                (!IF_valid             , 0.U),
                (!io.IF_to_ID_bus.ready, io.IF_to_ID_bus.bits.PC),
                (io.bp_flush           , 0.U)
            ))

    IF_Inst := MuxCase(pre_fetch.io.inst, Seq(
                (!io.IF_to_ID_bus.ready, io.IF_to_ID_bus.bits.Inst),
                (io.bp_flush           , 0.U)
            ))
    IF_valid := MuxCase(pre_fetch.io.inst_valid, Seq(
                (!io.IF_to_ID_bus.ready, io.IF_to_ID_bus.valid),
                (io.bp_flush           , 0.U)
            ))

    regConnect(io.IF_to_ID_bus.bits.PC          , IF_pc         )
    regConnect(io.IF_to_ID_bus.bits.Inst        , IF_Inst       )
    regConnect(io.IF_to_ID_bus.valid            , IF_valid      )

}

