import chisel3._

object OpType{
    val OP_PLUS  = 0.U
    val OP_SUB   = 1.U
    val OP_JAL   = 2.U
    val OP_AND   = 3.U
    val OP_OR    = 4.U
    val OP_XOR   = 5.U
    val OP_SLL   = 6.U
    val OP_SRL   = 7.U
    val OP_SRA   = 8.U
    val OP_SLT   = 9.U
    val OP_SLTU  = 10.U
    val OP_MUL   = 11.U
    val OP_DIV   = 12.U
    val OP_DIVU  = 13.U
    val OP_REM   = 14.U
    val OP_REMU  = 15.U
    val OP_ADDW  = 16.U
    val OP_SUBW  = 17.U
    val OP_SLLW  = 18.U
    val OP_SRAW  = 19.U
    val OP_SRLW  = 20.U
    val OP_XORW  = 21.U
    val OP_ORW   = 22.U
    val OP_ANDW  = 23.U
    val OP_MULW  = 24.U
    val OP_DIVW  = 25.U
    val OP_DIVUW = 26.U
    val OP_REMW  = 27.U
    val OP_REMUW = 28.U
    val OP_ECALL = 29.U
    val OP_MRET  = 30.U
    val OP_NONE  = 31.U
}


object LSUOpType{
    val ld = "b10001".U
    val lw = "b01001".U
    val lh = "b00101".U
    val lb = "b00011".U
    val lwu = "b01000".U
    val lhu = "b00100".U
    val lbu = "b00010".U
    val sd = "b10000".U
    val sw = "b01000".U
    val sh = "b00100".U
    val sb = "b00010".U
}

object FuType{
    val alu = 0.U
    val lsu = 1.U
}

object InstType{
    val TYPE_I = 1.U(4.W)
    val TYPE_R = 2.U(4.W)
    val TYPE_U = 3.U(4.W)
    val TYPE_S = 4.U(4.W)
    val TYPE_J = 5.U(4.W)
    val TYPE_B = 6.U(4.W)
    val TYPE_E = 7.U(4.W)
    val TYPE_N = 8.U(4.W)
}

object FuSource{
    val ZERO = 0.U
    val PC   = 1.U
    val RS1  = 2.U
    val RS2  = 3.U
    val IMM  = 4.U
    val SHAMT = 5.U
    val NPC  = 6.U
    val CSR  = 7.U
}

object BType
{
    val BEQ  = 1.U
    val BNE  = 2.U
    val BLT  = 3.U
    val BLTU = 4.U
    val BGEU = 5.U
    val BGE  = 6.U
}