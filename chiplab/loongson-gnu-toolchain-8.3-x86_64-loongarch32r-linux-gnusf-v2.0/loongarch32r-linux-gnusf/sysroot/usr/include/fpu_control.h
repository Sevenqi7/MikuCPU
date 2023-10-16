/* FPU control word bits.  Mips version.
   Copyright (C) 1996-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Olaf Flebbe and Ralf Baechle.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _FPU_CONTROL_H
#define _FPU_CONTROL_H

/* MIPS FPU floating point control register bits.
 *
 * 31-25  -> floating point conditions code bits 7-1.  These bits are only
 *           available in MIPS IV.
 * 24     -> flush denormalized results to zero instead of
 *           causing unimplemented operation exception.  This bit is only
 *           available for MIPS III and newer.
 * 23     -> Condition bit
 * 22-21  -> reserved for architecture implementers
 * 20     -> reserved (read as 0, write with 0)
 * 19     -> IEEE 754-2008 non-arithmetic ABS.fmt and NEG.fmt enable
 * 18     -> IEEE 754-2008 recommended NaN encoding enable
 * 17     -> cause bit for unimplemented operation
 * 28     -> cause bit for invalid exception
 * 27     -> cause bit for division by zero exception
 * 26     -> cause bit for overflow exception
 * 25     -> cause bit for underflow exception
 * 24     -> cause bit for inexact exception
 *  4     -> enable exception for invalid exception
 *  3     -> enable exception for division by zero exception
 *  2     -> enable exception for overflow exception
 *  1     -> enable exception for underflow exception
 *  0     -> enable exception for inexact exception
 * 20     -> flag invalid exception
 * 19     -> flag division by zero exception
 * 18     -> flag overflow exception
 * 17     -> flag underflow exception
 * 16     -> flag inexact exception
 *  9-8   -> rounding control
 *
 *
 * Rounding Control:
 * 00 - rounding to nearest (RN)
 * 01 - rounding toward zero (RZ)
 * 10 - rounding (up) toward plus infinity (RP)
 * 11 - rounding (down)toward minus infinity (RM)
 */

#include <features.h>

#ifdef __loongarch_soft_float

#define _FPU_RESERVED 0xffffffff
#define _FPU_DEFAULT  0x00000000
typedef unsigned int fpu_control_t;
#define _FPU_GETCW(cw) (cw) = 0
#define _FPU_SETCW(cw) (void) (cw)
extern fpu_control_t __fpu_control;

#else /* __loongarch_soft_float */

/* Masks for interrupts.  */
#define _FPU_MASK_V     0x10  /* Invalid operation */
#define _FPU_MASK_Z     0x08  /* Division by zero  */
#define _FPU_MASK_O     0x04  /* Overflow          */
#define _FPU_MASK_U     0x02  /* Underflow         */
#define _FPU_MASK_I     0x01  /* Inexact operation */

/* Flush denormalized numbers to zero.  */
#define _FPU_FLUSH_TZ   0x1000000

/* Rounding control.  */
#define _FPU_RC_NEAREST 0x000     /* RECOMMENDED */
#define _FPU_RC_ZERO    0x100
#define _FPU_RC_UP      0x200
#define _FPU_RC_DOWN    0x300
/* Mask for rounding control.  */
#define _FPU_RC_MASK	0x300

#define _FPU_RESERVED 0x0

#define _FPU_DEFAULT 0x0
#define _FPU_IEEE    0x1F

/* Type of the control word.  */
typedef unsigned int fpu_control_t __attribute__ ((__mode__ (__SI__)));

/* Macros for accessing the hardware control word.  */
extern fpu_control_t __mips_fpu_getcw (void) __THROW;
extern void __mips_fpu_setcw (fpu_control_t) __THROW;
#define _FPU_GETCW(cw) __asm__ volatile ("movfcsr2gr %0,$r0" : "=r" (cw))
#define _FPU_SETCW(cw) __asm__ volatile ("movgr2fcsr $r0,%0" : : "r" (cw))

/* Default control word set at startup.  */
extern fpu_control_t __fpu_control;

#endif /* __loongarch_soft_float */

#endif	/* fpu_control.h */
