#ifndef __DEVICE_H
#define __DEVICE_H

#include <stdint.h>

#include "npc.h"
#include "mmio.h"

#define MMIO_BASE     0x10000000
#define MMIO_END     (MMIO_BASE + 0x20000000)
#define RTC_ADDR     (MMIO_BASE + 0x00000048)
#define VGACTL_ADDR  (MMIO_BASE + 0x00000100)
#define SYNC_ADDR    (VGACTL_ADDR + 0x4)
#define FB_ADDR      (0xa0000000 + 0x01000000)

extern void init_vga();
extern void init_serial();

extern void serial_write(uint32_t offset, word_t data, int len);
extern word_t serial_read(uint32_t offset, int len);

extern void init_clint();
extern void clint_write(uint32_t offset, word_t data, int len);
extern word_t clint_read(uint32_t offset, int len);

#endif
