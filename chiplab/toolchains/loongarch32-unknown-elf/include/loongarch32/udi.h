/*
 * Copyright (c) 2002-2004 MIPS Technologies, Inc.
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
 * mips/udi.h: UDI intrinsics
 */


#ifndef _MIPS_UDI_H_
#define _MIPS_UDI_H_

/* rs read-write */
#define __mips_udi_ri_x(VOL, OP, S, IMM)  			\
__extension__ ({						\
  __typeof__(S) __s = (S);					\
  __asm__ VOL ("udi%1 %0,%2" 					\
	       : "+d" (__s) 					\
	       : "K" (OP), "K" (IMM)); 				\
  __s; 								\
})

/* rs read-only; rt write-only */
#define __mips_udi_rwi_x(VOL, OP, S, IMM)  			\
__extension__ ({						\
  __typeof__(S) __t;						\
  __asm__ VOL ("udi%1 %z2,%0,%3" 				\
	   : "=d" (__t) 					\
	   : "K" (OP), "dJ" (S), "K" (IMM)); 			\
  __t; 								\
})

/* rs read-only; rt read-write */
#define __mips_udi_rri_x(VOL, OP, S, T, IMM)  			\
__extension__ ({						\
  __typeof__(S) __t = (T);					\
  __asm__ VOL ("udi%1 %z2,%0,%3" 				\
	   : "+d" (__t) 					\
	   : "K" (OP), "dJ" (S), "K" (IMM)); 			\
  __t; 								\
})

/* rs & rt read-only; rd write-only */
#define __mips_udi_rrwi_x(VOL, OP, S, T, IMM)  			\
__extension__ ({						\
  __typeof__(S) __d;						\
  __asm__ VOL ("udi%1 %z2,%z3,%0,%4" 				\
	   : "=d" (__d) 					\
	   : "K" (OP), "dJ" (S), "dJ" (T), "K" (IMM)); 		\
  __d; 								\
})


/* Basic UDI instructions are assumed to write a result to their
   final CPU register operand, but may may have other side effects
   such as using or modifying internal UDI registers, so they won't be
   optimised by the compiler. */

/* The mips_udi_ri() intrinsic passes S in RS register, 
   and returns the r/w RS register */
#define mips_udi_ri(OP, S, IMM)					\
	__mips_udi_ri_x (__volatile, OP, S, IMM)

/* The mips_udi_rwi() intrinsic passes S in RS register, 
   and returns the w/o RT register */
#define mips_udi_rwi(OP, S, IMM)					\
	__mips_udi_rwi_x (__volatile, OP, S, IMM)

/* The mips_udi_rri() intrinsic passes S in RS register, T in RT,
   and returns the r/w RT register */
#define mips_udi_rri(OP, S, T, IMM)				\
	__mips_udi_rri_x (__volatile, OP, S, T, IMM) 

/* The mips_udi_rrwi() intrinsic passes S in RS, T in RT, 
   and returns the w/o RD register */
#define mips_udi_rrwi(OP, S, T, IMM)				\
	__mips_udi_rrwi_x (__volatile, OP, S, T, IMM)

/* For backwards compatibility... */
#define mips_udi_rrri(OP, S, T, IMM)				\
	__mips_udi_rrwi_x (__volatile, OP, S, T, IMM)

/* The mips_udi_i() intrinsics use no register inputs, but return the
   value written to the RS register (the input value is assumed
   discarded). */
#define mips_udi_i(OP, IMM)					\
__extension__ ({						\
  int __s;							\
  __asm__ __volatile ("udi%1 %0,%2" 				\
	       : "=d" (__s) 					\
	       : "K" (OP), "K" (IMM)); 				\
  __s; 								\
})

#define mips_udi_i_64(OP, IMM)					\
__extension__ ({						\
  long long __s;						\
  __asm__ __volatile ("udi%1 %0,%2" 				\
	       : "=d" (__s) 					\
	       : "K" (OP), "K" (IMM)); 				\
  __s; 								\
})

/* Optimisable intrinsics for UDI instructions which read only the CPU
   source registers and write to the destination CPU register only,
   and have no other side effects, i.e. they only use and modify the
   supplied CPU registers. */

#define mips_udi_ri_safe(OP, S, IMM)				\
	__mips_udi_ri_x (, OP, S, IMM)
#define mips_udi_rwi_safe(OP, S, IMM)				\
	__mips_udi_rwi_x (, OP, S, IMM)
#define mips_udi_rri_safe(OP, S, T, IMM)			\
	__mips_udi_rri_x (, OP, S, T, IMM) 
#define mips_udi_rrwi_safe(OP, S, T, IMM)			\
	__mips_udi_rrwi_x (, OP, S, T, IMM)

/* Backwards compatibility... */
#define mips_udi_rrri_safe(OP, S, T, IMM)			\
	__mips_udi_rrwi_x (, OP, S, T, IMM)


/* "Novalue" intrinsics for UDI instructions which don't write a
   result to a CPU register, so presumably must have some other side
   effect, such as modifying an internal UDI register. */

#define mips_udi_nv(IMM)					\
  do { 								\
    __asm__ __volatile ("udi %0"				\
		 : /* no outputs */				\
 	         : "n" (IMM));					\
  } while (0)

#define mips_udi_i_nv(OP, IMM)					\
  do { 								\
    __asm__ __volatile ("udi%0 %1"				\
		 : /* no outputs */				\
		 : "K" (OP), "n" (IMM)); 			\
  } while (0)

#define mips_udi_ri_nv(OP, S, IMM)				\
  do { 								\
    __asm__ __volatile ("udi%0 %z1,%2"				\
	       : /* no outputs */				\
	       : "K" (OP), "dJ" (S), "K" (IMM)); 		\
  } while (0)

#define mips_udi_rri_nv(OP, S, T, IMM)				\
  do { 								\
    __asm__ __volatile ("udi%0 %z1,%z2,%3"			\
	       : /* no outputs */				\
	       : "K" (OP), "dJ" (S), "dJ" (T), "K" (IMM)); 	\
  } while (0)

#define mips_udi(IMM)						\
	mips_udi_nv (IMM)

/* These 4 variants of the three register operand format allow
   constant values to be placed in the RS, RT fields, presumably
   because they name internal UDI registers. The RD register is still
   allocated by the compiler. They are implicitly "unsafe" or
   volatile. */

#define mips_udi_riri(OP, S, IT, IMM) 				\
__extension__ ({ 						\
  __typeof__(S) __d;						\
  __asm__ __volatile ("udi%1 %z2,$%3,%0,%4" 			\
	   : "=d" (__d) 					\
	   : "K" (OP), "dJ" (S), "K" (IT), "K" (IMM)); 		\
  __d; 								\
})

#define mips_udi_irri(OP, IS, T, IMM)  				\
__extension__ ({ 						\
  __typeof__(T) __d;						\
  __asm__ __volatile ("udi%1 $%2,%z3,%0,%4" 			\
	   : "=d" (__d) 					\
	   : "K" (OP), "K" (IS), "dJ" (T), "K" (IMM)); 		\
  __d; 								\
})

#define mips_udi_iiri_32(OP, IS, IT, IMM) 			\
__extension__ ({						\
  int __d;							\
  __asm__ __volatile ("udi%1 $%2,$%3,%0,%4" 			\
	   : "=d" (__d) 					\
	   : "K" (OP), "K" (IS), "K" (IT), "K" (IMM)); 		\
  __d; 								\
})

#define mips_udi_iiri_64(OP, IS, IT, IMM) 			\
__extension__ ({ 						\
  long long __d;						\
  __asm__ __volatile ("udi%1 $%2,$%3,%0,%4" 			\
	   : "=d" (__d) 					\
	   : "K" (OP), "K" (IS), "K" (IT), "K" (IMM)); 		\
  __d; 								\
})


/* These 5 variants of the three register format allow constant values
   to be placed in the RS, RT and RD fields, presumably because they
   name internal UDI registers. In case the instruction writes to an
   implicit gp register, pass the register number as GPDEST and the
   compiler will be told that it's been clobbered, and its value will
   be returned - if no gp register is written, pass 0. They are all
   implicitly unsafe, or volatile. */

#define mips_udi_rrii(OP, S, T, ID, IMM, GPDEST) 		\
__extension__ ({ 						\
  __typeof__(S) __d;						\
  __asm__ ("udi%0 %z1,%z2,$%3,%4" 				\
	   : /* no outputs */ 					\
	   : "K" (OP), "dJ" (S), "dJ" (T), "K" (ID), "K" (IMM)  \
           : "$" # GPDEST); 					\
  if (GPDEST != 0)						\
    __asm__ __volatile ("move %0,$"  # GPDEST			\
			: "=d" (__d));				\
  __d;								\
})

#define mips_udi_riii(OP, S, IT, ID, IMM, GPDEST)  		\
__extension__ ({ 						\
  __typeof__(S) __d;						\
  __asm__ ("udi%0 %z1,$%2,$%3,%4" 				\
	   : /* no outputs */ 					\
	   : "K" (OP), "dJ" (S), "K" (IT), "K" (ID), "K" (IMM)	\
           : "$" # GPDEST); 					\
  if (GPDEST != 0)						\
    __asm__ __volatile ("move %0,$"  # GPDEST			\
			: "=d" (__d));				\
})

#define mips_udi_irii(OP, IS, T, ID, IMM, GPDEST)  		\
__extension__ ({ 						\
  __typeof__(T) __d;						\
  __asm__ ("udi%0 $%1,%z2,$%3,%4" 				\
	   : /* no outputs */ 					\
	   : "K" (OP), "K" (IS), "dJ" (T), "K" (ID), "K" (IMM)	\
           : "$" # GPDEST); 					\
  if (GPDEST != 0)						\
    __asm__ __volatile ("move %0,$"  # GPDEST			\
			: "=d" (__d));				\
})

#define mips_udi_iiii_32(OP, IS, IT, ID, IMM, GPDEST)  		\
__extension__ ({						\
  int __d;							\
  __asm__ ("udi%0 $%1,$%2,$%3,%4" 				\
	   : /* no outputs */ 					\
	   : "K" (OP), "K" (IS), "K" (IT), "K" (ID), "K" (IMM)  \
           : "$" # GPDEST); 					\
  if (GPDEST != 0)						\
    __asm__ __volatile ("move %0,$"  # GPDEST			\
			: "=d" (__d));				\
})

#define mips_udi_iiii_64(OP, IS, IT, ID, IMM, GPDEST)  		\
__extension__ ({ 						\
  long long __d;						\
  __asm__ ("udi%0 $%1,$%2,$%3,%4" 				\
	   : /* no outputs */ 					\
	   : "K" (OP), "K" (IS), "K" (IT), "K" (ID), "K" (IMM)  \
           : "$" # GPDEST); 					\
  if (GPDEST != 0)						\
    __asm__ __volatile ("move %0,$"  # GPDEST			\
			: "=d" (__d));				\
})

#endif
