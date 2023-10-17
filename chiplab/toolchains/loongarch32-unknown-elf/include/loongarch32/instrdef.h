/*
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
 * instrdef.h: instruction classifications
 */


#include "loongarch32/endian.h"

/* MIPS instruction generators */
#define	ITYPE_special	0
#define	ITYPE_regimm	1
#define	ITYPE_j		2
#define	ITYPE_jal	3
#define	ITYPE_beq	4
#define	ITYPE_bne	5
#define	ITYPE_blez	6
#define	ITYPE_bgtz	7
#define	ITYPE_addi	8
#define	ITYPE_addiu	9
#define	ITYPE_slti	10
#define	ITYPE_sltiu	11
#define	ITYPE_andi	12
#define	ITYPE_ori	13
#define	ITYPE_xori	14
#define	ITYPE_lui	15
#define	ITYPE_c0	16
#define	ITYPE_c1	17
#define	ITYPE_c2	18
#define	ITYPE_c3	19
#define	ITYPE_c1x	19	/* MIPS4 */
#define	ITYPE_beql	20
#define	ITYPE_bnel	21
#define	ITYPE_blezl	22
#define	ITYPE_bgtzl	23
#define	ITYPE_daddi	24	/* MIPS3 */
#define	ITYPE_daddiu	25	/* MIPS3 */
#define	ITYPE_ldl	26	/* MIPS3 */
#define	ITYPE_ldr	27	/* MIPS3 */
#define	ITYPE_special2	28	/* various uses */
#define	ITYPE_madd	28	/* R3900/R4650/CW4020 */
#define	ITYPE_addciu	28	/* Scobra */
#define	ITYPE_dbg	28	/* Vr5400 */
#define	ITYPE_jalx	29	/* MIPS16 special */
#define	ITYPE_mtd	30	/* TR4101 debug */
#define	ITYPE_mfd	31	/* TR4101 debug */
#define	ITYPE_lb	32
#define	ITYPE_lh	33
#define	ITYPE_lwl	34
#define	ITYPE_lw	35
#define	ITYPE_lbu	36
#define	ITYPE_lhu	37
#define	ITYPE_lwr	38
#define	ITYPE_lwu	39	/* MIPS3 */
#define	ITYPE_sb	40
#define	ITYPE_sh	41
#define	ITYPE_swl	42
#define	ITYPE_sw	43
#define	ITYPE_sdl	44	/* MIPS3 */
#define	ITYPE_sdr	45	/* MIPS3 */
#define	ITYPE_swr	46
#define	ITYPE_cache	47
#define	ITYPE_ll	48	/* MIPS2 */
#define	ITYPE_lwc1	49
#define	ITYPE_lwc2	50
#define	ITYPE_lwc3	51
#define	ITYPE_pref	51	/* MIPS4 */
#define	ITYPE_lld	52	/* MIPS3 */
#define	ITYPE_ldc1	53	/* MIPS2 */
#define	ITYPE_ldc2	54	/* MIPS3 */
#define	ITYPE_ld	55	/* MIPS3 */
#define	ITYPE_sc	56	/* MIPS3 */
#define	ITYPE_swc1	57
#define	ITYPE_swc2	58
#define	ITYPE_swc3	59
#define	ITYPE_scd	60	/* MIPS3 */
#define	ITYPE_sdc1	61	/* MIPS2 */
#define	ITYPE_sdc2	62	/* MIPS3 */
#define	ITYPE_sd	63	/* MIPS3 */

#define MTYPE_madd	0	/* R3900,R4650 */
#define MTYPE_maddu	1	/* R3900,R4650 */
#define MTYPE_mult3	2	/* R4650 */
#define MTYPE_msub	4	/* Cronus/CW4020 */
#define MTYPE_msubu	5	/* Cronus/CW4020 */
#define MTYPE_clz	32	/* Cronus */
#define MTYPE_clo	33	/* Cronus */
#define MTYPE_sdbbp	63	/* JTAG */

#define SPEC2_lxs	8

#define LXS_lwxs	2

#define	RRTYPE_sll	0
#define	RRTYPE_selsr	1	/* Scobra */
#define	RRTYPE_movci	1	/* MIPS4 (tests fpu cond code) */
#define	RRTYPE_srl	2
#define	RRTYPE_sra	3
#define	RRTYPE_sllv	4
#define	RRTYPE_selsl	5	/* Scobra */
#define	RRTYPE_srlv	6
#define	RRTYPE_srav	7
#define	RRTYPE_jr	8
#define	RRTYPE_jalr	9
#define	RRTYPE_ffs	10	/* Scobra */
#define	RRTYPE_movz	10	/* MIPS4 */
#define	RRTYPE_ffc	11	/* Scobra */
#define	RRTYPE_movn	11	/* MIPS4 */
#define	RRTYPE_syscall	12
#define	RRTYPE_break	13
#define	RRTYPE_14	14
#define	RRTYPE_sync	15
#define	RRTYPE_mfhi	16
#define	RRTYPE_mthi	17
#define	RRTYPE_mflo	18
#define	RRTYPE_mtlo	19
#define	RRTYPE_dsllv	20	/* MIPS3 */
#define	RRTYPE_21	21
#define	RRTYPE_dsrlv	22	/* MIPS3 */
#define	RRTYPE_dsrav	23	/* MIPS3 */
#define	RRTYPE_mult	24
#define	RRTYPE_multu	25
#define	RRTYPE_divd	26
#define	RRTYPE_divdu	27
#define	RRTYPE_dmult	28	/* MIPS3 */
#define RRTYPE_madd_cw	28	/* LSI CW40xx */
#define	RRTYPE_dmultu	29	/* MIPS3 */
#define RRTYPE_maddu_cw	29	/* LSI CW40xx */
#define	RRTYPE_ddivd	30	/* MIPS3 */
#define RRTYPE_msub_cw	30	/* LSI CW40xx */
#define	RRTYPE_ddivdu	31	/* MIPS3 */
#define RRTYPE_msubu_cw	31	/* LSI CW40xx */
#define	RRTYPE_add	32
#define	RRTYPE_addu	33
#define	RRTYPE_sub	34
#define	RRTYPE_subu	35
#define	RRTYPE_and	36
#define	RRTYPE_or	37
#define	RRTYPE_xor	38
#define	RRTYPE_nor	39
#define	RRTYPE_min	40	/* Scobra */
#define	RRTYPE_max	41	/* Scobra */
#define RRTYPE_madd16	40	/* R4100 */
#define RRTYPE_dmadd16	41	/* R4100 */
#define	RRTYPE_slt	42
#define	RRTYPE_sltu	43
#define	RRTYPE_dadd	44	/* MIPS3 */
#define	RRTYPE_daddu	45	/* MIPS3 */
#define	RRTYPE_dsub	46	/* MIPS3 */
#define	RRTYPE_dsubu	47	/* MIPS3 */
#define	RRTYPE_tge	48	/* MIPS2 */
#define	RRTYPE_tgeu	49	/* MIPS2 */
#define	RRTYPE_tlt	50	/* MIPS2 */
#define	RRTYPE_tltu	51	/* MIPS2 */
#define	RRTYPE_teq	52	/* MIPS2 */
#define	RRTYPE_53	53
#define	RRTYPE_tne	54	/* MIPS2 */
#define	RRTYPE_55	55
#define	RRTYPE_dsll	56	/* MIPS3 */
#define	RRTYPE_57	57
#define	RRTYPE_dsrl	58	/* MIPS3 */
#define	RRTYPE_dsra	59	/* MIPS3 */
#define	RRTYPE_dsll32	60	/* MIPS3 */
#define	RRTYPE_61	61
#define	RRTYPE_dsrl32	62	/* MIPS3 */
#define	RRTYPE_dsra32	63	/* MIPS3 */

#define	RITYPE_bltz	0
#define	RITYPE_bgez	1
#define	RITYPE_bltzl	2	/* MIPS2 */
#define	RITYPE_bgezl	3	/* MIPS2 */
#define	RITYPE_4	4
#define	RITYPE_5	5
#define	RITYPE_6	6
#define	RITYPE_7	7
#define	RITYPE_tgei	8	/* MIPS2 */
#define	RITYPE_tgeiu	9	/* MIPS2 */
#define	RITYPE_tlti	10	/* MIPS2 */
#define	RITYPE_tltiu	11	/* MIPS2 */
#define	RITYPE_teqi	12	/* MIPS2 */
#define	RITYPE_13	13
#define	RITYPE_tnei	14	/* MIPS2 */
#define	RITYPE_15	15
#define	RITYPE_bltzal	16
#define	RITYPE_bgezal	17
#define	RITYPE_bltzall	18	/* MIPS2 */
#define	RITYPE_bgezall	19	/* MIPS2 */
#define	RITYPE_20	20
#define	RITYPE_21	21
#define	RITYPE_22	22
#define	RITYPE_23	23
#define	RITYPE_24	24
#define	RITYPE_25	25
#define	RITYPE_26	26
#define	RITYPE_27	27
#define	RITYPE_28	28
#define	RITYPE_29	29
#define	RITYPE_30	30
#define	RITYPE_31	31

#define COPZRS_mf	0
#define COPZRS_dmf	1	/* MIPS3 */
#define COPZRS_cf	2
#define COPZRS_mfh	3	/* MIPS32r2 */
#define COPZRS_mt	4
#define COPZRS_dmt	5	/* MIPS3 */
#define COPZRS_ct	6
#define COPZRS_mth	7	/* MIPS32r2 */
#define COPZRS_bc	8

#define COPZRT_BCF	0
#define COPZRT_BCT	1
#define COPZRT_BCFL	2	/* MIPS2 */
#define COPZRT_BCTL	3	/* MIPS2 */

#define COP0_tlbr	1
#define COP0_tlbwi	2
#define COP0_tlbwr	6
#define COP0_tlbp	8
#define COP0_rfe	16	/* MIPS1 */
#define COP0_eret	24
#define COP0_dret	31	/* R3900/JTAG */
#define COP0_waiti	32	/* Scobra */
#define COP0_standby	33	/* R4100 */
#define COP0_suspend	34	/* R4100 */
#define COP0_hibernate	35	/* R4100 */

#define	COP1_add	0
#define	COP1_sub	1
#define	COP1_mul	2
#define	COP1_div	3
#define	COP1_sqrt	4	/* MIPS2 */
#define	COP1_abs	5
#define	COP1_mov	6
#define	COP1_neg	7
#define	COP1_roundl	8	/* MIPS3 */
#define	COP1_truncl	9	/* MIPS3 */
#define	COP1_ceill	10	/* MIPS3 */
#define	COP1_floorl	11	/* MIPS3 */
#define	COP1_round	12	/* MIPS2 */
#define	COP1_trunc	13	/* MIPS2 */
#define	COP1_ceil	14	/* MIPS2 */
#define	COP1_floor	15	/* MIPS2 */
#define	COP1_16		16
#define	COP1_movcf	17	/* MIPS4 (tests fpu cond code) */
#define	COP1_movz	18	/* MIPS4 (tests integer reg) */
#define	COP1_movn	19	/* MIPS4 (tests integer reg) */
#define	COP1_20		20
#define	COP1_recip	21	/* MIPS4 */
#define	COP1_rsqrt	22	/* MIPS4 */
#define	COP1_23		23
#define	COP1_24		24
#define	COP1_25		25
#define	COP1_26		26
#define	COP1_27		27
#define	COP1_28		28
#define	COP1_29		29
#define	COP1_30		30
#define	COP1_31		31
#define	COP1_cvts	32
#define	COP1_cvtd	33
#define	COP1_34		34
#define	COP1_35		35
#define	COP1_cvtw	36
#define	COP1_cvtl	37	/* MIPS3 */
#define	COP1_cvtps	38	/* MIPS5 */
#define	COP1_39		39
#define	COP1_cvts_pu	40	/* MIPS5 */
#define	COP1_41		41
#define	COP1_42		42
#define	COP1_43		43
#define	COP1_pll	44	/* MIPS5 */
#define	COP1_plu	45	/* MIPS5 */
#define	COP1_pul	46	/* MIPS5 */
#define	COP1_puu	47	/* MIPS5 */
#define	COP1_cmp_f	48
#define	COP1_cmp_un	49
#define	COP1_cmp_eq	50
#define	COP1_cmp_ueq	51
#define	COP1_cmp_olt	52
#define	COP1_cmp_ult	53
#define	COP1_cmp_ole	54
#define	COP1_cmp_ule	55
#define	COP1_cmp_sf	56
#define	COP1_cmp_ngle	57
#define	COP1_cmp_seq	58
#define	COP1_cmp_ngl	59
#define	COP1_cmp_lt	60
#define	COP1_cmp_nge	61
#define	COP1_cmp_le	62
#define	COP1_cmp_ngt	63

/* COMP1X - all MIPS4 */
#define	COP1X_lxc1	0x00
#define	COP1X_sxc1	0x01
#define	COP1X_alnv_ps	0x03	/* MIPS5 */
#define	COP1X_madd	0x04
#define	COP1X_msub	0x05
#define	COP1X_nmadd	0x06
#define	COP1X_nmsub	0x07

#define CP1SFMT 	0
#define CP1DFMT 	1
#define CP1WFMT		4
#define CP1LFMT		5
#define CP1ULFMT	5	/* unaligned access (MIPS5) */
#define CP1PSFMT	6


#if BYTE_ORDER == LITTLE_ENDIAN
union  mipsn_instr {
    struct rrtype {
	unsigned	funct:6;
	unsigned	shamt:5;
	unsigned	rd:5;		/* sometimes written */
	unsigned	rt:5;
	unsigned	rs:5;
	unsigned	op:6;		/* == 0 */
    } rrtype;
    struct itype {
	int		imm:16;
	unsigned	rt:5;		/* sometime written */
	unsigned	rs:5;
	unsigned	op:6;
    } itype;
    struct utype {		/* itype without sign extend */
	unsigned	imm:16;
	unsigned	rt:5;		/* sometime written */
	unsigned	rs:5;
	unsigned	op:6;
    } utype;
    struct jtype {
	unsigned	target:26;
	unsigned	op:6;
    } jtype;
    struct cp1type {
	unsigned	funct:6;
	unsigned	fd:5;
	unsigned	fs:5;
	unsigned	ft:5;
	unsigned	fmt:5;
	unsigned 	op:6;	/* == COP1 	*/
    } cp1type;
    struct cp1xtype {
	unsigned	fmt:3;
	unsigned	funct:3;
	unsigned	fd:5;
	unsigned	fs:5;
	unsigned	ft:5;
	unsigned	fr:5;
	unsigned 	op:6;	/* == COP1X 	*/
    } cp1xtype;
    struct mdmxtype {
	unsigned	funct:6;
	unsigned	vd:5;
	unsigned	vs:5;
	unsigned	vt:5;
	unsigned	fmtsel:5;
	unsigned 	op:6;	/* == COP2 	*/
    } mdmxtype;
    struct ttype {		/* Trap type */
	unsigned	funct:6;	/* == BREAK */
	unsigned	tcode:10;	/* trap code */
	unsigned	bcode:10;	/* break code (should be more) */
	unsigned	op:6;		/* == 0 */
    } ttype;
    struct cptype {
	unsigned	funct:25;
	unsigned	one:1;
	unsigned	op:6;
    } cptype;
    unsigned		value;
};
#elif BYTE_ORDER == BIG_ENDIAN
union  mipsn_instr {
    struct rrtype {
	unsigned	op:6;		/* == 0 */
	unsigned	rs:5;
	unsigned	rt:5;
	unsigned	rd:5;		/* sometimes written */
	unsigned	shamt:5;
	unsigned	funct:6;
    } rrtype;
    struct itype {
	unsigned	op:6;
	unsigned	rs:5;
	unsigned	rt:5;		/* sometime written */
	int		imm:16;
    } itype;
    struct utype {		/* itype without sign extend */
	unsigned	op:6;
	unsigned	rs:5;
	unsigned	rt:5;		/* sometime written */
	unsigned	imm:16;
    } utype;
    struct jtype {
	unsigned	op:6;
	unsigned	target:26;
    } jtype;
    struct cp1type {
	unsigned 	op:6;	/* == COP1 	*/
	unsigned	fmt:5;
	unsigned	ft:5;
	unsigned	fs:5;
	unsigned	fd:5;
	unsigned	funct:6;
    } cp1type;
    struct cp1xtype {
	unsigned 	op:6;	/* == COP1X 	*/
	unsigned	fr:5;
	unsigned	ft:5;
	unsigned	fs:5;
	unsigned	fd:5;
	unsigned	funct:3;
	unsigned	fmt:3;
    } cp1xtype;
    struct mdmxtype {
	unsigned 	op:6;	/* == COP2 	*/
	unsigned	fmtsel:5;
	unsigned	vt:5;
	unsigned	vs:5;
	unsigned	vd:5;
	unsigned	funct:6;
    } mdmxtype;
    struct ttype {		/* Trap type */
	unsigned	op:6;		/* == 0 */
	unsigned	bcode:10;	/* break code (should be more) */
	unsigned	tcode:10;	/* trap code */
	unsigned	funct:6;	/* == BREAK */
    } ttype;
    struct cptype {
	unsigned	op:6;
	unsigned	one:1;
	unsigned	funct:25;
    } cptype;
    unsigned		value;
};
#endif

/* compat defines */
#define mips_instr	mipsn_instr
#define r3k_instr	mipsn_instr
#define r4k_instr	mipsn_instr
#define rtype		rrtype
