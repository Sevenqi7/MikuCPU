#ifndef __DEVICE_H
#define __DEVICE_H

#include <stdint.h>

#define MMIO_BASE     0xa0000000
#define MMIO_END     (MMIO_BASE + 0x20000000)
#define SERIAL_PORT  (MMIO_BASE + 0x000003f8)
#define RTC_ADDR     (MMIO_BASE + 0x00000048)
#define VGACTL_ADDR  (MMIO_BASE + 0x00000100)
#define SYNC_ADDR    (VGACTL_ADDR + 0x4)
#define FB_ADDR      (0xa0000000 + 0x01000000)


// #define io_read(reg) \
//   ({ reg##_T __io_param; \
//     ioe_read(reg, &__io_param); \
//     __io_param; })

// #define io_write(reg, ...) \
//   ({ reg##_T __io_param = (reg##_T) { __VA_ARGS__ }; \
//     ioe_write(reg, &__io_param); })

#endif
