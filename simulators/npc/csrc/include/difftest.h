#ifndef NEMU_DIFFTEST_H
#define NEMU_DIFFTEST_H

#include <npc.h>
#include <memory.h>
#include <verilator.h>

typedef struct {
    uint8_t  excp_valid   = 0;
    uint8_t  eret         = 0;
    uint32_t interrupt    = 0;
    uint32_t exception    = 0;
    uint32_t exceptionPC  = 0;
    uint32_t exceptionIst = 0;
} excp_event_t;

typedef struct {
    uint8_t  valid = 0;
    uint32_t pc;
    uint32_t inst;
    uint8_t  skip;
    uint8_t  wen;
    uint8_t  wdest;
    uint32_t wdata;
    uint32_t csr_data;
} instr_commit_t;

typedef struct {
    word_t gpr[32];
} arch_greg_state_t;

typedef struct {
    uint8_t  valid = 0;
    uint64_t paddr;
    uint64_t vaddr;
    uint64_t data;
} store_event_t;

typedef struct {
    uint8_t  valid = 0;
    uint64_t paddr;
    uint64_t vaddr;
} load_event_t;

typedef struct {
    word_t mstatus;
    word_t mie;
    word_t mtvec;
    word_t mscratch;
    word_t mepc;
    word_t mcause;
    word_t mtval;
    word_t mip;
} arch_csr_state_t;

typedef struct {
    // trap_event_t trap;
    excp_event_t      excp;
    instr_commit_t    commit;
    arch_greg_state_t regs;
    arch_csr_state_t  csr;
    store_event_t     store;
    load_event_t      load;
} difftest_core_state_t;

/* dut/ref core info */
extern difftest_core_state_t dut;

extern difftest_core_state_t ref;

extern uint32_t *dut_regs_ptr;
extern uint32_t *ref_regs_ptr;

typedef struct {
    word_t  gpr[32];
    vaddr_t pc;
} REF_GPR;

typedef struct {
    word_t mstatus;
    word_t mtvec;
    word_t mepc;
    word_t mcause;
} REF_CSR;

#endif
