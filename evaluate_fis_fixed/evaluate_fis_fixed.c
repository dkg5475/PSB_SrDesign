/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: evaluate_fis_fixed.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 04-Feb-2025 19:00:21
 */

/* Include Files */
#include "evaluate_fis_fixed.h"
#include "evalfis.h"
#include "evaluate_fis_fixed_data.h"
#include "evaluate_fis_fixed_initialize.h"
#include "evaluate_fis_fixed_internal_types.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Type Definitions */
#ifndef typedef_i_struct_T
#define typedef_i_struct_T
typedef struct {
  double range[2];
  g_struct_T mf[5];
} i_struct_T;
#endif /* typedef_i_struct_T */

#ifndef typedef_j_struct_T
#define typedef_j_struct_T
typedef struct {
  char type[6];
  char andMethod[4];
  char orMethod[6];
  char defuzzMethod[6];
  char impMethod[4];
  char aggMethod[3];
  f_struct_T input[2];
  i_struct_T output;
  h_struct_T rule[7];
} j_struct_T;
#endif /* typedef_j_struct_T */

#ifndef typedef_k_struct_T
#define typedef_k_struct_T
typedef struct {
  j_struct_T fisCG;
} k_struct_T;
#endif /* typedef_k_struct_T */

/* Variable Definitions */
static k_struct_T fisCG;

/* Function Definitions */
/*
 * Arguments    : double TempDeviation
 *                double TempSlope
 * Return Type  : double
 */
double evaluate_fis_fixed(double TempDeviation, double TempSlope)
{
  double b_TempDeviation[2];
  double output;
  double v;
  short i;
  if (!isInitialized_evaluate_fis_fixed) {
    evaluate_fis_fixed_initialize();
  }
  /*  Convert inputs to fixed-point (Q15 format) inside the function */
  /*  Evaluate the FIS */
  output = TempDeviation * 32768.0;
  v = fabs(output);
  if (v < 4.503599627370496E+15) {
    if (v >= 0.5) {
      output = floor(output + 0.5);
    } else {
      output *= 0.0;
    }
  }
  if (output < 32768.0) {
    if (output >= -32768.0) {
      i = (short)output;
    } else {
      i = MIN_int16_T;
    }
  } else if (output >= 32768.0) {
    i = MAX_int16_T;
  } else {
    i = 0;
  }
  b_TempDeviation[0] = (double)i * 3.0517578125E-5;
  output = TempSlope * 32768.0;
  v = fabs(output);
  if (v < 4.503599627370496E+15) {
    if (v >= 0.5) {
      output = floor(output + 0.5);
    } else {
      output *= 0.0;
    }
  }
  if (output < 32768.0) {
    if (output >= -32768.0) {
      i = (short)output;
    } else {
      i = MIN_int16_T;
    }
  } else if (output >= 32768.0) {
    i = MAX_int16_T;
  } else {
    i = 0;
  }
  b_TempDeviation[1] = (double)i * 3.0517578125E-5;
  return evalfis(fisCG.fisCG.andMethod, fisCG.fisCG.defuzzMethod,
                 fisCG.fisCG.input, fisCG.fisCG.output.range,
                 fisCG.fisCG.output.mf, fisCG.fisCG.rule, b_TempDeviation);
  /*  Convert back to double for evalfis */
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void evaluate_fis_fixed_init(void)
{
  static const k_struct_T r = {
      {
          {'s', 'u', 'g', 'e', 'n', 'o'}, /* type */
          {'p', 'r', 'o', 'd'},           /* andMethod */
          {'p', 'r', 'o', 'b', 'o', 'r'}, /* orMethod */
          {'w', 't', 'a', 'v', 'e', 'r'}, /* defuzzMethod */
          {'p', 'r', 'o', 'd'},           /* impMethod */
          {'s', 'u', 'm'},                /* aggMethod */
          {{
               {90.0, 105.0}, /* range */
               {{
                    {'g', 'a', 'u', 's', 's', '2', 'm', 'f'}, /* type */
                    {1.5, 87.0, 2.0, 90.0}                    /* params */
                },
                {
                    {'g', 'a', 'u', 's', 's', '2', 'm', 'f'}, /* type */
                    {2.0, 96.0, 2.0, 98.0}                    /* params */
                },
                {
                    {'g', 'a', 'u', 's', 's', '2', 'm', 'f'}, /* type */
                    {1.5, 103.0, 2.0, 106.0}                  /* params */
                }}                                            /* mf */
           },
           {
               {-0.5, 0.5}, /* range */
               {{
                    {'g', 'a', 'u', 's', 's', '2', 'm', 'f'}, /* type */
                    {0.1, -0.3, 0.2, -0.1}                    /* params */
                },
                {
                    {'g', 'a', 'u', 's', 's', '2', 'm', 'f'}, /* type */
                    {0.1, -0.05, 0.2, 0.05}                   /* params */
                },
                {
                    {'g', 'a', 'u', 's', 's', '2', 'm', 'f'}, /* type */
                    {0.1, 0.1, 0.2, 0.3}                      /* params */
                }}                                            /* mf */
           }},                                                /* input */
          {
              {-1.0, 1.0}, /* range */
              {{
                   {'c', 'o', 'n', 's', 't', 'a', 'n', 't'}, /* type */
                   -1.0                                      /* params */
               },
               {
                   {'c', 'o', 'n', 's', 't', 'a', 'n', 't'}, /* type */
                   -0.5                                      /* params */
               },
               {
                   {'c', 'o', 'n', 's', 't', 'a', 'n', 't'}, /* type */
                   0.0                                       /* params */
               },
               {
                   {'c', 'o', 'n', 's', 't', 'a', 'n', 't'}, /* type */
                   0.5                                       /* params */
               },
               {
                   {'c', 'o', 'n', 's', 't', 'a', 'n', 't'}, /* type */
                   1.0                                       /* params */
               }}                                            /* mf */
          },                                                 /* output */
          {{
               {1.0, 1.0}, /* antecedent */
               5.0         /* consequent */
           },
           {
               {1.0, 2.0}, /* antecedent */
               4.0         /* consequent */
           },
           {
               {1.0, 3.0}, /* antecedent */
               3.0         /* consequent */
           },
           {
               {2.0, 0.0}, /* antecedent */
               3.0         /* consequent */
           },
           {
               {3.0, 1.0}, /* antecedent */
               3.0         /* consequent */
           },
           {
               {3.0, 2.0}, /* antecedent */
               2.0         /* consequent */
           },
           {
               {3.0, 3.0}, /* antecedent */
               1.0         /* consequent */
           }}              /* rule */
      }                    /* fisCG */
  };
  fisCG = r;
  /*  Load preprocessed FIS data for code generation */
}

/*
 * File trailer for evaluate_fis_fixed.c
 *
 * [EOF]
 */
