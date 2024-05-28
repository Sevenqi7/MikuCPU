import chisel3._
import chisel3.util._
import utils._

//axi return 64bits data within single read transaction
class ICache(tagWidth: Int, nrSets: Int, nrLines: Int, offsetWidth: Int) extends Module{
    val io = IO(new Bundle{
        //cache-pipeline
        val valid   = Input(Bool())
        val addr    = Input(UInt(64.W))
        val rdata   = Output(UInt(32.W))
        val hit     = Output(Bool()) 
        val arready = Output(Bool())
        val rvalid  = Output(Bool())
        val state   = Output(UInt(3.W))
        val miss    = Output(Bool())

        //debug
        val cache_tag = Output(UInt(tagWidth.W))
        val cache_set = Output(UInt(2.W))
        val cache_offset = Output(UInt(4.W))
        val cache_miss_cnt = Output(UInt(32.W))
        val lineBuf   = Output(UInt(128.W)) 

        //cache-axi
        val axi_busy        = Input(Bool())
        val axi_rreq        = Output(Bool())
        val axi_raddr       = Output(UInt(32.W))
        val axi_arready     = Input(Bool())
        val axi_rvalid      = Input(Bool())
        val axi_rlast       = Input(Bool())
        val axi_rdata       = Input(UInt(64.W))
    })

    val sIdle :: sLookup :: sMiss :: sRefill :: sReplace :: Nil = Enum(5)

    //statistic
    val cache_miss_cnt = RegInit(0.U(32.W))
    io.cache_miss_cnt   := cache_miss_cnt

    val cacheline = Wire(new CacheLine(tagWidth, 128))

    cacheline.tag   := 0.U
    cacheline.data  := 0.U
    cacheline.valid := 0.U
    val cache = RegInit(VecInit.fill(nrSets, nrLines)(cacheline))

    val setWidth  = log2Ceil(nrSets)
    val lineWidth = log2Ceil(nrLines)
    val dataWidth = 128
    // val dataWidth = (Math.pow(2, offsetWidth) * 8).toInt

    //buffer of req
    val req_addr  = RegInit(0.U(64.W))
    val req_valid = RegInit(0.B)

    val offset    = req_addr(offsetWidth - 1, 0)
    val set       = req_addr(offsetWidth + setWidth - 1, offsetWidth)
    val tag       = req_addr(offsetWidth + setWidth + tagWidth -1 , offsetWidth + setWidth)
    val index     = 127.U - offset * 8.U
    
    val state           = RegInit(sIdle)
    val lineBuf         = RegInit(0.U(dataWidth.W))

    io.lineBuf          := lineBuf
    io.cache_offset     := offset
    io.cache_set        := set
    io.cache_tag        := tag

    io.state        := state

    //initialise
    io.hit          := 0.U
    io.arready      := 0.U
    io.rdata        := 0x7777.U
    io.rvalid       := 0.U
    io.axi_rreq     := 0.U
    io.axi_raddr    := 0.U
    io.miss         := !io.rvalid & req_valid
    

    //FSM
    val refillIDX       = Wire(UInt(lineWidth.W))
    val refillHit       = Wire(Bool())
    refillIDX           := 0.U
    refillHit           := 0.U

    switch(state){
        is (sIdle){
            when(io.valid){
                state       := sLookup
                io.arready  := 1.U
                req_valid   := io.valid
                req_addr    := io.addr
            }
        }
        is (sLookup){
            for(i <- 0 until nrLines-1){
                when(cache(set)(i).tag === tag && cache(set)(i).valid){
                    io.hit      := 1.U
                    io.rvalid   := 1.U
                    switch(offset){
                        is ("b0000".U){ io.rdata := cache(set)(i).data(dataWidth-33, dataWidth-64 )}
                        is ("b0100".U){ io.rdata := cache(set)(i).data(dataWidth-1 , dataWidth-32 )}
                        is ("b1000".U){ io.rdata := cache(set)(i).data(31, 0)}
                        is ("b1100".U){ io.rdata := cache(set)(i).data(dataWidth-65, dataWidth-96 )}
                    }
                }
            }    
            when(!io.hit){
                state           := sMiss
            }
            .elsewhen(io.valid){
                state           := sLookup
                io.arready      := 1.U
                req_valid       := io.valid
                req_addr        := io.addr
            }
            .otherwise{
                state           := sIdle
                io.arready      := 0.U
            }
        }
        is (sMiss){
            io.axi_rreq         := 1.U
            when(!io.axi_arready | io.axi_busy){ 
                state           := sMiss
            }       
            .otherwise{
                io.axi_raddr    := req_addr & (0xFFFFFFFFL.U << offsetWidth)
                state           := sRefill
            }
        }
        is (sRefill){
            state           := sRefill
            io.axi_rreq     := 1.U
            io.axi_raddr    := req_addr & (0xFFFFFFFFL.U << offsetWidth)
            when(io.axi_rvalid){
                lineBuf         := (lineBuf << 64) | io.axi_rdata
            }
            when(io.axi_rlast){
                state       := sReplace
            }
            .elsewhen(io.axi_busy){
                state       := sMiss
            }
        }   
        is (sReplace){
            state                       := sIdle
            for(i <- 0 until nrLines-1){
                when(!cache(set)(i).valid){
                    refillHit           := 1.U
                    refillIDX           := i.U
                }
            }
            for(i  <- 0 until nrLines-1){
                when(cache(set)(i).valid & tag === cache(set)(i).tag){
                    refillHit           := 1.U
                    refillIDX           := i.U
                }
            }
            when(!refillHit){
                refillIDX               := random.LFSR(16)(lineWidth-1, 0)
            }
            cache(set)(refillIDX).valid := 1.U
            cache(set)(refillIDX).tag   := tag
            cache(set)(refillIDX).data  := lineBuf
            io.axi_rreq                 := 0.U

            cache_miss_cnt              := cache_miss_cnt+1.U
        }
    }

}
