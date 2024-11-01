#include "difftest.h"
#include <cstring>
#include <dlfcn.h>
#include <memory.h>
#include <npc.h>
#include <verilator.h>

void (*ref_difftest_memcpy)(paddr_t addr, void *buf, size_t n, bool direction) = NULL;
void (*ref_difftest_regcpy)(void *dut, bool direction)                         = NULL;
void (*ref_difftest_csrcpy)(void *dut, bool direction)                         = NULL;
void (*ref_difftest_exec)(uint64_t n)                                          = NULL;
void (*ref_difftest_raise_intr)(bool intr, word_t code)                        = NULL;
void (*ref_difftest_dump_state)(void)                                          = NULL;

difftest_core_state_t dut;
difftest_core_state_t ref;

uint32_t *dut_regs_ptr = (uint32_t *)&dut.regs;
uint32_t *ref_regs_ptr = (uint32_t *)&ref.regs;

#ifdef CONFIG_DIFFTEST

extern bool difftest_checkregs();

extern long img_size;

void init_difftest(const char *ref_so_file, long img_size, int port) {
    assert(ref_so_file != NULL);

    void *handle;
    handle = dlopen(ref_so_file, RTLD_LAZY);
    assert(handle);

    ref_difftest_memcpy = (void (*)(paddr_t, void *, size_t, bool))dlsym(handle, "difftest_memcpy");
    assert(ref_difftest_memcpy);

    ref_difftest_regcpy = (void (*)(void *, bool))dlsym(handle, "difftest_regcpy");
    assert(ref_difftest_regcpy);

    ref_difftest_csrcpy = (void (*)(void *, bool))dlsym(handle, "difftest_csrcpy");
    assert(ref_difftest_csrcpy);

    ref_difftest_exec = (void (*)(uint64_t))dlsym(handle, "difftest_exec");
    assert(ref_difftest_exec);

    ref_difftest_raise_intr = (void (*)(bool, word_t))dlsym(handle, "difftest_raise_intr");
    assert(ref_difftest_raise_intr);

    ref_difftest_dump_state = (void (*)(void))dlsym(handle, "difftest_dump_state");
    assert(ref_difftest_dump_state);

    void (*ref_difftest_init)(int) = (void (*)(int))dlsym(handle, "difftest_init");
    assert(ref_difftest_init);

    Log("Differential testing: %s", ANSI_FMT("ON", ANSI_FG_GREEN));
    Log("The result of every instruction will be compared with %s. "
        "This will help you a lot for debugging, but also significantly reduce "
        "the performance. "
        "If it is not necessary, you can turn it off in menuconfig.",
        ref_so_file);

    REF_GPR to_ref = {.pc = RESET_VECTOR};
    memcpy(to_ref.gpr, dut_regs_ptr, sizeof(to_ref.gpr));
    ref_difftest_init(port);
    ref_difftest_memcpy(RESET_VECTOR, guest_to_host(RESET_VECTOR), img_size, DIFFTEST_TO_REF);
    ref_difftest_regcpy(&to_ref, DIFFTEST_TO_REF);
    dut.commit.valid = 0;
}

static void checkregs() {
    if (!difftest_checkregs()) {
        npc_state.state = NPC_ABORT;
        reg_display();
    }
}

bool is_skip_ref = false;

extern bool    check_mmio_access();
extern vaddr_t device_io_pc;

typedef struct {
    char    *name;
    uint16_t addr;
    word_t   value;
} NEMU_CSR;

typedef struct {
    NEMU_CSR mstatus;
    NEMU_CSR mie;
    NEMU_CSR mtvec;
    NEMU_CSR mscratch;
    NEMU_CSR mepc;
    NEMU_CSR mcause;
    NEMU_CSR mtval;
    NEMU_CSR mip;
} NEMU_CSR_Set;

void difftest_step(vaddr_t pc) {
    // return ;
    REF_GPR      from_ref;
    NEMU_CSR_Set nemu_csr;
    if (check_mmio_access()) { return; }
    if (is_skip_ref) {
        from_ref.pc = pc;
        memcpy(from_ref.gpr, dut_regs_ptr, sizeof(from_ref.gpr));
        ref_difftest_regcpy(&from_ref, DIFFTEST_TO_REF);
        // Log("skip, pc: " VADDR_FMT, npc_state.pc);
        is_skip_ref = false;
    }
    if (dut.excp.excp_valid) {
        printf("excp detected\n");
        ref_difftest_raise_intr(false, dut.excp.exception);
        return;
    }
    ref_difftest_regcpy(&from_ref, DIFFTEST_TO_DUT);
    ref.commit.pc = from_ref.pc;
    // Log("pc1:" VADDR_FMT, from_ref.pc);
    ref_difftest_exec(1);
    ref_difftest_regcpy(&from_ref, DIFFTEST_TO_DUT);
    ref_difftest_csrcpy(&nemu_csr, DIFFTEST_TO_DUT);

    NEMU_CSR *csr_p     = (NEMU_CSR *)&nemu_csr;
    word_t   *ref_csr_p = (word_t *)&ref.csr;
    for (int i = 0; i < sizeof(NEMU_CSR_Set) / sizeof(NEMU_CSR); i++) {
        *ref_csr_p = csr_p->value;
        csr_p++, ref_csr_p++;
    }

    // Log("pc2:" VADDR_FMT, from_ref.pc);
    memcpy(ref_regs_ptr, &from_ref.gpr, sizeof(from_ref.gpr));
    checkregs();
}

#endif
