package AXIDefs
{

import chisel3._
import chisel3.util._

// Part I: Definitions for the actual data carried over AXI channels
// in part II we will provide definitions for the actual AXI interfaces
// by wrapping the part I types in Decoupled (ready/valid) bundles

// AXI channel data definitions

class AXIAddress(addrWidthBits: Int, idBits: Int) extends Bundle {
  // address for the transaction, should be burst aligned if bursts are used
  val addr    = UInt(addrWidthBits.W)
  // size of data beat in bytes
  // set to UInt(log2Up((dataBits/8)-1)) for full-width bursts
  val size    = UInt(3.W) 
  // number of data beats -1 in burst: max 255 for incrementing, 15 for wrapping
  val len     = UInt(8.W)
  // burst mode: 0 for fixed, 1 for incrementing, 2 for wrapping
  val burst   = UInt(2.W)
  // transaction ID for multiple outstanding requests
  val id      = UInt(idBits.W)
  // set to 1 for exclusive access
  val lock    = Bool()
  // cachability, set to 0010 or 0011
  val cache   = UInt(4.W)
  // generally ignored, set to to all zeroes
  val prot    = UInt(3.W)
  // not implemented, set to zeroes
  // val qos     = UInt(4.W)
  override def clone = { new AXIAddress(addrWidthBits, idBits).asInstanceOf[this.type] }
}

class AXIWriteData(dataWidthBits: Int) extends Bundle {
  val data    = UInt((dataWidthBits).W)
  val id      = Bool()
  val strb    = UInt((dataWidthBits / 8).W)
  val last    = Bool()
  override def clone = { new AXIWriteData(dataWidthBits).asInstanceOf[this.type] }
}

class AXIWriteResponse(idBits: Int) extends Bundle {
  val id      = UInt(idBits.W)
  val resp    = UInt(2.W)
  override def clone = { new AXIWriteResponse(idBits).asInstanceOf[this.type] }
}

class AXIReadData(dataWidthBits: Int, idBits: Int) extends Bundle {
  val data    = UInt(dataWidthBits.W)
  val id      = UInt(idBits.W)
  val last    = Bool()
  val resp    = UInt(2.W)
  override def clone = { new AXIReadData(dataWidthBits, idBits).asInstanceOf[this.type] }
}



// Part II: Definitions for the actual AXI interfaces

// TODO add full slave interface definition

class AXIMasterIF(addrWidthBits: Int, dataWidthBits: Int, idBits: Int) extends Bundle {  
  // write address channel
  val writeAddr   = Decoupled(new AXIAddress(addrWidthBits, idBits))
  // write data channel
  val writeData   = Decoupled(new AXIWriteData(dataWidthBits))
  // write response channel (for memory consistency)
  val writeResp   = Flipped(Decoupled(new AXIWriteResponse(idBits)))
  
  // read address channel
  val readAddr    = Decoupled(new AXIAddress(addrWidthBits, idBits))
  // read data channel
  val readData    = Flipped(Decoupled(new AXIReadData(dataWidthBits, idBits)))
  
  
  override def clone = { new AXIMasterIF(addrWidthBits, dataWidthBits, idBits).asInstanceOf[this.type] }
}

}
