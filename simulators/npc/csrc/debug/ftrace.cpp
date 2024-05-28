#include <verilator.h>
#include <npc.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <elf.h>

#define MAX_FTRACE_INFO_SIZE  128
#define MAX_FTRACE_STACK_SIZE 512

void get_symbol_list(const char *elf_path);

void init_ftrace(const char *path) {
    get_symbol_list(path);
}

#ifdef CONFIG_FTRACE
static int f_info_num = 0;

static struct function_info {
    vaddr_t f_addr;
    char    f_name[64];
} f_info[MAX_FTRACE_INFO_SIZE];

static struct function_call_stack {
    struct function_info function[MAX_FTRACE_STACK_SIZE];
    bool                 is_ret[MAX_FTRACE_STACK_SIZE];
    vaddr_t              call_pc[MAX_FTRACE_STACK_SIZE];
    vaddr_t              ret_addr[MAX_FTRACE_STACK_SIZE];
    int                  f_trace_end;
} f_trace_buf = {0};

void ftrace_check_jal(vaddr_t jump_addr, vaddr_t ret_addr, int rs1, int rd) {
    assert(f_trace_buf.f_trace_end <= MAX_FTRACE_STACK_SIZE);
    // Log("jump_addr:%lx ret_addr:%lx rd:%d, rs1:%d", jump_addr, ret_addr, rd, rs1);
    if (rd == 0 && rs1 == 1) {
        for (int i = f_trace_buf.f_trace_end - 1; i >= 0; i--) {
            if (f_trace_buf.ret_addr[i] == jump_addr) {
                f_trace_buf.function[f_trace_buf.f_trace_end] = f_trace_buf.function[i];
                f_trace_buf.is_ret[f_trace_buf.f_trace_end]   = true;
                f_trace_buf.call_pc[f_trace_buf.f_trace_end]  = ret_addr - 4;

                // Log("%s ret", f_trace_buf.function[f_trace_buf.f_trace_end].f_name);
                f_trace_buf.f_trace_end++;
                return;
            }
        }
    }
    for (int i = 0; i < f_info_num; i++) {
        if (f_info[i].f_addr == jump_addr) {
            f_trace_buf.function[f_trace_buf.f_trace_end] = f_info[i];
            f_trace_buf.ret_addr[f_trace_buf.f_trace_end] = ret_addr;
            f_trace_buf.is_ret[f_trace_buf.f_trace_end]   = false;
            f_trace_buf.call_pc[f_trace_buf.f_trace_end]  = ret_addr - 4;

            // Log("f_trace_end:%d", f_trace_buf.f_trace_end);
            // Log("jump to 0x%lx(%s)", f_trace_buf.function[f_trace_buf.f_trace_end].f_addr,
            // f_trace_buf.function[f_trace_buf.f_trace_end].f_name);

            f_trace_buf.f_trace_end++;
            return;
        }
    }
}

void display_ftrace() {
    int i = 0, j = 0;
    for (; i < f_trace_buf.f_trace_end; i++) {
        printf("0x%lx:", f_trace_buf.call_pc[i]);
        if (f_trace_buf.is_ret[i] == false) {
            j++;
            for (int k = 0; k < 2 * j; k++) printf(" ");
            printf(
                "call[%s@0x%lx]\n", f_trace_buf.function[i].f_name, f_trace_buf.function[i].f_addr);
        } else {
            j--;
            for (int k = 0; k < 2 * j; k++) printf(" ");
            printf("ret  [%s]\n", f_trace_buf.function[i].f_name);
        }
    }
}
#endif

void get_symbol_list(const char *elf_path) {
#ifdef CONFIG_FTRACE
    int fd = open(elf_path, O_RDONLY, 0);
    if (fd == -1) {
        printf("Failed to open elf file!\n");
        return;
    }
    Elf64_Ehdr ehdr;
    if (read(fd, &ehdr, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
        printf("Failed to read Elf Header\n");
        return;
    }
    // read .shstrtab
    lseek(fd, ehdr.e_shoff + ehdr.e_shentsize * ehdr.e_shstrndx, SEEK_SET);
    Elf64_Shdr shdr;
    if (read(fd, &shdr, sizeof(shdr)) != sizeof(Elf64_Shdr)) {
        printf("Failed to read section header of string table!\n");
        return;
    }
    char *shstrtab = (char *)malloc(shdr.sh_size);
    lseek(fd, shdr.sh_offset, SEEK_SET);
    if (read(fd, shstrtab, shdr.sh_size) != shdr.sh_size) {
        printf("Failed to read section .shstrtab!\n");
        return;
    }

    // read shstrtab
    for (int i = 0; i < ehdr.e_shnum; i++) {
        lseek(fd, ehdr.e_shoff + ehdr.e_shentsize * i, SEEK_SET);
        if (read(fd, &shdr, sizeof(Elf64_Shdr)) != sizeof(Elf64_Shdr)) return;
        if (shdr.sh_type == SHT_STRTAB && !strcmp(".strtab", shstrtab + shdr.sh_name)) break;
    }

    char *strtab = (char *)malloc(shdr.sh_size);
    lseek(fd, shdr.sh_offset, SEEK_SET);
    if (read(fd, strtab, shdr.sh_size) != shdr.sh_size) {
        printf("Failed to read string table!\n");
        return;
    }
    lseek(fd, ehdr.e_shoff, SEEK_SET);
    for (int i = 0; i < ehdr.e_shnum; i++) {
        if (read(fd, &shdr, sizeof(Elf64_Shdr)) != sizeof(Elf64_Shdr)) {
            printf("Failed to load section %d!\n", i);
            return;
        }
        if (shdr.sh_type == SHT_SYMTAB) {
            Elf64_Sym sym;
            lseek(fd, shdr.sh_offset, SEEK_SET);
            int sym_num = shdr.sh_size / sizeof(Elf64_Sym);
            //   printf("syn_num:%d\n", sym_num);
            for (int j = 0; j < sym_num; j++) {
                if (read(fd, &sym, sizeof(Elf64_Sym)) != sizeof(Elf64_Sym)) {
                    printf("Failed to read symbol info!\n");
                    return;
                }
                if ((sym.st_info & 0xf) == STT_FUNC) {
                    // assert(0);
                    char *func_name = strtab + sym.st_name;
                    memcpy(f_info[f_info_num].f_name, func_name, strlen(func_name) + 1);
                    //   Log("sym %d funcname:%s", j, func_name);
                    f_info[f_info_num].f_addr = sym.st_value;
                    f_info_num++;
                }
            }
        }
    }
    printf("\033[0m\033[1;36mThe ELF path is %s\033[0m\n", elf_path);

    free(strtab);
    free(shstrtab);
#endif
}
