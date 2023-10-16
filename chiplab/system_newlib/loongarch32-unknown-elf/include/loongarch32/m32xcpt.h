/*
 * Copyright (c) 1999-2006 MIPS Technologies, Inc.
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
 * m32xcpt.h : MIPS32 / MIPS64 exceptions
 */

/* Exception classes. */
#ifdef XCPCDEF
/*XCPCDEF(NAME,		NUM, 	SIG,		DESC)*/
#define M32XCPC			/* required for gcc-2.96! */
XCPCDEF(XCPC_GENERAL,	0, 	0,		"General")
# if ! #cpu(m4k)
XCPCDEF(XCPC_TLBMISS,	1, 	SIGSEGV,	"TLBMiss")
XCPCDEF(XCPC_XTLBMISS,	2, 	SIGSEGV,	"XTLBMiss")
XCPCDEF(XCPC_CACHEERR,	3, 	SIGBUS,		"CacheErr")
# endif
XCPCDEF(XCPC_DEBUG,	4, 	SIGTRAP,	"Debug")
XCPCDEF(XCPC_INTR,	5, 	SIGKILL,	"Intr")
#endif /* XCPCDEF */

/* Exception codes. */
#ifdef XCPTDEF
/*XCPTDEF(NAME,		NUM, 	SIG,		BRIEF,		DESC)*/
#define M32XCPT			/* required for gcc-2.96! */
XCPTDEF(XCPTINTR,  	0,	SIGKILL,	"Intr",		"interrupt")
# if #cpu(m4k)
XCPTDEF(XCPTRES1,	1,	SIGKILL,	"1",		"1")
XCPTDEF(XCPTRES2,	2,	SIGKILL,	"2",		"2")
XCPTDEF(XCPTRES3,	3,	SIGKILL,	"3",		"3")
# else
XCPTDEF(XCPTMOD,	1,	SIGSEGV,	"TLBMod",	"tlb modification")
XCPTDEF(XCPTTLBL,	2,	SIGSEGV,	"TLBL",		"tlb fault on read")
XCPTDEF(XCPTTLBS,	3,	SIGSEGV,	"TLBS",		"tlb fault on write")
# endif
XCPTDEF(XCPTADEL,	4,	SIGBUS,		"AdEL",		"address error on read")
XCPTDEF(XCPTADES,	5,	SIGBUS,		"AdES",		"address error on write")
XCPTDEF(XCPTIBE,	6,	SIGBUS,		"IBE",		"instruction bus error")
XCPTDEF(XCPTDBE,	7,	SIGBUS,		"DBE",		"data bus error")
XCPTDEF(XCPTSYS,	8,	SIGSYS,		"Sys",		"syscall instruction")
XCPTDEF(XCPTBP,		9,	SIGABRT,	"Bp",		"break instruction")
XCPTDEF(XCPTRI,		10,	SIGILL,		"RI",		"reserved instruction")
XCPTDEF(XCPTCPU,	11,	SIGILL,		"CpU",		"coprocessor unusable")
XCPTDEF(XCPTOVF,	12,	SIGFPE, 	"Ovf",		"arithmetic overflow")
XCPTDEF(XCPTTRAP,	13,	SIGABRT,	"Trap",		"trap exception")
XCPTDEF(XCPTRES14,	14,	SIGKILL,	"14",		"14")
XCPTDEF(XCPTFPE,	15,	SIGFPE,		"FPE",		"floating point exception")
XCPTDEF(XCPTIS1,	16,	SIGKILL,	"IS1",		"implementation-specific 1")
#ifdef EXC_CEU
XCPTDEF(XCPTCEU,	17,	SIGILL,		"CEU",		"coreextend unusable")
#else
XCPTDEF(XCPTIS2,	17,	SIGKILL,	"IS2",		"implementation-specific 2")
#endif
XCPTDEF(XCPTC2E,	18,	SIGFPE,		"C2E",		"coprocessor 2 exception")
XCPTDEF(XCPTRES19,	19,	SIGKILL,	"19",		"19")
XCPTDEF(XCPTRES20,	20,	SIGKILL,	"20",		"20")
XCPTDEF(XCPTRES21,	21,	SIGKILL,	"21",		"21")
XCPTDEF(XCPTMDMX,	22,	SIGILL,		"MDMX",		"mdmx unusable")
XCPTDEF(XCPTWATCH,	23,	SIGTRAP,	"Watch",	"watchpoint")
XCPTDEF(XCPTMCHECK,	24,	SIGBUS,		"MCheck",	"machine check")
XCPTDEF(XCPTTHREAD,	25,	SIGKILL,	"Thread",	"thread")
XCPTDEF(XCPTDSPU,	26,	SIGILL,		"DSPU",		"dsp unusable")
XCPTDEF(XCPTRES27,	27,	SIGKILL,	"27",		"27")
XCPTDEF(XCPTRES28,	28,	SIGKILL,	"28",		"28")
XCPTDEF(XCPTRES29,	29,	SIGKILL,	"29",		"29")
# if #cpu(m4k)
XCPTDEF(XCPTRES30,	30,	SIGKILL,	"30",		"30")
# else
XCPTDEF(XCPTCACHEERR,	30,	SIGBUS,		"CacheErr",	"cache error")
# endif
XCPTDEF(XCPTRES31,	31,	SIGKILL,	"31",		"31")
#endif /* XCPTDEF */

#define NXCPT		32

/* CPU specific extensions to xcptcontext */
#ifndef _xcptcontext_cpu

/* cpu-specific context (C version) */
#define _xcptcontext_cpu \
    unsigned int srsctl;

/* cpu-specific context (assembler version) */
#define _xcptcontext_cpu_asm \
    XCP_SRSCTL:    .word	0;

/* cpu-specific context save to frame @xp, using registers tmp1 & tmp2 */
#define _xcptcontext_cpu_save(xp,tmp1,tmp2)

/* cpu-specific context restore from frame @xp, using registers tmp1 & tmp2 */
#define _xcptcontext_cpu_restore(xp,tmp1,tmp2)

/* cpu-specific cache error context save to frame @xp, using registers tmp1 & tmp2 */
#define _cxcptcontext_cpu_save(xp,tmp1,tmp2)

#endif /* ! _xcptcontext_cpu */
