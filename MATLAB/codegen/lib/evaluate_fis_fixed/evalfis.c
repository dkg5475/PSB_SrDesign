/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: evalfis.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 04-Feb-2025 19:00:21
 */

/* Include Files */
#include "evalfis.h"
#include "evaluate_fis_fixed_internal_types.h"
#include "evaluate_fis_fixed_rtwutil.h"
#include "fuzzifyInputs.h"
#include "isequal.h"
#include "packageAndSetDataType.h"
#include "rt_nonfinite.h"

/* Type Definitions */
#ifndef typedef_emxArray_struct_T_1x3
#define typedef_emxArray_struct_T_1x3
typedef struct {
  struct_T data[3];
} emxArray_struct_T_1x3;
#endif /* typedef_emxArray_struct_T_1x3 */

/* Function Definitions */
/*
 * Arguments    : const char arg1_andMethod[4]
 *                const char arg1_defuzzMethod[6]
 *                const f_struct_T arg1_input[2]
 *                const double arg1_output_range[2]
 *                const g_struct_T arg1_output_mf[5]
 *                const h_struct_T arg1_rule[7]
 *                const double arg2[2]
 * Return Type  : double
 */
double evalfis(const char arg1_andMethod[4], const char arg1_defuzzMethod[6],
               const f_struct_T arg1_input[2],
               const double arg1_output_range[2],
               const g_struct_T arg1_output_mf[5],
               const h_struct_T arg1_rule[7], const double arg2[2])
{
  static const unsigned char uv2[8] = {99U,  111U, 110U, 115U,
                                       116U, 97U,  110U, 116U};
  static const unsigned char uv[6] = {119U, 116U, 97U, 118U, 101U, 114U};
  static const unsigned char uv1[4] = {112U, 114U, 111U, 100U};
  m_struct_T expl_temp;
  struct_T b_expl_temp;
  struct_T c_expl_temp;
  struct_T d_expl_temp;
  double varargout_1;
  double y;
  int i;
  int j;
  int k;
  int ruleID;
  boolean_T exitg1;
  boolean_T p;
  packageAndSetDataType(arg1_andMethod, arg1_defuzzMethod, arg1_input,
                        arg1_output_range, arg1_output_mf, arg1_rule,
                        &expl_temp);
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 6)) {
    if (expl_temp.defuzzMethod[k] != uv[k]) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (p) {
    c_emxArray_struct_T_1x5 b_mf;
    cell_wrap_0 inVarMF[2];
    emxArray_struct_T_1x3 mf;
    double irr[14];
    double consequentOutputs_tmp[7];
    double w[7];
    double tmp_data[6];
    double outputMFCache_data[5];
    int loop_ub;
    int loop_ub_tmp;
    loop_ub_tmp = expl_temp.inputMF[0].origNumMF;
    i = (unsigned char)expl_temp.inputMF[0].origNumMF;
    if (i - 1 >= 0) {
      b_expl_temp.type.size[0] = 1;
      b_expl_temp.params.size[0] = 1;
    }
    for (j = 0; j < i; j++) {
      k = expl_temp.inputMF[0].mf.data[j].origTypeLength;
      if (k < 1) {
        loop_ub = 0;
      } else {
        loop_ub = k;
      }
      k = expl_temp.inputMF[0].mf.data[j].origParamLength;
      if (k < 1) {
        k = 0;
      }
      b_expl_temp.type.size[1] = loop_ub;
      for (ruleID = 0; ruleID < loop_ub; ruleID++) {
        b_expl_temp.type.data[ruleID] =
            expl_temp.inputMF[0].mf.data[j].type.data[ruleID];
      }
      b_expl_temp.params.size[1] = k;
      for (ruleID = 0; ruleID < k; ruleID++) {
        b_expl_temp.params.data[ruleID] =
            expl_temp.inputMF[0].mf.data[j].params.data[ruleID];
      }
      mf.data[j] = b_expl_temp;
    }
    for (i = 0; i < loop_ub_tmp; i++) {
      inVarMF[0].f1.data[i] = mf.data[i];
    }
    loop_ub_tmp = expl_temp.inputMF[1].origNumMF;
    i = (unsigned char)expl_temp.inputMF[1].origNumMF;
    if (i - 1 >= 0) {
      c_expl_temp.type.size[0] = 1;
      c_expl_temp.params.size[0] = 1;
    }
    for (j = 0; j < i; j++) {
      k = expl_temp.inputMF[1].mf.data[j].origTypeLength;
      if (k < 1) {
        loop_ub = 0;
      } else {
        loop_ub = k;
      }
      k = expl_temp.inputMF[1].mf.data[j].origParamLength;
      if (k < 1) {
        k = 0;
      }
      c_expl_temp.type.size[1] = loop_ub;
      for (ruleID = 0; ruleID < loop_ub; ruleID++) {
        c_expl_temp.type.data[ruleID] =
            expl_temp.inputMF[1].mf.data[j].type.data[ruleID];
      }
      c_expl_temp.params.size[1] = k;
      for (ruleID = 0; ruleID < k; ruleID++) {
        c_expl_temp.params.data[ruleID] =
            expl_temp.inputMF[1].mf.data[j].params.data[ruleID];
      }
      mf.data[j] = c_expl_temp;
    }
    for (i = 0; i < loop_ub_tmp; i++) {
      inVarMF[1].f1.data[i] = mf.data[i];
    }
    for (i = 0; i < 6; i++) {
      tmp_data[i] = 0.0;
    }
    fuzzifyInputs(arg2, expl_temp.antecedent, expl_temp.numCumInputMFs, inVarMF,
                  tmp_data, irr);
    varargout_1 = 0.0;
    for (ruleID = 0; ruleID < 7; ruleID++) {
      w[ruleID] = -1.0;
      p = true;
      k = 0;
      exitg1 = false;
      while ((!exitg1) && (k < 4)) {
        if (expl_temp.andMethod[k] != uv1[k]) {
          p = false;
          exitg1 = true;
        } else {
          k++;
        }
      }
      if (p) {
        w[ruleID] = irr[ruleID] * irr[ruleID + 7];
      } else {
        exit(0);
      }
      varargout_1 += w[ruleID];
    }
    d_expl_temp.type.size[0] = 1;
    d_expl_temp.params.size[0] = 1;
    for (j = 0; j < 5; j++) {
      loop_ub_tmp = expl_temp.outputMF.mf.data[j].origTypeLength;
      if (loop_ub_tmp < 1) {
        loop_ub = 0;
      } else {
        loop_ub = loop_ub_tmp;
      }
      k = (expl_temp.outputMF.mf.data[j].origParamLength >= 1);
      d_expl_temp.type.size[1] = loop_ub;
      for (i = 0; i < loop_ub; i++) {
        d_expl_temp.type.data[i] = expl_temp.outputMF.mf.data[j].type.data[i];
      }
      d_expl_temp.params.size[1] = k;
      if (k - 1 >= 0) {
        d_expl_temp.params.data[0] =
            expl_temp.outputMF.mf.data[j].params.data[0];
      }
      b_mf.data[j] = d_expl_temp;
      if (e_isequal(b_mf.data[j].type.data, b_mf.data[j].type.size, uv2)) {
        y = b_mf.data[j].params.data[0];
      } else {
        /* A check that is always false is detected at compile-time. Eliminating
         * code that follows. */
      }
      outputMFCache_data[j] = y;
    }
    for (ruleID = 0; ruleID < 7; ruleID++) {
      y = rt_roundd_snf(expl_temp.consequent[ruleID]);
      if (y < 2.147483648E+9) {
        if (y >= -2.147483648E+9) {
          i = (int)y;
        } else {
          i = MIN_int32_T;
        }
      } else if (y >= 2.147483648E+9) {
        i = MAX_int32_T;
      } else {
        i = 0;
      }
      consequentOutputs_tmp[ruleID] = outputMFCache_data[i - 1] * w[ruleID];
    }
    y = consequentOutputs_tmp[0];
    for (k = 0; k < 6; k++) {
      y += consequentOutputs_tmp[k + 1];
    }
    if (varargout_1 == 0.0) {
      varargout_1 = (expl_temp.outputRange[0] + expl_temp.outputRange[1]) / 2.0;
    } else {
      varargout_1 = y * (1.0 / varargout_1);
    }
  } else {
    varargout_1 = 0.0;
    exit(0);
  }
  return varargout_1;
}

/*
 * File trailer for evalfis.c
 *
 * [EOF]
 */
