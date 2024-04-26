package miku

import chisel3._
import chisel3.util._

class MkParams {
    val FETCH_WIDTH  = 1
    val DECODE_WIDTH = 1
    val RETIRE_WIDTH = 1
    val INST_BITS    = 32
    val VADDR_WIDTH  = 32
    val PADDR_WIDTH  = 32
    val WORD_WIDTH   = 32
    val REG_ADDR_NUM = 32
    val REG_RD_PORTS = 3

    val INST_QUEUE_SIZE = 32

    // BPU
    val RAS_SIZE = 8

    // TLB
    val TLB_NUM = 32

    /* Cache
                        tag_wd
                          | offset_wd
                          |  | way line_wd
                          |  |  |    | read-only
                          |  |  |    |    |         */
    val ICACHE_PARAMS = (20, 4, 2, 128, true)
    val DCACHE_PARAMS = (20, 4, 2, 128, false)

    // ScoreBoard and issue
    val NR_ENTRIES  = 8
    val NR_WB_PORTS = 2

    val TIMER_WD = 32

    val DIFFTEST_MODE  = true // used to generate port for difftest
    val RESET_VECTOR   = 0x1bfffffc
    val DEBUG_MAGICNUM = 0x77777777
}

trait HasMkParams {
    val mkParams = new MkParams()

    val FETCH_WIDTH  = mkParams.FETCH_WIDTH
    val DECODE_WIDTH = mkParams.DECODE_WIDTH
    val RETIRE_WIDTH = mkParams.RETIRE_WIDTH
    val INST_BITS    = mkParams.INST_BITS
    val VADDR_WIDTH  = mkParams.VADDR_WIDTH
    val PADDR_WIDTH  = mkParams.PADDR_WIDTH
    val WORD_WIDTH   = mkParams.WORD_WIDTH

    val RAS_SIZE        = mkParams.RAS_SIZE
    val INST_QUEUE_SIZE = mkParams.INST_QUEUE_SIZE

    // ScoreBoard
    val NR_ENTRIES    = mkParams.NR_ENTRIES
    val BITS_ENTRIES  = log2Ceil(mkParams.NR_ENTRIES)
    val TRANS_ID_BITS = log2Ceil(mkParams.NR_ENTRIES)
    val REG_ADDR_WD   = log2Ceil(mkParams.REG_ADDR_NUM)
    val REG_ADDR_NUM  = mkParams.REG_ADDR_NUM
    val REG_RD_PORTS  = mkParams.REG_RD_PORTS

    // TLB
    val TLB_NUM = mkParams.TLB_NUM

    // Cache
    val ICACHE_PARAMS = mkParams.ICACHE_PARAMS
    val DCACHE_PARAMS = mkParams.DCACHE_PARAMS

    val DIFFTEST_MODE  = mkParams.DIFFTEST_MODE
    val RESET_VECTOR   = mkParams.RESET_VECTOR
    val DEBUG_MAGICNUM = mkParams.DEBUG_MAGICNUM
    val NR_WB_PORTS    = mkParams.NR_WB_PORTS

    def instBytes = INST_BITS / 8
    def wordBytes = WORD_WIDTH / 8
}

abstract class MkModule extends Module with HasMkParams {}

abstract class MkBundle extends Bundle with HasMkParams {}
