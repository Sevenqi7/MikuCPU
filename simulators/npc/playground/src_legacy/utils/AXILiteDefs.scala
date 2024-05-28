package AXILiteDefs
{

  import chisel3._
  import chisel3.util._

  class AXILiteAddress(addrWidth: Int) extends Bundle {
    val addr    = UInt(addrWidth.W)
    // val prot    = UInt(3.W)
  }

  class AXILiteWriteData(dataWidth: Int) extends Bundle {
    val data    = UInt(dataWidth.W)
    val strb    = UInt((dataWidth/8).W)
  }

  class AXILiteReadData(dataWidth: Int) extends Bundle {
    val data    = UInt(dataWidth.W)
    val resp    = UInt(2.W)
  }

  class AXILiteWriteResp extends Bundle {
    val resp    = UInt(2.W)
  }
  // Part II: Definitions for the actual AXI interfaces

  class AXILiteSlaveIF(addrWidth: Int, dataWidth: Int) extends Bundle {
    // write address channel
    val writeAddr   = Flipped(Decoupled(new AXILiteAddress(addrWidth)))
    // write data channel
    val writeData   = Flipped(Decoupled(new AXILiteWriteData(dataWidth)))
    // write response channel (for memory consistency)
    val writeResp   = Decoupled(UInt(2.W))
    
    // read address channel
    val readAddr    = Flipped(Decoupled(new AXILiteAddress(addrWidth)))
    // read data channel
    val readData    = Decoupled(new AXILiteReadData(dataWidth))
    
    
  }



  class AXILiteMasterIF(addrWidth: Int, dataWidth: Int) extends Bundle {  
    // write address channel
    val writeAddr   = Decoupled(new AXILiteAddress(addrWidth))
    // write data channel
    val writeData   = Decoupled(new AXILiteWriteData(dataWidth))
    // write response channel (for memory consistency)
    val writeResp   = Flipped(Decoupled(new AXILiteWriteResp))
    
    // read address channel
    val readAddr    = Decoupled(new AXILiteAddress(addrWidth))
    // read data channel
    val readData    = Flipped(Decoupled(new AXILiteReadData(dataWidth)))
    
  }

}
