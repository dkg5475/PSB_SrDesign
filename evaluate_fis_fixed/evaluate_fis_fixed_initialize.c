/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: evaluate_fis_fixed_initialize.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 04-Feb-2025 19:00:21
 */

/* Include Files */
#include "evaluate_fis_fixed_initialize.h"
#include "evaluate_fis_fixed.h"
#include "evaluate_fis_fixed_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void evaluate_fis_fixed_initialize(void)
{
  evaluate_fis_fixed_init();
  isInitialized_evaluate_fis_fixed = true;
}

/*
 * File trailer for evaluate_fis_fixed_initialize.c
 *
 * [EOF]
 */
