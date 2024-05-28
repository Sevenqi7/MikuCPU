#include <npc.h>
#include <memory.h>
#include <difftest.h>

#include <string.h>

const char *riscv_regstr[] = {"$0", "ra", "sp", "gp", "tp",  "t0",  "t1", "t2", "s0", "s1", "a0",
                              "a1", "a2", "a3", "a4", "a5",  "a6",  "a7", "s2", "s3", "s4", "s5",
                              "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

#ifdef CONFIG_DIFFTEST

bool difftest_checkregs() {
    if (ref.commit.pc != dut.commit.pc) {
        Log("Difftest found PC value is 0x%lx, should be 0x%lx", dut.commit.pc, ref.commit.pc);
        return false;
    }
    for (int i = 0; i < 32; i++) {
        if (ref_regs_ptr[i] != dut_regs_ptr[i]) {
            Log("Difftest found %s value is 0x%lx, should be 0x%lx",
                riscv_regstr[i],
                dut_regs_ptr[i],
                ref_regs_ptr[i]);
            return false;
        }
    }
    return true;
}
#endif

void reg_display() {
    for (int i = 0; i < 32; i++) { printf("%d: %s = 0x%016lx\n", i, riscv_regstr[i], dut_regs_ptr[i]); }
}

word_t reg_str2val(const char *s, bool *success) {
    int i;
    *success = false;
    for (i = 1; i < 32; i++)
        if (!strcmp(s + 1, riscv_regstr[i])) break;
    if (!strcmp(s, riscv_regstr[0])) {
        *success = true;
        return 0;
    }
    if (!strcmp(s, "$pc")) {
        *success = true;
        return npc_state.pc;
    }
    if (i < 32) {
        *success = true;
        return dut_regs_ptr[i];
    } else
        return 0;
}
