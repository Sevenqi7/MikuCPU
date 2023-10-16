#ifndef GCC_TM_H
#define GCC_TM_H
#ifndef LIBC_GLIBC
# define LIBC_GLIBC 1
#endif
#ifndef LIBC_UCLIBC
# define LIBC_UCLIBC 2
#endif
#ifndef LIBC_BIONIC
# define LIBC_BIONIC 3
#endif
#ifndef LIBC_MUSL
# define LIBC_MUSL 4
#endif
#ifndef DEFAULT_LIBC
# define DEFAULT_LIBC LIBC_GLIBC
#endif
#ifndef ANDROID_DEFAULT
# define ANDROID_DEFAULT 0
#endif
#ifndef LA_MULTIARCH_TRIPLET
# define LA_MULTIARCH_TRIPLET loongarch32r-linux-gnusf
#endif
#ifndef TM_MULTILIB_LIST
# define TM_MULTILIB_LIST ABI_BASE_ILP32S,ABI_EXT_BASE
#endif
#ifndef DEFAULT_CPU_ARCH
# define DEFAULT_CPU_ARCH CPU_LOONGARCH32R
#endif
#ifndef DEFAULT_CPU_TUNE
# define DEFAULT_CPU_TUNE CPU_NONE
#endif
#ifndef DEFAULT_ABI_BASE
# define DEFAULT_ABI_BASE ABI_BASE_ILP32S
#endif
#ifndef DEFAULT_ABI_EXT
# define DEFAULT_ABI_EXT ABI_EXT_BASE
#endif
#ifndef DEFAULT_ISA_EXT_FPU
# define DEFAULT_ISA_EXT_FPU ISA_EXT_NONE
#endif
#ifndef LA_DISABLE_MULTIARCH
# define LA_DISABLE_MULTIARCH
#endif
#ifdef IN_GCC
# include "options.h"
# include "insn-constants.h"
# include "config/dbxelf.h"
# include "config/elfos.h"
# include "config/gnu-user.h"
# include "config/linux.h"
# include "config/linux-android.h"
# include "config/glibc-stdint.h"
# include "config/loongarch/loongarch.h"
# include "config/loongarch/gnu-user.h"
# include "config/loongarch/linux.h"
# include "config/initfini-array.h"
#endif
#if defined IN_GCC && !defined GENERATOR_FILE && !defined USED_FOR_TARGET
# include "insn-flags.h"
#endif
#if defined IN_GCC && !defined GENERATOR_FILE
# include "insn-modes.h"
#endif
# include "defaults.h"
#endif /* GCC_TM_H */
