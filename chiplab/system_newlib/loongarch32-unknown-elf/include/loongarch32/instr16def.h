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
 * instr16def.h: instruction classifications
 */


#include "loongarch32/endian.h"

/* MIPS instruction generators */
#define	ITYPE16_addiusp	0
#define	ITYPE16_addiupc	1
#define	ITYPE16_b	2
#define	ITYPE16_jal	3
#define	ITYPE16_beqz	4
#define	ITYPE16_bnez	5
#define	ITYPE16_shift	6
#define	ITYPE16_ld	7
#define	ITYPE16_rria	8
#define	ITYPE16_addiu8	9
#define	ITYPE16_slti	10
#define	ITYPE16_sltiu	11
#define	ITYPE16_i8	12
#define	ITYPE16_li	13
#define	ITYPE16_cmpi	14
#define	ITYPE16_sd	15
#define	ITYPE16_lb	16
#define	ITYPE16_lh	17
#define	ITYPE16_lwsp	18
#define	ITYPE16_lw	19
#define	ITYPE16_lbu	20
#define	ITYPE16_lhu	21
#define	ITYPE16_lwpc	22
#define	ITYPE16_lwu	23
#define	ITYPE16_sb	24
#define	ITYPE16_sh	25
#define	ITYPE16_swsp	26
#define	ITYPE16_sw	27
#define	ITYPE16_rrr	28
#define	ITYPE16_rr	29
#define	ITYPE16_extend	30
#define	ITYPE16_i64	31

#define RRTYPE16_jr	0
#define RRTYPE16_1	1
#define RRTYPE16_slt	2
#define RRTYPE16_sltu	3
#define RRTYPE16_sllv	4
#define RRTYPE16_break	5
#define RRTYPE16_srlv	6
#define RRTYPE16_srav	7
#define RRTYPE16_dsrl	8
#define RRTYPE16_entry	9	/* currently reserved */
#define RRTYPE16_cmp	10
#define RRTYPE16_neg	11
#define RRTYPE16_and	12
#define RRTYPE16_or	13
#define RRTYPE16_xor	14
#define RRTYPE16_not	15
#define RRTYPE16_mfhi	16
#define RRTYPE16_17	17
#define RRTYPE16_mflo	18
#define RRTYPE16_dsra	19
#define RRTYPE16_dsllv	20
#define RRTYPE16_21	21
#define RRTYPE16_dsrlv	22
#define RRTYPE16_dsrav	23
#define RRTYPE16_mult	24
#define RRTYPE16_multu	25
#define RRTYPE16_div	26
#define RRTYPE16_divu	27
#define RRTYPE16_dmult	28
#define RRTYPE16_dmultu	29
#define RRTYPE16_ddiv	30
#define RRTYPE16_ddivu	31

#define RRRTYPE16_daddu	0
#define RRRTYPE16_addu	1
#define RRRTYPE16_dsubu	2
#define RRRTYPE16_subu	3

#define RRIATYPE16_addiu  0
#define RRIATYPE16_daddiu 1

#define SHIFTTYPE16_sll  0
#define SHIFTTYPE16_dsll 1
#define SHIFTTYPE16_srl	 2
#define SHIFTTYPE16_sra	 3

#define I8TYPE16_bteqz	0
#define I8TYPE16_btnez	1
#define I8TYPE16_swrasp	2
#define I8TYPE16_adjsp	3
#define I8TYPE16_svrs	4
#define I8TYPE16_mov32r	5
#define I8TYPE16_6	6
#define I8TYPE16_movr32	7

#define I64TYPE16_ldsp	   0
#define I64TYPE16_sdsp	   1
#define I64TYPE16_sdrasp   2
#define I64TYPE16_dadjsp   3
#define I64TYPE16_ldpc	   4
#define I64TYPE16_daddiu   5
#define I64TYPE16_daddiupc 6
#define I64TYPE16_daddiusp 7

#if BYTE_ORDER == LITTLE_ENDIAN
union  mips16_instr {
    struct i16itype {
	int		imm:11;
	unsigned	op:5;
    } itype;
    struct i16ritype {
	int		imm:8;
	unsigned	rx:3;
	unsigned	op:5;
    } ritype;
    struct i16rrtype {
	unsigned	funct:5;
	unsigned	ry:3;
	unsigned	rx:3;
	unsigned	op:5;	/* op == INST16_RR */
    } rrtype;
    struct i16rritype {
	int		imm:5;
	unsigned	ry:3;
	unsigned	rx:3;
	unsigned	op:5;
    } rritype;
    struct i16rrrtype {
	unsigned	funct:2;
	unsigned	rz:3;
	unsigned	ry:3;
	unsigned	rx:3;
	unsigned	op:5;	/* == INST16_RRR */
    } rrrtype;
    struct i16rriatype {
	int		imm:4;
	unsigned	funct:1;
	unsigned	ry:3;
	unsigned	rx:3;
	unsigned	op:5;	/* == INST16_RRIA */
    } rriatype;
    struct i16stype {
	unsigned	funct:2;
	unsigned	sa:3;
	unsigned	ry:3;
	unsigned	rx:3;
	unsigned	op:5;	/* == INST16_SHIFT */
    } stype;
    struct i16i8type {
	int		imm:8;
	unsigned	funct:3;
	unsigned	op:5;	/* == INST16_I8 */
    } i8type;
    struct i16i8r32type {
	unsigned	r32:5;
	unsigned	ry:3;
	unsigned	funct:3;
	unsigned	op:5;	/* == INST16_I8 */
    } i8r32type;
    struct i16i8r32rtype {
	unsigned	rz:3;
	unsigned	r32:5;
	unsigned	funct:3;
	unsigned	i8:5;	/* == INST16_I8 */
    } i8r32rtype;
    struct i16i64type {
	int		imm:8;
	unsigned	funct:3;
	unsigned	op:5;	/* == INST16_64 */
    } i64type;
    struct i16ri64type {
	int		imm:5;
	unsigned	ry:3;
	unsigned	funct:3;
	unsigned	op:5;	/* == INST16_64 */
    } ri64type;
    struct i16exttype {
	unsigned	imm:11;
	unsigned	op:5;	/* == INST16_EXTEND */
    } exttype;
    struct i16extitype {
	unsigned 	imm:5;
	unsigned	ry:3;
	unsigned	rx:3;
	unsigned	op:5;
    } extitype;
    struct i16extrriatype {
	unsigned 	imm:4;
	unsigned 	funct:1;
	unsigned	ry:3;
	unsigned	rx:3;
	unsigned	op:5;
    } extrriatype;
    unsigned short	value;
};
#elif BYTE_ORDER == BIG_ENDIAN
union  mips16_instr {
    struct i16itype {
	unsigned	op:5;
	int		imm:11;
    } itype;
    struct i16ritype {
	unsigned	op:5;
	unsigned	rx:3;
	int		imm:8;
    } ritype;
    struct i16rrtype {
	unsigned	op:5;	/* op == INST16_RR */
	unsigned	rx:3;
	unsigned	ry:3;
	unsigned	funct:5;
    } rrtype;
    struct i16rritype {
	unsigned	op:5;
	unsigned	rx:3;
	unsigned	ry:3;
	int		imm:5;
    } rritype;
    struct i16rrrtype {
	unsigned	op:5;	/* == INST16_RRR */
	unsigned	rx:3;
	unsigned	ry:3;
	unsigned	rz:3;
	unsigned	funct:2;
    } rrrtype;
    struct i16rriatype {
	unsigned	op:5;	/* == INST16_RRIA */
	unsigned	rx:3;
	unsigned	ry:3;
	unsigned	funct:1;
	int		imm:4;
    } rriatype;
    struct i16stype {
	unsigned	op:5;	/* == INST16_SHIFT */
	unsigned	rx:3;
	unsigned	ry:3;
	unsigned	sa:3;
	unsigned	funct:2;
    } stype;
    struct i16i8type {
	unsigned	op:5;	/* == INST16_I8 */
	unsigned	funct:3;
	int		imm:8;
    } i8type;
    struct i16i8r32type {
	unsigned	op:5;	/* == INST16_I8 */
	unsigned	funct:3;
	unsigned	ry:3;
	unsigned	r32:5;
    } i8r32type;
    struct i16i832rtype {
	unsigned	i8:5;	/* == INST16_I8 */
	unsigned	funct:3;
	unsigned	r32:5;
	unsigned	rz:3;
    } i832rtype;
    struct i16i64type {
	unsigned	op:5;	/* == INST16_64 */
	unsigned	funct:3;
	int		imm:8;
    } i64type;
    struct i16ri64type {
	unsigned	op:5;	/* == INST16_64 */
	unsigned	funct:3;
	unsigned	ry:3;
	int		imm:5;
    } ri64type;
    struct i16jaltype {
	unsigned	op:5;	/* == INST16_JAL */
	unsigned	x:1;
	unsigned	imm20_16;		
	int		imm25_21;
    } jaltype;
    struct i16exttype {
	unsigned	op:5;	/* == INST16_EXTEND */
	unsigned	imm:11;		
    } exttype;
    struct i16extitype {
	unsigned	op:5;
	unsigned	rx:3;
	unsigned	ry:3;
	unsigned 	imm:5;
    } extitype;
    struct i16extrriatype {
	unsigned	op:5;
	unsigned	rx:3;
	unsigned	ry:3;
	unsigned 	funct:1;
	unsigned 	imm:4;
    } extrriatype;
    unsigned short	value;
};
#endif

