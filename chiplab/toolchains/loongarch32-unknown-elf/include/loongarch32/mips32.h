/*
 * Copyright (c) 2004-2007 MIPS Technologies, Inc.
 * Copyright (C) 2009 CodeSourcery, LLC,
 *
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
 * loongarch32/mips32.h : MIPS32 intrinsics
 */

#ifndef _MIPS32_H_
#define _MIPS32_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ASSEMBLER__

#if ! __mips16

/* C interface to clz/clo instructions */

# if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)

/* use GCC builtins for better optimisation */

/* count leading zeros */
# define mips_clz(x) __builtin_clz (x)

/* count trailing zeros */
# define mips_ctz(x) __builtin_ctz (x)

#else

/* count leading zeros */
#define mips_clz(x) ""

/* count trailing zeros */
#define mips_ctz(x) ""

#endif

#define mips_clo(x) ""

#ifndef __mips64

/* Simulate 64-bit count leading zeroes */
#define mips_dclz(x) ""

/* Simulate 64-bit count leading ones */
#define mips_dclo(x) ""

/* Simulate 64-bit count trailing zeroes */
#define mips_dctz(x) ""
#endif

#if __mips_isa_rev >= 2

/* MIPS32r2 wsbh opcode */
#define _mips32r2_wsbh(x) __extension__({ \
    unsigned int __x = (x), __v; \
    __asm__ ("revb.2h %0,%1" \
	     : "=d" (__v) \
	     : "d" (__x)); \
    __v; \
})

/* MIPS32r2 byte-swap word */
#define _mips32r2_bswapw(x) __extension__({ \
    unsigned int __x = (x), __v; \
    __asm__ ("revb.2h %0,%1; rotr %0,16" \
	     : "=d" (__v) \
	     : "d" (__x)); \
    __v; \
})

/* MIPS32r2 insert bits */
#define _mips32r2_ins(tgt,val,pos,sz) __extension__({ \
    unsigned int __t = (tgt), __v = (val); \
    __asm__ ("bstrins.w %0,%z1,%3,%2" \
	     : "+d" (__t) \
	     : "dJ" (__v), "I" (pos), "I" (sz+pos-1)); \
    __t; \
})

/* MIPS32r2 extract bits */
#define _mips32r2_ext(x,pos,sz) __extension__({ \
    unsigned int __x = (x), __v; \
    __asm__ ("bstrpick.w %0,%z1,%3,%2" \
	     : "=d" (__v) \
	     : "dJ" (__x), "I" (pos), "I" (sz+pos-1)); \
    __v; \
})

#endif /* __mips_isa_rev >= 2 */

/* MIPS32r2 jr.hb */
#if _MIPS_SIM==_ABIO32 || _MIPS_SIM==_ABIN32 || _MIPS_SIM==_ABIO64
#define mips32_jr_hb() ""
#elif _MIPS_SIM==_ABI64
#define mips32_jr_hb() ""
#else
#error Unknown ABI
#endif

#endif /* ! __mips16 */

#endif /* __ASSEMBLER__ */

#ifdef __cplusplus
}
#endif

#endif /* _MIPS32_H_ */
