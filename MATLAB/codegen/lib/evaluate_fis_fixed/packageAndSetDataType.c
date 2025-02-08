/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: packageAndSetDataType.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 04-Feb-2025 19:00:21
 */

/* Include Files */
#include "packageAndSetDataType.h"
#include "evaluate_fis_fixed_internal_types.h"
#include "evaluate_fis_fixed_rtwutil.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Type Definitions */
#ifndef typedef_c_struct_T
#define typedef_c_struct_T
typedef struct {
  emxArray_char_T_1x8 type;
  double origTypeLength;
  emxArray_real_T_1x4 params;
  double origParamLength;
} c_struct_T;
#endif /* typedef_c_struct_T */

#ifndef typedef_emxArray_struct_T_1x5
#define typedef_emxArray_struct_T_1x5
typedef struct {
  c_struct_T data[5];
  int size[2];
} emxArray_struct_T_1x5;
#endif /* typedef_emxArray_struct_T_1x5 */

#ifndef typedef_d_struct_T
#define typedef_d_struct_T
typedef struct {
  emxArray_struct_T_1x5 mf;
  double origNumMF;
} d_struct_T;
#endif /* typedef_d_struct_T */

/* Function Declarations */
static double b_cast(const char t1_mf_type_data[], const int t1_mf_type_size[2],
                     double t1_mf_origTypeLength,
                     const double t1_mf_params_data[],
                     const int t1_mf_params_size[2],
                     double t1_mf_origParamLength, c_struct_T t2_mf_data[],
                     int t2_mf_size[2]);

static double cast(char t0_type_data[], int t0_type_size[2],
                   double t0_params_data[], int t0_params_size[2],
                   double *t0_origParamLength);

/* Function Definitions */
/*
 * Arguments    : const char t1_mf_type_data[]
 *                const int t1_mf_type_size[2]
 *                double t1_mf_origTypeLength
 *                const double t1_mf_params_data[]
 *                const int t1_mf_params_size[2]
 *                double t1_mf_origParamLength
 *                c_struct_T t2_mf_data[]
 *                int t2_mf_size[2]
 * Return Type  : double
 */
static double b_cast(const char t1_mf_type_data[], const int t1_mf_type_size[2],
                     double t1_mf_origTypeLength,
                     const double t1_mf_params_data[],
                     const int t1_mf_params_size[2],
                     double t1_mf_origParamLength, c_struct_T t2_mf_data[],
                     int t2_mf_size[2])
{
  int i;
  int loop_ub;
  t2_mf_size[0] = 1;
  t2_mf_size[1] = 1;
  t2_mf_data[0].type.size[0] = 1;
  loop_ub = t1_mf_type_size[1];
  t2_mf_data[0].type.size[1] = t1_mf_type_size[1];
  for (i = 0; i < loop_ub; i++) {
    t2_mf_data[0].type.data[i] = t1_mf_type_data[i];
  }
  t2_mf_data[0].origTypeLength = t1_mf_origTypeLength;
  t2_mf_data[0].params.size[0] = 1;
  loop_ub = t1_mf_params_size[1];
  t2_mf_data[0].params.size[1] = t1_mf_params_size[1];
  for (i = 0; i < loop_ub; i++) {
    t2_mf_data[0].params.data[i] = t1_mf_params_data[i];
  }
  t2_mf_data[0].origParamLength = t1_mf_origParamLength;
  return 0.0;
}

/*
 * Arguments    : char t0_type_data[]
 *                int t0_type_size[2]
 *                double t0_params_data[]
 *                int t0_params_size[2]
 *                double *t0_origParamLength
 * Return Type  : double
 */
static double cast(char t0_type_data[], int t0_type_size[2],
                   double t0_params_data[], int t0_params_size[2],
                   double *t0_origParamLength)
{
  double t0_origTypeLength;
  t0_type_size[0] = 1;
  t0_type_size[1] = 1;
  t0_type_data[0] = '\x00';
  t0_origTypeLength = 0.0;
  t0_params_size[0] = 1;
  t0_params_size[1] = 1;
  t0_params_data[0] = 0.0;
  *t0_origParamLength = 0.0;
  return t0_origTypeLength;
}

/*
 * Arguments    : const char fis_andMethod[4]
 *                const char fis_defuzzMethod[6]
 *                const f_struct_T fis_input[2]
 *                const double fis_output_range[2]
 *                const g_struct_T fis_output_mf[5]
 *                const h_struct_T fis_rule[7]
 *                m_struct_T *fis
 * Return Type  : void
 */
void packageAndSetDataType(const char fis_andMethod[4],
                           const char fis_defuzzMethod[6],
                           const f_struct_T fis_input[2],
                           const double fis_output_range[2],
                           const g_struct_T fis_output_mf[5],
                           const h_struct_T fis_rule[7], m_struct_T *fis)
{
  b_struct_T b_mfStruct;
  b_struct_T mfStruct;
  c_struct_T mfStruct_tmp;
  d_struct_T fis_inputMF[2];
  d_struct_T varStruct;
  emxArray_struct_T_1x5 fis_outputMF_mf;
  l_struct_T b_varStruct;
  double d;
  int fis_inputMF_idx_1;
  int i;
  int maxMFParamLength;
  int maxMFTypeLength;
  int maxNumMF;
  int mfID;
  int varID;
  mfStruct_tmp.origTypeLength = cast(
      mfStruct_tmp.type.data, mfStruct_tmp.type.size, mfStruct_tmp.params.data,
      mfStruct_tmp.params.size, &mfStruct_tmp.origParamLength);
  varStruct.origNumMF =
      b_cast(mfStruct_tmp.type.data, mfStruct_tmp.type.size,
             mfStruct_tmp.origTypeLength, mfStruct_tmp.params.data,
             mfStruct_tmp.params.size, mfStruct_tmp.origParamLength,
             varStruct.mf.data, varStruct.mf.size);
  maxNumMF = 0;
  maxMFTypeLength = 0;
  maxMFParamLength = 0;
  for (varID = 0; varID < 2; varID++) {
    fis_inputMF[varID] = varStruct;
    if (maxNumMF < 3) {
      maxNumMF = 3;
    }
    if (maxMFTypeLength < 8) {
      maxMFTypeLength = 8;
    }
    if (maxMFParamLength < 4) {
      maxMFParamLength = 4;
    }
  }
  for (varID = 0; varID < 2; varID++) {
    fis_inputMF[varID].origNumMF = 3.0;
    fis_inputMF[varID].mf.size[0] = 1;
    fis_inputMF[varID].mf.size[1] = maxNumMF;
    for (mfID = 0; mfID < maxNumMF; mfID++) {
      fis_inputMF[varID].mf.data[mfID] = mfStruct_tmp;
      fis_inputMF[varID].mf.data[mfID].type.size[0] = 1;
      fis_inputMF[varID].mf.data[mfID].type.size[1] = maxMFTypeLength;
      for (i = 0; i < maxMFTypeLength; i++) {
        fis_inputMF[varID].mf.data[mfID].type.data[i] = '\x00';
      }
      fis_inputMF[varID].mf.data[mfID].params.size[0] = 1;
      fis_inputMF[varID].mf.data[mfID].params.size[1] = maxMFParamLength;
      for (i = 0; i < maxMFParamLength; i++) {
        fis_inputMF[varID].mf.data[mfID].params.data[i] = 0.0;
      }
      fis_inputMF[varID].mf.data[mfID].origTypeLength = 0.0;
      fis_inputMF[varID].mf.data[mfID].origParamLength = 0.0;
      if ((double)mfID + 1.0 <= fis_inputMF[varID].origNumMF) {
        fis_inputMF_idx_1 = fis_inputMF[varID].mf.data[mfID].type.size[1];
        fis_inputMF[varID].mf.data[mfID].type.size[0] = 1;
        fis_inputMF[varID].mf.data[mfID].type.size[1] = fis_inputMF_idx_1;
        for (i = 0; i < fis_inputMF_idx_1; i++) {
          fis_inputMF[varID].mf.data[mfID].type.data[i] =
              fis_input[varID].mf[mfID].type[i];
        }
        fis_inputMF[varID].mf.data[mfID].origTypeLength = 8.0;
        fis_inputMF_idx_1 = fis_inputMF[varID].mf.data[mfID].params.size[1];
        fis_inputMF[varID].mf.data[mfID].params.size[0] = 1;
        fis_inputMF[varID].mf.data[mfID].params.size[1] = fis_inputMF_idx_1;
        for (i = 0; i < fis_inputMF_idx_1; i++) {
          fis_inputMF[varID].mf.data[mfID].params.data[i] =
              fis_input[varID].mf[mfID].params[i];
        }
        fis_inputMF[varID].mf.data[mfID].origParamLength = 4.0;
      }
    }
  }
  maxMFTypeLength = 0;
  maxMFParamLength = 0;
  for (mfID = 0; mfID < 5; mfID++) {
    if (maxMFTypeLength < 8) {
      maxMFTypeLength = 8;
    }
    if (maxMFParamLength < 1) {
      maxMFParamLength = 1;
    }
    fis_outputMF_mf.data[mfID] = mfStruct_tmp;
  }
  for (mfID = 0; mfID < 5; mfID++) {
    fis_outputMF_mf.data[mfID].type.size[0] = 1;
    fis_outputMF_mf.data[mfID].type.size[1] = maxMFTypeLength;
    for (i = 0; i < maxMFTypeLength; i++) {
      fis_outputMF_mf.data[mfID].type.data[i] = '\x00';
    }
    fis_outputMF_mf.data[mfID].params.size[0] = 1;
    fis_outputMF_mf.data[mfID].params.size[1] = maxMFParamLength;
    if (maxMFParamLength - 1 >= 0) {
      fis_outputMF_mf.data[mfID].params.data[0] = 0.0;
    }
    fis_outputMF_mf.data[mfID].origTypeLength = 0.0;
    fis_outputMF_mf.data[mfID].origParamLength = 0.0;
    fis_inputMF_idx_1 = fis_outputMF_mf.data[mfID].type.size[1];
    fis_outputMF_mf.data[mfID].type.size[0] = 1;
    fis_outputMF_mf.data[mfID].type.size[1] = fis_inputMF_idx_1;
    for (i = 0; i < fis_inputMF_idx_1; i++) {
      fis_outputMF_mf.data[mfID].type.data[i] = fis_output_mf[mfID].type[i];
    }
    fis_outputMF_mf.data[mfID].origTypeLength = 8.0;
    fis_inputMF_idx_1 = fis_outputMF_mf.data[mfID].params.size[1];
    fis_outputMF_mf.data[mfID].params.size[0] = 1;
    fis_outputMF_mf.data[mfID].params.size[1] = fis_inputMF_idx_1;
    for (i = 0; i < fis_inputMF_idx_1; i++) {
      fis_outputMF_mf.data[mfID].params.data[i] = fis_output_mf[mfID].params;
    }
    fis_outputMF_mf.data[mfID].origParamLength = 1.0;
  }
  for (maxNumMF = 0; maxNumMF < 7; maxNumMF++) {
    fis->antecedent[maxNumMF] = fis_rule[maxNumMF].antecedent[0];
    fis->antecedent[maxNumMF + 7] = fis_rule[maxNumMF].antecedent[1];
    fis->consequent[maxNumMF] = fis_rule[maxNumMF].consequent;
  }
  fis->andMethod[0] = (unsigned char)fis_andMethod[0];
  fis->andMethod[1] = (unsigned char)fis_andMethod[1];
  fis->andMethod[2] = (unsigned char)fis_andMethod[2];
  fis->andMethod[3] = (unsigned char)fis_andMethod[3];
  for (i = 0; i < 6; i++) {
    fis->defuzzMethod[i] = (unsigned char)fis_defuzzMethod[i];
  }
  fis->outputRange[0] = fis_output_range[0];
  fis->outputRange[1] = fis_output_range[1];
  mfStruct.type.size[0] = 1;
  maxNumMF = fis_inputMF[0].mf.data[0].type.size[1];
  mfStruct.type.size[1] = fis_inputMF[0].mf.data[0].type.size[1];
  if (maxNumMF - 1 >= 0) {
    memset(&mfStruct.type.data[0], 0, (unsigned int)maxNumMF * sizeof(char));
  }
  mfStruct.origTypeLength = 0;
  mfStruct.params.size[0] = 1;
  maxNumMF = fis_inputMF[0].mf.data[0].params.size[1];
  mfStruct.params.size[1] = fis_inputMF[0].mf.data[0].params.size[1];
  if (maxNumMF - 1 >= 0) {
    memset(&mfStruct.params.data[0], 0,
           (unsigned int)maxNumMF * sizeof(double));
  }
  mfStruct.origParamLength = 0;
  maxNumMF = fis_inputMF[0].mf.size[1];
  for (i = 0; i < maxNumMF; i++) {
    b_varStruct.mf.data[i] = mfStruct;
  }
  b_varStruct.origNumMF = 0;
  for (varID = 0; varID < 2; varID++) {
    fis->inputMF[varID] = b_varStruct;
    d = rt_roundd_snf(fis_inputMF[varID].origNumMF);
    if (d < 2.147483648E+9) {
      if (d >= -2.147483648E+9) {
        i = (int)d;
      } else {
        i = MIN_int32_T;
      }
    } else if (d >= 2.147483648E+9) {
      i = MAX_int32_T;
    } else {
      i = 0;
    }
    fis->inputMF[varID].origNumMF = i;
    for (mfID = 0; mfID < maxNumMF; mfID++) {
      fis->inputMF[varID].mf.data[mfID].type.size[0] = 1;
      maxMFTypeLength = fis_inputMF[varID].mf.data[mfID].type.size[1];
      fis->inputMF[varID].mf.data[mfID].type.size[1] = maxMFTypeLength;
      for (i = 0; i < maxMFTypeLength; i++) {
        fis->inputMF[varID].mf.data[mfID].type.data[i] =
            fis_inputMF[varID].mf.data[mfID].type.data[i];
      }
      fis->inputMF[varID].mf.data[mfID].params.size[0] = 1;
      maxMFTypeLength = fis_inputMF[varID].mf.data[mfID].params.size[1];
      fis->inputMF[varID].mf.data[mfID].params.size[1] = maxMFTypeLength;
      for (i = 0; i < maxMFTypeLength; i++) {
        fis->inputMF[varID].mf.data[mfID].params.data[i] =
            fis_inputMF[varID].mf.data[mfID].params.data[i];
      }
      d = rt_roundd_snf(fis_inputMF[varID].mf.data[mfID].origTypeLength);
      if (d < 2.147483648E+9) {
        if (d >= -2.147483648E+9) {
          i = (int)d;
        } else {
          i = MIN_int32_T;
        }
      } else if (d >= 2.147483648E+9) {
        i = MAX_int32_T;
      } else {
        i = 0;
      }
      fis->inputMF[varID].mf.data[mfID].origTypeLength = i;
      d = rt_roundd_snf(fis_inputMF[varID].mf.data[mfID].origParamLength);
      if (d < 2.147483648E+9) {
        if (d >= -2.147483648E+9) {
          i = (int)d;
        } else {
          i = MIN_int32_T;
        }
      } else if (d >= 2.147483648E+9) {
        i = MAX_int32_T;
      } else {
        i = 0;
      }
      fis->inputMF[varID].mf.data[mfID].origParamLength = i;
    }
  }
  b_mfStruct.type.size[0] = 1;
  maxNumMF = fis_outputMF_mf.data[0].type.size[1];
  b_mfStruct.type.size[1] = fis_outputMF_mf.data[0].type.size[1];
  if (maxNumMF - 1 >= 0) {
    memset(&b_mfStruct.type.data[0], 0, (unsigned int)maxNumMF * sizeof(char));
  }
  b_mfStruct.origTypeLength = 0;
  b_mfStruct.params.size[0] = 1;
  maxNumMF = fis_outputMF_mf.data[0].params.size[1];
  b_mfStruct.params.size[1] = fis_outputMF_mf.data[0].params.size[1];
  if (maxNumMF - 1 >= 0) {
    memset(&b_mfStruct.params.data[0], 0,
           (unsigned int)maxNumMF * sizeof(double));
  }
  b_mfStruct.origParamLength = 0;
  fis->outputMF.origNumMF = 5;
  for (mfID = 0; mfID < 5; mfID++) {
    fis->outputMF.mf.data[mfID] = b_mfStruct;
    fis->outputMF.mf.data[mfID].type.size[0] = 1;
    maxMFTypeLength = fis_outputMF_mf.data[mfID].type.size[1];
    fis->outputMF.mf.data[mfID].type.size[1] = maxMFTypeLength;
    for (i = 0; i < maxMFTypeLength; i++) {
      fis->outputMF.mf.data[mfID].type.data[i] =
          fis_outputMF_mf.data[mfID].type.data[i];
    }
    fis->outputMF.mf.data[mfID].params.size[0] = 1;
    maxMFTypeLength = fis_outputMF_mf.data[mfID].params.size[1];
    fis->outputMF.mf.data[mfID].params.size[1] = maxMFTypeLength;
    for (i = 0; i < maxMFTypeLength; i++) {
      fis->outputMF.mf.data[mfID].params.data[i] =
          fis_outputMF_mf.data[mfID].params.data[i];
    }
    d = rt_roundd_snf(fis_outputMF_mf.data[mfID].origTypeLength);
    if (d < 2.147483648E+9) {
      if (d >= -2.147483648E+9) {
        i = (int)d;
      } else {
        i = MIN_int32_T;
      }
    } else if (d >= 2.147483648E+9) {
      i = MAX_int32_T;
    } else {
      i = 0;
    }
    fis->outputMF.mf.data[mfID].origTypeLength = i;
    d = rt_roundd_snf(fis_outputMF_mf.data[mfID].origParamLength);
    if (d < 2.147483648E+9) {
      if (d >= -2.147483648E+9) {
        i = (int)d;
      } else {
        i = MIN_int32_T;
      }
    } else if (d >= 2.147483648E+9) {
      i = MAX_int32_T;
    } else {
      i = 0;
    }
    fis->outputMF.mf.data[mfID].origParamLength = i;
  }
  fis->numCumInputMFs[0] = 0;
  fis->numCumInputMFs[1] = 3;
}

/*
 * File trailer for packageAndSetDataType.c
 *
 * [EOF]
 */
