/*
 * Copyright (c) 2000-2003 MIPS Technologies, Inc.
 * Copyright (C) 2009 CodeSourcery, LLC.
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *      copyright
 *        notice, this list of conditions and the following disclaimer
 *        in the documentation and/or other materials provided with
 *        the distribution.
 *      * Neither the name of MIPS Technologies Inc. nor the names of its
 *        contributors may be used to endorse or promote products derived
 *        from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * watchpoint.h: MIPS SDE h/w watchpoint and debug support
 */

#ifndef _MIPS_WATCHPOINT_H_
#define _MIPS_WATCHPOINT_H_
#ifdef __cplusplus
extern "C" {
#endif

#define WATCHPOINT_MAX	8	/* max # of watchpoints for all cpus */

struct mips_watchpoint {
    int			num;
    int			capabilities;
    void		*private;
    unsigned short	type;
    short		asid;
    vaddr_t		va;
    paddr_t		pa;
    size_t		len;
    vaddr_t		mask;
    vaddr_t		maxmask;
};

/* Per-cpu watchpoint support functions */
struct mips_watchpoint_funcs {
    int		(*wp_init) (unsigned int);
    void	(*wp_setup) (struct mips_watchpoint *);
    int		(*wp_hit) (const struct xcptcontext *, vaddr_t *, size_t *);
    int		(*wp_set) (struct mips_watchpoint *);
    int		(*wp_clear) (struct mips_watchpoint *);
    void	(*wp_remove) (void);
    void	(*wp_insert) (void);
    void	(*wp_reset) (void);
};


/* watchpoint and other debug capabilities (returned) */
#define MIPS_WATCHPOINT_INEXACT	0x8000	/* inexact (unmatched) watchpoint */
#define MIPS_WATCHPOINT_SSTEP	0x1000	/* single-step supported */
#define MIPS_WATCHPOINT_VALUE	0x0400	/* data value match supported */
#define MIPS_WATCHPOINT_ASID	0x0200	/* ASID match supported */
#define MIPS_WATCHPOINT_VADDR	0x0100	/* virtual address (not physical) */
#define MIPS_WATCHPOINT_RANGE	0x0080	/* supports an address range */
#define MIPS_WATCHPOINT_MASK	0x0040	/* supports an address mask */
#define MIPS_WATCHPOINT_DWORD	0x0020	/* dword alignment (8 bytes) */
#define MIPS_WATCHPOINT_WORD	0x0010	/* word alignment (4 bytes) */

/* watchpoint capabilities and type (when setting) */
#define MIPS_WATCHPOINT_X	0x0004	/* instruction fetch wp */
#define MIPS_WATCHPOINT_R	0x0002	/* data read wp */
#define MIPS_WATCHPOINT_W	0x0001	/* data write wp */

/* watchpoint support functions */
struct xcptcontext;
int	_mips_watchpoint_init (void);
int	_mips_watchpoint_capabilities (int);
vaddr_t	_mips_watchpoint_mask (int);
int	_mips_watchpoint_hit (const struct xcptcontext *, vaddr_t *, size_t *);
int	_mips_watchpoint_set (int, int, vaddr_t, paddr_t, size_t);
int	_mips_watchpoint_clear (int, int, vaddr_t, size_t);
void	_mips_watchpoint_remove (void);
void	_mips_watchpoint_insert (void);
void	_mips_watchpoint_reset (void);

/* internal utility functions for watchpoint code */
vaddr_t		_mips_watchpoint_calc_mask (vaddr_t, size_t);
int		_mips_watchpoint_address (const struct xcptcontext *, int,
					  vaddr_t *, size_t *);
int		_mips_watchpoint_set_callback (int, vaddr_t, size_t);

/* return codes from set/clear */
#define MIPS_WP_OK		0
#define MIPS_WP_NONE		1
#define MIPS_WP_NOTSUP		2
#define MIPS_WP_INUSE		3
#define MIPS_WP_NOMATCH		4
#define MIPS_WP_OVERLAP		5
#define MIPS_WP_BADADDR		6

/* in exception handler */
extern reg_t _mips_watchlo, _mips_watchhi;

#ifdef __cplusplus
}
#endif
#endif /*  _MIPS_WATCHPOINT_H_ */
