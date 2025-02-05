/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: evaluate_fis_fixed_internal_types.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 04-Feb-2025 19:00:21
 */

#ifndef EVALUATE_FIS_FIXED_INTERNAL_TYPES_H
#define EVALUATE_FIS_FIXED_INTERNAL_TYPES_H

/* Include Files */
#include "evaluate_fis_fixed_types.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_char_T_1x8
#define struct_emxArray_char_T_1x8
struct emxArray_char_T_1x8 {
  char data[8];
  int size[2];
};
#endif /* struct_emxArray_char_T_1x8 */
#ifndef typedef_emxArray_char_T_1x8
#define typedef_emxArray_char_T_1x8
typedef struct emxArray_char_T_1x8 emxArray_char_T_1x8;
#endif /* typedef_emxArray_char_T_1x8 */

#ifndef struct_emxArray_real_T_1x4
#define struct_emxArray_real_T_1x4
struct emxArray_real_T_1x4 {
  double data[4];
  int size[2];
};
#endif /* struct_emxArray_real_T_1x4 */
#ifndef typedef_emxArray_real_T_1x4
#define typedef_emxArray_real_T_1x4
typedef struct emxArray_real_T_1x4 emxArray_real_T_1x4;
#endif /* typedef_emxArray_real_T_1x4 */

#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct {
  emxArray_char_T_1x8 type;
  emxArray_real_T_1x4 params;
} struct_T;
#endif /* typedef_struct_T */

#ifndef typedef_b_struct_T
#define typedef_b_struct_T
typedef struct {
  emxArray_char_T_1x8 type;
  int origTypeLength;
  emxArray_real_T_1x4 params;
  int origParamLength;
} b_struct_T;
#endif /* typedef_b_struct_T */

#ifndef typedef_e_struct_T
#define typedef_e_struct_T
typedef struct {
  char type[8];
  double params[4];
} e_struct_T;
#endif /* typedef_e_struct_T */

#ifndef typedef_f_struct_T
#define typedef_f_struct_T
typedef struct {
  double range[2];
  e_struct_T mf[3];
} f_struct_T;
#endif /* typedef_f_struct_T */

#ifndef typedef_g_struct_T
#define typedef_g_struct_T
typedef struct {
  char type[8];
  double params;
} g_struct_T;
#endif /* typedef_g_struct_T */

#ifndef typedef_h_struct_T
#define typedef_h_struct_T
typedef struct {
  double antecedent[2];
  double consequent;
} h_struct_T;
#endif /* typedef_h_struct_T */

#ifndef typedef_b_emxArray_struct_T_1x5
#define typedef_b_emxArray_struct_T_1x5
typedef struct {
  b_struct_T data[5];
} b_emxArray_struct_T_1x5;
#endif /* typedef_b_emxArray_struct_T_1x5 */

#ifndef typedef_l_struct_T
#define typedef_l_struct_T
typedef struct {
  b_emxArray_struct_T_1x5 mf;
  int origNumMF;
} l_struct_T;
#endif /* typedef_l_struct_T */

#ifndef typedef_m_struct_T
#define typedef_m_struct_T
typedef struct {
  unsigned char andMethod[4];
  unsigned char defuzzMethod[6];
  double outputRange[2];
  l_struct_T inputMF[2];
  l_struct_T outputMF;
  double antecedent[14];
  double consequent[7];
  int numCumInputMFs[2];
} m_struct_T;
#endif /* typedef_m_struct_T */

#ifndef typedef_c_emxArray_struct_T_1x5
#define typedef_c_emxArray_struct_T_1x5
typedef struct {
  struct_T data[5];
} c_emxArray_struct_T_1x5;
#endif /* typedef_c_emxArray_struct_T_1x5 */

#ifndef typedef_cell_wrap_0
#define typedef_cell_wrap_0
typedef struct {
  c_emxArray_struct_T_1x5 f1;
} cell_wrap_0;
#endif /* typedef_cell_wrap_0 */

#endif
/*
 * File trailer for evaluate_fis_fixed_internal_types.h
 *
 * [EOF]
 */
