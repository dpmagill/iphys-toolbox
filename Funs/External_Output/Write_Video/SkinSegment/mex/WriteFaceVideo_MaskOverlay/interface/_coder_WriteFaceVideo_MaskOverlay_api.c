/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_WriteFaceVideo_MaskOverlay_api.c
 *
 * Code generation for function '_coder_WriteFaceVideo_MaskOverlay_api'
 *
 */

/* Include files */
#include "_coder_WriteFaceVideo_MaskOverlay_api.h"
#include "WriteFaceVideo_MaskOverlay.h"
#include "WriteFaceVideo_MaskOverlay_data.h"
#include "WriteFaceVideo_MaskOverlay_emxutil.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y);
static real32_T c_emlrt_marshallIn(const mxArray *Transparency, const char_T
  *identifier);
static real32_T d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void e_emlrt_marshallIn(const mxArray *IsSkinMask_Inverted, const char_T *
  identifier, emxArray_boolean_T *y);
static void emlrt_marshallIn(const mxArray *VidFrameROI, const char_T
  *identifier, emxArray_uint8_T *y);
static void emlrt_marshallOut(const emxArray_uint8_T *u, const mxArray *y);
static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_boolean_T *y);
static real_T (*g_emlrt_marshallIn(const mxArray *Color, const char_T
  *identifier))[3];
static real_T (*h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[3];
static uint16_T i_emlrt_marshallIn(const mxArray *nRows, const char_T
  *identifier);
static uint16_T j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret);
static real32_T l_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);
static void m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_boolean_T *ret);
static real_T (*n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[3];
static uint16_T o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);

/* Function Definitions */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y)
{
  k_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real32_T c_emlrt_marshallIn(const mxArray *Transparency, const char_T
  *identifier)
{
  real32_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(emlrtAlias(Transparency), &thisId);
  emlrtDestroyArray(&Transparency);
  return y;
}

static real32_T d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  real32_T y;
  y = l_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void e_emlrt_marshallIn(const mxArray *IsSkinMask_Inverted, const char_T *
  identifier, emxArray_boolean_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(emlrtAlias(IsSkinMask_Inverted), &thisId, y);
  emlrtDestroyArray(&IsSkinMask_Inverted);
}

static void emlrt_marshallIn(const mxArray *VidFrameROI, const char_T
  *identifier, emxArray_uint8_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(VidFrameROI), &thisId, y);
  emlrtDestroyArray(&VidFrameROI);
}

static void emlrt_marshallOut(const emxArray_uint8_T *u, const mxArray *y)
{
  emlrtMxSetData((mxArray *)y, &u->data[0]);
  emlrtSetDimensions((mxArray *)y, u->size, 3);
}

static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_boolean_T *y)
{
  m_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real_T (*g_emlrt_marshallIn(const mxArray *Color, const char_T
  *identifier))[3]
{
  real_T (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = h_emlrt_marshallIn(emlrtAlias(Color), &thisId);
  emlrtDestroyArray(&Color);
  return y;
}
  static real_T (*h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[3]
{
  real_T (*y)[3];
  y = n_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static uint16_T i_emlrt_marshallIn(const mxArray *nRows, const char_T
  *identifier)
{
  uint16_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = j_emlrt_marshallIn(emlrtAlias(nRows), &thisId);
  emlrtDestroyArray(&nRows);
  return y;
}

static uint16_T j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  uint16_T y;
  y = o_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret)
{
  static const int32_T dims[3] = { -1, -1, 3 };

  const boolean_T bv[3] = { true, true, false };

  int32_T iv[3];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint8", false, 3U,
    dims, &bv[0], iv);
  ret->allocatedSize = iv[0] * iv[1] * iv[2];
  i = ret->size[0] * ret->size[1] * ret->size[2];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  ret->size[2] = iv[2];
  emxEnsureCapacity_uint8_T(ret, i);
  ret->data = (uint8_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static real32_T l_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
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

static void m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static real_T (*n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[3]
{
  real_T (*ret)[3];
  static const int32_T dims[2] = { 1, 3 };

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 2U,
    dims);
  ret = (real_T (*)[3])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static uint16_T o_emlrt_marshallIn(const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  uint16_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint16", false, 0U,
    &dims);
  ret = *(uint16_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void WriteFaceVideo_MaskOverlay_api(const mxArray * const prhs[6], int32_T nlhs,
  const mxArray *plhs[1])
{
  emxArray_uint8_T *VidFrameROI;
  emxArray_boolean_T *IsSkinMask_Inverted;
  const mxArray *prhs_copy_idx_0;
  real32_T Transparency;
  real_T (*Color)[3];
  uint16_T nRows;
  uint16_T nCols;
  (void)nlhs;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint8_T(&VidFrameROI, 3, true);
  emxInit_boolean_T(&IsSkinMask_Inverted, 2, true);
  prhs_copy_idx_0 = emlrtProtectR2012b(prhs[0], 0, true, -1);

  /* Marshall function inputs */
  VidFrameROI->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs_copy_idx_0), "VidFrameROI", VidFrameROI);
  Transparency = c_emlrt_marshallIn(emlrtAliasP(prhs[1]), "Transparency");
  IsSkinMask_Inverted->canFreeData = false;
  e_emlrt_marshallIn(emlrtAlias(prhs[2]), "IsSkinMask_Inverted",
                     IsSkinMask_Inverted);
  Color = g_emlrt_marshallIn(emlrtAlias(prhs[3]), "Color");
  nRows = i_emlrt_marshallIn(emlrtAliasP(prhs[4]), "nRows");
  nCols = i_emlrt_marshallIn(emlrtAliasP(prhs[5]), "nCols");

  /* Invoke the target function */
  WriteFaceVideo_MaskOverlay(VidFrameROI, Transparency, IsSkinMask_Inverted,
    *Color, nRows, nCols);

  /* Marshall function outputs */
  VidFrameROI->canFreeData = false;
  emlrt_marshallOut(VidFrameROI, prhs_copy_idx_0);
  plhs[0] = prhs_copy_idx_0;
  emxFree_boolean_T(&IsSkinMask_Inverted);
  emxFree_uint8_T(&VidFrameROI);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_WriteFaceVideo_MaskOverlay_api.c) */
