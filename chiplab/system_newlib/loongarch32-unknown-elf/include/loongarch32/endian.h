/*
 * Copyright (c) 1997 Niklas Hallqvist.  All rights reserved.
 * Copyright (c) 1996-2006 MIPS Technologies, Inc.
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
 * mips/endian.h : MIPS-specific endian definitions
 */

#ifndef _MIPS_ENDIAN_H_
#define _MIPS_ENDIAN_H_

#include <stdint.h>

#ifndef BYTE_ORDER
/*
 * Definitions for byte order,
 * according to byte significance from low address to high.
 */
#define LITTLE_ENDIAN   1234    /* least-significant byte first (vax) */
#define BIG_ENDIAN      4321    /* most-significant byte first (IBM, net) */

#if #endian(big) || defined(__MIPSEB__) || defined(MIPSEB)
#define BYTE_ORDER      BIG_ENDIAN
#elif #endian(little) || defined(__MIPSEL__) || defined(MIPSEL)
#define BYTE_ORDER      LITTLE_ENDIAN
#else
#error BYTE_ORDER 
#endif
#endif

#ifndef __ASSEMBLER__

#define __swap16gen(x) __extension__({					\
	uint16_t __swap16gen_x = (x);					\
									\
	(uint16_t)((__swap16gen_x << 8) |				\
		    (__swap16gen_x >> 8));				\
})

#define __swap32gen(x) __extension__({					\
	uint32_t __swap32gen_x = (x);					\
									\
        __swap32gen_x = (__swap32gen_x >> 16) | (__swap32gen_x << 16);	\
        ((__swap32gen_x & 0xff00ff) << 8) |				\
	((__swap32gen_x >> 8) & 0xff00ff);				\
})

#if __mips_isa_rev >= 2 && ! __mips16

/* MIPS32r2 & MIPS64r2 can use the wsbh and rotate instructions, define
   MD_SWAP so that <sys/endian.h> will use them. */

#define MD_SWAP

#define __swap16md(x) __extension__({					\
    uint16_t __swap16md_x = (x);					\
    uint16_t __swap16md_v;						\
    __asm__ ("wsbh %0,%1" 						\
	     : "=d" (__swap16md_v) 					\
	     : "d" (__swap16md_x)); 					\
    __swap16md_v; 							\
})

#define __swap32md(x) __extension__({					\
    uint32_t __swap32md_x = (x);					\
    uint32_t __swap32md_v;						\
    __asm__ ("wsbh %0,%1; rotr %0,16" 					\
	     : "=d" (__swap32md_v) 					\
	     : "d" (__swap32md_x)); 					\
    __swap32md_v; 							\
})

#elif defined(__OPTIMIZE_SIZE__) && !defined(_POSIX_SOURCE)

#define MD_SWAP

/* When optimizing for size, better to call a shared worker function,
   unless the code is small enough or there's only one use of the
   function, in which case it will be inlined. */

#ifdef __cplusplus
extern "C" {
#endif

extern __inline__ uint16_t __attribute__((__gnu_inline)) __swap16md (uint16_t x)
{
    return __swap16gen(x);
}

extern __inline__ uint32_t __attribute__((__gnu_inline)) __swap32md (uint32_t x)
{
    return __swap32gen(x);
}

#ifdef __cplusplus
}
#endif

#endif

#ifndef _POSIX_SOURCE
/*
 * Define MD_SWAP if you provide swap{16,32}md functions/macros that are
 * optimized for your architecture,  These will be used for swap{16,32}
 * unless the argument is a constant and we are using GCC, where we can
 * take advantage of the CSE phase much better by using the generic version.
 */
#ifdef MD_SWAP

#define swap16(x) __extension__({					\
	uint16_t __swap16_x = (x);					\
									\
	__builtin_constant_p(x) ? __swap16gen(__swap16_x) :		\
	    __swap16md(__swap16_x);					\
})

#define swap32(x) __extension__({					\
	uint32_t __swap32_x = (x);					\
									\
	__builtin_constant_p(x) ? __swap32gen(__swap32_x) :		\
	    __swap32md(__swap32_x);					\
})

#else /* MD_SWAP */
#define swap16 __swap16gen
#define swap32 __swap32gen
#endif /* MD_SWAP */

#define swap16_multi(v, n) do {					        \
	size_t __swap16_multi_n = (n);					\
	uint16_t *__swap16_multi_v = (v);				\
									\
	while (__swap16_multi_n) {					\
		*__swap16_multi_v = swap16(*__swap16_multi_v);		\
		__swap16_multi_v++;					\
		__swap16_multi_n--;					\
	}								\
} while (0)

#ifdef __cplusplus
extern "C" {
#endif

uint32_t	htobe32 (uint32_t);
uint16_t	htobe16 (uint16_t);
uint32_t	betoh32 (uint32_t);
uint16_t	betoh16 (uint16_t);

uint32_t	htole32 (uint32_t);
uint16_t	htole16 (uint16_t);
uint32_t	letoh32 (uint32_t);
uint16_t	letoh16 (uint16_t);

uint32_t	(ntohl) (uint32_t);
uint32_t	(htonl) (uint32_t);
uint16_t	(ntohs) (uint16_t);
uint16_t	(htons) (uint16_t);
#ifdef __cplusplus
}
#endif

#if BYTE_ORDER == LITTLE_ENDIAN

#ifndef _QUAD_HIGHWORD
#define _QUAD_HIGHWORD 1
#endif
#ifndef _QUAD_LOWWORD
#define _QUAD_LOWWORD 0
#endif

#define htobe16 swap16
#define htobe32 swap32
#define betoh16 swap16
#define betoh32 swap32

#define htole16(x) (x)
#define htole32(x) (x)
#define letoh16(x) (x)
#define letoh32(x) (x)

#elif BYTE_ORDER == BIG_ENDIAN

#ifndef _QUAD_HIGHWORD
#define _QUAD_HIGHWORD 0
#endif
#ifndef _QUAD_LOWWORD
#define _QUAD_LOWWORD 1
#endif

#define htole16 swap16
#define htole32 swap32
#define letoh16 swap16
#define letoh32 swap32

#define htobe16(x) (x)
#define htobe32(x) (x)
#define betoh16(x) (x)
#define betoh32(x) (x)

#endif /* BYTE_ORDER */

#define htons htobe16
#define htonl htobe32
#define ntohs betoh16
#define ntohl betoh32

#define	NTOHL(x) (x) = ntohl((uint32_t)(x))
#define	NTOHS(x) (x) = ntohs((uint16_t)(x))
#define	HTONL(x) (x) = htonl((uint32_t)(x))
#define	HTONS(x) (x) = htons((uint16_t)(x))

#endif /* _POSIX_SOURCE */

#endif /* __ASSEMBLER__ */
#endif /* _MIPS_ENDIAN_H */
