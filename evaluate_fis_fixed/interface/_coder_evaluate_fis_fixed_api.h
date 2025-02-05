/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_evaluate_fis_fixed_api.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 04-Feb-2025 19:00:21
 */

#ifndef _CODER_EVALUATE_FIS_FIXED_API_H
#define _CODER_EVALUATE_FIS_FIXED_API_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
real_T evaluate_fis_fixed(real_T TempDeviation, real_T TempSlope);

void evaluate_fis_fixed_api(const mxArray *const prhs[2], const mxArray **plhs);

void evaluate_fis_fixed_atexit(void);

void evaluate_fis_fixed_initialize(void);

void evaluate_fis_fixed_terminate(void);

void evaluate_fis_fixed_xil_shutdown(void);

void evaluate_fis_fixed_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_evaluate_fis_fixed_api.h
 *
 * [EOF]
 */
