import chisel3._
import chisel3.util._
import chisel3.experimental._
import AXILiteDefs._

class sim extends BlackBox with HasBlackBoxPath{
    val io = IO(new Bundle{
        val clock = Input(Clock())
        val reset = Input(UInt(1.W))
        val IF_pc = Input(UInt(64.W))
        val GPR  = Input(Vec(32, UInt(64.W)))
        val unknown_inst_flag = Input(UInt(1.W))
        val WB_Inst = Input(UInt(32.W))
        val inst = Output(UInt(64.W))
    })
    addPath("/home/seven7/Documents/学业/一生一芯/ysyx-workbench/npc/playground/verilog/sim.v")
}

class top extends Module{
    val io = IO(new Bundle{
        val ID_npc = Output(UInt(64.W))
        val PF_npc = Output(UInt(64.W))
        val PF_pc = Output(UInt(64.W))
        val PF_axidata =Output(UInt(64.W))
        val IF_pc = Output(UInt(64.W))
        val ID_pc = Output(UInt(64.W))
        val EX_pc = Output(UInt(64.W))
        val PMEM_pc = Output(UInt(64.W))
        val WB_pc = Output(UInt(64.W))
        val WB_Inst = Output(UInt(32.W))
        val WB_RegWriteData = Output(UInt(64.W))
        val WB_RegWriteID = Output(UInt(64.W))
        val WB_valid = Output(Bool())
        // val MEM_pc = Output(UInt(64.W))
        val MEM_memReadEn    = Output(Bool())
        val MEM_RegWriteData = Output(UInt(64.W))
        val stall   = Output(Bool())

        val BTB_hit = Output(Bool())
        val BTB_wset = Output(UInt(3.W))
        val BTB_wtag = Output(UInt(16.W))
        val BTB_rset = Output(UInt(3.W))
        val BTB_rtag = Output(UInt(16.W))
        val BTB_rdata = Output(UInt(64.W))
        val BTB_wdata = Output(UInt(64.W))
        val btype_cnt  = Output(UInt(32.W))
        val jal_cnt  = Output(UInt(32.W))
        val jalr_cnt  = Output(UInt(32.W))
        val btype_fail = Output(UInt(32.W))
        val jal_fail = Output(UInt(32.W))
        val jalr_fail = Output(UInt(32.W))
        val btb_hit_cnt = Output(UInt(32.W))
        val bp_npc  = Output(UInt(64.W))
        val bp_taken = Output(Bool())
        val bp_flush = Output(Bool())
        val bht_update = Output(UInt(4.W))
        val pht_idx  = Output(UInt(4.W))
        val pht_sel  = Output(UInt(4.W))
        val pht_update = Output(UInt(2.W))
        val ras_push = Output(UInt(64.W))
        val ras_pop  = Output(UInt(64.W))
        
        val csrWriteEn = Output(Bool())
        val csrWriteAddr = Output(UInt(12.W))
        val csrWriteData = Output(UInt(64.W))
        val EX_csrWriteData = Output(UInt(64.W))
        val mstatus   = Output(UInt(64.W))
        val mtvec     = Output(UInt(64.W))
        val mepc      = Output(UInt(64.W))
        val mcause    = Output(UInt(64.W))      

        val icache_hit = Output(Bool())
        val icache_state = Output(UInt(3.W))
        val icache_rvalid = Output(Bool())
        val icache_axi_req = Output(Bool())
        val icache_tag    = Output(UInt(21.W))
        val icache_set    = Output(UInt(2.W))
        val icache_offset = Output(UInt(4.W))
        val icache_miss_cnt = Output(UInt(32.W))
        val lineBuf      = Output(UInt(128.W))

        val dcache_hit = Output(Bool())
        val dcache_miss = Output(Bool())
        val dcache_state = Output(UInt(3.W))
        val dcache_qstate = Output(UInt(3.W))
        val dcache_wstate = Output(UInt(3.W))
        val dcache_rdata  = Output(UInt(64.W))
        val dcache_maskedData = Output(UInt(64.W))
        val dcache_dataMask = Output(UInt(64.W))
        val dcache_originWdata = Output(UInt(64.W))
        val dcache_req_addr    = Output(UInt(64.W))
        val dcache_linewdata1   = Output(UInt(64.W))
        val dcache_linewdata2   = Output(UInt(64.W))
        val dcache_linerdata1   = Output(UInt(64.W))
        val dcache_linerdata2   = Output(UInt(64.W))

        val IF_Inst = Output(UInt(32.W))
        val IF_valid = Output(Bool())
        val IF_AXIREQ = Output(Bool())
        val MEM_AXIREQ = Output(Bool())

        val ID_ALU_Data1 = Output(UInt(64.W))
        val ID_ALU_Data2 = Output(UInt(64.W))
        val EX_ALU_result_pass = Output(UInt(64.W))
        val ID_Rs1Data = Output(UInt(64.W))
        val ID_Rs2Data = Output(UInt(64.W))
        val ALUResult = Output(UInt(64.W))
    })

    val bp_unit         = Module(new BPU)
    val inst_fetch_unit = Module(new IFU)
    val inst_decode_unit = Module(new IDU)
    val excute_unit = Module(new EXU)
    val pre_mem_unit = Module(new MEM_pre_stage)
    val mem_unit = Module(new MEMU)
    val wb_unit = Module(new WBU)
    val csr     = Module(new CSR)

    //for npc to trace
    io.BTB_hit   := bp_unit.io.BTB_hit
    io.BTB_rset  := bp_unit.io.BTB_rset
    io.BTB_rtag  := bp_unit.io.BTB_rtag
    io.BTB_wset  := bp_unit.io.BTB_wset
    io.BTB_wtag  := bp_unit.io.BTB_wtag
    io.BTB_rdata := bp_unit.io.BTB_rdata
    io.BTB_wdata := bp_unit.io.BTB_wdata
    io.bp_npc    := bp_unit.io.bp_npc
    io.bp_taken  := bp_unit.io.bp_taken
    io.bp_flush  := bp_unit.io.bp_flush
    io.btype_cnt := bp_unit.io.btype_cnt
    io.btype_fail := bp_unit.io.btype_fail
    io.jal_cnt   := bp_unit.io.jal_cnt
    io.jal_fail   := bp_unit.io.jal_fail
    io.jalr_cnt  := bp_unit.io.jalr_cnt
    io.jalr_fail  := bp_unit.io.jalr_fail
    io.btb_hit_cnt := bp_unit.io.hit_cnt
    io.bht_update := bp_unit.io.bht_update 
    io.pht_idx    := bp_unit.io.pht_idx
    io.pht_sel    := bp_unit.io.pht_sel
    io.pht_update := bp_unit.io.pht_update
    io.ras_push   := bp_unit.io.ras_push    
    io.ras_pop    := bp_unit.io.ras_pop
    io.csrWriteEn   := csr.io.writeEn
    io.csrWriteAddr := csr.io.writeAddr
    io.csrWriteData := csr.io.writeData
    io.EX_csrWriteData := excute_unit.io.EX_to_MEM_bus.bits.csrWriteData

    io.IF_Inst  := inst_fetch_unit.io.IF_to_ID_bus.bits.Inst
    io.IF_valid := inst_fetch_unit.io.IF_to_ID_bus.valid
    io.icache_hit := inst_fetch_unit.io.cache_hit
    io.icache_state := inst_fetch_unit.io.cache_state
    io.icache_axi_req := inst_fetch_unit.axi.readAddr.valid
    io.icache_rvalid := inst_fetch_unit.io.cache_rvalid
    io.icache_tag           := inst_fetch_unit.io.cache_tag
    io.icache_set           := inst_fetch_unit.io.cache_set
    io.icache_offset        := inst_fetch_unit.io.cache_offset
    io.icache_miss_cnt      := inst_fetch_unit.io.cache_miss_cnt
    io.lineBuf              := inst_fetch_unit.io.lineBuf
    io.dcache_hit           := pre_mem_unit.io.dcache_hit
    io.dcache_miss          := pre_mem_unit.io.dcache_miss
    io.dcache_qstate        := pre_mem_unit.io.dcache_qstate
    io.dcache_wstate        := pre_mem_unit.io.dcache_wstate
    io.dcache_state         := pre_mem_unit.io.dcache_state
    io.dcache_rdata         := pre_mem_unit.io.dcache_rdata
    io.dcache_req_addr      := pre_mem_unit.io.dcache_req_addr
    io.dcache_maskedData    := pre_mem_unit.io.dcache_maskedData
    io.dcache_dataMask      := pre_mem_unit.io.dcache_dataMask
    io.dcache_originWdata   := pre_mem_unit.io.dcache_originWdata
    io.dcache_linewdata1    := pre_mem_unit.io.dcache_linewdata(63, 0)
    io.dcache_linewdata2    := pre_mem_unit.io.dcache_linewdata(127, 64)
    io.dcache_linerdata1    := pre_mem_unit.io.dcache_linerdata(63, 0)
    io.dcache_linerdata2    := pre_mem_unit.io.dcache_linerdata(127, 64)


    io.ID_npc   := inst_decode_unit.io.ID_to_BPU_bus.bits.br_target
    io.PF_npc   := inst_fetch_unit.io.PF_npc
    io.PF_pc := inst_fetch_unit.io.PF_pc
    io.IF_pc := inst_fetch_unit.io.IF_to_ID_bus.bits.PC
    io.ID_pc := inst_decode_unit.io.ID_to_EX_bus.bits.PC
    io.EX_pc := excute_unit.io.EX_to_MEM_bus.bits.PC
    io.PMEM_pc := pre_mem_unit.io.PMEM_to_MEM_bus.bits.PC
    io.WB_pc := wb_unit.io.WB_pc
    io.WB_Inst := wb_unit.io.WB_Inst
    io.WB_RegWriteData := wb_unit.io.WB_to_ID_forward.bits.regWriteData
    io.WB_RegWriteID   := wb_unit.io.WB_to_ID_forward.bits.regWriteID
    io.WB_valid     := wb_unit.io.WB_to_ID_forward.valid
    io.MEM_memReadEn    := pre_mem_unit.io.PMEM_to_MEM_bus.bits.memReadEn
    io.MEM_RegWriteData := pre_mem_unit.io.memReadData
    
    io.ID_ALU_Data1 := inst_decode_unit.io.ID_to_EX_bus.bits.ALU_Data1
    io.ID_ALU_Data2 := inst_decode_unit.io.ID_to_EX_bus.bits.ALU_Data2
    io.ID_Rs1Data := inst_decode_unit.io.ID_to_EX_bus.bits.rs1_data
    io.ID_Rs2Data := inst_decode_unit.io.ID_to_EX_bus.bits.rs2_data
    io.EX_ALU_result_pass := excute_unit.io.EX_ALUResult_Pass
    io.ALUResult  := excute_unit.io.EX_to_MEM_bus.bits.ALU_result
    io.stall := inst_decode_unit.io.ID_stall
    
    io.mstatus := csr.io.mstatus
    io.mtvec   := csr.io.mtvec
    io.mepc    := csr.io.mepc
    io.mcause  := csr.io.mcause


    val simulate = Module(new sim)
    
    simulate.io.IF_pc                       := inst_fetch_unit.io.IF_to_ID_bus.bits.PC
    simulate.io.GPR                         := inst_decode_unit.io.ID_GPR
    simulate.io.WB_Inst                     := wb_unit.io.WB_Inst
    simulate.io.unknown_inst_flag           := inst_decode_unit.io.ID_unknown_inst

    bp_unit.io.PF_npc                       := inst_fetch_unit.io.PF_npc
    bp_unit.io.PF_pc                        := inst_fetch_unit.io.PF_pc
    bp_unit.io.PF_valid                     := inst_fetch_unit.io.PF_valid
    bp_unit.io.PF_inst                      := inst_fetch_unit.io.PF_Inst
    inst_fetch_unit.io.bp_npc               := bp_unit.io.bp_npc
    inst_fetch_unit.io.bp_taken             := bp_unit.io.bp_taken
    inst_fetch_unit.io.bp_stall             := bp_unit.io.bp_stall
    inst_fetch_unit.io.bp_flush             := bp_unit.io.bp_flush
    bp_unit.io.ID_to_BPU_bus                <> inst_decode_unit.io.ID_to_BPU_bus

    inst_decode_unit.io.IF_to_ID_bus        <> inst_fetch_unit.io.IF_to_ID_bus
    inst_decode_unit.io.WB_to_ID_forward    <> wb_unit.io.WB_to_ID_forward
    inst_decode_unit.io.PMEM_to_ID_forward  <> pre_mem_unit.io.PMEM_to_ID_forward
    inst_decode_unit.io.MEM_to_ID_forward   <> mem_unit.io.MEM_to_ID_forward
    inst_decode_unit.io.dcache_miss         := pre_mem_unit.io.dcache_miss
    inst_decode_unit.io.EX_ALUResult        := excute_unit.io.EX_ALUResult_Pass
    inst_decode_unit.io.CSR_csrReadData     := csr.io.readData

    excute_unit.io.ID_to_EX_bus             <> inst_decode_unit.io.ID_to_EX_bus
    excute_unit.io.MEM_regWriteData         := mem_unit.io.MEM_to_ID_forward.bits.regWriteData

    //PMEM
    pre_mem_unit.io.EX_to_MEM_bus           <> excute_unit.io.EX_to_MEM_bus

    mem_unit.io.PMEM_to_MEM_bus             <> pre_mem_unit.io.PMEM_to_MEM_bus
    mem_unit.io.memReadData                 := pre_mem_unit.io.memReadData
    mem_unit.io.dcache_miss                 := pre_mem_unit.io.dcache_miss

    wb_unit.io.MEM_to_WB_bus                <> mem_unit.io.MEM_to_WB_bus

    //CSR
    csr.io.ID_ecall                         := inst_decode_unit.io.ID_ecall
    csr.io.readAddr                         := inst_decode_unit.io.ID_csrReadAddr
    csr.io.writeEn                          := mem_unit.io.MEM_to_WB_bus.bits.csrWriteEn
    csr.io.writeAddr                        := mem_unit.io.MEM_to_WB_bus.bits.csrWriteAddr
    csr.io.writeData                        := mem_unit.io.MEM_to_WB_bus.bits.csrWriteData


    val ram_unit = Module(new RAMU)
    val arb = Module(new AXI_Arbiter(2))
    ram_unit.axi    <> arb.out
    arb.in(0)       <> pre_mem_unit.axi
    arb.in(1)       <> inst_fetch_unit.axi
    arb.req(0)      <> pre_mem_unit.axi_req
    arb.req(1)      <> inst_fetch_unit.axi_req
    io.PF_axidata := inst_fetch_unit.axi.readData.bits.data

    //debug
    io.MEM_AXIREQ:= arb.req(0).ready
    io.IF_AXIREQ := arb.req(1).ready
}

