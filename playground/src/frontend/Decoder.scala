package miku.frontend

import chisel3._
import chisel3.util._

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

    def decodeDefault: List[BitPat] = /*
           src1       src2      src3        FuncUnit
            |           |         |           |    regWen            
            |           |         |           |     | flush                     
            |           |         |           |     |  |        SelImm
            |           |         |           |     |  |          |             */
    List(SrcType.X, SrcType.X, SrcType.X, FuType.X, N, N, SelImm.INVALID_INSTR)

    val decodeTable: Array[(BitPat, List[BitPat])]
}

//3R-Type decoder
object LA3RDecoder extends DecodeConstants {
    val decodeTable: Array[(BitPat, List[BitPat])] = Array(
        ADDW    -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, Y, N, SelImm.X),
        SUBW    -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, Y, N, SelImm.X),
        SLT     -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, Y, N, SelImm.X),
        SLTU    -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, Y, N, SelImm.X),
        NOR     -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, Y, N, SelImm.X),
        AND     -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, Y, N, SelImm.X),
        OR      -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, Y, N, SelImm.X),
        XOR     -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, Y, N, SelImm.X),
        SLLW    -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, Y, N, SelImm.X),
        SRAW    -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, Y, N, SelImm.X),
        MULW    -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.mul, Y, N, SelImm.X),
        MULHW   -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.mul, Y, N, SelImm.X),
        MULHWU  -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.mul, Y, N, SelImm.X),
        DIVW    -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.div, Y, N, SelImm.X),
        MODW    -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.div, Y, N, SelImm.X),
        DIVWU   -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.div, Y, N, SelImm.X),
        MODWU   -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.div, Y, N, SelImm.X)
    )
}

object LA2RI12Decoder extends DecodeConstants {
    val decodeTable: Array[(BitPat, List[BitPat])] = Array(
        SLTI    -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, Y, N, SelImm.IMM_12),      
        SLTUI   -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, Y, N, SelImm.IMM_12),     
        ADDIW   -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, Y, N, SelImm.IMM_12),     
        ANDI    -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, Y, N, SelImm.IMM_12),     
        ORI     -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, Y, N, SelImm.IMM_12), 
        XORI    -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, Y, N, SelImm.IMM_12),     
        LDB     -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, Y, N, SelImm.IMM_12), 
        LDH     -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, Y, N, SelImm.IMM_12), 
        LDW     -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, Y, N, SelImm.IMM_12), 
        STB     -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, N, N, SelImm.IMM_12), 
        STH     -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, N, N, SelImm.IMM_12), 
        STW     -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, N, N, SelImm.IMM_12), 
        LDBU    -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, Y, N, SelImm.IMM_12),     
        LDHU    -> List(SrcType.reg, SrcType.X  , SrcType.X, FuType.alu, Y, N, SelImm.IMM_12) 
    )
}

object LA2RI16Decoder extends DecodeConstants {
    val decodeTable: Array[(BitPat, List[BitPat])] = Array(
        BCECQZ  -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, N, Y, SelImm.IMM_16),     
        BCENEZ  -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, N, Y, SelImm.IMM_16),     
        JIRL    -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, N, Y, SelImm.IMM_16),   
        B       -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, N, Y, SelImm.IMM_16),
        BL      -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, N, Y, SelImm.IMM_16), 
        BEQ     -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, N, Y, SelImm.IMM_16),  
        BNE     -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, N, Y, SelImm.IMM_16),  
        BLT     -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, N, Y, SelImm.IMM_16),  
        BGE     -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, N, Y, SelImm.IMM_16),  
        BLTU    -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, N, Y, SelImm.IMM_16),   
        BGEU    -> List(SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, N, Y, SelImm.IMM_16)   
    )
}

