/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_IndexAndMean_LogIdx_api.c
 *
 * Code generation for function '_coder_IndexAndMean_LogIdx_api'
 *
 */

/* Include files */
#include "_coder_IndexAndMean_LogIdx_api.h"
#include "IndexAndMean_LogIdx.h"
#include "IndexAndMean_LogIdx_data.h"
#include "IndexAndMean_LogIdx_emxutil.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y);
static const mxArray *b_emlrt_marshallOut(const real_T u);
static void c_emlrt_marshallIn(const mxArray *Luminance_Single, const char_T
  *identifier, emxArray_real32_T *y);
static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real32_T *y);
static void e_emlrt_marshallIn(const mxArray *LogIdx, const char_T *identifier,
  emxArray_boolean_T *y);
static void emlrt_marshallIn(const mxArray *R_Uint8, const char_T *identifier,
  emxArray_uint8_T *y);
static const mxArray *emlrt_marshallOut(const real_T u[3]);
static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_boolean_T *y);
static int32_T g_emlrt_marshallIn(const mxArray *NRows, const char_T *identifier);
static int32_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static uint32_T i_emlrt_marshallIn(const mxArray *TrueCount, const char_T
  *identifier);
static uint32_T j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static boolean_T k_emlrt_marshallIn(const mxArray *TakeLuminanceMeanTF, const
  char_T *identifier);
static boolean_T l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret);
static void n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real32_T *ret);
static void o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_boolean_T *ret);
static int32_T p_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static uint32_T q_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);
static boolean_T r_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);

/* Function Definitions */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y)
{
  m_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *b_emlrt_marshallOut(const real_T u)
{
  const mxArray *y;
  const mxArray *m;
  y = NULL;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

static void c_emlrt_marshallIn(const mxArray *Luminance_Single, const char_T
  *identifier, emxArray_real32_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(emlrtAlias(Luminance_Single), &thisId, y);
  emlrtDestroyArray(&Luminance_Single);
}

static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real32_T *y)
{
  n_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void e_emlrt_marshallIn(const mxArray *LogIdx, const char_T *identifier,
  emxArray_boolean_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(emlrtAlias(LogIdx), &thisId, y);
  emlrtDestroyArray(&LogIdx);
}

static void emlrt_marshallIn(const mxArray *R_Uint8, const char_T *identifier,
  emxArray_uint8_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(R_Uint8), &thisId, y);
  emlrtDestroyArray(&R_Uint8);
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
  o_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int32_T g_emlrt_marshallIn(const mxArray *NRows, const char_T *identifier)
{
  int32_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = h_emlrt_marshallIn(emlrtAlias(NRows), &thisId);
  emlrtDestroyArray(&NRows);
  return y;
}

static int32_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  int32_T y;
  y = p_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static uint32_T i_emlrt_marshallIn(const mxArray *TrueCount, const char_T
  *identifier)
{
  uint32_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = j_emlrt_marshallIn(emlrtAlias(TrueCount), &thisId);
  emlrtDestroyArray(&TrueCount);
  return y;
}

static uint32_T j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  uint32_T y;
  y = q_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static boolean_T k_emlrt_marshallIn(const mxArray *TakeLuminanceMeanTF, const
  char_T *identifier)
{
  boolean_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = l_emlrt_marshallIn(emlrtAlias(TakeLuminanceMeanTF), &thisId);
  emlrtDestroyArray(&TakeLuminanceMeanTF);
  return y;
}

static boolean_T l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  boolean_T y;
  y = r_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static void n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static void o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static int32_T p_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static uint32_T q_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId)
{
  uint32_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint32", false, 0U,
    &dims);
  ret = *(uint32_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static boolean_T r_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

void IndexAndMean_LogIdx_api(const mxArray * const prhs[9], int32_T nlhs, const
  mxArray *plhs[2])
{
  real_T (*RGBMeans_Double)[3];
  emxArray_uint8_T *R_Uint8;
  emxArray_uint8_T *G_Uint8;
  emxArray_uint8_T *B_Uint8;
  emxArray_real32_T *Luminance_Single;
  emxArray_boolean_T *LogIdx;
  int32_T NRows;
  int32_T NCols;
  uint32_T TrueCount;
  boolean_T TakeLuminanceMeanTF;
  real_T LuminanceMean_Double;
  RGBMeans_Double = (real_T (*)[3])mxMalloc(sizeof(real_T [3]));
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint8_T(&R_Uint8, 2, true);
  emxInit_uint8_T(&G_Uint8, 2, true);
  emxInit_uint8_T(&B_Uint8, 2, true);
  emxInit_real32_T(&Luminance_Single, 2, true);
  emxInit_boolean_T(&LogIdx, 2, true);

  /* Marshall function inputs */
  R_Uint8->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs[0]), "R_Uint8", R_Uint8);
  G_Uint8->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs[1]), "G_Uint8", G_Uint8);
  B_Uint8->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs[2]), "B_Uint8", B_Uint8);
  Luminance_Single->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[3]), "Luminance_Single", Luminance_Single);
  LogIdx->canFreeData = false;
  e_emlrt_marshallIn(emlrtAlias(prhs[4]), "LogIdx", LogIdx);
  NRows = g_emlrt_marshallIn(emlrtAliasP(prhs[5]), "NRows");
  NCols = g_emlrt_marshallIn(emlrtAliasP(prhs[6]), "NCols");
  TrueCount = i_emlrt_marshallIn(emlrtAliasP(prhs[7]), "TrueCount");
  TakeLuminanceMeanTF = k_emlrt_marshallIn(emlrtAliasP(prhs[8]),
    "TakeLuminanceMeanTF");

  /* Invoke the target function */
  IndexAndMean_LogIdx(emlrtRootTLSGlobal, R_Uint8, G_Uint8, B_Uint8,
                      Luminance_Single, LogIdx, NRows, NCols, TrueCount,
                      TakeLuminanceMeanTF, *RGBMeans_Double,
                      &LuminanceMean_Double);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*RGBMeans_Double);
  emxFree_boolean_T(&LogIdx);
  emxFree_real32_T(&Luminance_Single);
  emxFree_uint8_T(&B_Uint8);
  emxFree_uint8_T(&G_Uint8);
  emxFree_uint8_T(&R_Uint8);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(LuminanceMean_Double);
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_IndexAndMean_LogIdx_api.c) */
