/*
 * Copyright (c) 1997-2003 MIPS Technologies, Inc.
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
 * r5kc1.h : SDE R5000 coprocessor 1 (fpa) definitions
 */


#ifndef _MIPS_R5KC1_H_
#define _MIPS_R5KC1_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ASSEMBLER__

typedef unsigned long long _fpreg_t;

struct fpactx {
    unsigned	sr;		/* floating-point status register */
    unsigned	dummy;
    _fpreg_t	regs[32];	/* floating-point registers $f0-$f31 */
#if #cpu(r54xx)
    _fpreg_t	acl;		/* MDMX accumulator (low 64 bits) */
    _fpreg_t	acm;		/* MDMX accumulator (middle 64 bits) */
    _fpreg_t	ach;		/* MDMX accumulator (high 64 bits) */
#endif
};

#ifdef __STDC__
int	 fpa_enable(int);	/* enable fpa, return 1 if present (always) */
unsigned fpa_getrid(void);	/* get fpa revision id */
unsigned fpa_getsr(void);	/* get fpa status register */
void	 fpa_setsr(unsigned);
unsigned fpa_xchsr(unsigned);
unsigned fpa_bicsr(unsigned);
unsigned fpa_bissr(unsigned);
void	fpa_save(struct fpactx *);
void	fpa_restore(const struct fpactx *);
#else
int	 fpa_enable();
unsigned fpa_getrid();
unsigned fpa_getsr();
void	 fpa_setsr();
unsigned fpa_xchsr();
unsigned fpa_bicsr();
unsigned fpa_bissr();
void	fpa_save();
void	fpa_restore();
#endif /* __STDC__ */

/* 
 * Define macros to accessing the R3000 coprocessor 1 control registers.
 * Most apart from "set" return the original register value.
 */

#define fpa_getrid() \
({ \
  register unsigned __r; \
  __asm__ __volatile ("cfc1 %0,$0" : "=d" (__r)); \
  __r; \
})

#define fpa_getsr() \
({ \
  register unsigned __r; \
  __asm__ __volatile ("cfc1 %0,$31" : "=d" (__r)); \
  __r; \
})

#define fpa_setsr(val) \
({ \
    register unsigned __r = (val); \
    __asm__ __volatile ("ctc1 %0,$31" : : "d" (__r)); \
    __r; \
})

#define fpa_xchsr(val) \
({ \
    register unsigned __o, __n = (val); \
    __asm__ __volatile ("cfc1 %0,$31" : "=d" (__o)); \
    __asm__ __volatile ("ctc1 %0,$31" : : "d" (__n)); \
    __o; \
})


#define fpa_bissr(val) \
({ \
    register unsigned __o, __n; \
    __asm__ __volatile ("cfc1 %0,$31" : "=d" (__o)); \
    __n = __o | (val); \
    __asm__ __volatile ("ctc1 %0,$31" : : "d" (__n)); \
    __o; \
})


#define fpa_bicsr(val) \
({ \
    register unsigned __o, __n; \
    __asm__ __volatile ("cfc1 %0,$31" : "=d" (__o)); \
    __n = __o &~ (val); \
    __asm__ __volatile ("ctc1 %0,$31" : : "d" (__n)); \
    __o; \
})
#endif /* !ASSEMBLER */

/* 
 * Status Register Values
 */

#define FPA_CSR_COND	0x00800000	/* $fcc0 */
#define FPA_CSR_COND0	0x00800000	/* $fcc0 */
#define FPA_CSR_FLUSH	0x01000000	/* flush to 0 */
#define FPA_CSR_FS	0x01000000	/* flush to 0 */
#define FPA_CSR_COND1	0x02000000	/* $fcc1 */
#define FPA_CSR_COND2	0x04000000	/* $fcc2 */
#define FPA_CSR_COND3	0x08000000	/* $fcc3 */
#define FPA_CSR_COND4	0x10000000	/* $fcc4 */
#define FPA_CSR_COND5	0x20000000	/* $fcc5 */
#define FPA_CSR_COND6	0x40000000	/* $fcc6 */
#define FPA_CSR_COND7	0x80000000	/* $fcc7 */

/*
 * X the exception cause indicator
 * E the exception enable
 * S the sticky/flag bit
*/
#define FPA_CSR_ALL_X 0x0003f000
#define FPA_CSR_UNI_X	0x00020000
#define FPA_CSR_INV_X	0x00010000
#define FPA_CSR_DIV_X	0x00008000
#define FPA_CSR_OVF_X	0x00004000
#define FPA_CSR_UDF_X	0x00002000
#define FPA_CSR_INE_X	0x00001000

#define FPA_CSR_ALL_E	0x00000f80
#define FPA_CSR_INV_E	0x00000800
#define FPA_CSR_DIV_E	0x00000400
#define FPA_CSR_OVF_E	0x00000200
#define FPA_CSR_UDF_E	0x00000100
#define FPA_CSR_INE_E	0x00000080

#define FPA_CSR_ALL_S	0x0000007c
#define FPA_CSR_INV_S	0x00000040
#define FPA_CSR_DIV_S	0x00000020
#define FPA_CSR_OVF_S	0x00000010
#define FPA_CSR_UDF_S	0x00000008
#define FPA_CSR_INE_S	0x00000004

/* rounding mode */
#define FPA_CSR_RN	0x0	/* nearest */
#define FPA_CSR_RZ	0x1	/* towards zero */
#define FPA_CSR_RU	0x2	/* towards +Infinity */
#define FPA_CSR_RD	0x3	/* towards -Infinity */

#ifdef __ASSEMBLER__

	.struct 0
FPACTX_SR:	.word	0
FPACTX_DUMMY:	.word	0
#define FPACTX_RSIZE	8
FPACTX_REGS:	.dword	0:32
#if #cpu(r54xx)
FPACTX_ACL:	.dword	0
FPACTX_ACM:	.dword	0
FPACTX_ACH:	.dword	0
#endif
	.previous

/* control regs */
	$fpa_rid =	$0
	$fpa_sr  =	$31
#endif

#ifdef __cplusplus
}
#endif

#endif /*_MIPS_R5KC1_H_*/
