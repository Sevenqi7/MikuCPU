/* Generated automatically by the program `genflags'
   from the machine description file `md'.  */

#ifndef GCC_INSN_FLAGS_H
#define GCC_INSN_FLAGS_H

#define HAVE_trap 1
#define HAVE_addsf3 (TARGET_HARD_FLOAT)
#define HAVE_adddf3 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_addsi3 1
#define HAVE_adddi3 (TARGET_64BIT)
#define HAVE_subsf3 (TARGET_HARD_FLOAT)
#define HAVE_subdf3 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_subsi3 1
#define HAVE_subdi3 (TARGET_64BIT)
#define HAVE_mulsf3 (TARGET_HARD_FLOAT)
#define HAVE_muldf3 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_mulsi3 1
#define HAVE_muldi3 (TARGET_64BIT)
#define HAVE_mulsidi3_64bit (TARGET_64BIT)
#define HAVE_muldi3_highpart (TARGET_64BIT)
#define HAVE_umuldi3_highpart (TARGET_64BIT)
#define HAVE_mulsi3_highpart 1
#define HAVE_umulsi3_highpart 1
#define HAVE_copysignsf3 (TARGET_HARD_FLOAT)
#define HAVE_copysigndf3 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_divdi3_fake 1
#define HAVE_udivdi3_fake 1
#define HAVE_moddi3_fake 1
#define HAVE_umoddi3_fake 1
#define HAVE_fmasf4 (TARGET_HARD_FLOAT)
#define HAVE_fmadf4 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_fmssf4 (TARGET_HARD_FLOAT)
#define HAVE_fmsdf4 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_fnmasf4 ((TARGET_HARD_FLOAT && !HONOR_SIGNED_ZEROS (SFmode)) && (TARGET_HARD_FLOAT))
#define HAVE_fnmadf4 ((TARGET_HARD_FLOAT && !HONOR_SIGNED_ZEROS (DFmode)) && (TARGET_DOUBLE_FLOAT))
#define HAVE_fnmssf4 ((TARGET_HARD_FLOAT && !HONOR_SIGNED_ZEROS (SFmode)) && (TARGET_HARD_FLOAT))
#define HAVE_fnmsdf4 ((TARGET_HARD_FLOAT && !HONOR_SIGNED_ZEROS (DFmode)) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sqrtsf2 (TARGET_HARD_FLOAT)
#define HAVE_sqrtdf2 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_abssf2 (TARGET_HARD_FLOAT)
#define HAVE_absdf2 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_clzsi2 (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_clzdi2 ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_64BIT))
#define HAVE_ctzsi2 (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_ctzdi2 ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_64BIT))
#define HAVE_smaxsf3 (TARGET_HARD_FLOAT)
#define HAVE_smaxdf3 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sminsf3 (TARGET_HARD_FLOAT)
#define HAVE_smindf3 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_smaxasf3 (TARGET_HARD_FLOAT)
#define HAVE_smaxadf3 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sminasf3 (TARGET_HARD_FLOAT)
#define HAVE_sminadf3 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_negsi2 1
#define HAVE_negdi2 (TARGET_64BIT)
#define HAVE_one_cmplsi2 1
#define HAVE_one_cmpldi2 (TARGET_64BIT)
#define HAVE_negsf2 (TARGET_HARD_FLOAT)
#define HAVE_negdf2 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_andsi3 1
#define HAVE_iorsi3 1
#define HAVE_xorsi3 1
#define HAVE_anddi3 (TARGET_64BIT)
#define HAVE_iordi3 (TARGET_64BIT)
#define HAVE_xordi3 (TARGET_64BIT)
#define HAVE_andsi3_extended (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_anddi3_extended ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_64BIT))
#define HAVE_andnsi (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_iornsi (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_andndi ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_64BIT))
#define HAVE_iorndi ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_64BIT))
#define HAVE_truncdiqi2 (TARGET_64BIT)
#define HAVE_truncdihi2 (TARGET_64BIT)
#define HAVE_truncdisi2 (TARGET_64BIT)
#define HAVE_truncdfsf2 (TARGET_DOUBLE_FLOAT)
#define HAVE_extendsidi2 (TARGET_64BIT)
#define HAVE_extendsfdf2 (TARGET_DOUBLE_FLOAT)
#define HAVE_fix_truncsfsi2 (TARGET_HARD_FLOAT)
#define HAVE_fix_truncsfdi2 ((TARGET_HARD_FLOAT) && ((TARGET_64BIT) && (TARGET_HARD_FLOAT)))
#define HAVE_fix_truncdfsi2 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_fix_truncdfdi2 ((TARGET_HARD_FLOAT) && ((TARGET_64BIT) && (TARGET_DOUBLE_FLOAT)))
#define HAVE_floatsidf2 (TARGET_DOUBLE_FLOAT)
#define HAVE_floatdidf2 (TARGET_DOUBLE_FLOAT && (TARGET_32BIT_STANDARD || TARGET_64BIT))
#define HAVE_floatsisf2 (TARGET_HARD_FLOAT)
#define HAVE_floatdisf2 (TARGET_DOUBLE_FLOAT && (TARGET_32BIT_STANDARD || TARGET_64BIT))
#define HAVE_movfcc (TARGET_HARD_FLOAT)
#define HAVE_lu32i_d (TARGET_64BIT)
#define HAVE_lu52i_d (TARGET_64BIT)
#define HAVE_frint_s (TARGET_HARD_FLOAT)
#define HAVE_frint_d ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_load_lowdf ((TARGET_HARD_FLOAT) && (TARGET_32BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_load_lowdi ((TARGET_HARD_FLOAT) && (TARGET_32BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_load_lowtf ((TARGET_HARD_FLOAT) && (TARGET_64BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_load_highdf ((TARGET_HARD_FLOAT) && (TARGET_32BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_load_highdi ((TARGET_HARD_FLOAT) && (TARGET_32BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_load_hightf ((TARGET_HARD_FLOAT) && (TARGET_64BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_store_worddf ((TARGET_HARD_FLOAT) && (TARGET_32BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_store_worddi ((TARGET_HARD_FLOAT) && (TARGET_32BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_store_wordtf ((TARGET_HARD_FLOAT) && (TARGET_64BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_got_load_tls_gdsi (Pmode == SImode)
#define HAVE_got_load_tls_gddi (Pmode == DImode)
#define HAVE_got_load_tls_ldsi (Pmode == SImode)
#define HAVE_got_load_tls_lddi (Pmode == DImode)
#define HAVE_got_load_tls_lesi (Pmode == SImode)
#define HAVE_got_load_tls_ledi (Pmode == DImode)
#define HAVE_got_load_tls_iesi (Pmode == SImode)
#define HAVE_got_load_tls_iedi (Pmode == DImode)
#define HAVE_movgr2frhdf ((TARGET_DOUBLE_FLOAT) && (TARGET_32BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_movgr2frhdi ((TARGET_DOUBLE_FLOAT) && (TARGET_32BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_movgr2frhtf ((TARGET_DOUBLE_FLOAT) && (TARGET_64BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_movsgr2frsf (TARGET_HARD_FLOAT)
#define HAVE_movsgr2frdf ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_movdgr2frsf ((TARGET_HARD_FLOAT && (TARGET_32BIT_STANDARD || TARGET_64BIT)) && (TARGET_HARD_FLOAT))
#define HAVE_movdgr2frdf ((TARGET_HARD_FLOAT && (TARGET_32BIT_STANDARD || TARGET_64BIT)) && (TARGET_DOUBLE_FLOAT))
#define HAVE_movfrh2grdf ((TARGET_DOUBLE_FLOAT) && (TARGET_32BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_movfrh2grdi ((TARGET_DOUBLE_FLOAT) && (TARGET_32BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_movfrh2grtf ((TARGET_DOUBLE_FLOAT) && (TARGET_64BIT && TARGET_DOUBLE_FLOAT))
#define HAVE_movsfr2grsi (TARGET_HARD_FLOAT)
#define HAVE_movsfr2grdi ((TARGET_HARD_FLOAT) && (TARGET_64BIT))
#define HAVE_movdfr2grsi (TARGET_DOUBLE_FLOAT && (TARGET_32BIT_STANDARD || TARGET_64BIT))
#define HAVE_movdfr2grdi ((TARGET_DOUBLE_FLOAT && (TARGET_32BIT_STANDARD || TARGET_64BIT)) && (TARGET_64BIT))
#define HAVE_movfr2fccsf (TARGET_HARD_FLOAT)
#define HAVE_movfr2fccdf ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_movgr2fccsi (TARGET_HARD_FLOAT)
#define HAVE_movgr2fccdi ((TARGET_HARD_FLOAT) && (TARGET_64BIT))
#define HAVE_movfcc2grsi (TARGET_HARD_FLOAT)
#define HAVE_movfcc2grdi ((TARGET_HARD_FLOAT) && (TARGET_64BIT))
#define HAVE_loongarch_ibar 1
#define HAVE_loongarch_dbar 1
#define HAVE_loongarch_cpucfg (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_loongarch_syscall 1
#define HAVE_loongarch_break 1
#define HAVE_loongarch_asrtle_d (TARGET_64BIT)
#define HAVE_loongarch_asrtgt_d (TARGET_64BIT)
#define HAVE_loongarch_csrrd_w 1
#define HAVE_loongarch_csrrd_d (TARGET_64BIT)
#define HAVE_loongarch_csrwr_w 1
#define HAVE_loongarch_csrwr_d (TARGET_64BIT)
#define HAVE_loongarch_csrxchg_w 1
#define HAVE_loongarch_csrxchg_d (TARGET_64BIT)
#define HAVE_loongarch_iocsrrd_b (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_loongarch_iocsrrd_h (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_loongarch_iocsrrd_w (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_loongarch_iocsrrd_d ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_64BIT))
#define HAVE_loongarch_iocsrwr_b (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_loongarch_iocsrwr_h (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_loongarch_iocsrwr_w (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_loongarch_iocsrwr_d ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_64BIT))
#define HAVE_loongarch_cacop_w (TARGET_32BIT)
#define HAVE_loongarch_cacop_d (TARGET_64BIT)
#define HAVE_loongarch_lddir_w ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_32BIT))
#define HAVE_loongarch_lddir_d ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_64BIT))
#define HAVE_loongarch_ldpte_w ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_32BIT))
#define HAVE_loongarch_ldpte_d ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_64BIT))
#define HAVE_ashlsi3 1
#define HAVE_ashrsi3 1
#define HAVE_lshrsi3 1
#define HAVE_ashldi3 (TARGET_64BIT)
#define HAVE_ashrdi3 (TARGET_64BIT)
#define HAVE_lshrdi3 (TARGET_64BIT)
#define HAVE_rotrsi3 (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_rotrdi3 ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_64BIT))
#define HAVE_zero_extend_ashift (TARGET_64BIT \
   && ((INTVAL (operands[3]) >> INTVAL (operands[2])) == 0xffffffff))
#define HAVE_bstrpick_alsl_paired (TARGET_64BIT \
   && ((INTVAL (operands[4]) >> INTVAL (operands[3])) == 0xffffffff))
#define HAVE_alslsi3 (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_alsldi3 ((TARGET_32BIT_STANDARD || TARGET_64BIT) && (TARGET_64BIT))
#define HAVE_bswaphi2 (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_bswapsi2 (TARGET_64BIT)
#define HAVE_bswapdi2 (TARGET_64BIT)
#define HAVE_revb_2h (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_revb_4h (TARGET_64BIT)
#define HAVE_revh_d (TARGET_64BIT)
#define HAVE_sunordered_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_suneq_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_sunlt_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_sunle_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_seq_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_slt_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_sle_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_sordered_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_sltgt_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_sne_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_sge_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_sgt_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_sunge_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_sungt_sf_using_FCCmode (TARGET_HARD_FLOAT)
#define HAVE_sunordered_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_suneq_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sunlt_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sunle_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_seq_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_slt_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sle_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sordered_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sltgt_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sne_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sge_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sgt_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sunge_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_sungt_df_using_FCCmode ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_indirect_jumpsi (Pmode == SImode)
#define HAVE_indirect_jumpdi (Pmode == DImode)
#define HAVE_tablejumpsi (Pmode == SImode)
#define HAVE_tablejumpdi (Pmode == DImode)
#define HAVE_blockage 1
#define HAVE_probe_stack_rangesi (Pmode == SImode)
#define HAVE_probe_stack_rangedi (Pmode == DImode)
#define HAVE_return_internal 1
#define HAVE_simple_return_internal 1
#define HAVE_loongarch_ertn 1
#define HAVE_eh_set_ra_si (! TARGET_64BIT)
#define HAVE_eh_set_ra_di (TARGET_64BIT)
#define HAVE_sibcall_internal (SIBLING_CALL_P (insn))
#define HAVE_sibcall_value_internal (SIBLING_CALL_P (insn))
#define HAVE_sibcall_value_multiple_internal (SIBLING_CALL_P (insn))
#define HAVE_call_internal 1
#define HAVE_call_value_internal 1
#define HAVE_call_value_multiple_internal 1
#define HAVE_prefetch 1
#define HAVE_nop 1
#define HAVE_loongarch_movfcsr2gr (TARGET_HARD_FLOAT)
#define HAVE_loongarch_movgr2fcsr (TARGET_HARD_FLOAT)
#define HAVE_fclass_s (TARGET_HARD_FLOAT)
#define HAVE_fclass_d ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_bytepick_w (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_bytepick_d (TARGET_64BIT)
#define HAVE_bitrev_4b (TARGET_32BIT_STANDARD || TARGET_64BIT)
#define HAVE_bitrev_8b (TARGET_64BIT)
#define HAVE_stack_tiesi (TARGET_32BIT)
#define HAVE_stack_tiedi (TARGET_64BIT)
#define HAVE_loongarch_crc_w_b_w (TARGET_64BIT)
#define HAVE_loongarch_crc_w_h_w (TARGET_64BIT)
#define HAVE_loongarch_crc_w_w_w (TARGET_64BIT)
#define HAVE_loongarch_crc_w_d_w (TARGET_64BIT)
#define HAVE_loongarch_crcc_w_b_w (TARGET_64BIT)
#define HAVE_loongarch_crcc_w_h_w (TARGET_64BIT)
#define HAVE_loongarch_crcc_w_w_w (TARGET_64BIT)
#define HAVE_loongarch_crcc_w_d_w (TARGET_64BIT)
#define HAVE_mem_thread_fence_1 1
#define HAVE_atomic_storedi (TARGET_64BIT)
#define HAVE_atomic_storesi 1
#define HAVE_atomic_adddi (TARGET_64BIT)
#define HAVE_atomic_ordi (TARGET_64BIT)
#define HAVE_atomic_xordi (TARGET_64BIT)
#define HAVE_atomic_anddi (TARGET_64BIT)
#define HAVE_atomic_addsi 1
#define HAVE_atomic_orsi 1
#define HAVE_atomic_xorsi 1
#define HAVE_atomic_andsi 1
#define HAVE_atomic_fetch_adddi (TARGET_64BIT)
#define HAVE_atomic_fetch_ordi (TARGET_64BIT)
#define HAVE_atomic_fetch_xordi (TARGET_64BIT)
#define HAVE_atomic_fetch_anddi (TARGET_64BIT)
#define HAVE_atomic_fetch_addsi 1
#define HAVE_atomic_fetch_orsi 1
#define HAVE_atomic_fetch_xorsi 1
#define HAVE_atomic_fetch_andsi 1
#define HAVE_atomic_exchangedi (TARGET_64BIT)
#define HAVE_atomic_exchangesi 1
#define HAVE_atomic_cas_value_strongsi 1
#define HAVE_atomic_cas_value_strongdi (TARGET_64BIT)
#define HAVE_atomic_cas_value_cmp_and_7_si 1
#define HAVE_atomic_cas_value_cmp_and_7_di (TARGET_64BIT)
#define HAVE_atomic_cas_value_add_7_si 1
#define HAVE_atomic_cas_value_add_7_di (TARGET_64BIT)
#define HAVE_atomic_cas_value_sub_7_si 1
#define HAVE_atomic_cas_value_sub_7_di (TARGET_64BIT)
#define HAVE_atomic_cas_value_and_7_si 1
#define HAVE_atomic_cas_value_and_7_di (TARGET_64BIT)
#define HAVE_atomic_cas_value_xor_7_si 1
#define HAVE_atomic_cas_value_xor_7_di (TARGET_64BIT)
#define HAVE_atomic_cas_value_or_7_si 1
#define HAVE_atomic_cas_value_or_7_di (TARGET_64BIT)
#define HAVE_atomic_cas_value_nand_7_si 1
#define HAVE_atomic_cas_value_nand_7_di (TARGET_64BIT)
#define HAVE_atomic_cas_value_exchange_7_si 1
#define HAVE_atomic_cas_value_exchange_7_di (TARGET_64BIT)
#define HAVE_vec_pack_trunc_v2di (ISA_HAS_LSX)
#define HAVE_vec_pack_trunc_v4si (ISA_HAS_LSX)
#define HAVE_vec_pack_trunc_v8hi (ISA_HAS_LSX)
#define HAVE_lsx_vec_extract_d_f (ISA_HAS_LSX)
#define HAVE_lsx_vec_extract_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vinsgr2vr_d (ISA_HAS_LSX)
#define HAVE_lsx_vinsgr2vr_w (ISA_HAS_LSX)
#define HAVE_lsx_vinsgr2vr_h (ISA_HAS_LSX)
#define HAVE_lsx_vinsgr2vr_b (ISA_HAS_LSX)
#define HAVE_lsx_vextrins_d_f_internal (ISA_HAS_LSX)
#define HAVE_lsx_vextrins_w_f_internal (ISA_HAS_LSX)
#define HAVE_lsx_vextrins_d_internal (ISA_HAS_LSX)
#define HAVE_lsx_vextrins_w_internal (ISA_HAS_LSX)
#define HAVE_lsx_vextrins_h_internal (ISA_HAS_LSX)
#define HAVE_lsx_vextrins_b_internal (ISA_HAS_LSX)
#define HAVE_lsx_vextrins_d_f_scalar (ISA_HAS_LSX)
#define HAVE_lsx_vextrins_w_f_scalar (ISA_HAS_LSX)
#define HAVE_lsx_vpickve2gr_h (ISA_HAS_LSX)
#define HAVE_lsx_vpickve2gr_hu (ISA_HAS_LSX)
#define HAVE_lsx_vpickve2gr_b (ISA_HAS_LSX)
#define HAVE_lsx_vpickve2gr_bu (ISA_HAS_LSX)
#define HAVE_lsx_vpickve2gr_w (ISA_HAS_LSX)
#define HAVE_lsx_vpickve2gr_wu (ISA_HAS_LSX)
#define HAVE_lsx_vpickve2gr_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vpickve2gr_w_fu (ISA_HAS_LSX)
#define HAVE_lsx_vpickve2gr_du (ISA_HAS_LSX)
#define HAVE_lsx_vpickve2gr_d (ISA_HAS_LSX)
#define HAVE_lsx_vpickve2gr_d_f (ISA_HAS_LSX)
#define HAVE_lsx_vshuf_d_f (ISA_HAS_LSX)
#define HAVE_lsx_vshuf_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vshuf_d (ISA_HAS_LSX)
#define HAVE_lsx_vshuf_w (ISA_HAS_LSX)
#define HAVE_lsx_vshuf_h (ISA_HAS_LSX)
#define HAVE_movv2df_lsx (ISA_HAS_LSX)
#define HAVE_movv4sf_lsx (ISA_HAS_LSX)
#define HAVE_movv2di_lsx (ISA_HAS_LSX)
#define HAVE_movv4si_lsx (ISA_HAS_LSX)
#define HAVE_movv8hi_lsx (ISA_HAS_LSX)
#define HAVE_movv16qi_lsx (ISA_HAS_LSX)
#define HAVE_addv2di3 (ISA_HAS_LSX)
#define HAVE_addv4si3 (ISA_HAS_LSX)
#define HAVE_addv8hi3 (ISA_HAS_LSX)
#define HAVE_addv16qi3 (ISA_HAS_LSX)
#define HAVE_subv2di3 (ISA_HAS_LSX)
#define HAVE_subv4si3 (ISA_HAS_LSX)
#define HAVE_subv8hi3 (ISA_HAS_LSX)
#define HAVE_subv16qi3 (ISA_HAS_LSX)
#define HAVE_mulv2di3 (ISA_HAS_LSX)
#define HAVE_mulv4si3 (ISA_HAS_LSX)
#define HAVE_mulv8hi3 (ISA_HAS_LSX)
#define HAVE_mulv16qi3 (ISA_HAS_LSX)
#define HAVE_lsx_vmadd_d (ISA_HAS_LSX)
#define HAVE_lsx_vmadd_w (ISA_HAS_LSX)
#define HAVE_lsx_vmadd_h (ISA_HAS_LSX)
#define HAVE_lsx_vmadd_b (ISA_HAS_LSX)
#define HAVE_lsx_vmsub_d (ISA_HAS_LSX)
#define HAVE_lsx_vmsub_w (ISA_HAS_LSX)
#define HAVE_lsx_vmsub_h (ISA_HAS_LSX)
#define HAVE_lsx_vmsub_b (ISA_HAS_LSX)
#define HAVE_divv2di3 (ISA_HAS_LSX)
#define HAVE_divv4si3 (ISA_HAS_LSX)
#define HAVE_divv8hi3 (ISA_HAS_LSX)
#define HAVE_divv16qi3 (ISA_HAS_LSX)
#define HAVE_udivv2di3 (ISA_HAS_LSX)
#define HAVE_udivv4si3 (ISA_HAS_LSX)
#define HAVE_udivv8hi3 (ISA_HAS_LSX)
#define HAVE_udivv16qi3 (ISA_HAS_LSX)
#define HAVE_modv2di3 (ISA_HAS_LSX)
#define HAVE_modv4si3 (ISA_HAS_LSX)
#define HAVE_modv8hi3 (ISA_HAS_LSX)
#define HAVE_modv16qi3 (ISA_HAS_LSX)
#define HAVE_umodv2di3 (ISA_HAS_LSX)
#define HAVE_umodv4si3 (ISA_HAS_LSX)
#define HAVE_umodv8hi3 (ISA_HAS_LSX)
#define HAVE_umodv16qi3 (ISA_HAS_LSX)
#define HAVE_xorv2di3 (ISA_HAS_LSX)
#define HAVE_xorv4si3 (ISA_HAS_LSX)
#define HAVE_xorv8hi3 (ISA_HAS_LSX)
#define HAVE_xorv16qi3 (ISA_HAS_LSX)
#define HAVE_iorv2df3 (ISA_HAS_LSX)
#define HAVE_iorv4sf3 (ISA_HAS_LSX)
#define HAVE_iorv2di3 (ISA_HAS_LSX)
#define HAVE_iorv4si3 (ISA_HAS_LSX)
#define HAVE_iorv8hi3 (ISA_HAS_LSX)
#define HAVE_iorv16qi3 (ISA_HAS_LSX)
#define HAVE_andv2df3 (ISA_HAS_LSX)
#define HAVE_andv4sf3 (ISA_HAS_LSX)
#define HAVE_andv2di3 (ISA_HAS_LSX)
#define HAVE_andv4si3 (ISA_HAS_LSX)
#define HAVE_andv8hi3 (ISA_HAS_LSX)
#define HAVE_andv16qi3 (ISA_HAS_LSX)
#define HAVE_one_cmplv2di2 (ISA_HAS_LSX)
#define HAVE_one_cmplv4si2 (ISA_HAS_LSX)
#define HAVE_one_cmplv8hi2 (ISA_HAS_LSX)
#define HAVE_one_cmplv16qi2 (ISA_HAS_LSX)
#define HAVE_vlshrv2di3 (ISA_HAS_LSX)
#define HAVE_vlshrv4si3 (ISA_HAS_LSX)
#define HAVE_vlshrv8hi3 (ISA_HAS_LSX)
#define HAVE_vlshrv16qi3 (ISA_HAS_LSX)
#define HAVE_vashrv2di3 (ISA_HAS_LSX)
#define HAVE_vashrv4si3 (ISA_HAS_LSX)
#define HAVE_vashrv8hi3 (ISA_HAS_LSX)
#define HAVE_vashrv16qi3 (ISA_HAS_LSX)
#define HAVE_vashlv2di3 (ISA_HAS_LSX)
#define HAVE_vashlv4si3 (ISA_HAS_LSX)
#define HAVE_vashlv8hi3 (ISA_HAS_LSX)
#define HAVE_vashlv16qi3 (ISA_HAS_LSX)
#define HAVE_addv2df3 (ISA_HAS_LSX)
#define HAVE_addv4sf3 (ISA_HAS_LSX)
#define HAVE_subv2df3 (ISA_HAS_LSX)
#define HAVE_subv4sf3 (ISA_HAS_LSX)
#define HAVE_mulv2df3 (ISA_HAS_LSX)
#define HAVE_mulv4sf3 (ISA_HAS_LSX)
#define HAVE_divv2df3 (ISA_HAS_LSX)
#define HAVE_divv4sf3 (ISA_HAS_LSX)
#define HAVE_fmav2df4 (ISA_HAS_LSX)
#define HAVE_fmav4sf4 (ISA_HAS_LSX)
#define HAVE_fnmav2df4 (ISA_HAS_LSX)
#define HAVE_fnmav4sf4 (ISA_HAS_LSX)
#define HAVE_sqrtv2df2 (ISA_HAS_LSX)
#define HAVE_sqrtv4sf2 (ISA_HAS_LSX)
#define HAVE_lsx_vadda_d (ISA_HAS_LSX)
#define HAVE_lsx_vadda_w (ISA_HAS_LSX)
#define HAVE_lsx_vadda_h (ISA_HAS_LSX)
#define HAVE_lsx_vadda_b (ISA_HAS_LSX)
#define HAVE_ssaddv2di3 (ISA_HAS_LSX)
#define HAVE_ssaddv4si3 (ISA_HAS_LSX)
#define HAVE_ssaddv8hi3 (ISA_HAS_LSX)
#define HAVE_ssaddv16qi3 (ISA_HAS_LSX)
#define HAVE_usaddv2di3 (ISA_HAS_LSX)
#define HAVE_usaddv4si3 (ISA_HAS_LSX)
#define HAVE_usaddv8hi3 (ISA_HAS_LSX)
#define HAVE_usaddv16qi3 (ISA_HAS_LSX)
#define HAVE_lsx_vabsd_s_d (ISA_HAS_LSX)
#define HAVE_lsx_vabsd_s_w (ISA_HAS_LSX)
#define HAVE_lsx_vabsd_s_h (ISA_HAS_LSX)
#define HAVE_lsx_vabsd_s_b (ISA_HAS_LSX)
#define HAVE_lsx_vabsd_u_du (ISA_HAS_LSX)
#define HAVE_lsx_vabsd_u_wu (ISA_HAS_LSX)
#define HAVE_lsx_vabsd_u_hu (ISA_HAS_LSX)
#define HAVE_lsx_vabsd_u_bu (ISA_HAS_LSX)
#define HAVE_lsx_vavg_s_d (ISA_HAS_LSX)
#define HAVE_lsx_vavg_s_w (ISA_HAS_LSX)
#define HAVE_lsx_vavg_s_h (ISA_HAS_LSX)
#define HAVE_lsx_vavg_s_b (ISA_HAS_LSX)
#define HAVE_lsx_vavg_u_du (ISA_HAS_LSX)
#define HAVE_lsx_vavg_u_wu (ISA_HAS_LSX)
#define HAVE_lsx_vavg_u_hu (ISA_HAS_LSX)
#define HAVE_lsx_vavg_u_bu (ISA_HAS_LSX)
#define HAVE_lsx_vavgr_s_d (ISA_HAS_LSX)
#define HAVE_lsx_vavgr_s_w (ISA_HAS_LSX)
#define HAVE_lsx_vavgr_s_h (ISA_HAS_LSX)
#define HAVE_lsx_vavgr_s_b (ISA_HAS_LSX)
#define HAVE_lsx_vavgr_u_du (ISA_HAS_LSX)
#define HAVE_lsx_vavgr_u_wu (ISA_HAS_LSX)
#define HAVE_lsx_vavgr_u_hu (ISA_HAS_LSX)
#define HAVE_lsx_vavgr_u_bu (ISA_HAS_LSX)
#define HAVE_lsx_vbitclr_d (ISA_HAS_LSX)
#define HAVE_lsx_vbitclr_w (ISA_HAS_LSX)
#define HAVE_lsx_vbitclr_h (ISA_HAS_LSX)
#define HAVE_lsx_vbitclr_b (ISA_HAS_LSX)
#define HAVE_lsx_vbitclri_d (ISA_HAS_LSX)
#define HAVE_lsx_vbitclri_w (ISA_HAS_LSX)
#define HAVE_lsx_vbitclri_h (ISA_HAS_LSX)
#define HAVE_lsx_vbitclri_b (ISA_HAS_LSX)
#define HAVE_lsx_vbitrev_d (ISA_HAS_LSX)
#define HAVE_lsx_vbitrev_w (ISA_HAS_LSX)
#define HAVE_lsx_vbitrev_h (ISA_HAS_LSX)
#define HAVE_lsx_vbitrev_b (ISA_HAS_LSX)
#define HAVE_lsx_vbitrevi_d (ISA_HAS_LSX)
#define HAVE_lsx_vbitrevi_w (ISA_HAS_LSX)
#define HAVE_lsx_vbitrevi_h (ISA_HAS_LSX)
#define HAVE_lsx_vbitrevi_b (ISA_HAS_LSX)
#define HAVE_lsx_vbitsel_d (ISA_HAS_LSX)
#define HAVE_lsx_vbitsel_w (ISA_HAS_LSX)
#define HAVE_lsx_vbitsel_h (ISA_HAS_LSX)
#define HAVE_lsx_vbitsel_b (ISA_HAS_LSX)
#define HAVE_lsx_vbitseli_b (ISA_HAS_LSX)
#define HAVE_lsx_vbitset_d (ISA_HAS_LSX)
#define HAVE_lsx_vbitset_w (ISA_HAS_LSX)
#define HAVE_lsx_vbitset_h (ISA_HAS_LSX)
#define HAVE_lsx_vbitset_b (ISA_HAS_LSX)
#define HAVE_lsx_vbitseti_d (ISA_HAS_LSX)
#define HAVE_lsx_vbitseti_w (ISA_HAS_LSX)
#define HAVE_lsx_vbitseti_h (ISA_HAS_LSX)
#define HAVE_lsx_vbitseti_b (ISA_HAS_LSX)
#define HAVE_lsx_vseq_d (ISA_HAS_LSX)
#define HAVE_lsx_vsle_d (ISA_HAS_LSX)
#define HAVE_lsx_vsle_du (ISA_HAS_LSX)
#define HAVE_lsx_vslt_d (ISA_HAS_LSX)
#define HAVE_lsx_vslt_du (ISA_HAS_LSX)
#define HAVE_lsx_vseq_w (ISA_HAS_LSX)
#define HAVE_lsx_vsle_w (ISA_HAS_LSX)
#define HAVE_lsx_vsle_wu (ISA_HAS_LSX)
#define HAVE_lsx_vslt_w (ISA_HAS_LSX)
#define HAVE_lsx_vslt_wu (ISA_HAS_LSX)
#define HAVE_lsx_vseq_h (ISA_HAS_LSX)
#define HAVE_lsx_vsle_h (ISA_HAS_LSX)
#define HAVE_lsx_vsle_hu (ISA_HAS_LSX)
#define HAVE_lsx_vslt_h (ISA_HAS_LSX)
#define HAVE_lsx_vslt_hu (ISA_HAS_LSX)
#define HAVE_lsx_vseq_b (ISA_HAS_LSX)
#define HAVE_lsx_vsle_b (ISA_HAS_LSX)
#define HAVE_lsx_vsle_bu (ISA_HAS_LSX)
#define HAVE_lsx_vslt_b (ISA_HAS_LSX)
#define HAVE_lsx_vslt_bu (ISA_HAS_LSX)
#define HAVE_lsx_vfclass_d (ISA_HAS_LSX)
#define HAVE_lsx_vfclass_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_caf_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_caf_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cune_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cune_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cun_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cor_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_ceq_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cne_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cle_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_clt_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cueq_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cule_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cult_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cun_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cor_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_ceq_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cne_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cle_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_clt_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cueq_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cule_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_cult_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_saf_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sun_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sor_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_seq_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sne_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sueq_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sune_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sule_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sult_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sle_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_slt_d (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_saf_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sun_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sor_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_seq_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sne_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sueq_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sune_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sule_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sult_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_sle_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcmp_slt_s (ISA_HAS_LSX)
#define HAVE_floatv2div2df2 (ISA_HAS_LSX)
#define HAVE_floatv4siv4sf2 (ISA_HAS_LSX)
#define HAVE_floatunsv2div2df2 (ISA_HAS_LSX)
#define HAVE_floatunsv4siv4sf2 (ISA_HAS_LSX)
#define HAVE_lsx_vreplgr2vr_d (ISA_HAS_LSX)
#define HAVE_lsx_vreplgr2vr_w (ISA_HAS_LSX)
#define HAVE_lsx_vreplgr2vr_h (ISA_HAS_LSX)
#define HAVE_lsx_vreplgr2vr_b (ISA_HAS_LSX)
#define HAVE_logbv2df2 (ISA_HAS_LSX)
#define HAVE_logbv4sf2 (ISA_HAS_LSX)
#define HAVE_smaxv2df3 (ISA_HAS_LSX)
#define HAVE_smaxv4sf3 (ISA_HAS_LSX)
#define HAVE_lsx_vfmaxa_d (ISA_HAS_LSX)
#define HAVE_lsx_vfmaxa_s (ISA_HAS_LSX)
#define HAVE_sminv2df3 (ISA_HAS_LSX)
#define HAVE_sminv4sf3 (ISA_HAS_LSX)
#define HAVE_lsx_vfmina_d (ISA_HAS_LSX)
#define HAVE_lsx_vfmina_s (ISA_HAS_LSX)
#define HAVE_lsx_vfrecip_d (ISA_HAS_LSX)
#define HAVE_lsx_vfrecip_s (ISA_HAS_LSX)
#define HAVE_lsx_vfrint_d (ISA_HAS_LSX)
#define HAVE_lsx_vfrint_s (ISA_HAS_LSX)
#define HAVE_lsx_vfrsqrt_d (ISA_HAS_LSX)
#define HAVE_lsx_vfrsqrt_s (ISA_HAS_LSX)
#define HAVE_lsx_vftint_s_l_d (ISA_HAS_LSX)
#define HAVE_lsx_vftint_s_w_s (ISA_HAS_LSX)
#define HAVE_lsx_vftint_u_lu_d (ISA_HAS_LSX)
#define HAVE_lsx_vftint_u_wu_s (ISA_HAS_LSX)
#define HAVE_fix_truncv2dfv2di2 (ISA_HAS_LSX)
#define HAVE_fix_truncv4sfv4si2 (ISA_HAS_LSX)
#define HAVE_fixuns_truncv2dfv2di2 (ISA_HAS_LSX)
#define HAVE_fixuns_truncv4sfv4si2 (ISA_HAS_LSX)
#define HAVE_lsx_vhaddw_h_b (ISA_HAS_LSX)
#define HAVE_lsx_vhaddw_hu_bu (ISA_HAS_LSX)
#define HAVE_lsx_vhsubw_h_b (ISA_HAS_LSX)
#define HAVE_lsx_vhsubw_hu_bu (ISA_HAS_LSX)
#define HAVE_lsx_vhaddw_w_h (ISA_HAS_LSX)
#define HAVE_lsx_vhaddw_wu_hu (ISA_HAS_LSX)
#define HAVE_lsx_vhsubw_w_h (ISA_HAS_LSX)
#define HAVE_lsx_vhsubw_wu_hu (ISA_HAS_LSX)
#define HAVE_lsx_vhaddw_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vhaddw_du_wu (ISA_HAS_LSX)
#define HAVE_lsx_vhsubw_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vhsubw_du_wu (ISA_HAS_LSX)
#define HAVE_lsx_vpackev_b (ISA_HAS_LSX)
#define HAVE_lsx_vpackev_h (ISA_HAS_LSX)
#define HAVE_lsx_vpackev_w (ISA_HAS_LSX)
#define HAVE_lsx_vpackev_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vilvh_b (ISA_HAS_LSX)
#define HAVE_lsx_vilvh_h (ISA_HAS_LSX)
#define HAVE_lsx_vilvh_w (ISA_HAS_LSX)
#define HAVE_lsx_vilvh_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vilvh_d (ISA_HAS_LSX)
#define HAVE_lsx_vilvh_d_f (ISA_HAS_LSX)
#define HAVE_lsx_vpackod_b (ISA_HAS_LSX)
#define HAVE_lsx_vpackod_h (ISA_HAS_LSX)
#define HAVE_lsx_vpackod_w (ISA_HAS_LSX)
#define HAVE_lsx_vpackod_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vilvl_b (ISA_HAS_LSX)
#define HAVE_lsx_vilvl_h (ISA_HAS_LSX)
#define HAVE_lsx_vilvl_w (ISA_HAS_LSX)
#define HAVE_lsx_vilvl_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vilvl_d (ISA_HAS_LSX)
#define HAVE_lsx_vilvl_d_f (ISA_HAS_LSX)
#define HAVE_smaxv2di3 (ISA_HAS_LSX)
#define HAVE_smaxv4si3 (ISA_HAS_LSX)
#define HAVE_smaxv8hi3 (ISA_HAS_LSX)
#define HAVE_smaxv16qi3 (ISA_HAS_LSX)
#define HAVE_umaxv2di3 (ISA_HAS_LSX)
#define HAVE_umaxv4si3 (ISA_HAS_LSX)
#define HAVE_umaxv8hi3 (ISA_HAS_LSX)
#define HAVE_umaxv16qi3 (ISA_HAS_LSX)
#define HAVE_sminv2di3 (ISA_HAS_LSX)
#define HAVE_sminv4si3 (ISA_HAS_LSX)
#define HAVE_sminv8hi3 (ISA_HAS_LSX)
#define HAVE_sminv16qi3 (ISA_HAS_LSX)
#define HAVE_uminv2di3 (ISA_HAS_LSX)
#define HAVE_uminv4si3 (ISA_HAS_LSX)
#define HAVE_uminv8hi3 (ISA_HAS_LSX)
#define HAVE_uminv16qi3 (ISA_HAS_LSX)
#define HAVE_lsx_vclo_d (ISA_HAS_LSX)
#define HAVE_lsx_vclo_w (ISA_HAS_LSX)
#define HAVE_lsx_vclo_h (ISA_HAS_LSX)
#define HAVE_lsx_vclo_b (ISA_HAS_LSX)
#define HAVE_clzv2di2 (ISA_HAS_LSX)
#define HAVE_clzv4si2 (ISA_HAS_LSX)
#define HAVE_clzv8hi2 (ISA_HAS_LSX)
#define HAVE_clzv16qi2 (ISA_HAS_LSX)
#define HAVE_lsx_nor_d (ISA_HAS_LSX)
#define HAVE_lsx_nor_w (ISA_HAS_LSX)
#define HAVE_lsx_nor_h (ISA_HAS_LSX)
#define HAVE_lsx_nor_b (ISA_HAS_LSX)
#define HAVE_lsx_vpickev_b (ISA_HAS_LSX)
#define HAVE_lsx_vpickev_h (ISA_HAS_LSX)
#define HAVE_lsx_vpickev_w (ISA_HAS_LSX)
#define HAVE_lsx_vpickev_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vpickod_b (ISA_HAS_LSX)
#define HAVE_lsx_vpickod_h (ISA_HAS_LSX)
#define HAVE_lsx_vpickod_w (ISA_HAS_LSX)
#define HAVE_lsx_vpickod_w_f (ISA_HAS_LSX)
#define HAVE_popcountv2di2 (ISA_HAS_LSX)
#define HAVE_popcountv4si2 (ISA_HAS_LSX)
#define HAVE_popcountv8hi2 (ISA_HAS_LSX)
#define HAVE_popcountv16qi2 (ISA_HAS_LSX)
#define HAVE_lsx_vsat_s_d (ISA_HAS_LSX)
#define HAVE_lsx_vsat_s_w (ISA_HAS_LSX)
#define HAVE_lsx_vsat_s_h (ISA_HAS_LSX)
#define HAVE_lsx_vsat_s_b (ISA_HAS_LSX)
#define HAVE_lsx_vsat_u_du (ISA_HAS_LSX)
#define HAVE_lsx_vsat_u_wu (ISA_HAS_LSX)
#define HAVE_lsx_vsat_u_hu (ISA_HAS_LSX)
#define HAVE_lsx_vsat_u_bu (ISA_HAS_LSX)
#define HAVE_lsx_vshuf4i_w (ISA_HAS_LSX)
#define HAVE_lsx_vshuf4i_h (ISA_HAS_LSX)
#define HAVE_lsx_vshuf4i_b (ISA_HAS_LSX)
#define HAVE_lsx_vshuf4i_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vsrar_d (ISA_HAS_LSX)
#define HAVE_lsx_vsrar_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrar_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrar_b (ISA_HAS_LSX)
#define HAVE_lsx_vsrari_d (ISA_HAS_LSX)
#define HAVE_lsx_vsrari_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrari_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrari_b (ISA_HAS_LSX)
#define HAVE_lsx_vsrlr_d (ISA_HAS_LSX)
#define HAVE_lsx_vsrlr_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrlr_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrlr_b (ISA_HAS_LSX)
#define HAVE_lsx_vsrlri_d (ISA_HAS_LSX)
#define HAVE_lsx_vsrlri_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrlri_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrlri_b (ISA_HAS_LSX)
#define HAVE_lsx_vssub_s_d (ISA_HAS_LSX)
#define HAVE_lsx_vssub_s_w (ISA_HAS_LSX)
#define HAVE_lsx_vssub_s_h (ISA_HAS_LSX)
#define HAVE_lsx_vssub_s_b (ISA_HAS_LSX)
#define HAVE_lsx_vssub_u_du (ISA_HAS_LSX)
#define HAVE_lsx_vssub_u_wu (ISA_HAS_LSX)
#define HAVE_lsx_vssub_u_hu (ISA_HAS_LSX)
#define HAVE_lsx_vssub_u_bu (ISA_HAS_LSX)
#define HAVE_lsx_vreplve_d_f (ISA_HAS_LSX)
#define HAVE_lsx_vreplve_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vreplve_d (ISA_HAS_LSX)
#define HAVE_lsx_vreplve_w (ISA_HAS_LSX)
#define HAVE_lsx_vreplve_h (ISA_HAS_LSX)
#define HAVE_lsx_vreplve_b (ISA_HAS_LSX)
#define HAVE_lsx_vreplvei_d_f (ISA_HAS_LSX)
#define HAVE_lsx_vreplvei_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vreplvei_d (ISA_HAS_LSX)
#define HAVE_lsx_vreplvei_w (ISA_HAS_LSX)
#define HAVE_lsx_vreplvei_h (ISA_HAS_LSX)
#define HAVE_lsx_vreplvei_b (ISA_HAS_LSX)
#define HAVE_lsx_vreplvei_d_f_scalar (ISA_HAS_LSX)
#define HAVE_lsx_vreplvei_w_f_scalar (ISA_HAS_LSX)
#define HAVE_lsx_vfcvt_h_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcvt_s_d (ISA_HAS_LSX)
#define HAVE_vec_pack_trunc_v2df (ISA_HAS_LSX)
#define HAVE_lsx_vfcvth_s_h (ISA_HAS_LSX)
#define HAVE_lsx_vfcvth_d_s (ISA_HAS_LSX)
#define HAVE_lsx_vfcvtl_s_h (ISA_HAS_LSX)
#define HAVE_lsx_vfcvtl_d_s (ISA_HAS_LSX)
#define HAVE_lsx_bz_d_f (ISA_HAS_LSX)
#define HAVE_lsx_bnz_d_f (ISA_HAS_LSX)
#define HAVE_lsx_bz_w_f (ISA_HAS_LSX)
#define HAVE_lsx_bnz_w_f (ISA_HAS_LSX)
#define HAVE_lsx_bz_d (ISA_HAS_LSX)
#define HAVE_lsx_bnz_d (ISA_HAS_LSX)
#define HAVE_lsx_bz_w (ISA_HAS_LSX)
#define HAVE_lsx_bnz_w (ISA_HAS_LSX)
#define HAVE_lsx_bz_h (ISA_HAS_LSX)
#define HAVE_lsx_bnz_h (ISA_HAS_LSX)
#define HAVE_lsx_bz_b (ISA_HAS_LSX)
#define HAVE_lsx_bnz_b (ISA_HAS_LSX)
#define HAVE_lsx_bz_v_d_f (ISA_HAS_LSX)
#define HAVE_lsx_bnz_v_d_f (ISA_HAS_LSX)
#define HAVE_lsx_bz_v_w_f (ISA_HAS_LSX)
#define HAVE_lsx_bnz_v_w_f (ISA_HAS_LSX)
#define HAVE_lsx_bz_v_d (ISA_HAS_LSX)
#define HAVE_lsx_bnz_v_d (ISA_HAS_LSX)
#define HAVE_lsx_bz_v_w (ISA_HAS_LSX)
#define HAVE_lsx_bnz_v_w (ISA_HAS_LSX)
#define HAVE_lsx_bz_v_h (ISA_HAS_LSX)
#define HAVE_lsx_bnz_v_h (ISA_HAS_LSX)
#define HAVE_lsx_bz_v_b (ISA_HAS_LSX)
#define HAVE_lsx_bnz_v_b (ISA_HAS_LSX)
#define HAVE_vandnv2df3 (ISA_HAS_LSX)
#define HAVE_vandnv4sf3 (ISA_HAS_LSX)
#define HAVE_vandnv2di3 (ISA_HAS_LSX)
#define HAVE_vandnv4si3 (ISA_HAS_LSX)
#define HAVE_vandnv8hi3 (ISA_HAS_LSX)
#define HAVE_vandnv16qi3 (ISA_HAS_LSX)
#define HAVE_vabsv2di2 (ISA_HAS_LSX)
#define HAVE_vabsv4si2 (ISA_HAS_LSX)
#define HAVE_vabsv8hi2 (ISA_HAS_LSX)
#define HAVE_vabsv16qi2 (ISA_HAS_LSX)
#define HAVE_vnegv2di2 (ISA_HAS_LSX)
#define HAVE_vnegv4si2 (ISA_HAS_LSX)
#define HAVE_vnegv8hi2 (ISA_HAS_LSX)
#define HAVE_vnegv16qi2 (ISA_HAS_LSX)
#define HAVE_lsx_vmuh_s_d (ISA_HAS_LSX)
#define HAVE_lsx_vmuh_s_w (ISA_HAS_LSX)
#define HAVE_lsx_vmuh_s_h (ISA_HAS_LSX)
#define HAVE_lsx_vmuh_s_b (ISA_HAS_LSX)
#define HAVE_lsx_vmuh_u_du (ISA_HAS_LSX)
#define HAVE_lsx_vmuh_u_wu (ISA_HAS_LSX)
#define HAVE_lsx_vmuh_u_hu (ISA_HAS_LSX)
#define HAVE_lsx_vmuh_u_bu (ISA_HAS_LSX)
#define HAVE_lsx_vextw_s_d (ISA_HAS_LSX)
#define HAVE_lsx_vextw_u_d (ISA_HAS_LSX)
#define HAVE_lsx_vsllwil_s_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vsllwil_s_w_h (ISA_HAS_LSX)
#define HAVE_lsx_vsllwil_s_h_b (ISA_HAS_LSX)
#define HAVE_lsx_vsllwil_u_du_wu (ISA_HAS_LSX)
#define HAVE_lsx_vsllwil_u_wu_hu (ISA_HAS_LSX)
#define HAVE_lsx_vsllwil_u_hu_bu (ISA_HAS_LSX)
#define HAVE_lsx_vsran_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vsran_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vsran_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssran_s_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vssran_s_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vssran_s_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssran_u_wu_d (ISA_HAS_LSX)
#define HAVE_lsx_vssran_u_hu_w (ISA_HAS_LSX)
#define HAVE_lsx_vssran_u_bu_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrain_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrain_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrain_b (ISA_HAS_LSX)
#define HAVE_lsx_vsrains_s_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrains_s_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrains_s_b (ISA_HAS_LSX)
#define HAVE_lsx_vsrains_u_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrains_u_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrains_u_b (ISA_HAS_LSX)
#define HAVE_lsx_vsrarn_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vsrarn_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrarn_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrarn_s_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrarn_s_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrarn_s_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrarn_u_wu_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrarn_u_hu_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrarn_u_bu_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrln_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vsrln_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrln_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrln_u_wu_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrln_u_hu_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrln_u_bu_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrlrn_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vsrlrn_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrlrn_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrn_u_wu_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrn_u_hu_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrn_u_bu_h (ISA_HAS_LSX)
#define HAVE_lsx_vfrstpi_h (ISA_HAS_LSX)
#define HAVE_lsx_vfrstpi_b (ISA_HAS_LSX)
#define HAVE_lsx_vfrstp_h (ISA_HAS_LSX)
#define HAVE_lsx_vfrstp_b (ISA_HAS_LSX)
#define HAVE_lsx_vshuf4i_d (ISA_HAS_LSX)
#define HAVE_lsx_vbsrl_d_f (ISA_HAS_LSX)
#define HAVE_lsx_vbsrl_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vbsrl_d (ISA_HAS_LSX)
#define HAVE_lsx_vbsrl_w (ISA_HAS_LSX)
#define HAVE_lsx_vbsrl_h (ISA_HAS_LSX)
#define HAVE_lsx_vbsrl_b (ISA_HAS_LSX)
#define HAVE_lsx_vbsll_d (ISA_HAS_LSX)
#define HAVE_lsx_vbsll_w (ISA_HAS_LSX)
#define HAVE_lsx_vbsll_h (ISA_HAS_LSX)
#define HAVE_lsx_vbsll_b (ISA_HAS_LSX)
#define HAVE_lsx_vextrins_d (ISA_HAS_LSX)
#define HAVE_lsx_vextrins_w (ISA_HAS_LSX)
#define HAVE_lsx_vextrins_h (ISA_HAS_LSX)
#define HAVE_lsx_vextrins_b (ISA_HAS_LSX)
#define HAVE_lsx_vmskltz_d (ISA_HAS_LSX)
#define HAVE_lsx_vmskltz_w (ISA_HAS_LSX)
#define HAVE_lsx_vmskltz_h (ISA_HAS_LSX)
#define HAVE_lsx_vmskltz_b (ISA_HAS_LSX)
#define HAVE_lsx_vsigncov_d (ISA_HAS_LSX)
#define HAVE_lsx_vsigncov_w (ISA_HAS_LSX)
#define HAVE_lsx_vsigncov_h (ISA_HAS_LSX)
#define HAVE_lsx_vsigncov_b (ISA_HAS_LSX)
#define HAVE_absv2df2 (ISA_HAS_LSX)
#define HAVE_absv4sf2 (ISA_HAS_LSX)
#define HAVE_vfmaddv2df4 (ISA_HAS_LSX)
#define HAVE_vfmaddv4sf4 (ISA_HAS_LSX)
#define HAVE_vfmsubv2df4 (ISA_HAS_LSX)
#define HAVE_vfmsubv4sf4 (ISA_HAS_LSX)
#define HAVE_vfnmsubv2df4_nmsub4 (ISA_HAS_LSX)
#define HAVE_vfnmsubv4sf4_nmsub4 (ISA_HAS_LSX)
#define HAVE_vfnmaddv2df4_nmadd4 (ISA_HAS_LSX)
#define HAVE_vfnmaddv4sf4_nmadd4 (ISA_HAS_LSX)
#define HAVE_lsx_vftintrne_w_s (ISA_HAS_LSX)
#define HAVE_lsx_vftintrne_l_d (ISA_HAS_LSX)
#define HAVE_lsx_vftintrp_w_s (ISA_HAS_LSX)
#define HAVE_lsx_vftintrp_l_d (ISA_HAS_LSX)
#define HAVE_lsx_vftintrm_w_s (ISA_HAS_LSX)
#define HAVE_lsx_vftintrm_l_d (ISA_HAS_LSX)
#define HAVE_lsx_vftint_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vffint_s_l (ISA_HAS_LSX)
#define HAVE_lsx_vftintrz_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vftintrp_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vftintrm_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vftintrne_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vftinth_l_s (ISA_HAS_LSX)
#define HAVE_lsx_vftintl_l_s (ISA_HAS_LSX)
#define HAVE_lsx_vffinth_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vffintl_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vftintrzh_l_s (ISA_HAS_LSX)
#define HAVE_lsx_vftintrzl_l_s (ISA_HAS_LSX)
#define HAVE_lsx_vftintrph_l_s (ISA_HAS_LSX)
#define HAVE_lsx_vftintrpl_l_s (ISA_HAS_LSX)
#define HAVE_lsx_vftintrmh_l_s (ISA_HAS_LSX)
#define HAVE_lsx_vftintrml_l_s (ISA_HAS_LSX)
#define HAVE_lsx_vftintrneh_l_s (ISA_HAS_LSX)
#define HAVE_lsx_vftintrnel_l_s (ISA_HAS_LSX)
#define HAVE_lsx_vfrintrne_s (ISA_HAS_LSX)
#define HAVE_lsx_vfrintrne_d (ISA_HAS_LSX)
#define HAVE_lsx_vfrintrz_s (ISA_HAS_LSX)
#define HAVE_lsx_vfrintrz_d (ISA_HAS_LSX)
#define HAVE_lsx_vfrintrp_s (ISA_HAS_LSX)
#define HAVE_lsx_vfrintrp_d (ISA_HAS_LSX)
#define HAVE_lsx_vfrintrm_s (ISA_HAS_LSX)
#define HAVE_lsx_vfrintrm_d (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_d_f_insn (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_w_f_insn (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_d_insn (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_w_insn (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_h_insn (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_b_insn (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_d_f_insn_0 (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_w_f_insn_0 (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_d_insn_0 (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_w_insn_0 (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_h_insn_0 (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_b_insn_0 (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_d_f_insn (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_w_f_insn (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_d_insn (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_w_insn (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_h_insn (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_b_insn (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_d_f_insn_0 (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_w_f_insn_0 (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_d_insn_0 (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_w_insn_0 (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_h_insn_0 (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_b_insn_0 (ISA_HAS_LSX)
#define HAVE_lsx_vssrln_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrln_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrln_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrn_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrn_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrn_b_h (ISA_HAS_LSX)
#define HAVE_vornv2di3 (ISA_HAS_LSX)
#define HAVE_vornv4si3 (ISA_HAS_LSX)
#define HAVE_vornv8hi3 (ISA_HAS_LSX)
#define HAVE_vornv16qi3 (ISA_HAS_LSX)
#define HAVE_lsx_vldi (ISA_HAS_LSX)
#define HAVE_lsx_vshuf_b (ISA_HAS_LSX)
#define HAVE_lsx_vldx (ISA_HAS_LSX)
#define HAVE_lsx_vstx (ISA_HAS_LSX)
#define HAVE_lsx_vextl_qu_du (ISA_HAS_LSX)
#define HAVE_lsx_vseteqz_v (ISA_HAS_LSX)
#define HAVE_lsx_vaddwev_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vaddwev_d_wu (ISA_HAS_LSX)
#define HAVE_lsx_vsubwev_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vsubwev_d_wu (ISA_HAS_LSX)
#define HAVE_lsx_vmulwev_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vmulwev_d_wu (ISA_HAS_LSX)
#define HAVE_lsx_vaddwev_w_h (ISA_HAS_LSX)
#define HAVE_lsx_vaddwev_w_hu (ISA_HAS_LSX)
#define HAVE_lsx_vsubwev_w_h (ISA_HAS_LSX)
#define HAVE_lsx_vsubwev_w_hu (ISA_HAS_LSX)
#define HAVE_lsx_vmulwev_w_h (ISA_HAS_LSX)
#define HAVE_lsx_vmulwev_w_hu (ISA_HAS_LSX)
#define HAVE_lsx_vaddwev_h_b (ISA_HAS_LSX)
#define HAVE_lsx_vaddwev_h_bu (ISA_HAS_LSX)
#define HAVE_lsx_vsubwev_h_b (ISA_HAS_LSX)
#define HAVE_lsx_vsubwev_h_bu (ISA_HAS_LSX)
#define HAVE_lsx_vmulwev_h_b (ISA_HAS_LSX)
#define HAVE_lsx_vmulwev_h_bu (ISA_HAS_LSX)
#define HAVE_lsx_vaddwod_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vaddwod_d_wu (ISA_HAS_LSX)
#define HAVE_lsx_vsubwod_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vsubwod_d_wu (ISA_HAS_LSX)
#define HAVE_lsx_vmulwod_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vmulwod_d_wu (ISA_HAS_LSX)
#define HAVE_lsx_vaddwod_w_h (ISA_HAS_LSX)
#define HAVE_lsx_vaddwod_w_hu (ISA_HAS_LSX)
#define HAVE_lsx_vsubwod_w_h (ISA_HAS_LSX)
#define HAVE_lsx_vsubwod_w_hu (ISA_HAS_LSX)
#define HAVE_lsx_vmulwod_w_h (ISA_HAS_LSX)
#define HAVE_lsx_vmulwod_w_hu (ISA_HAS_LSX)
#define HAVE_lsx_vaddwod_h_b (ISA_HAS_LSX)
#define HAVE_lsx_vaddwod_h_bu (ISA_HAS_LSX)
#define HAVE_lsx_vsubwod_h_b (ISA_HAS_LSX)
#define HAVE_lsx_vsubwod_h_bu (ISA_HAS_LSX)
#define HAVE_lsx_vmulwod_h_b (ISA_HAS_LSX)
#define HAVE_lsx_vmulwod_h_bu (ISA_HAS_LSX)
#define HAVE_lsx_vaddwev_d_wu_w (ISA_HAS_LSX)
#define HAVE_lsx_vmulwev_d_wu_w (ISA_HAS_LSX)
#define HAVE_lsx_vaddwev_w_hu_h (ISA_HAS_LSX)
#define HAVE_lsx_vmulwev_w_hu_h (ISA_HAS_LSX)
#define HAVE_lsx_vaddwev_h_bu_b (ISA_HAS_LSX)
#define HAVE_lsx_vmulwev_h_bu_b (ISA_HAS_LSX)
#define HAVE_lsx_vaddwod_d_wu_w (ISA_HAS_LSX)
#define HAVE_lsx_vmulwod_d_wu_w (ISA_HAS_LSX)
#define HAVE_lsx_vaddwod_w_hu_h (ISA_HAS_LSX)
#define HAVE_lsx_vmulwod_w_hu_h (ISA_HAS_LSX)
#define HAVE_lsx_vaddwod_h_bu_b (ISA_HAS_LSX)
#define HAVE_lsx_vmulwod_h_bu_b (ISA_HAS_LSX)
#define HAVE_lsx_vaddwev_q_d (ISA_HAS_LSX)
#define HAVE_lsx_vaddwev_q_du (ISA_HAS_LSX)
#define HAVE_lsx_vaddwod_q_d (ISA_HAS_LSX)
#define HAVE_lsx_vaddwod_q_du (ISA_HAS_LSX)
#define HAVE_lsx_vsubwev_q_d (ISA_HAS_LSX)
#define HAVE_lsx_vsubwev_q_du (ISA_HAS_LSX)
#define HAVE_lsx_vsubwod_q_d (ISA_HAS_LSX)
#define HAVE_lsx_vsubwod_q_du (ISA_HAS_LSX)
#define HAVE_lsx_vaddwev_q_du_d (ISA_HAS_LSX)
#define HAVE_lsx_vaddwod_q_du_d (ISA_HAS_LSX)
#define HAVE_lsx_vmulwev_q_du_d (ISA_HAS_LSX)
#define HAVE_lsx_vmulwod_q_du_d (ISA_HAS_LSX)
#define HAVE_lsx_vmulwev_q_d (ISA_HAS_LSX)
#define HAVE_lsx_vmulwev_q_du (ISA_HAS_LSX)
#define HAVE_lsx_vmulwod_q_d (ISA_HAS_LSX)
#define HAVE_lsx_vmulwod_q_du (ISA_HAS_LSX)
#define HAVE_lsx_vhaddw_q_d (ISA_HAS_LSX)
#define HAVE_lsx_vhaddw_qu_du (ISA_HAS_LSX)
#define HAVE_lsx_vhsubw_q_d (ISA_HAS_LSX)
#define HAVE_lsx_vhsubw_qu_du (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwev_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwev_d_wu (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwev_w_h (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwev_w_hu (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwev_h_b (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwev_h_bu (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwod_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwod_d_wu (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwod_w_h (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwod_w_hu (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwod_h_b (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwod_h_bu (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwev_d_wu_w (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwev_w_hu_h (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwev_h_bu_b (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwod_d_wu_w (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwod_w_hu_h (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwod_h_bu_b (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwev_q_d (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwod_q_d (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwev_q_du (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwod_q_du (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwev_q_du_d (ISA_HAS_LSX)
#define HAVE_lsx_vmaddwod_q_du_d (ISA_HAS_LSX)
#define HAVE_lsx_vrotr_d (ISA_HAS_LSX)
#define HAVE_lsx_vrotr_w (ISA_HAS_LSX)
#define HAVE_lsx_vrotr_h (ISA_HAS_LSX)
#define HAVE_lsx_vrotr_b (ISA_HAS_LSX)
#define HAVE_lsx_vadd_q (ISA_HAS_LSX)
#define HAVE_lsx_vsub_q (ISA_HAS_LSX)
#define HAVE_lsx_vmskgez_b (ISA_HAS_LSX)
#define HAVE_lsx_vmsknz_b (ISA_HAS_LSX)
#define HAVE_lsx_vexth_h_b (ISA_HAS_LSX)
#define HAVE_lsx_vexth_hu_bu (ISA_HAS_LSX)
#define HAVE_lsx_vexth_w_h (ISA_HAS_LSX)
#define HAVE_lsx_vexth_wu_hu (ISA_HAS_LSX)
#define HAVE_lsx_vexth_d_w (ISA_HAS_LSX)
#define HAVE_lsx_vexth_du_wu (ISA_HAS_LSX)
#define HAVE_lsx_vexth_q_d (ISA_HAS_LSX)
#define HAVE_lsx_vexth_qu_du (ISA_HAS_LSX)
#define HAVE_lsx_vrotri_d (ISA_HAS_LSX)
#define HAVE_lsx_vrotri_w (ISA_HAS_LSX)
#define HAVE_lsx_vrotri_h (ISA_HAS_LSX)
#define HAVE_lsx_vrotri_b (ISA_HAS_LSX)
#define HAVE_lsx_vextl_q_d (ISA_HAS_LSX)
#define HAVE_lsx_vsrlni_d_q (ISA_HAS_LSX)
#define HAVE_lsx_vsrlni_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vsrlni_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrlni_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrlrni_d_q (ISA_HAS_LSX)
#define HAVE_lsx_vsrlrni_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vsrlrni_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrlrni_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrlni_d_q (ISA_HAS_LSX)
#define HAVE_lsx_vssrlni_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrlni_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrlni_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrlni_du_q (ISA_HAS_LSX)
#define HAVE_lsx_vssrlni_wu_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrlni_hu_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrlni_bu_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrni_d_q (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrni_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrni_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrni_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrni_du_q (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrni_wu_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrni_hu_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrlrni_bu_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrani_d_q (ISA_HAS_LSX)
#define HAVE_lsx_vsrani_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vsrani_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrani_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vsrarni_d_q (ISA_HAS_LSX)
#define HAVE_lsx_vsrarni_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vsrarni_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vsrarni_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrani_d_q (ISA_HAS_LSX)
#define HAVE_lsx_vssrani_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrani_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrani_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrani_du_q (ISA_HAS_LSX)
#define HAVE_lsx_vssrani_wu_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrani_hu_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrani_bu_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrarni_d_q (ISA_HAS_LSX)
#define HAVE_lsx_vssrarni_w_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrarni_h_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrarni_b_h (ISA_HAS_LSX)
#define HAVE_lsx_vssrarni_du_q (ISA_HAS_LSX)
#define HAVE_lsx_vssrarni_wu_d (ISA_HAS_LSX)
#define HAVE_lsx_vssrarni_hu_w (ISA_HAS_LSX)
#define HAVE_lsx_vssrarni_bu_h (ISA_HAS_LSX)
#define HAVE_lsx_vpermi_w (ISA_HAS_LSX)
#define HAVE_vec_pack_trunc_v4di (ISA_HAS_LASX)
#define HAVE_vec_pack_trunc_v8si (ISA_HAS_LASX)
#define HAVE_vec_pack_trunc_v16hi (ISA_HAS_LASX)
#define HAVE_lasx_xvinsgr2vr_d (ISA_HAS_LASX)
#define HAVE_lasx_xvinsgr2vr_w (ISA_HAS_LASX)
#define HAVE_vec_concatv4di (ISA_HAS_LASX)
#define HAVE_vec_concatv8si (ISA_HAS_LASX)
#define HAVE_vec_concatv16hi (ISA_HAS_LASX)
#define HAVE_vec_concatv32qi (ISA_HAS_LASX)
#define HAVE_vec_concatv4df (ISA_HAS_LASX)
#define HAVE_vec_concatv8sf (ISA_HAS_LASX)
#define HAVE_lasx_xvperm_w (ISA_HAS_LASX)
#define HAVE_lasx_xvperm_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_d_v4df (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_d_v8sf (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_d_v4di (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_d_v8si (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_d_v16hi (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_d_v32qi (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_d_v4di_1 (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_d_v4df_1 (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_q_v4df (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_q_v8sf (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_q_v4di (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_q_v8si (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_q_v16hi (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_q_v32qi (ISA_HAS_LASX)
#define HAVE_lasx_xvpickve2gr_d (ISA_HAS_LASX)
#define HAVE_lasx_xvpickve2gr_du (ISA_HAS_LASX)
#define HAVE_movv4df_lasx (ISA_HAS_LASX)
#define HAVE_movv8sf_lasx (ISA_HAS_LASX)
#define HAVE_movv4di_lasx (ISA_HAS_LASX)
#define HAVE_movv8si_lasx (ISA_HAS_LASX)
#define HAVE_movv16hi_lasx (ISA_HAS_LASX)
#define HAVE_movv32qi_lasx (ISA_HAS_LASX)
#define HAVE_addv4di3 (ISA_HAS_LASX)
#define HAVE_addv8si3 (ISA_HAS_LASX)
#define HAVE_addv16hi3 (ISA_HAS_LASX)
#define HAVE_addv32qi3 (ISA_HAS_LASX)
#define HAVE_subv4di3 (ISA_HAS_LASX)
#define HAVE_subv8si3 (ISA_HAS_LASX)
#define HAVE_subv16hi3 (ISA_HAS_LASX)
#define HAVE_subv32qi3 (ISA_HAS_LASX)
#define HAVE_mulv4di3 (ISA_HAS_LASX)
#define HAVE_mulv8si3 (ISA_HAS_LASX)
#define HAVE_mulv16hi3 (ISA_HAS_LASX)
#define HAVE_mulv32qi3 (ISA_HAS_LASX)
#define HAVE_lasx_xvmadd_d (ISA_HAS_LASX)
#define HAVE_lasx_xvmadd_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmadd_h (ISA_HAS_LASX)
#define HAVE_lasx_xvmadd_b (ISA_HAS_LASX)
#define HAVE_lasx_xvmsub_d (ISA_HAS_LASX)
#define HAVE_lasx_xvmsub_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmsub_h (ISA_HAS_LASX)
#define HAVE_lasx_xvmsub_b (ISA_HAS_LASX)
#define HAVE_divv4di3 (ISA_HAS_LASX)
#define HAVE_divv8si3 (ISA_HAS_LASX)
#define HAVE_divv16hi3 (ISA_HAS_LASX)
#define HAVE_divv32qi3 (ISA_HAS_LASX)
#define HAVE_udivv4di3 (ISA_HAS_LASX)
#define HAVE_udivv8si3 (ISA_HAS_LASX)
#define HAVE_udivv16hi3 (ISA_HAS_LASX)
#define HAVE_udivv32qi3 (ISA_HAS_LASX)
#define HAVE_modv4di3 (ISA_HAS_LASX)
#define HAVE_modv8si3 (ISA_HAS_LASX)
#define HAVE_modv16hi3 (ISA_HAS_LASX)
#define HAVE_modv32qi3 (ISA_HAS_LASX)
#define HAVE_umodv4di3 (ISA_HAS_LASX)
#define HAVE_umodv8si3 (ISA_HAS_LASX)
#define HAVE_umodv16hi3 (ISA_HAS_LASX)
#define HAVE_umodv32qi3 (ISA_HAS_LASX)
#define HAVE_xorv4di3 (ISA_HAS_LASX)
#define HAVE_xorv8si3 (ISA_HAS_LASX)
#define HAVE_xorv16hi3 (ISA_HAS_LASX)
#define HAVE_xorv32qi3 (ISA_HAS_LASX)
#define HAVE_iorv4df3 (ISA_HAS_LASX)
#define HAVE_iorv8sf3 (ISA_HAS_LASX)
#define HAVE_iorv4di3 (ISA_HAS_LASX)
#define HAVE_iorv8si3 (ISA_HAS_LASX)
#define HAVE_iorv16hi3 (ISA_HAS_LASX)
#define HAVE_iorv32qi3 (ISA_HAS_LASX)
#define HAVE_andv4df3 (ISA_HAS_LASX)
#define HAVE_andv8sf3 (ISA_HAS_LASX)
#define HAVE_andv4di3 (ISA_HAS_LASX)
#define HAVE_andv8si3 (ISA_HAS_LASX)
#define HAVE_andv16hi3 (ISA_HAS_LASX)
#define HAVE_andv32qi3 (ISA_HAS_LASX)
#define HAVE_one_cmplv4di2 (ISA_HAS_LASX)
#define HAVE_one_cmplv8si2 (ISA_HAS_LASX)
#define HAVE_one_cmplv16hi2 (ISA_HAS_LASX)
#define HAVE_one_cmplv32qi2 (ISA_HAS_LASX)
#define HAVE_vlshrv4di3 (ISA_HAS_LASX)
#define HAVE_vlshrv8si3 (ISA_HAS_LASX)
#define HAVE_vlshrv16hi3 (ISA_HAS_LASX)
#define HAVE_vlshrv32qi3 (ISA_HAS_LASX)
#define HAVE_vashrv4di3 (ISA_HAS_LASX)
#define HAVE_vashrv8si3 (ISA_HAS_LASX)
#define HAVE_vashrv16hi3 (ISA_HAS_LASX)
#define HAVE_vashrv32qi3 (ISA_HAS_LASX)
#define HAVE_vashlv4di3 (ISA_HAS_LASX)
#define HAVE_vashlv8si3 (ISA_HAS_LASX)
#define HAVE_vashlv16hi3 (ISA_HAS_LASX)
#define HAVE_vashlv32qi3 (ISA_HAS_LASX)
#define HAVE_addv4df3 (ISA_HAS_LASX)
#define HAVE_addv8sf3 (ISA_HAS_LASX)
#define HAVE_subv4df3 (ISA_HAS_LASX)
#define HAVE_subv8sf3 (ISA_HAS_LASX)
#define HAVE_mulv4df3 (ISA_HAS_LASX)
#define HAVE_mulv8sf3 (ISA_HAS_LASX)
#define HAVE_divv4df3 (ISA_HAS_LASX)
#define HAVE_divv8sf3 (ISA_HAS_LASX)
#define HAVE_fmav4df4 (ISA_HAS_LASX)
#define HAVE_fmav8sf4 (ISA_HAS_LASX)
#define HAVE_fnmav4df4 (ISA_HAS_LASX)
#define HAVE_fnmav8sf4 (ISA_HAS_LASX)
#define HAVE_sqrtv4df2 (ISA_HAS_LASX)
#define HAVE_sqrtv8sf2 (ISA_HAS_LASX)
#define HAVE_lasx_xvadda_d (ISA_HAS_LASX)
#define HAVE_lasx_xvadda_w (ISA_HAS_LASX)
#define HAVE_lasx_xvadda_h (ISA_HAS_LASX)
#define HAVE_lasx_xvadda_b (ISA_HAS_LASX)
#define HAVE_ssaddv4di3 (ISA_HAS_LASX)
#define HAVE_ssaddv8si3 (ISA_HAS_LASX)
#define HAVE_ssaddv16hi3 (ISA_HAS_LASX)
#define HAVE_ssaddv32qi3 (ISA_HAS_LASX)
#define HAVE_usaddv4di3 (ISA_HAS_LASX)
#define HAVE_usaddv8si3 (ISA_HAS_LASX)
#define HAVE_usaddv16hi3 (ISA_HAS_LASX)
#define HAVE_usaddv32qi3 (ISA_HAS_LASX)
#define HAVE_lasx_xvabsd_s_d (ISA_HAS_LASX)
#define HAVE_lasx_xvabsd_s_w (ISA_HAS_LASX)
#define HAVE_lasx_xvabsd_s_h (ISA_HAS_LASX)
#define HAVE_lasx_xvabsd_s_b (ISA_HAS_LASX)
#define HAVE_lasx_xvabsd_u_du (ISA_HAS_LASX)
#define HAVE_lasx_xvabsd_u_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvabsd_u_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvabsd_u_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvavg_s_d (ISA_HAS_LASX)
#define HAVE_lasx_xvavg_s_w (ISA_HAS_LASX)
#define HAVE_lasx_xvavg_s_h (ISA_HAS_LASX)
#define HAVE_lasx_xvavg_s_b (ISA_HAS_LASX)
#define HAVE_lasx_xvavg_u_du (ISA_HAS_LASX)
#define HAVE_lasx_xvavg_u_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvavg_u_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvavg_u_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvavgr_s_d (ISA_HAS_LASX)
#define HAVE_lasx_xvavgr_s_w (ISA_HAS_LASX)
#define HAVE_lasx_xvavgr_s_h (ISA_HAS_LASX)
#define HAVE_lasx_xvavgr_s_b (ISA_HAS_LASX)
#define HAVE_lasx_xvavgr_u_du (ISA_HAS_LASX)
#define HAVE_lasx_xvavgr_u_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvavgr_u_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvavgr_u_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvbitclr_d (ISA_HAS_LASX)
#define HAVE_lasx_xvbitclr_w (ISA_HAS_LASX)
#define HAVE_lasx_xvbitclr_h (ISA_HAS_LASX)
#define HAVE_lasx_xvbitclr_b (ISA_HAS_LASX)
#define HAVE_lasx_xvbitclri_d (ISA_HAS_LASX)
#define HAVE_lasx_xvbitclri_w (ISA_HAS_LASX)
#define HAVE_lasx_xvbitclri_h (ISA_HAS_LASX)
#define HAVE_lasx_xvbitclri_b (ISA_HAS_LASX)
#define HAVE_lasx_xvbitrev_d (ISA_HAS_LASX)
#define HAVE_lasx_xvbitrev_w (ISA_HAS_LASX)
#define HAVE_lasx_xvbitrev_h (ISA_HAS_LASX)
#define HAVE_lasx_xvbitrev_b (ISA_HAS_LASX)
#define HAVE_lasx_xvbitrevi_d (ISA_HAS_LASX)
#define HAVE_lasx_xvbitrevi_w (ISA_HAS_LASX)
#define HAVE_lasx_xvbitrevi_h (ISA_HAS_LASX)
#define HAVE_lasx_xvbitrevi_b (ISA_HAS_LASX)
#define HAVE_lasx_xvbitsel_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xvbitsel_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvbitsel_d (ISA_HAS_LASX)
#define HAVE_lasx_xvbitsel_w (ISA_HAS_LASX)
#define HAVE_lasx_xvbitsel_h (ISA_HAS_LASX)
#define HAVE_lasx_xvbitsel_b (ISA_HAS_LASX)
#define HAVE_lasx_xvbitseli_b (ISA_HAS_LASX)
#define HAVE_lasx_xvbitset_d (ISA_HAS_LASX)
#define HAVE_lasx_xvbitset_w (ISA_HAS_LASX)
#define HAVE_lasx_xvbitset_h (ISA_HAS_LASX)
#define HAVE_lasx_xvbitset_b (ISA_HAS_LASX)
#define HAVE_lasx_xvbitseti_d (ISA_HAS_LASX)
#define HAVE_lasx_xvbitseti_w (ISA_HAS_LASX)
#define HAVE_lasx_xvbitseti_h (ISA_HAS_LASX)
#define HAVE_lasx_xvbitseti_b (ISA_HAS_LASX)
#define HAVE_lasx_xvseq_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsle_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsle_du (ISA_HAS_LASX)
#define HAVE_lasx_xvslt_d (ISA_HAS_LASX)
#define HAVE_lasx_xvslt_du (ISA_HAS_LASX)
#define HAVE_lasx_xvseq_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsle_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsle_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvslt_w (ISA_HAS_LASX)
#define HAVE_lasx_xvslt_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvseq_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsle_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsle_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvslt_h (ISA_HAS_LASX)
#define HAVE_lasx_xvslt_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvseq_b (ISA_HAS_LASX)
#define HAVE_lasx_xvsle_b (ISA_HAS_LASX)
#define HAVE_lasx_xvsle_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvslt_b (ISA_HAS_LASX)
#define HAVE_lasx_xvslt_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvfclass_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfclass_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_caf_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_caf_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cune_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cune_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cun_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cor_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_ceq_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cne_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cle_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_clt_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cueq_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cule_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cult_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cun_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cor_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_ceq_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cne_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cle_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_clt_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cueq_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cule_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_cult_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_saf_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sun_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sor_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_seq_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sne_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sueq_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sune_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sule_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sult_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sle_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_slt_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_saf_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sun_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sor_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_seq_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sne_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sueq_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sune_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sule_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sult_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_sle_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcmp_slt_s (ISA_HAS_LASX)
#define HAVE_floatv4div4df2 (ISA_HAS_LASX)
#define HAVE_floatv8siv8sf2 (ISA_HAS_LASX)
#define HAVE_floatunsv4div4df2 (ISA_HAS_LASX)
#define HAVE_floatunsv8siv8sf2 (ISA_HAS_LASX)
#define HAVE_lasx_xvreplgr2vr_d (ISA_HAS_LASX)
#define HAVE_lasx_xvreplgr2vr_w (ISA_HAS_LASX)
#define HAVE_lasx_xvreplgr2vr_h (ISA_HAS_LASX)
#define HAVE_lasx_xvreplgr2vr_b (ISA_HAS_LASX)
#define HAVE_logbv4df2 (ISA_HAS_LASX)
#define HAVE_logbv8sf2 (ISA_HAS_LASX)
#define HAVE_smaxv4df3 (ISA_HAS_LASX)
#define HAVE_smaxv8sf3 (ISA_HAS_LASX)
#define HAVE_lasx_xvfmaxa_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfmaxa_s (ISA_HAS_LASX)
#define HAVE_sminv4df3 (ISA_HAS_LASX)
#define HAVE_sminv8sf3 (ISA_HAS_LASX)
#define HAVE_lasx_xvfmina_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfmina_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfrecip_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfrecip_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfrint_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfrint_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfrsqrt_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfrsqrt_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftint_s_l_d (ISA_HAS_LASX)
#define HAVE_lasx_xvftint_s_w_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftint_u_lu_d (ISA_HAS_LASX)
#define HAVE_lasx_xvftint_u_wu_s (ISA_HAS_LASX)
#define HAVE_fix_truncv4dfv4di2 (ISA_HAS_LASX)
#define HAVE_fix_truncv8sfv8si2 (ISA_HAS_LASX)
#define HAVE_fixuns_truncv4dfv4di2 (ISA_HAS_LASX)
#define HAVE_fixuns_truncv8sfv8si2 (ISA_HAS_LASX)
#define HAVE_lasx_xvhaddw_h_b (ISA_HAS_LASX)
#define HAVE_lasx_xvhaddw_hu_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvhsubw_h_b (ISA_HAS_LASX)
#define HAVE_lasx_xvhsubw_hu_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvhaddw_w_h (ISA_HAS_LASX)
#define HAVE_lasx_xvhaddw_wu_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvhsubw_w_h (ISA_HAS_LASX)
#define HAVE_lasx_xvhsubw_wu_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvhaddw_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvhaddw_du_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvhsubw_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvhsubw_du_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvpackev_b (ISA_HAS_LASX)
#define HAVE_lasx_xvpackev_h (ISA_HAS_LASX)
#define HAVE_lasx_xvpackev_w (ISA_HAS_LASX)
#define HAVE_lasx_xvpackev_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvilvh_b (ISA_HAS_LASX)
#define HAVE_lasx_xvilvh_h (ISA_HAS_LASX)
#define HAVE_lasx_xvilvh_w (ISA_HAS_LASX)
#define HAVE_lasx_xvilvh_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvilvh_d (ISA_HAS_LASX)
#define HAVE_lasx_xvilvh_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xvpackod_b (ISA_HAS_LASX)
#define HAVE_lasx_xvpackod_h (ISA_HAS_LASX)
#define HAVE_lasx_xvpackod_w (ISA_HAS_LASX)
#define HAVE_lasx_xvpackod_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvilvl_b (ISA_HAS_LASX)
#define HAVE_lasx_xvilvl_h (ISA_HAS_LASX)
#define HAVE_lasx_xvilvl_w (ISA_HAS_LASX)
#define HAVE_lasx_xvilvl_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvilvl_d (ISA_HAS_LASX)
#define HAVE_lasx_xvilvl_d_f (ISA_HAS_LASX)
#define HAVE_smaxv4di3 (ISA_HAS_LASX)
#define HAVE_smaxv8si3 (ISA_HAS_LASX)
#define HAVE_smaxv16hi3 (ISA_HAS_LASX)
#define HAVE_smaxv32qi3 (ISA_HAS_LASX)
#define HAVE_umaxv4di3 (ISA_HAS_LASX)
#define HAVE_umaxv8si3 (ISA_HAS_LASX)
#define HAVE_umaxv16hi3 (ISA_HAS_LASX)
#define HAVE_umaxv32qi3 (ISA_HAS_LASX)
#define HAVE_sminv4di3 (ISA_HAS_LASX)
#define HAVE_sminv8si3 (ISA_HAS_LASX)
#define HAVE_sminv16hi3 (ISA_HAS_LASX)
#define HAVE_sminv32qi3 (ISA_HAS_LASX)
#define HAVE_uminv4di3 (ISA_HAS_LASX)
#define HAVE_uminv8si3 (ISA_HAS_LASX)
#define HAVE_uminv16hi3 (ISA_HAS_LASX)
#define HAVE_uminv32qi3 (ISA_HAS_LASX)
#define HAVE_lasx_xvclo_d (ISA_HAS_LASX)
#define HAVE_lasx_xvclo_w (ISA_HAS_LASX)
#define HAVE_lasx_xvclo_h (ISA_HAS_LASX)
#define HAVE_lasx_xvclo_b (ISA_HAS_LASX)
#define HAVE_clzv4di2 (ISA_HAS_LASX)
#define HAVE_clzv8si2 (ISA_HAS_LASX)
#define HAVE_clzv16hi2 (ISA_HAS_LASX)
#define HAVE_clzv32qi2 (ISA_HAS_LASX)
#define HAVE_lasx_xvnor_d (ISA_HAS_LASX)
#define HAVE_lasx_xvnor_w (ISA_HAS_LASX)
#define HAVE_lasx_xvnor_h (ISA_HAS_LASX)
#define HAVE_lasx_xvnor_b (ISA_HAS_LASX)
#define HAVE_lasx_xvpickev_b (ISA_HAS_LASX)
#define HAVE_lasx_xvpickev_h (ISA_HAS_LASX)
#define HAVE_lasx_xvpickev_w (ISA_HAS_LASX)
#define HAVE_lasx_xvpickev_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvpickod_b (ISA_HAS_LASX)
#define HAVE_lasx_xvpickod_h (ISA_HAS_LASX)
#define HAVE_lasx_xvpickod_w (ISA_HAS_LASX)
#define HAVE_lasx_xvpickod_w_f (ISA_HAS_LASX)
#define HAVE_popcountv4di2 (ISA_HAS_LASX)
#define HAVE_popcountv8si2 (ISA_HAS_LASX)
#define HAVE_popcountv16hi2 (ISA_HAS_LASX)
#define HAVE_popcountv32qi2 (ISA_HAS_LASX)
#define HAVE_lasx_xvsat_s_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsat_s_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsat_s_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsat_s_b (ISA_HAS_LASX)
#define HAVE_lasx_xvsat_u_du (ISA_HAS_LASX)
#define HAVE_lasx_xvsat_u_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvsat_u_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvsat_u_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvshuf4i_w (ISA_HAS_LASX)
#define HAVE_lasx_xvshuf4i_h (ISA_HAS_LASX)
#define HAVE_lasx_xvshuf4i_b (ISA_HAS_LASX)
#define HAVE_lasx_xvshuf4i_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvshuf4i_w_1 (ISA_HAS_LASX \
   && INTVAL (operands[2]) + 4 == INTVAL (operands[6]) \
   && INTVAL (operands[3]) + 4 == INTVAL (operands[7]) \
   && INTVAL (operands[4]) + 4 == INTVAL (operands[8]) \
   && INTVAL (operands[5]) + 4 == INTVAL (operands[9]))
#define HAVE_lasx_xvshuf4i_w_f_1 (ISA_HAS_LASX \
   && INTVAL (operands[2]) + 4 == INTVAL (operands[6]) \
   && INTVAL (operands[3]) + 4 == INTVAL (operands[7]) \
   && INTVAL (operands[4]) + 4 == INTVAL (operands[8]) \
   && INTVAL (operands[5]) + 4 == INTVAL (operands[9]))
#define HAVE_lasx_xvsrar_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsrar_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsrar_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsrar_b (ISA_HAS_LASX)
#define HAVE_lasx_xvsrari_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsrari_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsrari_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsrari_b (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlr_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlr_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlr_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlr_b (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlri_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlri_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlri_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlri_b (ISA_HAS_LASX)
#define HAVE_lasx_xvssub_s_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssub_s_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssub_s_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssub_s_b (ISA_HAS_LASX)
#define HAVE_lasx_xvssub_u_du (ISA_HAS_LASX)
#define HAVE_lasx_xvssub_u_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvssub_u_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvssub_u_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvshuf_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xvshuf_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvshuf_d (ISA_HAS_LASX)
#define HAVE_lasx_xvshuf_w (ISA_HAS_LASX)
#define HAVE_lasx_xvshuf_h (ISA_HAS_LASX)
#define HAVE_lasx_xvshuf_b (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve0_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve0_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve0_d (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve0_w (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve0_h (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve0_b (ISA_HAS_LASX)
#define HAVE_lasx_xvrepl128vei_b_internal (ISA_HAS_LASX && ((INTVAL (operands[3]) - INTVAL (operands[2])) == 16))
#define HAVE_lasx_xvrepl128vei_h_internal (ISA_HAS_LASX && ((INTVAL (operands[3]) - INTVAL (operands[2])) == 8))
#define HAVE_lasx_xvrepl128vei_w_internal (ISA_HAS_LASX && ((INTVAL (operands[3]) - INTVAL (operands[2])) == 4))
#define HAVE_lasx_xvrepl128vei_d_internal (ISA_HAS_LASX && ((INTVAL (operands[3]) - INTVAL (operands[2])) == 2))
#define HAVE_lasx_xvrepl128vei_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xvrepl128vei_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvrepl128vei_d (ISA_HAS_LASX)
#define HAVE_lasx_xvrepl128vei_w (ISA_HAS_LASX)
#define HAVE_lasx_xvrepl128vei_h (ISA_HAS_LASX)
#define HAVE_lasx_xvrepl128vei_b (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve0_d_f_scalar (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve0_w_f_scalar (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve0_q (ISA_HAS_LASX)
#define HAVE_lasx_xvfcvt_h_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcvt_s_d (ISA_HAS_LASX)
#define HAVE_vec_pack_trunc_v4df (ISA_HAS_LASX)
#define HAVE_lasx_xvfcvth_s_h (ISA_HAS_LASX)
#define HAVE_lasx_xvfcvth_d_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcvth_d_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvfcvtl_s_h (ISA_HAS_LASX)
#define HAVE_lasx_xvfcvtl_d_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfcvtl_d_insn (ISA_HAS_LASX)
#define HAVE_lasx_xbz_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xbnz_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xbz_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xbnz_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xbz_d (ISA_HAS_LASX)
#define HAVE_lasx_xbnz_d (ISA_HAS_LASX)
#define HAVE_lasx_xbz_w (ISA_HAS_LASX)
#define HAVE_lasx_xbnz_w (ISA_HAS_LASX)
#define HAVE_lasx_xbz_h (ISA_HAS_LASX)
#define HAVE_lasx_xbnz_h (ISA_HAS_LASX)
#define HAVE_lasx_xbz_b (ISA_HAS_LASX)
#define HAVE_lasx_xbnz_b (ISA_HAS_LASX)
#define HAVE_lasx_xbz_v_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xbnz_v_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xbz_v_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xbnz_v_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xbz_v_d (ISA_HAS_LASX)
#define HAVE_lasx_xbnz_v_d (ISA_HAS_LASX)
#define HAVE_lasx_xbz_v_w (ISA_HAS_LASX)
#define HAVE_lasx_xbnz_v_w (ISA_HAS_LASX)
#define HAVE_lasx_xbz_v_h (ISA_HAS_LASX)
#define HAVE_lasx_xbnz_v_h (ISA_HAS_LASX)
#define HAVE_lasx_xbz_v_b (ISA_HAS_LASX)
#define HAVE_lasx_xbnz_v_b (ISA_HAS_LASX)
#define HAVE_lasx_vext2xv_h_b (ISA_HAS_LASX)
#define HAVE_lasx_vext2xv_hu_bu (ISA_HAS_LASX)
#define HAVE_lasx_vext2xv_w_h (ISA_HAS_LASX)
#define HAVE_lasx_vext2xv_wu_hu (ISA_HAS_LASX)
#define HAVE_lasx_vext2xv_d_w (ISA_HAS_LASX)
#define HAVE_lasx_vext2xv_du_wu (ISA_HAS_LASX)
#define HAVE_lasx_vext2xv_w_b (ISA_HAS_LASX)
#define HAVE_lasx_vext2xv_wu_bu (ISA_HAS_LASX)
#define HAVE_lasx_vext2xv_d_h (ISA_HAS_LASX)
#define HAVE_lasx_vext2xv_du_hu (ISA_HAS_LASX)
#define HAVE_lasx_vext2xv_d_b (ISA_HAS_LASX)
#define HAVE_lasx_vext2xv_du_bu (ISA_HAS_LASX)
#define HAVE_xvandnv4df3 (ISA_HAS_LASX)
#define HAVE_xvandnv8sf3 (ISA_HAS_LASX)
#define HAVE_xvandnv4di3 (ISA_HAS_LASX)
#define HAVE_xvandnv8si3 (ISA_HAS_LASX)
#define HAVE_xvandnv16hi3 (ISA_HAS_LASX)
#define HAVE_xvandnv32qi3 (ISA_HAS_LASX)
#define HAVE_absv4di2 (ISA_HAS_LASX)
#define HAVE_absv8si2 (ISA_HAS_LASX)
#define HAVE_absv16hi2 (ISA_HAS_LASX)
#define HAVE_absv32qi2 (ISA_HAS_LASX)
#define HAVE_negv4di2 (ISA_HAS_LASX)
#define HAVE_negv8si2 (ISA_HAS_LASX)
#define HAVE_negv16hi2 (ISA_HAS_LASX)
#define HAVE_negv32qi2 (ISA_HAS_LASX)
#define HAVE_lasx_xvmuh_s_d (ISA_HAS_LASX)
#define HAVE_lasx_xvmuh_s_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmuh_s_h (ISA_HAS_LASX)
#define HAVE_lasx_xvmuh_s_b (ISA_HAS_LASX)
#define HAVE_lasx_xvmuh_u_du (ISA_HAS_LASX)
#define HAVE_lasx_xvmuh_u_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvmuh_u_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvmuh_u_bu (ISA_HAS_LASX)
#define HAVE_lasx_mxvextw_u_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsllwil_s_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsllwil_s_w_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsllwil_s_h_b (ISA_HAS_LASX)
#define HAVE_lasx_xvsllwil_u_du_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvsllwil_u_wu_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvsllwil_u_hu_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvsran_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsran_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsran_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssran_s_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssran_s_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssran_s_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssran_u_wu_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssran_u_hu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssran_u_bu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsrarn_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsrarn_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsrarn_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarn_s_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarn_s_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarn_s_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarn_u_wu_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarn_u_hu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarn_u_bu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsrln_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsrln_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsrln_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssrln_u_wu_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrln_u_hu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrln_u_bu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlrn_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlrn_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlrn_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrn_u_wu_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrn_u_hu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrn_u_bu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvfrstpi_h (ISA_HAS_LASX)
#define HAVE_lasx_xvfrstpi_b (ISA_HAS_LASX)
#define HAVE_lasx_xvfrstp_h (ISA_HAS_LASX)
#define HAVE_lasx_xvfrstp_b (ISA_HAS_LASX)
#define HAVE_lasx_xvshuf4i_d (ISA_HAS_LASX)
#define HAVE_lasx_xvbsrl_d (ISA_HAS_LASX)
#define HAVE_lasx_xvbsrl_w (ISA_HAS_LASX)
#define HAVE_lasx_xvbsrl_h (ISA_HAS_LASX)
#define HAVE_lasx_xvbsrl_b (ISA_HAS_LASX)
#define HAVE_lasx_xvbsll_d (ISA_HAS_LASX)
#define HAVE_lasx_xvbsll_w (ISA_HAS_LASX)
#define HAVE_lasx_xvbsll_h (ISA_HAS_LASX)
#define HAVE_lasx_xvbsll_b (ISA_HAS_LASX)
#define HAVE_lasx_xvextrins_d (ISA_HAS_LASX)
#define HAVE_lasx_xvextrins_w (ISA_HAS_LASX)
#define HAVE_lasx_xvextrins_h (ISA_HAS_LASX)
#define HAVE_lasx_xvextrins_b (ISA_HAS_LASX)
#define HAVE_lasx_xvmskltz_d (ISA_HAS_LASX)
#define HAVE_lasx_xvmskltz_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmskltz_h (ISA_HAS_LASX)
#define HAVE_lasx_xvmskltz_b (ISA_HAS_LASX)
#define HAVE_lasx_xvsigncov_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsigncov_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsigncov_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsigncov_b (ISA_HAS_LASX)
#define HAVE_absv4df2 (ISA_HAS_LASX)
#define HAVE_absv8sf2 (ISA_HAS_LASX)
#define HAVE_negv4df2 (ISA_HAS_LASX)
#define HAVE_negv8sf2 (ISA_HAS_LASX)
#define HAVE_xvfmaddv4df4 (ISA_HAS_LASX)
#define HAVE_xvfmaddv8sf4 (ISA_HAS_LASX)
#define HAVE_xvfmsubv4df4 (ISA_HAS_LASX)
#define HAVE_xvfmsubv8sf4 (ISA_HAS_LASX)
#define HAVE_xvfnmsubv4df4_nmsub4 (ISA_HAS_LASX)
#define HAVE_xvfnmsubv8sf4_nmsub4 (ISA_HAS_LASX)
#define HAVE_xvfnmaddv4df4_nmadd4 (ISA_HAS_LASX)
#define HAVE_xvfnmaddv8sf4_nmadd4 (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrne_w_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrne_l_d (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrp_w_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrp_l_d (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrm_w_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrm_l_d (ISA_HAS_LASX)
#define HAVE_lasx_xvftint_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvffint_s_l (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrz_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrp_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrm_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrne_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvftinth_l_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftintl_l_s (ISA_HAS_LASX)
#define HAVE_lasx_xvffinth_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvffintl_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrzh_l_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrzl_l_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrph_l_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrpl_l_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrmh_l_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrml_l_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrneh_l_s (ISA_HAS_LASX)
#define HAVE_lasx_xvftintrnel_l_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfrintrne_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfrintrne_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfrintrz_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfrintrz_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfrintrp_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfrintrp_d (ISA_HAS_LASX)
#define HAVE_lasx_xvfrintrm_s (ISA_HAS_LASX)
#define HAVE_lasx_xvfrintrm_d (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_d_f_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_w_f_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_d_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_w_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_h_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_b_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_d_f_insn_0 (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_w_f_insn_0 (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_d_insn_0 (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_w_insn_0 (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_h_insn_0 (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_b_insn_0 (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwev_h_b (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwev_h_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwev_h_b (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwev_h_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwev_h_b (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwev_h_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwev_w_h (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwev_w_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwev_w_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwev_w_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwev_w_h (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwev_w_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwev_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwev_d_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwev_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwev_d_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwev_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwev_d_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwev_q_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwev_q_d (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwev_q_d (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwod_h_b (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwod_h_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwod_h_b (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwod_h_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwod_h_b (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwod_h_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwod_w_h (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwod_w_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwod_w_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwod_w_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwod_w_h (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwod_w_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwod_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwod_d_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwod_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwod_d_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwod_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwod_d_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwod_q_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwod_q_d (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwod_q_d (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwev_q_du (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwev_q_du (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwev_q_du (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwod_q_du (ISA_HAS_LASX)
#define HAVE_lasx_xvsubwod_q_du (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwod_q_du (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwev_h_bu_b (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwev_h_bu_b (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwev_w_hu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwev_w_hu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwev_d_wu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwev_d_wu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwod_h_bu_b (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwod_h_bu_b (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwod_w_hu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwod_w_hu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwod_d_wu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwod_d_wu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwev_h_b (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwev_h_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwev_w_h (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwev_w_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwev_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwev_d_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwev_q_d (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwod_h_b (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwod_h_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwod_w_h (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwod_w_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwod_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwod_d_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwod_q_d (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwev_q_du (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwod_q_du (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwev_h_bu_b (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwev_w_hu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwev_d_wu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwev_q_du_d (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwod_h_bu_b (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwod_w_hu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwod_d_wu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvmaddwod_q_du_d (ISA_HAS_LASX)
#define HAVE_lasx_xvhaddw_q_d (ISA_HAS_LASX)
#define HAVE_lasx_xvhsubw_q_d (ISA_HAS_LASX)
#define HAVE_lasx_xvhaddw_qu_du (ISA_HAS_LASX)
#define HAVE_lasx_xvhsubw_qu_du (ISA_HAS_LASX)
#define HAVE_lasx_xvrotr_d (ISA_HAS_LASX)
#define HAVE_lasx_xvrotr_w (ISA_HAS_LASX)
#define HAVE_lasx_xvrotr_h (ISA_HAS_LASX)
#define HAVE_lasx_xvrotr_b (ISA_HAS_LASX)
#define HAVE_lasx_xvadd_q (ISA_HAS_LASX)
#define HAVE_lasx_xvsub_q (ISA_HAS_LASX)
#define HAVE_lasx_xvssrln_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrln_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrln_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve_d (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve_w (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve_h (ISA_HAS_LASX)
#define HAVE_lasx_xvreplve_b (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwev_q_du_d (ISA_HAS_LASX)
#define HAVE_lasx_xvaddwod_q_du_d (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwev_q_du_d (ISA_HAS_LASX)
#define HAVE_lasx_xvmulwod_q_du_d (ISA_HAS_LASX)
#define HAVE_lasx_xvpickve2gr_w (ISA_HAS_LASX)
#define HAVE_lasx_xvpickve2gr_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvmskgez_b (ISA_HAS_LASX)
#define HAVE_lasx_xvmsknz_b (ISA_HAS_LASX)
#define HAVE_lasx_xvexth_h_b (ISA_HAS_LASX)
#define HAVE_lasx_xvexth_hu_bu (ISA_HAS_LASX)
#define HAVE_lasx_xvexth_w_h (ISA_HAS_LASX)
#define HAVE_lasx_xvexth_wu_hu (ISA_HAS_LASX)
#define HAVE_lasx_xvexth_d_w (ISA_HAS_LASX)
#define HAVE_lasx_xvexth_du_wu (ISA_HAS_LASX)
#define HAVE_lasx_xvexth_q_d (ISA_HAS_LASX)
#define HAVE_lasx_xvexth_qu_du (ISA_HAS_LASX)
#define HAVE_lasx_xvrotri_d (ISA_HAS_LASX)
#define HAVE_lasx_xvrotri_w (ISA_HAS_LASX)
#define HAVE_lasx_xvrotri_h (ISA_HAS_LASX)
#define HAVE_lasx_xvrotri_b (ISA_HAS_LASX)
#define HAVE_lasx_xvextl_q_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlni_d_q (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlni_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlni_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlni_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlrni_d_q (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlrni_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlrni_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsrlrni_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlni_d_q (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlni_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlni_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlni_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlni_du_q (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlni_wu_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlni_hu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlni_bu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrni_d_q (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrni_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrni_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrni_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrni_du_q (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrni_wu_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrni_hu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrni_bu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsrani_d_q (ISA_HAS_LASX)
#define HAVE_lasx_xvsrani_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsrani_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsrani_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvsrarni_d_q (ISA_HAS_LASX)
#define HAVE_lasx_xvsrarni_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvsrarni_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvsrarni_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssrani_d_q (ISA_HAS_LASX)
#define HAVE_lasx_xvssrani_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrani_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrani_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssrani_du_q (ISA_HAS_LASX)
#define HAVE_lasx_xvssrani_wu_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrani_hu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrani_bu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarni_d_q (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarni_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarni_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarni_b_h (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarni_du_q (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarni_wu_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarni_hu_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrarni_bu_h (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_w (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvpermi_w_1 (ISA_HAS_LASX \
  && INTVAL (operands[3]) + 4 == INTVAL (operands[7]) \
  && INTVAL (operands[4]) + 4 == INTVAL (operands[8]) \
  && INTVAL (operands[5]) + 4 == INTVAL (operands[9]) \
  && INTVAL (operands[6]) + 4 == INTVAL (operands[10]))
#define HAVE_lasx_xvpermi_w_f_1 (ISA_HAS_LASX \
  && INTVAL (operands[3]) + 4 == INTVAL (operands[7]) \
  && INTVAL (operands[4]) + 4 == INTVAL (operands[8]) \
  && INTVAL (operands[5]) + 4 == INTVAL (operands[9]) \
  && INTVAL (operands[6]) + 4 == INTVAL (operands[10]))
#define HAVE_lasx_xvstelm_d_f_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_w_f_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_d_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_w_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_h_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_b_insn (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_d_insn_0 (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_d_f_insn_0 (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_w_insn_0 (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_w_f_insn_0 (ISA_HAS_LASX)
#define HAVE_lasx_xvinsve0_d (ISA_HAS_LASX)
#define HAVE_lasx_xvinsve0_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xvinsve0_w (ISA_HAS_LASX)
#define HAVE_lasx_xvinsve0_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvinsve0_d_f_scalar (ISA_HAS_LASX)
#define HAVE_lasx_xvinsve0_w_f_scalar (ISA_HAS_LASX)
#define HAVE_lasx_xvpickve_d (ISA_HAS_LASX)
#define HAVE_lasx_xvpickve_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xvpickve_w (ISA_HAS_LASX)
#define HAVE_lasx_xvpickve_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvpickve_d_f_scalar (ISA_HAS_LASX)
#define HAVE_lasx_xvpickve_w_f_scalar (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrn_w_d (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrn_h_w (ISA_HAS_LASX)
#define HAVE_lasx_xvssrlrn_b_h (ISA_HAS_LASX)
#define HAVE_xvornv4di3 (ISA_HAS_LASX)
#define HAVE_xvornv8si3 (ISA_HAS_LASX)
#define HAVE_xvornv16hi3 (ISA_HAS_LASX)
#define HAVE_xvornv32qi3 (ISA_HAS_LASX)
#define HAVE_lasx_xvextl_qu_du (ISA_HAS_LASX)
#define HAVE_lasx_xvldi (ISA_HAS_LASX)
#define HAVE_lasx_xvldx (ISA_HAS_LASX)
#define HAVE_lasx_xvstx (ISA_HAS_LASX)
#define HAVE_vec_widen_smult_even_v8si (ISA_HAS_LASX)
#define HAVE_vec_widen_umult_even_v8si (ISA_HAS_LASX)
#define HAVE_mulditi3 (TARGET_64BIT)
#define HAVE_umulditi3 (TARGET_64BIT)
#define HAVE_mulsidi3 (TARGET_32BIT)
#define HAVE_umulsidi3 (TARGET_32BIT)
#define HAVE_divsf3 (TARGET_HARD_FLOAT)
#define HAVE_divdf3 ((TARGET_HARD_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_divsi3 1
#define HAVE_udivsi3 1
#define HAVE_modsi3 1
#define HAVE_umodsi3 1
#define HAVE_divdi3 (TARGET_64BIT)
#define HAVE_udivdi3 (TARGET_64BIT)
#define HAVE_moddi3 (TARGET_64BIT)
#define HAVE_umoddi3 (TARGET_64BIT)
#define HAVE_rsqrtsf2 (TARGET_HARD_FLOAT && flag_unsafe_math_optimizations && flag_finite_math_only)
#define HAVE_zero_extendsidi2 (TARGET_64BIT)
#define HAVE_zero_extendqisi2 1
#define HAVE_zero_extendqidi2 (TARGET_64BIT)
#define HAVE_zero_extendhisi2 1
#define HAVE_zero_extendhidi2 (TARGET_64BIT)
#define HAVE_zero_extendqihi2 1
#define HAVE_extendqisi2 1
#define HAVE_extendqidi2 (TARGET_64BIT)
#define HAVE_extendhisi2 1
#define HAVE_extendhidi2 (TARGET_64BIT)
#define HAVE_extendqihi2 1
#define HAVE_fixuns_truncdfsi2 (TARGET_DOUBLE_FLOAT)
#define HAVE_fixuns_truncdfdi2 (TARGET_DOUBLE_FLOAT && TARGET_64BIT)
#define HAVE_fixuns_truncsfsi2 (TARGET_HARD_FLOAT)
#define HAVE_fixuns_truncsfdi2 (TARGET_DOUBLE_FLOAT && TARGET_64BIT)
#define HAVE_extzvsi ((!TARGET_32BIT_REDUCED) && (TARGET_32BIT))
#define HAVE_extzvdi ((!TARGET_32BIT_REDUCED) && (TARGET_64BIT))
#define HAVE_insvsi (!TARGET_32BIT_REDUCED)
#define HAVE_insvdi ((!TARGET_32BIT_REDUCED) && (TARGET_64BIT))
#define HAVE_movdi 1
#define HAVE_movsi 1
#define HAVE_movhi 1
#define HAVE_movqi 1
#define HAVE_movsf 1
#define HAVE_movdf 1
#define HAVE_movti (TARGET_64BIT)
#define HAVE_movtf (TARGET_64BIT)
#define HAVE_move_doubleword_fprdf (TARGET_32BIT && TARGET_DOUBLE_FLOAT)
#define HAVE_move_doubleword_fprdi (TARGET_32BIT && TARGET_DOUBLE_FLOAT)
#define HAVE_move_doubleword_fprtf (TARGET_64BIT && TARGET_DOUBLE_FLOAT)
#define HAVE_movsicc ((TARGET_32BIT_STANDARD || TARGET_64BIT) && TARGET_COND_MOVE_INT)
#define HAVE_movdicc (((TARGET_32BIT_STANDARD || TARGET_64BIT) && TARGET_COND_MOVE_INT) && (TARGET_64BIT))
#define HAVE_movsfcc ((TARGET_COND_MOVE_FLOAT) && (TARGET_HARD_FLOAT))
#define HAVE_movdfcc ((TARGET_COND_MOVE_FLOAT) && (TARGET_DOUBLE_FLOAT))
#define HAVE_clear_cache 1
#define HAVE_movmemsi ( !TARGET_MEMCPY)
#define HAVE_cbranchsi4 1
#define HAVE_cbranchdi4 (TARGET_64BIT)
#define HAVE_cbranchsf4 (TARGET_HARD_FLOAT)
#define HAVE_cbranchdf4 (TARGET_DOUBLE_FLOAT)
#define HAVE_condjump 1
#define HAVE_cstoresi4 1
#define HAVE_cstoredi4 (TARGET_64BIT)
#define HAVE_jump 1
#define HAVE_indirect_jump 1
#define HAVE_tablejump 1
#define HAVE_prologue 1
#define HAVE_epilogue 1
#define HAVE_sibcall_epilogue 1
#define HAVE_return (loongarch_can_use_return_insn ())
#define HAVE_simple_return 1
#define HAVE_eh_return 1
#define HAVE_sibcall 1
#define HAVE_sibcall_value 1
#define HAVE_call 1
#define HAVE_call_value 1
#define HAVE_untyped_call 1
#define HAVE_mem_thread_fence 1
#define HAVE_atomic_compare_and_swapsi 1
#define HAVE_atomic_compare_and_swapdi (TARGET_64BIT)
#define HAVE_atomic_test_and_set 1
#define HAVE_atomic_compare_and_swapqi 1
#define HAVE_atomic_compare_and_swaphi 1
#define HAVE_atomic_exchangeqi 1
#define HAVE_atomic_exchangehi 1
#define HAVE_atomic_fetch_addqi 1
#define HAVE_atomic_fetch_addhi 1
#define HAVE_atomic_fetch_subqi 1
#define HAVE_atomic_fetch_subhi 1
#define HAVE_atomic_fetch_andqi 1
#define HAVE_atomic_fetch_andhi 1
#define HAVE_atomic_fetch_xorqi 1
#define HAVE_atomic_fetch_xorhi 1
#define HAVE_atomic_fetch_orqi 1
#define HAVE_atomic_fetch_orhi 1
#define HAVE_atomic_fetch_nandqi 1
#define HAVE_atomic_fetch_nandhi 1
#define HAVE_vec_initv2dfdf (ISA_HAS_LSX)
#define HAVE_vec_initv4sfsf (ISA_HAS_LSX)
#define HAVE_vec_initv2didi (ISA_HAS_LSX)
#define HAVE_vec_initv4sisi (ISA_HAS_LSX)
#define HAVE_vec_initv8hihi (ISA_HAS_LSX)
#define HAVE_vec_initv16qiqi (ISA_HAS_LSX)
#define HAVE_vec_unpacks_hi_v4sf (ISA_HAS_LSX)
#define HAVE_vec_unpacks_lo_v4sf (ISA_HAS_LSX)
#define HAVE_vec_unpacks_hi_v4si (ISA_HAS_LSX)
#define HAVE_vec_unpacks_hi_v8hi (ISA_HAS_LSX)
#define HAVE_vec_unpacks_hi_v16qi (ISA_HAS_LSX)
#define HAVE_vec_unpacks_lo_v4si (ISA_HAS_LSX)
#define HAVE_vec_unpacks_lo_v8hi (ISA_HAS_LSX)
#define HAVE_vec_unpacks_lo_v16qi (ISA_HAS_LSX)
#define HAVE_vec_unpacku_hi_v4si (ISA_HAS_LSX)
#define HAVE_vec_unpacku_hi_v8hi (ISA_HAS_LSX)
#define HAVE_vec_unpacku_hi_v16qi (ISA_HAS_LSX)
#define HAVE_vec_unpacku_lo_v4si (ISA_HAS_LSX)
#define HAVE_vec_unpacku_lo_v8hi (ISA_HAS_LSX)
#define HAVE_vec_unpacku_lo_v16qi (ISA_HAS_LSX)
#define HAVE_vec_extractv2didi (ISA_HAS_LSX)
#define HAVE_vec_extractv4sisi (ISA_HAS_LSX)
#define HAVE_vec_extractv8hihi (ISA_HAS_LSX)
#define HAVE_vec_extractv16qiqi (ISA_HAS_LSX)
#define HAVE_vec_extractv2dfdf (ISA_HAS_LSX)
#define HAVE_vec_extractv4sfsf (ISA_HAS_LSX)
#define HAVE_vec_setv2di (ISA_HAS_LSX)
#define HAVE_vec_setv4si (ISA_HAS_LSX)
#define HAVE_vec_setv8hi (ISA_HAS_LSX)
#define HAVE_vec_setv16qi (ISA_HAS_LSX)
#define HAVE_vec_setv2df (ISA_HAS_LSX)
#define HAVE_vec_setv4sf (ISA_HAS_LSX)
#define HAVE_vconduv2dfv2di (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DFmode) == GET_MODE_NUNITS (V2DImode)))
#define HAVE_vconduv4sfv2di (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SFmode) == GET_MODE_NUNITS (V2DImode)))
#define HAVE_vconduv2div2di (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DImode) == GET_MODE_NUNITS (V2DImode)))
#define HAVE_vconduv4siv2di (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SImode) == GET_MODE_NUNITS (V2DImode)))
#define HAVE_vconduv8hiv2di (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V8HImode) == GET_MODE_NUNITS (V2DImode)))
#define HAVE_vconduv16qiv2di (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V16QImode) == GET_MODE_NUNITS (V2DImode)))
#define HAVE_vconduv2dfv4si (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DFmode) == GET_MODE_NUNITS (V4SImode)))
#define HAVE_vconduv4sfv4si (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SFmode) == GET_MODE_NUNITS (V4SImode)))
#define HAVE_vconduv2div4si (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DImode) == GET_MODE_NUNITS (V4SImode)))
#define HAVE_vconduv4siv4si (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SImode) == GET_MODE_NUNITS (V4SImode)))
#define HAVE_vconduv8hiv4si (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V8HImode) == GET_MODE_NUNITS (V4SImode)))
#define HAVE_vconduv16qiv4si (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V16QImode) == GET_MODE_NUNITS (V4SImode)))
#define HAVE_vconduv2dfv8hi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DFmode) == GET_MODE_NUNITS (V8HImode)))
#define HAVE_vconduv4sfv8hi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SFmode) == GET_MODE_NUNITS (V8HImode)))
#define HAVE_vconduv2div8hi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DImode) == GET_MODE_NUNITS (V8HImode)))
#define HAVE_vconduv4siv8hi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SImode) == GET_MODE_NUNITS (V8HImode)))
#define HAVE_vconduv8hiv8hi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V8HImode) == GET_MODE_NUNITS (V8HImode)))
#define HAVE_vconduv16qiv8hi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V16QImode) == GET_MODE_NUNITS (V8HImode)))
#define HAVE_vconduv2dfv16qi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DFmode) == GET_MODE_NUNITS (V16QImode)))
#define HAVE_vconduv4sfv16qi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SFmode) == GET_MODE_NUNITS (V16QImode)))
#define HAVE_vconduv2div16qi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DImode) == GET_MODE_NUNITS (V16QImode)))
#define HAVE_vconduv4siv16qi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SImode) == GET_MODE_NUNITS (V16QImode)))
#define HAVE_vconduv8hiv16qi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V8HImode) == GET_MODE_NUNITS (V16QImode)))
#define HAVE_vconduv16qiv16qi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V16QImode) == GET_MODE_NUNITS (V16QImode)))
#define HAVE_vcondv2dfv2df (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DFmode) == GET_MODE_NUNITS (V2DFmode)))
#define HAVE_vcondv4sfv2df (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SFmode) == GET_MODE_NUNITS (V2DFmode)))
#define HAVE_vcondv2div2df (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DImode) == GET_MODE_NUNITS (V2DFmode)))
#define HAVE_vcondv4siv2df (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SImode) == GET_MODE_NUNITS (V2DFmode)))
#define HAVE_vcondv8hiv2df (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V8HImode) == GET_MODE_NUNITS (V2DFmode)))
#define HAVE_vcondv16qiv2df (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V16QImode) == GET_MODE_NUNITS (V2DFmode)))
#define HAVE_vcondv2dfv4sf (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DFmode) == GET_MODE_NUNITS (V4SFmode)))
#define HAVE_vcondv4sfv4sf (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SFmode) == GET_MODE_NUNITS (V4SFmode)))
#define HAVE_vcondv2div4sf (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DImode) == GET_MODE_NUNITS (V4SFmode)))
#define HAVE_vcondv4siv4sf (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SImode) == GET_MODE_NUNITS (V4SFmode)))
#define HAVE_vcondv8hiv4sf (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V8HImode) == GET_MODE_NUNITS (V4SFmode)))
#define HAVE_vcondv16qiv4sf (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V16QImode) == GET_MODE_NUNITS (V4SFmode)))
#define HAVE_vcondv2dfv2di (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DFmode) == GET_MODE_NUNITS (V2DImode)))
#define HAVE_vcondv4sfv2di (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SFmode) == GET_MODE_NUNITS (V2DImode)))
#define HAVE_vcondv2div2di (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DImode) == GET_MODE_NUNITS (V2DImode)))
#define HAVE_vcondv4siv2di (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SImode) == GET_MODE_NUNITS (V2DImode)))
#define HAVE_vcondv8hiv2di (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V8HImode) == GET_MODE_NUNITS (V2DImode)))
#define HAVE_vcondv16qiv2di (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V16QImode) == GET_MODE_NUNITS (V2DImode)))
#define HAVE_vcondv2dfv4si (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DFmode) == GET_MODE_NUNITS (V4SImode)))
#define HAVE_vcondv4sfv4si (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SFmode) == GET_MODE_NUNITS (V4SImode)))
#define HAVE_vcondv2div4si (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DImode) == GET_MODE_NUNITS (V4SImode)))
#define HAVE_vcondv4siv4si (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SImode) == GET_MODE_NUNITS (V4SImode)))
#define HAVE_vcondv8hiv4si (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V8HImode) == GET_MODE_NUNITS (V4SImode)))
#define HAVE_vcondv16qiv4si (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V16QImode) == GET_MODE_NUNITS (V4SImode)))
#define HAVE_vcondv2dfv8hi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DFmode) == GET_MODE_NUNITS (V8HImode)))
#define HAVE_vcondv4sfv8hi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SFmode) == GET_MODE_NUNITS (V8HImode)))
#define HAVE_vcondv2div8hi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DImode) == GET_MODE_NUNITS (V8HImode)))
#define HAVE_vcondv4siv8hi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SImode) == GET_MODE_NUNITS (V8HImode)))
#define HAVE_vcondv8hiv8hi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V8HImode) == GET_MODE_NUNITS (V8HImode)))
#define HAVE_vcondv16qiv8hi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V16QImode) == GET_MODE_NUNITS (V8HImode)))
#define HAVE_vcondv2dfv16qi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DFmode) == GET_MODE_NUNITS (V16QImode)))
#define HAVE_vcondv4sfv16qi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SFmode) == GET_MODE_NUNITS (V16QImode)))
#define HAVE_vcondv2div16qi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V2DImode) == GET_MODE_NUNITS (V16QImode)))
#define HAVE_vcondv4siv16qi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V4SImode) == GET_MODE_NUNITS (V16QImode)))
#define HAVE_vcondv8hiv16qi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V8HImode) == GET_MODE_NUNITS (V16QImode)))
#define HAVE_vcondv16qiv16qi (ISA_HAS_LSX \
   && (GET_MODE_NUNITS (V16QImode) == GET_MODE_NUNITS (V16QImode)))
#define HAVE_absv2di2 (ISA_HAS_LSX)
#define HAVE_absv4si2 (ISA_HAS_LSX)
#define HAVE_absv8hi2 (ISA_HAS_LSX)
#define HAVE_absv16qi2 (ISA_HAS_LSX)
#define HAVE_negv2di2 (ISA_HAS_LSX)
#define HAVE_negv4si2 (ISA_HAS_LSX)
#define HAVE_negv8hi2 (ISA_HAS_LSX)
#define HAVE_negv16qi2 (ISA_HAS_LSX)
#define HAVE_negv2df2 (ISA_HAS_LSX)
#define HAVE_negv4sf2 (ISA_HAS_LSX)
#define HAVE_lsx_vrepliv2di (ISA_HAS_LSX)
#define HAVE_lsx_vrepliv4si (ISA_HAS_LSX)
#define HAVE_lsx_vrepliv8hi (ISA_HAS_LSX)
#define HAVE_lsx_vrepliv16qi (ISA_HAS_LSX)
#define HAVE_vec_permv2df (ISA_HAS_LSX)
#define HAVE_vec_permv4sf (ISA_HAS_LSX)
#define HAVE_vec_permv2di (ISA_HAS_LSX)
#define HAVE_vec_permv4si (ISA_HAS_LSX)
#define HAVE_vec_permv8hi (ISA_HAS_LSX)
#define HAVE_vec_permv16qi (ISA_HAS_LSX)
#define HAVE_movv2df (ISA_HAS_LSX)
#define HAVE_movv4sf (ISA_HAS_LSX)
#define HAVE_movv2di (ISA_HAS_LSX)
#define HAVE_movv4si (ISA_HAS_LSX)
#define HAVE_movv8hi (ISA_HAS_LSX)
#define HAVE_movv16qi (ISA_HAS_LSX)
#define HAVE_movmisalignv2df (ISA_HAS_LSX)
#define HAVE_movmisalignv4sf (ISA_HAS_LSX)
#define HAVE_movmisalignv2di (ISA_HAS_LSX)
#define HAVE_movmisalignv4si (ISA_HAS_LSX)
#define HAVE_movmisalignv8hi (ISA_HAS_LSX)
#define HAVE_movmisalignv16qi (ISA_HAS_LSX)
#define HAVE_lsx_ld_d_f (ISA_HAS_LSX)
#define HAVE_lsx_ld_w_f (ISA_HAS_LSX)
#define HAVE_lsx_ld_d (ISA_HAS_LSX)
#define HAVE_lsx_ld_w (ISA_HAS_LSX)
#define HAVE_lsx_ld_h (ISA_HAS_LSX)
#define HAVE_lsx_ld_b (ISA_HAS_LSX)
#define HAVE_lsx_st_d_f (ISA_HAS_LSX)
#define HAVE_lsx_st_w_f (ISA_HAS_LSX)
#define HAVE_lsx_st_d (ISA_HAS_LSX)
#define HAVE_lsx_st_w (ISA_HAS_LSX)
#define HAVE_lsx_st_h (ISA_HAS_LSX)
#define HAVE_lsx_st_b (ISA_HAS_LSX)
#define HAVE_rsqrtv2df2 (ISA_HAS_LSX && flag_unsafe_math_optimizations)
#define HAVE_rsqrtv4sf2 (ISA_HAS_LSX && flag_unsafe_math_optimizations)
#define HAVE_vec_concatv2di (ISA_HAS_LSX)
#define HAVE_copysignv2df3 (ISA_HAS_LSX)
#define HAVE_copysignv4sf3 (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_d_f (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_d (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_w (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_h (ISA_HAS_LSX)
#define HAVE_lsx_vldrepl_b (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_d_f (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_w_f (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_d (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_w (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_h (ISA_HAS_LSX)
#define HAVE_lsx_vstelm_b (ISA_HAS_LSX)
#define HAVE_lsx_vld (ISA_HAS_LSX)
#define HAVE_lsx_vst (ISA_HAS_LSX)
#define HAVE_reduc_plus_scal_v2di (ISA_HAS_LSX)
#define HAVE_reduc_plus_scal_v4si (ISA_HAS_LSX)
#define HAVE_reduc_plus_scal_v2df (ISA_HAS_LSX)
#define HAVE_reduc_plus_scal_v4sf (ISA_HAS_LSX)
#define HAVE_reduc_and_scal_v2di (ISA_HAS_LSX)
#define HAVE_reduc_ior_scal_v2di (ISA_HAS_LSX)
#define HAVE_reduc_xor_scal_v2di (ISA_HAS_LSX)
#define HAVE_reduc_and_scal_v4si (ISA_HAS_LSX)
#define HAVE_reduc_ior_scal_v4si (ISA_HAS_LSX)
#define HAVE_reduc_xor_scal_v4si (ISA_HAS_LSX)
#define HAVE_reduc_and_scal_v8hi (ISA_HAS_LSX)
#define HAVE_reduc_ior_scal_v8hi (ISA_HAS_LSX)
#define HAVE_reduc_xor_scal_v8hi (ISA_HAS_LSX)
#define HAVE_reduc_and_scal_v16qi (ISA_HAS_LSX)
#define HAVE_reduc_ior_scal_v16qi (ISA_HAS_LSX)
#define HAVE_reduc_xor_scal_v16qi (ISA_HAS_LSX)
#define HAVE_reduc_smax_scal_v2df (ISA_HAS_LSX)
#define HAVE_reduc_smax_scal_v4sf (ISA_HAS_LSX)
#define HAVE_reduc_smax_scal_v2di (ISA_HAS_LSX)
#define HAVE_reduc_smax_scal_v4si (ISA_HAS_LSX)
#define HAVE_reduc_smax_scal_v8hi (ISA_HAS_LSX)
#define HAVE_reduc_smax_scal_v16qi (ISA_HAS_LSX)
#define HAVE_reduc_smin_scal_v2df (ISA_HAS_LSX)
#define HAVE_reduc_smin_scal_v4sf (ISA_HAS_LSX)
#define HAVE_reduc_smin_scal_v2di (ISA_HAS_LSX)
#define HAVE_reduc_smin_scal_v4si (ISA_HAS_LSX)
#define HAVE_reduc_smin_scal_v8hi (ISA_HAS_LSX)
#define HAVE_reduc_smin_scal_v16qi (ISA_HAS_LSX)
#define HAVE_reduc_umax_scal_v2di (ISA_HAS_LSX)
#define HAVE_reduc_umax_scal_v4si (ISA_HAS_LSX)
#define HAVE_reduc_umax_scal_v8hi (ISA_HAS_LSX)
#define HAVE_reduc_umax_scal_v16qi (ISA_HAS_LSX)
#define HAVE_reduc_umin_scal_v2di (ISA_HAS_LSX)
#define HAVE_reduc_umin_scal_v4si (ISA_HAS_LSX)
#define HAVE_reduc_umin_scal_v8hi (ISA_HAS_LSX)
#define HAVE_reduc_umin_scal_v16qi (ISA_HAS_LSX)
#define HAVE_vec_initv4dfdf (ISA_HAS_LASX)
#define HAVE_vec_initv8sfsf (ISA_HAS_LASX)
#define HAVE_vec_initv4didi (ISA_HAS_LASX)
#define HAVE_vec_initv8sisi (ISA_HAS_LASX)
#define HAVE_vec_initv16hihi (ISA_HAS_LASX)
#define HAVE_vec_initv32qiqi (ISA_HAS_LASX)
#define HAVE_vec_unpacks_hi_v8sf (ISA_HAS_LASX)
#define HAVE_vec_unpacks_lo_v8sf (ISA_HAS_LASX)
#define HAVE_vec_unpacks_hi_v8si (ISA_HAS_LASX)
#define HAVE_vec_unpacks_hi_v16hi (ISA_HAS_LASX)
#define HAVE_vec_unpacks_hi_v32qi (ISA_HAS_LASX)
#define HAVE_vec_unpacks_lo_v8si (ISA_HAS_LASX)
#define HAVE_vec_unpacks_lo_v16hi (ISA_HAS_LASX)
#define HAVE_vec_unpacks_lo_v32qi (ISA_HAS_LASX)
#define HAVE_vec_unpacku_hi_v8si (ISA_HAS_LASX)
#define HAVE_vec_unpacku_hi_v16hi (ISA_HAS_LASX)
#define HAVE_vec_unpacku_hi_v32qi (ISA_HAS_LASX)
#define HAVE_vec_unpacku_lo_v8si (ISA_HAS_LASX)
#define HAVE_vec_unpacku_lo_v16hi (ISA_HAS_LASX)
#define HAVE_vec_unpacku_lo_v32qi (ISA_HAS_LASX)
#define HAVE_vec_setv4di (ISA_HAS_LASX)
#define HAVE_vec_setv8si (ISA_HAS_LASX)
#define HAVE_vec_setv4df (ISA_HAS_LASX)
#define HAVE_vec_setv8sf (ISA_HAS_LASX)
#define HAVE_vec_extractv4dfdf (ISA_HAS_LASX)
#define HAVE_vec_extractv8sfsf (ISA_HAS_LASX)
#define HAVE_vec_extractv4didi (ISA_HAS_LASX)
#define HAVE_vec_extractv8sisi (ISA_HAS_LASX)
#define HAVE_vec_extractv16hihi (ISA_HAS_LASX)
#define HAVE_vec_extractv32qiqi (ISA_HAS_LASX)
#define HAVE_vec_permv4df (ISA_HAS_LASX)
#define HAVE_vec_permv8sf (ISA_HAS_LASX)
#define HAVE_vec_permv4di (ISA_HAS_LASX)
#define HAVE_vec_permv8si (ISA_HAS_LASX)
#define HAVE_vec_permv16hi (ISA_HAS_LASX)
#define HAVE_vec_permv32qi (ISA_HAS_LASX)
#define HAVE_vconduv4dfv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vconduv4dfv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vconduv4dfv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vconduv4dfv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vconduv8sfv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vconduv8sfv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vconduv8sfv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vconduv8sfv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vconduv4div4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vconduv4div8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vconduv4div16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vconduv4div32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vconduv8siv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vconduv8siv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vconduv8siv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vconduv8siv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vconduv16hiv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vconduv16hiv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vconduv16hiv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vconduv16hiv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vconduv32qiv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vconduv32qiv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vconduv32qiv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vconduv32qiv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vcondv4dfv4df (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V4DFmode)))
#define HAVE_vcondv8sfv4df (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V4DFmode)))
#define HAVE_vcondv4div4df (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V4DFmode)))
#define HAVE_vcondv8siv4df (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V4DFmode)))
#define HAVE_vcondv16hiv4df (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V4DFmode)))
#define HAVE_vcondv32qiv4df (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V4DFmode)))
#define HAVE_vcondv4dfv8sf (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V8SFmode)))
#define HAVE_vcondv8sfv8sf (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V8SFmode)))
#define HAVE_vcondv4div8sf (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V8SFmode)))
#define HAVE_vcondv8siv8sf (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V8SFmode)))
#define HAVE_vcondv16hiv8sf (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V8SFmode)))
#define HAVE_vcondv32qiv8sf (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V8SFmode)))
#define HAVE_vcondv4dfv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vcondv8sfv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vcondv4div4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vcondv8siv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vcondv16hiv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vcondv32qiv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vcondv4dfv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vcondv8sfv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vcondv4div8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vcondv8siv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vcondv16hiv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vcondv32qiv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vcondv4dfv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vcondv8sfv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vcondv4div16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vcondv8siv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vcondv16hiv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vcondv32qiv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vcondv4dfv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vcondv8sfv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vcondv4div32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vcondv8siv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vcondv16hiv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vcondv32qiv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vcond_maskv4dfv4df (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V4DFmode)))
#define HAVE_vcond_maskv8sfv4df (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V4DFmode)))
#define HAVE_vcond_maskv4div4df (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V4DFmode)))
#define HAVE_vcond_maskv8siv4df (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V4DFmode)))
#define HAVE_vcond_maskv16hiv4df (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V4DFmode)))
#define HAVE_vcond_maskv32qiv4df (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V4DFmode)))
#define HAVE_vcond_maskv4dfv8sf (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V8SFmode)))
#define HAVE_vcond_maskv8sfv8sf (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V8SFmode)))
#define HAVE_vcond_maskv4div8sf (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V8SFmode)))
#define HAVE_vcond_maskv8siv8sf (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V8SFmode)))
#define HAVE_vcond_maskv16hiv8sf (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V8SFmode)))
#define HAVE_vcond_maskv32qiv8sf (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V8SFmode)))
#define HAVE_vcond_maskv4dfv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vcond_maskv8sfv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vcond_maskv4div4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vcond_maskv8siv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vcond_maskv16hiv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vcond_maskv32qiv4di (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V4DImode)))
#define HAVE_vcond_maskv4dfv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vcond_maskv8sfv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vcond_maskv4div8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vcond_maskv8siv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vcond_maskv16hiv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vcond_maskv32qiv8si (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V8SImode)))
#define HAVE_vcond_maskv4dfv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vcond_maskv8sfv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vcond_maskv4div16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vcond_maskv8siv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vcond_maskv16hiv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vcond_maskv32qiv16hi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V16HImode)))
#define HAVE_vcond_maskv4dfv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DFmode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vcond_maskv8sfv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SFmode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vcond_maskv4div32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V4DImode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vcond_maskv8siv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V8SImode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vcond_maskv16hiv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V16HImode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_vcond_maskv32qiv32qi (ISA_HAS_LASX \
   && (GET_MODE_NUNITS (V32QImode) == GET_MODE_NUNITS (V32QImode)))
#define HAVE_lasx_xvrepliv4di (ISA_HAS_LASX)
#define HAVE_lasx_xvrepliv8si (ISA_HAS_LASX)
#define HAVE_lasx_xvrepliv16hi (ISA_HAS_LASX)
#define HAVE_lasx_xvrepliv32qi (ISA_HAS_LASX)
#define HAVE_movv4df (ISA_HAS_LASX)
#define HAVE_movv8sf (ISA_HAS_LASX)
#define HAVE_movv4di (ISA_HAS_LASX)
#define HAVE_movv8si (ISA_HAS_LASX)
#define HAVE_movv16hi (ISA_HAS_LASX)
#define HAVE_movv32qi (ISA_HAS_LASX)
#define HAVE_movmisalignv4df (ISA_HAS_LASX)
#define HAVE_movmisalignv8sf (ISA_HAS_LASX)
#define HAVE_movmisalignv4di (ISA_HAS_LASX)
#define HAVE_movmisalignv8si (ISA_HAS_LASX)
#define HAVE_movmisalignv16hi (ISA_HAS_LASX)
#define HAVE_movmisalignv32qi (ISA_HAS_LASX)
#define HAVE_lasx_mxld_d_f (ISA_HAS_LASX)
#define HAVE_lasx_mxld_w_f (ISA_HAS_LASX)
#define HAVE_lasx_mxld_d (ISA_HAS_LASX)
#define HAVE_lasx_mxld_w (ISA_HAS_LASX)
#define HAVE_lasx_mxld_h (ISA_HAS_LASX)
#define HAVE_lasx_mxld_b (ISA_HAS_LASX)
#define HAVE_lasx_mxst_d_f (ISA_HAS_LASX)
#define HAVE_lasx_mxst_w_f (ISA_HAS_LASX)
#define HAVE_lasx_mxst_d (ISA_HAS_LASX)
#define HAVE_lasx_mxst_w (ISA_HAS_LASX)
#define HAVE_lasx_mxst_h (ISA_HAS_LASX)
#define HAVE_lasx_mxst_b (ISA_HAS_LASX)
#define HAVE_vec_cmpv4dfv4di (ISA_HAS_LASX)
#define HAVE_vec_cmpv8sfv8si (ISA_HAS_LASX)
#define HAVE_vec_cmpv4div4di (ISA_HAS_LASX)
#define HAVE_vec_cmpv8siv8si (ISA_HAS_LASX)
#define HAVE_vec_cmpv16hiv16hi (ISA_HAS_LASX)
#define HAVE_vec_cmpv32qiv32qi (ISA_HAS_LASX)
#define HAVE_vec_cmpuv4div4di (ISA_HAS_LASX)
#define HAVE_vec_cmpuv8siv8si (ISA_HAS_LASX)
#define HAVE_vec_cmpuv16hiv16hi (ISA_HAS_LASX)
#define HAVE_vec_cmpuv32qiv32qi (ISA_HAS_LASX)
#define HAVE_rsqrtv4df2 (ISA_HAS_LASX && flag_unsafe_math_optimizations)
#define HAVE_rsqrtv8sf2 (ISA_HAS_LASX && flag_unsafe_math_optimizations)
#define HAVE_copysignv4df3 (ISA_HAS_LASX)
#define HAVE_copysignv8sf3 (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_d (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_w (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_h (ISA_HAS_LASX)
#define HAVE_lasx_xvldrepl_b (ISA_HAS_LASX)
#define HAVE_lasx_xvld (ISA_HAS_LASX)
#define HAVE_lasx_xvst (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_d_f (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_w_f (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_d (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_w (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_h (ISA_HAS_LASX)
#define HAVE_lasx_xvstelm_b (ISA_HAS_LASX)
#define HAVE_reduc_plus_scal_v4di (ISA_HAS_LASX)
#define HAVE_reduc_plus_scal_v8si (ISA_HAS_LASX)
#define HAVE_reduc_plus_scal_v4df (ISA_HAS_LASX)
#define HAVE_reduc_plus_scal_v8sf (ISA_HAS_LASX)
#define HAVE_reduc_and_scal_v4di (ISA_HAS_LASX)
#define HAVE_reduc_ior_scal_v4di (ISA_HAS_LASX)
#define HAVE_reduc_xor_scal_v4di (ISA_HAS_LASX)
#define HAVE_reduc_and_scal_v8si (ISA_HAS_LASX)
#define HAVE_reduc_ior_scal_v8si (ISA_HAS_LASX)
#define HAVE_reduc_xor_scal_v8si (ISA_HAS_LASX)
#define HAVE_reduc_and_scal_v16hi (ISA_HAS_LASX)
#define HAVE_reduc_ior_scal_v16hi (ISA_HAS_LASX)
#define HAVE_reduc_xor_scal_v16hi (ISA_HAS_LASX)
#define HAVE_reduc_and_scal_v32qi (ISA_HAS_LASX)
#define HAVE_reduc_ior_scal_v32qi (ISA_HAS_LASX)
#define HAVE_reduc_xor_scal_v32qi (ISA_HAS_LASX)
#define HAVE_reduc_smax_scal_v4df (ISA_HAS_LASX)
#define HAVE_reduc_smax_scal_v8sf (ISA_HAS_LASX)
#define HAVE_reduc_smax_scal_v4di (ISA_HAS_LASX)
#define HAVE_reduc_smax_scal_v8si (ISA_HAS_LASX)
#define HAVE_reduc_smax_scal_v16hi (ISA_HAS_LASX)
#define HAVE_reduc_smax_scal_v32qi (ISA_HAS_LASX)
#define HAVE_reduc_smin_scal_v4df (ISA_HAS_LASX)
#define HAVE_reduc_smin_scal_v8sf (ISA_HAS_LASX)
#define HAVE_reduc_smin_scal_v4di (ISA_HAS_LASX)
#define HAVE_reduc_smin_scal_v8si (ISA_HAS_LASX)
#define HAVE_reduc_smin_scal_v16hi (ISA_HAS_LASX)
#define HAVE_reduc_smin_scal_v32qi (ISA_HAS_LASX)
#define HAVE_reduc_umax_scal_v4di (ISA_HAS_LASX)
#define HAVE_reduc_umax_scal_v8si (ISA_HAS_LASX)
#define HAVE_reduc_umax_scal_v16hi (ISA_HAS_LASX)
#define HAVE_reduc_umax_scal_v32qi (ISA_HAS_LASX)
#define HAVE_reduc_umin_scal_v4di (ISA_HAS_LASX)
#define HAVE_reduc_umin_scal_v8si (ISA_HAS_LASX)
#define HAVE_reduc_umin_scal_v16hi (ISA_HAS_LASX)
#define HAVE_reduc_umin_scal_v32qi (ISA_HAS_LASX)
extern rtx        gen_trap                            (void);
extern rtx        gen_addsf3                          (rtx, rtx, rtx);
extern rtx        gen_adddf3                          (rtx, rtx, rtx);
extern rtx        gen_addsi3                          (rtx, rtx, rtx);
extern rtx        gen_adddi3                          (rtx, rtx, rtx);
extern rtx        gen_subsf3                          (rtx, rtx, rtx);
extern rtx        gen_subdf3                          (rtx, rtx, rtx);
extern rtx        gen_subsi3                          (rtx, rtx, rtx);
extern rtx        gen_subdi3                          (rtx, rtx, rtx);
extern rtx        gen_mulsf3                          (rtx, rtx, rtx);
extern rtx        gen_muldf3                          (rtx, rtx, rtx);
extern rtx        gen_mulsi3                          (rtx, rtx, rtx);
extern rtx        gen_muldi3                          (rtx, rtx, rtx);
extern rtx        gen_mulsidi3_64bit                  (rtx, rtx, rtx);
extern rtx        gen_muldi3_highpart                 (rtx, rtx, rtx);
extern rtx        gen_umuldi3_highpart                (rtx, rtx, rtx);
extern rtx        gen_mulsi3_highpart                 (rtx, rtx, rtx);
extern rtx        gen_umulsi3_highpart                (rtx, rtx, rtx);
extern rtx        gen_copysignsf3                     (rtx, rtx, rtx);
extern rtx        gen_copysigndf3                     (rtx, rtx, rtx);
extern rtx        gen_divdi3_fake                     (rtx, rtx, rtx);
extern rtx        gen_udivdi3_fake                    (rtx, rtx, rtx);
extern rtx        gen_moddi3_fake                     (rtx, rtx, rtx);
extern rtx        gen_umoddi3_fake                    (rtx, rtx, rtx);
extern rtx        gen_fmasf4                          (rtx, rtx, rtx, rtx);
extern rtx        gen_fmadf4                          (rtx, rtx, rtx, rtx);
extern rtx        gen_fmssf4                          (rtx, rtx, rtx, rtx);
extern rtx        gen_fmsdf4                          (rtx, rtx, rtx, rtx);
extern rtx        gen_fnmasf4                         (rtx, rtx, rtx, rtx);
extern rtx        gen_fnmadf4                         (rtx, rtx, rtx, rtx);
extern rtx        gen_fnmssf4                         (rtx, rtx, rtx, rtx);
extern rtx        gen_fnmsdf4                         (rtx, rtx, rtx, rtx);
extern rtx        gen_sqrtsf2                         (rtx, rtx);
extern rtx        gen_sqrtdf2                         (rtx, rtx);
extern rtx        gen_abssf2                          (rtx, rtx);
extern rtx        gen_absdf2                          (rtx, rtx);
extern rtx        gen_clzsi2                          (rtx, rtx);
extern rtx        gen_clzdi2                          (rtx, rtx);
extern rtx        gen_ctzsi2                          (rtx, rtx);
extern rtx        gen_ctzdi2                          (rtx, rtx);
extern rtx        gen_smaxsf3                         (rtx, rtx, rtx);
extern rtx        gen_smaxdf3                         (rtx, rtx, rtx);
extern rtx        gen_sminsf3                         (rtx, rtx, rtx);
extern rtx        gen_smindf3                         (rtx, rtx, rtx);
extern rtx        gen_smaxasf3                        (rtx, rtx, rtx);
extern rtx        gen_smaxadf3                        (rtx, rtx, rtx);
extern rtx        gen_sminasf3                        (rtx, rtx, rtx);
extern rtx        gen_sminadf3                        (rtx, rtx, rtx);
extern rtx        gen_negsi2                          (rtx, rtx);
extern rtx        gen_negdi2                          (rtx, rtx);
extern rtx        gen_one_cmplsi2                     (rtx, rtx);
extern rtx        gen_one_cmpldi2                     (rtx, rtx);
extern rtx        gen_negsf2                          (rtx, rtx);
extern rtx        gen_negdf2                          (rtx, rtx);
extern rtx        gen_andsi3                          (rtx, rtx, rtx);
extern rtx        gen_iorsi3                          (rtx, rtx, rtx);
extern rtx        gen_xorsi3                          (rtx, rtx, rtx);
extern rtx        gen_anddi3                          (rtx, rtx, rtx);
extern rtx        gen_iordi3                          (rtx, rtx, rtx);
extern rtx        gen_xordi3                          (rtx, rtx, rtx);
extern rtx        gen_andsi3_extended                 (rtx, rtx, rtx);
extern rtx        gen_anddi3_extended                 (rtx, rtx, rtx);
extern rtx        gen_andnsi                          (rtx, rtx, rtx);
extern rtx        gen_iornsi                          (rtx, rtx, rtx);
extern rtx        gen_andndi                          (rtx, rtx, rtx);
extern rtx        gen_iorndi                          (rtx, rtx, rtx);
extern rtx        gen_truncdiqi2                      (rtx, rtx);
extern rtx        gen_truncdihi2                      (rtx, rtx);
extern rtx        gen_truncdisi2                      (rtx, rtx);
extern rtx        gen_truncdfsf2                      (rtx, rtx);
extern rtx        gen_extendsidi2                     (rtx, rtx);
extern rtx        gen_extendsfdf2                     (rtx, rtx);
extern rtx        gen_fix_truncsfsi2                  (rtx, rtx);
extern rtx        gen_fix_truncsfdi2                  (rtx, rtx);
extern rtx        gen_fix_truncdfsi2                  (rtx, rtx);
extern rtx        gen_fix_truncdfdi2                  (rtx, rtx);
extern rtx        gen_floatsidf2                      (rtx, rtx);
extern rtx        gen_floatdidf2                      (rtx, rtx);
extern rtx        gen_floatsisf2                      (rtx, rtx);
extern rtx        gen_floatdisf2                      (rtx, rtx);
extern rtx        gen_movfcc                          (rtx);
extern rtx        gen_lu32i_d                         (rtx, rtx, rtx);
extern rtx        gen_lu52i_d                         (rtx, rtx, rtx, rtx);
extern rtx        gen_frint_s                         (rtx, rtx);
extern rtx        gen_frint_d                         (rtx, rtx);
extern rtx        gen_load_lowdf                      (rtx, rtx);
extern rtx        gen_load_lowdi                      (rtx, rtx);
extern rtx        gen_load_lowtf                      (rtx, rtx);
extern rtx        gen_load_highdf                     (rtx, rtx, rtx);
extern rtx        gen_load_highdi                     (rtx, rtx, rtx);
extern rtx        gen_load_hightf                     (rtx, rtx, rtx);
extern rtx        gen_store_worddf                    (rtx, rtx, rtx);
extern rtx        gen_store_worddi                    (rtx, rtx, rtx);
extern rtx        gen_store_wordtf                    (rtx, rtx, rtx);
extern rtx        gen_got_load_tls_gdsi               (rtx, rtx);
extern rtx        gen_got_load_tls_gddi               (rtx, rtx);
extern rtx        gen_got_load_tls_ldsi               (rtx, rtx);
extern rtx        gen_got_load_tls_lddi               (rtx, rtx);
extern rtx        gen_got_load_tls_lesi               (rtx, rtx);
extern rtx        gen_got_load_tls_ledi               (rtx, rtx);
extern rtx        gen_got_load_tls_iesi               (rtx, rtx);
extern rtx        gen_got_load_tls_iedi               (rtx, rtx);
extern rtx        gen_movgr2frhdf                     (rtx, rtx, rtx);
extern rtx        gen_movgr2frhdi                     (rtx, rtx, rtx);
extern rtx        gen_movgr2frhtf                     (rtx, rtx, rtx);
extern rtx        gen_movsgr2frsf                     (rtx, rtx);
extern rtx        gen_movsgr2frdf                     (rtx, rtx);
extern rtx        gen_movdgr2frsf                     (rtx, rtx);
extern rtx        gen_movdgr2frdf                     (rtx, rtx);
extern rtx        gen_movfrh2grdf                     (rtx, rtx);
extern rtx        gen_movfrh2grdi                     (rtx, rtx);
extern rtx        gen_movfrh2grtf                     (rtx, rtx);
extern rtx        gen_movsfr2grsi                     (rtx, rtx);
extern rtx        gen_movsfr2grdi                     (rtx, rtx);
extern rtx        gen_movdfr2grsi                     (rtx, rtx);
extern rtx        gen_movdfr2grdi                     (rtx, rtx);
extern rtx        gen_movfr2fccsf                     (rtx, rtx);
extern rtx        gen_movfr2fccdf                     (rtx, rtx);
extern rtx        gen_movgr2fccsi                     (rtx, rtx);
extern rtx        gen_movgr2fccdi                     (rtx, rtx);
extern rtx        gen_movfcc2grsi                     (rtx, rtx);
extern rtx        gen_movfcc2grdi                     (rtx, rtx);
extern rtx        gen_loongarch_ibar                  (rtx);
extern rtx        gen_loongarch_dbar                  (rtx);
extern rtx        gen_loongarch_cpucfg                (rtx, rtx);
extern rtx        gen_loongarch_syscall               (rtx);
extern rtx        gen_loongarch_break                 (rtx);
extern rtx        gen_loongarch_asrtle_d              (rtx, rtx);
extern rtx        gen_loongarch_asrtgt_d              (rtx, rtx);
extern rtx        gen_loongarch_csrrd_w               (rtx, rtx);
extern rtx        gen_loongarch_csrrd_d               (rtx, rtx);
extern rtx        gen_loongarch_csrwr_w               (rtx, rtx, rtx);
extern rtx        gen_loongarch_csrwr_d               (rtx, rtx, rtx);
extern rtx        gen_loongarch_csrxchg_w             (rtx, rtx, rtx, rtx);
extern rtx        gen_loongarch_csrxchg_d             (rtx, rtx, rtx, rtx);
extern rtx        gen_loongarch_iocsrrd_b             (rtx, rtx);
extern rtx        gen_loongarch_iocsrrd_h             (rtx, rtx);
extern rtx        gen_loongarch_iocsrrd_w             (rtx, rtx);
extern rtx        gen_loongarch_iocsrrd_d             (rtx, rtx);
extern rtx        gen_loongarch_iocsrwr_b             (rtx, rtx);
extern rtx        gen_loongarch_iocsrwr_h             (rtx, rtx);
extern rtx        gen_loongarch_iocsrwr_w             (rtx, rtx);
extern rtx        gen_loongarch_iocsrwr_d             (rtx, rtx);
extern rtx        gen_loongarch_cacop_w               (rtx, rtx, rtx);
extern rtx        gen_loongarch_cacop_d               (rtx, rtx, rtx);
extern rtx        gen_loongarch_lddir_w               (rtx, rtx, rtx);
extern rtx        gen_loongarch_lddir_d               (rtx, rtx, rtx);
extern rtx        gen_loongarch_ldpte_w               (rtx, rtx);
extern rtx        gen_loongarch_ldpte_d               (rtx, rtx);
extern rtx        gen_ashlsi3                         (rtx, rtx, rtx);
extern rtx        gen_ashrsi3                         (rtx, rtx, rtx);
extern rtx        gen_lshrsi3                         (rtx, rtx, rtx);
extern rtx        gen_ashldi3                         (rtx, rtx, rtx);
extern rtx        gen_ashrdi3                         (rtx, rtx, rtx);
extern rtx        gen_lshrdi3                         (rtx, rtx, rtx);
extern rtx        gen_rotrsi3                         (rtx, rtx, rtx);
extern rtx        gen_rotrdi3                         (rtx, rtx, rtx);
extern rtx        gen_zero_extend_ashift              (rtx, rtx, rtx, rtx);
extern rtx        gen_bstrpick_alsl_paired            (rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_alslsi3                         (rtx, rtx, rtx, rtx);
extern rtx        gen_alsldi3                         (rtx, rtx, rtx, rtx);
extern rtx        gen_bswaphi2                        (rtx, rtx);
extern rtx        gen_bswapsi2                        (rtx, rtx);
extern rtx        gen_bswapdi2                        (rtx, rtx);
extern rtx        gen_revb_2h                         (rtx, rtx);
extern rtx        gen_revb_4h                         (rtx, rtx);
extern rtx        gen_revh_d                          (rtx, rtx);
extern rtx        gen_sunordered_sf_using_FCCmode     (rtx, rtx, rtx);
extern rtx        gen_suneq_sf_using_FCCmode          (rtx, rtx, rtx);
extern rtx        gen_sunlt_sf_using_FCCmode          (rtx, rtx, rtx);
extern rtx        gen_sunle_sf_using_FCCmode          (rtx, rtx, rtx);
extern rtx        gen_seq_sf_using_FCCmode            (rtx, rtx, rtx);
extern rtx        gen_slt_sf_using_FCCmode            (rtx, rtx, rtx);
extern rtx        gen_sle_sf_using_FCCmode            (rtx, rtx, rtx);
extern rtx        gen_sordered_sf_using_FCCmode       (rtx, rtx, rtx);
extern rtx        gen_sltgt_sf_using_FCCmode          (rtx, rtx, rtx);
extern rtx        gen_sne_sf_using_FCCmode            (rtx, rtx, rtx);
extern rtx        gen_sge_sf_using_FCCmode            (rtx, rtx, rtx);
extern rtx        gen_sgt_sf_using_FCCmode            (rtx, rtx, rtx);
extern rtx        gen_sunge_sf_using_FCCmode          (rtx, rtx, rtx);
extern rtx        gen_sungt_sf_using_FCCmode          (rtx, rtx, rtx);
extern rtx        gen_sunordered_df_using_FCCmode     (rtx, rtx, rtx);
extern rtx        gen_suneq_df_using_FCCmode          (rtx, rtx, rtx);
extern rtx        gen_sunlt_df_using_FCCmode          (rtx, rtx, rtx);
extern rtx        gen_sunle_df_using_FCCmode          (rtx, rtx, rtx);
extern rtx        gen_seq_df_using_FCCmode            (rtx, rtx, rtx);
extern rtx        gen_slt_df_using_FCCmode            (rtx, rtx, rtx);
extern rtx        gen_sle_df_using_FCCmode            (rtx, rtx, rtx);
extern rtx        gen_sordered_df_using_FCCmode       (rtx, rtx, rtx);
extern rtx        gen_sltgt_df_using_FCCmode          (rtx, rtx, rtx);
extern rtx        gen_sne_df_using_FCCmode            (rtx, rtx, rtx);
extern rtx        gen_sge_df_using_FCCmode            (rtx, rtx, rtx);
extern rtx        gen_sgt_df_using_FCCmode            (rtx, rtx, rtx);
extern rtx        gen_sunge_df_using_FCCmode          (rtx, rtx, rtx);
extern rtx        gen_sungt_df_using_FCCmode          (rtx, rtx, rtx);
extern rtx        gen_indirect_jumpsi                 (rtx);
extern rtx        gen_indirect_jumpdi                 (rtx);
extern rtx        gen_tablejumpsi                     (rtx, rtx);
extern rtx        gen_tablejumpdi                     (rtx, rtx);
extern rtx        gen_blockage                        (void);
extern rtx        gen_probe_stack_rangesi             (rtx, rtx, rtx, rtx);
extern rtx        gen_probe_stack_rangedi             (rtx, rtx, rtx, rtx);
extern rtx        gen_return_internal                 (rtx);
extern rtx        gen_simple_return_internal          (rtx);
extern rtx        gen_loongarch_ertn                  (void);
extern rtx        gen_eh_set_ra_si                    (rtx);
extern rtx        gen_eh_set_ra_di                    (rtx);
extern rtx        gen_sibcall_internal                (rtx, rtx);
extern rtx        gen_sibcall_value_internal          (rtx, rtx, rtx);
extern rtx        gen_sibcall_value_multiple_internal (rtx, rtx, rtx, rtx);
extern rtx        gen_call_internal                   (rtx, rtx);
extern rtx        gen_call_value_internal             (rtx, rtx, rtx);
extern rtx        gen_call_value_multiple_internal    (rtx, rtx, rtx, rtx);
extern rtx        gen_prefetch                        (rtx, rtx, rtx);
extern rtx        gen_nop                             (void);
extern rtx        gen_loongarch_movfcsr2gr            (rtx, rtx);
extern rtx        gen_loongarch_movgr2fcsr            (rtx, rtx);
extern rtx        gen_fclass_s                        (rtx, rtx);
extern rtx        gen_fclass_d                        (rtx, rtx);
extern rtx        gen_bytepick_w                      (rtx, rtx, rtx, rtx);
extern rtx        gen_bytepick_d                      (rtx, rtx, rtx, rtx);
extern rtx        gen_bitrev_4b                       (rtx, rtx);
extern rtx        gen_bitrev_8b                       (rtx, rtx);
extern rtx        gen_stack_tiesi                     (rtx, rtx);
extern rtx        gen_stack_tiedi                     (rtx, rtx);
extern rtx        gen_loongarch_crc_w_b_w             (rtx, rtx, rtx);
extern rtx        gen_loongarch_crc_w_h_w             (rtx, rtx, rtx);
extern rtx        gen_loongarch_crc_w_w_w             (rtx, rtx, rtx);
extern rtx        gen_loongarch_crc_w_d_w             (rtx, rtx, rtx);
extern rtx        gen_loongarch_crcc_w_b_w            (rtx, rtx, rtx);
extern rtx        gen_loongarch_crcc_w_h_w            (rtx, rtx, rtx);
extern rtx        gen_loongarch_crcc_w_w_w            (rtx, rtx, rtx);
extern rtx        gen_loongarch_crcc_w_d_w            (rtx, rtx, rtx);
extern rtx        gen_mem_thread_fence_1              (rtx, rtx);
extern rtx        gen_atomic_storedi                  (rtx, rtx, rtx);
extern rtx        gen_atomic_storesi                  (rtx, rtx, rtx);
extern rtx        gen_atomic_adddi                    (rtx, rtx, rtx);
extern rtx        gen_atomic_ordi                     (rtx, rtx, rtx);
extern rtx        gen_atomic_xordi                    (rtx, rtx, rtx);
extern rtx        gen_atomic_anddi                    (rtx, rtx, rtx);
extern rtx        gen_atomic_addsi                    (rtx, rtx, rtx);
extern rtx        gen_atomic_orsi                     (rtx, rtx, rtx);
extern rtx        gen_atomic_xorsi                    (rtx, rtx, rtx);
extern rtx        gen_atomic_andsi                    (rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_adddi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_ordi               (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_xordi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_anddi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_addsi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_orsi               (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_xorsi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_andsi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_exchangedi               (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_exchangesi               (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_strongsi       (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_strongdi       (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_cmp_and_7_si   (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_cmp_and_7_di   (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_add_7_si       (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_add_7_di       (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_sub_7_si       (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_sub_7_di       (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_and_7_si       (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_and_7_di       (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_xor_7_si       (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_xor_7_di       (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_or_7_si        (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_or_7_di        (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_nand_7_si      (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_nand_7_di      (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_exchange_7_si  (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_cas_value_exchange_7_di  (rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vec_pack_trunc_v2di             (rtx, rtx, rtx);
extern rtx        gen_vec_pack_trunc_v4si             (rtx, rtx, rtx);
extern rtx        gen_vec_pack_trunc_v8hi             (rtx, rtx, rtx);
extern rtx        gen_lsx_vec_extract_d_f             (rtx, rtx);
extern rtx        gen_lsx_vec_extract_w_f             (rtx, rtx);
extern rtx        gen_lsx_vinsgr2vr_d                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vinsgr2vr_w                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vinsgr2vr_h                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vinsgr2vr_b                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vextrins_d_f_internal       (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vextrins_w_f_internal       (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vextrins_d_internal         (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vextrins_w_internal         (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vextrins_h_internal         (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vextrins_b_internal         (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vextrins_d_f_scalar         (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vextrins_w_f_scalar         (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vpickve2gr_h                (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickve2gr_hu               (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickve2gr_b                (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickve2gr_bu               (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickve2gr_w                (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickve2gr_wu               (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickve2gr_w_f              (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickve2gr_w_fu             (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickve2gr_du               (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickve2gr_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickve2gr_d_f              (rtx, rtx, rtx);
extern rtx        gen_lsx_vshuf_d_f                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vshuf_w_f                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vshuf_d                     (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vshuf_w                     (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vshuf_h                     (rtx, rtx, rtx, rtx);
extern rtx        gen_movv2df_lsx                     (rtx, rtx);
extern rtx        gen_movv4sf_lsx                     (rtx, rtx);
extern rtx        gen_movv2di_lsx                     (rtx, rtx);
extern rtx        gen_movv4si_lsx                     (rtx, rtx);
extern rtx        gen_movv8hi_lsx                     (rtx, rtx);
extern rtx        gen_movv16qi_lsx                    (rtx, rtx);
extern rtx        gen_addv2di3                        (rtx, rtx, rtx);
extern rtx        gen_addv4si3                        (rtx, rtx, rtx);
extern rtx        gen_addv8hi3                        (rtx, rtx, rtx);
extern rtx        gen_addv16qi3                       (rtx, rtx, rtx);
extern rtx        gen_subv2di3                        (rtx, rtx, rtx);
extern rtx        gen_subv4si3                        (rtx, rtx, rtx);
extern rtx        gen_subv8hi3                        (rtx, rtx, rtx);
extern rtx        gen_subv16qi3                       (rtx, rtx, rtx);
extern rtx        gen_mulv2di3                        (rtx, rtx, rtx);
extern rtx        gen_mulv4si3                        (rtx, rtx, rtx);
extern rtx        gen_mulv8hi3                        (rtx, rtx, rtx);
extern rtx        gen_mulv16qi3                       (rtx, rtx, rtx);
extern rtx        gen_lsx_vmadd_d                     (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmadd_w                     (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmadd_h                     (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmadd_b                     (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmsub_d                     (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmsub_w                     (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmsub_h                     (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmsub_b                     (rtx, rtx, rtx, rtx);
extern rtx        gen_divv2di3                        (rtx, rtx, rtx);
extern rtx        gen_divv4si3                        (rtx, rtx, rtx);
extern rtx        gen_divv8hi3                        (rtx, rtx, rtx);
extern rtx        gen_divv16qi3                       (rtx, rtx, rtx);
extern rtx        gen_udivv2di3                       (rtx, rtx, rtx);
extern rtx        gen_udivv4si3                       (rtx, rtx, rtx);
extern rtx        gen_udivv8hi3                       (rtx, rtx, rtx);
extern rtx        gen_udivv16qi3                      (rtx, rtx, rtx);
extern rtx        gen_modv2di3                        (rtx, rtx, rtx);
extern rtx        gen_modv4si3                        (rtx, rtx, rtx);
extern rtx        gen_modv8hi3                        (rtx, rtx, rtx);
extern rtx        gen_modv16qi3                       (rtx, rtx, rtx);
extern rtx        gen_umodv2di3                       (rtx, rtx, rtx);
extern rtx        gen_umodv4si3                       (rtx, rtx, rtx);
extern rtx        gen_umodv8hi3                       (rtx, rtx, rtx);
extern rtx        gen_umodv16qi3                      (rtx, rtx, rtx);
extern rtx        gen_xorv2di3                        (rtx, rtx, rtx);
extern rtx        gen_xorv4si3                        (rtx, rtx, rtx);
extern rtx        gen_xorv8hi3                        (rtx, rtx, rtx);
extern rtx        gen_xorv16qi3                       (rtx, rtx, rtx);
extern rtx        gen_iorv2df3                        (rtx, rtx, rtx);
extern rtx        gen_iorv4sf3                        (rtx, rtx, rtx);
extern rtx        gen_iorv2di3                        (rtx, rtx, rtx);
extern rtx        gen_iorv4si3                        (rtx, rtx, rtx);
extern rtx        gen_iorv8hi3                        (rtx, rtx, rtx);
extern rtx        gen_iorv16qi3                       (rtx, rtx, rtx);
extern rtx        gen_andv2df3                        (rtx, rtx, rtx);
extern rtx        gen_andv4sf3                        (rtx, rtx, rtx);
extern rtx        gen_andv2di3                        (rtx, rtx, rtx);
extern rtx        gen_andv4si3                        (rtx, rtx, rtx);
extern rtx        gen_andv8hi3                        (rtx, rtx, rtx);
extern rtx        gen_andv16qi3                       (rtx, rtx, rtx);
extern rtx        gen_one_cmplv2di2                   (rtx, rtx);
extern rtx        gen_one_cmplv4si2                   (rtx, rtx);
extern rtx        gen_one_cmplv8hi2                   (rtx, rtx);
extern rtx        gen_one_cmplv16qi2                  (rtx, rtx);
extern rtx        gen_vlshrv2di3                      (rtx, rtx, rtx);
extern rtx        gen_vlshrv4si3                      (rtx, rtx, rtx);
extern rtx        gen_vlshrv8hi3                      (rtx, rtx, rtx);
extern rtx        gen_vlshrv16qi3                     (rtx, rtx, rtx);
extern rtx        gen_vashrv2di3                      (rtx, rtx, rtx);
extern rtx        gen_vashrv4si3                      (rtx, rtx, rtx);
extern rtx        gen_vashrv8hi3                      (rtx, rtx, rtx);
extern rtx        gen_vashrv16qi3                     (rtx, rtx, rtx);
extern rtx        gen_vashlv2di3                      (rtx, rtx, rtx);
extern rtx        gen_vashlv4si3                      (rtx, rtx, rtx);
extern rtx        gen_vashlv8hi3                      (rtx, rtx, rtx);
extern rtx        gen_vashlv16qi3                     (rtx, rtx, rtx);
extern rtx        gen_addv2df3                        (rtx, rtx, rtx);
extern rtx        gen_addv4sf3                        (rtx, rtx, rtx);
extern rtx        gen_subv2df3                        (rtx, rtx, rtx);
extern rtx        gen_subv4sf3                        (rtx, rtx, rtx);
extern rtx        gen_mulv2df3                        (rtx, rtx, rtx);
extern rtx        gen_mulv4sf3                        (rtx, rtx, rtx);
extern rtx        gen_divv2df3                        (rtx, rtx, rtx);
extern rtx        gen_divv4sf3                        (rtx, rtx, rtx);
extern rtx        gen_fmav2df4                        (rtx, rtx, rtx, rtx);
extern rtx        gen_fmav4sf4                        (rtx, rtx, rtx, rtx);
extern rtx        gen_fnmav2df4                       (rtx, rtx, rtx, rtx);
extern rtx        gen_fnmav4sf4                       (rtx, rtx, rtx, rtx);
extern rtx        gen_sqrtv2df2                       (rtx, rtx);
extern rtx        gen_sqrtv4sf2                       (rtx, rtx);
extern rtx        gen_lsx_vadda_d                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vadda_w                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vadda_h                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vadda_b                     (rtx, rtx, rtx);
extern rtx        gen_ssaddv2di3                      (rtx, rtx, rtx);
extern rtx        gen_ssaddv4si3                      (rtx, rtx, rtx);
extern rtx        gen_ssaddv8hi3                      (rtx, rtx, rtx);
extern rtx        gen_ssaddv16qi3                     (rtx, rtx, rtx);
extern rtx        gen_usaddv2di3                      (rtx, rtx, rtx);
extern rtx        gen_usaddv4si3                      (rtx, rtx, rtx);
extern rtx        gen_usaddv8hi3                      (rtx, rtx, rtx);
extern rtx        gen_usaddv16qi3                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vabsd_s_d                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vabsd_s_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vabsd_s_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vabsd_s_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vabsd_u_du                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vabsd_u_wu                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vabsd_u_hu                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vabsd_u_bu                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vavg_s_d                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vavg_s_w                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vavg_s_h                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vavg_s_b                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vavg_u_du                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vavg_u_wu                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vavg_u_hu                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vavg_u_bu                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vavgr_s_d                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vavgr_s_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vavgr_s_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vavgr_s_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vavgr_u_du                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vavgr_u_wu                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vavgr_u_hu                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vavgr_u_bu                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitclr_d                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitclr_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitclr_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitclr_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitclri_d                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitclri_w                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitclri_h                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitclri_b                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitrev_d                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitrev_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitrev_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitrev_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitrevi_d                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitrevi_w                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitrevi_h                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitrevi_b                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitsel_d                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vbitsel_w                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vbitsel_h                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vbitsel_b                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vbitseli_b                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vbitset_d                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitset_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitset_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitset_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitseti_d                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitseti_w                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitseti_h                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vbitseti_b                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vseq_d                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vsle_d                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vsle_du                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vslt_d                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vslt_du                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vseq_w                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vsle_w                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vsle_wu                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vslt_w                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vslt_wu                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vseq_h                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vsle_h                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vsle_hu                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vslt_h                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vslt_hu                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vseq_b                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vsle_b                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vsle_bu                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vslt_b                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vslt_bu                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vfclass_d                   (rtx, rtx);
extern rtx        gen_lsx_vfclass_s                   (rtx, rtx);
extern rtx        gen_lsx_vfcmp_caf_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_caf_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cune_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cune_s                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cun_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cor_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_ceq_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cne_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cle_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_clt_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cueq_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cule_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cult_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cun_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cor_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_ceq_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cne_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cle_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_clt_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cueq_s                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cule_s                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_cult_s                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_saf_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sun_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sor_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_seq_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sne_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sueq_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sune_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sule_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sult_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sle_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_slt_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_saf_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sun_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sor_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_seq_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sne_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sueq_s                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sune_s                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sule_s                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sult_s                (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_sle_s                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcmp_slt_s                 (rtx, rtx, rtx);
extern rtx        gen_floatv2div2df2                  (rtx, rtx);
extern rtx        gen_floatv4siv4sf2                  (rtx, rtx);
extern rtx        gen_floatunsv2div2df2               (rtx, rtx);
extern rtx        gen_floatunsv4siv4sf2               (rtx, rtx);
extern rtx        gen_lsx_vreplgr2vr_d                (rtx, rtx);
extern rtx        gen_lsx_vreplgr2vr_w                (rtx, rtx);
extern rtx        gen_lsx_vreplgr2vr_h                (rtx, rtx);
extern rtx        gen_lsx_vreplgr2vr_b                (rtx, rtx);
extern rtx        gen_logbv2df2                       (rtx, rtx);
extern rtx        gen_logbv4sf2                       (rtx, rtx);
extern rtx        gen_smaxv2df3                       (rtx, rtx, rtx);
extern rtx        gen_smaxv4sf3                       (rtx, rtx, rtx);
extern rtx        gen_lsx_vfmaxa_d                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vfmaxa_s                    (rtx, rtx, rtx);
extern rtx        gen_sminv2df3                       (rtx, rtx, rtx);
extern rtx        gen_sminv4sf3                       (rtx, rtx, rtx);
extern rtx        gen_lsx_vfmina_d                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vfmina_s                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vfrecip_d                   (rtx, rtx);
extern rtx        gen_lsx_vfrecip_s                   (rtx, rtx);
extern rtx        gen_lsx_vfrint_d                    (rtx, rtx);
extern rtx        gen_lsx_vfrint_s                    (rtx, rtx);
extern rtx        gen_lsx_vfrsqrt_d                   (rtx, rtx);
extern rtx        gen_lsx_vfrsqrt_s                   (rtx, rtx);
extern rtx        gen_lsx_vftint_s_l_d                (rtx, rtx);
extern rtx        gen_lsx_vftint_s_w_s                (rtx, rtx);
extern rtx        gen_lsx_vftint_u_lu_d               (rtx, rtx);
extern rtx        gen_lsx_vftint_u_wu_s               (rtx, rtx);
extern rtx        gen_fix_truncv2dfv2di2              (rtx, rtx);
extern rtx        gen_fix_truncv4sfv4si2              (rtx, rtx);
extern rtx        gen_fixuns_truncv2dfv2di2           (rtx, rtx);
extern rtx        gen_fixuns_truncv4sfv4si2           (rtx, rtx);
extern rtx        gen_lsx_vhaddw_h_b                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vhaddw_hu_bu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vhsubw_h_b                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vhsubw_hu_bu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vhaddw_w_h                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vhaddw_wu_hu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vhsubw_w_h                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vhsubw_wu_hu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vhaddw_d_w                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vhaddw_du_wu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vhsubw_d_w                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vhsubw_du_wu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vpackev_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpackev_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpackev_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpackev_w_f                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vilvh_b                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vilvh_h                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vilvh_w                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vilvh_w_f                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vilvh_d                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vilvh_d_f                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpackod_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpackod_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpackod_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpackod_w_f                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vilvl_b                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vilvl_h                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vilvl_w                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vilvl_w_f                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vilvl_d                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vilvl_d_f                   (rtx, rtx, rtx);
extern rtx        gen_smaxv2di3                       (rtx, rtx, rtx);
extern rtx        gen_smaxv4si3                       (rtx, rtx, rtx);
extern rtx        gen_smaxv8hi3                       (rtx, rtx, rtx);
extern rtx        gen_smaxv16qi3                      (rtx, rtx, rtx);
extern rtx        gen_umaxv2di3                       (rtx, rtx, rtx);
extern rtx        gen_umaxv4si3                       (rtx, rtx, rtx);
extern rtx        gen_umaxv8hi3                       (rtx, rtx, rtx);
extern rtx        gen_umaxv16qi3                      (rtx, rtx, rtx);
extern rtx        gen_sminv2di3                       (rtx, rtx, rtx);
extern rtx        gen_sminv4si3                       (rtx, rtx, rtx);
extern rtx        gen_sminv8hi3                       (rtx, rtx, rtx);
extern rtx        gen_sminv16qi3                      (rtx, rtx, rtx);
extern rtx        gen_uminv2di3                       (rtx, rtx, rtx);
extern rtx        gen_uminv4si3                       (rtx, rtx, rtx);
extern rtx        gen_uminv8hi3                       (rtx, rtx, rtx);
extern rtx        gen_uminv16qi3                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vclo_d                      (rtx, rtx);
extern rtx        gen_lsx_vclo_w                      (rtx, rtx);
extern rtx        gen_lsx_vclo_h                      (rtx, rtx);
extern rtx        gen_lsx_vclo_b                      (rtx, rtx);
extern rtx        gen_clzv2di2                        (rtx, rtx);
extern rtx        gen_clzv4si2                        (rtx, rtx);
extern rtx        gen_clzv8hi2                        (rtx, rtx);
extern rtx        gen_clzv16qi2                       (rtx, rtx);
extern rtx        gen_lsx_nor_d                       (rtx, rtx, rtx);
extern rtx        gen_lsx_nor_w                       (rtx, rtx, rtx);
extern rtx        gen_lsx_nor_h                       (rtx, rtx, rtx);
extern rtx        gen_lsx_nor_b                       (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickev_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickev_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickev_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickev_w_f                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickod_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickod_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickod_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vpickod_w_f                 (rtx, rtx, rtx);
extern rtx        gen_popcountv2di2                   (rtx, rtx);
extern rtx        gen_popcountv4si2                   (rtx, rtx);
extern rtx        gen_popcountv8hi2                   (rtx, rtx);
extern rtx        gen_popcountv16qi2                  (rtx, rtx);
extern rtx        gen_lsx_vsat_s_d                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsat_s_w                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsat_s_h                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsat_s_b                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsat_u_du                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vsat_u_wu                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vsat_u_hu                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vsat_u_bu                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vshuf4i_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vshuf4i_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vshuf4i_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vshuf4i_w_f                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrar_d                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrar_w                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrar_h                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrar_b                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrari_d                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrari_w                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrari_h                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrari_b                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlr_d                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlr_w                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlr_h                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlr_b                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlri_d                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlri_w                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlri_h                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlri_b                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vssub_s_d                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vssub_s_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vssub_s_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vssub_s_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vssub_u_du                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vssub_u_wu                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vssub_u_hu                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vssub_u_bu                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplve_d_f                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplve_w_f                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplve_d                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplve_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplve_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplve_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplvei_d_f                (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplvei_w_f                (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplvei_d                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplvei_w                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplvei_h                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplvei_b                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vreplvei_d_f_scalar         (rtx, rtx);
extern rtx        gen_lsx_vreplvei_w_f_scalar         (rtx, rtx);
extern rtx        gen_lsx_vfcvt_h_s                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcvt_s_d                   (rtx, rtx, rtx);
extern rtx        gen_vec_pack_trunc_v2df             (rtx, rtx, rtx);
extern rtx        gen_lsx_vfcvth_s_h                  (rtx, rtx);
extern rtx        gen_lsx_vfcvth_d_s                  (rtx, rtx);
extern rtx        gen_lsx_vfcvtl_s_h                  (rtx, rtx);
extern rtx        gen_lsx_vfcvtl_d_s                  (rtx, rtx);
extern rtx        gen_lsx_bz_d_f                      (rtx, rtx, rtx);
extern rtx        gen_lsx_bnz_d_f                     (rtx, rtx, rtx);
extern rtx        gen_lsx_bz_w_f                      (rtx, rtx, rtx);
extern rtx        gen_lsx_bnz_w_f                     (rtx, rtx, rtx);
extern rtx        gen_lsx_bz_d                        (rtx, rtx, rtx);
extern rtx        gen_lsx_bnz_d                       (rtx, rtx, rtx);
extern rtx        gen_lsx_bz_w                        (rtx, rtx, rtx);
extern rtx        gen_lsx_bnz_w                       (rtx, rtx, rtx);
extern rtx        gen_lsx_bz_h                        (rtx, rtx, rtx);
extern rtx        gen_lsx_bnz_h                       (rtx, rtx, rtx);
extern rtx        gen_lsx_bz_b                        (rtx, rtx, rtx);
extern rtx        gen_lsx_bnz_b                       (rtx, rtx, rtx);
extern rtx        gen_lsx_bz_v_d_f                    (rtx, rtx, rtx);
extern rtx        gen_lsx_bnz_v_d_f                   (rtx, rtx, rtx);
extern rtx        gen_lsx_bz_v_w_f                    (rtx, rtx, rtx);
extern rtx        gen_lsx_bnz_v_w_f                   (rtx, rtx, rtx);
extern rtx        gen_lsx_bz_v_d                      (rtx, rtx, rtx);
extern rtx        gen_lsx_bnz_v_d                     (rtx, rtx, rtx);
extern rtx        gen_lsx_bz_v_w                      (rtx, rtx, rtx);
extern rtx        gen_lsx_bnz_v_w                     (rtx, rtx, rtx);
extern rtx        gen_lsx_bz_v_h                      (rtx, rtx, rtx);
extern rtx        gen_lsx_bnz_v_h                     (rtx, rtx, rtx);
extern rtx        gen_lsx_bz_v_b                      (rtx, rtx, rtx);
extern rtx        gen_lsx_bnz_v_b                     (rtx, rtx, rtx);
extern rtx        gen_vandnv2df3                      (rtx, rtx, rtx);
extern rtx        gen_vandnv4sf3                      (rtx, rtx, rtx);
extern rtx        gen_vandnv2di3                      (rtx, rtx, rtx);
extern rtx        gen_vandnv4si3                      (rtx, rtx, rtx);
extern rtx        gen_vandnv8hi3                      (rtx, rtx, rtx);
extern rtx        gen_vandnv16qi3                     (rtx, rtx, rtx);
extern rtx        gen_vabsv2di2                       (rtx, rtx);
extern rtx        gen_vabsv4si2                       (rtx, rtx);
extern rtx        gen_vabsv8hi2                       (rtx, rtx);
extern rtx        gen_vabsv16qi2                      (rtx, rtx);
extern rtx        gen_vnegv2di2                       (rtx, rtx);
extern rtx        gen_vnegv4si2                       (rtx, rtx);
extern rtx        gen_vnegv8hi2                       (rtx, rtx);
extern rtx        gen_vnegv16qi2                      (rtx, rtx);
extern rtx        gen_lsx_vmuh_s_d                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vmuh_s_w                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vmuh_s_h                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vmuh_s_b                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vmuh_u_du                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vmuh_u_wu                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vmuh_u_hu                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vmuh_u_bu                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vextw_s_d                   (rtx, rtx);
extern rtx        gen_lsx_vextw_u_d                   (rtx, rtx);
extern rtx        gen_lsx_vsllwil_s_d_w               (rtx, rtx, rtx);
extern rtx        gen_lsx_vsllwil_s_w_h               (rtx, rtx, rtx);
extern rtx        gen_lsx_vsllwil_s_h_b               (rtx, rtx, rtx);
extern rtx        gen_lsx_vsllwil_u_du_wu             (rtx, rtx, rtx);
extern rtx        gen_lsx_vsllwil_u_wu_hu             (rtx, rtx, rtx);
extern rtx        gen_lsx_vsllwil_u_hu_bu             (rtx, rtx, rtx);
extern rtx        gen_lsx_vsran_w_d                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vsran_h_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vsran_b_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vssran_s_w_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vssran_s_h_w                (rtx, rtx, rtx);
extern rtx        gen_lsx_vssran_s_b_h                (rtx, rtx, rtx);
extern rtx        gen_lsx_vssran_u_wu_d               (rtx, rtx, rtx);
extern rtx        gen_lsx_vssran_u_hu_w               (rtx, rtx, rtx);
extern rtx        gen_lsx_vssran_u_bu_h               (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrain_w                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrain_h                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrain_b                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrains_s_w                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrains_s_h                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrains_s_b                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrains_u_w                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrains_u_h                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrains_u_b                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrarn_w_d                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrarn_h_w                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrarn_b_h                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarn_s_w_d               (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarn_s_h_w               (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarn_s_b_h               (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarn_u_wu_d              (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarn_u_hu_w              (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarn_u_bu_h              (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrln_w_d                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrln_h_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrln_b_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrln_u_wu_d               (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrln_u_hu_w               (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrln_u_bu_h               (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlrn_w_d                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlrn_h_w                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlrn_b_h                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrn_u_wu_d              (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrn_u_hu_w              (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrn_u_bu_h              (rtx, rtx, rtx);
extern rtx        gen_lsx_vfrstpi_h                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vfrstpi_b                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vfrstp_h                    (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vfrstp_b                    (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vshuf4i_d                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vbsrl_d_f                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbsrl_w_f                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vbsrl_d                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vbsrl_w                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vbsrl_h                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vbsrl_b                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vbsll_d                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vbsll_w                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vbsll_h                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vbsll_b                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vextrins_d                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vextrins_w                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vextrins_h                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vextrins_b                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmskltz_d                   (rtx, rtx);
extern rtx        gen_lsx_vmskltz_w                   (rtx, rtx);
extern rtx        gen_lsx_vmskltz_h                   (rtx, rtx);
extern rtx        gen_lsx_vmskltz_b                   (rtx, rtx);
extern rtx        gen_lsx_vsigncov_d                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vsigncov_w                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vsigncov_h                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vsigncov_b                  (rtx, rtx, rtx);
extern rtx        gen_absv2df2                        (rtx, rtx);
extern rtx        gen_absv4sf2                        (rtx, rtx);
extern rtx        gen_vfmaddv2df4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_vfmaddv4sf4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_vfmsubv2df4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_vfmsubv4sf4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_vfnmsubv2df4_nmsub4             (rtx, rtx, rtx, rtx);
extern rtx        gen_vfnmsubv4sf4_nmsub4             (rtx, rtx, rtx, rtx);
extern rtx        gen_vfnmaddv2df4_nmadd4             (rtx, rtx, rtx, rtx);
extern rtx        gen_vfnmaddv4sf4_nmadd4             (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vftintrne_w_s               (rtx, rtx);
extern rtx        gen_lsx_vftintrne_l_d               (rtx, rtx);
extern rtx        gen_lsx_vftintrp_w_s                (rtx, rtx);
extern rtx        gen_lsx_vftintrp_l_d                (rtx, rtx);
extern rtx        gen_lsx_vftintrm_w_s                (rtx, rtx);
extern rtx        gen_lsx_vftintrm_l_d                (rtx, rtx);
extern rtx        gen_lsx_vftint_w_d                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vffint_s_l                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vftintrz_w_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vftintrp_w_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vftintrm_w_d                (rtx, rtx, rtx);
extern rtx        gen_lsx_vftintrne_w_d               (rtx, rtx, rtx);
extern rtx        gen_lsx_vftinth_l_s                 (rtx, rtx);
extern rtx        gen_lsx_vftintl_l_s                 (rtx, rtx);
extern rtx        gen_lsx_vffinth_d_w                 (rtx, rtx);
extern rtx        gen_lsx_vffintl_d_w                 (rtx, rtx);
extern rtx        gen_lsx_vftintrzh_l_s               (rtx, rtx);
extern rtx        gen_lsx_vftintrzl_l_s               (rtx, rtx);
extern rtx        gen_lsx_vftintrph_l_s               (rtx, rtx);
extern rtx        gen_lsx_vftintrpl_l_s               (rtx, rtx);
extern rtx        gen_lsx_vftintrmh_l_s               (rtx, rtx);
extern rtx        gen_lsx_vftintrml_l_s               (rtx, rtx);
extern rtx        gen_lsx_vftintrneh_l_s              (rtx, rtx);
extern rtx        gen_lsx_vftintrnel_l_s              (rtx, rtx);
extern rtx        gen_lsx_vfrintrne_s                 (rtx, rtx);
extern rtx        gen_lsx_vfrintrne_d                 (rtx, rtx);
extern rtx        gen_lsx_vfrintrz_s                  (rtx, rtx);
extern rtx        gen_lsx_vfrintrz_d                  (rtx, rtx);
extern rtx        gen_lsx_vfrintrp_s                  (rtx, rtx);
extern rtx        gen_lsx_vfrintrp_d                  (rtx, rtx);
extern rtx        gen_lsx_vfrintrm_s                  (rtx, rtx);
extern rtx        gen_lsx_vfrintrm_d                  (rtx, rtx);
extern rtx        gen_lsx_vldrepl_d_f_insn            (rtx, rtx, rtx);
extern rtx        gen_lsx_vldrepl_w_f_insn            (rtx, rtx, rtx);
extern rtx        gen_lsx_vldrepl_d_insn              (rtx, rtx, rtx);
extern rtx        gen_lsx_vldrepl_w_insn              (rtx, rtx, rtx);
extern rtx        gen_lsx_vldrepl_h_insn              (rtx, rtx, rtx);
extern rtx        gen_lsx_vldrepl_b_insn              (rtx, rtx, rtx);
extern rtx        gen_lsx_vldrepl_d_f_insn_0          (rtx, rtx);
extern rtx        gen_lsx_vldrepl_w_f_insn_0          (rtx, rtx);
extern rtx        gen_lsx_vldrepl_d_insn_0            (rtx, rtx);
extern rtx        gen_lsx_vldrepl_w_insn_0            (rtx, rtx);
extern rtx        gen_lsx_vldrepl_h_insn_0            (rtx, rtx);
extern rtx        gen_lsx_vldrepl_b_insn_0            (rtx, rtx);
extern rtx        gen_lsx_vstelm_d_f_insn             (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_w_f_insn             (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_d_insn               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_w_insn               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_h_insn               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_b_insn               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_d_f_insn_0           (rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_w_f_insn_0           (rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_d_insn_0             (rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_w_insn_0             (rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_h_insn_0             (rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_b_insn_0             (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrln_w_d                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrln_h_w                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrln_b_h                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrn_w_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrn_h_w                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrn_b_h                 (rtx, rtx, rtx);
extern rtx        gen_vornv2di3                       (rtx, rtx, rtx);
extern rtx        gen_vornv4si3                       (rtx, rtx, rtx);
extern rtx        gen_vornv8hi3                       (rtx, rtx, rtx);
extern rtx        gen_vornv16qi3                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vldi                        (rtx, rtx);
extern rtx        gen_lsx_vshuf_b                     (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vldx                        (rtx, rtx, rtx);
extern rtx        gen_lsx_vstx                        (rtx, rtx, rtx);
extern rtx        gen_lsx_vextl_qu_du                 (rtx, rtx);
extern rtx        gen_lsx_vseteqz_v                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwev_d_w                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwev_d_wu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwev_d_w                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwev_d_wu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwev_d_w                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwev_d_wu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwev_w_h                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwev_w_hu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwev_w_h                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwev_w_hu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwev_w_h                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwev_w_hu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwev_h_b                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwev_h_bu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwev_h_b                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwev_h_bu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwev_h_b                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwev_h_bu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwod_d_w                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwod_d_wu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwod_d_w                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwod_d_wu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwod_d_w                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwod_d_wu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwod_w_h                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwod_w_hu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwod_w_h                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwod_w_hu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwod_w_h                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwod_w_hu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwod_h_b                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwod_h_bu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwod_h_b                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwod_h_bu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwod_h_b                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwod_h_bu                (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwev_d_wu_w              (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwev_d_wu_w              (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwev_w_hu_h              (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwev_w_hu_h              (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwev_h_bu_b              (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwev_h_bu_b              (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwod_d_wu_w              (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwod_d_wu_w              (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwod_w_hu_h              (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwod_w_hu_h              (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwod_h_bu_b              (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwod_h_bu_b              (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwev_q_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwev_q_du                (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwod_q_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwod_q_du                (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwev_q_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwev_q_du                (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwod_q_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vsubwod_q_du                (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwev_q_du_d              (rtx, rtx, rtx);
extern rtx        gen_lsx_vaddwod_q_du_d              (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwev_q_du_d              (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwod_q_du_d              (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwev_q_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwev_q_du                (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwod_q_d                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vmulwod_q_du                (rtx, rtx, rtx);
extern rtx        gen_lsx_vhaddw_q_d                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vhaddw_qu_du                (rtx, rtx, rtx);
extern rtx        gen_lsx_vhsubw_q_d                  (rtx, rtx, rtx);
extern rtx        gen_lsx_vhsubw_qu_du                (rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwev_d_w                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwev_d_wu               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwev_w_h                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwev_w_hu               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwev_h_b                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwev_h_bu               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwod_d_w                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwod_d_wu               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwod_w_h                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwod_w_hu               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwod_h_b                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwod_h_bu               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwev_d_wu_w             (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwev_w_hu_h             (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwev_h_bu_b             (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwod_d_wu_w             (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwod_w_hu_h             (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwod_h_bu_b             (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwev_q_d                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwod_q_d                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwev_q_du               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwod_q_du               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwev_q_du_d             (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vmaddwod_q_du_d             (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vrotr_d                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vrotr_w                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vrotr_h                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vrotr_b                     (rtx, rtx, rtx);
extern rtx        gen_lsx_vadd_q                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vsub_q                      (rtx, rtx, rtx);
extern rtx        gen_lsx_vmskgez_b                   (rtx, rtx);
extern rtx        gen_lsx_vmsknz_b                    (rtx, rtx);
extern rtx        gen_lsx_vexth_h_b                   (rtx, rtx);
extern rtx        gen_lsx_vexth_hu_bu                 (rtx, rtx);
extern rtx        gen_lsx_vexth_w_h                   (rtx, rtx);
extern rtx        gen_lsx_vexth_wu_hu                 (rtx, rtx);
extern rtx        gen_lsx_vexth_d_w                   (rtx, rtx);
extern rtx        gen_lsx_vexth_du_wu                 (rtx, rtx);
extern rtx        gen_lsx_vexth_q_d                   (rtx, rtx);
extern rtx        gen_lsx_vexth_qu_du                 (rtx, rtx);
extern rtx        gen_lsx_vrotri_d                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vrotri_w                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vrotri_h                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vrotri_b                    (rtx, rtx, rtx);
extern rtx        gen_lsx_vextl_q_d                   (rtx, rtx);
extern rtx        gen_lsx_vsrlni_d_q                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlni_w_d                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlni_h_w                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlni_b_h                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlrni_d_q                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlrni_w_d                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlrni_h_w                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrlrni_b_h                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlni_d_q                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlni_w_d                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlni_h_w                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlni_b_h                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlni_du_q                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlni_wu_d                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlni_hu_w                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlni_bu_h                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrni_d_q                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrni_w_d                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrni_h_w                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrni_b_h                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrni_du_q               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrni_wu_d               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrni_hu_w               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrlrni_bu_h               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrani_d_q                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrani_w_d                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrani_h_w                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrani_b_h                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrarni_d_q                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrarni_w_d                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrarni_h_w                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vsrarni_b_h                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrani_d_q                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrani_w_d                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrani_h_w                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrani_b_h                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrani_du_q                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrani_wu_d                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrani_hu_w                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrani_bu_h                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarni_d_q                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarni_w_d                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarni_h_w                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarni_b_h                (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarni_du_q               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarni_wu_d               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarni_hu_w               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vssrarni_bu_h               (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vpermi_w                    (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_pack_trunc_v4di             (rtx, rtx, rtx);
extern rtx        gen_vec_pack_trunc_v8si             (rtx, rtx, rtx);
extern rtx        gen_vec_pack_trunc_v16hi            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvinsgr2vr_d               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvinsgr2vr_w               (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_concatv4di                  (rtx, rtx, rtx);
extern rtx        gen_vec_concatv8si                  (rtx, rtx, rtx);
extern rtx        gen_vec_concatv16hi                 (rtx, rtx, rtx);
extern rtx        gen_vec_concatv32qi                 (rtx, rtx, rtx);
extern rtx        gen_vec_concatv4df                  (rtx, rtx, rtx);
extern rtx        gen_vec_concatv8sf                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvperm_w                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvperm_w_f                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_d_v4df             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_d_v8sf             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_d_v4di             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_d_v8si             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_d_v16hi            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_d_v32qi            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_d_v4di_1           (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_d_v4df_1           (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_q_v4df             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_q_v8sf             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_q_v4di             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_q_v8si             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_q_v16hi            (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_q_v32qi            (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickve2gr_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickve2gr_du             (rtx, rtx, rtx);
extern rtx        gen_movv4df_lasx                    (rtx, rtx);
extern rtx        gen_movv8sf_lasx                    (rtx, rtx);
extern rtx        gen_movv4di_lasx                    (rtx, rtx);
extern rtx        gen_movv8si_lasx                    (rtx, rtx);
extern rtx        gen_movv16hi_lasx                   (rtx, rtx);
extern rtx        gen_movv32qi_lasx                   (rtx, rtx);
extern rtx        gen_addv4di3                        (rtx, rtx, rtx);
extern rtx        gen_addv8si3                        (rtx, rtx, rtx);
extern rtx        gen_addv16hi3                       (rtx, rtx, rtx);
extern rtx        gen_addv32qi3                       (rtx, rtx, rtx);
extern rtx        gen_subv4di3                        (rtx, rtx, rtx);
extern rtx        gen_subv8si3                        (rtx, rtx, rtx);
extern rtx        gen_subv16hi3                       (rtx, rtx, rtx);
extern rtx        gen_subv32qi3                       (rtx, rtx, rtx);
extern rtx        gen_mulv4di3                        (rtx, rtx, rtx);
extern rtx        gen_mulv8si3                        (rtx, rtx, rtx);
extern rtx        gen_mulv16hi3                       (rtx, rtx, rtx);
extern rtx        gen_mulv32qi3                       (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmadd_d                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmadd_w                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmadd_h                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmadd_b                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmsub_d                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmsub_w                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmsub_h                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmsub_b                   (rtx, rtx, rtx, rtx);
extern rtx        gen_divv4di3                        (rtx, rtx, rtx);
extern rtx        gen_divv8si3                        (rtx, rtx, rtx);
extern rtx        gen_divv16hi3                       (rtx, rtx, rtx);
extern rtx        gen_divv32qi3                       (rtx, rtx, rtx);
extern rtx        gen_udivv4di3                       (rtx, rtx, rtx);
extern rtx        gen_udivv8si3                       (rtx, rtx, rtx);
extern rtx        gen_udivv16hi3                      (rtx, rtx, rtx);
extern rtx        gen_udivv32qi3                      (rtx, rtx, rtx);
extern rtx        gen_modv4di3                        (rtx, rtx, rtx);
extern rtx        gen_modv8si3                        (rtx, rtx, rtx);
extern rtx        gen_modv16hi3                       (rtx, rtx, rtx);
extern rtx        gen_modv32qi3                       (rtx, rtx, rtx);
extern rtx        gen_umodv4di3                       (rtx, rtx, rtx);
extern rtx        gen_umodv8si3                       (rtx, rtx, rtx);
extern rtx        gen_umodv16hi3                      (rtx, rtx, rtx);
extern rtx        gen_umodv32qi3                      (rtx, rtx, rtx);
extern rtx        gen_xorv4di3                        (rtx, rtx, rtx);
extern rtx        gen_xorv8si3                        (rtx, rtx, rtx);
extern rtx        gen_xorv16hi3                       (rtx, rtx, rtx);
extern rtx        gen_xorv32qi3                       (rtx, rtx, rtx);
extern rtx        gen_iorv4df3                        (rtx, rtx, rtx);
extern rtx        gen_iorv8sf3                        (rtx, rtx, rtx);
extern rtx        gen_iorv4di3                        (rtx, rtx, rtx);
extern rtx        gen_iorv8si3                        (rtx, rtx, rtx);
extern rtx        gen_iorv16hi3                       (rtx, rtx, rtx);
extern rtx        gen_iorv32qi3                       (rtx, rtx, rtx);
extern rtx        gen_andv4df3                        (rtx, rtx, rtx);
extern rtx        gen_andv8sf3                        (rtx, rtx, rtx);
extern rtx        gen_andv4di3                        (rtx, rtx, rtx);
extern rtx        gen_andv8si3                        (rtx, rtx, rtx);
extern rtx        gen_andv16hi3                       (rtx, rtx, rtx);
extern rtx        gen_andv32qi3                       (rtx, rtx, rtx);
extern rtx        gen_one_cmplv4di2                   (rtx, rtx);
extern rtx        gen_one_cmplv8si2                   (rtx, rtx);
extern rtx        gen_one_cmplv16hi2                  (rtx, rtx);
extern rtx        gen_one_cmplv32qi2                  (rtx, rtx);
extern rtx        gen_vlshrv4di3                      (rtx, rtx, rtx);
extern rtx        gen_vlshrv8si3                      (rtx, rtx, rtx);
extern rtx        gen_vlshrv16hi3                     (rtx, rtx, rtx);
extern rtx        gen_vlshrv32qi3                     (rtx, rtx, rtx);
extern rtx        gen_vashrv4di3                      (rtx, rtx, rtx);
extern rtx        gen_vashrv8si3                      (rtx, rtx, rtx);
extern rtx        gen_vashrv16hi3                     (rtx, rtx, rtx);
extern rtx        gen_vashrv32qi3                     (rtx, rtx, rtx);
extern rtx        gen_vashlv4di3                      (rtx, rtx, rtx);
extern rtx        gen_vashlv8si3                      (rtx, rtx, rtx);
extern rtx        gen_vashlv16hi3                     (rtx, rtx, rtx);
extern rtx        gen_vashlv32qi3                     (rtx, rtx, rtx);
extern rtx        gen_addv4df3                        (rtx, rtx, rtx);
extern rtx        gen_addv8sf3                        (rtx, rtx, rtx);
extern rtx        gen_subv4df3                        (rtx, rtx, rtx);
extern rtx        gen_subv8sf3                        (rtx, rtx, rtx);
extern rtx        gen_mulv4df3                        (rtx, rtx, rtx);
extern rtx        gen_mulv8sf3                        (rtx, rtx, rtx);
extern rtx        gen_divv4df3                        (rtx, rtx, rtx);
extern rtx        gen_divv8sf3                        (rtx, rtx, rtx);
extern rtx        gen_fmav4df4                        (rtx, rtx, rtx, rtx);
extern rtx        gen_fmav8sf4                        (rtx, rtx, rtx, rtx);
extern rtx        gen_fnmav4df4                       (rtx, rtx, rtx, rtx);
extern rtx        gen_fnmav8sf4                       (rtx, rtx, rtx, rtx);
extern rtx        gen_sqrtv4df2                       (rtx, rtx);
extern rtx        gen_sqrtv8sf2                       (rtx, rtx);
extern rtx        gen_lasx_xvadda_d                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvadda_w                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvadda_h                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvadda_b                   (rtx, rtx, rtx);
extern rtx        gen_ssaddv4di3                      (rtx, rtx, rtx);
extern rtx        gen_ssaddv8si3                      (rtx, rtx, rtx);
extern rtx        gen_ssaddv16hi3                     (rtx, rtx, rtx);
extern rtx        gen_ssaddv32qi3                     (rtx, rtx, rtx);
extern rtx        gen_usaddv4di3                      (rtx, rtx, rtx);
extern rtx        gen_usaddv8si3                      (rtx, rtx, rtx);
extern rtx        gen_usaddv16hi3                     (rtx, rtx, rtx);
extern rtx        gen_usaddv32qi3                     (rtx, rtx, rtx);
extern rtx        gen_lasx_xvabsd_s_d                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvabsd_s_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvabsd_s_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvabsd_s_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvabsd_u_du                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvabsd_u_wu                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvabsd_u_hu                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvabsd_u_bu                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavg_s_d                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavg_s_w                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavg_s_h                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavg_s_b                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavg_u_du                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavg_u_wu                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavg_u_hu                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavg_u_bu                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavgr_s_d                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavgr_s_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavgr_s_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavgr_s_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavgr_u_du                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavgr_u_wu                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavgr_u_hu                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvavgr_u_bu                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitclr_d                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitclr_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitclr_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitclr_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitclri_d                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitclri_w                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitclri_h                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitclri_b                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitrev_d                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitrev_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitrev_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitrev_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitrevi_d                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitrevi_w                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitrevi_h                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitrevi_b                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitsel_d_f               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitsel_w_f               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitsel_d                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitsel_w                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitsel_h                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitsel_b                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitseli_b                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitset_d                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitset_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitset_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitset_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitseti_d                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitseti_w                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitseti_h                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbitseti_b                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvseq_d                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsle_d                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsle_du                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvslt_d                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvslt_du                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvseq_w                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsle_w                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsle_wu                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvslt_w                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvslt_wu                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvseq_h                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsle_h                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsle_hu                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvslt_h                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvslt_hu                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvseq_b                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsle_b                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsle_bu                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvslt_b                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvslt_bu                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfclass_d                 (rtx, rtx);
extern rtx        gen_lasx_xvfclass_s                 (rtx, rtx);
extern rtx        gen_lasx_xvfcmp_caf_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_caf_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cune_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cune_s              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cun_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cor_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_ceq_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cne_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cle_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_clt_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cueq_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cule_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cult_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cun_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cor_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_ceq_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cne_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cle_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_clt_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cueq_s              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cule_s              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_cult_s              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_saf_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sun_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sor_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_seq_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sne_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sueq_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sune_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sule_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sult_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sle_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_slt_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_saf_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sun_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sor_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_seq_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sne_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sueq_s              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sune_s              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sule_s              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sult_s              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_sle_s               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcmp_slt_s               (rtx, rtx, rtx);
extern rtx        gen_floatv4div4df2                  (rtx, rtx);
extern rtx        gen_floatv8siv8sf2                  (rtx, rtx);
extern rtx        gen_floatunsv4div4df2               (rtx, rtx);
extern rtx        gen_floatunsv8siv8sf2               (rtx, rtx);
extern rtx        gen_lasx_xvreplgr2vr_d              (rtx, rtx);
extern rtx        gen_lasx_xvreplgr2vr_w              (rtx, rtx);
extern rtx        gen_lasx_xvreplgr2vr_h              (rtx, rtx);
extern rtx        gen_lasx_xvreplgr2vr_b              (rtx, rtx);
extern rtx        gen_logbv4df2                       (rtx, rtx);
extern rtx        gen_logbv8sf2                       (rtx, rtx);
extern rtx        gen_smaxv4df3                       (rtx, rtx, rtx);
extern rtx        gen_smaxv8sf3                       (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfmaxa_d                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfmaxa_s                  (rtx, rtx, rtx);
extern rtx        gen_sminv4df3                       (rtx, rtx, rtx);
extern rtx        gen_sminv8sf3                       (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfmina_d                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfmina_s                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfrecip_d                 (rtx, rtx);
extern rtx        gen_lasx_xvfrecip_s                 (rtx, rtx);
extern rtx        gen_lasx_xvfrint_d                  (rtx, rtx);
extern rtx        gen_lasx_xvfrint_s                  (rtx, rtx);
extern rtx        gen_lasx_xvfrsqrt_d                 (rtx, rtx);
extern rtx        gen_lasx_xvfrsqrt_s                 (rtx, rtx);
extern rtx        gen_lasx_xvftint_s_l_d              (rtx, rtx);
extern rtx        gen_lasx_xvftint_s_w_s              (rtx, rtx);
extern rtx        gen_lasx_xvftint_u_lu_d             (rtx, rtx);
extern rtx        gen_lasx_xvftint_u_wu_s             (rtx, rtx);
extern rtx        gen_fix_truncv4dfv4di2              (rtx, rtx);
extern rtx        gen_fix_truncv8sfv8si2              (rtx, rtx);
extern rtx        gen_fixuns_truncv4dfv4di2           (rtx, rtx);
extern rtx        gen_fixuns_truncv8sfv8si2           (rtx, rtx);
extern rtx        gen_lasx_xvhaddw_h_b                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhaddw_hu_bu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhsubw_h_b                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhsubw_hu_bu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhaddw_w_h                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhaddw_wu_hu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhsubw_w_h                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhsubw_wu_hu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhaddw_d_w                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhaddw_du_wu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhsubw_d_w                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhsubw_du_wu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpackev_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpackev_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpackev_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpackev_w_f               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvilvh_b                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvilvh_h                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvilvh_w                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvilvh_w_f                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvilvh_d                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvilvh_d_f                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpackod_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpackod_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpackod_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpackod_w_f               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvilvl_b                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvilvl_h                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvilvl_w                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvilvl_w_f                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvilvl_d                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvilvl_d_f                 (rtx, rtx, rtx);
extern rtx        gen_smaxv4di3                       (rtx, rtx, rtx);
extern rtx        gen_smaxv8si3                       (rtx, rtx, rtx);
extern rtx        gen_smaxv16hi3                      (rtx, rtx, rtx);
extern rtx        gen_smaxv32qi3                      (rtx, rtx, rtx);
extern rtx        gen_umaxv4di3                       (rtx, rtx, rtx);
extern rtx        gen_umaxv8si3                       (rtx, rtx, rtx);
extern rtx        gen_umaxv16hi3                      (rtx, rtx, rtx);
extern rtx        gen_umaxv32qi3                      (rtx, rtx, rtx);
extern rtx        gen_sminv4di3                       (rtx, rtx, rtx);
extern rtx        gen_sminv8si3                       (rtx, rtx, rtx);
extern rtx        gen_sminv16hi3                      (rtx, rtx, rtx);
extern rtx        gen_sminv32qi3                      (rtx, rtx, rtx);
extern rtx        gen_uminv4di3                       (rtx, rtx, rtx);
extern rtx        gen_uminv8si3                       (rtx, rtx, rtx);
extern rtx        gen_uminv16hi3                      (rtx, rtx, rtx);
extern rtx        gen_uminv32qi3                      (rtx, rtx, rtx);
extern rtx        gen_lasx_xvclo_d                    (rtx, rtx);
extern rtx        gen_lasx_xvclo_w                    (rtx, rtx);
extern rtx        gen_lasx_xvclo_h                    (rtx, rtx);
extern rtx        gen_lasx_xvclo_b                    (rtx, rtx);
extern rtx        gen_clzv4di2                        (rtx, rtx);
extern rtx        gen_clzv8si2                        (rtx, rtx);
extern rtx        gen_clzv16hi2                       (rtx, rtx);
extern rtx        gen_clzv32qi2                       (rtx, rtx);
extern rtx        gen_lasx_xvnor_d                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvnor_w                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvnor_h                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvnor_b                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickev_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickev_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickev_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickev_w_f               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickod_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickod_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickod_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickod_w_f               (rtx, rtx, rtx);
extern rtx        gen_popcountv4di2                   (rtx, rtx);
extern rtx        gen_popcountv8si2                   (rtx, rtx);
extern rtx        gen_popcountv16hi2                  (rtx, rtx);
extern rtx        gen_popcountv32qi2                  (rtx, rtx);
extern rtx        gen_lasx_xvsat_s_d                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsat_s_w                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsat_s_h                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsat_s_b                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsat_u_du                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsat_u_wu                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsat_u_hu                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsat_u_bu                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf4i_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf4i_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf4i_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf4i_w_f               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf4i_w_1               (rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf4i_w_f_1             (rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrar_d                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrar_w                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrar_h                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrar_b                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrari_d                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrari_w                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrari_h                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrari_b                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlr_d                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlr_w                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlr_h                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlr_b                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlri_d                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlri_w                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlri_h                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlri_b                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssub_s_d                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssub_s_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssub_s_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssub_s_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssub_u_du                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssub_u_wu                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssub_u_hu                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssub_u_bu                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf_d_f                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf_w_f                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf_d                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf_w                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf_h                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf_b                   (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvreplve0_d_f              (rtx, rtx);
extern rtx        gen_lasx_xvreplve0_w_f              (rtx, rtx);
extern rtx        gen_lasx_xvreplve0_d                (rtx, rtx);
extern rtx        gen_lasx_xvreplve0_w                (rtx, rtx);
extern rtx        gen_lasx_xvreplve0_h                (rtx, rtx);
extern rtx        gen_lasx_xvreplve0_b                (rtx, rtx);
extern rtx        gen_lasx_xvrepl128vei_b_internal    (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvrepl128vei_h_internal    (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvrepl128vei_w_internal    (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvrepl128vei_d_internal    (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvrepl128vei_d_f           (rtx, rtx, rtx);
extern rtx        gen_lasx_xvrepl128vei_w_f           (rtx, rtx, rtx);
extern rtx        gen_lasx_xvrepl128vei_d             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvrepl128vei_w             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvrepl128vei_h             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvrepl128vei_b             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvreplve0_d_f_scalar       (rtx, rtx);
extern rtx        gen_lasx_xvreplve0_w_f_scalar       (rtx, rtx);
extern rtx        gen_lasx_xvreplve0_q                (rtx, rtx);
extern rtx        gen_lasx_xvfcvt_h_s                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcvt_s_d                 (rtx, rtx, rtx);
extern rtx        gen_vec_pack_trunc_v4df             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfcvth_s_h                (rtx, rtx);
extern rtx        gen_lasx_xvfcvth_d_s                (rtx, rtx);
extern rtx        gen_lasx_xvfcvth_d_insn             (rtx, rtx);
extern rtx        gen_lasx_xvfcvtl_s_h                (rtx, rtx);
extern rtx        gen_lasx_xvfcvtl_d_s                (rtx, rtx);
extern rtx        gen_lasx_xvfcvtl_d_insn             (rtx, rtx);
extern rtx        gen_lasx_xbz_d_f                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xbnz_d_f                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xbz_w_f                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xbnz_w_f                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xbz_d                      (rtx, rtx, rtx);
extern rtx        gen_lasx_xbnz_d                     (rtx, rtx, rtx);
extern rtx        gen_lasx_xbz_w                      (rtx, rtx, rtx);
extern rtx        gen_lasx_xbnz_w                     (rtx, rtx, rtx);
extern rtx        gen_lasx_xbz_h                      (rtx, rtx, rtx);
extern rtx        gen_lasx_xbnz_h                     (rtx, rtx, rtx);
extern rtx        gen_lasx_xbz_b                      (rtx, rtx, rtx);
extern rtx        gen_lasx_xbnz_b                     (rtx, rtx, rtx);
extern rtx        gen_lasx_xbz_v_d_f                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xbnz_v_d_f                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xbz_v_w_f                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xbnz_v_w_f                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xbz_v_d                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xbnz_v_d                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xbz_v_w                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xbnz_v_w                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xbz_v_h                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xbnz_v_h                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xbz_v_b                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xbnz_v_b                   (rtx, rtx, rtx);
extern rtx        gen_lasx_vext2xv_h_b                (rtx, rtx);
extern rtx        gen_lasx_vext2xv_hu_bu              (rtx, rtx);
extern rtx        gen_lasx_vext2xv_w_h                (rtx, rtx);
extern rtx        gen_lasx_vext2xv_wu_hu              (rtx, rtx);
extern rtx        gen_lasx_vext2xv_d_w                (rtx, rtx);
extern rtx        gen_lasx_vext2xv_du_wu              (rtx, rtx);
extern rtx        gen_lasx_vext2xv_w_b                (rtx, rtx);
extern rtx        gen_lasx_vext2xv_wu_bu              (rtx, rtx);
extern rtx        gen_lasx_vext2xv_d_h                (rtx, rtx);
extern rtx        gen_lasx_vext2xv_du_hu              (rtx, rtx);
extern rtx        gen_lasx_vext2xv_d_b                (rtx, rtx);
extern rtx        gen_lasx_vext2xv_du_bu              (rtx, rtx);
extern rtx        gen_xvandnv4df3                     (rtx, rtx, rtx);
extern rtx        gen_xvandnv8sf3                     (rtx, rtx, rtx);
extern rtx        gen_xvandnv4di3                     (rtx, rtx, rtx);
extern rtx        gen_xvandnv8si3                     (rtx, rtx, rtx);
extern rtx        gen_xvandnv16hi3                    (rtx, rtx, rtx);
extern rtx        gen_xvandnv32qi3                    (rtx, rtx, rtx);
extern rtx        gen_absv4di2                        (rtx, rtx);
extern rtx        gen_absv8si2                        (rtx, rtx);
extern rtx        gen_absv16hi2                       (rtx, rtx);
extern rtx        gen_absv32qi2                       (rtx, rtx);
extern rtx        gen_negv4di2                        (rtx, rtx);
extern rtx        gen_negv8si2                        (rtx, rtx);
extern rtx        gen_negv16hi2                       (rtx, rtx);
extern rtx        gen_negv32qi2                       (rtx, rtx);
extern rtx        gen_lasx_xvmuh_s_d                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmuh_s_w                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmuh_s_h                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmuh_s_b                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmuh_u_du                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmuh_u_wu                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmuh_u_hu                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmuh_u_bu                 (rtx, rtx, rtx);
extern rtx        gen_lasx_mxvextw_u_d                (rtx, rtx);
extern rtx        gen_lasx_xvsllwil_s_d_w             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsllwil_s_w_h             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsllwil_s_h_b             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsllwil_u_du_wu           (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsllwil_u_wu_hu           (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsllwil_u_hu_bu           (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsran_w_d                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsran_h_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsran_b_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssran_s_w_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssran_s_h_w              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssran_s_b_h              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssran_u_wu_d             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssran_u_hu_w             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssran_u_bu_h             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrarn_w_d                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrarn_h_w                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrarn_b_h                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarn_s_w_d             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarn_s_h_w             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarn_s_b_h             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarn_u_wu_d            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarn_u_hu_w            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarn_u_bu_h            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrln_w_d                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrln_h_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrln_b_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrln_u_wu_d             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrln_u_hu_w             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrln_u_bu_h             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlrn_w_d                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlrn_h_w                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlrn_b_h                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrn_u_wu_d            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrn_u_hu_w            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrn_u_bu_h            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvfrstpi_h                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvfrstpi_b                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvfrstp_h                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvfrstp_b                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvshuf4i_d                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvbsrl_d                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbsrl_w                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbsrl_h                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbsrl_b                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbsll_d                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbsll_w                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbsll_h                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvbsll_b                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvextrins_d                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvextrins_w                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvextrins_h                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvextrins_b                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmskltz_d                 (rtx, rtx);
extern rtx        gen_lasx_xvmskltz_w                 (rtx, rtx);
extern rtx        gen_lasx_xvmskltz_h                 (rtx, rtx);
extern rtx        gen_lasx_xvmskltz_b                 (rtx, rtx);
extern rtx        gen_lasx_xvsigncov_d                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsigncov_w                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsigncov_h                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsigncov_b                (rtx, rtx, rtx);
extern rtx        gen_absv4df2                        (rtx, rtx);
extern rtx        gen_absv8sf2                        (rtx, rtx);
extern rtx        gen_negv4df2                        (rtx, rtx);
extern rtx        gen_negv8sf2                        (rtx, rtx);
extern rtx        gen_xvfmaddv4df4                    (rtx, rtx, rtx, rtx);
extern rtx        gen_xvfmaddv8sf4                    (rtx, rtx, rtx, rtx);
extern rtx        gen_xvfmsubv4df4                    (rtx, rtx, rtx, rtx);
extern rtx        gen_xvfmsubv8sf4                    (rtx, rtx, rtx, rtx);
extern rtx        gen_xvfnmsubv4df4_nmsub4            (rtx, rtx, rtx, rtx);
extern rtx        gen_xvfnmsubv8sf4_nmsub4            (rtx, rtx, rtx, rtx);
extern rtx        gen_xvfnmaddv4df4_nmadd4            (rtx, rtx, rtx, rtx);
extern rtx        gen_xvfnmaddv8sf4_nmadd4            (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvftintrne_w_s             (rtx, rtx);
extern rtx        gen_lasx_xvftintrne_l_d             (rtx, rtx);
extern rtx        gen_lasx_xvftintrp_w_s              (rtx, rtx);
extern rtx        gen_lasx_xvftintrp_l_d              (rtx, rtx);
extern rtx        gen_lasx_xvftintrm_w_s              (rtx, rtx);
extern rtx        gen_lasx_xvftintrm_l_d              (rtx, rtx);
extern rtx        gen_lasx_xvftint_w_d                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvffint_s_l                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvftintrz_w_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvftintrp_w_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvftintrm_w_d              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvftintrne_w_d             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvftinth_l_s               (rtx, rtx);
extern rtx        gen_lasx_xvftintl_l_s               (rtx, rtx);
extern rtx        gen_lasx_xvffinth_d_w               (rtx, rtx);
extern rtx        gen_lasx_xvffintl_d_w               (rtx, rtx);
extern rtx        gen_lasx_xvftintrzh_l_s             (rtx, rtx);
extern rtx        gen_lasx_xvftintrzl_l_s             (rtx, rtx);
extern rtx        gen_lasx_xvftintrph_l_s             (rtx, rtx);
extern rtx        gen_lasx_xvftintrpl_l_s             (rtx, rtx);
extern rtx        gen_lasx_xvftintrmh_l_s             (rtx, rtx);
extern rtx        gen_lasx_xvftintrml_l_s             (rtx, rtx);
extern rtx        gen_lasx_xvftintrneh_l_s            (rtx, rtx);
extern rtx        gen_lasx_xvftintrnel_l_s            (rtx, rtx);
extern rtx        gen_lasx_xvfrintrne_s               (rtx, rtx);
extern rtx        gen_lasx_xvfrintrne_d               (rtx, rtx);
extern rtx        gen_lasx_xvfrintrz_s                (rtx, rtx);
extern rtx        gen_lasx_xvfrintrz_d                (rtx, rtx);
extern rtx        gen_lasx_xvfrintrp_s                (rtx, rtx);
extern rtx        gen_lasx_xvfrintrp_d                (rtx, rtx);
extern rtx        gen_lasx_xvfrintrm_s                (rtx, rtx);
extern rtx        gen_lasx_xvfrintrm_d                (rtx, rtx);
extern rtx        gen_lasx_xvldrepl_d_f_insn          (rtx, rtx, rtx);
extern rtx        gen_lasx_xvldrepl_w_f_insn          (rtx, rtx, rtx);
extern rtx        gen_lasx_xvldrepl_d_insn            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvldrepl_w_insn            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvldrepl_h_insn            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvldrepl_b_insn            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvldrepl_d_f_insn_0        (rtx, rtx);
extern rtx        gen_lasx_xvldrepl_w_f_insn_0        (rtx, rtx);
extern rtx        gen_lasx_xvldrepl_d_insn_0          (rtx, rtx);
extern rtx        gen_lasx_xvldrepl_w_insn_0          (rtx, rtx);
extern rtx        gen_lasx_xvldrepl_h_insn_0          (rtx, rtx);
extern rtx        gen_lasx_xvldrepl_b_insn_0          (rtx, rtx);
extern rtx        gen_lasx_xvaddwev_h_b               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwev_h_bu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwev_h_b               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwev_h_bu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwev_h_b               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwev_h_bu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwev_w_h               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwev_w_hu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwev_w_h               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwev_w_hu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwev_w_h               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwev_w_hu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwev_d_w               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwev_d_wu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwev_d_w               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwev_d_wu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwev_d_w               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwev_d_wu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwev_q_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwev_q_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwev_q_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwod_h_b               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwod_h_bu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwod_h_b               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwod_h_bu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwod_h_b               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwod_h_bu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwod_w_h               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwod_w_hu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwod_w_h               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwod_w_hu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwod_w_h               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwod_w_hu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwod_d_w               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwod_d_wu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwod_d_w               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwod_d_wu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwod_d_w               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwod_d_wu              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwod_q_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwod_q_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwod_q_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwev_q_du              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwev_q_du              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwev_q_du              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwod_q_du              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsubwod_q_du              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwod_q_du              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwev_h_bu_b            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwev_h_bu_b            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwev_w_hu_h            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwev_w_hu_h            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwev_d_wu_w            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwev_d_wu_w            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwod_h_bu_b            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwod_h_bu_b            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwod_w_hu_h            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwod_w_hu_h            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwod_d_wu_w            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwod_d_wu_w            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwev_h_b              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwev_h_bu             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwev_w_h              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwev_w_hu             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwev_d_w              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwev_d_wu             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwev_q_d              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwod_h_b              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwod_h_bu             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwod_w_h              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwod_w_hu             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwod_d_w              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwod_d_wu             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwod_q_d              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwev_q_du             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwod_q_du             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwev_h_bu_b           (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwev_w_hu_h           (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwev_d_wu_w           (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwev_q_du_d           (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwod_h_bu_b           (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwod_w_hu_h           (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwod_d_wu_w           (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvmaddwod_q_du_d           (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvhaddw_q_d                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhsubw_q_d                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhaddw_qu_du              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvhsubw_qu_du              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvrotr_d                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvrotr_w                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvrotr_h                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvrotr_b                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvadd_q                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvsub_q                    (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrln_w_d                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrln_h_w                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrln_b_h                (rtx, rtx, rtx);
extern rtx        gen_lasx_xvreplve_d_f               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvreplve_w_f               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvreplve_d                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvreplve_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvreplve_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvreplve_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwev_q_du_d            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvaddwod_q_du_d            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwev_q_du_d            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmulwod_q_du_d            (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickve2gr_w              (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickve2gr_wu             (rtx, rtx, rtx);
extern rtx        gen_lasx_xvmskgez_b                 (rtx, rtx);
extern rtx        gen_lasx_xvmsknz_b                  (rtx, rtx);
extern rtx        gen_lasx_xvexth_h_b                 (rtx, rtx);
extern rtx        gen_lasx_xvexth_hu_bu               (rtx, rtx);
extern rtx        gen_lasx_xvexth_w_h                 (rtx, rtx);
extern rtx        gen_lasx_xvexth_wu_hu               (rtx, rtx);
extern rtx        gen_lasx_xvexth_d_w                 (rtx, rtx);
extern rtx        gen_lasx_xvexth_du_wu               (rtx, rtx);
extern rtx        gen_lasx_xvexth_q_d                 (rtx, rtx);
extern rtx        gen_lasx_xvexth_qu_du               (rtx, rtx);
extern rtx        gen_lasx_xvrotri_d                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvrotri_w                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvrotri_h                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvrotri_b                  (rtx, rtx, rtx);
extern rtx        gen_lasx_xvextl_q_d                 (rtx, rtx);
extern rtx        gen_lasx_xvsrlni_d_q                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlni_w_d                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlni_h_w                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlni_b_h                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlrni_d_q               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlrni_w_d               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlrni_h_w               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrlrni_b_h               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlni_d_q               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlni_w_d               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlni_h_w               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlni_b_h               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlni_du_q              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlni_wu_d              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlni_hu_w              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlni_bu_h              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrni_d_q              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrni_w_d              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrni_h_w              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrni_b_h              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrni_du_q             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrni_wu_d             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrni_hu_w             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrni_bu_h             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrani_d_q                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrani_w_d                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrani_h_w                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrani_b_h                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrarni_d_q               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrarni_w_d               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrarni_h_w               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvsrarni_b_h               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrani_d_q               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrani_w_d               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrani_h_w               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrani_b_h               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrani_du_q              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrani_wu_d              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrani_hu_w              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrani_bu_h              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarni_d_q              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarni_w_d              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarni_h_w              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarni_b_h              (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarni_du_q             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarni_wu_d             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarni_hu_w             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrarni_bu_h             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_w                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_w_f                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_w_1                (rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpermi_w_f_1              (rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_d_f_insn           (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_w_f_insn           (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_d_insn             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_w_insn             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_h_insn             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_b_insn             (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_d_insn_0           (rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_d_f_insn_0         (rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_w_insn_0           (rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_w_f_insn_0         (rtx, rtx, rtx);
extern rtx        gen_lasx_xvinsve0_d                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvinsve0_d_f               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvinsve0_w                 (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvinsve0_w_f               (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvinsve0_d_f_scalar        (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvinsve0_w_f_scalar        (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickve_d                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickve_d_f               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickve_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickve_w_f               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickve_d_f_scalar        (rtx, rtx, rtx);
extern rtx        gen_lasx_xvpickve_w_f_scalar        (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrn_w_d               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrn_h_w               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvssrlrn_b_h               (rtx, rtx, rtx);
extern rtx        gen_xvornv4di3                      (rtx, rtx, rtx);
extern rtx        gen_xvornv8si3                      (rtx, rtx, rtx);
extern rtx        gen_xvornv16hi3                     (rtx, rtx, rtx);
extern rtx        gen_xvornv32qi3                     (rtx, rtx, rtx);
extern rtx        gen_lasx_xvextl_qu_du               (rtx, rtx);
extern rtx        gen_lasx_xvldi                      (rtx, rtx);
extern rtx        gen_lasx_xvldx                      (rtx, rtx, rtx);
extern rtx        gen_lasx_xvstx                      (rtx, rtx, rtx);
extern rtx        gen_vec_widen_smult_even_v8si       (rtx, rtx, rtx);
extern rtx        gen_vec_widen_umult_even_v8si       (rtx, rtx, rtx);
extern rtx        gen_mulditi3                        (rtx, rtx, rtx);
extern rtx        gen_umulditi3                       (rtx, rtx, rtx);
extern rtx        gen_mulsidi3                        (rtx, rtx, rtx);
extern rtx        gen_umulsidi3                       (rtx, rtx, rtx);
extern rtx        gen_divsf3                          (rtx, rtx, rtx);
extern rtx        gen_divdf3                          (rtx, rtx, rtx);
extern rtx        gen_divsi3                          (rtx, rtx, rtx);
extern rtx        gen_udivsi3                         (rtx, rtx, rtx);
extern rtx        gen_modsi3                          (rtx, rtx, rtx);
extern rtx        gen_umodsi3                         (rtx, rtx, rtx);
extern rtx        gen_divdi3                          (rtx, rtx, rtx);
extern rtx        gen_udivdi3                         (rtx, rtx, rtx);
extern rtx        gen_moddi3                          (rtx, rtx, rtx);
extern rtx        gen_umoddi3                         (rtx, rtx, rtx);
extern rtx        gen_rsqrtsf2                        (rtx, rtx);
extern rtx        gen_zero_extendsidi2                (rtx, rtx);
extern rtx        gen_zero_extendqisi2                (rtx, rtx);
extern rtx        gen_zero_extendqidi2                (rtx, rtx);
extern rtx        gen_zero_extendhisi2                (rtx, rtx);
extern rtx        gen_zero_extendhidi2                (rtx, rtx);
extern rtx        gen_zero_extendqihi2                (rtx, rtx);
extern rtx        gen_extendqisi2                     (rtx, rtx);
extern rtx        gen_extendqidi2                     (rtx, rtx);
extern rtx        gen_extendhisi2                     (rtx, rtx);
extern rtx        gen_extendhidi2                     (rtx, rtx);
extern rtx        gen_extendqihi2                     (rtx, rtx);
extern rtx        gen_fixuns_truncdfsi2               (rtx, rtx);
extern rtx        gen_fixuns_truncdfdi2               (rtx, rtx);
extern rtx        gen_fixuns_truncsfsi2               (rtx, rtx);
extern rtx        gen_fixuns_truncsfdi2               (rtx, rtx);
extern rtx        gen_extzvsi                         (rtx, rtx, rtx, rtx);
extern rtx        gen_extzvdi                         (rtx, rtx, rtx, rtx);
extern rtx        gen_insvsi                          (rtx, rtx, rtx, rtx);
extern rtx        gen_insvdi                          (rtx, rtx, rtx, rtx);
extern rtx        gen_movdi                           (rtx, rtx);
extern rtx        gen_movsi                           (rtx, rtx);
extern rtx        gen_movhi                           (rtx, rtx);
extern rtx        gen_movqi                           (rtx, rtx);
extern rtx        gen_movsf                           (rtx, rtx);
extern rtx        gen_movdf                           (rtx, rtx);
extern rtx        gen_movti                           (rtx, rtx);
extern rtx        gen_movtf                           (rtx, rtx);
extern rtx        gen_move_doubleword_fprdf           (rtx, rtx);
extern rtx        gen_move_doubleword_fprdi           (rtx, rtx);
extern rtx        gen_move_doubleword_fprtf           (rtx, rtx);
extern rtx        gen_movsicc                         (rtx, rtx, rtx, rtx);
extern rtx        gen_movdicc                         (rtx, rtx, rtx, rtx);
extern rtx        gen_movsfcc                         (rtx, rtx, rtx, rtx);
extern rtx        gen_movdfcc                         (rtx, rtx, rtx, rtx);
extern rtx        gen_clear_cache                     (rtx, rtx);
extern rtx        gen_movmemsi                        (rtx, rtx, rtx, rtx);
extern rtx        gen_cbranchsi4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_cbranchdi4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_cbranchsf4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_cbranchdf4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_condjump                        (rtx, rtx);
extern rtx        gen_cstoresi4                       (rtx, rtx, rtx, rtx);
extern rtx        gen_cstoredi4                       (rtx, rtx, rtx, rtx);
extern rtx        gen_jump                            (rtx);
extern rtx        gen_indirect_jump                   (rtx);
extern rtx        gen_tablejump                       (rtx, rtx);
extern rtx        gen_prologue                        (void);
extern rtx        gen_epilogue                        (void);
extern rtx        gen_sibcall_epilogue                (void);
extern rtx        gen_return                          (void);
extern rtx        gen_simple_return                   (void);
extern rtx        gen_eh_return                       (rtx);
extern rtx        gen_sibcall                         (rtx, rtx, rtx, rtx);
extern rtx        gen_sibcall_value                   (rtx, rtx, rtx, rtx);
extern rtx        gen_call                            (rtx, rtx, rtx, rtx);
extern rtx        gen_call_value                      (rtx, rtx, rtx, rtx);
extern rtx        gen_untyped_call                    (rtx, rtx, rtx);
extern rtx        gen_mem_thread_fence                (rtx);
extern rtx        gen_atomic_compare_and_swapsi       (rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_compare_and_swapdi       (rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_test_and_set             (rtx, rtx, rtx);
extern rtx        gen_atomic_compare_and_swapqi       (rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_compare_and_swaphi       (rtx, rtx, rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_exchangeqi               (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_exchangehi               (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_addqi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_addhi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_subqi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_subhi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_andqi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_andhi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_xorqi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_xorhi              (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_orqi               (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_orhi               (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_nandqi             (rtx, rtx, rtx, rtx);
extern rtx        gen_atomic_fetch_nandhi             (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_initv2dfdf                  (rtx, rtx);
extern rtx        gen_vec_initv4sfsf                  (rtx, rtx);
extern rtx        gen_vec_initv2didi                  (rtx, rtx);
extern rtx        gen_vec_initv4sisi                  (rtx, rtx);
extern rtx        gen_vec_initv8hihi                  (rtx, rtx);
extern rtx        gen_vec_initv16qiqi                 (rtx, rtx);
extern rtx        gen_vec_unpacks_hi_v4sf             (rtx, rtx);
extern rtx        gen_vec_unpacks_lo_v4sf             (rtx, rtx);
extern rtx        gen_vec_unpacks_hi_v4si             (rtx, rtx);
extern rtx        gen_vec_unpacks_hi_v8hi             (rtx, rtx);
extern rtx        gen_vec_unpacks_hi_v16qi            (rtx, rtx);
extern rtx        gen_vec_unpacks_lo_v4si             (rtx, rtx);
extern rtx        gen_vec_unpacks_lo_v8hi             (rtx, rtx);
extern rtx        gen_vec_unpacks_lo_v16qi            (rtx, rtx);
extern rtx        gen_vec_unpacku_hi_v4si             (rtx, rtx);
extern rtx        gen_vec_unpacku_hi_v8hi             (rtx, rtx);
extern rtx        gen_vec_unpacku_hi_v16qi            (rtx, rtx);
extern rtx        gen_vec_unpacku_lo_v4si             (rtx, rtx);
extern rtx        gen_vec_unpacku_lo_v8hi             (rtx, rtx);
extern rtx        gen_vec_unpacku_lo_v16qi            (rtx, rtx);
extern rtx        gen_vec_extractv2didi               (rtx, rtx, rtx);
extern rtx        gen_vec_extractv4sisi               (rtx, rtx, rtx);
extern rtx        gen_vec_extractv8hihi               (rtx, rtx, rtx);
extern rtx        gen_vec_extractv16qiqi              (rtx, rtx, rtx);
extern rtx        gen_vec_extractv2dfdf               (rtx, rtx, rtx);
extern rtx        gen_vec_extractv4sfsf               (rtx, rtx, rtx);
extern rtx        gen_vec_setv2di                     (rtx, rtx, rtx);
extern rtx        gen_vec_setv4si                     (rtx, rtx, rtx);
extern rtx        gen_vec_setv8hi                     (rtx, rtx, rtx);
extern rtx        gen_vec_setv16qi                    (rtx, rtx, rtx);
extern rtx        gen_vec_setv2df                     (rtx, rtx, rtx);
extern rtx        gen_vec_setv4sf                     (rtx, rtx, rtx);
extern rtx        gen_vconduv2dfv2di                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4sfv2di                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv2div2di                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4siv2di                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8hiv2di                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv16qiv2di                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv2dfv4si                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4sfv4si                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv2div4si                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4siv4si                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8hiv4si                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv16qiv4si                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv2dfv8hi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4sfv8hi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv2div8hi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4siv8hi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8hiv8hi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv16qiv8hi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv2dfv16qi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4sfv16qi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv2div16qi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4siv16qi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8hiv16qi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv16qiv16qi                (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2dfv2df                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4sfv2df                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2div2df                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4siv2df                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8hiv2df                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv16qiv2df                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2dfv4sf                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4sfv4sf                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2div4sf                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4siv4sf                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8hiv4sf                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv16qiv4sf                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2dfv2di                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4sfv2di                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2div2di                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4siv2di                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8hiv2di                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv16qiv2di                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2dfv4si                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4sfv4si                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2div4si                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4siv4si                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8hiv4si                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv16qiv4si                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2dfv8hi                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4sfv8hi                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2div8hi                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4siv8hi                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8hiv8hi                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv16qiv8hi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2dfv16qi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4sfv16qi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv2div16qi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4siv16qi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8hiv16qi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv16qiv16qi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_absv2di2                        (rtx, rtx);
extern rtx        gen_absv4si2                        (rtx, rtx);
extern rtx        gen_absv8hi2                        (rtx, rtx);
extern rtx        gen_absv16qi2                       (rtx, rtx);
extern rtx        gen_negv2di2                        (rtx, rtx);
extern rtx        gen_negv4si2                        (rtx, rtx);
extern rtx        gen_negv8hi2                        (rtx, rtx);
extern rtx        gen_negv16qi2                       (rtx, rtx);
extern rtx        gen_negv2df2                        (rtx, rtx);
extern rtx        gen_negv4sf2                        (rtx, rtx);
extern rtx        gen_lsx_vrepliv2di                  (rtx, rtx);
extern rtx        gen_lsx_vrepliv4si                  (rtx, rtx);
extern rtx        gen_lsx_vrepliv8hi                  (rtx, rtx);
extern rtx        gen_lsx_vrepliv16qi                 (rtx, rtx);
extern rtx        gen_vec_permv2df                    (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv4sf                    (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv2di                    (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv4si                    (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv8hi                    (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv16qi                   (rtx, rtx, rtx, rtx);
extern rtx        gen_movv2df                         (rtx, rtx);
extern rtx        gen_movv4sf                         (rtx, rtx);
extern rtx        gen_movv2di                         (rtx, rtx);
extern rtx        gen_movv4si                         (rtx, rtx);
extern rtx        gen_movv8hi                         (rtx, rtx);
extern rtx        gen_movv16qi                        (rtx, rtx);
extern rtx        gen_movmisalignv2df                 (rtx, rtx);
extern rtx        gen_movmisalignv4sf                 (rtx, rtx);
extern rtx        gen_movmisalignv2di                 (rtx, rtx);
extern rtx        gen_movmisalignv4si                 (rtx, rtx);
extern rtx        gen_movmisalignv8hi                 (rtx, rtx);
extern rtx        gen_movmisalignv16qi                (rtx, rtx);
extern rtx        gen_lsx_ld_d_f                      (rtx, rtx, rtx);
extern rtx        gen_lsx_ld_w_f                      (rtx, rtx, rtx);
extern rtx        gen_lsx_ld_d                        (rtx, rtx, rtx);
extern rtx        gen_lsx_ld_w                        (rtx, rtx, rtx);
extern rtx        gen_lsx_ld_h                        (rtx, rtx, rtx);
extern rtx        gen_lsx_ld_b                        (rtx, rtx, rtx);
extern rtx        gen_lsx_st_d_f                      (rtx, rtx, rtx);
extern rtx        gen_lsx_st_w_f                      (rtx, rtx, rtx);
extern rtx        gen_lsx_st_d                        (rtx, rtx, rtx);
extern rtx        gen_lsx_st_w                        (rtx, rtx, rtx);
extern rtx        gen_lsx_st_h                        (rtx, rtx, rtx);
extern rtx        gen_lsx_st_b                        (rtx, rtx, rtx);
extern rtx        gen_rsqrtv2df2                      (rtx, rtx);
extern rtx        gen_rsqrtv4sf2                      (rtx, rtx);
extern rtx        gen_vec_concatv2di                  (rtx, rtx, rtx);
extern rtx        gen_copysignv2df3                   (rtx, rtx, rtx);
extern rtx        gen_copysignv4sf3                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vldrepl_d_f                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vldrepl_w_f                 (rtx, rtx, rtx);
extern rtx        gen_lsx_vldrepl_d                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vldrepl_w                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vldrepl_h                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vldrepl_b                   (rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_d_f                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_w_f                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_d                    (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_w                    (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_h                    (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vstelm_b                    (rtx, rtx, rtx, rtx);
extern rtx        gen_lsx_vld                         (rtx, rtx, rtx);
extern rtx        gen_lsx_vst                         (rtx, rtx, rtx);
extern rtx        gen_reduc_plus_scal_v2di            (rtx, rtx);
extern rtx        gen_reduc_plus_scal_v4si            (rtx, rtx);
extern rtx        gen_reduc_plus_scal_v2df            (rtx, rtx);
extern rtx        gen_reduc_plus_scal_v4sf            (rtx, rtx);
extern rtx        gen_reduc_and_scal_v2di             (rtx, rtx);
extern rtx        gen_reduc_ior_scal_v2di             (rtx, rtx);
extern rtx        gen_reduc_xor_scal_v2di             (rtx, rtx);
extern rtx        gen_reduc_and_scal_v4si             (rtx, rtx);
extern rtx        gen_reduc_ior_scal_v4si             (rtx, rtx);
extern rtx        gen_reduc_xor_scal_v4si             (rtx, rtx);
extern rtx        gen_reduc_and_scal_v8hi             (rtx, rtx);
extern rtx        gen_reduc_ior_scal_v8hi             (rtx, rtx);
extern rtx        gen_reduc_xor_scal_v8hi             (rtx, rtx);
extern rtx        gen_reduc_and_scal_v16qi            (rtx, rtx);
extern rtx        gen_reduc_ior_scal_v16qi            (rtx, rtx);
extern rtx        gen_reduc_xor_scal_v16qi            (rtx, rtx);
extern rtx        gen_reduc_smax_scal_v2df            (rtx, rtx);
extern rtx        gen_reduc_smax_scal_v4sf            (rtx, rtx);
extern rtx        gen_reduc_smax_scal_v2di            (rtx, rtx);
extern rtx        gen_reduc_smax_scal_v4si            (rtx, rtx);
extern rtx        gen_reduc_smax_scal_v8hi            (rtx, rtx);
extern rtx        gen_reduc_smax_scal_v16qi           (rtx, rtx);
extern rtx        gen_reduc_smin_scal_v2df            (rtx, rtx);
extern rtx        gen_reduc_smin_scal_v4sf            (rtx, rtx);
extern rtx        gen_reduc_smin_scal_v2di            (rtx, rtx);
extern rtx        gen_reduc_smin_scal_v4si            (rtx, rtx);
extern rtx        gen_reduc_smin_scal_v8hi            (rtx, rtx);
extern rtx        gen_reduc_smin_scal_v16qi           (rtx, rtx);
extern rtx        gen_reduc_umax_scal_v2di            (rtx, rtx);
extern rtx        gen_reduc_umax_scal_v4si            (rtx, rtx);
extern rtx        gen_reduc_umax_scal_v8hi            (rtx, rtx);
extern rtx        gen_reduc_umax_scal_v16qi           (rtx, rtx);
extern rtx        gen_reduc_umin_scal_v2di            (rtx, rtx);
extern rtx        gen_reduc_umin_scal_v4si            (rtx, rtx);
extern rtx        gen_reduc_umin_scal_v8hi            (rtx, rtx);
extern rtx        gen_reduc_umin_scal_v16qi           (rtx, rtx);
extern rtx        gen_vec_initv4dfdf                  (rtx, rtx);
extern rtx        gen_vec_initv8sfsf                  (rtx, rtx);
extern rtx        gen_vec_initv4didi                  (rtx, rtx);
extern rtx        gen_vec_initv8sisi                  (rtx, rtx);
extern rtx        gen_vec_initv16hihi                 (rtx, rtx);
extern rtx        gen_vec_initv32qiqi                 (rtx, rtx);
extern rtx        gen_vec_unpacks_hi_v8sf             (rtx, rtx);
extern rtx        gen_vec_unpacks_lo_v8sf             (rtx, rtx);
extern rtx        gen_vec_unpacks_hi_v8si             (rtx, rtx);
extern rtx        gen_vec_unpacks_hi_v16hi            (rtx, rtx);
extern rtx        gen_vec_unpacks_hi_v32qi            (rtx, rtx);
extern rtx        gen_vec_unpacks_lo_v8si             (rtx, rtx);
extern rtx        gen_vec_unpacks_lo_v16hi            (rtx, rtx);
extern rtx        gen_vec_unpacks_lo_v32qi            (rtx, rtx);
extern rtx        gen_vec_unpacku_hi_v8si             (rtx, rtx);
extern rtx        gen_vec_unpacku_hi_v16hi            (rtx, rtx);
extern rtx        gen_vec_unpacku_hi_v32qi            (rtx, rtx);
extern rtx        gen_vec_unpacku_lo_v8si             (rtx, rtx);
extern rtx        gen_vec_unpacku_lo_v16hi            (rtx, rtx);
extern rtx        gen_vec_unpacku_lo_v32qi            (rtx, rtx);
extern rtx        gen_vec_setv4di                     (rtx, rtx, rtx);
extern rtx        gen_vec_setv8si                     (rtx, rtx, rtx);
extern rtx        gen_vec_setv4df                     (rtx, rtx, rtx);
extern rtx        gen_vec_setv8sf                     (rtx, rtx, rtx);
extern rtx        gen_vec_extractv4dfdf               (rtx, rtx, rtx);
extern rtx        gen_vec_extractv8sfsf               (rtx, rtx, rtx);
extern rtx        gen_vec_extractv4didi               (rtx, rtx, rtx);
extern rtx        gen_vec_extractv8sisi               (rtx, rtx, rtx);
extern rtx        gen_vec_extractv16hihi              (rtx, rtx, rtx);
extern rtx        gen_vec_extractv32qiqi              (rtx, rtx, rtx);
extern rtx        gen_vec_permv4df                    (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv8sf                    (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv4di                    (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv8si                    (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv16hi                   (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_permv32qi                   (rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4dfv4di                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4dfv8si                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4dfv16hi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4dfv32qi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8sfv4di                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8sfv8si                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8sfv16hi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8sfv32qi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4div4di                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4div8si                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4div16hi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv4div32qi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8siv4di                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8siv8si                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8siv16hi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv8siv32qi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv16hiv4di                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv16hiv8si                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv16hiv16hi                (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv16hiv32qi                (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv32qiv4di                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv32qiv8si                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv32qiv16hi                (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vconduv32qiv32qi                (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4dfv4df                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8sfv4df                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4div4df                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8siv4df                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv16hiv4df                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv32qiv4df                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4dfv8sf                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8sfv8sf                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4div8sf                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8siv8sf                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv16hiv8sf                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv32qiv8sf                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4dfv4di                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8sfv4di                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4div4di                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8siv4di                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv16hiv4di                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv32qiv4di                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4dfv8si                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8sfv8si                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4div8si                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8siv8si                   (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv16hiv8si                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv32qiv8si                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4dfv16hi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8sfv16hi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4div16hi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8siv16hi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv16hiv16hi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv32qiv16hi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4dfv32qi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8sfv32qi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv4div32qi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv8siv32qi                  (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv16hiv32qi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcondv32qiv32qi                 (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv4dfv4df              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv8sfv4df              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv4div4df              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv8siv4df              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv16hiv4df             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv32qiv4df             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv4dfv8sf              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv8sfv8sf              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv4div8sf              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv8siv8sf              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv16hiv8sf             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv32qiv8sf             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv4dfv4di              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv8sfv4di              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv4div4di              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv8siv4di              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv16hiv4di             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv32qiv4di             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv4dfv8si              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv8sfv8si              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv4div8si              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv8siv8si              (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv16hiv8si             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv32qiv8si             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv4dfv16hi             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv8sfv16hi             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv4div16hi             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv8siv16hi             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv16hiv16hi            (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv32qiv16hi            (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv4dfv32qi             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv8sfv32qi             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv4div32qi             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv8siv32qi             (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv16hiv32qi            (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_vcond_maskv32qiv32qi            (rtx, rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvrepliv4di                (rtx, rtx);
extern rtx        gen_lasx_xvrepliv8si                (rtx, rtx);
extern rtx        gen_lasx_xvrepliv16hi               (rtx, rtx);
extern rtx        gen_lasx_xvrepliv32qi               (rtx, rtx);
extern rtx        gen_movv4df                         (rtx, rtx);
extern rtx        gen_movv8sf                         (rtx, rtx);
extern rtx        gen_movv4di                         (rtx, rtx);
extern rtx        gen_movv8si                         (rtx, rtx);
extern rtx        gen_movv16hi                        (rtx, rtx);
extern rtx        gen_movv32qi                        (rtx, rtx);
extern rtx        gen_movmisalignv4df                 (rtx, rtx);
extern rtx        gen_movmisalignv8sf                 (rtx, rtx);
extern rtx        gen_movmisalignv4di                 (rtx, rtx);
extern rtx        gen_movmisalignv8si                 (rtx, rtx);
extern rtx        gen_movmisalignv16hi                (rtx, rtx);
extern rtx        gen_movmisalignv32qi                (rtx, rtx);
extern rtx        gen_lasx_mxld_d_f                   (rtx, rtx, rtx);
extern rtx        gen_lasx_mxld_w_f                   (rtx, rtx, rtx);
extern rtx        gen_lasx_mxld_d                     (rtx, rtx, rtx);
extern rtx        gen_lasx_mxld_w                     (rtx, rtx, rtx);
extern rtx        gen_lasx_mxld_h                     (rtx, rtx, rtx);
extern rtx        gen_lasx_mxld_b                     (rtx, rtx, rtx);
extern rtx        gen_lasx_mxst_d_f                   (rtx, rtx, rtx);
extern rtx        gen_lasx_mxst_w_f                   (rtx, rtx, rtx);
extern rtx        gen_lasx_mxst_d                     (rtx, rtx, rtx);
extern rtx        gen_lasx_mxst_w                     (rtx, rtx, rtx);
extern rtx        gen_lasx_mxst_h                     (rtx, rtx, rtx);
extern rtx        gen_lasx_mxst_b                     (rtx, rtx, rtx);
extern rtx        gen_vec_cmpv4dfv4di                 (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_cmpv8sfv8si                 (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_cmpv4div4di                 (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_cmpv8siv8si                 (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_cmpv16hiv16hi               (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_cmpv32qiv32qi               (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_cmpuv4div4di                (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_cmpuv8siv8si                (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_cmpuv16hiv16hi              (rtx, rtx, rtx, rtx);
extern rtx        gen_vec_cmpuv32qiv32qi              (rtx, rtx, rtx, rtx);
extern rtx        gen_rsqrtv4df2                      (rtx, rtx);
extern rtx        gen_rsqrtv8sf2                      (rtx, rtx);
extern rtx        gen_copysignv4df3                   (rtx, rtx, rtx);
extern rtx        gen_copysignv8sf3                   (rtx, rtx, rtx);
extern rtx        gen_lasx_xvldrepl_d_f               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvldrepl_w_f               (rtx, rtx, rtx);
extern rtx        gen_lasx_xvldrepl_d                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvldrepl_w                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvldrepl_h                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvldrepl_b                 (rtx, rtx, rtx);
extern rtx        gen_lasx_xvld                       (rtx, rtx, rtx);
extern rtx        gen_lasx_xvst                       (rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_d_f                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_w_f                (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_d                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_w                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_h                  (rtx, rtx, rtx, rtx);
extern rtx        gen_lasx_xvstelm_b                  (rtx, rtx, rtx, rtx);
extern rtx        gen_reduc_plus_scal_v4di            (rtx, rtx);
extern rtx        gen_reduc_plus_scal_v8si            (rtx, rtx);
extern rtx        gen_reduc_plus_scal_v4df            (rtx, rtx);
extern rtx        gen_reduc_plus_scal_v8sf            (rtx, rtx);
extern rtx        gen_reduc_and_scal_v4di             (rtx, rtx);
extern rtx        gen_reduc_ior_scal_v4di             (rtx, rtx);
extern rtx        gen_reduc_xor_scal_v4di             (rtx, rtx);
extern rtx        gen_reduc_and_scal_v8si             (rtx, rtx);
extern rtx        gen_reduc_ior_scal_v8si             (rtx, rtx);
extern rtx        gen_reduc_xor_scal_v8si             (rtx, rtx);
extern rtx        gen_reduc_and_scal_v16hi            (rtx, rtx);
extern rtx        gen_reduc_ior_scal_v16hi            (rtx, rtx);
extern rtx        gen_reduc_xor_scal_v16hi            (rtx, rtx);
extern rtx        gen_reduc_and_scal_v32qi            (rtx, rtx);
extern rtx        gen_reduc_ior_scal_v32qi            (rtx, rtx);
extern rtx        gen_reduc_xor_scal_v32qi            (rtx, rtx);
extern rtx        gen_reduc_smax_scal_v4df            (rtx, rtx);
extern rtx        gen_reduc_smax_scal_v8sf            (rtx, rtx);
extern rtx        gen_reduc_smax_scal_v4di            (rtx, rtx);
extern rtx        gen_reduc_smax_scal_v8si            (rtx, rtx);
extern rtx        gen_reduc_smax_scal_v16hi           (rtx, rtx);
extern rtx        gen_reduc_smax_scal_v32qi           (rtx, rtx);
extern rtx        gen_reduc_smin_scal_v4df            (rtx, rtx);
extern rtx        gen_reduc_smin_scal_v8sf            (rtx, rtx);
extern rtx        gen_reduc_smin_scal_v4di            (rtx, rtx);
extern rtx        gen_reduc_smin_scal_v8si            (rtx, rtx);
extern rtx        gen_reduc_smin_scal_v16hi           (rtx, rtx);
extern rtx        gen_reduc_smin_scal_v32qi           (rtx, rtx);
extern rtx        gen_reduc_umax_scal_v4di            (rtx, rtx);
extern rtx        gen_reduc_umax_scal_v8si            (rtx, rtx);
extern rtx        gen_reduc_umax_scal_v16hi           (rtx, rtx);
extern rtx        gen_reduc_umax_scal_v32qi           (rtx, rtx);
extern rtx        gen_reduc_umin_scal_v4di            (rtx, rtx);
extern rtx        gen_reduc_umin_scal_v8si            (rtx, rtx);
extern rtx        gen_reduc_umin_scal_v16hi           (rtx, rtx);
extern rtx        gen_reduc_umin_scal_v32qi           (rtx, rtx);

#endif /* GCC_INSN_FLAGS_H */
