/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: evalfis.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 04-Feb-2025 19:00:21
 */

#ifndef EVALFIS_H
#define EVALFIS_H

/* Include Files */
#include "evaluate_fis_fixed_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double evalfis(const char arg1_andMethod[4], const char arg1_defuzzMethod[6],
               const f_struct_T arg1_input[2],
               const double arg1_output_range[2],
               const g_struct_T arg1_output_mf[5],
               const h_struct_T arg1_rule[7], const double arg2[2]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for evalfis.h
 *
 * [EOF]
 */
