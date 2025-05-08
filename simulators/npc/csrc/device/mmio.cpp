#include <stdlib.h>

#include "npc.h"
#include "mmio.h"

#define IO_SPACE_SIZE 0x10000000

static uint8_t *io_space_base   = NULL;
static uint8_t *free_space_base = NULL;

#define NR_MAP 16
static IOMap maps[NR_MAP];
static int   nr_map = 0;

static IOMap *fetch_mmio_map(paddr_t addr) {
    int mapid = find_mapid_by_addr(maps, nr_map, addr);
    return (mapid == -1 ? NULL : &maps[mapid]);
}

void init_mmio() {
    io_space_base   = (uint8_t *)malloc(IO_SPACE_SIZE);
    free_space_base = io_space_base;
    assert(io_space_base);
}

static void report_mmio_overlap(
    const char *name1, paddr_t l1, paddr_t r1, const char *name2, paddr_t l2, paddr_t r2) {
    panic(
        "MMIO region %s@[" PADDR_FMT ", " PADDR_FMT "] is overlapped "
        "with %s@[" PADDR_FMT ", " PADDR_FMT "]",
        name1,
        l1,
        r1,
        name2,
        l2,
        r2);
}

void add_mmio_map(const char *name, paddr_t addr, void *space, uint32_t len, io_callback_t callback) {
    assert(nr_map < NR_MAP);
    paddr_t left = addr, right = addr + len - 1;
    if (in_pmem(left) || in_pmem(right)) {
        report_mmio_overlap(name, left, right, "pmem", PMEM_BASE, PMEM_BASE + MEMSIZE);
    }
    for (int i = 0; i < nr_map; i++) {
        if (left <= maps[i].high && right >= maps[i].low) {
            report_mmio_overlap(name, left, right, maps[i].name, maps[i].low, maps[i].high);
        }
    }

    maps[nr_map] =
        (IOMap){.name = name, .low = addr, .high = addr + len - 1, .space = space, .callback = callback};
    Log("Add mmio map '%s' at [" PADDR_FMT ", " PADDR_FMT "]",
        maps[nr_map].name,
        maps[nr_map].low,
        maps[nr_map].high);

    nr_map++;
}

uint8_t *new_space(int size) {
    uint8_t *p       = free_space_base;
    free_space_base += size;
    assert((free_space_base - io_space_base) < IO_SPACE_SIZE);
    return p;
}

static void check_bound(IOMap *map, paddr_t addr) {
    if (map == NULL) {
        printf("address (" PADDR_FMT ") is out of bound at pc = " FMT_WORD "\n", addr, npc_state.pc);
        assert(map != NULL);
    } else if (addr >= map->high || addr < map->low) {
        printf(
            "address (" PADDR_FMT ") is out of bound {%s} [" PADDR_FMT ", " PADDR_FMT "] at pc = " FMT_WORD "\n",
            addr,
            map->name,
            map->low,
            map->high,
            npc_state.pc);
        assert(0);
    }
}

static void invoke_callback(io_callback_t c, paddr_t offset, int len, bool is_write) {
    if (c != NULL) { c(offset, len, is_write); }
}

word_t map_read(paddr_t addr, int len, IOMap *map) {
    assert(len >= 1 && len <= 8);
    check_bound(map, addr);
    paddr_t offset = addr - map->low;
    // Log("mapname:%s offset:0x%x addr:0x%x, low:%x, high:%x",
    //     map->name,
    //     addr - map->low,
    //     addr,
    //     map->low,
    //     map->high);
    invoke_callback(map->callback, offset, len, false); // prepare data to read
    word_t ret = host_read((uint8_t *)map->space + offset, len);
    return ret;
}

void map_write(paddr_t addr, int len, word_t data, IOMap *map) {
    assert(len >= 1 && len <= 8);
    check_bound(map, addr);
    paddr_t offset = addr - map->low;
    host_write((uint8_t *)map->space + offset, len, data);
    invoke_callback(map->callback, offset, len, true);
}

word_t mmio_read(paddr_t addr, int len) {
    word_t rdata = map_read(addr, len, fetch_mmio_map(addr));
    // Log("mmio_raddr " PADDR_FMT" data: 0x%x len:%d" , addr, rdata, len);
    return rdata;
    // return map_read(addr, len, fetch_mmio_map(addr));
}

void mmio_write(paddr_t addr, int len, word_t data) {
    // Log("mmio_waddr " PADDR_FMT " data: 0x%x len:%d" , addr, data, len);
    map_write(addr, len, data, fetch_mmio_map(addr));
}
