/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ROIAdjustIfExceedsFrameDims_api.c
 *
 * Code generation for function '_coder_ROIAdjustIfExceedsFrameDims_api'
 *
 */

/* Include files */
#include "_coder_ROIAdjustIfExceedsFrameDims_api.h"
#include "ROIAdjustIfExceedsFrameDims.h"
#include "ROIAdjustIfExceedsFrameDims_data.h"
#include "ROIAdjustIfExceedsFrameDims_emxutil.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int16_T *y);
static int16_T c_emlrt_marshallIn(const mxArray *VidObjWidth, const char_T
  *identifier);
static int16_T d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void e_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int16_T *ret);
static void emlrt_marshallIn(const mxArray *ROIsProposed, const char_T
  *identifier, emxArray_int16_T *y);
static void emlrt_marshallOut(const emxArray_int16_T *u, const mxArray *y);
static int16_T f_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);

/* Function Definitions */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int16_T *y)
{
  e_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int16_T c_emlrt_marshallIn(const mxArray *VidObjWidth, const char_T
  *identifier)
{
  int16_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(emlrtAlias(VidObjWidth), &thisId);
  emlrtDestroyArray(&VidObjWidth);
  return y;
}

static int16_T d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  int16_T y;
  y = f_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void e_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int16_T *ret)
{
  static const int32_T dims[2] = { -1, 4 };

  const boolean_T bv[2] = { true, false };

  int32_T iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int16", false, 2U,
    dims, &bv[0], iv);
  ret->allocatedSize = iv[0] * iv[1];
  i = ret->size[0] * ret->size[1];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  emxEnsureCapacity_int16_T(ret, i);
  ret->data = (int16_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void emlrt_marshallIn(const mxArray *ROIsProposed, const char_T
  *identifier, emxArray_int16_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(ROIsProposed), &thisId, y);
  emlrtDestroyArray(&ROIsProposed);
}

static void emlrt_marshallOut(const emxArray_int16_T *u, const mxArray *y)
{
  emlrtMxSetData((mxArray *)y, &u->data[0]);
  emlrtSetDimensions((mxArray *)y, u->size, 2);
}

static int16_T f_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId)
{
  int16_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int16", false, 0U,
    &dims);
  ret = *(int16_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void ROIAdjustIfExceedsFrameDims_api(const mxArray * const prhs[3], int32_T nlhs,
  const mxArray *plhs[1])
{
  emxArray_int16_T *ROIsProposed;
  const mxArray *prhs_copy_idx_0;
  int16_T VidObjWidth;
  int16_T VidObjHeight;
  (void)nlhs;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_int16_T(&ROIsProposed, 2, true);
  prhs_copy_idx_0 = emlrtProtectR2012b(prhs[0], 0, true, -1);

  /* Marshall function inputs */
  ROIsProposed->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs_copy_idx_0), "ROIsProposed", ROIsProposed);
  VidObjWidth = c_emlrt_marshallIn(emlrtAliasP(prhs[1]), "VidObjWidth");
  VidObjHeight = c_emlrt_marshallIn(emlrtAliasP(prhs[2]), "VidObjHeight");

  /* Invoke the target function */
  ROIAdjustIfExceedsFrameDims(ROIsProposed, VidObjWidth, VidObjHeight);

  /* Marshall function outputs */
  ROIsProposed->canFreeData = false;
  emlrt_marshallOut(ROIsProposed, prhs_copy_idx_0);
  plhs[0] = prhs_copy_idx_0;
  emxFree_int16_T(&ROIsProposed);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_ROIAdjustIfExceedsFrameDims_api.c) */
