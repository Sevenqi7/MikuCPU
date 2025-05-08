#ifndef _MMIO_H
#define _MMIO_H

#include "memory.h"

typedef void(*io_callback_t)(uint32_t, int, bool);

struct IOMap {
    const char *name;
    paddr_t low;
    paddr_t high;
    void *space;
    io_callback_t callback;
};

static inline bool map_inside(IOMap *map, paddr_t addr) {
  return (addr >= map->low && addr <= map->high);
}

static inline int find_mapid_by_addr(IOMap *maps, int size, paddr_t addr) {
  int i;
  for (i = 0; i < size; i ++) {
    if (map_inside(maps + i, addr)) {
        return i;
    }
  }
  return -1;
}

void init_mmio();
uint8_t *new_space(int size);

void add_mmio_map(const char *name, paddr_t addr,
        void *space, uint32_t len, io_callback_t callback);

word_t mmio_read(paddr_t addr, int len) ;
void mmio_write(paddr_t addr, int len, word_t data);

#endif
