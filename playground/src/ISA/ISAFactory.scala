package miku.isa

import chisel3._
import chisel3.util._

import miku._
import miku.issue._
import miku.frontend._
import miku.backend._
import FuOpType.MaxOpNum
import miku.utils.util.uintToBitPat
import miku.isa.la32._
import miku.utils.ReadyValidBundle

object SrcType {
    def num = 4

    def reg  = "b00".U(log2Ceil(num).W)
    def pc   = "b01".U(log2Ceil(num).W)
    def imm  = "b10".U(log2Ceil(num).W)
    def none = "b11".U(log2Ceil(num).W)

    def X = BitPat("b??")

    def apply() = UInt(log2Ceil(num).W)
}

object SelImm {
    def num         = 8
    def IMM_MAX_LEN = 26

    // LA32
    def IMM_U8  = "b000".U(log2Ceil(num).W)
    def IMM_S12 = "b001".U(log2Ceil(num).W)
    def IMM_U12 = "b010".U(log2Ceil(num).W)
    def IMM_S14 = "b011".U(log2Ceil(num).W)
    def IMM_S16 = "b100".U(log2Ceil(num).W)
    def IMM_U20 = "b100".U(log2Ceil(num).W)
    def IMM_S20 = "b101".U(log2Ceil(num).W)
    def IMM_B12 = "b110".U(log2Ceil(num).W) // for B-type instruction of RISCV
    def IMM_S26 = "b111".U(log2Ceil(num).W) // for B instruction of Loongarch
    // def IMM_B6 = "b1000".U

    // RV32
    def IMM_U = "b000".U(log2Ceil(num).W)
    def IMM_S = "b001".U(log2Ceil(num).W)
    def IMM_B = "b010".U(log2Ceil(num).W)
    def IMM_J = "b011".U(log2Ceil(num).W)
    def IMM_I = "b100".U(log2Ceil(num).W)

    def X = BitPat("b???")

    def apply() = UInt(log2Ceil(num).W)
}

object FuOpType {
    def MaxOpNum =
        List(ALUOpType.num, MulDivOpType.num, JumpOpType.num, LSUOpType.num, CSROpType.num, MiscOpType.num).max

    def X = BitPat("b????")

    def apply() = UInt(log2Ceil(MaxOpNum).W)
}

object ALUOpType {
    def num = 12

    def add   = "b0001".U(log2Ceil(MaxOpNum).W) // R(rd) = R(rj) + R(rk)
    def sub   = "b0010".U(log2Ceil(MaxOpNum).W) // R(rd) = R(ri) - R(rk)
    def lui   = "b0011".U(log2Ceil(MaxOpNum).W) // R(rd) = {imm20, 12'b0}
    def slt   = "b0100".U(log2Ceil(MaxOpNum).W) // R(rd) = (signed(R(rj)) < signed(R(rk)))
    def sltu  = "b0101".U(log2Ceil(MaxOpNum).W) // R(rd) = (R(rj) < R(rk))
    def and   = "b0110".U(log2Ceil(MaxOpNum).W) // R(rd) = R(rj) & R(rk)
    def or    = "b0111".U(log2Ceil(MaxOpNum).W) // R(rd) = R(rj) | R(rk)
    def nor   = "b1000".U(log2Ceil(MaxOpNum).W) // R(rd) = ~(R(rj) | R(rk))
    def xor   = "b1001".U(log2Ceil(MaxOpNum).W) // R(rd) = R(rj) ^ R(rk)
    def sll   = "b1010".U(log2Ceil(MaxOpNum).W) // R(rd) = sll(R(rj), R(rk)[4:0])[31:0]
    def srl   = "b1011".U(log2Ceil(MaxOpNum).W) // R(rd) = srl(R(rj), R(rk)[4:0])[31:0]
    def sra   = "b1100".U(log2Ceil(MaxOpNum).W) // R(rd) = sra(R(rj), R(rk)[4:0])[31:0]
    def auipc = "b1101".U(log2Ceil(MaxOpNum).W) // R(rd) = PC + SEXT({imm20, 12'b0})

    def apply() = UInt(log2Ceil(MaxOpNum).W)
}

object MulDivOpType {
    def num = 7

    def mul   = "b000".U(log2Ceil(MaxOpNum).W) // R(rd) = (signed(R(rj)) * signed(R(rk)))[31:0]
    def mulh  = "b001".U(log2Ceil(MaxOpNum).W) // R(rd) = (signed(R(rj)) * signed(R(rk)))[63:32]
    def mulhu = "b010".U(log2Ceil(MaxOpNum).W) // R(rd) = (R(rj) * R(rk))[63:32]
    def div   = "b011".U(log2Ceil(MaxOpNum).W) // R(rd) = (signed(R(rj)) / signed(R(rk)))[31:0]
    def divu  = "b100".U(log2Ceil(MaxOpNum).W) // R(rd) = (R(rj) / R(rk))[31:0]
    def mod   = "b101".U(log2Ceil(MaxOpNum).W) // R(rd) = (signed(R(rj)) % signed(R(rk)))[31:0]
    def modu  = "b110".U(log2Ceil(MaxOpNum).W) // R(rd) = (R(rj) % R(rk))[31:0]

    def apply() = UInt(log2Ceil(MaxOpNum).W)
}

object JumpOpType {
    def num = 9

    // General branch inst
    def beq  = "b0000".U(log2Ceil(MaxOpNum).W)
    def bne  = "b0001".U(log2Ceil(MaxOpNum).W)
    def blt  = "b0010".U(log2Ceil(MaxOpNum).W)
    def bge  = "b0011".U(log2Ceil(MaxOpNum).W)
    def bltu = "b0100".U(log2Ceil(MaxOpNum).W)
    def bgeu = "b0101".U(log2Ceil(MaxOpNum).W)

    // LA32 specified branch inst
    def b    = "b0110".U(log2Ceil(MaxOpNum).W)
    def bl   = "b0111".U(log2Ceil(MaxOpNum).W)
    def jirl = "b1000".U(log2Ceil(MaxOpNum).W)

    // RV32 specified branch inst
    def jal  = "b0110".U(log2Ceil(MaxOpNum).W)
    def jalr = "b0111".U(log2Ceil(MaxOpNum).W)

    def apply() = UInt(log2Ceil(num).W)
}

object LSUOpType {
    def num = 10

    def isLoadType(optype: UInt)  = optype(3, 0) >= ldb
    def isStoreType(optype: UInt) = optype(3, 0) <= scw

    def ldb  = "b1000".U(log2Ceil(MaxOpNum).W)
    def ldh  = "b1001".U(log2Ceil(MaxOpNum).W)
    def ldw  = "b1010".U(log2Ceil(MaxOpNum).W)
    def ldbu = "b1011".U(log2Ceil(MaxOpNum).W)
    def ldhu = "b1100".U(log2Ceil(MaxOpNum).W)
    def llw  = "b1101".U(log2Ceil(MaxOpNum).W)
    def stb  = "b0000".U(log2Ceil(MaxOpNum).W)
    def sth  = "b0001".U(log2Ceil(MaxOpNum).W)
    def stw  = "b0010".U(log2Ceil(MaxOpNum).W)
    def scw  = "b0011".U(log2Ceil(MaxOpNum).W)

    def X = BitPat("b????")

    def apply() = UInt(log2Ceil(num).W)
}

object CSROpType {
    def num = 7

    def csrrd   = "b000".U(log2Ceil(MaxOpNum).W)
    def csrwr   = "b001".U(log2Ceil(MaxOpNum).W)
    def csrxchg = "b010".U(log2Ceil(MaxOpNum).W)
    def tlbsrch = "b011".U(log2Ceil(MaxOpNum).W)
    def tlbrd   = "b100".U(log2Ceil(MaxOpNum).W)
    def tlbwr   = "b101".U(log2Ceil(MaxOpNum).W)
    def tlbfill = "b110".U(log2Ceil(MaxOpNum).W)
    def invtlb  = "b111".U(log2Ceil(MaxOpNum).W)
    def apply() = UInt(log2Ceil(num).W)
}

object MiscOpType {
    def num = 10

    def none    = "b0000".U(log2Ceil(MaxOpNum).W)
    def rdcntid = "b0001".U(log2Ceil(MaxOpNum).W)
    def rdcntvl = "b0010".U(log2Ceil(MaxOpNum).W)
    def rdcntvh = "b0011".U(log2Ceil(MaxOpNum).W)
    def cacop   = "b0100".U(log2Ceil(MaxOpNum).W)
    def syscall = "b0101".U(log2Ceil(MaxOpNum).W)
    def break   = "b0110".U(log2Ceil(MaxOpNum).W)
    def ertn    = "b0111".U(log2Ceil(MaxOpNum).W)
    def idle    = "b1000".U(log2Ceil(MaxOpNum).W)
    def unknown = "b1111".U(log2Ceil(MaxOpNum).W)

    def apply() = UInt(log2Ceil(num).W)
}

// Function Unit Type
// IT MUST BE ONE-HOT since we use OHtoUInt when indexing function unit
object FuType {
    def num = 5

    def alu  = "b00001".U(num.W)
    def lsu  = "b00010".U(num.W)
    def mul  = "b00100".U(num.W)
    def bru  = "b01000".U(num.W)
    def csr  = "b10000".U(num.W)
    def misc = "b00000".U(num.W)

    def X = BitPat("b?????")

    def apply() = UInt(num.W)
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

abstract class DecodedInst extends MkBundle with DecodeConstants {
    val regwen   = Bool()
    // src(2), src(1), src(0) seperately represent rs2, rs1, rd when their value are SrcType.reg
    val src      = Vec(3, SrcType())
    val futype   = FuType()
    val fuoptype = FuOpType()
    val dest_rs1 = Bool()
    val selImm   = SelImm()

    def getRs1(raw_inst: UInt): UInt
    def getRs2(raw_inst: UInt): UInt
    def getRd(raw_inst:  UInt): UInt
}

abstract class DecoderUnit extends MkModule with DecodeConstants {
    val io = IO(new Bundle {
        val raw_inst     = Input(UInt(INST_BITS.W))
        val decoded_inst = Output(ArchDecodedInst())
    })
}

abstract class ExceptionType {
    // enumerate number for each exception that would be used in HDL.
    // should be set by addExtype in ExceptionTrait to make it unique.
    var enum_no: UInt = 0xf.U
}

abstract class ExceptionDefns {
    private var extype_map = Seq[(UInt, ExceptionType)]()
    private def addExtype[T <: ExceptionType](extype: T): Unit = {
        if (extype_map.contains(extype.enum_no)) {
            println("Error: Duplicate exception type defined.")
            throw new IllegalArgumentException
        }
        extype_map = extype_map :+ (extype.enum_no -> extype)
    }

    val NONE: ExceptionType // describe no exception occured
    val INT:  ExceptionType

    def apply(): UInt
}

abstract class ExceptionInfo extends MkBundle {
    val extype   = ArchExceptionType()
    val pc       = UInt(VADDR_WIDTH.W)
    val mem_addr = UInt(VADDR_WIDTH.W)
}

abstract class MkCSRBundle extends MkBundle {
    def initData: UInt = 0.U(32.W)
    def rdata: UInt
    def getRealWdata(wdata: UInt): UInt
    def wmask = ~0.U(this.getWidth.W)
    def write(wdata: UInt): Unit = {
        val real_wdata = getRealWdata(wdata)
        val bools      = VecInit(this.asUInt.asBools)
        require(real_wdata.getWidth == this.getWidth)
        // println(this.className)
        for (i <- 0 until this.getWidth) {
            when(wmask(i)) {
                bools(i) := real_wdata(i)
            }
        }
        this := bools.asTypeOf(this)
    }
}

trait CSRRegistersDefns extends MkParams {
    val csr_defns: Seq[(UInt, () => MkCSRBundle)]
    def getExcpEntry(csr:   CSRVecBundle, excp_enum: UInt): UInt
    def getExcpRetAddr(csr: CSRVecBundle): UInt
}

class CSRVecBundle extends MkBundle {
    val csr_defns   = ArchCSRDefns.csr_defns
    val csr_vec     = MixedVec(csr_defns.map(csr => UInt(csr._2().getWidth.W)))
    val timer_cycle = UInt(64.W)

    def getTargetCSR[T <: MkCSRBundle](target_info: (UInt, () => T)): T    = {
        var index = csr_defns.indexOf(target_info)
        if (index == -1) {
            println("Error: target CSR doesn't exist in csr_defns")
            throw new IllegalArgumentException
        }
        csr_vec(index).asTypeOf(target_info._2())
    }
    def getExcpEntry(excp_enum: UInt):                                UInt = {
        ArchCSRDefns.getExcpEntry(this, excp_enum)
    }
    def getExcpRetAddr():                                             UInt = {
        ArchCSRDefns.getExcpRetAddr(this)
    }

}

abstract class ISAFactory {
    type ExcepDefns <: ExceptionDefns
    type CSRDefns <: CSRRegistersDefns

    def isaName:            String
    def getFetchUnit():     MkIFU
    def getDecoder():       DecoderUnit
    def getDecodedInst():   DecodedInst
    def getOperandGen():    OperandGenerator
    def getExcepDefns():    ExcepDefns
    def getExcepInfo():     ExceptionInfo
    def getLoadStoreUnit(): MkLSU
    def getBranchUnit():    MkBRU
    def getMiscFu():        MiscFunctionUnit
    def getCSRDefns():      CSRDefns
    def getCSRBuffer():     CSRBuffer
    def getCSRRegfiles():   CSRRegfiles

    val RESET_VECTOR: Int
    def CSR_ADDR_WD: Int
}
