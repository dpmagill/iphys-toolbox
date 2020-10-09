/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_insertShapeFast_FilledCircles_api.c
 *
 * Code generation for function '_coder_insertShapeFast_FilledCircles_api'
 *
 */

/* Include files */
#include "_coder_insertShapeFast_FilledCircles_api.h"
#include "insertShapeFast_FilledCircles.h"
#include "insertShapeFast_FilledCircles_data.h"
#include "insertShapeFast_FilledCircles_emxutil.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y);
static void c_emlrt_marshallIn(const mxArray *BulletPointsXYR_Cropped, const
  char_T *identifier, int16_T **y_data, int32_T y_size[2]);
static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, int16_T **y_data, int32_T y_size[2]);
static void e_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret);
static void emlrt_marshallIn(const mxArray *FrameCropped_BulletPoints, const
  char_T *identifier, emxArray_uint8_T *y);
static void emlrt_marshallOut(const emxArray_uint8_T *u, const mxArray *y);
static void f_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, int16_T **ret_data, int32_T ret_size[2]);

/* Function Definitions */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y)
{
  e_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void c_emlrt_marshallIn(const mxArray *BulletPointsXYR_Cropped, const
  char_T *identifier, int16_T **y_data, int32_T y_size[2])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(emlrtAlias(BulletPointsXYR_Cropped), &thisId, y_data,
                     y_size);
  emlrtDestroyArray(&BulletPointsXYR_Cropped);
}

static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, int16_T **y_data, int32_T y_size[2])
{
  f_emlrt_marshallIn(emlrtAlias(u), parentId, y_data, y_size);
  emlrtDestroyArray(&u);
}

static void e_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static void emlrt_marshallIn(const mxArray *FrameCropped_BulletPoints, const
  char_T *identifier, emxArray_uint8_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(FrameCropped_BulletPoints), &thisId, y);
  emlrtDestroyArray(&FrameCropped_BulletPoints);
}

static void emlrt_marshallOut(const emxArray_uint8_T *u, const mxArray *y)
{
  emlrtMxSetData((mxArray *)y, &u->data[0]);
  emlrtSetDimensions((mxArray *)y, u->size, 3);
}

static void f_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, int16_T **ret_data, int32_T ret_size[2])
{
  static const int32_T dims[2] = { 50, 3 };

  const boolean_T bv[2] = { true, false };

  int32_T iv[2];
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int16", false, 2U,
    dims, &bv[0], iv);
  ret_size[0] = iv[0];
  ret_size[1] = iv[1];
  *ret_data = (int16_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
}

void insertShapeFast_FilledCircles_api(const mxArray * const prhs[2], int32_T
  nlhs, const mxArray *plhs[1])
{
  emxArray_uint8_T *FrameCropped_BulletPoints;
  const mxArray *prhs_copy_idx_0;
  int16_T (*BulletPointsXYR_Cropped_data)[150];
  int32_T BulletPointsXYR_Cropped_size[2];
  (void)nlhs;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint8_T(&FrameCropped_BulletPoints, 3, true);
  prhs_copy_idx_0 = emlrtProtectR2012b(prhs[0], 0, true, -1);

  /* Marshall function inputs */
  FrameCropped_BulletPoints->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs_copy_idx_0), "FrameCropped_BulletPoints",
                   FrameCropped_BulletPoints);
  c_emlrt_marshallIn(emlrtAlias(prhs[1]), "BulletPointsXYR_Cropped", (int16_T **)
                     &BulletPointsXYR_Cropped_data, BulletPointsXYR_Cropped_size);

  /* Invoke the target function */
  insertShapeFast_FilledCircles(FrameCropped_BulletPoints,
    *BulletPointsXYR_Cropped_data, BulletPointsXYR_Cropped_size);

  /* Marshall function outputs */
  FrameCropped_BulletPoints->canFreeData = false;
  emlrt_marshallOut(FrameCropped_BulletPoints, prhs_copy_idx_0);
  plhs[0] = prhs_copy_idx_0;
  emxFree_uint8_T(&FrameCropped_BulletPoints);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_insertShapeFast_FilledCircles_api.c) */
