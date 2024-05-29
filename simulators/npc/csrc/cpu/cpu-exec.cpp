#include <verilator.h>
#include <npc.h>
#include "difftest.h"
#include "macro.h"

#include <stdint.h>
#include <memory.h>
#include <string.h>

#define MAX_INST_TO_PRINT 10
#define MAX_ITRACE_STORE  10

char            g_itrace_buf[MAX_ITRACE_STORE][128];
static bool     g_print_step;
static uint64_t nr_bubble     = 0;
static uint32_t g_itrace_base = 0;
static uint32_t g_itrace_end  = 0;
static uint64_t nr_total_inst = 0;
#ifdef CONFIG_ITRACE
static uint32_t g_itrace_num = 0;
#endif

void device_update();
void ebreak(long long int halt_ret);
void difftest_regcpy(void *dut, bool direction);

static void trace_and_difftest(char *logbuf) {
    if (g_print_step) { puts(logbuf); }
#ifdef CONFIG_FTRACE
    void ftrace_check_jal(uint64_t jump_addr, uint64_t ret_addr, int rs1, int rd);
    int  rd = BITS(npc_state.inst, 11, 7), rs1 = BITS(npc_state.inst, 19, 15);
    ftrace_check_jal(top->io_WB_pc, npc_state.pc + 4, rs1, rd);
#endif
#ifdef CONFIG_WATCHPOINT
    if (check_watchpoints()) npc_state.state = NPC_STOP;
#endif

#ifdef CONFIG_DIFFTEST
    void difftest_step(vaddr_t pc);
    difftest_step(npc_state.pc);
#endif
}

void display_itrace() {
    printf("\nItrace Info : q\n\n");
    char printbuf[150];
    memset(printbuf, ' ', 150);
    int i = g_itrace_base;
    do {
        memcpy(&printbuf[10], g_itrace_buf[i], strlen(g_itrace_buf[i]) + 1);
        i = i < MAX_ITRACE_STORE - 1 ? i + 1 : 0;
        if (i == g_itrace_end) memcpy(printbuf, "-->", 3);
        printf("%s\n", printbuf);
    } while (i != g_itrace_end);
    printf("\nItrace Info End\n");
}

void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);

void exec_once() {
    instr_commit_t *cmt_inst = &dut.commit;
    excp_event_t   *excp     = &dut.excp;

    clock_step();
    int bubble_cnt = 0;
    while (!cmt_inst->valid & !excp->excp_valid) {
        clock_step();
        bubble_cnt++;
        if (bubble_cnt > 10000) { // deadlock
            printf("\033[0m\033[1;31m%s\033[0m\n", "Deadlock detected! NPC Stopped.");
            npc_state.state = NPC_STOP;
            return;
        }
        nr_bubble++;
    }
    // printf("cmt_valid:0x%x\n", cmt_inst->valid);
    // printf("cmt_inst:0x%x\n", cmt_inst->inst);
    // printf("cmt_pc:0x%x\n", cmt_inst->pc);
    npc_state.inst = cmt_inst->inst;
    npc_state.pc   = cmt_inst->pc;
    nr_total_inst++;
    if (cmt_inst->inst == EBREAK) {
        ebreak(dut_regs_ptr[10]);
        return;
    }
trace:
    static char logbuf[128];
#ifdef CONFIG_ITRACE
    char *p        = logbuf;
    p             += snprintf(p, sizeof(logbuf), VADDR_FMT ":", npc_state.pc);
    uint8_t *inst  = (uint8_t *)&npc_state.inst;
    for (int i = 3; i >= 0; i--) p += snprintf(p, 4, "%02x", inst[i]);
    // Log("logbuf:%s", logbuf);
    *p++ = ' ';
    disassemble(p, logbuf + sizeof(logbuf) - p, npc_state.pc, inst,
                4); // riscv64所有指令都是32位长
    memcpy(g_itrace_buf[g_itrace_end], logbuf, strlen(logbuf) + 1);
    if (g_itrace_num < MAX_ITRACE_STORE)
        g_itrace_num++;
    else
        g_itrace_base = g_itrace_base < MAX_ITRACE_STORE - 1 ? g_itrace_base + 1 : 0;
    g_itrace_end = g_itrace_end < MAX_ITRACE_STORE - 1 ? g_itrace_end + 1 : 0;
#endif

    trace_and_difftest(logbuf);
    cmt_inst->valid  = false;
    excp->excp_valid = false;
}

void execute(uint64_t n) {
    switch (npc_state.state) {
        case NPC_END:
        case NPC_ABORT:
            printf("Simulation has ended.\n");
            return;
        default:
            npc_state.state = NPC_RUNNING;
    }
    for (int i = 0; i < n; i++) {
        g_print_step = (n < MAX_INST_TO_PRINT);
        exec_once();
        device_update();
        if (npc_state.state != NPC_RUNNING) {
            Log("Total instruction number: %ld", nr_total_inst);
            Log("Recieve %ld bubbles when pipelines running", nr_bubble);
            break;
        }
    }

    if (npc_state.state == NPC_ABORT) {
        printf("\n\033[0m\033[1;31mNPC ABORT \033[0mat pc = " VADDR_FMT "\n", npc_state.pc);
#ifdef CONFIG_ITRACE
        display_itrace();
#endif
    }
}
