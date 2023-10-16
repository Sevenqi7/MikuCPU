/* Generated automatically by the program 'build/genpreds'
   from the machine description file '/dev/shm/build_loongarch32r-linux-gnusf_x86_64_v2.0_20230903/src/target_gcc/gcc/config/loongarch/loongarch.md'.  */

#ifndef GCC_TM_PREDS_H
#define GCC_TM_PREDS_H

#ifdef HAVE_MACHINE_MODES
extern int general_operand (rtx, machine_mode);
extern int address_operand (rtx, machine_mode);
extern int register_operand (rtx, machine_mode);
extern int pmode_register_operand (rtx, machine_mode);
extern int scratch_operand (rtx, machine_mode);
extern int immediate_operand (rtx, machine_mode);
extern int const_int_operand (rtx, machine_mode);
extern int const_double_operand (rtx, machine_mode);
extern int nonimmediate_operand (rtx, machine_mode);
extern int nonmemory_operand (rtx, machine_mode);
extern int push_operand (rtx, machine_mode);
extern int pop_operand (rtx, machine_mode);
extern int memory_operand (rtx, machine_mode);
extern int indirect_operand (rtx, machine_mode);
extern int ordered_comparison_operator (rtx, machine_mode);
extern int comparison_operator (rtx, machine_mode);
extern int const_uns_arith_operand (rtx, machine_mode);
extern int uns_arith_operand (rtx, machine_mode);
extern int const_lu32i_operand (rtx, machine_mode);
extern int const_lu52i_operand (rtx, machine_mode);
extern int const_arith_operand (rtx, machine_mode);
extern int const_imm16_operand (rtx, machine_mode);
extern int arith_operand (rtx, machine_mode);
extern int const_immalsl_operand (rtx, machine_mode);
extern int const_lsx_branch_operand (rtx, machine_mode);
extern int const_uimm3_operand (rtx, machine_mode);
extern int const_uimm4_operand (rtx, machine_mode);
extern int const_uimm5_operand (rtx, machine_mode);
extern int const_uimm6_operand (rtx, machine_mode);
extern int const_uimm8_operand (rtx, machine_mode);
extern int const_uimm14_operand (rtx, machine_mode);
extern int const_uimm15_operand (rtx, machine_mode);
extern int const_imm10_operand (rtx, machine_mode);
extern int const_imm12_operand (rtx, machine_mode);
extern int const_imm13_operand (rtx, machine_mode);
extern int aq8b_operand (rtx, machine_mode);
extern int aq8h_operand (rtx, machine_mode);
extern int aq8w_operand (rtx, machine_mode);
extern int aq8d_operand (rtx, machine_mode);
extern int aq10b_operand (rtx, machine_mode);
extern int aq10h_operand (rtx, machine_mode);
extern int aq10w_operand (rtx, machine_mode);
extern int aq10d_operand (rtx, machine_mode);
extern int aq12b_operand (rtx, machine_mode);
extern int aq12h_operand (rtx, machine_mode);
extern int aq12w_operand (rtx, machine_mode);
extern int aq12d_operand (rtx, machine_mode);
extern int sle_operand (rtx, machine_mode);
extern int sleu_operand (rtx, machine_mode);
extern int const_0_operand (rtx, machine_mode);
extern int const_m1_operand (rtx, machine_mode);
extern int reg_or_m1_operand (rtx, machine_mode);
extern int reg_or_0_operand (rtx, machine_mode);
extern int const_1_operand (rtx, machine_mode);
extern int reg_or_1_operand (rtx, machine_mode);
extern int const_exp_2_operand (rtx, machine_mode);
extern int const_exp_4_operand (rtx, machine_mode);
extern int const_exp_8_operand (rtx, machine_mode);
extern int const_exp_16_operand (rtx, machine_mode);
extern int const_exp_32_operand (rtx, machine_mode);
extern int const_0_or_1_operand (rtx, machine_mode);
extern int const_2_or_3_operand (rtx, machine_mode);
extern int const_0_to_3_operand (rtx, machine_mode);
extern int const_0_to_7_operand (rtx, machine_mode);
extern int const_4_to_7_operand (rtx, machine_mode);
extern int const_8_to_15_operand (rtx, machine_mode);
extern int const_8_to_11_operand (rtx, machine_mode);
extern int const_12_to_15_operand (rtx, machine_mode);
extern int const_16_to_31_operand (rtx, machine_mode);
extern int lu52i_mask_operand (rtx, machine_mode);
extern int low_bitmask_operand (rtx, machine_mode);
extern int const_call_insn_operand (rtx, machine_mode);
extern int call_insn_operand (rtx, machine_mode);
extern int is_const_call_local_symbol (rtx, machine_mode);
extern int is_const_call_weak_symbol (rtx, machine_mode);
extern int is_const_call_plt_symbol (rtx, machine_mode);
extern int is_const_call_global_noplt_symbol (rtx, machine_mode);
extern int splittable_const_int_operand (rtx, machine_mode);
extern int move_operand (rtx, machine_mode);
extern int symbolic_operand (rtx, machine_mode);
extern int equality_operator (rtx, machine_mode);
extern int order_operator (rtx, machine_mode);
extern int loongarch_cstore_operator (rtx, machine_mode);
extern int small_data_pattern (rtx, machine_mode);
extern int non_volatile_mem_operand (rtx, machine_mode);
extern int const_vector_same_val_operand (rtx, machine_mode);
extern int const_vector_same_simm5_operand (rtx, machine_mode);
extern int const_vector_same_uimm5_operand (rtx, machine_mode);
extern int const_vector_same_ximm5_operand (rtx, machine_mode);
extern int const_vector_same_uimm6_operand (rtx, machine_mode);
extern int par_const_vector_shf_set_operand (rtx, machine_mode);
extern int reg_or_vector_same_val_operand (rtx, machine_mode);
extern int reg_or_vector_same_simm5_operand (rtx, machine_mode);
extern int reg_or_vector_same_uimm5_operand (rtx, machine_mode);
extern int reg_or_vector_same_ximm5_operand (rtx, machine_mode);
extern int reg_or_vector_same_uimm6_operand (rtx, machine_mode);
#endif /* HAVE_MACHINE_MODES */

#define CONSTRAINT_NUM_DEFINED_P 1
enum constraint_num
{
  CONSTRAINT__UNKNOWN = 0,
  CONSTRAINT_r,
  CONSTRAINT_e,
  CONSTRAINT_f,
  CONSTRAINT_j,
  CONSTRAINT_q,
  CONSTRAINT_z,
  CONSTRAINT_I,
  CONSTRAINT_J,
  CONSTRAINT_K,
  CONSTRAINT_w,
  CONSTRAINT_o,
  CONSTRAINT_k,
  CONSTRAINT_m,
  CONSTRAINT_ZC,
  CONSTRAINT_ZB,
  CONSTRAINT_R,
  CONSTRAINT_p,
  CONSTRAINT_a,
  CONSTRAINT_c,
  CONSTRAINT_h,
  CONSTRAINT_l,
  CONSTRAINT_t,
  CONSTRAINT_u,
  CONSTRAINT_v,
  CONSTRAINT_G,
  CONSTRAINT_Q,
  CONSTRAINT_Yx,
  CONSTRAINT_YG,
  CONSTRAINT_YI,
  CONSTRAINT_YC,
  CONSTRAINT_YZ,
  CONSTRAINT_Unv5,
  CONSTRAINT_Uuv5,
  CONSTRAINT_Usv5,
  CONSTRAINT_Uuv6,
  CONSTRAINT_Urv8,
  CONSTRAINT_V,
  CONSTRAINT__l,
  CONSTRAINT__g,
  CONSTRAINT_i,
  CONSTRAINT_s,
  CONSTRAINT_n,
  CONSTRAINT_E,
  CONSTRAINT_F,
  CONSTRAINT_X,
  CONSTRAINT_Yd,
  CONSTRAINT__LIMIT
};

extern enum constraint_num lookup_constraint_1 (const char *);
extern const unsigned char lookup_constraint_array[];

/* Return the constraint at the beginning of P, or CONSTRAINT__UNKNOWN if it
   isn't recognized.  */

static inline enum constraint_num
lookup_constraint (const char *p)
{
  unsigned int index = lookup_constraint_array[(unsigned char) *p];
  return (index == UCHAR_MAX
          ? lookup_constraint_1 (p)
          : (enum constraint_num) index);
}

extern bool (*constraint_satisfied_p_array[]) (rtx);

/* Return true if X satisfies constraint C.  */

static inline bool
constraint_satisfied_p (rtx x, enum constraint_num c)
{
  int i = (int) c - (int) CONSTRAINT_I;
  return i >= 0 && constraint_satisfied_p_array[i] (x);
}

static inline bool
insn_extra_register_constraint (enum constraint_num c)
{
  return c >= CONSTRAINT_r && c <= CONSTRAINT_z;
}

static inline bool
insn_extra_memory_constraint (enum constraint_num c)
{
  return c >= CONSTRAINT_w && c <= CONSTRAINT_R;
}

static inline bool
insn_extra_special_memory_constraint (enum constraint_num)
{
  return false;
}

static inline bool
insn_extra_address_constraint (enum constraint_num c)
{
  return c >= CONSTRAINT_p && c <= CONSTRAINT_p;
}

static inline void
insn_extra_constraint_allows_reg_mem (enum constraint_num c,
				      bool *allows_reg, bool *allows_mem)
{
  if (c >= CONSTRAINT_a && c <= CONSTRAINT_Urv8)
    return;
  if (c >= CONSTRAINT_V && c <= CONSTRAINT__g)
    {
      *allows_mem = true;
      return;
    }
  (void) c;
  *allows_reg = true;
  *allows_mem = true;
}

static inline size_t
insn_constraint_len (char fc, const char *str ATTRIBUTE_UNUSED)
{
  switch (fc)
    {
    case 'U': return 4;
    case 'Y': return 2;
    case 'Z': return 2;
    default: break;
    }
  return 1;
}

#define CONSTRAINT_LEN(c_,s_) insn_constraint_len (c_,s_)

extern enum reg_class reg_class_for_constraint_1 (enum constraint_num);

static inline enum reg_class
reg_class_for_constraint (enum constraint_num c)
{
  if (insn_extra_register_constraint (c))
    return reg_class_for_constraint_1 (c);
  return NO_REGS;
}

extern bool insn_const_int_ok_for_constraint (HOST_WIDE_INT, enum constraint_num);
#define CONST_OK_FOR_CONSTRAINT_P(v_,c_,s_) \
    insn_const_int_ok_for_constraint (v_, lookup_constraint (s_))

enum constraint_type
{
  CT_REGISTER,
  CT_CONST_INT,
  CT_MEMORY,
  CT_SPECIAL_MEMORY,
  CT_ADDRESS,
  CT_FIXED_FORM
};

static inline enum constraint_type
get_constraint_type (enum constraint_num c)
{
  if (c >= CONSTRAINT_p)
    {
      if (c >= CONSTRAINT_a)
        return CT_FIXED_FORM;
      return CT_ADDRESS;
    }
  if (c >= CONSTRAINT_w)
    return CT_MEMORY;
  if (c >= CONSTRAINT_I)
    return CT_CONST_INT;
  return CT_REGISTER;
}
#endif /* tm-preds.h */
