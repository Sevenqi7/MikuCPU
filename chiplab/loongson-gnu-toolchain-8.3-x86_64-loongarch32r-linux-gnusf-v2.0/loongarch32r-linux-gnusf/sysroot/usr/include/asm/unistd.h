/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#define __ARCH_WANT_NEW_STAT
#define __ARCH_WANT_SYS_CLONE
#define __ARCH_WANT_SYS_CLONE3
#define __ARCH_WANT_SET_GET_RLIMIT

#if (defined __loongarch32) || (defined __loongarch32r)
#define __ARCH_WANT_STAT64
#define __ARCH_WANT_TIME32_SYSCALLS
#endif

#include <asm-generic/unistd.h>
