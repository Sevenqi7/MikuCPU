#include <verilator.h>
#include <npc.h>
#include <memory.h>
#include <device.h>

#include <sys/time.h>

static uint8_t pmem[MEMSIZE] __attribute((aligned(4096)));

extern uint8_t *guest_to_host(paddr_t paddr) {
    return pmem + (paddr & MEMMASK);
}

void   device_write(vaddr_t addr, word_t data, int len);
word_t device_read(vaddr_t addr);

uint64_t *pmem_addr(vaddr_t addr) {
    return (uint64_t *)(pmem + ((uint64_t)addr & 0xFFFFFF));
}

void outofbound(paddr_t paddr) {
    if (paddr >= MEMSIZE) {
        printf("\033[0m\033[1;31m%s addr: " PADDR_FMT "\033[0m\n", "Addr out of bound, ", paddr);
        exit(-1);
    }
}

uint64_t get_time();

word_t pmem_read(vaddr_t addr, int len) {
    paddr_t paddr = addr & MEMMASK;
    // Log("paddr:%lx", paddr);
    if (addr > MMIO_BASE && addr < MMIO_END) return device_read(addr);
    outofbound(paddr);
    assert(paddr < MEMSIZE);
    int ret = 0;
    switch (len) {
        case 0:
            return 0;
        case 1:
            return *(uint8_t *)(pmem + paddr);
        case 2:
            return *(uint16_t *)(pmem + paddr);
        case 4:
            return *(uint32_t *)(pmem + paddr);
#ifdef CONFIG_RV64
        case 8:
            return *(uint64_t *)(pmem + paddr);
#endif
        default:
            printf("\033[0m\033[1;31mInvalid read len:%d at PC:" VADDR_FMT "\033[0m\n", len, npc_state.pc);
            npc_state.state = NPC_ABORT;
    }
    return 0;
}

void pmem_write(vaddr_t addr, int len, word_t data) {
    vaddr_t paddr = addr & MEMMASK;
    if (addr == 0x87fffffe) {
        putchar((char)data);
        return;
    }
    if (addr > MMIO_BASE && addr < MMIO_END) {
        device_write(addr, data, len);
        return;
    }
    outofbound(paddr);
    int ret = 0;
    switch (len) {
        case 1:
            *(uint8_t *)(pmem + paddr) = data;
            return;
        case 2:
            *(uint16_t *)(pmem + paddr) = data;
            return;
        case 4:
            *(uint32_t *)(pmem + paddr) = data;
            return;
#ifdef CONFIG_RV64
        case 8:
            *(uint64_t *)(pmem + paddr) = data;
            return;
#endif
        default:
            printf("\033[0m\033[1;31mInvalid wirte len:%d at PC: " VADDR_FMT "\033[0m\n", len, npc_state.pc);
            npc_state.state = NPC_ABORT;
    }
}

extern "C" void dci_pmem_read(long long raddr, long long *rdata, char rmask) {
    // 总是读取地址为`raddr & ~0x7ull`的8字节返回给`rdata`
    int     len  = 0;
    uint8_t mask = rmask;
    if (!top->aresetn) return;
    for (; mask; mask = mask >> 1, len++);
    *rdata = pmem_read(raddr, len);
#ifdef CONFIG_DEBUGMSG
    Log("raddr:0x%lx value:0x%lx len:%d", raddr, *rdata, len);
#endif
}

extern "C" void dci_pmem_write(long long waddr, long long wdata, char wmask) {
    // 总是往地址为`waddr & ~0x7ull`的8字节按写掩码`wmask`写入`wdata`
    // `wmask`中每比特表示`wdata`中1个字节的掩码,
    // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
    int     len  = 0;
    uint8_t mask = wmask;
    if (!top->aresetn) return;
    for (; mask; mask = mask >> 1, len++);
    pmem_write(waddr, len, wdata);
#ifdef CONFIG_DEBUGMSG
    Log("waddr:0x%lx value:0x%lx len:%d", waddr, wdata, len);
#endif
}
