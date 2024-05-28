// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2017 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0
//======================================================================

#include <npc.h>
#include <verilator.h>

void sdb_mainloop();
void init_npc(int argc, char **argv);

int main(int argc, char **argv, char **env) {
    init_npc(argc, argv);
    while (!contextp->gotFinish() && npc_state.state != NPC_QUIT && npc_state.state != NPC_ABORT)
        sdb_mainloop();

    // Return good completion status
    // Don't use exit() or destructor won't get called
    top->final();
    return npc_state.state == NPC_ABORT;
}
