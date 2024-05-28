#include "difftest.h"
#include <cstring>
#include <dlfcn.h>
#include <memory.h>
#include <npc.h>
#include <verilator.h>

void (*ref_difftest_memcpy)(paddr_t addr, void *buf, size_t n, bool direction) = NULL;
void (*ref_difftest_regcpy)(void *dut, bool direction)                         = NULL;
void (*ref_difftest_exec)(uint64_t n)                                          = NULL;
void (*ref_difftest_raise_intr)(uint64_t NO)                                   = NULL;

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

    ref_difftest_exec = (void (*)(uint64_t))dlsym(handle, "difftest_exec");
    assert(ref_difftest_exec);

    ref_difftest_raise_intr = (void (*)(uint64_t))dlsym(handle, "difftest_raise_intr");
    assert(ref_difftest_raise_intr);

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
    printf("break\n");
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

bool           is_skip_ref = false;
extern vaddr_t device_io_pc;

void difftest_step(vaddr_t pc) {
    REF_GPR from_ref;
    if (pc == device_io_pc) {
        device_io_pc = 0;
        is_skip_ref  = true;
        return;
    }
    if (is_skip_ref) {
        // ref.pc = npc_state.pc;

        from_ref.pc = pc;
        memcpy(from_ref.gpr, dut_regs_ptr, sizeof(from_ref.gpr));
        ref_difftest_regcpy(&from_ref, DIFFTEST_TO_REF);
        // Log("skip, pc:0x%lx, 0x%lx", pc, npc_state.pc);
        is_skip_ref = false;
        return;
    }
    ref_difftest_regcpy(&from_ref, DIFFTEST_TO_DUT);
    ref.commit.pc = from_ref.pc;
    ref_difftest_exec(1);
    ref_difftest_regcpy(&from_ref, DIFFTEST_TO_DUT);
    memcpy(ref_regs_ptr, &from_ref.gpr, sizeof(from_ref.gpr));
    checkregs();
}

#endif
