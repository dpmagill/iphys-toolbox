/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ROIResize_api.c
 *
 * Code generation for function '_coder_ROIResize_api'
 *
 */

/* Include files */
#include "_coder_ROIResize_api.h"
#include "ROIResize.h"
#include "ROIResize_data.h"
#include "ROIResize_emxutil.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int16_T *y);
static void c_emlrt_marshallIn(const mxArray *ROIsToResizeLinIdx, const char_T
  *identifier, emxArray_int32_T *y);
static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int32_T *y);
static real_T e_emlrt_marshallIn(const mxArray *ROIWidthResizeFactor, const
  char_T *identifier);
static void emlrt_marshallIn(const mxArray *ROI, const char_T *identifier,
  emxArray_int16_T *y);
static const mxArray *emlrt_marshallOut(const emxArray_int16_T *u);
static real_T f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static int16_T g_emlrt_marshallIn(const mxArray *VidObjWidth, const char_T
  *identifier);
static int16_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void i_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int16_T *ret);
static void j_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int32_T *ret);
static real_T k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static int16_T l_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);

/* Function Definitions */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int16_T *y)
{
  i_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void c_emlrt_marshallIn(const mxArray *ROIsToResizeLinIdx, const char_T
  *identifier, emxArray_int32_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(emlrtAlias(ROIsToResizeLinIdx), &thisId, y);
  emlrtDestroyArray(&ROIsToResizeLinIdx);
}

static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int32_T *y)
{
  j_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real_T e_emlrt_marshallIn(const mxArray *ROIWidthResizeFactor, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(emlrtAlias(ROIWidthResizeFactor), &thisId);
  emlrtDestroyArray(&ROIWidthResizeFactor);
  return y;
}

static void emlrt_marshallIn(const mxArray *ROI, const char_T *identifier,
  emxArray_int16_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(ROI), &thisId, y);
  emlrtDestroyArray(&ROI);
}

static const mxArray *emlrt_marshallOut(const emxArray_int16_T *u)
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 0, 0 };

  y = NULL;
  m = emlrtCreateNumericArray(2, &iv[0], mxINT16_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &u->data[0]);
  emlrtSetDimensions((mxArray *)m, u->size, 2);
  emlrtAssign(&y, m);
  return y;
}

static real_T f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  real_T y;
  y = k_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static int16_T g_emlrt_marshallIn(const mxArray *VidObjWidth, const char_T
  *identifier)
{
  int16_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = h_emlrt_marshallIn(emlrtAlias(VidObjWidth), &thisId);
  emlrtDestroyArray(&VidObjWidth);
  return y;
}

static int16_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  int16_T y;
  y = l_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void i_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static void j_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int32_T *ret)
{
  static const int32_T dims[2] = { 1, -1 };

  const boolean_T bv[2] = { false, true };

  int32_T iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int32", false, 2U,
    dims, &bv[0], iv);
  ret->allocatedSize = iv[0] * iv[1];
  i = ret->size[0] * ret->size[1];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  emxEnsureCapacity_int32_T(ret, i);
  ret->data = (int32_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static real_T k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static int16_T l_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

void ROIResize_api(const mxArray * const prhs[6], int32_T nlhs, const mxArray
                   *plhs[1])
{
  emxArray_int16_T *ROI;
  emxArray_int32_T *ROIsToResizeLinIdx;
  emxArray_int16_T *b_ROIResize;
  real_T ROIWidthResizeFactor;
  real_T ROIHeightResizeFactor;
  int16_T VidObjWidth;
  int16_T VidObjHeight;
  (void)nlhs;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_int16_T(&ROI, 2, true);
  emxInit_int32_T(&ROIsToResizeLinIdx, 2, true);
  emxInit_int16_T(&b_ROIResize, 2, true);

  /* Marshall function inputs */
  ROI->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs[0]), "ROI", ROI);
  ROIsToResizeLinIdx->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[1]), "ROIsToResizeLinIdx",
                     ROIsToResizeLinIdx);
  ROIWidthResizeFactor = e_emlrt_marshallIn(emlrtAliasP(prhs[2]),
    "ROIWidthResizeFactor");
  ROIHeightResizeFactor = e_emlrt_marshallIn(emlrtAliasP(prhs[3]),
    "ROIHeightResizeFactor");
  VidObjWidth = g_emlrt_marshallIn(emlrtAliasP(prhs[4]), "VidObjWidth");
  VidObjHeight = g_emlrt_marshallIn(emlrtAliasP(prhs[5]), "VidObjHeight");

  /* Invoke the target function */
  ROIResize(ROI, ROIsToResizeLinIdx, ROIWidthResizeFactor, ROIHeightResizeFactor,
            VidObjWidth, VidObjHeight, b_ROIResize);

  /* Marshall function outputs */
  b_ROIResize->canFreeData = false;
  plhs[0] = emlrt_marshallOut(b_ROIResize);
  emxFree_int16_T(&b_ROIResize);
  emxFree_int32_T(&ROIsToResizeLinIdx);
  emxFree_int16_T(&ROI);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_ROIResize_api.c) */
