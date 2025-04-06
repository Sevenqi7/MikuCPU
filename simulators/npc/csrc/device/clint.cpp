#include "npc.h"
#include <stdlib.h>
#include "verilator.h"
#include "difftest.h"

#define MSIP_OFFSET 0
#define MTIMECMPL_OFFSET 0x4000
#define MTIMECMPH_OFFSET 0x4004
#define MTIMEL_OFFSET 0xbff8
#define MTIMEH_OFFSET 0xbffc

static uint8_t *clint_base = NULL;
static uint32_t *msip_ptr, *mtimecmph_ptr, *mtimecmpl_ptr, *mtimeh_ptr, *mtimel_ptr;

void clint_write(uint32_t offset, word_t data, int len) {
    // Log("offset: %d data: 0x%x, len:%d", offset, data, len);
    // npc_state.state = NPC_STOP;
    switch(offset){
        case MSIP_OFFSET: *msip_ptr &= 0x1; break;
        case MTIMECMPL_OFFSET:    
        case MTIMECMPH_OFFSET:    
        case MTIMEL_OFFSET:
        case MTIMEH_OFFSET:
            switch(len) {
                case 1: clint_base[offset] = data; break;
                case 2: *((uint16_t *)&clint_base[offset]) = data; break;
                case 4: *((uint32_t *)&clint_base[offset]) = data; break;
                case 8: *((uint64_t *)&clint_base[offset]) = data; break;
                default: 
                    Log("Unsupported read length:%d when accessing clint", len);
                    npc_state.state = NPC_STOP;
            }   
        default: break;
    }
}

word_t clint_read(uint32_t offset, int len) {
    // Log("offset: %d, len:%d, retdata: 0x%x", offset, len, clint_base[offset]);
    // npc_state.state = NPC_STOP;
    switch(len) {
        case 1: return clint_base[offset];
        case 2: return *((uint16_t *)&clint_base[offset]);
        case 4: return *((uint32_t *)&clint_base[offset]);
        case 8: return *((uint64_t *)&clint_base[offset]);
        default: 
            Log("Unsupported read length:%d when accessing clint", len);
            npc_state.state = NPC_STOP;
    }
    return -1;
}

svScope scope;
void init_clint() {
    scope = svGetScopeFromName("TOP.simu_top"); 
    clint_base = (uint8_t *)malloc(0XC000);
    msip_ptr = (uint32_t *)(clint_base + MSIP_OFFSET);
    mtimecmpl_ptr = (uint32_t *)(clint_base + MTIMECMPL_OFFSET);
    mtimecmph_ptr = (uint32_t *)(clint_base + MTIMECMPH_OFFSET);
    mtimel_ptr = (uint32_t *)(clint_base + MTIMEL_OFFSET);
    mtimeh_ptr = (uint32_t *)(clint_base + MTIMEH_OFFSET); 
    *msip_ptr = 0,  *mtimecmph_ptr = 0,*mtimecmpl_ptr = 0;
    *mtimeh_ptr = 0, *mtimel_ptr = 0;
}

// extern "C" void dpic_set_mtimer_irq(int int_num);

void clint_update() {
    // *mtime_ptr += lasttime_us;
    if(*mtimel_ptr == UINT32_MAX) 
    {
        *mtimel_ptr = 0;
        (*mtimeh_ptr)++;
    }
    else (*mtimel_ptr)++;
    bool flag =  ((*mtimeh_ptr > *mtimecmph_ptr) || ((*mtimeh_ptr == *mtimecmph_ptr) && (*mtimel_ptr >= *mtimecmpl_ptr)));
    bool mtie = dut.csr.mie & 0x80;
    svSetScope(scope);
    bool mie = dut.csr.mstatus & 0x8;
    #ifdef CONFIG_DIFFTEST
    if(flag & mtie & mie) {
        void (*ref_difftest_raise_intr)(bool intr, word_t code);
        // Log("raise clint interrupt");
        // npc_state.state = NPC_STOP;
        // Log("mtimeh:0x%x mtimel:0x%x mtimecmph:0x%x mtimecmpl: 0x%x", *mtimeh_ptr, *mtimel_ptr, *mtimecmph_ptr, *mtimecmpl_ptr);
    }
    #endif
    top->dpic_set_mtimer_irq(flag);
}
