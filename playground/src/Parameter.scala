package miku

import chisel3._
import chisel3._


class MkParams {
    val FETCH_WIDTH = 1
    val DECODE_WIDTH = 1
    val RETIRE_WIDTH = 1
    val INST_BITS = 32
    val VADDR_WIDTH = 32
    val WORD_WIDTH = 32
    val REG_ADDR_WD = 32

    //BPU
    val RAS_SIZE = 8

    //ScoreBoard
    val NR_ENTRIES = 8
    val FU_STATUS  = 4
}

trait HasMkParams {
    val mkParams = new MkParams()
    
    val FETCH_WIDTH = mkParams.FETCH_WIDTH
    val DECODE_WIDTH = mkParams.DECODE_WIDTH
    val RETIRE_WIDTH = mkParams.RETIRE_WIDTH
    val INST_BITS = mkParams.INST_BITS
    val VADDR_WIDTH = mkParams.VADDR_WIDTH
    val WORD_WIDTH = mkParams.WORD_WIDTH

    val RAS_SIZE = mkParams.RAS_SIZE

    //ScoreBoard
    val NR_ENTRIES = mkParams.NR_ENTRIES
    val BITS_ENTRIES = log2Ceil(mkParams.NR_ENTRIES)
    val REG_ADDR_WD = mkParams.REG_ADDR_WD
    val REG_ADDR_SIZE = log2Ceil(mkParams.REG_ADDR_WD)
    val FU_STATUS_SIZE = log2Ceil(mkParams.FU_STATUS)

    def instBytes = INST_BITS / 8
    def wordBytes = WORD_WIDTH / 8
}

abstract class MkModule extends Module with HasMkParams{

}

abstract class MkBundle extends Bundle with HasMkParams{}
