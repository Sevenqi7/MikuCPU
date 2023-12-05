package miku.frontend

import chisel3._
import chisel3.util._
import chisel3.util.experimental.decode._


import miku.utils.util.uintToBitPat
import miku.frontend.LA32Instructions._

object SelImm {

    
    def IMM_8  = "b000".U
    def IMM_12 = "b001".U
    def IMM_14 = "b010".U
    def IMM_16 = "b011".U
    def IMM_21 = "b100".U
    def IMM_26 = "b101".U
    def INVALID_INSTR = "b0111".U
    // def IMM_B6 = "b1000".U
    
    def X      = BitPat("b????")
    
    def apply() = UInt(4.W)
}

abstract trait DecodeConstants {
    def X = BitPat("b?")
    def N = BitPat("b0")
    def Y = BitPat("b1")

    def decodeDefault: BitPat = /*
        src1       src2          src3        FuncUnit
        |           |             |           |       regWen            
        |           |             |           |        |   flush                     
        |           |             |           |        |    |           SelImm
        |           |             |           |        |    |             |             */
    SrcType.X ## SrcType.X ## SrcType.X ## FuType.X ## N ## N ## SelImm.INVALID_INSTR
}

//3R-Type decoder
object LA3RDecoder extends DecodeConstants {
    val decodeTable = TruthTable(
        Map(  
            ADDW    -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.X,
            SUBW    -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.X,
            SLT     -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.X,
            SLTU    -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.X,
            NOR     -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.X,
            AND     -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.X,
            OR      -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.X,
            XOR     -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.X,
            SLLW    -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.X,
            SRAW    -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.X,
            MULW    -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.mul ## Y ## N ## SelImm.X,
            MULHW   -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.mul ## Y ## N ## SelImm.X,
            MULHWU  -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.mul ## Y ## N ## SelImm.X,
            DIVW    -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.div ## Y ## N ## SelImm.X,
            MODW    -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.div ## Y ## N ## SelImm.X,
            DIVWU   -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.div ## Y ## N ## SelImm.X,
            MODWU   -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.div ## Y ## N ## SelImm.X
        ),
        decodeDefault
    )
}

object LA2RI12Decoder extends DecodeConstants {
    val decodeTable = TruthTable(
        Map(
            SLTI    -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.IMM_12,      
            SLTUI   -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.IMM_12,     
            ADDIW   -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.IMM_12,     
            ANDI    -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.IMM_12,     
            ORI     -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.IMM_12, 
            XORI    -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.IMM_12,     
            LDB     -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.IMM_12, 
            LDH     -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.IMM_12, 
            LDW     -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.IMM_12, 
            STB     -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## N ## N ## SelImm.IMM_12, 
            STH     -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## N ## N ## SelImm.IMM_12, 
            STW     -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## N ## N ## SelImm.IMM_12, 
            LDBU    -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.IMM_12,     
            LDHU    -> SrcType.reg ## SrcType.X ## SrcType.X ## FuType.alu ## Y ## N ## SelImm.IMM_12 
        ),
        decodeDefault
    )
}

object LA2RI16Decoder extends DecodeConstants {
    val decodeTable = TruthTable(
        Map(
            BCECQZ  -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.jmp ## N ## Y ## SelImm.IMM_16,     
            BCENEZ  -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.jmp ## N ## Y ## SelImm.IMM_16,     
            JIRL    -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.jmp ## N ## Y ## SelImm.IMM_16,   
            B       -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.jmp ## N ## Y ## SelImm.IMM_16,
            BL      -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.jmp ## N ## Y ## SelImm.IMM_16, 
            BEQ     -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.jmp ## N ## Y ## SelImm.IMM_16,  
            BNE     -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.jmp ## N ## Y ## SelImm.IMM_16,  
            BLT     -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.jmp ## N ## Y ## SelImm.IMM_16,  
            BGE     -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.jmp ## N ## Y ## SelImm.IMM_16,  
            BLTU    -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.jmp ## N ## Y ## SelImm.IMM_16,   
            BGEU    -> SrcType.reg ## SrcType.reg ## SrcType.X ## FuType.jmp ## N ## Y ## SelImm.IMM_16   
        ),
        decodeDefault
    )
}

