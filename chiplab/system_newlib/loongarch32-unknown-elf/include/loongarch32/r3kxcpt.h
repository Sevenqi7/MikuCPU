/*
 * Copyright (c) 1996-2004 MIPS Technologies, Inc.
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
 * r3kxcpt.h: SDE R3000 xcption handling 
 */

/* Exception classes. */
#ifdef XCPCDEF
/*XCPCDEF(NAME,		NUM, 	SIG,		DESC)*/
XCPCDEF(XCPC_GENERAL,	0, 	0,		"General")
XCPCDEF(XCPC_TLBMISS,	1, 	SIGSEGV,	"TLBMiss")
#if #cpu(cw400x) || #cpu(tr410x)
XCPCDEF(XCPC_DEBUG,	2, 	SIGTRAP,	"Debug")
#endif
#endif /* XCPCDEF */

/* Exception codes. */
#ifdef XCPTDEF
/*XCPTDEF(NAME,		NUM, 	SIG,		BRIEF,		DESC)*/
XCPTDEF(XCPTINTR,  	0,	SIGKILL,	"Intr",		"interrupt")
XCPTDEF(XCPTMOD,	1,	SIGSEGV,	"TLBMod",	"tlb modification")
XCPTDEF(XCPTTLBL,	2,	SIGSEGV,	"TLBL",		"tlb fault on read")
XCPTDEF(XCPTTLBS,	3,	SIGSEGV,	"TLBS",		"tlb fault on write")
XCPTDEF(XCPTADEL,	4,	SIGBUS,		"AdEL",		"address error on read")
XCPTDEF(XCPTADES,	5,	SIGBUS,		"AdES",		"address error on write")
XCPTDEF(XCPTIBE,	6,	SIGBUS,		"IBE",		"instruction bus error")
XCPTDEF(XCPTDBE,	7,	SIGBUS,		"DBE",		"data bus error")
XCPTDEF(XCPTSYS,	8,	SIGSYS,		"Sys",		"syscall instruction")
XCPTDEF(XCPTBP,		9,	SIGABRT,	"Bp",		"break instruction")
XCPTDEF(XCPTRI,		10,	SIGILL,		"RI",		"reserved instruction")
XCPTDEF(XCPTCPU,	11,	SIGILL,		"CpU",		"coprocessor unusable")
XCPTDEF(XCPTOVF,	12,	SIGFPE, 	"Ovf",		"arithmetic overflow")
#if #cpu(cw400x) || #cpu(tr410x)
XCPTDEF(XCPTTRAP,	13,	SIGABRT,	"Trap",		"trap exception")
#else
XCPTDEF(XCPTRES13,	13,	SIGKILL,	"13",		"13")
#endif
XCPTDEF(XCPTRES14,	14,	SIGKILL,	"14",		"14")
XCPTDEF(XCPTRES15,	15,	SIGKILL,	"15",		"15")
#endif /* XCPTDEF */

/* Use floating point interrupt instead of exception. */
#define XCPTFPE_ABSENT

#ifndef NXCPT
#define NXCPT		16
#endif

/* CPU specific extensions to xcptcontext */
#ifndef _xcptcontext_cpu

/* cpu-specific context (C version) */
#define _xcptcontext_cpu

/* cpu-specific context (assembler version) */
#define _xcptcontext_cpu_asm

/* cpu-specific context save to frame @xp, using registers tmp1 & tmp2 */
#define _xcptcontext_cpu_save(xp,tmp1,tmp2)

/* cpu-specific context restore from frame @xp, using registers tmp1 & tmp2 */
#define _xcptcontext_cpu_restore(xp,tmp1,tmp2)

/* cpu-specific cache error context save to frame @xp, using registers tmp1 & tmp2 */
#define _cxcptcontext_cpu_save(xp,tmp1,tmp2)

#endif /* ! _xcptcontext_cpu */
