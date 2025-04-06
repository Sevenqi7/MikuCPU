package miku.isa.riscv32

import chisel3._
import chisel3.util._
import chisel3.util.experimental.decode._

import miku._
import miku.isa._
import miku.utils.util.uintToBitPat

import RV32Instructions._

class RV32DecoderUnit extends DecoderUnit {
    val rv32_decode_table =
        RV32IDecoder.decodeTable ++ RV32MDecoder.decodeTable ++ RV32ZicsrDecoder.decodeTable ++ RV32ADecoder.decodeTable ++ RV32MiscDecoder.decodeTable

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
// rs2 rs1 rd

object RV32IDecoder extends DecodeConstants {
    val decodeTable = Array[(BitPat, List[BitPat])](
        LUI    -> List(Y, SrcType.imm, SrcType.none, SrcType.none, FuType.alu, ALUOpType.lui  , N, SelImm.IMM_U),
        AUIPC  -> List(Y, SrcType.imm, SrcType.none, SrcType.none, FuType.alu, ALUOpType.auipc, N, SelImm.IMM_U),
        JAL    -> List(Y, SrcType.imm, SrcType.none, SrcType.none, FuType.bru, JumpOpType.jal , N, SelImm.IMM_J),
        JALR   -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.bru, JumpOpType.jalr, N, SelImm.IMM_I),
        BEQ    -> List(N, SrcType.reg, SrcType.reg , SrcType.imm , FuType.bru, JumpOpType.beq , N, SelImm.IMM_B),
        BNE    -> List(N, SrcType.reg, SrcType.reg , SrcType.imm , FuType.bru, JumpOpType.bne , N, SelImm.IMM_B),
        BLT    -> List(N, SrcType.reg, SrcType.reg , SrcType.imm , FuType.bru, JumpOpType.blt , N, SelImm.IMM_B),
        BGE    -> List(N, SrcType.reg, SrcType.reg , SrcType.imm , FuType.bru, JumpOpType.bge , N, SelImm.IMM_B),
        BLTU   -> List(N, SrcType.reg, SrcType.reg , SrcType.imm , FuType.bru, JumpOpType.bltu, N, SelImm.IMM_B),
        BGEU   -> List(N, SrcType.reg, SrcType.reg , SrcType.imm , FuType.bru, JumpOpType.bgeu, N, SelImm.IMM_B),
        LB     -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.lsu, LSUOpType.ldb  , N, SelImm.IMM_I),
        LH     -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.lsu, LSUOpType.ldh  , N, SelImm.IMM_I),
        LW     -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.lsu, LSUOpType.ldw  , N, SelImm.IMM_I),
        LBU    -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.lsu, LSUOpType.ldbu , N, SelImm.IMM_I),
        LHU    -> List(Y, SrcType.imm, SrcType.reg , SrcType.none, FuType.lsu, LSUOpType.ldhu , N, SelImm.IMM_I),
        SB     -> List(N, SrcType.reg, SrcType.reg , SrcType.imm , FuType.lsu, LSUOpType.stb  , N, SelImm.IMM_S),
        SH     -> List(N, SrcType.reg, SrcType.reg , SrcType.imm , FuType.lsu, LSUOpType.sth  , N, SelImm.IMM_S),
        SW     -> List(N, SrcType.reg, SrcType.reg , SrcType.imm , FuType.lsu, LSUOpType.stw  , N, SelImm.IMM_S),
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

    )  
}

object RV32MDecoder extends DecodeConstants {
    val decodeTable = Array[(BitPat, List[BitPat])](
        MUL     -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.mul  , N, SelImm.X),
        MULH    -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.mulh , N, SelImm.X),
        MULHU   -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.mulhu, N, SelImm.X),
        // MULHSU  -> 
        DIV     -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.div  , N, SelImm.X),
        DIVU    -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.divu , N, SelImm.X),        
        REM     -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.mod  , N, SelImm.X),        
        REMU    -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.mul, MulDivOpType.modu , N, SelImm.X)        
    )
}

object RV32ZicsrDecoder extends DecodeConstants {
    val decodeTable = Array[(BitPat, List[BitPat])](
        CSRRW    -> List(Y, SrcType.imm , SrcType.reg, SrcType.none, FuType.csr, CSROpType.csrrw, N, SelImm.IMM_I),
        CSRRS    -> List(Y, SrcType.imm , SrcType.reg, SrcType.none, FuType.csr, CSROpType.csrrs, N, SelImm.IMM_I),
        CSRRC    -> List(Y, SrcType.imm , SrcType.reg, SrcType.none, FuType.csr, CSROpType.csrrc, N, SelImm.IMM_I),
        CSRRWI   -> List(Y, SrcType.imm , SrcType.none, SrcType.none, FuType.csr, CSROpType.csrrw, N, SelImm.IMM_I),
        CSRRSI   -> List(Y, SrcType.imm , SrcType.none, SrcType.none, FuType.csr, CSROpType.csrrs, N, SelImm.IMM_I),
        CSRRCI   -> List(Y, SrcType.imm , SrcType.none, SrcType.none, FuType.csr, CSROpType.csrrc, N, SelImm.IMM_I)
    )
}

object RV32ADecoder extends DecodeConstants {
    val decodeTable = Array[(BitPat, List[BitPat])](
        AMOOR   -> List(Y, SrcType.reg , SrcType.reg, SrcType.none, FuType.lsu, LSUOpType.amoor  , N, SelImm.X),
        AMOAND  -> List(Y, SrcType.reg , SrcType.reg, SrcType.none, FuType.lsu, LSUOpType.amoand , N, SelImm.X),
        AMOADD  -> List(Y, SrcType.reg , SrcType.reg, SrcType.none, FuType.lsu, LSUOpType.amoadd , N, SelImm.X),
        AMOSWAP -> List(Y, SrcType.reg , SrcType.reg, SrcType.none, FuType.lsu, LSUOpType.amoswap, N, SelImm.X),
        SC      -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.lsu, LSUOpType.scw, N, SelImm.X),
        LR      -> List(Y, SrcType.reg, SrcType.reg, SrcType.none, FuType.lsu, LSUOpType.llw, N, SelImm.X),
    )
}

object RV32MiscDecoder extends DecodeConstants {
    val decodeTable = Array[(BitPat, List[BitPat])](
        ECALL   -> List(N, SrcType.none, SrcType.none, SrcType.none, FuType.misc, MiscOpType.ecall, N, SelImm.X),
        MRET    -> List(N, SrcType.none, SrcType.none, SrcType.none, FuType.misc, MiscOpType.mret , N, SelImm.X),
        // WFI     -> List(N, SrcType.none, SrcType.none, SrcType.none, FuType.misc, MiscOpType.idle , N, SelImm.X)  
    )
}

// format: on
