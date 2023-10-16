/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LOONGARCH_UAPI_ASM_UCONTEXT_H
#define __LOONGARCH_UAPI_ASM_UCONTEXT_H

/**
 * struct extcontext - extended context header structure
 * @magic:	magic value identifying the type of extended context
 * @size:	the size in bytes of the enclosing structure
 *
 * Extended context structures provide context which does not fit within struct
 * sigcontext. They are placed sequentially in memory at the end of struct
 * ucontext and struct sigframe, with each extended context structure beginning
 * with a header defined by this struct. The type of context represented is
 * indicated by the magic field. Userland may check each extended context
 * structure against magic values that it recognises. The size field allows any
 * unrecognised context to be skipped, allowing for future expansion. The end
 * of the extended context data is indicated by the magic value
 * END_EXTCONTEXT_MAGIC.
 */

/**
 * struct ucontext - user context structure
 * @uc_flags:
 * @uc_link:
 * @uc_stack:
 * @uc_mcontext:	holds basic processor state
 * @uc_sigmask:
 */
struct ucontext {
	/* Historic fields matching asm-generic */
	unsigned long		uc_flags;
	struct ucontext		*uc_link;
	stack_t			uc_stack;
	sigset_t		uc_sigmask;
	/* reserved space, sigmask will be expanded in the future. */
	__u8              __unused[1024 / 8 - sizeof(sigset_t)];

	/* sigcontext will be expanded too, for example, vector ISA extension will
	 * almost certainly add ISA state, putting mcontext at the end in order to
	 * allow for infinite extensibility. */
	struct sigcontext	uc_mcontext;
};

#endif /* __LOONGARCH_UAPI_ASM_UCONTEXT_H */
