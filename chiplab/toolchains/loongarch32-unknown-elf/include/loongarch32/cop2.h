/*
 * Copyright (c) 2002-2003 MIPS Technologies, Inc.
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
 * mips/cop2.h: COP2 intrinsics
 */


#ifndef _MIPS_COP2_H_
#define _MIPS_COP2_H_

/* Load 32-bit COP2 data register C2REG from memory operand MEM */
#define mips_lwc2(C2REG, MEM)					\
do {								\
    __asm__ __volatile ("lwc2 $%0,%1"				\
			  : /* no outputs */			\
			  : "n" (C2REG), "m" (MEM));		\
} while (0)

/* Store 32-bit COP2 data register C2REG to memory operand MEM */
#define mips_swc2(C2REG, MEM)					\
do {								\
    __asm__ __volatile ("swc2 $%1,%0"				\
			  : "=m" (MEM)				\
			  : "n" (C2REG));			\
} while (0)

/* Load 64-bit COP2 data register C2REG from memory operand MEM */
#define mips_ldc2(C2REG, MEM)					\
do {								\
    __asm__ __volatile ("ldc2 $%0,%1"				\
			  : /* no outputs */			\
			  : "n" (C2REG), "m" (MEM));		\
} while (0)

/* Store 64-bit COP2 data register C2REG to memory operand MEM */
#define mips_sdc2(C2REG, MEM)					\
do {								\
    __asm__ __volatile ("sdc1 $%1,%0"				\
			  : "=m" (MEM)				\
			  : "n" (C2REG));			\
} while (0)

/* Set 32-bit COP2 data register C2REG,SEL to VAL */
#define mips_mtc2(VAL, C2REG, SEL)				\
do {								\
    __asm__ __volatile ("mtc2 %0,$%1,%2"			\
			  : /* no outputs */			\
			  :  "d" (VAL), "n" (C2REG), "n" (SEL));\
} while (0)

/* Get 32-bit COP2 data register C2REG,SEL */
#define mips_mfc2(C2REG, SEL)					\
__extension__ ({						\
    int __v;							\
    __asm__ __volatile ("mfc2 %0,$%1,%2"			\
			  : "=d" (__v)				\
			  : "n" (C2REG), "n" (SEL));		\
    __v;							\
})

/* Set 64-bit COP2 data register C2REG,SEL to VAL */
#define mips_dmtc2(VAL, C2REG, SEL)				\
do {								\
    __asm__ __volatile ("dmtc2 %0,$%1,%2"			\
			  : /* no outputs */			\
			  :  "d" (VAL), "n" (C2REG), "n" (SEL));\
} while (0)

/* Get 64-bit COP2 data register C2REG,SEL */
#define mips_dmfc2(C2REG, SEL)					\
__extension__ ({						\
    long long __v;						\
    __asm__ __volatile ("dmfc2 %0,$%1,%2"			\
			  : "=d" (__v)				\
			  : "n" (C2REG), "n" (SEL));		\
    __v;							\
})

/* Perform COP2 operation OP */
#define mips_cop2(OP)						\
do {								\
    __asm__ __volatile ("c2 %0"					\
			  : /* no outputs */			\
			  :  "n" (OP));				\
} while (0)

/* Set 32-bit COP2 control register C2REG to VAL */
#define mips_ctc2(VAL, C2REG)					\
do {								\
    __asm__ __volatile ("ctc2 %1,$%0"				\
			  : /* no outputs */			\
			  :  "n" (C2REG), "d" (VAL));		\
} while (0)

/* Get 32-bit COP2 control register C2REG */
#define mips_cfc2(C2REG)					\
__extension__ ({						\
    int __v;							\
    __asm__ __volatile ("cfc2 %0,$%1"				\
			  : "=d" (__v)				\
			  : "n" (C2REG));			\
    __v;							\
})

/* Return value of COP2 cond code number CC */
#define mips_c2t(CC)						\
__extension__ ({						\
   int __c;							\
   __asm__ __volatile (						\
       "li	%0,1\n"						\
"	%(bc2tl	$cc%1,0f\n"					\
"	move	%0,%.%)\n"					\
"0:"								\
  	: "=&d" (__c)						\
 	:  "n" (CC));						\
   __c;								\
})

/* Return inverted value of COP2 cond code number CC */
#define mips_c2f(CC)						\
__extension__ ({						\
   int __c;							\
   __asm__ __volatile (						\
       "li	%0,1\n"						\
"	%(bc2fl	$cc%1,0f\n"					\
"	move	%0,%.%)\n"					\
"0:"								\
  	: "=&d" (__c)						\
 	:  "n" (CC));						\
   __c;								\
})

#endif
