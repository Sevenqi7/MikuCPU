/*
 * Copyright (c) 1998-2003 MIPS Technologies, Inc.
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
 * loongarch32/m16c1.h: MIPS16 coprocessor 1 (fpu) support.
 *  
 * Define functions for accessing the coprocessor 1 control
 * registers * from mips16 mode.
 *
 * Most apart from "set" return the original register value.
 */


#ifndef _MIPS_M16C1_H_
#define _MIPS_M16C1_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ASSEMBLER__

unsigned int	_mips16_frid (void);
unsigned int	_mips16_fsr (unsigned int clear, unsigned int set);
void		_mips16_lwc1 (const void *);
void		_mips16_ldc1 (const void *);

#undef fpa_getsr
#undef fpa_setsr
#undef fpa_xchsr
#undef fpa_bicsr
#undef fpa_bissr
#undef fpa_getrid

#define fpa_getsr()	_mips16_fsr (0, 0)
#define fpa_setsr(v)	_mips16_fsr (~0, v)
#define fpa_xchsr(v)	_mips16_fsr (~0, v)
#define fpa_bicsr(v)	_mips16_fsr (v, 0)
#define fpa_bissr(v)	_mips16_fsr (0, v)
#define fpa_getrid() 	_mips16_frid ();

#endif /* __ASSEMBLER */

#ifdef __cplusplus
}
#endif

#endif /* _MIPS_M16C1_H_ */
