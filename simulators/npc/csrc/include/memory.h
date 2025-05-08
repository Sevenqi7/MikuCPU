#ifndef __MEMORY_H
#define __MEMORY_H

#include <npc.h>

#include <stdint.h>

typedef uint32_t      paddr_t;
typedef uint32_t      vaddr_t;
typedef unsigned char uint8_t;

extern uint8_t *guest_to_host(paddr_t paddr);
extern paddr_t  host_to_guest(uint8_t *haddr);

static inline word_t host_read(void *addr, int len) {
  switch (len) {
    case 1: return *(uint8_t  *)addr;
    case 2: return *(uint16_t *)addr;
    case 4: return *(uint32_t *)addr;
    #ifdef CONFIG_RV64
    case 8: return *(uint64_t *)addr;
    #endif
    default: 
        npc_state.state = NPC_ABORT;
        return -1;
  }
}

static inline void host_write(void *addr, int len, word_t data) {
  switch (len) {
    case 1: *(uint8_t  *)addr = data; return;
    case 2: *(uint16_t *)addr = data; return;
    case 4: *(uint32_t *)addr = data; return;
    #ifdef CONFIG_RV64
    case 8: *(uint64_t *)addr = data; return;
    #endif
    default: npc_state.state = NPC_ABORT;
  }
}

#define MEMSIZE   0x20000000
#define MEMMASK   0x1FFFFFFF
#define PMEM_BASE 0x80000000

static inline bool in_pmem(paddr_t addr){
    return ((addr >= PMEM_BASE) && (addr <= (PMEM_BASE + MEMSIZE)));
}

extern uint64_t *pmem_addr(vaddr_t addr);
extern word_t    pmem_read(vaddr_t addr, int len);
extern void      pmem_write(vaddr_t addr, int len, word_t data);

#define PADDR_FMT "0x%08x"
#define VADDR_FMT "0x%08x"

#endif
