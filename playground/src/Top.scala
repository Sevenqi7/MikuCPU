import chisel3._
import chisel3.util._

import miku._
import miku.utils._

class TopIO extends MkBundle{
    val axi = new AXIMasterIF(VADDR_WIDTH, WORD_WIDTH, 4)
    
}

class Top extends MkModule{
    val io = IO(new TopIO)
}
