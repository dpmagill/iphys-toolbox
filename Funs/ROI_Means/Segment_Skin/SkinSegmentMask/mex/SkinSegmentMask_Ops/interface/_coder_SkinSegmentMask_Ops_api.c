/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_SkinSegmentMask_Ops_api.c
 *
 * Code generation for function '_coder_SkinSegmentMask_Ops_api'
 *
 */

/* Include files */
#include "_coder_SkinSegmentMask_Ops_api.h"
#include "SkinSegmentMask_Ops.h"
#include "SkinSegmentMask_Ops_data.h"
#include "SkinSegmentMask_Ops_emxutil.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void ab_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[8]);
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y);
static const mxArray *b_emlrt_marshallOut(const uint32_T u_data[], const int32_T
  u_size[1]);
static void bb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[3]);
static void c_emlrt_marshallIn(const mxArray *YSingle, const char_T *identifier,
  emxArray_real32_T *y);
static const mxArray *c_emlrt_marshallOut(const emxArray_real32_T *u);
static int16_T cb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);
static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real32_T *y);
static void d_emlrt_marshallOut(const emxArray_boolean_T *u, const mxArray *y);
static uint8_T db_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);
static void e_emlrt_marshallIn(const mxArray *IsSkinMask_Range, const char_T
  *identifier, emxArray_boolean_T *y);
static void emlrt_marshallIn(const mxArray *RBounded_Uint8, const char_T
  *identifier, emxArray_uint8_T *y);
static const mxArray *emlrt_marshallOut(const emxArray_boolean_T *u);
static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_boolean_T *y);
static int32_T g_emlrt_marshallIn(const mxArray *NRows_Matrix, const char_T
  *identifier);
static int32_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static boolean_T i_emlrt_marshallIn(const mxArray *CountTrueTF, const char_T
  *identifier);
static boolean_T j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void k_emlrt_marshallIn(const mxArray *SkinSegmentArgs, const char_T
  *identifier, struct0_T *y);
static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct0_T *y);
static void m_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[7]);
static void n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[2]);
static void o_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[8]);
static void p_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[3]);
static int16_T q_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static uint8_T r_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void s_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret);
static void t_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real32_T *ret);
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
  *parentId, emxArray_uint8_T *y)
{
  s_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *b_emlrt_marshallOut(const uint32_T u_data[], const int32_T
  u_size[1])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[1] = { 0 };

  y = NULL;
  m = emlrtCreateNumericArray(1, &iv[0], mxUINT32_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m, u_size, 1);
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

static void c_emlrt_marshallIn(const mxArray *YSingle, const char_T *identifier,
  emxArray_real32_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(emlrtAlias(YSingle), &thisId, y);
  emlrtDestroyArray(&YSingle);
}

static const mxArray *c_emlrt_marshallOut(const emxArray_real32_T *u)
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 0, 0 };

  y = NULL;
  m = emlrtCreateNumericArray(2, &iv[0], mxSINGLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &u->data[0]);
  emlrtSetDimensions((mxArray *)m, u->size, 2);
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
  *parentId, emxArray_real32_T *y)
{
  t_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void d_emlrt_marshallOut(const emxArray_boolean_T *u, const mxArray *y)
{
  emlrtMxSetData((mxArray *)y, &u->data[0]);
  emlrtSetDimensions((mxArray *)y, u->size, 2);
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

static void e_emlrt_marshallIn(const mxArray *IsSkinMask_Range, const char_T
  *identifier, emxArray_boolean_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(emlrtAlias(IsSkinMask_Range), &thisId, y);
  emlrtDestroyArray(&IsSkinMask_Range);
}

static void emlrt_marshallIn(const mxArray *RBounded_Uint8, const char_T
  *identifier, emxArray_uint8_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(RBounded_Uint8), &thisId, y);
  emlrtDestroyArray(&RBounded_Uint8);
}

static const mxArray *emlrt_marshallOut(const emxArray_boolean_T *u)
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 0, 0 };

  y = NULL;
  m = emlrtCreateLogicalArray(2, &iv[0]);
  emlrtMxSetData((mxArray *)m, &u->data[0]);
  emlrtSetDimensions((mxArray *)m, u->size, 2);
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

static boolean_T i_emlrt_marshallIn(const mxArray *CountTrueTF, const char_T
  *identifier)
{
  boolean_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = j_emlrt_marshallIn(emlrtAlias(CountTrueTF), &thisId);
  emlrtDestroyArray(&CountTrueTF);
  return y;
}

static boolean_T j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  boolean_T y;
  y = w_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void k_emlrt_marshallIn(const mxArray *SkinSegmentArgs, const char_T
  *identifier, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  l_emlrt_marshallIn(emlrtAlias(SkinSegmentArgs), &thisId, y);
  emlrtDestroyArray(&SkinSegmentArgs);
}

static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
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
  y->c_SkinColorSamples_NThresholdPa = j_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 0,
    "SkinColorSamples_NThresholdPassedTF")), &thisId);
  thisId.fIdentifier = "YCbCrThresholdsGeneric";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
    "YCbCrThresholdsGeneric")), &thisId, y->YCbCrThresholdsGeneric);
  thisId.fIdentifier = "HSThresholdsGeneric";
  n_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 2,
    "HSThresholdsGeneric")), &thisId, y->HSThresholdsGeneric);
  thisId.fIdentifier = "YCbCrThresholdsTailored";
  o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 3,
    "YCbCrThresholdsTailored")), &thisId, y->YCbCrThresholdsTailored);
  thisId.fIdentifier = "YCbCrThresholdsTailored_Sev";
  o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 4,
    "YCbCrThresholdsTailored_Sev")), &thisId, y->YCbCrThresholdsTailored_Sev);
  thisId.fIdentifier = "HSThresholdsTailored";
  p_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 5,
    "HSThresholdsTailored")), &thisId, y->HSThresholdsTailored);
  thisId.fIdentifier = "HSThresholdsTailored_Sev";
  p_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 6,
    "HSThresholdsTailored_Sev")), &thisId, y->HSThresholdsTailored_Sev);
  thisId.fIdentifier = "RangeSEWidth";
  y->RangeSEWidth = q_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 7, "RangeSEWidth")), &thisId);
  thisId.fIdentifier = "RangeThreshold";
  y->RangeThreshold = r_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 8, "RangeThreshold")), &thisId);
  thisId.fIdentifier = "MorphCloseSEMediumWidth_Tuned";
  y->MorphCloseSEMediumWidth_Tuned = q_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 9,
    "MorphCloseSEMediumWidth_Tuned")), &thisId);
  thisId.fIdentifier = "MorphCloseSELargeWidth_Tuned";
  y->MorphCloseSELargeWidth_Tuned = q_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 10,
    "MorphCloseSELargeWidth_Tuned")), &thisId);
  emlrtDestroyArray(&u);
}

static void m_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[7])
{
  x_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[2])
{
  y_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void o_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[8])
{
  ab_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void p_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[3])
{
  bb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int16_T q_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  int16_T y;
  y = cb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static uint8_T r_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  uint8_T y;
  y = db_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void s_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret)
{
  static const int32_T dims[2] = { -1, -1 };

  const boolean_T b_bv[2] = { true, true };

  int32_T iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint8", false, 2U,
    dims, &b_bv[0], iv);
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

  const boolean_T b_bv[2] = { true, true };

  int32_T iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 2U,
    dims, &b_bv[0], iv);
  ret->allocatedSize = iv[0] * iv[1];
  i = ret->size[0] * ret->size[1];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  emxEnsureCapacity_real32_T(ret, i);
  ret->data = (real32_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void u_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_boolean_T *ret)
{
  static const int32_T dims[2] = { -1, -1 };

  const boolean_T b_bv[2] = { true, true };

  int32_T iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "logical", false, 2U,
    dims, &b_bv[0], iv);
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

void SkinSegmentMask_Ops_api(const mxArray * const prhs[21], int32_T nlhs, const
  mxArray *plhs[8])
{
  uint32_T (*TrueCount_data)[1];
  emxArray_uint8_T *RBounded_Uint8;
  emxArray_uint8_T *GBounded_Uint8;
  emxArray_uint8_T *BBounded_Uint8;
  emxArray_real32_T *YSingle;
  emxArray_real32_T *CbSingle;
  emxArray_real32_T *CrSingle;
  emxArray_real32_T *HSingle;
  emxArray_real32_T *SSingle;
  emxArray_boolean_T *IsSkinMask_Range;
  emxArray_boolean_T *IsSkinMask;
  emxArray_real32_T *YBounded_Single;
  emxArray_real32_T *CbBounded_Single;
  emxArray_real32_T *CrBounded_Single;
  emxArray_real32_T *HBounded_Single;
  emxArray_real32_T *SBounded_Single;
  const mxArray *prhs_copy_idx_8;
  int32_T NRows_Matrix;
  int32_T NCols_Matrix;
  boolean_T CountTrueTF;
  boolean_T TailoredThresholdsTF;
  boolean_T ReturnYTF;
  boolean_T ReturnCbCrTF;
  boolean_T ReturnHSTF;
  boolean_T TailoredThresholdsSevereTF;
  boolean_T MorphCloseSevereTF;
  int32_T XOffset;
  int32_T YOffset;
  struct0_T SkinSegmentArgs;
  int32_T TrueCount_size[1];
  TrueCount_data = (uint32_T (*)[1])mxMalloc(sizeof(uint32_T [1]));
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint8_T(emlrtRootTLSGlobal, &RBounded_Uint8, 2, true);
  emxInit_uint8_T(emlrtRootTLSGlobal, &GBounded_Uint8, 2, true);
  emxInit_uint8_T(emlrtRootTLSGlobal, &BBounded_Uint8, 2, true);
  emxInit_real32_T(&YSingle, 2, true);
  emxInit_real32_T(&CbSingle, 2, true);
  emxInit_real32_T(&CrSingle, 2, true);
  emxInit_real32_T(&HSingle, 2, true);
  emxInit_real32_T(&SSingle, 2, true);
  emxInit_boolean_T(&IsSkinMask_Range, 2, true);
  emxInit_boolean_T(&IsSkinMask, 2, true);
  emxInit_real32_T(&YBounded_Single, 2, true);
  emxInit_real32_T(&CbBounded_Single, 2, true);
  emxInit_real32_T(&CrBounded_Single, 2, true);
  emxInit_real32_T(&HBounded_Single, 2, true);
  emxInit_real32_T(&SBounded_Single, 2, true);
  prhs_copy_idx_8 = emlrtProtectR2012b(prhs[8], 8, true, -1);

  /* Marshall function inputs */
  RBounded_Uint8->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs[0]), "RBounded_Uint8", RBounded_Uint8);
  GBounded_Uint8->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs[1]), "GBounded_Uint8", GBounded_Uint8);
  BBounded_Uint8->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs[2]), "BBounded_Uint8", BBounded_Uint8);
  YSingle->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[3]), "YSingle", YSingle);
  CbSingle->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[4]), "CbSingle", CbSingle);
  CrSingle->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[5]), "CrSingle", CrSingle);
  HSingle->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[6]), "HSingle", HSingle);
  SSingle->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[7]), "SSingle", SSingle);
  IsSkinMask_Range->canFreeData = false;
  e_emlrt_marshallIn(emlrtAlias(prhs_copy_idx_8), "IsSkinMask_Range",
                     IsSkinMask_Range);
  NRows_Matrix = g_emlrt_marshallIn(emlrtAliasP(prhs[9]), "NRows_Matrix");
  NCols_Matrix = g_emlrt_marshallIn(emlrtAliasP(prhs[10]), "NCols_Matrix");
  CountTrueTF = i_emlrt_marshallIn(emlrtAliasP(prhs[11]), "CountTrueTF");
  TailoredThresholdsTF = i_emlrt_marshallIn(emlrtAliasP(prhs[12]),
    "TailoredThresholdsTF");
  ReturnYTF = i_emlrt_marshallIn(emlrtAliasP(prhs[13]), "ReturnYTF");
  ReturnCbCrTF = i_emlrt_marshallIn(emlrtAliasP(prhs[14]), "ReturnCbCrTF");
  ReturnHSTF = i_emlrt_marshallIn(emlrtAliasP(prhs[15]), "ReturnHSTF");
  TailoredThresholdsSevereTF = i_emlrt_marshallIn(emlrtAliasP(prhs[16]),
    "TailoredThresholdsSevereTF");
  MorphCloseSevereTF = i_emlrt_marshallIn(emlrtAliasP(prhs[17]),
    "MorphCloseSevereTF");
  XOffset = g_emlrt_marshallIn(emlrtAliasP(prhs[18]), "XOffset");
  YOffset = g_emlrt_marshallIn(emlrtAliasP(prhs[19]), "YOffset");
  k_emlrt_marshallIn(emlrtAliasP(prhs[20]), "SkinSegmentArgs", &SkinSegmentArgs);

  /* Invoke the target function */
  SkinSegmentMask_Ops(RBounded_Uint8, GBounded_Uint8, BBounded_Uint8, YSingle,
                      CbSingle, CrSingle, HSingle, SSingle, IsSkinMask_Range,
                      NRows_Matrix, NCols_Matrix, CountTrueTF,
                      TailoredThresholdsTF, ReturnYTF, ReturnCbCrTF, ReturnHSTF,
                      TailoredThresholdsSevereTF, MorphCloseSevereTF, XOffset,
                      YOffset, &SkinSegmentArgs, IsSkinMask, *TrueCount_data,
                      TrueCount_size, YBounded_Single, CbBounded_Single,
                      CrBounded_Single, HBounded_Single, SBounded_Single);

  /* Marshall function outputs */
  IsSkinMask->canFreeData = false;
  plhs[0] = emlrt_marshallOut(IsSkinMask);
  emxFree_boolean_T(&IsSkinMask);
  emxFree_real32_T(&SSingle);
  emxFree_real32_T(&HSingle);
  emxFree_real32_T(&CrSingle);
  emxFree_real32_T(&CbSingle);
  emxFree_real32_T(&YSingle);
  emxFree_uint8_T(&BBounded_Uint8);
  emxFree_uint8_T(&GBounded_Uint8);
  emxFree_uint8_T(&RBounded_Uint8);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(*TrueCount_data, TrueCount_size);
  }

  if (nlhs > 2) {
    YBounded_Single->canFreeData = false;
    plhs[2] = c_emlrt_marshallOut(YBounded_Single);
  }

  emxFree_real32_T(&YBounded_Single);
  if (nlhs > 3) {
    CbBounded_Single->canFreeData = false;
    plhs[3] = c_emlrt_marshallOut(CbBounded_Single);
  }

  emxFree_real32_T(&CbBounded_Single);
  if (nlhs > 4) {
    CrBounded_Single->canFreeData = false;
    plhs[4] = c_emlrt_marshallOut(CrBounded_Single);
  }

  emxFree_real32_T(&CrBounded_Single);
  if (nlhs > 5) {
    HBounded_Single->canFreeData = false;
    plhs[5] = c_emlrt_marshallOut(HBounded_Single);
  }

  emxFree_real32_T(&HBounded_Single);
  if (nlhs > 6) {
    SBounded_Single->canFreeData = false;
    plhs[6] = c_emlrt_marshallOut(SBounded_Single);
  }

  emxFree_real32_T(&SBounded_Single);
  if (nlhs > 7) {
    IsSkinMask_Range->canFreeData = false;
    d_emlrt_marshallOut(IsSkinMask_Range, prhs_copy_idx_8);
    plhs[7] = prhs_copy_idx_8;
  }

  emxFree_boolean_T(&IsSkinMask_Range);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_SkinSegmentMask_Ops_api.c) */
