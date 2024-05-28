#include <npc.h>
#include <verilator.h>

// toggle the clk 2 times

VerilatedContext *contextp;
VerilatedVcdC    *tfp;
Vsimu_top        *top;

void clock_step() {
    for (int i = 0; i < 2; i++) {
        contextp->timeInc(1); // 1 timeprecision period passes...
        top->aclk = !top->aclk;
        tfp->dump(contextp->time());
        top->eval();
    }
}

void reset(int time) {
    clock_step();
    top->aresetn = 0;
    for (int i = 0; i < time; i++) { clock_step(); }
    top->aresetn = 1;
    clock_step();
}
