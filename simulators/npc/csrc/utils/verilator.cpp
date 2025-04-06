#include <npc.h>
#include <verilator.h>

// toggle the clk 2 times

VerilatedContext *contextp;
VerilatedVcdC    *tfp;
Vsimu_top        *top;

void clock_step() {
    static uint64_t last_dump;
    if((contextp->time() - last_dump) > 1000000) {
        last_dump = contextp->time();
        tfp->close();
        tfp->open("./logs/simu_trace.vcd");
    } 
    for (int i = 0; i < 2; i++) {
        contextp->timeInc(1); // 1 timeprecision period passes...
        top->aclk = !top->aclk;
        tfp->dump(contextp->time());
        top->eval();
    }
    #ifdef CONFIG_NOMMU_LINUX
    static uint32_t timer_inc_flag = 0;
    void clint_update();
    if(timer_inc_flag == 10) {
        clint_update();
        timer_inc_flag = 0;
    } else {
        timer_inc_flag++;
    }
    #endif
}

void reset(int time) {
    clock_step();
    top->aresetn = 0;
    for (int i = 0; i < time; i++) { clock_step(); }
    top->aresetn = 1;
    clock_step();
}
