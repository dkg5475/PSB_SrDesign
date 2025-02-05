/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fuzzifyInputs.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 04-Feb-2025 19:00:21
 */

#ifndef FUZZIFYINPUTS_H
#define FUZZIFYINPUTS_H

/* Include Files */
#include "evaluate_fis_fixed_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void fuzzifyInputs(const double inputs[2], const double fis_antecedent[14],
                   const int fis_numCumInputMFs[2],
                   const cell_wrap_0 varargin_1[2], double varargin_2_data[],
                   double fuzzifiedInputs[14]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for fuzzifyInputs.h
 *
 * [EOF]
 */
