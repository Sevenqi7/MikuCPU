/***************************************************************************************
 * Copyright (c) 2020-2021 Institute of Computing Technology, Chinese Academy of
 *Sciences Copyright (c) 2020-2021 Peng Cheng Laboratory
 *
 * XiangShan is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 *PSL v2. You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 *KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 *NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#include "interface.h"
#include "stdio.h"
#define RETURN_NO_NULL \
    if (!CONFIG_DIFFTEST) return;

INTERFACE_INSTR_COMMIT {
    RETURN_NO_NULL
    auto packet   = &dut.commit;
    packet->valid = valid;
    if (packet->valid) {
        packet->pc    = pc;
        packet->inst  = instr;
        packet->skip  = skip;
        packet->wen   = wen;
        packet->wdest = wdest;
        packet->wdata = wdata;
    }
}

INTERFACE_EXCP_EVENT {
    RETURN_NO_NULL
    auto packet          = &dut.excp;
    packet->excp_valid   = excp_valid;
    packet->eret         = eret;
    packet->interrupt    = intrNo;
    packet->exception    = cause;
    packet->exceptionPC  = exceptionPC;
    packet->exceptionIst = exceptionInst;
}

INTERFACE_GREG_STATE {
    RETURN_NO_NULL
    auto packet     = &dut.regs;
    packet->gpr[0]  = gpr_0;
    packet->gpr[1]  = gpr_1;
    packet->gpr[2]  = gpr_2;
    packet->gpr[3]  = gpr_3;
    packet->gpr[4]  = gpr_4;
    packet->gpr[5]  = gpr_5;
    packet->gpr[6]  = gpr_6;
    packet->gpr[7]  = gpr_7;
    packet->gpr[8]  = gpr_8;
    packet->gpr[9]  = gpr_9;
    packet->gpr[10] = gpr_10;
    packet->gpr[11] = gpr_11;
    packet->gpr[12] = gpr_12;
    packet->gpr[13] = gpr_13;
    packet->gpr[14] = gpr_14;
    packet->gpr[15] = gpr_15;
    packet->gpr[16] = gpr_16;
    packet->gpr[17] = gpr_17;
    packet->gpr[18] = gpr_18;
    packet->gpr[19] = gpr_19;
    packet->gpr[20] = gpr_20;
    packet->gpr[21] = gpr_21;
    packet->gpr[22] = gpr_22;
    packet->gpr[23] = gpr_23;
    packet->gpr[24] = gpr_24;
    packet->gpr[25] = gpr_25;
    packet->gpr[26] = gpr_26;
    packet->gpr[27] = gpr_27;
    packet->gpr[28] = gpr_28;
    packet->gpr[29] = gpr_29;
    packet->gpr[30] = gpr_30;
    packet->gpr[31] = gpr_31;
}

INTERFACE_CSRREG_STATE {
    RETURN_NO_NULL
    auto packet      = &dut.csr;
    packet->mstatus  = mstatus;
    packet->mie      = mie;
    packet->mtvec    = mtvec;
    packet->mscratch = mscratch;
    packet->mepc     = mepc;
    packet->mcause   = mcause;
    packet->mtval    = mtval;
    packet->mip      = mip;
}

INTERFACE_STORE_EVENT {
    RETURN_NO_NULL
    auto packet   = &dut.store;
    packet->valid = valid;
    if (packet->valid) {
        packet->paddr = storePAddr;
        packet->vaddr = storeVAddr;
        packet->data  = storeData;
    }
}

INTERFACE_LOAD_EVENT {
    RETURN_NO_NULL
    auto packet   = &dut.load;
    packet->valid = valid;
    if (packet->valid) {
        packet->paddr = paddr;
        packet->vaddr = vaddr;
    }
}
