#ifndef __VERILATOR_H
#define __VERILATOR_H

#include <memory>
#include <verilated.h>
#include "verilated_dpi.h"
#include <verilated_vcd_c.h>
#include "svdpi.h"
#include "Vsimu_top__Dpi.h"
#include "Vsimu_top.h"

extern Vsimu_top        *top;
extern VerilatedVcdC    *tfp;
extern VerilatedContext *contextp;

extern void clock_step();
extern void reset(int time);

#endif
