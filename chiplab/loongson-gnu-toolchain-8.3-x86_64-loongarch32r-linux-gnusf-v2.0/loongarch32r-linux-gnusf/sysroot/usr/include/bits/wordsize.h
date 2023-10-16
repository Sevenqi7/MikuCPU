/* Copyright (C) 1999-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifdef __loongarch64
#define __loongarch_xlen			64
#elif (defined __loongarch32) || (defined __loongarch32r)
#define __loongarch_xlen			32
#endif

#define __WORDSIZE			__loongarch_xlen
#define __WORDSIZE_TIME64_COMPAT32	0

#if __WORDSIZE == 32
# define __WORDSIZE32_SIZE_ULONG    0
# define __WORDSIZE32_PTRDIFF_LONG  0
#endif
