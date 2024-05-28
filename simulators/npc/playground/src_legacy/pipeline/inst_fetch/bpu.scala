import chisel3._
import chisel3.util._
import BType._

object PH_State{
    val ST  = "b11".U          //strongly taken
    val WT  = "b01".U          //weakly taken
    val WNT = "b00".U          //weakly not taken
    val SNT = "b10".U          //strongly not taken
}

class BPU_Cache(tagWidth: Int, nrSets: Int, nrLines: Int) extends Module{
    val io = IO(new Bundle{
        val raddr = Input(UInt(64.W))
        val waddr = Input(UInt(64.W))
        val writeData = Input(UInt(64.W))
        val writeEn   = Input(Bool())
        val readData = Output(UInt(64.W))
        val hit  = Output(Bool())

        //debug
        val wset = Output(UInt(log2Ceil(nrSets).W))
        val wtag = Output(UInt(tagWidth.W))
        val rset = Output(UInt(log2Ceil(nrSets).W))
        val rtag = Output(UInt(tagWidth.W))
    })

    val cacheline = Wire(new CacheLine(tagWidth, 64))
    cacheline.tag := 0.U
    cacheline.data := 0.U
    cacheline.valid := 0.U
    val cache = RegInit(VecInit.fill(nrSets, nrLines)(cacheline))

    val setWidth = log2Ceil(nrSets)
    val lineWidth = log2Ceil(nrLines)

    val rtag = io.raddr(tagWidth + setWidth - 1, setWidth)
    val rset = io.raddr(setWidth - 1, 0)

    //read
    io.readData := 0x7777.U       //Magic number, for debug
    io.hit := 0.U
    for(i <- 0 until nrLines-1){
        when(rtag === cache(rset)(i).tag && cache(rset)(i).valid){
            io.hit := 1.U
            io.readData := cache(rset)(i).data
        }
    }

    //write
    val wtag = io.waddr(tagWidth + setWidth - 1, setWidth)
    val wset = io.waddr(setWidth - 1, 0)
    val writeIDX = Wire(UInt(lineWidth.W))
    val writeHit = Wire(Bool())
    writeIDX := 0.U
    writeHit := 0.U
    for(i <- 0 until nrLines-1){
        when(!cache(wset)(i).valid){
            writeIDX := i.U
            writeHit := 1.U
        }
    }
    for(i <- 0 until nrLines-1){
        when(wtag === cache(wset)(i).tag){
            writeIDX := i.U
            writeHit := 1.U
        }
    }
    when(io.writeEn){
        when(!writeHit){
            writeIDX := random.LFSR(16)(lineWidth, 0)
        }
        cache(wset)(writeIDX).valid := 1.U
        cache(wset)(writeIDX).tag   := wtag
        cache(wset)(writeIDX).data  := io.writeData
    }
    
    io.wset := wset
    io.rset := rset
    io.wtag := wtag
    io.rtag := rtag
}

class BPU extends Module{
    val io = IO(new Bundle{
        val PF_npc   = Input(UInt(64.W))
        val PF_pc    = Input(UInt(64.W))
        val PF_inst  = Input(UInt(32.W))
        val PF_valid = Input(Bool())
        val bp_stall = Output(Bool())
        val bp_taken = Output(Bool())
        val bp_flush = Output(Bool())

        val ID_to_BPU_bus = Flipped(Decoupled(new ID_BPU_Message))
        val bp_npc     = Output(UInt(64.W))

        //for debug
        val BTB_wset = Output(UInt(3.W))
        val BTB_wtag = Output(UInt(16.W))
        val BTB_rset = Output(UInt(3.W))
        val BTB_rtag = Output(UInt(16.W))
        val BTB_rdata = Output(UInt(64.W))
        val BTB_wdata = Output(UInt(64.W))

        val BTB_hit   = Output(Bool())
        val btype_cnt = Output(UInt(32.W))
        val jal_cnt = Output(UInt(32.W))
        val jalr_cnt = Output(UInt(32.W))
        val btype_fail = Output(UInt(32.W))
        val jal_fail = Output(UInt(32.W))
        val jalr_fail = Output(UInt(32.W))
        val hit_cnt = Output(UInt(32.W))
        val bht_update = Output(UInt(4.W))
        val pht_idx  = Output(UInt(4.W))
        val pht_sel  = Output(UInt(4.W))
        val pht_update = Output(UInt(2.W))
        val ras_pop  = Output(UInt(64.W))
        val ras_push = Output(UInt(64.W))
    })

    def hash(x: UInt): UInt = {
        val ret = Wire(UInt(8.W))
        val x1 = x(31, 16) ^ x(15, 0)
        ret := x1(15, 8) ^ x1(7, 0)
        ret
    }

    
    //unpack bus from IDU
    val ID_pc = io.ID_to_BPU_bus.bits.PC
    val ID_br_taken = io.ID_to_BPU_bus.bits.taken
    io.ID_to_BPU_bus.ready := 1.U

    //fast decode
    val opcode = io.PF_inst(6, 0)
    val B_type = Wire(Bool())
    val J_type = Wire(Bool())
    val JAL    = Wire(Bool())
    val JALR   = Wire(Bool())
 
    JALR     := (opcode === "b1100111".U)
    JAL      := (opcode === "b1101111".U)

    B_type  := (opcode === "b1100011".U)
    J_type  :=  JAL | JALR


    val bp_taken = Wire(Bool())
    val bp_target = RegInit(0.U(64.W))

    when((B_type | J_type) & !io.ID_to_BPU_bus.bits.stall){
        bp_target := io.bp_npc
    }    
    
    //parameter
    val nrPHTs = 16
    val nrBHTs = 256
    val bhtWidth = 4
    val bhtIdxWidth = log2Ceil(nrBHTs)
    val phtIdxWidth = log2Ceil(nrPHTs)
    
    //parameter end
    val BHT = RegInit(VecInit(Seq.fill(nrBHTs)(0.U(bhtWidth.W))))
    val PHT = RegInit(VecInit.fill(nrPHTs, scala.math.pow(2, bhtWidth).toInt)("b01".U(2.W)))
    val BTB = Module(new BPU_Cache(16, 8, 8))
    val RAS = Module(new LIFO(UInt(64.W), 16))
    
    //BTB
    BTB.io.raddr      := io.PF_pc
    BTB.io.waddr      := ID_pc
    BTB.io.writeEn    := ID_br_taken & io.ID_to_BPU_bus.valid
    BTB.io.writeData  := io.ID_to_BPU_bus.bits.br_target 

    //debug
    io.BTB_rtag       := BTB.io.rtag
    io.BTB_rset       := BTB.io.rset
    io.BTB_rdata      := BTB.io.readData
    io.BTB_hit        := BTB.io.hit
    io.BTB_wtag       := BTB.io.wtag
    io.BTB_wset       := BTB.io.wset
    io.BTB_wdata      := Mux(ID_br_taken, io.ID_to_BPU_bus.bits.br_target, 0.U)

    
    
    //BHT & PHT
    //1.prediction
    val bht_idx = hash(io.PF_pc)
    val pht_idx = io.PF_pc(phtIdxWidth-1, 0)
    val pht_sel = BHT(bht_idx) ^ io.PF_pc(3, 0)
    
    bp_taken     := 0.U
    when(io.PF_valid & (B_type | J_type)){
        when(BTB.io.hit){
            bp_taken := Mux(J_type, 1.U, PHT(pht_idx)(pht_sel))
        }
        .elsewhen(J_type){
            bp_taken := 1.U
        }
    }
    
    
    //2.update
    val up_bht_idx = hash(ID_pc)
    // val up_bht_idx = ID_pc(phtIdxWidth + bhtIdxWidth -1, phtIdxWidth)
    val up_pht_idx = ID_pc(phtIdxWidth-1, 0)
    val up_pht_sel = BHT(up_bht_idx) ^ ID_pc(3, 0)
    when(io.ID_to_BPU_bus.valid & io.ID_to_BPU_bus.bits.Type === 2.U){
        
        PHT(up_pht_idx)(up_pht_sel) := MuxCase(PHT(up_pht_idx)(up_pht_sel), Seq(
            (PHT(up_pht_idx)(up_pht_sel) === PH_State.ST  && !ID_br_taken, PH_State.WT ),
            (PHT(up_pht_idx)(up_pht_sel) === PH_State.WT  && !ID_br_taken, PH_State.WNT),
            (PHT(up_pht_idx)(up_pht_sel) === PH_State.WT  &&  ID_br_taken, PH_State.ST ),
            (PHT(up_pht_idx)(up_pht_sel) === PH_State.WNT &&  ID_br_taken, PH_State.WT ),
            (PHT(up_pht_idx)(up_pht_sel) === PH_State.WNT && !ID_br_taken, PH_State.SNT),
            (PHT(up_bht_idx)(up_pht_sel) === PH_State.SNT &&  ID_br_taken, PH_State.SNT)
            ))
        BHT(up_bht_idx) := ((BHT(up_bht_idx) << 1) + ID_br_taken)(bhtWidth-1, 0)
    }
    io.bht_update := ((BHT(up_bht_idx) << 1) + ID_br_taken)(bhtWidth-1, 0)
    io.pht_update := MuxCase(PHT(up_pht_idx)(up_pht_sel), Seq(
        (PHT(up_pht_idx)(up_pht_sel) === PH_State.ST  && !ID_br_taken, PH_State.WT ),
        (PHT(up_pht_idx)(up_pht_sel) === PH_State.WT  && !ID_br_taken, PH_State.WNT),
        (PHT(up_pht_idx)(up_pht_sel) === PH_State.WT  &&  ID_br_taken, PH_State.ST ),
        (PHT(up_pht_idx)(up_pht_sel) === PH_State.WNT &&  ID_br_taken, PH_State.WT ),
        (PHT(up_pht_idx)(up_pht_sel) === PH_State.WNT && !ID_br_taken, PH_State.SNT),
        (PHT(up_bht_idx)(up_pht_sel) === PH_State.SNT &&  ID_br_taken, PH_State.SNT)
    ))
    io.pht_idx := Mux(io.ID_to_BPU_bus.valid, up_pht_idx, 0.U)
    io.pht_sel := Mux(io.ID_to_BPU_bus.valid, up_pht_sel, 0.U)
    
            
    //RAS
    val rs1 = io.PF_inst(19, 15)
    val rs2 = io.PF_inst(24, 20)
    val rd  = io.PF_inst(11, 7)

    val pushEn = (JAL & (rd === 1.U || rd === 5.U)) | (JALR & (rd === 1.U || rd === 5.U) & (rs1 === rd))
    val popEn  = JALR & (
                            (rs1 === 1.U || rs1 === 5.U) & (rd =/= 1.U && rd =/= 5.U)
                        
                        )
    RAS.io.pushEn := pushEn & io.PF_valid
    RAS.io.popEn  := popEn & io.PF_valid

    // RAS.io.pushEn := call & io.PF_valid
    RAS.io.push   := io.PF_pc + 4.U
    // RAS.io.popEn  := ret  & io.PF_valid

    io.ras_pop    := RAS.io.pop
    io.ras_push   := Mux(RAS.io.pushEn, RAS.io.push, 0.U)
            
    io.bp_flush       := io.ID_to_BPU_bus.valid & (bp_target =/= io.ID_to_BPU_bus.bits.br_target)
    io.bp_npc         := MuxCase(io.PF_pc + 4.U, Seq(
        (io.bp_flush             , io.ID_to_BPU_bus.bits.br_target),
        (bp_taken & RAS.io.popEn , RAS.io.pop                     ),
        (bp_taken                , BTB.io.readData                )
        ))
    io.bp_taken       := bp_taken
    io.bp_stall       := 0.U


    //statistic
    val jal_cnt  = RegInit(0.U(32.W))
    val jalr_cnt = RegInit(0.U(32.W))
    val btype_cnt  = RegInit(0.U(32.W))
    val btype_fail = RegInit(0.U(32.W))
    val jal_fail = RegInit(0.U(32.W))
    val jalr_fail = RegInit(0.U(32.W))
    val hit_cnt = RegInit(0.U(32.W))
    
    when(io.ID_to_BPU_bus.valid & io.ID_to_BPU_bus.bits.Type === 1.U){
        jal_cnt := jal_cnt + 1.U
    }
    when(io.ID_to_BPU_bus.valid & io.ID_to_BPU_bus.bits.Type === 2.U){
        btype_cnt := btype_cnt + 1.U
    }
    when(io.ID_to_BPU_bus.valid & io.ID_to_BPU_bus.bits.Type === 3.U){
        jalr_cnt := jalr_cnt + 1.U
    }
    when(io.bp_flush & io.ID_to_BPU_bus.valid && io.ID_to_BPU_bus.bits.Type === 1.U){
        jal_fail := jal_fail + 1.U
    }
    when(io.bp_flush & io.ID_to_BPU_bus.valid && io.ID_to_BPU_bus.bits.Type === 2.U){
        btype_fail := btype_fail + 1.U
    }
    when(io.bp_flush & io.ID_to_BPU_bus.valid && io.ID_to_BPU_bus.bits.Type === 3.U){
        jalr_fail := jalr_fail + 1.U
    }
    when(BTB.io.hit & io.PF_valid & (B_type | J_type) & !io.ID_to_BPU_bus.bits.stall){
        hit_cnt := hit_cnt + 1.U
    }
    
    io.jal_cnt  := jal_cnt
    io.jal_fail  := jal_fail
    io.jalr_cnt := jalr_cnt
    io.jalr_fail := jalr_fail
    io.btype_cnt := btype_cnt
    io.btype_fail := btype_fail
    io.hit_cnt := hit_cnt
}