#ifndef NPC_INTERFACE_H
#define NPC_INTERFACE_H

#include "autoconf.h"
#include "difftest.h"
#include <stdint.h>

/**
 * Headers for Verilog DPI-C difftest interface
 * These hearders are called to copy signals of dut
 */
#define DIFFTEST_DPIC_FUNC_NAME(name) v_difftest_##name

#define DIFFTEST_DPIC_FUNC_DECL(name) \
    extern "C" void DIFFTEST_DPIC_FUNC_NAME(name)

#define DPIC_ARG_BIT  uint8_t
#define DPIC_ARG_BYTE char
#define DPIC_ARG_INT  int
#define DPIC_ARG_LONG long long

#define INTERFACE_INSTR_COMMIT           \
    DIFFTEST_DPIC_FUNC_DECL(InstrCommit) \
    (DPIC_ARG_BYTE index,                \
     DPIC_ARG_BIT  valid,                \
     DPIC_ARG_LONG pc,                   \
     DPIC_ARG_INT  instr,                \
     DPIC_ARG_BIT  skip,                 \
     DPIC_ARG_BIT  wen,                  \
     DPIC_ARG_BYTE wdest,                \
     DPIC_ARG_LONG wdata)

// v_difftest_GRegState
#define INTERFACE_GREG_STATE           \
    DIFFTEST_DPIC_FUNC_DECL(GRegState) \
    (DPIC_ARG_LONG gpr_0,              \
     DPIC_ARG_LONG gpr_1,              \
     DPIC_ARG_LONG gpr_2,              \
     DPIC_ARG_LONG gpr_3,              \
     DPIC_ARG_LONG gpr_4,              \
     DPIC_ARG_LONG gpr_5,              \
     DPIC_ARG_LONG gpr_6,              \
     DPIC_ARG_LONG gpr_7,              \
     DPIC_ARG_LONG gpr_8,              \
     DPIC_ARG_LONG gpr_9,              \
     DPIC_ARG_LONG gpr_10,             \
     DPIC_ARG_LONG gpr_11,             \
     DPIC_ARG_LONG gpr_12,             \
     DPIC_ARG_LONG gpr_13,             \
     DPIC_ARG_LONG gpr_14,             \
     DPIC_ARG_LONG gpr_15,             \
     DPIC_ARG_LONG gpr_16,             \
     DPIC_ARG_LONG gpr_17,             \
     DPIC_ARG_LONG gpr_18,             \
     DPIC_ARG_LONG gpr_19,             \
     DPIC_ARG_LONG gpr_20,             \
     DPIC_ARG_LONG gpr_21,             \
     DPIC_ARG_LONG gpr_22,             \
     DPIC_ARG_LONG gpr_23,             \
     DPIC_ARG_LONG gpr_24,             \
     DPIC_ARG_LONG gpr_25,             \
     DPIC_ARG_LONG gpr_26,             \
     DPIC_ARG_LONG gpr_27,             \
     DPIC_ARG_LONG gpr_28,             \
     DPIC_ARG_LONG gpr_29,             \
     DPIC_ARG_LONG gpr_30,             \
     DPIC_ARG_LONG gpr_31)

#endif
