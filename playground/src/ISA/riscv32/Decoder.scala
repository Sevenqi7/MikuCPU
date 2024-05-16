package miku.isa.riscv32

import chisel3._
import chisel3.util._
import chisel3.util.experimental.decode._

import miku._
import miku.isa._
import miku.utils.util.uintToBitPat

import RV32Instructions._

class RV32DecoderUnit extends DecoderUnit {
    val rv32_decode_table = RV32IDecoder.decodeTable

    val rv32_decode_map = TruthTable(
        rv32_decode_table.map { case (instBits, decodeList) =>
            (instBits, decodeList.reduce(_ ## _))
        }.toMap,
        decodeDefault.reduce(_ ## _)
    )

    val decoded_inst = decoder(io.raw_inst, rv32_decode_map).asTypeOf(ArchDecodedInst())
    io.decoded_inst := decoded_inst
}

// format: off

object RV32IDecoder extends DecodeConstants {
    val decodeTable = Array[(BitPat, List[BitPat])](
        LUI    -> List(Y, SrcType.imm, SrcType.none, SrcType.none, FuType.alu, ALUOpType.add  , N, SelImm.IMM_U),
        AUIPC  -> List(Y, SrcType.imm, SrcType.none, SrcType.none, FuType.alu, ALUOpType.auipc, N, SelImm.IMM_U),
        JAL    -> List(Y, SrcType.imm, SrcType.none, SrcType.none, FuType.bru, ALUOpType.add  , N, SelImm.IMM_J),
        JALR   -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.bru, ALUOpType.add  , N, SelImm.IMM_J),
        BEQ    -> List(N, SrcType.reg, SrcType.reg , SrcType.none, FuType.bru, JumpOpType.beq , N, SelImm.IMM_B),
        BNE    -> List(N, SrcType.reg, SrcType.reg , SrcType.none, FuType.bru, JumpOpType.bne , N, SelImm.IMM_B),
        BLT    -> List(N, SrcType.reg, SrcType.reg , SrcType.none, FuType.bru, JumpOpType.blt , N, SelImm.IMM_B),
        BGE    -> List(N, SrcType.reg, SrcType.reg , SrcType.none, FuType.bru, JumpOpType.bge , N, SelImm.IMM_B),
        BLTU   -> List(N, SrcType.reg, SrcType.reg , SrcType.none, FuType.bru, JumpOpType.bltu, N, SelImm.IMM_B),
        BGEU   -> List(N, SrcType.reg, SrcType.reg , SrcType.none, FuType.bru, JumpOpType.bgeu, N, SelImm.IMM_B),
        LB     -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, LSUOpType.ldb  , N, SelImm.IMM_S),
        LH     -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, LSUOpType.ldh  , N, SelImm.IMM_S),
        LW     -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, LSUOpType.ldw  , N, SelImm.IMM_S),
        LBU    -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, LSUOpType.ldbu , N, SelImm.IMM_S),
        LHU    -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, LSUOpType.ldhu , N, SelImm.IMM_S),
        SB     -> List(N, SrcType.reg, SrcType.reg , SrcType.imm , FuType.alu, LSUOpType.stb  , N, SelImm.IMM_S),
        SH     -> List(N, SrcType.reg, SrcType.reg , SrcType.imm , FuType.alu, LSUOpType.sth  , N, SelImm.IMM_S),
        SW     -> List(N, SrcType.reg, SrcType.reg , SrcType.imm , FuType.alu, LSUOpType.stw  , N, SelImm.IMM_S),
        ADDI   -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.add  , N, SelImm.IMM_I),
        SLTI   -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.slt  , N, SelImm.IMM_I),
        SLTIU  -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.sltu , N, SelImm.IMM_I),
        XORI   -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.xor  , N, SelImm.IMM_I),
        ORI    -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.or   , N, SelImm.IMM_I),
        ANDI   -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.and  , N, SelImm.IMM_I),
        SLLI   -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.sll  , N, SelImm.IMM_I),
        SRLI   -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.srl  , N, SelImm.IMM_I),
        SRAI   -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.sra  , N, SelImm.IMM_I),
        ADD    -> List(Y, SrcType.reg, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.add  , N, SelImm.X),
        SUB    -> List(Y, SrcType.reg, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.sub  , N, SelImm.X),
        SLL    -> List(Y, SrcType.reg, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.sll  , N, SelImm.X),
        SLT    -> List(Y, SrcType.reg, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.slt  , N, SelImm.X),
        SLTU   -> List(Y, SrcType.reg, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.sltu , N, SelImm.X),
        XOR    -> List(Y, SrcType.reg, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.xor  , N, SelImm.X),
        SRL    -> List(Y, SrcType.reg, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.srl  , N, SelImm.X),
        SRA    -> List(Y, SrcType.reg, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.sra  , N, SelImm.X),
        OR     -> List(Y, SrcType.reg, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.or   , N, SelImm.X),
        AND    -> List(Y, SrcType.reg, SrcType.reg , SrcType.none, FuType.alu, ALUOpType.and  , N, SelImm.X),

        // FENCE  -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, MiscOpType.unknown  , N, SelImm.X),
        // ECALL  -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, MiscOpType.unknown  , N, SelImm.X),
        // EBREAk -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.alu, MiscOpType.unknown  , N, SelImm.X)
    )  

    // format: on
}
