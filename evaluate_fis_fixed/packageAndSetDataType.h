/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: packageAndSetDataType.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 04-Feb-2025 19:00:21
 */

#ifndef PACKAGEANDSETDATATYPE_H
#define PACKAGEANDSETDATATYPE_H

/* Include Files */
#include "evaluate_fis_fixed_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void packageAndSetDataType(const char fis_andMethod[4],
                           const char fis_defuzzMethod[6],
                           const f_struct_T fis_input[2],
                           const double fis_output_range[2],
                           const g_struct_T fis_output_mf[5],
                           const h_struct_T fis_rule[7], m_struct_T *fis);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for packageAndSetDataType.h
 *
 * [EOF]
 */
