/*
 * Copyright (c) 1999-2003 MIPS Technologies, Inc.
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
 * r3ktlb.h : MIPS SDE R3000 MMU/TLB definitions
 */


#ifndef _MIPS_R3KTLB_H_
#define _MIPS_R3KTLB_H_

#assert mmu(type1)

#ifdef __cplusplus
extern "C" {
#endif

/* R3000 EntryHi bits */
#define TLBHI_VPNMASK	0xfffff000
#define TLBHI_VPNSHIFT	12
#define TLBHI_PIDMASK	0x00000fc0
#define TLBHI_PIDSHIFT	6

/* R3000 EntryLo bits */
#define TLB_PFNMASK	0xfffff000
#define TLB_PFNSHIFT	12
#define TLB_FLAGS	0x00000f00
#define TLB_N		0x00000800
#define TLB_D		0x00000400
#define TLB_V		0x00000200
#define TLB_G		0x00000100

/* R3000 Index bits */
#define TLBIDX_MASK	0x3f00
#define TLBIDX_SHIFT	8

/* R3000 Random bits */
#define TLBRAND_MASK	0x3f00
#define TLBRAND_SHIFT	8

#define NTLBID		64	/* total number of tlb entries */
#define NTLBWIRED	8	/* number of wired tlb entries */

/* macros to constuct tlbhi and tlblo */
#define mktlbhi(vpn,id)   	(((unsigned)(vpn) << TLBHI_VPNSHIFT) | \
				 ((id) << TLBHI_PIDSHIFT))
#define mktlblo(pn,flags) 	(((unsigned)(pn) << TLB_PFNSHIFT) | (flags))

/* and destruct them */
#define tlbhiVpn(hi) 	((hi) >> TLBHI_VPNSHIFT)
#define tlbhiId(hi) 	(((hi) & TLBHI_PIDMASK) >> TLBHI_PIDSHIFT)
#define tlbloPn(lo)	((lo) >> TLB_PFNSHIFT)
#define tlbloFlags(lo)	((lo) & TLB_FLAGS)

#ifndef ROM_BASE
#define ROM_BASE	0xbfc00000	/* standard ROM base address */
#endif

#ifdef __ASSEMBLER__

/* 
 * R3000 virtual memory regions 
 */
#define	KSEG0_BASE	0x80000000
#define	KSEG1_BASE	0xa0000000
#define	KSEG2_BASE	0xc0000000

#define KUSEG_SIZE	0x80000000
#define KSEG0_SIZE	0x20000000
#define KSEG1_SIZE	0x20000000
#define KSEG2_SIZE	0x40000000
#define RVEC_BASE	ROM_BASE

/* 
 * Translate a kernel virtual address in KSEG0 or KSEG1 to a real
 * physical address and back.
 */
#define KVA_TO_PA(v) 	((v) & 0x1fffffff)
#define PA_TO_KVA0(pa)	((pa) | 0x80000000)
#define PA_TO_KVA1(pa)	((pa) | 0xa0000000)

/* translate between KSEG0 and KSEG1 virtual addresses */
#define KVA0_TO_KVA1(v)	((v) | 0x20000000)
#define KVA1_TO_KVA0(v)	((v) & ~0x20000000)

#else /* __ASSEMBLER__ */

/*
 * Standard address types
 */
#ifndef _PADDR_T_DEFINED_
typedef unsigned long		paddr_t;	/* a physical address */
#define _PADDR_T_DEFINED_
#endif
#ifndef _VADDR_T_DEFINED_
typedef unsigned long		vaddr_t;	/* a virtual address */
#define _VADDR_T_DEFINED_
#endif

typedef unsigned long	tlblo_t;	/* the tlblo field */
typedef unsigned long	tlbhi_t;	/* the tlbhi field */

/* 
 * R3000 virtual memory regions 
 */
#define KUSEG_BASE 	((void  *)0x00000000)
#define KSEG0_BASE	((void  *)0x80000000)
#define KSEG1_BASE	((void  *)0xa0000000)
#define KSEG2_BASE	((void  *)0xc0000000)

#define KUSEG_SIZE	0x80000000u
#define KSEG0_SIZE	0x20000000u
#define KSEG1_SIZE	0x20000000u
#define KSEG2_SIZE	0x40000000u

#define RVEC_BASE	((void *)ROM_BASE)	/* reset vector base */

/* 
 * Translate a kernel virtual address in KSEG0 or KSEG1 to a real
 * physical address and back.
 */
#define KVA_TO_PA(v) 	((paddr_t)(v) & 0x1fffffff)
#define PA_TO_KVA0(pa)	((void *) ((pa) | 0x80000000))
#define PA_TO_KVA1(pa)	((void *) ((pa) | 0xa0000000))

/* translate between KSEG0 and KSEG1 virtual addresses */
#define KVA0_TO_KVA1(v)	((void *) ((unsigned)(v) | 0x20000000))
#define KVA1_TO_KVA0(v)	((void *) ((unsigned)(v) & ~0x20000000))

/* Test for KSEGS */
#define IS_KVA(v)	((int)(v) < 0)
#define IS_KVA0(v)	(((unsigned)(v) >> 29) == 0x4)
#define IS_KVA1(v)	(((unsigned)(v) >> 29) == 0x5)
#define IS_KVA01(v)	(((unsigned)(v) >> 30) == 0x2)
#define IS_KVA2(v)	(((unsigned)(v) >> 30) == 0x3)
#define IS_UVA(v)	((int)(v) >= 0)

/* convert register type to address and back */
#define VA_TO_REG(v)	((long)(v))
#define REG_TO_VA(v)	((void *)(v))

/*
 * R3000 fixed virtual memory page size.
 */
#define VMPGSIZE 	4096			/* min page size = 4K */
#define VMPGSIZEMAX	4096			/* max page size = 4K */
#define VMPGSHIFT 	12			/* log2(vmpgsize) */
#define VMPGMASK 	(VMPGSIZE-1)

/* virtual address to virtual page number and back */
#define vaToVpn(va)	((unsigned)(va) >> VMPGSHIFT)
#define vpnToVa(vpn)	(void *)((vpn) << VMPGSHIFT)

/* physical address to phyiscal page number and back */
#define paToPn(pa)	((pa) >> VMPGSHIFT)
#define pnToPa(pn)	((paddr_t)((pn) << VMPGSHIFT))

/* 
 * R3000 TLB acccess functions
 */
void	mips_tlbri (tlbhi_t *, tlblo_t *, unsigned);
void	mips_tlbwi (tlbhi_t, tlblo_t, unsigned);
void	mips_tlbwr (tlbhi_t, tlblo_t);
int	mips_tlbrwr (tlbhi_t, tlblo_t);
int	mips_tlbprobe (tlbhi_t, tlblo_t *);
void	mips_tlbinval (tlbhi_t);
void	mips_tlbinvalall (void);

/* R3000 CP0 Context register */
#define mips_getcontext()	_mips_mfc0(C0_CONTEXT)
#define mips_setcontext(v)	_mips_mtc0(C0_CONTEXT,v)
#define mips_xchcontext(v)	_mips_mxc0(C0_CONTEXT,v)

/* R3000 CP0 EntryHi register */
#define mips_getentryhi()	_mips_mfc0(C0_ENTRYHI)
#define mips_setentryhi(v)	_mips_mtc0(C0_ENTRYHI,v)
#define mips_xchentryhi(v)	_mips_mxc0(C0_ENTRYHI,v)

/* R3000 CP0 EntryLo register */
#define mips_getentrylo()	_mips_mfc0(C0_ENTRYLO)
#define mips_setentrylo(v)	_mips_mtc0(C0_ENTRYLO,v)
#define mips_xchentrylo(v)	_mips_mxc0(C0_ENTRYLO,v)

/* Return number of wired entries (hard wired) */
#define mips_getwired()		(NTLBWIRED)

#endif /* __ASSEMBLER__ */

#ifdef __cplusplus
}
#endif
#endif /* _MIPS_R3KTLB_H_*/
