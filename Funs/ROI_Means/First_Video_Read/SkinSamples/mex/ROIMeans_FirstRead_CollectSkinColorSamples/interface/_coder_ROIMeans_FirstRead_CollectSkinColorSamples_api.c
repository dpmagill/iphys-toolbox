/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ROIMeans_FirstRead_CollectSkinColorSamples_api.c
 *
 * Code generation for function '_coder_ROIMeans_FirstRead_CollectSkinColorSamples_api'
 *
 */

/* Include files */
#include "_coder_ROIMeans_FirstRead_CollectSkinColorSamples_api.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_data.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_emxutil.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void ab_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[8]);
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real32_T *y);
static const mxArray *b_emlrt_marshallOut(const real32_T u[3]);
static void bb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[3]);
static void c_emlrt_marshallIn(const mxArray *RUint8, const char_T *identifier,
  emxArray_uint8_T *y);
static const mxArray *c_emlrt_marshallOut(const real32_T u[11]);
static int16_T cb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);
static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y);
static uint8_T db_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);
static void e_emlrt_marshallIn(const mxArray *IsSkinMask_LocalRange, const
  char_T *identifier, emxArray_boolean_T *y);
static void emlrt_marshallIn(const mxArray *YSingle, const char_T *identifier,
  emxArray_real32_T *y);
static const mxArray *emlrt_marshallOut(const real_T u[3]);
static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_boolean_T *y);
static int32_T g_emlrt_marshallIn(const mxArray *NRows_Matrix, const char_T
  *identifier);
static int32_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void i_emlrt_marshallIn(const mxArray *SkinSegmentConfig_Args, const
  char_T *identifier, struct0_T *y);
static void j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct0_T *y);
static boolean_T k_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[7]);
static void m_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[2]);
static void n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[8]);
static void o_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[3]);
static int16_T p_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static uint8_T q_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static boolean_T r_emlrt_marshallIn(const mxArray *UseCompiledFunctionsTF, const
  char_T *identifier);
static void s_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real32_T *ret);
static void t_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret);
static void u_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_boolean_T *ret);
static int32_T v_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static boolean_T w_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static void x_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[7]);
static void y_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[2]);

/* Function Definitions */
static void ab_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[8])
{
  static const int32_T dims[2] = { 1, 8 };

  real32_T (*r)[8];
  int32_T i;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 2U,
    dims);
  r = (real32_T (*)[8])emlrtMxGetData(src);
  for (i = 0; i < 8; i++) {
    ret[i] = (*r)[i];
  }

  emlrtDestroyArray(&src);
}

static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real32_T *y)
{
  s_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *b_emlrt_marshallOut(const real32_T u[3])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 0, 0 };

  static const int32_T iv1[2] = { 1, 3 };

  y = NULL;
  m = emlrtCreateNumericArray(2, &iv[0], mxSINGLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, iv1, 2);
  emlrtAssign(&y, m);
  return y;
}

static void bb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[3])
{
  static const int32_T dims[2] = { 1, 3 };

  real32_T (*r)[3];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 2U,
    dims);
  r = (real32_T (*)[3])emlrtMxGetData(src);
  ret[0] = (*r)[0];
  ret[1] = (*r)[1];
  ret[2] = (*r)[2];
  emlrtDestroyArray(&src);
}

static void c_emlrt_marshallIn(const mxArray *RUint8, const char_T *identifier,
  emxArray_uint8_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(emlrtAlias(RUint8), &thisId, y);
  emlrtDestroyArray(&RUint8);
}

static const mxArray *c_emlrt_marshallOut(const real32_T u[11])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 0, 0 };

  static const int32_T iv1[2] = { 1, 11 };

  y = NULL;
  m = emlrtCreateNumericArray(2, &iv[0], mxSINGLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, iv1, 2);
  emlrtAssign(&y, m);
  return y;
}

static int16_T cb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId)
{
  int16_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int16", false, 0U,
    &dims);
  ret = *(int16_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y)
{
  t_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static uint8_T db_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId)
{
  uint8_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint8", false, 0U,
    &dims);
  ret = *(uint8_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void e_emlrt_marshallIn(const mxArray *IsSkinMask_LocalRange, const
  char_T *identifier, emxArray_boolean_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(emlrtAlias(IsSkinMask_LocalRange), &thisId, y);
  emlrtDestroyArray(&IsSkinMask_LocalRange);
}

static void emlrt_marshallIn(const mxArray *YSingle, const char_T *identifier,
  emxArray_real32_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(YSingle), &thisId, y);
  emlrtDestroyArray(&YSingle);
}

static const mxArray *emlrt_marshallOut(const real_T u[3])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 0, 0 };

  static const int32_T iv1[2] = { 1, 3 };

  y = NULL;
  m = emlrtCreateNumericArray(2, &iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, iv1, 2);
  emlrtAssign(&y, m);
  return y;
}

static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_boolean_T *y)
{
  u_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int32_T g_emlrt_marshallIn(const mxArray *NRows_Matrix, const char_T
  *identifier)
{
  int32_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = h_emlrt_marshallIn(emlrtAlias(NRows_Matrix), &thisId);
  emlrtDestroyArray(&NRows_Matrix);
  return y;
}

static int32_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  int32_T y;
  y = v_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void i_emlrt_marshallIn(const mxArray *SkinSegmentConfig_Args, const
  char_T *identifier, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  j_emlrt_marshallIn(emlrtAlias(SkinSegmentConfig_Args), &thisId, y);
  emlrtDestroyArray(&SkinSegmentConfig_Args);
}

static void j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[11] = { "SkinColorSamples_NThresholdPassedTF",
    "YCbCrThresholdsGeneric", "HSThresholdsGeneric", "YCbCrThresholdsTailored",
    "YCbCrThresholdsTailored_Sev", "HSThresholdsTailored",
    "HSThresholdsTailored_Sev", "RangeSEWidth", "RangeThreshold",
    "MorphCloseSEMediumWidth_Tuned", "MorphCloseSELargeWidth_Tuned" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 11, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "SkinColorSamples_NThresholdPassedTF";
  y->c_SkinColorSamples_NThresholdPa = k_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 0,
    "SkinColorSamples_NThresholdPassedTF")), &thisId);
  thisId.fIdentifier = "YCbCrThresholdsGeneric";
  l_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
    "YCbCrThresholdsGeneric")), &thisId, y->YCbCrThresholdsGeneric);
  thisId.fIdentifier = "HSThresholdsGeneric";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 2,
    "HSThresholdsGeneric")), &thisId, y->HSThresholdsGeneric);
  thisId.fIdentifier = "YCbCrThresholdsTailored";
  n_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 3,
    "YCbCrThresholdsTailored")), &thisId, y->YCbCrThresholdsTailored);
  thisId.fIdentifier = "YCbCrThresholdsTailored_Sev";
  n_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 4,
    "YCbCrThresholdsTailored_Sev")), &thisId, y->YCbCrThresholdsTailored_Sev);
  thisId.fIdentifier = "HSThresholdsTailored";
  o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 5,
    "HSThresholdsTailored")), &thisId, y->HSThresholdsTailored);
  thisId.fIdentifier = "HSThresholdsTailored_Sev";
  o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 6,
    "HSThresholdsTailored_Sev")), &thisId, y->HSThresholdsTailored_Sev);
  thisId.fIdentifier = "RangeSEWidth";
  y->RangeSEWidth = p_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 7, "RangeSEWidth")), &thisId);
  thisId.fIdentifier = "RangeThreshold";
  y->RangeThreshold = q_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 8, "RangeThreshold")), &thisId);
  thisId.fIdentifier = "MorphCloseSEMediumWidth_Tuned";
  y->MorphCloseSEMediumWidth_Tuned = p_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 9,
    "MorphCloseSEMediumWidth_Tuned")), &thisId);
  thisId.fIdentifier = "MorphCloseSELargeWidth_Tuned";
  y->MorphCloseSELargeWidth_Tuned = p_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 10,
    "MorphCloseSELargeWidth_Tuned")), &thisId);
  emlrtDestroyArray(&u);
}

static boolean_T k_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  boolean_T y;
  y = w_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[7])
{
  x_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void m_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[2])
{
  y_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[8])
{
  ab_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void o_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[3])
{
  bb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int16_T p_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  int16_T y;
  y = cb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static uint8_T q_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  uint8_T y;
  y = db_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static boolean_T r_emlrt_marshallIn(const mxArray *UseCompiledFunctionsTF, const
  char_T *identifier)
{
  boolean_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = k_emlrt_marshallIn(emlrtAlias(UseCompiledFunctionsTF), &thisId);
  emlrtDestroyArray(&UseCompiledFunctionsTF);
  return y;
}

static void s_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real32_T *ret)
{
  static const int32_T dims[2] = { -1, -1 };

  const boolean_T bv[2] = { true, true };

  int32_T iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 2U,
    dims, &bv[0], iv);
  ret->allocatedSize = iv[0] * iv[1];
  i = ret->size[0] * ret->size[1];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  emxEnsureCapacity_real32_T(ret, i);
  ret->data = (real32_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void t_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret)
{
  static const int32_T dims[2] = { -1, -1 };

  const boolean_T bv[2] = { true, true };

  int32_T iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint8", false, 2U,
    dims, &bv[0], iv);
  ret->allocatedSize = iv[0] * iv[1];
  i = ret->size[0] * ret->size[1];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  emxEnsureCapacity_uint8_T(ret, i);
  ret->data = (uint8_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void u_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_boolean_T *ret)
{
  static const int32_T dims[2] = { -1, -1 };

  const boolean_T bv[2] = { true, true };

  int32_T iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "logical", false, 2U,
    dims, &bv[0], iv);
  ret->allocatedSize = iv[0] * iv[1];
  i = ret->size[0] * ret->size[1];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  emxEnsureCapacity_boolean_T(ret, i);
  ret->data = (boolean_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static int32_T v_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId)
{
  int32_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int32", false, 0U,
    &dims);
  ret = *(int32_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static boolean_T w_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId)
{
  boolean_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "logical", false, 0U,
    &dims);
  ret = *emlrtMxGetLogicals(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void x_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[7])
{
  static const int32_T dims[2] = { 1, 7 };

  real32_T (*r)[7];
  int32_T i;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 2U,
    dims);
  r = (real32_T (*)[7])emlrtMxGetData(src);
  for (i = 0; i < 7; i++) {
    ret[i] = (*r)[i];
  }

  emlrtDestroyArray(&src);
}

static void y_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[2])
{
  static const int32_T dims[2] = { 1, 2 };

  real32_T (*r)[2];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 2U,
    dims);
  r = (real32_T (*)[2])emlrtMxGetData(src);
  ret[0] = (*r)[0];
  ret[1] = (*r)[1];
  emlrtDestroyArray(&src);
}

void ROIMeans_FirstRead_CollectSkinColorSamples_api(const mxArray * const prhs
  [13], int32_T nlhs, const mxArray *plhs[3])
{
  real_T (*ithPrimaryROIRGBMeans)[3];
  real32_T (*ithPrimaryROIYCbCrMeans)[3];
  real32_T (*ithPrimaryROIYCbCrHSMinsMaxs)[11];
  emxArray_real32_T *YSingle;
  emxArray_real32_T *CbSingle;
  emxArray_real32_T *CrSingle;
  emxArray_uint8_T *RUint8;
  emxArray_uint8_T *GUint8;
  emxArray_uint8_T *BUint8;
  emxArray_real32_T *HSingle;
  emxArray_real32_T *SSingle;
  emxArray_boolean_T *IsSkinMask_LocalRange;
  int32_T NRows_Matrix;
  int32_T NCols_Matrix;
  struct0_T SkinSegmentConfig_Args;
  boolean_T UseCompiledFunctionsTF;
  ithPrimaryROIRGBMeans = (real_T (*)[3])mxMalloc(sizeof(real_T [3]));
  ithPrimaryROIYCbCrMeans = (real32_T (*)[3])mxMalloc(sizeof(real32_T [3]));
  ithPrimaryROIYCbCrHSMinsMaxs = (real32_T (*)[11])mxMalloc(sizeof(real32_T [11]));
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_real32_T(emlrtRootTLSGlobal, &YSingle, 2, true);
  emxInit_real32_T(emlrtRootTLSGlobal, &CbSingle, 2, true);
  emxInit_real32_T(emlrtRootTLSGlobal, &CrSingle, 2, true);
  emxInit_uint8_T(emlrtRootTLSGlobal, &RUint8, 2, true);
  emxInit_uint8_T(emlrtRootTLSGlobal, &GUint8, 2, true);
  emxInit_uint8_T(emlrtRootTLSGlobal, &BUint8, 2, true);
  emxInit_real32_T(emlrtRootTLSGlobal, &HSingle, 2, true);
  emxInit_real32_T(emlrtRootTLSGlobal, &SSingle, 2, true);
  emxInit_boolean_T(&IsSkinMask_LocalRange, 2, true);

  /* Marshall function inputs */
  YSingle->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs[0]), "YSingle", YSingle);
  CbSingle->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs[1]), "CbSingle", CbSingle);
  CrSingle->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs[2]), "CrSingle", CrSingle);
  RUint8->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[3]), "RUint8", RUint8);
  GUint8->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[4]), "GUint8", GUint8);
  BUint8->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[5]), "BUint8", BUint8);
  HSingle->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs[6]), "HSingle", HSingle);
  SSingle->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs[7]), "SSingle", SSingle);
  IsSkinMask_LocalRange->canFreeData = false;
  e_emlrt_marshallIn(emlrtAlias(prhs[8]), "IsSkinMask_LocalRange",
                     IsSkinMask_LocalRange);
  NRows_Matrix = g_emlrt_marshallIn(emlrtAliasP(prhs[9]), "NRows_Matrix");
  NCols_Matrix = g_emlrt_marshallIn(emlrtAliasP(prhs[10]), "NCols_Matrix");
  i_emlrt_marshallIn(emlrtAliasP(prhs[11]), "SkinSegmentConfig_Args",
                     &SkinSegmentConfig_Args);
  UseCompiledFunctionsTF = r_emlrt_marshallIn(emlrtAliasP(prhs[12]),
    "UseCompiledFunctionsTF");

  /* Invoke the target function */
  ROIMeans_FirstRead_CollectSkinColorSamples(YSingle, CbSingle, CrSingle, RUint8,
    GUint8, BUint8, HSingle, SSingle, IsSkinMask_LocalRange, NRows_Matrix,
    NCols_Matrix, &SkinSegmentConfig_Args, UseCompiledFunctionsTF,
    *ithPrimaryROIRGBMeans, *ithPrimaryROIYCbCrMeans,
    *ithPrimaryROIYCbCrHSMinsMaxs);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*ithPrimaryROIRGBMeans);
  emxFree_boolean_T(&IsSkinMask_LocalRange);
  emxFree_real32_T(&SSingle);
  emxFree_real32_T(&HSingle);
  emxFree_uint8_T(&BUint8);
  emxFree_uint8_T(&GUint8);
  emxFree_uint8_T(&RUint8);
  emxFree_real32_T(&CrSingle);
  emxFree_real32_T(&CbSingle);
  emxFree_real32_T(&YSingle);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(*ithPrimaryROIYCbCrMeans);
  }

  if (nlhs > 2) {
    plhs[2] = c_emlrt_marshallOut(*ithPrimaryROIYCbCrHSMinsMaxs);
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_ROIMeans_FirstRead_CollectSkinColorSamples_api.c) */
