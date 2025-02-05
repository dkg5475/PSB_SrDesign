/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_evaluate_fis_fixed_info.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 04-Feb-2025 19:00:21
 */

/* Include Files */
#include "_coder_evaluate_fis_fixed_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *c_emlrtMexFcnResolvedFunctionsI(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : const mxArray *
 */
static const mxArray *c_emlrtMexFcnResolvedFunctionsI(void)
{
  const mxArray *nameCaptureInfo;
  const char_T *data[4] = {
      "789c6360f4f465646060e06380023608c50be50a4069260654802ecf8883860156061614"
      "7d30f97e289d9c9f57925a5102e1e425e6a6c275a6e4e766e625e695"
      "845416a43214a516e7e794a5a68065d2327352433273538391397e205eae1b92149c0392"
      "02b19d335293b3834b73198a328a112ecc41e6c0c32301877f590884",
      "073a400f0f747523c5be1964da0733df9c807d30f9e8d05867ab98d0e2d4a2e21897c4bc"
      "b4cc18ffbc5497a2ccb2d41897fce4d2dcd4bc92e2185fc7101f47a7"
      "98b4cc6297c49244bddcc41282e1c24fa43b71e5035e060e88f9e5b7c152f4b2ef51efab"
      "83f4b40f0606cabe0a1ce6119bcec470d82780269f1c6952ee581615",
      "9294e112996c12901864e6ee57e18c704700017b08b98301079fd6e6030011444e7d",
      ""};
  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 1560U, &nameCaptureInfo);
  return nameCaptureInfo;
}

/*
 * Arguments    : void
 * Return Type  : mxArray *
 */
mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xEntryPoints;
  mxArray *xInputs;
  mxArray *xResult;
  const char_T *propFieldName[9] = {"Version",
                                    "ResolvedFunctions",
                                    "Checksum",
                                    "EntryPoints",
                                    "CoverageInfo",
                                    "IsPolymorphic",
                                    "PropertyList",
                                    "UUID",
                                    "ClassEntryPointIsHandle"};
  const char_T *epFieldName[8] = {
      "QualifiedName",    "NumberOfInputs", "NumberOfOutputs", "ConstantInputs",
      "ResolvedFilePath", "TimeStamp",      "Constructor",     "Visible"};
  xEntryPoints =
      emlrtCreateStructMatrix(1, 1, 8, (const char_T **)&epFieldName[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 2);
  emlrtSetField(xEntryPoints, 0, "QualifiedName",
                emlrtMxCreateString("evaluate_fis_fixed"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs",
                emlrtMxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "ResolvedFilePath",
                emlrtMxCreateString(
                    "C:\\Users\\Danfi\\OneDrive\\Documents\\MATLAB\\evaluate_"
                    "fis_fixed.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp",
                emlrtMxCreateDoubleScalar(739652.79138888884));
  emlrtSetField(xEntryPoints, 0, "Constructor",
                emlrtMxCreateLogicalScalar(false));
  emlrtSetField(xEntryPoints, 0, "Visible", emlrtMxCreateLogicalScalar(true));
  xResult =
      emlrtCreateStructMatrix(1, 1, 9, (const char_T **)&propFieldName[0]);
  emlrtSetField(xResult, 0, "Version",
                emlrtMxCreateString("24.2.0.2773142 (R2024b) Update 2"));
  emlrtSetField(xResult, 0, "ResolvedFunctions",
                (mxArray *)c_emlrtMexFcnResolvedFunctionsI());
  emlrtSetField(xResult, 0, "Checksum",
                emlrtMxCreateString("cY4wAvZTbhDYc4PaR6GNxC"));
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/*
 * File trailer for _coder_evaluate_fis_fixed_info.c
 *
 * [EOF]
 */
