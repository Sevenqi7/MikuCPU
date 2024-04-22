package miku.frontend

import chisel3._
import chisel3.util._
import chisel3.util.experimental.decode._

import miku._
import miku.LA32Instructions._
import miku.utils.util.uintToBitPat

object SelImm {
    def num         = 8
    def IMM_MAX_LEN = 26

    def IMM_U8  = "b000".U(log2Ceil(num).W)
    def IMM_S12 = "b001".U(log2Ceil(num).W)
    def IMM_U12 = "b010".U(log2Ceil(num).W)
    def IMM_S14 = "b011".U(log2Ceil(num).W)
    def IMM_S16 = "b100".U(log2Ceil(num).W)
    def IMM_S20 = "b101".U(log2Ceil(num).W)
    // def IMM_U14       = "b100".U(log2Ceil(num).W)    //这玩意我没找到在哪
    def IMM_S26 = "b110".U(log2Ceil(num).W)
    // def INVALID_INSTR = "b111".U(log2Ceil(num).W)
    // def IMM_B6 = "b1000".U

    def X = BitPat("b???")

    def apply() = UInt(log2Ceil(num).W)
}

abstract trait DecodeConstants {
    def X = BitPat("b?")
    def N = BitPat("b0")
    def Y = BitPat("b1")

    def decodeDefault: List[BitPat] = /*
           regWen   src2      src1       src0     FuncUnit
             |       |         |          |          |            operation
             |       |         |          |          |                |        dest_rj
             |       |         |          |          |                |           |       SelImm
             |       |         |          |          |                |           |         |             */
        List(N, SrcType.X, SrcType.X, SrcType.X, FuType.misc, MiscOpType.unknown, N, SelImm.X)
}

class DecodedInst extends MkBundle with DecodeConstants {
    val regwen   = Bool()
    val src      = Vec(3, SrcType())
    val futype   = FuType()
    val fuoptype = FuOpType()
    val dest_rj  = Bool()
    val selImm   = SelImm()

    // src(2), src(1), src(0) seperately represent rk, rj, rd if there value is reg
    def needRk  = src(2) === SrcType.reg
    def needRj  = src(1) === SrcType.reg
    def needRd  = src(0) === SrcType.reg
    def needImm = src.map(s => s === SrcType.imm).reduce(_ || _)
}

class LA32DecoderUnit extends MkModule with DecodeConstants {
    val io = IO(new Bundle {
        val raw_inst     = Input(UInt(INST_BITS.W))
        val decoded_inst = Output(new DecodedInst)
    })

    val la32_decode_table =
        LA3RDecoder.decodeTable ++ LA2RDecoder.decodeTable

    // ((instructions, decodeBits), defaultBits)
    val la32_decode_map = TruthTable(
        la32_decode_table.map { case (instBits, decodeList) =>
            (instBits, decodeList.reduce(_ ## _))
        }.toMap,
        decodeDefault.reduce(_ ## _)
    )

    // Since CSRXCHG has the same instruction code with CSRRD & CSRWR except its rd field not equal to 0 or 1,
    // and the decoder api in chisel3.experimental we use requires all input BitPat are orthogonal to each other,
    // we have to use ListLookup to independently handle some instructions here.
    val decoded_inst      = decoder(io.raw_inst, la32_decode_map).asTypeOf(new DecodedInst)
    val decoded_misc_inst =
        ListLookup(io.raw_inst, List.fill(decodeDefault.length)(0.U), LAMiscDecoder.decodeTable)
            .reduce(_ ## _).asTypeOf(new DecodedInst)
    val csr_inst_flag     = decoded_misc_inst.asUInt =/= 0.U

    io.decoded_inst := Mux(csr_inst_flag, decoded_misc_inst, decoded_inst)
}

//format: off
//3R-Type decoder
object LA3RDecoder extends DecodeConstants {
    val decodeTable = Array[(BitPat, List[BitPat])](
        ADDW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.addw     , N, SelImm.X),
        SUBW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.subw     , N, SelImm.X),
        SLT    -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.slt      , N, SelImm.X),
        SLTU   -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.sltu     , N, SelImm.X),
        NOR    -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.nor      , N, SelImm.X),
        AND    -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.and      , N, SelImm.X),
        OR     -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.or       , N, SelImm.X),
        XOR    -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.xor      , N, SelImm.X),
        SLLW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.sllw     , N, SelImm.X),
        SRLW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.srlw     , N, SelImm.X),
        SRAW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.sraw     , N, SelImm.X),
        MULW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.mulw  , N, SelImm.X),
        MULHW  -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.mulhw , N, SelImm.X),
        MULHWU -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.mulhwu, N, SelImm.X),
        DIVW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.divw  , N, SelImm.X),
        MODW   -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.modw  , N, SelImm.X),
        DIVWU  -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.divwu , N, SelImm.X),
        MODWU  -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.modwu , N, SelImm.X)
    )
}



object LA2RDecoder extends DecodeConstants {
    val decodeTable = Array[(BitPat, List[BitPat])](
        SLTI  -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.alu , ALUOpType.slt   , N, SelImm.IMM_S12),
        SLTUI -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.alu , ALUOpType.sltu  , N, SelImm.IMM_S12),
        ADDIW -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.alu , ALUOpType.addw  , N, SelImm.IMM_S12),
        ANDI  -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.alu , ALUOpType.and   , N, SelImm.IMM_U12),
        ORI   -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.alu , ALUOpType.or    , N, SelImm.IMM_U12),
        XORI  -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.alu , ALUOpType.xor   , N, SelImm.IMM_U12),
        LDB   -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.lsu , LSUOpType.ldb   , N, SelImm.IMM_S12),
        LDH   -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.lsu , LSUOpType.ldh   , N, SelImm.IMM_S12),
        LDW   -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.lsu , LSUOpType.ldw   , N, SelImm.IMM_S12),
        STB   -> List(N, SrcType.imm, SrcType.reg, SrcType.reg , FuType.lsu , LSUOpType.stb   , N, SelImm.IMM_S12),
        STH   -> List(N, SrcType.imm, SrcType.reg, SrcType.reg , FuType.lsu , LSUOpType.sth   , N, SelImm.IMM_S12),
        STW   -> List(N, SrcType.imm, SrcType.reg, SrcType.reg , FuType.lsu , LSUOpType.stw   , N, SelImm.IMM_S12),
        LDBU  -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.lsu , LSUOpType.ldbu  , N, SelImm.IMM_S12),
        LDHU  -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.lsu , LSUOpType.ldhu  , N, SelImm.IMM_S12),
        CACOP -> List(N, SrcType.imm, SrcType.reg, SrcType.none, FuType.misc, MiscOpType.cacop, N, SelImm.IMM_S12),

        // I8
        SLLIW -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.sllw, N, SelImm.IMM_U8),
        SRLIW -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.srlw, N, SelImm.IMM_U8),
        SRAIW -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.alu, ALUOpType.sraw, N, SelImm.IMM_U8),

        // I14
        LLW   -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.lsu, LSUOpType.llw, N, SelImm.IMM_S14),
        SCW   -> List(Y, SrcType.imm, SrcType.reg, SrcType.none, FuType.lsu, LSUOpType.scw, N, SelImm.IMM_S14),

        // I16
        // BCECQZ -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuOpType.X,      Y, SelImm.X     ), floating branch inst not supported yet
        // BCENEZ -> List(N, SrcType.reg, SrcType.reg, SrcType.X, FuOpType.X,      Y, SelImm.X     ),
        JIRL   -> List(Y, SrcType.imm, SrcType.reg , SrcType.none,   FuType.bru, JumpOpType.jirl, N, SelImm.IMM_S16),
        B      -> List(N, SrcType.imm, SrcType.none, SrcType.none,   FuType.bru, JumpOpType.b   , N, SelImm.IMM_S26),
        BL     -> List(Y, SrcType.imm, SrcType.none, SrcType.none,   FuType.bru, JumpOpType.bl  , N, SelImm.IMM_S26),
        BEQ    -> List(N, SrcType.imm, SrcType.reg , SrcType.reg ,   FuType.bru, JumpOpType.beq , N, SelImm.IMM_S16),
        BNE    -> List(N, SrcType.imm, SrcType.reg , SrcType.reg ,   FuType.bru, JumpOpType.bne , N, SelImm.IMM_S16),
        BLT    -> List(N, SrcType.imm, SrcType.reg , SrcType.reg ,   FuType.bru, JumpOpType.blt , N, SelImm.IMM_S16),
        BGE    -> List(N, SrcType.imm, SrcType.reg , SrcType.reg ,   FuType.bru, JumpOpType.bge , N, SelImm.IMM_S16),
        BLTU   -> List(N, SrcType.imm, SrcType.reg , SrcType.reg ,   FuType.bru, JumpOpType.bltu, N, SelImm.IMM_S16),
        BGEU   -> List(N, SrcType.imm, SrcType.reg , SrcType.reg ,   FuType.bru, JumpOpType.bgeu, N, SelImm.IMM_S16),

        // I20
        LU12IW     -> List(Y, SrcType.none, SrcType.imm, SrcType.none, FuType.alu, ALUOpType.lu12iw     , N, SelImm.IMM_S20),
        PCADDU12I  -> List(Y, SrcType.pc  , SrcType.imm, SrcType.none, FuType.alu, ALUOpType.pcaddu12i  , N, SelImm.IMM_S20)
    )
}

// this decodeTable is used with ListLookup API, not chisel3.experimental.decoder
object LAMiscDecoder extends DecodeConstants {
    import scala.language.implicitConversions
    implicit def bitPatToUInt(x: BitPat) : UInt = x.value.U
    val decodeTable = Array[(BitPat, List[UInt])](
        RDCNTIDW -> List(Y, SrcType.none, SrcType.none, SrcType.none, FuType.misc, MiscOpType.rdcntid, Y, SelImm.X),
        RDCNTVLW -> List(Y, SrcType.none, SrcType.none, SrcType.none, FuType.misc, MiscOpType.rdcntvl, N, SelImm.X),
        RDCNTVHW -> List(Y, SrcType.none, SrcType.none, SrcType.none, FuType.misc, MiscOpType.rdcntvh, N, SelImm.X),
        CSRRD   ->  List(Y, SrcType.imm , SrcType.none, SrcType.reg , FuType.csr , CSROpType.csrrd   , N, SelImm.IMM_S14),
        CSRWR   ->  List(Y, SrcType.imm , SrcType.none, SrcType.reg , FuType.csr , CSROpType.csrwr   , N, SelImm.IMM_S14),
        CSRXCHG ->  List(Y, SrcType.imm , SrcType.reg , SrcType.reg , FuType.csr , CSROpType.csrxchg , N, SelImm.IMM_S14),
        SYSCALL ->  List(Y, SrcType.imm , SrcType.none, SrcType.none, FuType.misc, MiscOpType.syscall, N, SelImm.X),
        BREAK   ->  List(Y, SrcType.imm , SrcType.none, SrcType.none, FuType.misc, MiscOpType.break  , N, SelImm.X),
        ERTN    ->  List(N, SrcType.none, SrcType.none, SrcType.none, FuType.misc, MiscOpType.ertn   , N, SelImm.X),
        TLBSRCH ->  List(N, SrcType.none, SrcType.none, SrcType.none, FuType.csr , CSROpType.tlbsrch , N, SelImm.X),
        TLBRD   ->  List(N, SrcType.none, SrcType.none, SrcType.none, FuType.csr , CSROpType.tlbrd   , N, SelImm.X),
        TLBWR   ->  List(N, SrcType.none, SrcType.none, SrcType.none, FuType.csr , CSROpType.tlbwr   , N, SelImm.X),
        TLBFILL ->  List(N, SrcType.none, SrcType.none, SrcType.none, FuType.csr , CSROpType.tlbfill , N, SelImm.X),
        INVTLB  ->  List(N, SrcType.reg , SrcType.reg , SrcType.none, FuType.csr , CSROpType.invtlb  , N, SelImm.X),
        IDLE    ->  List(N, SrcType.none, SrcType.none, SrcType.none, FuType.misc, MiscOpType.idle   , N, SelImm.X),
        DBAR    ->  List(N, SrcType.none ,SrcType.none, SrcType.none ,FuType.misc, MiscOpType.none   , N, SelImm.X),
        IBAR    ->  List(N, SrcType.none ,SrcType.none, SrcType.none ,FuType.misc, MiscOpType.none   , N, SelImm.X),
        PRELD   ->  List(N, SrcType.none ,SrcType.none, SrcType.none ,FuType.misc, MiscOpType.none   , N, SelImm.X),
    )
}
// format: on
