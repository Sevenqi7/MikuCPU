package miku.frontend

import chisel3._
import chisel3.util._

import miku._
import miku.frontend._


//operation number source


abstract trait DeconderConstants {
    def X = BitPat("b?")
    def N = BitPat("b0")
    def Y = BitPat("b1")

    def decodeDefault: List[BitPat] = 
//       src1          src2       src3       src4   FuncUnit rfwen  
//         |            |          |          |        |       | flush          
//         |            |          |          |        |       |  |    SelImm
//         |            |          |          |        |       |  |     |
    List(SrcType.X, SrcType.X, SrcType.X, SrcType.X, FuType.X, N, N, SelImm.X)    
}



