/*
 * Copyright (c) 1999-2003 MIPS Technologies, Inc.
 * Copyright (C) 2009 CodeSourcery, LLC
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
 * lsi/cw4002.h: definitions for LSI Logic CW4002
 */


#ifndef _MIPS_CW4002_H_
#define _MIPS_CW4002_H_

#ifdef __cplusplus
extern "C" {
#endif

/* cw400x + dbx module */
#include "loongarch32/cw400x.h"

#ifdef __ASSEMBLER__
/* 
 * DBX debug unit registers
 * N.B. Use mfd/mtd instructions to access these registers
 */
#define C0_DCS		$7
#define C0_BPC		$18
#define C0_BDA		$19
#define C0_BPCM		$20
#define	C0_BDAM		$21

$dcs		=	$7
$bpc		=	$18
$bda		=	$19
$bpcm		=	$20
$bdam		=	$21

#else

#define C0_DCS		7
#define C0_BPC		18
#define C0_BDA		19
#define C0_BPCM		20
#define	C0_BDAM		21

/* CW400X-specific dbx module register access */

#if __mips16
extern reg32_t	_cw400x_mfd (int);
extern void	_cw400x_mtd (int, reg32_t);
#else
#define _cw400x_mfd(reg) \
({ \
  register reg32_t __r; \
  __asm__ __volatile ("mfd %0,$%1" \
		      : "=d" (__r) \
      		      : "JK" (reg)); \
  __r; \
})

#define _cw400x_mtd(reg, val) \
do { \
    __asm__ __volatile ("%(mtd %z0,$%1; nop; nop; nop%)" \
			: \
			: "dJ" ((reg32_t)(val)), "JK" (reg) \
			: "memory");\
} while (0)
#endif

#define cw400x_getdcs()		_cw400x_mfd(7)
#define cw400x_setdcs(v)	_cw400x_mtd(7,v)

#define cw400x_getbpc()		_cw400x_mfd(18)
#define cw400x_setbpc(v)	_cw400x_mtd(18,v)

#define cw400x_getbda()		_cw400x_mfd(19)
#define cw400x_setbda(v)	_cw400x_mtd(19,v)

#define cw400x_getbpcm()	_cw400x_mfd(20)
#define cw400x_setbpcm(v)	_cw400x_mtd(20,v)

#define cw400x_getbdam()	_cw400x_mfd(21)
#define cw400x_setbdam(v)	_cw400x_mtd(21,v)

#endif

/* Debug Control and Status register */
#define DCS_TR		0x80000000	/* Trap enable */
#define DCS_UD		0x40000000	/* User debug enable */
#define DCS_KD		0x20000000	/* Kernel debug enable */
#define DCS_TE		0x10000000	/* Trace enable */
#define DCS_DW		0x08000000	/* Enable data breakpoints on write */
#define DCS_DR		0x04000000	/* Enable data breakpoints on read */
#define DCS_DAE 	0x02000000	/* Enable data addresss breakpoints */
#define DCS_PCE 	0x01000000	/* Enable instruction breakpoints */
#define DCS_DE		0x00800000	/* Debug enable */
#if #cpu(cw4002) || #cpu(tr4101)
#define DCS_IBD		0x00400000	/* Internal break disable */
#endif
#if #cpu(cw4002)
#define DCS_EBE		0x00200000	/* External break enable */
#endif
#define DCS_T		0x00000020	/* Trace, set by CPU */
#define DCS_W		0x00000010	/* Write reference, set by CPU */
#define DCS_R		0x00000008	/* Read reference, set by CPU */
#define DCS_DA		0x00000004	/* Data address, set by CPU */
#define DCS_PC		0x00000002	/* Program counter, set by CPU */
#define DCS_DB		0x00000001	/* Debug, set by CPU */

#ifdef __cplusplus
}
#endif
#endif /* _MIPS_CW4002_H_ */
