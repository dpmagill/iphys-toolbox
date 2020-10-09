/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ConfirmSkinPresent_SkinDetectReject_api.c
 *
 * Code generation for function '_coder_ConfirmSkinPresent_SkinDetectReject_api'
 *
 */

/* Include files */
#include "_coder_ConfirmSkinPresent_SkinDetectReject_api.h"
#include "ConfirmSkinPresent_SkinDetectReject.h"
#include "ConfirmSkinPresent_SkinDetectReject_data.h"
#include "ConfirmSkinPresent_SkinDetectReject_emxutil.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void ab_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[4]);
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_boolean_T *y);
static int16_T bb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);
static void c_emlrt_marshallIn(const mxArray *RBounded_Uint8, const char_T
  *identifier, emxArray_uint8_T *y);
static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y);
static void e_emlrt_marshallIn(const mxArray *YBounded_Single, const char_T
  *identifier, emxArray_real32_T *y);
static void emlrt_marshallIn(const mxArray *IsSkinMask, const char_T *identifier,
  emxArray_boolean_T *y);
static const mxArray *emlrt_marshallOut(const int32_T u);
static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real32_T *y);
static int32_T g_emlrt_marshallIn(const mxArray *NRows_Matrix, const char_T
  *identifier);
static int32_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void i_emlrt_marshallIn(const mxArray *SkinDetectConfig, const char_T
  *identifier, struct0_T *y);
static void j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct0_T *y);
static boolean_T k_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct1_T *y);
static real_T m_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[3]);
static real32_T o_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void p_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[4]);
static int16_T q_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void r_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_boolean_T *ret);
static void s_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret);
static void t_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real32_T *ret);
static int32_T u_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static boolean_T v_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static real_T w_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static void x_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[3]);
static real32_T y_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);

/* Function Definitions */
static void ab_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[4])
{
  static const int32_T dims[1] = { 4 };

  real_T (*r)[4];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 1U,
    dims);
  r = (real_T (*)[4])emlrtMxGetData(src);
  ret[0] = (*r)[0];
  ret[1] = (*r)[1];
  ret[2] = (*r)[2];
  ret[3] = (*r)[3];
  emlrtDestroyArray(&src);
}

static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_boolean_T *y)
{
  r_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int16_T bb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
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

static void c_emlrt_marshallIn(const mxArray *RBounded_Uint8, const char_T
  *identifier, emxArray_uint8_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(emlrtAlias(RBounded_Uint8), &thisId, y);
  emlrtDestroyArray(&RBounded_Uint8);
}

static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y)
{
  s_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void e_emlrt_marshallIn(const mxArray *YBounded_Single, const char_T
  *identifier, emxArray_real32_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(emlrtAlias(YBounded_Single), &thisId, y);
  emlrtDestroyArray(&YBounded_Single);
}

static void emlrt_marshallIn(const mxArray *IsSkinMask, const char_T *identifier,
  emxArray_boolean_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(IsSkinMask), &thisId, y);
  emlrtDestroyArray(&IsSkinMask);
}

static const mxArray *emlrt_marshallOut(const int32_T u)
{
  const mxArray *y;
  const mxArray *m;
  y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m) = u;
  emlrtAssign(&y, m);
  return y;
}

static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real32_T *y)
{
  t_emlrt_marshallIn(emlrtAlias(u), parentId, y);
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
  y = u_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void i_emlrt_marshallIn(const mxArray *SkinDetectConfig, const char_T
  *identifier, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  j_emlrt_marshallIn(emlrtAlias(SkinDetectConfig), &thisId, y);
  emlrtDestroyArray(&SkinDetectConfig);
}

static void j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[15] = { "ROISkinTF", "Thresholds",
    "ROISkinSkipFrameThreshold", "ROISkin_BoundingBoxGrowthThreshold",
    "ROISkin_BoundingBoxGrowthFactor", "ROISkin_InitialBoundingBoxScale",
    "ROISkinRegionMinSizeFactor", "ROISkinRegionProximityWeight",
    "ROISkinSmoothingWindow", "PartitionColInterval", "PartitionRowInterval",
    "SkinDetectionReadyTF", "ROISkin_BoundingBoxEnlargementFactor",
    "ROISkinSkipFrameThreshold_adjusted", "UseCompiledFunctionsTF" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 15, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "ROISkinTF";
  y->ROISkinTF = k_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 0, "ROISkinTF")), &thisId);
  thisId.fIdentifier = "Thresholds";
  l_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
    "Thresholds")), &thisId, &y->Thresholds);
  thisId.fIdentifier = "ROISkinSkipFrameThreshold";
  y->ROISkinSkipFrameThreshold = h_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 2,
    "ROISkinSkipFrameThreshold")), &thisId);
  thisId.fIdentifier = "ROISkin_BoundingBoxGrowthThreshold";
  y->c_ROISkin_BoundingBoxGrowthThre = h_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 3,
    "ROISkin_BoundingBoxGrowthThreshold")), &thisId);
  thisId.fIdentifier = "ROISkin_BoundingBoxGrowthFactor";
  y->ROISkin_BoundingBoxGrowthFactor = m_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 4,
    "ROISkin_BoundingBoxGrowthFactor")), &thisId);
  thisId.fIdentifier = "ROISkin_InitialBoundingBoxScale";
  y->ROISkin_InitialBoundingBoxScale = m_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 5,
    "ROISkin_InitialBoundingBoxScale")), &thisId);
  thisId.fIdentifier = "ROISkinRegionMinSizeFactor";
  y->ROISkinRegionMinSizeFactor = o_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 6,
    "ROISkinRegionMinSizeFactor")), &thisId);
  thisId.fIdentifier = "ROISkinRegionProximityWeight";
  y->ROISkinRegionProximityWeight = m_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 7,
    "ROISkinRegionProximityWeight")), &thisId);
  thisId.fIdentifier = "ROISkinSmoothingWindow";
  y->ROISkinSmoothingWindow = m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 8, "ROISkinSmoothingWindow")), &thisId);
  thisId.fIdentifier = "PartitionColInterval";
  y->PartitionColInterval = q_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 9, "PartitionColInterval")), &thisId);
  thisId.fIdentifier = "PartitionRowInterval";
  y->PartitionRowInterval = q_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 10, "PartitionRowInterval")), &thisId);
  thisId.fIdentifier = "SkinDetectionReadyTF";
  y->SkinDetectionReadyTF = k_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 11, "SkinDetectionReadyTF")), &thisId);
  thisId.fIdentifier = "ROISkin_BoundingBoxEnlargementFactor";
  y->c_ROISkin_BoundingBoxEnlargemen = m_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 12,
    "ROISkin_BoundingBoxEnlargementFactor")), &thisId);
  thisId.fIdentifier = "ROISkinSkipFrameThreshold_adjusted";
  y->c_ROISkinSkipFrameThreshold_adj = h_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 13,
    "ROISkinSkipFrameThreshold_adjusted")), &thisId);
  thisId.fIdentifier = "UseCompiledFunctionsTF";
  y->UseCompiledFunctionsTF = k_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 14, "UseCompiledFunctionsTF")), &thisId);
  emlrtDestroyArray(&u);
}

static boolean_T k_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  boolean_T y;
  y = v_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct1_T *y)
{
  emlrtMsgIdentifier thisId;
  static const char * fieldNames[16] = { "SetTF", "SkinColorSamples_NThreshold",
    "SkinColorSamples_NThresholdPassedTF", "SkinColorSamples_HighNThreshold",
    "SkinColorSamples_HighNThresholdPassedTF",
    "SkinColorSamples_HighNThresholdIdx", "ColorThreshold",
    "ColorThresholdHighN", "RecentThresholdOpsFrameIdx", "ThresholdOpsInterval",
    "ThresholdOpsRunCurrentFrameTF", "ColorSDThreshold", "RGBProbTheta",
    "YCbCrMeanOfMeans", "YCbCrStdDevOfMeans", "RegionNThreshold" };

  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 16, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "SetTF";
  y->SetTF = k_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 0, "SetTF")), &thisId);
  thisId.fIdentifier = "SkinColorSamples_NThreshold";
  y->SkinColorSamples_NThreshold = m_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
    "SkinColorSamples_NThreshold")), &thisId);
  thisId.fIdentifier = "SkinColorSamples_NThresholdPassedTF";
  y->c_SkinColorSamples_NThresholdPa = k_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 2,
    "SkinColorSamples_NThresholdPassedTF")), &thisId);
  thisId.fIdentifier = "SkinColorSamples_HighNThreshold";
  y->SkinColorSamples_HighNThreshold = m_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 3,
    "SkinColorSamples_HighNThreshold")), &thisId);
  thisId.fIdentifier = "SkinColorSamples_HighNThresholdPassedTF";
  y->b_SkinColorSamples_HighNThresho = k_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 4,
    "SkinColorSamples_HighNThresholdPassedTF")), &thisId);
  thisId.fIdentifier = "SkinColorSamples_HighNThresholdIdx";
  y->c_SkinColorSamples_HighNThresho = h_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 5,
    "SkinColorSamples_HighNThresholdIdx")), &thisId);
  thisId.fIdentifier = "ColorThreshold";
  n_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 6,
    "ColorThreshold")), &thisId, y->ColorThreshold);
  thisId.fIdentifier = "ColorThresholdHighN";
  n_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 7,
    "ColorThresholdHighN")), &thisId, y->ColorThresholdHighN);
  thisId.fIdentifier = "RecentThresholdOpsFrameIdx";
  y->RecentThresholdOpsFrameIdx = h_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 8,
    "RecentThresholdOpsFrameIdx")), &thisId);
  thisId.fIdentifier = "ThresholdOpsInterval";
  y->ThresholdOpsInterval = h_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 9, "ThresholdOpsInterval")), &thisId);
  thisId.fIdentifier = "ThresholdOpsRunCurrentFrameTF";
  y->ThresholdOpsRunCurrentFrameTF = k_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 10,
    "ThresholdOpsRunCurrentFrameTF")), &thisId);
  thisId.fIdentifier = "ColorSDThreshold";
  y->ColorSDThreshold = o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 11, "ColorSDThreshold")), &thisId);
  thisId.fIdentifier = "RGBProbTheta";
  p_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 12,
    "RGBProbTheta")), &thisId, y->RGBProbTheta);
  thisId.fIdentifier = "YCbCrMeanOfMeans";
  n_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 13,
    "YCbCrMeanOfMeans")), &thisId, y->YCbCrMeanOfMeans);
  thisId.fIdentifier = "YCbCrStdDevOfMeans";
  n_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 14,
    "YCbCrStdDevOfMeans")), &thisId, y->YCbCrStdDevOfMeans);
  thisId.fIdentifier = "RegionNThreshold";
  y->RegionNThreshold = o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 15, "RegionNThreshold")), &thisId);
  emlrtDestroyArray(&u);
}

static real_T m_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  real_T y;
  y = w_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[3])
{
  x_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real32_T o_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  real32_T y;
  y = y_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void p_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[4])
{
  ab_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int16_T q_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  int16_T y;
  y = bb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void r_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static void s_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static void t_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static int32_T u_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static boolean_T v_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static real_T w_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 0U,
    &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void x_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static real32_T y_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId)
{
  real32_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 0U,
    &dims);
  ret = *(real32_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void ConfirmSkinPresent_SkinDetectReject_api(const mxArray * const prhs[10],
  int32_T nlhs, const mxArray *plhs[1])
{
  emxArray_boolean_T *IsSkinMask;
  emxArray_uint8_T *RBounded_Uint8;
  emxArray_uint8_T *GBounded_Uint8;
  emxArray_uint8_T *BBounded_Uint8;
  emxArray_real32_T *YBounded_Single;
  emxArray_real32_T *CbBounded_Single;
  emxArray_real32_T *CrBounded_Single;
  const mxArray *prhs_copy_idx_0;
  int32_T NRows_Matrix;
  int32_T NCols_Matrix;
  struct0_T SkinDetectConfig;
  (void)nlhs;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_boolean_T(&IsSkinMask, 2, true);
  emxInit_uint8_T(&RBounded_Uint8, 2, true);
  emxInit_uint8_T(&GBounded_Uint8, 2, true);
  emxInit_uint8_T(&BBounded_Uint8, 2, true);
  emxInit_real32_T(&YBounded_Single, 2, true);
  emxInit_real32_T(&CbBounded_Single, 2, true);
  emxInit_real32_T(&CrBounded_Single, 2, true);
  prhs_copy_idx_0 = emlrtProtectR2012b(prhs[0], 0, false, -1);

  /* Marshall function inputs */
  IsSkinMask->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs_copy_idx_0), "IsSkinMask", IsSkinMask);
  RBounded_Uint8->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[1]), "RBounded_Uint8", RBounded_Uint8);
  GBounded_Uint8->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[2]), "GBounded_Uint8", GBounded_Uint8);
  BBounded_Uint8->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[3]), "BBounded_Uint8", BBounded_Uint8);
  YBounded_Single->canFreeData = false;
  e_emlrt_marshallIn(emlrtAlias(prhs[4]), "YBounded_Single", YBounded_Single);
  CbBounded_Single->canFreeData = false;
  e_emlrt_marshallIn(emlrtAlias(prhs[5]), "CbBounded_Single", CbBounded_Single);
  CrBounded_Single->canFreeData = false;
  e_emlrt_marshallIn(emlrtAlias(prhs[6]), "CrBounded_Single", CrBounded_Single);
  NRows_Matrix = g_emlrt_marshallIn(emlrtAliasP(prhs[7]), "NRows_Matrix");
  NCols_Matrix = g_emlrt_marshallIn(emlrtAliasP(prhs[8]), "NCols_Matrix");
  i_emlrt_marshallIn(emlrtAliasP(prhs[9]), "SkinDetectConfig", &SkinDetectConfig);

  /* Invoke the target function */
  NRows_Matrix = ConfirmSkinPresent_SkinDetectReject(IsSkinMask, RBounded_Uint8,
    GBounded_Uint8, BBounded_Uint8, YBounded_Single, CbBounded_Single,
    CrBounded_Single, NRows_Matrix, NCols_Matrix, &SkinDetectConfig);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(NRows_Matrix);
  emxFree_real32_T(&CrBounded_Single);
  emxFree_real32_T(&CbBounded_Single);
  emxFree_real32_T(&YBounded_Single);
  emxFree_uint8_T(&BBounded_Uint8);
  emxFree_uint8_T(&GBounded_Uint8);
  emxFree_uint8_T(&RBounded_Uint8);
  emxFree_boolean_T(&IsSkinMask);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_ConfirmSkinPresent_SkinDetectReject_api.c) */
