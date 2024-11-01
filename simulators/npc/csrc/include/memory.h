#ifndef __MEMORY_H
#define __MEMORY_H

#include <npc.h>

#include <stdint.h>

typedef uint32_t      paddr_t;
typedef uint32_t      vaddr_t;
typedef unsigned char uint8_t;

extern uint8_t *guest_to_host(paddr_t paddr);
extern paddr_t  host_to_guest(uint8_t *haddr);

// 用C++实现的仿真用的存储器
extern uint64_t *pmem_addr(vaddr_t addr);
extern word_t    pmem_read(vaddr_t addr, int len);
extern void      pmem_write(vaddr_t addr, int len, word_t data);

#define MEMSIZE   0x20000000
#define MEMMASK   0x1FFFFFFF

#define PADDR_FMT "0x%08x"
#define VADDR_FMT "0x%08x"

#endif
