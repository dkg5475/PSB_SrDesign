/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: isequal.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 04-Feb-2025 19:00:21
 */

/* Include Files */
#include "isequal.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const char varargin_1_data[]
 *                const int varargin_1_size[2]
 *                const unsigned char varargin_2[6]
 * Return Type  : boolean_T
 */
boolean_T b_isequal(const char varargin_1_data[], const int varargin_1_size[2],
                    const unsigned char varargin_2[6])
{
  boolean_T p;
  p = (varargin_1_size[1] == 6);
  if (p && (varargin_1_size[1] != 0)) {
    int k;
    boolean_T exitg1;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 6)) {
      if ((unsigned char)varargin_1_data[k] != varargin_2[k]) {
        p = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  return p;
}

/*
 * Arguments    : const char varargin_1_data[]
 *                const int varargin_1_size[2]
 *                const unsigned char varargin_2[7]
 * Return Type  : boolean_T
 */
boolean_T c_isequal(const char varargin_1_data[], const int varargin_1_size[2],
                    const unsigned char varargin_2[7])
{
  boolean_T p;
  p = (varargin_1_size[1] == 7);
  if (p && (varargin_1_size[1] != 0)) {
    int k;
    boolean_T exitg1;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 7)) {
      if ((unsigned char)varargin_1_data[k] != varargin_2[k]) {
        p = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  return p;
}

/*
 * Arguments    : const char varargin_1_data[]
 *                const int varargin_1_size[2]
 *                const unsigned char varargin_2[3]
 * Return Type  : boolean_T
 */
boolean_T d_isequal(const char varargin_1_data[], const int varargin_1_size[2],
                    const unsigned char varargin_2[3])
{
  boolean_T p;
  p = (varargin_1_size[1] == 3);
  if (p && (varargin_1_size[1] != 0)) {
    int k;
    boolean_T exitg1;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 3)) {
      if ((unsigned char)varargin_1_data[k] != varargin_2[k]) {
        p = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  return p;
}

/*
 * Arguments    : const char varargin_1_data[]
 *                const int varargin_1_size[2]
 *                const unsigned char varargin_2[8]
 * Return Type  : boolean_T
 */
boolean_T e_isequal(const char varargin_1_data[], const int varargin_1_size[2],
                    const unsigned char varargin_2[8])
{
  boolean_T p;
  p = (varargin_1_size[1] == 8);
  if (p && (varargin_1_size[1] != 0)) {
    int k;
    boolean_T exitg1;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 8)) {
      if ((unsigned char)varargin_1_data[k] != varargin_2[k]) {
        p = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  return p;
}

/*
 * Arguments    : const char varargin_1_data[]
 *                const int varargin_1_size[2]
 *                const unsigned char varargin_2[5]
 * Return Type  : boolean_T
 */
boolean_T isequal(const char varargin_1_data[], const int varargin_1_size[2],
                  const unsigned char varargin_2[5])
{
  boolean_T p;
  p = (varargin_1_size[1] == 5);
  if (p && (varargin_1_size[1] != 0)) {
    int k;
    boolean_T exitg1;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 5)) {
      if ((unsigned char)varargin_1_data[k] != varargin_2[k]) {
        p = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  return p;
}

/*
 * File trailer for isequal.c
 *
 * [EOF]
 */
