package miku.frontend

import chisel3._
import chisel3.util._
import chisel3.util.experimental.decode._

import miku._
import miku.utils.util.uintToBitPat
import miku.frontend.LA32Instructions._

object SelImm {
    def num         = 8
    def IMM_MAX_LEN = 26

    def IMM_8         = "b000".U(log2Ceil(num).W)
    def IMM_12        = "b001".U(log2Ceil(num).W)
    def IMM_14        = "b010".U(log2Ceil(num).W)
    def IMM_16        = "b011".U(log2Ceil(num).W)
    def IMM_21        = "b100".U(log2Ceil(num).W)
    def IMM_26        = "b101".U(log2Ceil(num).W)
    def INVALID_INSTR = "b111".U(log2Ceil(num).W)
    // def IMM_B6 = "b1000".U

    def X = BitPat("b???")

    def apply() = UInt(log2Ceil(num).W)
}

abstract trait DecodeConstants {
    def X = BitPat("b?")
    def N = BitPat("b0")
    def Y = BitPat("b1")

    def decodeDefault: List[BitPat] = /*
           regWen   src1      src2       src3     FuncUnit
             |       |         |          |          |              flush
             |       |         |          |          |                 |
             |       |         |          |          |                 |              SelImm
             |       |         |          |          |                 |                |             */
        List(N, SrcType.X, SrcType.X, SrcType.X, FuType.X, FuOpType.X, N, SelImm.INVALID_INSTR)
}

class DecodedInst extends MkBundle with DecodeConstants {
    val src1     = SrcType()
    val src2     = SrcType()
    val src3     = SrcType()
    val futype   = FuType()
    val fuoptype = FuOpType()
    val regwen   = Bool()
    val flush    = Bool()
    val selImm   = SelImm()
}

class LA32DecoderUnit extends MkModule with DecodeConstants {
    val raw_inst     = IO(Input(UInt(INST_BITS.W)))
    val decoded_inst = IO(Output(new DecodedInst))

    val la32_decode_table = LA3RDecoder.decodeTable ++ LA2RI12Decoder.decodeTable ++ LA2RI16Decoder.decodeTable

    // ((instructions, decodeBits), defaultBits)
    val la32_decode_map = TruthTable(
        la32_decode_table.map { case (instBits, decodeList) =>
            (instBits, decodeList.reduce(_ ## _))
        }.toMap,
        decodeDefault.reduce(_ ## _)
    )

    decoded_inst := decoder(raw_inst, la32_decode_map).asTypeOf(new DecodedInst)
}

//format: off
//3R-Type decoder
object LA3RDecoder extends DecodeConstants {
    val decodeTable = Array[(BitPat, List[BitPat])](
        ADDW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, ALUOpType.addw     , N, SelImm.X),
        SUBW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, ALUOpType.subw     , N, SelImm.X),
        SLT    -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, ALUOpType.slt      , N, SelImm.X),
        SLTU   -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, ALUOpType.sltu     , N, SelImm.X),
        NOR    -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, ALUOpType.nor      , N, SelImm.X),
        AND    -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, ALUOpType.and      , N, SelImm.X),
        OR     -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, ALUOpType.or       , N, SelImm.X),
        XOR    -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.alu, ALUOpType.xor      , N, SelImm.X),
        SLLW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.mul, ALUOpType.sllw     , N, SelImm.X),
        MULHWU -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.mul, MulDivOpType.mulhwu, N, SelImm.X),
        DIVW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.mul, MulDivOpType.divw  , N, SelImm.X),
        MODW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.mul, MulDivOpType.modw  , N, SelImm.X),
        DIVWU  -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.mul, MulDivOpType.divwu , N, SelImm.X),
        MODWU  -> List(Y, SrcType.reg, SrcType.reg, SrcType.X, FuType.mul, MulDivOpType.modwu , N, SelImm.X)
    )
}

object LA2RI12Decoder extends DecodeConstants {
    val decodeTable = Array[(BitPat, List[BitPat])](
        SLTI  -> List(Y, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, ALUOpType.slt , N, SelImm.IMM_12),
        SLTUI -> List(Y, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, ALUOpType.sltu, N, SelImm.IMM_12),
        ADDIW -> List(Y, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, ALUOpType.addw, N, SelImm.IMM_12),
        ANDI  -> List(Y, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, ALUOpType.and , N, SelImm.IMM_12),
        ORI   -> List(Y, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, ALUOpType.or  , N, SelImm.IMM_12),
        XORI  -> List(Y, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, ALUOpType.xor , N, SelImm.IMM_12),
        LDB   -> List(Y, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, LSUOpType.ldb , N, SelImm.IMM_12),
        LDH   -> List(Y, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, LSUOpType.ldh , N, SelImm.IMM_12),
        LDW   -> List(Y, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, LSUOpType.ldw , N, SelImm.IMM_12),
        STB   -> List(N, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, LSUOpType.stb , N, SelImm.IMM_12),
        STH   -> List(N, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, LSUOpType.sth , N, SelImm.IMM_12),
        STW   -> List(N, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, LSUOpType.stw , N, SelImm.IMM_12),
        LDBU  -> List(Y, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, LSUOpType.ldbu, N, SelImm.IMM_12),
        LDHU  -> List(Y, SrcType.reg, SrcType.imm, SrcType.X, FuType.alu, LSUOpType.ldhu, N, SelImm.IMM_12)
    )
}

object LA2RI16Decoder extends DecodeConstants {
    val decodeTable = Array[(BitPat, List[BitPat])](
        // BCECQZ -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuOpType.X,      Y, SelImm.X     ), floating branch inst not supported yet
        // BCENEZ -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuOpType.X,      Y, SelImm.X     ),
        JIRL   -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, JumpOpType.jirl, Y, SelImm.IMM_16),
        B      -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, JumpOpType.b,    Y, SelImm.IMM_16),
        BL     -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, JumpOpType.bl,   Y, SelImm.IMM_16),
        BEQ    -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, JumpOpType.beq,  Y, SelImm.IMM_16),
        BNE    -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, JumpOpType.bne,  Y, SelImm.IMM_16),
        BLT    -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, JumpOpType.blt,  Y, SelImm.IMM_16),
        BGE    -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, JumpOpType.bge,  Y, SelImm.IMM_16),
        BLTU   -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, JumpOpType.bltu, Y, SelImm.IMM_16),
        BGEU   -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuType.jmp, JumpOpType.bgeu, Y, SelImm.IMM_16)
    )
}
// format: on
