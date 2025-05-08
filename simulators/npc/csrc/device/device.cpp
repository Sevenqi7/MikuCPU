#include "npc.h"
#include "verilator.h"
#include "memory.h"
#include "device.h"
#include "difftest.h"

#include <sys/time.h>

// extern uint32_t *vgactl_port_base;
extern void *vmem;

static uint64_t boot_time = 0;

void     vga_update_screen();
uint64_t get_time_internal();
uint64_t get_time();

vaddr_t     device_io_pc = -1;
extern bool is_skip_ref;

bool check_mmio_access() {
    // is store or load inst
    bool store_inst = dut.store.valid;
    bool load_inst  = dut.load.valid;
    if (store_inst | load_inst) {
        // is addr in MMIO
        vaddr_t addr = store_inst ? dut.store.vaddr : dut.load.vaddr;
        if (addr >= MMIO_BASE && addr < MMIO_END) {
            device_io_pc = npc_state.pc;
            is_skip_ref  = true;
            // Log("pc: 0x%x, addr: 0x%x", npc_state.pc, addr);
            return true;
        }
    }
    return false;
}

void init_device() {
    IFDEF(CONFIG_HAS_SERIAL, init_serial());
    IFDEF(CONFIG_HAS_CLINT, init_clint());
    IFDEF(CONFIG_HAS_VGA, init_vga());
}

void device_update() {
    IFDEF(HAS_VGA, vga_update_screen());
}

uint64_t get_time_internal() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC_COARSE, &now);
    uint64_t us = now.tv_sec * 1000000 + now.tv_nsec / 1000;
    return us;
}

uint64_t get_time() {
    if (boot_time == 0) boot_time = get_time_internal();
    uint64_t now = get_time_internal();
    return now - boot_time;
}
