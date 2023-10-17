/*
 * Copyright (c) 1998-2004 MIPS Technologies, Inc.
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
 * r7kxcpt.h: QED RM7000 xcption handling 
 */


/* Exception classes. */
#ifdef XCPCDEF
/*XCPCDEF(NAME,		NUM, 	SIG,		DESC)*/
XCPCDEF(XCPC_GENERAL,	0, 	0,		"General")
XCPCDEF(XCPC_TLBMISS,	1, 	SIGSEGV,	"TLBMiss")
XCPCDEF(XCPC_XTLBMISS,	2, 	SIGSEGV,	"XTLBMiss")
XCPCDEF(XCPC_CACHEERR,	3, 	SIGBUS,		"CacheErr")
XCPCDEF(XCPC_INTR,	4, 	SIGKILL,	"Intr")
XCPCDEF(XCPC_DEBUG,	5, 	SIGTRAP,	"Debug")
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
XCPTDEF(XCPTTRAP,	13,	SIGABRT,	"Trap",		"trap exception")
XCPTDEF(XCPTRES14,	14,	SIGKILL,	"14",		"14")
XCPTDEF(XCPTFPE,	15,	SIGFPE,		"FPE",		"floating point exception")
XCPTDEF(XCPTIWE,	16,	SIGTRAP,	"IWE",		"instruction watchpoint")
XCPTDEF(XCPTRES17,	17,	SIGKILL,	"17",		"17")
XCPTDEF(XCPTRE18,	18,	SIGFPE,		"C2E",		"coprocessor 2 exception")
XCPTDEF(XCPTRES19,	19,	SIGKILL,	"19",		"19")
XCPTDEF(XCPTRES20,	20,	SIGKILL,	"20",		"20")
XCPTDEF(XCPTRES21,	21,	SIGKILL,	"21",		"21")
XCPTDEF(XCPTRES22,	22,	SIGKILL,	"22",		"22")
XCPTDEF(XCPTDWE,	23,	SIGTRAP,	"DWE",		"data watchpoint")
XCPTDEF(XCPTRES24,	24,	SIGKILL,	"24",		"24")
XCPTDEF(XCPTRES25,	25,	SIGKILL,	"25",		"25")
XCPTDEF(XCPTRES26,	26,	SIGKILL,	"26",		"26")
XCPTDEF(XCPTRES27,	27,	SIGKILL,	"27",		"27")
XCPTDEF(XCPTRES28,	28,	SIGKILL,	"28",		"28")
XCPTDEF(XCPTRES29,	29,	SIGKILL,	"29",		"29")
XCPTDEF(XCPTCACHEERR,	30,	SIGBUS,		"CacheErr",	"cache error")
XCPTDEF(XCPTRES31,	31,	SIGKILL,	"31",		"31")
#endif /* XCPTDEF */

#ifndef NXCPT
#define NXCPT		32
#endif

/* CPU specific extensions to xcptcontext */
#ifndef _xcptcontext_cpu

/* cpu-specific context (C version) */
#define _xcptcontext_cpu \
    unsigned int	icr;

/* cpu-specific context (assembler version) */
#define _xcptcontext_cpu_asm \
    XCP_ICR:    .word	0;

/* cpu-specific cache error context (C version) */
#define _cxcptcontext_cpu \
    reg_t derr1; \
    reg_t derr2;

/* cpu-specific cache error context (assembler version) */
#define _cxcptcontext_cpu_asm \
    CXCP_DERR1:	xcpreg; \
    CXCP_DERR2:	xcpreg;

/* cpu-specific context save to frame @xp, using registers tmp1 & tmp2 */
#define _xcptcontext_cpu_save(xp,tmp1,tmp2) \
    cfc0	tmp1,C0C_ICR; \
    sw		tmp1,XCP_ICR(xp); \
    and		tmp1,SR_IMASK; \
    ctc0	tmp1,C0C_ICR

/* cpu-specific context restore from frame @xp, using registers tmp1 & tmp2 */
#define _xcptcontext_cpu_restore(xp,tmp1,tmp2) \
    lw		tmp1,XCP_ICR(xp); \
    ctc0	tmp1,C0C_ICR

/* cpu-specific cache error context save to frame @xp, using registers tmp1 & tmp2 */
#define _cxcptcontext_cpu_save(xp,tmp1,tmp2) \
    cfc0	tmp1,C0C_DERRADDR1; \
    cfc0	tmp2,C0C_DERRADDR2; \
    sr		tmp1,CXCP_DERR1(xp); \
    sr		tmp2,CXCP_DERR2(xp);

#endif /* ! _xcptcontext_cpu */
