#include <stdlib.h>

#include "device.h"
#include "npc.h"
#include "mmio.h"

#define MSIP_OFFSET      0
#define MTIMECMPL_OFFSET 0x4000
#define MTIMECMPH_OFFSET 0x4004
#define MTIMEL_OFFSET    0xbff8
#define MTIMEH_OFFSET    0xbffc

static uint8_t  *clint_base = NULL;
static uint32_t *msip_ptr, *mtimecmph_ptr, *mtimecmpl_ptr, *mtimeh_ptr, *mtimel_ptr;

static void clint_io_handler(uint32_t offset, int len, bool is_write) {
    switch (offset) {
        case MSIP_OFFSET:
            if (is_write) *msip_ptr &= 0x1;
            break;
        case MTIMECMPL_OFFSET:
        case MTIMECMPH_OFFSET:
        case MTIMEL_OFFSET:
        case MTIMEH_OFFSET:
        default:
            break;
    }
}

void init_clint() {
    clint_base = new_space(0xC000);
    add_mmio_map("clint", CONFIG_CLINT_MMIO, clint_base, 0xC000, clint_io_handler);
    msip_ptr      = (uint32_t *)(clint_base + MSIP_OFFSET);
    mtimecmpl_ptr = (uint32_t *)(clint_base + MTIMECMPL_OFFSET);
    mtimecmph_ptr = (uint32_t *)(clint_base + MTIMECMPH_OFFSET);
    mtimel_ptr    = (uint32_t *)(clint_base + MTIMEL_OFFSET);
    mtimeh_ptr    = (uint32_t *)(clint_base + MTIMEH_OFFSET);
    *msip_ptr = 0, *mtimecmph_ptr = 0, *mtimecmpl_ptr = 0;
    *mtimeh_ptr = 0, *mtimel_ptr = 0;
}

bool clint_update() {
    // static uint64_t lasttime_us = 0;
    // lasttime_us = get_time() - lasttime_us;
    // *mtime_ptr += lasttime_us;
    if (*mtimel_ptr == UINT32_MAX) {
        *mtimel_ptr = 0;
        (*mtimeh_ptr)++;
    } else
        (*mtimel_ptr)++;
    bool flag =
        ((*mtimeh_ptr > *mtimecmph_ptr)
         || ((*mtimeh_ptr == *mtimecmph_ptr) && (*mtimel_ptr >= *mtimecmpl_ptr)));
    return flag;
}
