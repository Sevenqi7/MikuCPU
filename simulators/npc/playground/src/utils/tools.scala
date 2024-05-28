import chisel3._
import chisel3.util._
import chisel3.util.experimental

object utils {
    
    def SEXT(x : UInt, len : Int) :UInt = {
        val ret = Wire(UInt(64.W))
        ret := Cat(Fill(64-len, x(len-1)), x(len-1, 0))
        ret
    }

    //connect lhs to rhs through registers with implict reset in Module
    def regConnect(lhs: Data, rhs: Data, resetVal: UInt =0.U): Unit = {
        val rhsReg = RegInit(chiselTypeOf(rhs), resetVal)
        rhsReg := rhs
        lhs := rhsReg
    }


    //connect lhs to rhs through registers with a given reset and stall in Module
    def regConnectWithStall(lhs :Data, rhs: Data, stall: Bool): Unit = {
        val rhsReg = RegInit(chiselTypeOf(rhs), 0.U)
            when(!stall){
                rhsReg := rhs
            }
            lhs := rhsReg        
    }

}

object AddressSpace{
    val MBASE = 0x80000000L.U
    val MSIZE = 0x8000000L.U
}

class CacheLine(tagWidth: Int, dataWidth: Int) extends Bundle{
    val tag  = UInt(tagWidth.W)
    val data = UInt(dataWidth.W)
    val valid = Bool()
}

class MyReadyValidIO extends Bundle{
    val ready = Input(Bool())
    val valid = Output(Bool())
}

class LIFO[T <: Data](gen: T, depth: Int) extends Module{
    val io = IO(new Bundle{
        val push = Input(gen)
        val pushEn = Input(Bool())
        val pop = Output(gen)
        val popEn = Input(Bool())
    })

    val foo   = Wire(gen)
    foo := 0.U.asTypeOf(gen)
    val stack = RegInit(VecInit.fill(depth)(foo))
    val sptr  = RegInit(0.U(log2Ceil(depth).W))
    val stop  = RegInit(0.U(log2Ceil(depth).W))

    when(io.pushEn & !io.popEn){
        stack(sptr) := io.push
        sptr        := Mux(sptr === (depth-1).U, 0.U, sptr+1.U)
        stop        := sptr
    }.elsewhen(!io.pushEn && io.popEn){
        sptr        := Mux(sptr === 0.U, (depth-1).U, sptr-1.U)
        stop        := sptr
    }      

    io.pop := Mux(io.popEn, stack(stop), 0.U)
}


//deqData always keeps the data corresponding to the end of the queue.
class FIFO[T <: Data](gen: T, depth: Int) extends Module{
    val io = IO(new Bundle{
        val enqValid = Input(Bool())
        val enqData  = Input(gen)
        val deqValid = Input(Bool())
        val deqData  = Output(gen)
        val empty    = Output(Bool())
        val full     = Output(Bool())
    })

    val foo     = Wire(gen)
    foo         := 0.U.asTypeOf(gen)
    val queue   = RegInit(VecInit.fill(depth)(foo))
    val qrear   = RegInit(0.U(log2Ceil(depth).W))
    val qptr    = RegInit(0.U(log2Ceil(depth).W))
    val qfront  = RegInit(0.U(log2Ceil(depth).W))
    val full    = RegInit(0.B)
    val empty   = RegInit(1.B)


    io.empty    := empty
    io.full     := full

    when(io.enqValid & !full){
        queue(qrear)    := io.enqData
        qrear           := qrear + 1.U
        empty       := 0.U
        when(qrear+1.U === qfront){
            full        := 1.U
        }
    }.elsewhen(!io.enqValid & io.deqValid & !empty){
        qfront          := qfront + 1.U
        full            := 0.U
        when(qfront+1.U === qrear){
            empty       := 1.U
        }
    }

    io.deqData          := queue(qfront)
}