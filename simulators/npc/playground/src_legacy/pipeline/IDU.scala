import chisel3._
import chisel3.util._
import InstType._
import FuSource._
import utils._
import java.awt.font.OpenType


class ID_BPU_Message extends Bundle{
    val PC    = UInt(64.W)
    val taken = Bool()
    val br_target = UInt(64.W)
    val stall = Bool()
    //debug
    val Type  = UInt(2.W)
}

class ID_EX_Message extends Bundle{
    val ALU_Data1  = Output(UInt(64.W))
    val ALU_Data2  = Output(UInt(64.W))
    val futype     = Output(UInt(1.W))
    val optype     = Output(UInt(5.W))
    val rs1_data    = Output(UInt(64.W))
    val rs1_id      = Output(UInt(5.W))
    val rs2_data    = Output(UInt(64.W))
    val rs2_id      = Output(UInt(5.W))
    val regWriteID = Output(UInt(5.W))
    val regWriteEn = Output(Bool())
    val memWriteEn = Output(Bool())
    val memReadEn  = Output(Bool())
    val csrWriteAddr    = Output(UInt(12.W))
    val csrWriteEn = Output(Bool())
    //For npc trace
    val PC         = Output(UInt(64.W))
    val Inst       = Output(UInt(32.W))
}

class IDU extends Module{
    val io = IO(new Bundle{
        val IF_to_ID_bus = Flipped(Decoupled(new IF_to_ID_Message))
        //Bus
        val ID_to_EX_bus = Decoupled(new ID_EX_Message)

        //Bypass
        //1. Reg R/W from WB
        val WB_to_ID_forward = Flipped(Decoupled(new MEM_to_ID_Message))

        //2. Data from MEM (from ex_unit in top)
        val PMEM_to_ID_forward = Flipped(Decoupled(new PMEM_to_ID_Message))
        val MEM_to_ID_forward = Flipped(Decoupled(new MEM_to_ID_Message))
        val dcache_miss       = Input(Bool())
        
        //3. ALUResult from EX
        //this signal is connected to  "ALU_Result" in EXU, not "EX_ALUResult" because the
        //later one is not immediate
        val EX_ALUResult  = Input(UInt(64.W))
        
        //4. check result of branch prediction
        val ID_to_BPU_bus = Decoupled(new ID_BPU_Message)
        
        //5. Read from CSR
        val ID_csrReadAddr  = Output(UInt(12.W))
        val ID_ecall        = Output(Bool())
        val CSR_csrReadData = Input(UInt(64.W))
        
        //For NPCTRAP
        val ID_stall = Output(Bool())
        val ID_GPR =Output(Vec(32, UInt(64.W)))
        val ID_unknown_inst = Output(Bool())
    })
    
    val ID_valid = !io.ID_stall & io.IF_to_ID_bus.valid

    //unpack bus from IFU/MEMU/WBU
    val IF_pc = Mux(ID_valid, io.IF_to_ID_bus.bits.PC, 0.U)
    val IF_Inst = io.IF_to_ID_bus.bits.Inst

    val PMEM_ALUresult   = io.PMEM_to_ID_forward.bits.ALU_result
    val PMEM_regWriteEn  = io.PMEM_to_ID_forward.bits.regWriteEn
    val PMEM_regWriteID  = io.PMEM_to_ID_forward.bits.regWriteID
    val PMEM_memReadEn   = io.PMEM_to_ID_forward.bits.memReadEn
    
    val MEM_regWriteData = io.MEM_to_ID_forward.bits.regWriteData
    val MEM_regWriteEn   = io.MEM_to_ID_forward.bits.regWriteEn
    val MEM_regWriteID   = io.MEM_to_ID_forward.bits.regWriteID

    val WB_regWriteData  = io.WB_to_ID_forward.bits.regWriteData        
    val WB_regWriteEn    = io.WB_to_ID_forward.bits.regWriteEn
    val WB_regWriteID    = io.WB_to_ID_forward.bits.regWriteID

    //Decode
    val InstInfo = ListLookup(IF_Inst, List(0.U, 0.U, 0.U, 0.U, 0.U), RV64IInstr.table)
    val instType = Wire(UInt(4.W))
    val opType   = Wire(UInt(5.W))
    val futype   = Wire(UInt(2.W))
    
    opType          := InstInfo(4)
    instType        := InstInfo(0)
    futype          := InstInfo(1)
    
    
    //all kinds of imm
    val immI  = Wire(UInt(64.W))
    val immU  = Wire(UInt(64.W))
    val immJ  = Wire(UInt(64.W))
    val immB  = Wire(UInt(64.W))
    val immS  = Wire(UInt(64.W))
    val shamt = Wire(UInt(6.W))
    

    immI := SEXT(IF_Inst(31, 20), 12)
    immU := SEXT(IF_Inst(31, 12), 20) << 12
    immS := (SEXT(IF_Inst(31, 25), 7) << 5) | IF_Inst(11, 7)
    immJ := SEXT(IF_Inst(30, 21) | (IF_Inst(20) << 10) | (IF_Inst(19, 12) << 11) | (IF_Inst(31) << 19), 20)
    immB := SEXT((IF_Inst(31) << 11) | (IF_Inst(30, 25) << 4) | IF_Inst(11, 8) | (IF_Inst(7 ,7) << 10), 12)
    shamt := IF_Inst(25, 20)
    
    
    //GPR
    
    val GPR = RegInit(VecInit(Seq.fill(32)(0.U(64.W))))
    val rs1 = Wire(UInt(5.W))
    val rs2 = Wire(UInt(5.W))
    val rd  = Wire(UInt(5.W))
    
    val regWriteEn = Wire(Bool())
    val memWriteEn = Wire(Bool()) 
    val memReadEn =  Wire(Bool())
    
    val rs1_data = Wire(UInt(64.W))
    val rs2_data = Wire(UInt(64.W))
    
    rd := IF_Inst(11, 7)
    rs1 := IF_Inst(19, 15)
    rs2 := IF_Inst(24, 20)
    
    rs1_data := MuxCase(GPR(rs1), Seq(
        ((rs1 === 0.U)                                          ,                 0.U),
        (io.ID_to_EX_bus.valid && (io.ID_to_EX_bus.bits.regWriteID  === rs1) && io.ID_to_EX_bus.bits.regWriteEn , io.EX_ALUResult),
        (io.PMEM_to_ID_forward.valid && (PMEM_regWriteID === rs1) && PMEM_regWriteEn, PMEM_ALUresult),
        (io.MEM_to_ID_forward.valid && (MEM_regWriteID === rs1) && MEM_regWriteEn, MEM_regWriteData),
        (io.WB_to_ID_forward.valid && (WB_regWriteID  === rs1) && WB_regWriteEn , WB_regWriteData )
    ))
        
    rs2_data := MuxCase(GPR(rs2), Seq(
        ((rs2 === 0.U)                                          ,                 0.U),
        (io.ID_to_EX_bus.valid && (io.ID_to_EX_bus.bits.regWriteID  === rs2) && io.ID_to_EX_bus.bits.regWriteEn, io.EX_ALUResult    ),
        (io.PMEM_to_ID_forward.valid && (PMEM_regWriteID === rs2) && PMEM_regWriteEn, PMEM_ALUresult),
        (io.MEM_to_ID_forward.valid && (MEM_regWriteID === rs2) && MEM_regWriteEn, MEM_regWriteData),
        (io.WB_to_ID_forward.valid && (WB_regWriteID  === rs2) && WB_regWriteEn , WB_regWriteData ),
    ))
            
    when(WB_regWriteEn && WB_regWriteID =/= 0.U && io.WB_to_ID_forward.valid)
    {
        GPR(WB_regWriteID) := WB_regWriteData
    }
    
    io.ID_GPR := GPR
    
    //Analyse the operation
    val src1 = Wire(UInt(3.W)) 
    val src2 = Wire(UInt(3.W))
    val imm  = Wire(UInt(64.W))
    
    src1 := InstInfo(2) 
    src2 := InstInfo(3)
    
    val ALU_Data1 = Wire(UInt(64.W))
    val ALU_Data2 = Wire(UInt(64.W))
    val csr_data  = io.CSR_csrReadData
    
    
    imm := MuxCase(0.U, Seq(
        (instType === TYPE_I, immI),
        (instType === TYPE_B, immB),
        (instType === TYPE_U, immU),
        (instType === TYPE_S, immS)
    ))
        
    ALU_Data1 := MuxCase(0.U, Seq(
        (src1 === ZERO, 0.U     ),
        (src1 === PC  , IF_pc   ),
        (src1 === RS1 , rs1_data),
        (src1 === NPC , IF_pc+4.U)
    ))
            
    ALU_Data2 := MuxCase(0.U, Seq(
        (src2 === ZERO  , 0.U      ),
        (src2 === PC    , IF_pc    ),
        (src2 === RS2   , rs2_data ),
        (src2 === IMM   , imm      ),
        (src2 === SHAMT , shamt    ),
        (src2 === CSR   , csr_data )
    ))
        
    regWriteEn := (instType === TYPE_R) || (instType === TYPE_I) || (instType === TYPE_U) || (instType === TYPE_J) || (instType === TYPE_E)
    memWriteEn := (instType === TYPE_S)
    memReadEn  := (instType === TYPE_I  && futype === FuType.lsu)

    io.ID_ecall         := opType === OpType.OP_ECALL
    io.ID_csrReadAddr   := MuxCase(immI, Seq(
                            (opType === OpType.OP_ECALL, 0x305.U),
                            (opType === OpType.OP_MRET , 0x341.U)
                        ))

    val load_use_stall      = Wire(Bool())
    val csr_stall           = Wire(Bool())
    val dcache_miss_stall   = ((MEM_regWriteID === rs2 || MEM_regWriteID === rs1) 
                              && MEM_regWriteEn && io.dcache_miss)
    val csrWriteEn          = instType === TYPE_E | io.ID_ecall
    val csrWriteAddr        = Mux(io.ID_ecall, 0x341.U, immI)
    val flush = reset.asBool | load_use_stall  | !io.IF_to_ID_bus.valid | csr_stall
    io.ID_stall := load_use_stall | csr_stall | dcache_miss_stall


    regConnectWithStall(io.ID_to_EX_bus.bits.PC             , IF_pc                     , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.Inst           , IF_Inst                   , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.ALU_Data1      , ALU_Data1                 , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.ALU_Data2      , ALU_Data2                 , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.regWriteID     , rd                        , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.regWriteEn     , regWriteEn                , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.memReadEn      , memReadEn                 , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.memWriteEn     , memWriteEn                , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.optype         , opType                    , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.futype         , futype                    , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.rs1_data       , rs1_data                  , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.rs1_id         , rs1                       , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.rs2_data       , rs2_data                  , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.rs2_id         , rs2                       , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.csrWriteEn     , csrWriteEn                , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.bits.csrWriteAddr   , csrWriteAddr              , !io.ID_to_EX_bus.ready)
    regConnectWithStall(io.ID_to_EX_bus.valid               , ID_valid                  , !io.ID_to_EX_bus.ready)
    io.IF_to_ID_bus.ready := !io.ID_stall & io.ID_to_EX_bus.ready
    io.MEM_to_ID_forward.ready := 1.U
    io.PMEM_to_ID_forward.ready := 1.U
    io.WB_to_ID_forward.ready := 1.U


    io.ID_unknown_inst := instType === 0.U && io.IF_to_ID_bus.valid

    load_use_stall := (
        (
            (src1 === RS1 || src1 === NPC || instType === TYPE_B) && 
            ((io.ID_to_EX_bus.bits.memReadEn && io.ID_to_EX_bus.bits.regWriteID === rs1 && io.ID_to_EX_bus.valid) || 
            (PMEM_memReadEn && PMEM_regWriteID === rs1 && io.PMEM_to_ID_forward.valid))
                                                            )   ||
        (
            (src2 === RS2 || futype === FuType.lsu || instType === TYPE_B) && 
            ((io.ID_to_EX_bus.bits.memReadEn && io.ID_to_EX_bus.bits.regWriteID === rs2 && io.ID_to_EX_bus.valid) || 
            (PMEM_memReadEn && PMEM_regWriteID === rs2 && io.PMEM_to_ID_forward.valid))
                                                            )
    )

    csr_stall   :=  (
        (
            (src2 === CSR) && (
                (io.ID_to_EX_bus.valid && io.ID_to_EX_bus.bits.csrWriteEn && (io.ID_to_EX_bus.bits.csrWriteAddr === io.ID_csrReadAddr)) ||
                (io.PMEM_to_ID_forward.bits.csrWriteEn && (io.PMEM_to_ID_forward.bits.csrWriteAddr === io.ID_csrReadAddr)) ||
                (io.MEM_to_ID_forward.bits.csrWriteEn && (io.MEM_to_ID_forward.bits.csrWriteAddr === io.ID_csrReadAddr)) || 
                (io.WB_to_ID_forward.bits.csrWriteEn && (io.WB_to_ID_forward.bits.csrWriteAddr === io.ID_csrReadAddr))
            )
        )
    )

    // Check branch
    val BJ_flag = Wire(Bool())
    BJ_flag := 0.B
    switch(opType){
        is (BType.BEQ)  {BJ_flag := rs1_data === rs2_data                }
        is (BType.BNE)  {BJ_flag := rs1_data =/= rs2_data                }
        is (BType.BLT)  {BJ_flag := rs1_data.asSInt < rs2_data.asSInt    }
        is (BType.BGE)  {BJ_flag := rs1_data.asSInt >= rs2_data.asSInt   }
        is (BType.BLTU) {BJ_flag := rs1_data < rs2_data                  }
        is (BType.BGEU) {BJ_flag := rs1_data >= rs2_data                 }
    }

    val br_taken = Wire(Bool())
    br_taken  := 0.U
    switch(instType){
        is (TYPE_J) {br_taken := 1.U            }
        is (TYPE_B) {br_taken := BJ_flag        }
        is (TYPE_I) {br_taken := src1 === NPC   }       //JALR
    }

    val Type = Wire(UInt(2.W))
    Type := 0.U
    switch(instType){
        is (TYPE_J) {Type := 1.U                            }
        is (TYPE_B) {Type := 2.U                            }
        is (TYPE_I) {Type := Mux(src1 === NPC, 3.U, 0.U)    }       
    }

    val pcplus4 = Wire(UInt(32.W))
    pcplus4 := IF_pc + 4.U
    io.ID_to_BPU_bus.bits.br_target := MuxCase(pcplus4, Seq(
        (instType === TYPE_J, IF_pc + immJ * 2.U),
        (instType === TYPE_B  &&  BJ_flag, IF_pc + immB * 2.U),
        (instType === TYPE_I  &&  src1 === NPC, rs1_data + immI),
        (opType   === OpType.OP_ECALL || opType === OpType.OP_MRET, io.CSR_csrReadData),
    ))

    io.ID_to_BPU_bus.bits.taken := br_taken
    io.ID_to_BPU_bus.valid      := io.IF_to_ID_bus.valid & ((instType === TYPE_J) || (instType === TYPE_B) 
                                    || (instType === TYPE_I  &&  src1 === NPC) || (opType === OpType.OP_ECALL || opType === OpType.OP_MRET)) & !io.ID_stall
    io.ID_to_BPU_bus.bits.stall := io.ID_stall
    io.ID_to_BPU_bus.bits.PC    := IF_pc
    io.ID_to_BPU_bus.bits.Type  := Type
}
            
            
