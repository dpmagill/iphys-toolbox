/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_IndexAndMean_LogIdx_info.c
 *
 * Code generation for function '_coder_IndexAndMean_LogIdx_info'
 *
 */

/* Include files */
#include "_coder_IndexAndMean_LogIdx_info.h"
#include "emlrt.h"
#include "rt_nonfinite.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void);

/* Function Definitions */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  const char * data[8] = {
    "789ced57bb72d340149599244393908a0e4674d0646dc7c04c3ac7f12b891cbf080c998c23cbab6863ad56e861cb6948454bc90750c050d1d23014fc00af7fa0"
    "a3a602c9f2da1b13c59e3836138fefd8235d1d6bcfbd67d7472b2e9415421cc72d717ee46ff9c745f7fbc705963bd7af71a7a31f0f758ef37d39d7bd3ec7fd7e",
    "eedf4771effe979d5c229a051dcb4f3411c3ee9d358291266a56b9a543ce8026511bb0d64664a4c232c2b0c426392fc32906ea261ee49d271428d54b36e60cc5"
    "ec55a8b249570f3ed4ebd7ab9ff63b77861e2c4efbffc8e41e4e63b9d33fc5f792fbe93520b4f80d033520881b16925468028be8483281aeb44c44ba97f98422",
    "ea16344c2040d1b45d5540dcb688e64a25f1b9127f375d2af299e23d9029ba1fbe09ab928881206dd8b2cca791a5d8558fab498c3a488912ccdbaa098ba20541"
    "06aa3a342a295b334171275b71c777cfca621d764eb35a0d3a71ade665956d7298ad392bd8d7cbebe724408f61f5ba3d402f8a43ac569066556462a884e815d2",
    "8086ac926645f226b757cfc105ebe98fa07a6850be4f23f67fc0e467f1517c2fbbfd24b99f580379831c1a22e6bd85ed2e8778793bbe0e8ad170342cba8b87a8"
    "55e200572ca0a22ac0a2a58ad5767abe7e2b78907e3786ec873db2fd2c72d7dbf9bbd5af2156bf71f39dec7d2e4d928fc6ffe27302c61b763dde0ce0a3eb91e2",
    "e656d2496e1c1fe7379d684c8886138578249cecd5911fc033a80e8ec9cfea73dce3ff0cb87f581d5f048c4f75a4f8b8ffd777ceff414569fbffe8fe19eafbdd"
    "bf7dcfb5c747a68c589d47e563f71fa7f9e67d3ecd5a8d327c6f47e44b05f2f9e353fc42f32a2307d674e2d60c3c9dd8e76c904e97e523af5e7f9fac2fab4b6b",
    "93e4a331edbe1cd1cb4f339a14cb39da512315ce258db4939e225fbeaaff5f7dc4bad9f7a8b3eaa63832351b43034996f7fa34395f9714d1e018bef723f2ed0c"
    "e897e2a3cf13a3973b61d3eab7dcb70fc244f93a31ed7ebb757f4bcf4732f59a72089f65c4e6c3828563a9e9f1dbd93ef8627d2f04f6bd40f7a55874aeae3f6f",
    "06f2f9e3537ca47955dd13e02be53d4bd9fa83f4ba2c3ff9f563c2fbe1c2973793e4a331edfe1c4b3dc8b664d212d2bb91a6e2200d132c4cd17e78e6cfe3f367"
    "a4cdfc79387f46dacc9f2f978fc6b4fb73291f3dc2ebc956ba9628888fa160ed1eed3c4a5f7d7ffe0b12319192",
    "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 7528U, &nameCaptureInfo);
  return nameCaptureInfo;
}

mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xResult;
  mxArray *xEntryPoints;
  const char * epFieldName[6] = { "Name", "NumberOfInputs", "NumberOfOutputs",
    "ConstantInputs", "FullPath", "TimeStamp" };

  mxArray *xInputs;
  const char * propFieldName[4] = { "Version", "ResolvedFunctions",
    "EntryPoints", "CoverageInfo" };

  xEntryPoints = emlrtCreateStructMatrix(1, 1, 6, epFieldName);
  xInputs = emlrtCreateLogicalMatrix(1, 9);
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString(
    "IndexAndMean_LogIdx"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", emlrtMxCreateDoubleScalar(9.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (2.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath", emlrtMxCreateString(
    "G:\\My Drive\\Articles\\topics\\physio\\Articles Chapters\\Measures\\Autonomic NS (GSR HR)\\HR\\HR webcam\\McDuff Github\\My work\\FacePulse"
    "Rate\\Helper_Funs\\ROI_Means\\Take_Means\\IndexAndMean_LogIdx.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp", emlrtMxCreateDoubleScalar
                (738028.9196875));
  xResult = emlrtCreateStructMatrix(1, 1, 4, propFieldName);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.8.0.1417392 (R2020a) Update 4"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/* End of code generation (_coder_IndexAndMean_LogIdx_info.c) */
