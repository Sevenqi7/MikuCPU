#include <npc.h>
#include <verilator.h>

void sdb_mainloop();
void init_npc(int argc, char **argv);

int main(int argc, char **argv, char **env) {
    init_npc(argc, argv);
    while (!contextp->gotFinish() && npc_state.state != NPC_QUIT && npc_state.state != NPC_ABORT)
        sdb_mainloop();
    top->final();
    return npc_state.state == NPC_ABORT;
}
