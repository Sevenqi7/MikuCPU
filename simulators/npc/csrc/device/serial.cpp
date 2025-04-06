#include "npc.h"
#include "string.h"
#include "device.h"

/* http://en.wikibooks.org/wiki/Serial_Programming/8250_UART_Programming */
// NOTE: this is compatible to 16550

#define CH_OFFSET  0
#define IER_OFFSET 1
#define IIR_OFFSET 2
#define LCR_OFFSET 3
#define MCR_OFFSET 4
#define LSR_OFFSET 5
#define MSR_OFFSET 6

static uint8_t serial_base[12] = {0, 0, 0, 0, 0, 0x60, 0, 0, 0, 0, 0, 0};

static void serial_putc(char ch) {
  printf("\033[0m\033[1;31m%c\033[0m", ch);
  fflush(stdout);
  // MUXDEF(CONFIG_TARGET_AM, putch(ch), putc(ch, stderr));
}

void serial_write(uint32_t offset, word_t data, int len) {
  
//   assert(len == 1);
    // Log("offset: %d data: 0x%x, len:%d", offset, data, len);
    if(len != 1){
        Log("unsupported write len");
        npc_state.state = NPC_STOP;
        return;
    }
    switch (offset) {
        /* We bind the serial port with the host stderr in NEMU. */
        case CH_OFFSET:
        serial_putc((char) data);
        serial_base[0] = 0;
        break;
        #ifdef CONFIG_NOMMU_LINUX
        case IER_OFFSET:
        case IIR_OFFSET:
        case MCR_OFFSET:  
        case MSR_OFFSET:  
        case LCR_OFFSET: memset(serial_base + 1, 0, 4); return;
        case LSR_OFFSET: serial_base[5] = 0x60; return ;
        #endif
        default: 
            Log("do not support offset = %d", offset);
            npc_state.state = NPC_STOP;
    }
}

word_t serial_read(uint32_t offset, int len) {
    // Log("offset: %d, len:%d, retdata: 0x%x", offset, len, serial_base[offset]);
    // npc_state.state = NPC_STOP;
    assert(len == 1);
    return serial_base[offset];
}
