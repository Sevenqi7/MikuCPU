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
word_t device_read(vaddr_t addr, int len);

uint64_t *pmem_addr(vaddr_t addr) {
    return (uint64_t *)(pmem + ((uint64_t)addr & MEMMASK));
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
    // assert(addr != 0x11000000);
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
    // for (; mask; mask = mask >> 1, len++);
    for(int i=0;i < sizeof(word_t);i++) {
        if(mask & 0x1) len++;
        mask >>= 1;
    }
    if (raddr >= MMIO_BASE && raddr < MMIO_END) 
        *rdata = device_read(raddr, len);
    else    
        *rdata = pmem_read(raddr & ~0x3, len);
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
    // for(int i=0;i < sizeof(word_t);i++) {
    //     if(mask & 0x1) len++;
    //     mask >>= 1;
    // }
    #ifdef CONFIG_RV64
    word_t prev_data = pmem_read(waddr & ~0x3, 8);
    #else 
    word_t prev_data = pmem_read(waddr & ~0x3, 4);
    #endif
    for (int byte = 0; mask > 0; mask = mask >> 1, byte++) {
        if(mask & 0x1) {
            len++;
            prev_data = REPLACE_BYTE(prev_data, wdata, byte); 
        }
    }
    if (waddr >= MMIO_BASE && waddr < MMIO_END) {
        device_write(waddr, wdata, len);
        return;
    }

    #ifdef CONFIG_RV64
    pmem_write(waddr & ~0x3, 8, prev_data);
    #else 
    pmem_write(waddr & ~0x3, 4, prev_data);
    #endif
#ifdef CONFIG_DEBUGMSG
    Log("waddr:0x%lx value:0x%lx len:%d", waddr, wdata, len);
#endif
}
