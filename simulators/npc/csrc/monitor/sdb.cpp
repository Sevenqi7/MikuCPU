#include <verilator.h>
#include <expr.h>
#include <npc.h>
#include <memory.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NR_CMD ARRLEN(cmd_table)

void init_regex();
void init_wp_pool();

static char *rl_gets() {
    static char *line_read = NULL;

    if (line_read) {
        free(line_read);
        line_read = NULL;
    }

    line_read = readline("(npc) ");

    if (line_read && *line_read) {
        add_history(line_read);
    } else if (*line_read == '\0') {
        HIST_ENTRY **pp = history_list();
        if (pp != NULL) {
            while (true) {
                if (*(pp + 1) == NULL) {
                    line_read = strdup((*pp)->line);
                    break;
                }
                ++pp;
            }
        }
    }

    return line_read;
}

void execute(uint64_t n);

static int cmd_help(char *args);

static int cmd_c(char *args) {
    execute(-1);
    return 0;
}

static int cmd_q(char *args) {
    if (npc_state.state != NPC_ABORT) npc_state.state = NPC_QUIT;
    return -1;
}

static int cmd_w(char *args) {
    int wp_num;
    if (!args) {
        printf("Usage: w <EXPRESSION>\n");
        return 0;
    }
    wp_num = add_watchpoint(args);
    if (wp_num < 0)
        printf("Invalid Expression.\n");
    else
        printf("Watchpoint %d: %s\n", wp_num, args);
    return 0;
}

static int cmd_d(char *args) {
    int wp_num;
    if (!args) {
        printf("Usage: d <WATCHPOINT_NUM>\n");
    } else {
        wp_num = atoi(args);
        if (del_watchpoint(wp_num))
            printf("Watchpoint %d deleted.\n", wp_num);
        else
            printf("Watchpoint %d doesn't exist.\n", wp_num);
    }
    return 0;
}

static int cmd_x(char *args) {
    if (!args) {
        printf("usage: x <READ_NUM> <ADDR>");
        return 0;
    }
    char *str_end = args + strlen(args);
    strtok(args, " ");
    char   *str = args + strlen(args) + 1;
    int     times;
    vaddr_t addr;
    bool    success = false;
    if (str > str_end) {
        times = 1;
        addr  = expr(args, &success);
    } else {
        times = expr(args, &success);
        addr  = expr(str, &success);
    }
    if (!success) {
        printf("Wrong Arguments!\n");
        return 0;
    }
    // Log("Bytes:%lu addr:%d", addr, bytes);
    for (int i = 0; i < times; i++, addr += 4) {
        printf("0x%08lx: ", addr);
        for (int j = 0; j < 4; j++) printf("%02lx  ", pmem_read(addr + j, 1));
        printf("\n");
    }
    return 0;
}

#ifdef CONFIG_FTRACE
void display_ftrace();

static int cmd_ftrace(char *args) {
    display_ftrace();
    return 0;
}
#endif

static int cmd_si(char *args) {
    int steps = args ? atoi((const char *)args) : 1;
    execute(steps);
    return 0;
}

static int cmd_csi(char *args) {
    int steps = args ? atoi((const char *)args) : 1;
    for (int i = 0; i < steps; i++) clock_step();
    return 0;
}

static int cmd_info(char *args) {
    if (!args) {
        printf("usage: <REG>: info r /<WATCHPOINT> info w\n");
        return 0;
    }
    if (!strcmp("r", args))
        reg_display();
    else if (!strcmp("w", args)) {
        display_watchpoints();
        return 0;
    }
    return 0;
}

static int cmd_ptrace(char *args) {
    Log("PTRACE INFO:");
    Log("PTRACE INFO END.");
    return 0;
}

static struct {
    const char *name;
    const char *description;
    int (*handler)(char *);
} cmd_table[] = {
    {"help",   "Display information about all supported commands",     cmd_help  },
    {"c",      "Continue the execution of the program",                cmd_c     },
    {"q",      "Exit NPC",                                             cmd_q     },
    {"si",     "Excute next N instructions, 1 if N is not given",      cmd_si    },
    {"csi",
     "skip N clock cycles. 1 if N is not given. debuginfo will be printed if "
     "macro DEBUG_MSG is defined",                                     cmd_csi   },
    {"x",      "Print the content of memory with a given address.",    cmd_x     },
    {"w",      "Set watchpoint.",                                      cmd_w     },
    {"d",      "Delete watchpoint.",                                   cmd_d     },
#ifdef CONFIG_FTRACE
    {"ftrace", "Display function call trace.",                         cmd_ftrace},
#endif
    {"ptrace", "Display pipeline infomation.",                         cmd_ptrace},
    {"info",   "Print the content of register(-r) or watchpoing(-w).", cmd_info  }

    /* TODO: Add more commands */
};

static int cmd_help(char *args) {
    /* extract the first argument */
    char *arg = strtok(NULL, " ");
    int   i;

    if (arg == NULL) {
        /* no argument given */
        for (i = 0; i < NR_CMD; i++) { printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description); }
    } else {
        for (i = 0; i < NR_CMD; i++) {
            if (strcmp(arg, cmd_table[i].name) == 0) {
                printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
                return 0;
            }
        }
        printf("Unknown command '%s'\n", arg);
    }
    return 0;
}

void sdb_mainloop() {
    for (char *str; (str = rl_gets()) != NULL;) {
        char *str_end = str + strlen(str);

        /* extract the first token as the command */
        char *cmd = strtok(str, " ");
        if (cmd == NULL) { continue; }

        /* treat the remaining string as the arguments,
         * which may need further parsing
         */
        char *args = cmd + strlen(cmd) + 1;
        if (args >= str_end) { args = NULL; }

        int i;
        for (i = 0; i < NR_CMD; i++) {
            if (strcmp(cmd, cmd_table[i].name) == 0) {
                if (cmd_table[i].handler(args) < 0) { return; }
                break;
            }
        }

        if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
    }
}

void init_sdb() {
    init_regex();
    init_wp_pool();
}
