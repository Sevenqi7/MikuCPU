#include <verilator.h>
#include <npc.h>
#include <memory.h>
#include <device.h>

#include <sys/time.h>

static uint8_t pmem[MEMSIZE] __attribute((aligned(4096)));

extern uint8_t *guest_to_host(paddr_t paddr) {
    return pmem + (paddr & MEMMASK);
}

uint64_t *pmem_addr(vaddr_t addr) {
    return (uint64_t *)(pmem + ((uint64_t)addr & MEMMASK));
}

bool outofbound(paddr_t paddr) {
    if (paddr >= MEMSIZE) {
        printf("\033[0m\033[1;31m%s addr: " PADDR_FMT "\033[0m\n", "Addr out of bound, ", paddr);
        // exit(-1);
        npc_state.state = NPC_ABORT;
        return true;
    }
    return false;
}

uint64_t get_time();

word_t pmem_read(vaddr_t addr, int len) {
    paddr_t paddr = addr & MEMMASK;
    // Log("paddr:%lx", paddr);
    // assert(addr != 0x11000000);
    outofbound(paddr);
    assert(paddr < MEMSIZE);
    word_t rdata = host_read(pmem + paddr, len);
    if (npc_state.state == NPC_ABORT)
        printf("\033[0m\033[1;31mInvalid read len:%d at addr:" VADDR_FMT " PC:" VADDR_FMT"\033[0m\n", len, addr, npc_state.pc);
    return rdata;
}

void pmem_write(vaddr_t addr, int len, word_t data) {
    vaddr_t paddr = addr & MEMMASK;
    // paddr &= ~0x3;
    outofbound(paddr);
    int ret = 0;
    host_write(pmem + paddr, len, data);
    if (npc_state.state == NPC_ABORT)
        printf("\033[0m\033[1;31mInvalid wirte len:%d at PC: " VADDR_FMT "\033[0m\n", len, npc_state.pc);
}

word_t paddr_read(vaddr_t addr, int len) {
    if (in_pmem(addr)) return pmem_read(addr, len);
    return mmio_read(addr, len);
}

void paddr_write(vaddr_t addr, int len, word_t data) {
    if (in_pmem(addr))
        pmem_write(addr, len, data);
    else
        mmio_write(addr, len, data);
}

extern "C" void dci_pmem_read(long long raddr, long long *rdata, char rsize) {
    int     len  = 1 << rsize;
    if (!top->aresetn) return;
    if (in_pmem(raddr)) {
        *rdata = pmem_read(raddr, len) << ((raddr & 0x3) * 8);
    } else
        *rdata = paddr_read(raddr, len) << ((raddr & 0x3) * 8);
    // if (raddr >= MMIO_BASE && raddr < MMIO_END)
    //     *rdata = device_read(raddr, len);
    // else
    //     *rdata = pmem_read(raddr & ~0x3, len);
#ifdef CONFIG_DEBUGMSG
    Log("raddr:0x%lx value:0x%lx len:%d", raddr, *rdata, len);
#endif
}

extern "C" void dci_pmem_write(long long waddr, long long wdata, char wmask) {
    int     len  = 0;
    uint8_t mask = wmask;
    if (!top->aresetn) return;
#ifdef CONFIG_RV64
    word_t prev_data = pmem_read(waddr & ~0x3, 8);
#else
    word_t prev_data = in_pmem(waddr) ? pmem_read(waddr & ~0x3, 4) : wdata;
#endif
    for (int byte = 0; mask > 0; mask = mask >> 1, byte++) {
        if (mask & 0x1) {
            len++;
            prev_data = REPLACE_BYTE(prev_data, wdata, byte);
        }
    }
    if (in_pmem(waddr))
        pmem_write(waddr & ~0x3, 4, prev_data);
    else
        paddr_write(waddr, len, wdata);
//     if (waddr >= MMIO_BASE && waddr < MMIO_END) {
//         device_write(waddr, wdata, len);
//         return;
//     }

// #ifdef CONFIG_RV64
//     pmem_write(waddr & ~0x3, 8, prev_data);
// #else
//     pmem_write(waddr & ~0x3, 4, prev_data);
// #endif
#ifdef CONFIG_DEBUGMSG
    Log("waddr:0x%lx value:0x%lx len:%d", waddr, wdata, len);
#endif
}
