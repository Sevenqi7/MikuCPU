#include "npc.h"
#include "verilator.h"
#include "memory.h"
#include "device.h"
#include "difftest.h"

#include <sys/time.h>

extern uint32_t *vgactl_port_base;
extern void     *vmem;

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
    init_clint();
    init_vga();
}

word_t device_read(vaddr_t addr, int len) {
    assert(addr >= MMIO_BASE && addr < MMIO_END);
    // Log("device_io_read addr:" VADDR_FMT, addr);
    // Log("device_io_read at pc: " VADDR_FMT , npc_state.pc);
    // if(addr >= SERIAL_PORT <= SERAIL_PORT)
    if(addr >= SERIAL_BASE && addr <= SERIAL_END){
        return serial_read(addr & 0xf, 1) << ((addr & 0xf) * 8);
    }
    else if(addr >= CLINT_BASE && addr <= CLINT_END) {
        return clint_read(addr & 0xffff, len) << ((addr & 0xf) * 8);
    }
    else if (addr == RTC_ADDR) {
        return get_time();
    }
    else if (addr == SYNC_ADDR) {
        assert(len == 4);
        return vgactl_port_base[1];
    }
    else if (addr == VGACTL_ADDR) {
        assert(len == 4);
        return vgactl_port_base[0];
    }
    else if (addr >= FB_ADDR && addr < FB_ADDR + 480000){
        assert(len == 4);
        return ((uint32_t *)vmem)[(addr - FB_ADDR) / 4];
    }
    else {
        Log("addr: " VADDR_FMT, addr);
        Log("pc:%016lx", npc_state.pc);
        npc_state.state = NPC_STOP;
        // assert(0);
        return -1;
    }
}

void device_write(vaddr_t addr, word_t data, int len) {
    assert(addr >= MMIO_BASE && addr < MMIO_END);
    // Log("device_io_write at pc: " VADDR_FMT , npc_state.pc);
    // Log("addr: " VADDR_FMT ", data: " VADDR_FMT ", len: " VADDR_FMT, addr, data, len);
    if (addr >= SERIAL_BASE && addr <= SERIAL_END)
        serial_write(addr & 0xf, data >> ((addr & 0x3) * 8), len);
    else if(addr >= CLINT_BASE && addr <= CLINT_END) {
        return clint_write(addr & 0xffff, data >> ((addr & 0x3) * 8), len);
    }
    else if (addr == SYNC_ADDR) {
        assert(len == 4);
        vgactl_port_base[1] = data;
    } else if (addr == VGACTL_ADDR) {
        assert(len == 4);
        vgactl_port_base[0] = data;
    } else if (addr >= FB_ADDR && addr < FB_ADDR + 480000) {
        switch (len) {
            case 1:
                ((uint8_t *)vmem)[addr - FB_ADDR] = data;
                break;
            case 2:
                ((uint16_t *)vmem)[(addr - FB_ADDR) / sizeof(uint16_t)] = data;
                break;
            case 4:
                ((uint32_t *)vmem)[(addr - FB_ADDR) / sizeof(uint32_t)] = data;
                break;
#ifdef CONFIG_RV64
            case 8:
                ((uint64_t *)vmem)[(addr - FB_ADDR) / sizeof(uint64_t)] = data;
                break;
#endif
            default:
                Log("unsupport write len!");
                assert(0);
        }
        assert(len == 4);
        // ((uint32_t *)vmem)[(int)((addr - FB_ADDR) / 4 + offset)] = data;
    } else {
        Log("addr: " VADDR_FMT, addr);
        npc_state.state = NPC_STOP;
        // assert(0);
    }
}

void device_update() {
    vga_update_screen();
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
