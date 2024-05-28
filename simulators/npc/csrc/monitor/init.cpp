#include "Vsimu_top.h"
#include "verilated.h"
#include "verilator.h"
#include "npc.h"
#include "memory.h"
#include "cmdline.h"

#include <stdio.h>
#include <string.h>
#include <signal.h>

long img_size;

long init_img(const char *argv);
void init_sdb();
void init_disasm(const char *triple);
void init_ftrace(const char *path);
void init_vga();
#ifdef CONFIG_DIFFTEST
void init_difftest(const char *ref_so_file, long img_size, int port);
#endif

void sigint_handler(int sig){
    if(sig == SIGINT){
        npc_state.state = NPC_STOP;
    }
}

void init_npc(int argc, char **argv) {
    Log("npc initialize...");
    signal(SIGINT, sigint_handler);
    
    tfp = new VerilatedVcdC;
    Verilated::mkdir("logs");
    contextp = new VerilatedContext;
    contextp->debug(0);
    contextp->randReset(3);
    contextp->traceEverOn(true);
    contextp->commandArgs(argc, argv);
    top = new Vsimu_top;
    top->trace(tfp, 1);
    tfp->open("./logs/simu_trace.vcd");
    top->aclk = 0;
    reset(10);

    cmdline::parser cmd_parser;
    cmd_parser.add<std::string>("binary", 'b', "Binary file path", true, "");
    cmd_parser.add<std::string>("elf", '\0', "ELF file path", false, "");
    cmd_parser.add<std::string>("diff", '\0', "Difftest reference", false, "");
    cmd_parser.parse_check(argc, argv);

    const char *img_path    = strdup(cmd_parser.get<std::string>("binary").c_str());
    const char *elf_path    = strdup(cmd_parser.get<std::string>("elf").c_str());
    const char *ref_so_path = strdup(cmd_parser.get<std::string>("diff").c_str());

    img_size = init_img(img_path);
    init_disasm("riscv32");
    if (cmd_parser.exist("elf")) { init_ftrace(elf_path); }
#ifdef CONFIG_DIFFTEST
    if (cmd_parser.exist("diff")) { init_difftest(ref_so_path, img_size, 1234); }
#endif
    init_sdb();
    init_vga();
}

long init_img(const char *img_path) {
    // read img
    printf("Loading image file from:%s\n", img_path);
    if (img_path == NULL) {
        printf("\033[0m\033[1;31m%s\033[0m", "Error: No image is given!\n");
        exit(0);
    }
    FILE *fp = fopen(img_path, "rb");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    printf("\033[0m\033[1;36mThe image is %s, size=%ld\033[0m\n", img_path, size);

    fseek(fp, 0, SEEK_SET);
    int ret = fread(pmem_addr(0), size, 1, fp);
    if (ret == -1) {
        printf("\033[0m\033[1;31m%s\033[0m", "Error: Failed to read image file!\n");
        exit(-1);
    }
    fclose(fp);
    return size;
}
