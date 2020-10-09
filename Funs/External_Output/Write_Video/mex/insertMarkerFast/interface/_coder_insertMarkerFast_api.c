/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_insertMarkerFast_api.c
 *
 * Code generation for function '_coder_insertMarkerFast_api'
 *
 */

/* Include files */
#include "_coder_insertMarkerFast_api.h"
#include "insertMarkerFast.h"
#include "insertMarkerFast_data.h"
#include "insertMarkerFast_emxutil.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y);
static int16_T (*c_emlrt_marshallIn(const mxArray *MarkerPointsXY_Cropped, const
  char_T *identifier))[4];
static int16_T (*d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[4];
static real_T e_emlrt_marshallIn(const mxArray *MarkerSize, const char_T
  *identifier);
static void emlrt_marshallIn(const mxArray *FrameCropped_Markers, const char_T
  *identifier, emxArray_uint8_T *y);
static void emlrt_marshallOut(const emxArray_uint8_T *u, const mxArray *y);
static real_T f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void g_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret);
static int16_T (*h_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId))[4];
static real_T i_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);

/* Function Definitions */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y)
{
  g_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int16_T (*c_emlrt_marshallIn(const mxArray *MarkerPointsXY_Cropped, const
  char_T *identifier))[4]
{
  int16_T (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(emlrtAlias(MarkerPointsXY_Cropped), &thisId);
  emlrtDestroyArray(&MarkerPointsXY_Cropped);
  return y;
}
  static int16_T (*d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[4]
{
  int16_T (*y)[4];
  y = h_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T e_emlrt_marshallIn(const mxArray *MarkerSize, const char_T
  *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(emlrtAlias(MarkerSize), &thisId);
  emlrtDestroyArray(&MarkerSize);
  return y;
}

static void emlrt_marshallIn(const mxArray *FrameCropped_Markers, const char_T
  *identifier, emxArray_uint8_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(FrameCropped_Markers), &thisId, y);
  emlrtDestroyArray(&FrameCropped_Markers);
}

static void emlrt_marshallOut(const emxArray_uint8_T *u, const mxArray *y)
{
  emlrtMxSetData((mxArray *)y, &u->data[0]);
  emlrtSetDimensions((mxArray *)y, u->size, 3);
}

static real_T f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  real_T y;
  y = i_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void g_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static int16_T (*h_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId))[4]
{
  int16_T (*ret)[4];
  static const int32_T dims[2] = { 2, 2 };

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int16", false, 2U,
    dims);
  ret = (int16_T (*)[4])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static real_T i_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 0U,
    &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void insertMarkerFast_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[1])
{
  emxArray_uint8_T *FrameCropped_Markers;
  const mxArray *prhs_copy_idx_0;
  int16_T (*MarkerPointsXY_Cropped)[4];
  real_T MarkerSize;
  (void)nlhs;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint8_T(&FrameCropped_Markers, 3, true);
  prhs_copy_idx_0 = emlrtProtectR2012b(prhs[0], 0, true, -1);

  /* Marshall function inputs */
  FrameCropped_Markers->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs_copy_idx_0), "FrameCropped_Markers",
                   FrameCropped_Markers);
  MarkerPointsXY_Cropped = c_emlrt_marshallIn(emlrtAlias(prhs[1]),
    "MarkerPointsXY_Cropped");
  MarkerSize = e_emlrt_marshallIn(emlrtAliasP(prhs[2]), "MarkerSize");

  /* Invoke the target function */
  insertMarkerFast(FrameCropped_Markers, *MarkerPointsXY_Cropped, MarkerSize);

  /* Marshall function outputs */
  FrameCropped_Markers->canFreeData = false;
  emlrt_marshallOut(FrameCropped_Markers, prhs_copy_idx_0);
  plhs[0] = prhs_copy_idx_0;
  emxFree_uint8_T(&FrameCropped_Markers);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_insertMarkerFast_api.c) */
