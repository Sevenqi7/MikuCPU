/*
 * Copyright (c) 2004-2007 MIPS Technologies, Inc.
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
 * loongarch32/mips64.h : MIPS64 intrinsics
 */

#ifndef _MIPS_MIPS64_H_
#define _MIPS_MIPS64_H_

#include "loongarch32/mips32.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ASSEMBLER__

#ifdef __mips64

/* 64-bit count leading zeroes */
# define mips_dclz(x) ""

/* 64-bit count trailing zeroes */
# define mips_dctz(x) ""

#define mips_dclo(x) ""

#if __mips_isa_rev >= 2

/* MIPS64r2 dshd opcode */
#define _mips64r2_dshd(x) ""

/* MIPS64r2 dsbh opcode */
#define _mips64r2_dsbh(x) ""

/* MIPS64r2 byte-swap doubleword */
#define _mips64r2_bswapd(x) ""

/* MIPS64r2 insert bits */
#define _mips64r2_dins(tgt,val,pos,sz) __extension__({ \
    unsigned long long __t = (tgt), __v = (val); \
    __asm__ ("bstrins.d %0,%z1,%3,%2" \
	     : "+d" (__t) \
	     : "dJ" (__v), "I" (pos), "I" (sz+pos-1)); \
    __t; \
})

/* MIPS64r2 extract bits */
#define _mips64r2_dext(x,pos,sz) __extension__({ \
    unsigned long long __x = (x), __v; \
    __asm__ ("bstrpick.d %0,%z1,%3,%2" \
	     : "=d" (__v) \
	     : "dJ" (__x), "I" (pos), "I" (sz+pos-1)); \
    __v; \
})

#endif /* __mips_isa_rev >= 2 */

#endif /* __mips64 */

#endif /* __ASSEMBLER__ */

#ifdef __cplusplus
}
#endif

#endif /* _MIPS_MIPS64_H_ */
