/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fuzzifyInputs.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 04-Feb-2025 19:00:21
 */

/* Include Files */
#include "fuzzifyInputs.h"
#include "evaluate_fis_fixed_internal_types.h"
#include "evaluate_fis_fixed_rtwutil.h"
#include "isequal.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const double inputs[2]
 *                const double fis_antecedent[14]
 *                const int fis_numCumInputMFs[2]
 *                const cell_wrap_0 varargin_1[2]
 *                double varargin_2_data[]
 *                double fuzzifiedInputs[14]
 * Return Type  : void
 */
void fuzzifyInputs(const double inputs[2], const double fis_antecedent[14],
                   const int fis_numCumInputMFs[2],
                   const cell_wrap_0 varargin_1[2], double varargin_2_data[],
                   double fuzzifiedInputs[14])
{
  static const unsigned char uv9[8] = {103U, 97U, 117U, 115U,
                                       115U, 50U, 109U, 102U};
  static const unsigned char uv2[7] = {103U, 97U, 117U, 115U, 115U, 109U, 102U};
  static const unsigned char uv3[7] = {103U, 98U, 101U, 108U, 108U, 109U, 102U};
  static const unsigned char uv1[6] = {116U, 114U, 97U, 112U, 109U, 102U};
  static const unsigned char uv10[6] = {100U, 115U, 105U, 103U, 109U, 102U};
  static const unsigned char uv11[6] = {112U, 115U, 105U, 103U, 109U, 102U};
  static const unsigned char uv7[6] = {108U, 105U, 110U, 115U, 109U, 102U};
  static const unsigned char uv8[6] = {108U, 105U, 110U, 122U, 109U, 102U};
  static const unsigned char uv[5] = {116U, 114U, 105U, 109U, 102U};
  static const unsigned char uv4[5] = {115U, 105U, 103U, 109U, 102U};
  static const unsigned char uv12[4] = {112U, 105U, 109U, 102U};
  static const unsigned char uv5[3] = {115U, 109U, 102U};
  static const unsigned char uv6[3] = {122U, 109U, 102U};
  double d;
  int inputID;
  int mfID;
  int q0;
  int qY;
  for (inputID = 0; inputID < 2; inputID++) {
    q0 = fis_numCumInputMFs[inputID];
    for (mfID = 0; mfID < 3; mfID++) {
      boolean_T b;
      b = ((q0 < 0) && (mfID + 1 < MIN_int32_T - q0));
      if (b) {
        qY = MIN_int32_T;
      } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
        qY = MAX_int32_T;
      } else {
        qY = (q0 + mfID) + 1;
      }
      varargin_2_data[qY - 1] = -1.0;
      if (isequal(varargin_1[inputID].f1.data[mfID].type.data,
                  varargin_1[inputID].f1.data[mfID].type.size, uv)) {
        double d1;
        double d2;
        if (b) {
          qY = MIN_int32_T;
        } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
          qY = MAX_int32_T;
        } else {
          qY = (q0 + mfID) + 1;
        }
        varargin_2_data[qY - 1] = 0.0;
        d = varargin_1[inputID].f1.data[mfID].params.data[0];
        d1 = varargin_1[inputID].f1.data[mfID].params.data[1];
        if (d != d1) {
          d2 = inputs[inputID];
          if ((d < d2) && (d2 < d1)) {
            if (b) {
              qY = MIN_int32_T;
            } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
              qY = MAX_int32_T;
            } else {
              qY = (q0 + mfID) + 1;
            }
            varargin_2_data[qY - 1] = (d2 - d) * (1.0 / (d1 - d));
          }
        }
        d = varargin_1[inputID].f1.data[mfID].params.data[2];
        if (d1 != d) {
          d2 = inputs[inputID];
          if ((d1 < d2) && (d2 < d)) {
            if (b) {
              qY = MIN_int32_T;
            } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
              qY = MAX_int32_T;
            } else {
              qY = (q0 + mfID) + 1;
            }
            varargin_2_data[qY - 1] = (d - d2) * (1.0 / (d - d1));
          }
        }
        if (inputs[inputID] == d1) {
          if (b) {
            qY = MIN_int32_T;
          } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
            qY = MAX_int32_T;
          } else {
            qY = (q0 + mfID) + 1;
          }
          varargin_2_data[qY - 1] = 1.0;
        }
      } else if (b_isequal(varargin_1[inputID].f1.data[mfID].type.data,
                           varargin_1[inputID].f1.data[mfID].type.size, uv1)) {
        double b_value;
        double d1;
        double d2;
        double y;
        b_value = 0.0;
        y = 0.0;
        d = varargin_1[inputID].f1.data[mfID].params.data[1];
        d1 = inputs[inputID];
        if (d1 >= d) {
          b_value = 1.0;
        }
        d2 = varargin_1[inputID].f1.data[mfID].params.data[0];
        if (d1 < d2) {
          b_value = 0.0;
        }
        if ((d2 <= d1) && (d1 < d) && (d2 != d)) {
          b_value = (d1 - d2) * (1.0 / (d - d2));
        }
        d = varargin_1[inputID].f1.data[mfID].params.data[2];
        if (d1 <= d) {
          y = 1.0;
        }
        d2 = varargin_1[inputID].f1.data[mfID].params.data[3];
        if (d1 > d2) {
          y = 0.0;
        }
        if ((d < d1) && (d1 <= d2) && (d != d2)) {
          y = (d2 - d1) * (1.0 / (d2 - d));
        }
        if (b) {
          qY = MIN_int32_T;
        } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
          qY = MAX_int32_T;
        } else {
          qY = (q0 + mfID) + 1;
        }
        varargin_2_data[qY - 1] = fmin(b_value, y);
      } else if (c_isequal(varargin_1[inputID].f1.data[mfID].type.data,
                           varargin_1[inputID].f1.data[mfID].type.size, uv2)) {
        double y;
        y = inputs[inputID] - varargin_1[inputID].f1.data[mfID].params.data[1];
        d = varargin_1[inputID].f1.data[mfID].params.data[0];
        if (b) {
          qY = MIN_int32_T;
        } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
          qY = MAX_int32_T;
        } else {
          qY = (q0 + mfID) + 1;
        }
        varargin_2_data[qY - 1] = exp(-(y * y) / (2.0 * (d * d)));
      } else if (c_isequal(varargin_1[inputID].f1.data[mfID].type.data,
                           varargin_1[inputID].f1.data[mfID].type.size, uv3)) {
        double b_value;
        double y;
        y = 0.0;
        b_value = (inputs[inputID] -
                   varargin_1[inputID].f1.data[mfID].params.data[2]) *
                  (1.0 / varargin_1[inputID].f1.data[mfID].params.data[0]);
        b_value *= b_value;
        if ((b_value <= 0.0) &&
            (varargin_1[inputID].f1.data[mfID].params.data[1] == 0.0)) {
          y = 0.5;
        } else if ((!(b_value <= 0.0)) ||
                   (!(varargin_1[inputID].f1.data[mfID].params.data[1] <
                      0.0))) {
          d = varargin_1[inputID].f1.data[mfID].params.data[1];
          if (rtIsNaN(b_value) || rtIsNaN(d)) {
            b_value = rtNaN;
          } else {
            double d1;
            double d2;
            d1 = fabs(b_value);
            d2 = fabs(d);
            if (rtIsInf(d)) {
              if (d1 == 1.0) {
                b_value = 1.0;
              } else if (d1 > 1.0) {
                if (d > 0.0) {
                  b_value = rtInf;
                } else {
                  b_value = 0.0;
                }
              } else if (d > 0.0) {
                b_value = 0.0;
              } else {
                b_value = rtInf;
              }
            } else if (d2 == 0.0) {
              b_value = 1.0;
            } else if (d2 == 1.0) {
              if (!(d > 0.0)) {
                b_value = 1.0 / b_value;
              }
            } else if (d == 2.0) {
              b_value *= b_value;
            } else if ((d == 0.5) && (b_value >= 0.0)) {
              b_value = sqrt(b_value);
            } else if ((b_value < 0.0) && (d > floor(d))) {
              b_value = rtNaN;
            } else {
              b_value = pow(b_value, d);
            }
          }
          y = 1.0 / (b_value + 1.0);
        }
        if (b) {
          qY = MIN_int32_T;
        } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
          qY = MAX_int32_T;
        } else {
          qY = (q0 + mfID) + 1;
        }
        varargin_2_data[qY - 1] = y;
      } else if (isequal(varargin_1[inputID].f1.data[mfID].type.data,
                         varargin_1[inputID].f1.data[mfID].type.size, uv4)) {
        if (b) {
          qY = MIN_int32_T;
        } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
          qY = MAX_int32_T;
        } else {
          qY = (q0 + mfID) + 1;
        }
        varargin_2_data[qY - 1] =
            1.0 / (exp(-varargin_1[inputID].f1.data[mfID].params.data[0] *
                       (inputs[inputID] -
                        varargin_1[inputID].f1.data[mfID].params.data[1])) +
                   1.0);
      } else if (d_isequal(varargin_1[inputID].f1.data[mfID].type.data,
                           varargin_1[inputID].f1.data[mfID].type.size, uv5)) {
        double d1;
        d = varargin_1[inputID].f1.data[mfID].params.data[0];
        d1 = varargin_1[inputID].f1.data[mfID].params.data[1];
        if (d >= d1) {
          if (b) {
            qY = MIN_int32_T;
          } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
            qY = MAX_int32_T;
          } else {
            qY = (q0 + mfID) + 1;
          }
          varargin_2_data[qY - 1] = (inputs[inputID] >= (d + d1) / 2.0);
        } else {
          double b_value;
          double d2;
          if (b) {
            qY = MIN_int32_T;
          } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
            qY = MAX_int32_T;
          } else {
            qY = (q0 + mfID) + 1;
          }
          varargin_2_data[qY - 1] = 0.0;
          d2 = inputs[inputID];
          if ((d < d2) && (d2 <= (d + d1) / 2.0)) {
            b_value = (d2 - d) * (1.0 / (d1 - d));
            if (b) {
              qY = MIN_int32_T;
            } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
              qY = MAX_int32_T;
            } else {
              qY = (q0 + mfID) + 1;
            }
            varargin_2_data[qY - 1] = 2.0 * b_value * b_value;
          }
          if (((d + d1) / 2.0 < d2) && (d2 <= d1)) {
            b_value = (d1 - d2) * (1.0 / (d1 - d));
            if (b) {
              qY = MIN_int32_T;
            } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
              qY = MAX_int32_T;
            } else {
              qY = (q0 + mfID) + 1;
            }
            varargin_2_data[qY - 1] = 1.0 - 2.0 * b_value * b_value;
          }
          if (d1 <= d2) {
            if (b) {
              qY = MIN_int32_T;
            } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
              qY = MAX_int32_T;
            } else {
              qY = (q0 + mfID) + 1;
            }
            varargin_2_data[qY - 1] = 1.0;
          }
        }
      } else if (d_isequal(varargin_1[inputID].f1.data[mfID].type.data,
                           varargin_1[inputID].f1.data[mfID].type.size, uv6)) {
        double d1;
        d = varargin_1[inputID].f1.data[mfID].params.data[0];
        d1 = varargin_1[inputID].f1.data[mfID].params.data[1];
        if (d >= d1) {
          if (b) {
            qY = MIN_int32_T;
          } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
            qY = MAX_int32_T;
          } else {
            qY = (q0 + mfID) + 1;
          }
          varargin_2_data[qY - 1] = (inputs[inputID] <= (d + d1) / 2.0);
        } else {
          double b_value;
          double d2;
          if (b) {
            qY = MIN_int32_T;
          } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
            qY = MAX_int32_T;
          } else {
            qY = (q0 + mfID) + 1;
          }
          varargin_2_data[qY - 1] = 0.0;
          d2 = inputs[inputID];
          if (d2 <= d) {
            if (b) {
              qY = MIN_int32_T;
            } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
              qY = MAX_int32_T;
            } else {
              qY = (q0 + mfID) + 1;
            }
            varargin_2_data[qY - 1] = 1.0;
          }
          if ((d < d2) && (d2 <= (d + d1) / 2.0)) {
            b_value = (d2 - d) * (1.0 / (d - d1));
            if (b) {
              qY = MIN_int32_T;
            } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
              qY = MAX_int32_T;
            } else {
              qY = (q0 + mfID) + 1;
            }
            varargin_2_data[qY - 1] = 1.0 - 2.0 * b_value * b_value;
          }
          if (((d + d1) / 2.0 < d2) && (d2 <= d1)) {
            b_value = (d1 - d2) * (1.0 / (d - d1));
            if (b) {
              qY = MIN_int32_T;
            } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
              qY = MAX_int32_T;
            } else {
              qY = (q0 + mfID) + 1;
            }
            varargin_2_data[qY - 1] = 2.0 * b_value * b_value;
          }
          if (d1 <= d2) {
            if (b) {
              qY = MIN_int32_T;
            } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
              qY = MAX_int32_T;
            } else {
              qY = (q0 + mfID) + 1;
            }
            varargin_2_data[qY - 1] = 0.0;
          }
        }
      } else if (b_isequal(varargin_1[inputID].f1.data[mfID].type.data,
                           varargin_1[inputID].f1.data[mfID].type.size, uv7)) {
        double d1;
        if (b) {
          qY = MIN_int32_T;
        } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
          qY = MAX_int32_T;
        } else {
          qY = (q0 + mfID) + 1;
        }
        varargin_2_data[qY - 1] = 0.0;
        d = varargin_1[inputID].f1.data[mfID].params.data[1];
        d1 = inputs[inputID];
        if (d1 >= d) {
          if (b) {
            qY = MIN_int32_T;
          } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
            qY = MAX_int32_T;
          } else {
            qY = (q0 + mfID) + 1;
          }
          varargin_2_data[qY - 1] = 1.0;
        } else {
          double d2;
          d2 = varargin_1[inputID].f1.data[mfID].params.data[0];
          if (d1 >= d2) {
            if (b) {
              qY = MIN_int32_T;
            } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
              qY = MAX_int32_T;
            } else {
              qY = (q0 + mfID) + 1;
            }
            varargin_2_data[qY - 1] = (d1 - d2) * (1.0 / (d - d2));
          }
        }
      } else if (b_isequal(varargin_1[inputID].f1.data[mfID].type.data,
                           varargin_1[inputID].f1.data[mfID].type.size, uv8)) {
        double d1;
        if (b) {
          qY = MIN_int32_T;
        } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
          qY = MAX_int32_T;
        } else {
          qY = (q0 + mfID) + 1;
        }
        varargin_2_data[qY - 1] = 0.0;
        d = varargin_1[inputID].f1.data[mfID].params.data[0];
        d1 = inputs[inputID];
        if (d1 < d) {
          if (b) {
            qY = MIN_int32_T;
          } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
            qY = MAX_int32_T;
          } else {
            qY = (q0 + mfID) + 1;
          }
          varargin_2_data[qY - 1] = 1.0;
        } else {
          double d2;
          d2 = varargin_1[inputID].f1.data[mfID].params.data[1];
          if (d1 < d2) {
            if (b) {
              qY = MIN_int32_T;
            } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
              qY = MAX_int32_T;
            } else {
              qY = (q0 + mfID) + 1;
            }
            varargin_2_data[qY - 1] = (d2 - d1) * (1.0 / (d2 - d));
          }
        }
      } else if (e_isequal(varargin_1[inputID].f1.data[mfID].type.data,
                           varargin_1[inputID].f1.data[mfID].type.size, uv9)) {
        double b_value;
        double d1;
        double d2;
        double y;
        boolean_T c1Index;
        boolean_T c2Index;
        d = varargin_1[inputID].f1.data[mfID].params.data[1];
        d1 = inputs[inputID];
        c1Index = (d1 <= d);
        d2 = varargin_1[inputID].f1.data[mfID].params.data[3];
        c2Index = (d1 >= d2);
        y = d1 - d;
        b_value = d1 - d2;
        d = varargin_1[inputID].f1.data[mfID].params.data[0];
        d1 = varargin_1[inputID].f1.data[mfID].params.data[2];
        if (b) {
          qY = MIN_int32_T;
        } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
          qY = MAX_int32_T;
        } else {
          qY = (q0 + mfID) + 1;
        }
        varargin_2_data[qY - 1] =
            (exp(-(y * y) / (2.0 * (d * d))) * (double)c1Index +
             (1.0 - (double)c1Index)) *
            (exp(-(b_value * b_value) / (2.0 * (d1 * d1))) * (double)c2Index +
             (1.0 - (double)c2Index));
      } else if (b_isequal(varargin_1[inputID].f1.data[mfID].type.data,
                           varargin_1[inputID].f1.data[mfID].type.size, uv10)) {
        if (b) {
          qY = MIN_int32_T;
        } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
          qY = MAX_int32_T;
        } else {
          qY = (q0 + mfID) + 1;
        }
        d = inputs[inputID];
        varargin_2_data[qY - 1] = fabs(
            1.0 / (exp(-varargin_1[inputID].f1.data[mfID].params.data[0] *
                       (d - varargin_1[inputID].f1.data[mfID].params.data[1])) +
                   1.0) -
            1.0 / (exp(-varargin_1[inputID].f1.data[mfID].params.data[2] *
                       (d - varargin_1[inputID].f1.data[mfID].params.data[3])) +
                   1.0));
      } else if (b_isequal(varargin_1[inputID].f1.data[mfID].type.data,
                           varargin_1[inputID].f1.data[mfID].type.size, uv11)) {
        if (b) {
          qY = MIN_int32_T;
        } else if ((q0 > 0) && (mfID + 1 > MAX_int32_T - q0)) {
          qY = MAX_int32_T;
        } else {
          qY = (q0 + mfID) + 1;
        }
        d = inputs[inputID];
        varargin_2_data[qY - 1] =
            1.0 /
            (exp(-varargin_1[inputID].f1.data[mfID].params.data[0] *
                 (d - varargin_1[inputID].f1.data[mfID].params.data[1])) +
             1.0) *
            (1.0 /
             (exp(-varargin_1[inputID].f1.data[mfID].params.data[2] *
                  (d - varargin_1[inputID].f1.data[mfID].params.data[3])) +
              1.0));
      } else {
        boolean_T c1Index;
        qY = varargin_1[inputID].f1.data[mfID].type.size[1];
        c1Index = (qY == 4);
        if (c1Index && (qY != 0)) {
          boolean_T exitg1;
          qY = 0;
          exitg1 = false;
          while ((!exitg1) && (qY < 4)) {
            if ((unsigned char)varargin_1[inputID]
                    .f1.data[mfID]
                    .type.data[qY] != uv12[qY]) {
              c1Index = false;
              exitg1 = true;
            } else {
              qY++;
            }
          }
        }
        if (c1Index) {
          double b_value;
          double d1;
          double d2;
          double y;
          d = varargin_1[inputID].f1.data[mfID].params.data[0];
          d1 = varargin_1[inputID].f1.data[mfID].params.data[1];
          if (d >= d1) {
            d2 = inputs[inputID];
            y = (d2 >= (d + d1) / 2.0);
          } else {
            y = 0.0;
            d2 = inputs[inputID];
            if ((d < d2) && (d2 <= (d + d1) / 2.0)) {
              b_value = (d2 - d) * (1.0 / (d1 - d));
              y = 2.0 * b_value * b_value;
            }
            if (((d + d1) / 2.0 < d2) && (d2 <= d1)) {
              b_value = (d1 - d2) * (1.0 / (d1 - d));
              y = 1.0 - 2.0 * b_value * b_value;
            }
            if (d1 <= d2) {
              y = 1.0;
            }
          }
          d = varargin_1[inputID].f1.data[mfID].params.data[2];
          d1 = varargin_1[inputID].f1.data[mfID].params.data[3];
          if (d >= d1) {
            b_value = (d2 <= (d + d1) / 2.0);
          } else {
            b_value = 0.0;
            if (d2 <= d) {
              b_value = 1.0;
            }
            if ((d < d2) && (d2 <= (d + d1) / 2.0)) {
              b_value = (d2 - d) * (1.0 / (d - d1));
              b_value = 1.0 - 2.0 * b_value * b_value;
            }
            if (((d + d1) / 2.0 < d2) && (d2 <= d1)) {
              b_value = (d1 - d2) * (1.0 / (d - d1));
              b_value *= 2.0 * b_value;
            }
            if (d1 <= d2) {
              b_value = 0.0;
            }
          }
          qY = fis_numCumInputMFs[inputID];
          if (b) {
            qY = MIN_int32_T;
          } else if ((qY > 0) && (mfID + 1 > MAX_int32_T - qY)) {
            qY = MAX_int32_T;
          } else {
            qY = (qY + mfID) + 1;
          }
          varargin_2_data[qY - 1] = y * b_value;
        } else {
          exit(0);
        }
      }
    }
  }
  for (q0 = 0; q0 < 7; q0++) {
    d = rt_roundd_snf(fabs(fis_antecedent[q0]));
    if (d < 2.147483648E+9) {
      qY = (int)d;
    } else if (d >= 2.147483648E+9) {
      qY = MAX_int32_T;
    } else {
      qY = 0;
    }
    if (qY == 0) {
      fuzzifiedInputs[q0] = 1.0;
    } else {
      if ((fis_numCumInputMFs[0] < 0) &&
          (qY < MIN_int32_T - fis_numCumInputMFs[0])) {
        qY = MIN_int32_T;
      } else if ((fis_numCumInputMFs[0] > 0) &&
                 (qY > MAX_int32_T - fis_numCumInputMFs[0])) {
        qY = MAX_int32_T;
      } else {
        qY += fis_numCumInputMFs[0];
      }
      fuzzifiedInputs[q0] = varargin_2_data[qY - 1];
    }
    d = rt_roundd_snf(fabs(fis_antecedent[q0 + 7]));
    if (d < 2.147483648E+9) {
      qY = (int)d;
    } else if (d >= 2.147483648E+9) {
      qY = MAX_int32_T;
    } else {
      qY = 0;
    }
    if (qY == 0) {
      fuzzifiedInputs[q0 + 7] = 1.0;
    } else {
      if ((fis_numCumInputMFs[1] < 0) &&
          (qY < MIN_int32_T - fis_numCumInputMFs[1])) {
        qY = MIN_int32_T;
      } else if ((fis_numCumInputMFs[1] > 0) &&
                 (qY > MAX_int32_T - fis_numCumInputMFs[1])) {
        qY = MAX_int32_T;
      } else {
        qY += fis_numCumInputMFs[1];
      }
      fuzzifiedInputs[q0 + 7] = varargin_2_data[qY - 1];
    }
  }
}

/*
 * File trailer for fuzzifyInputs.c
 *
 * [EOF]
 */
