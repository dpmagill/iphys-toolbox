/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_insertTextFast_PulseRate20_api.c
 *
 * Code generation for function '_coder_insertTextFast_PulseRate20_api'
 *
 */

/* Include files */
#include "_coder_insertTextFast_PulseRate20_api.h"
#include "insertTextFast_PulseRate20.h"
#include "insertTextFast_PulseRate20_data.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static const int32_T iv1[3] = { 45, 850, 3 };

/* Function Declarations */
static uint8_T (*b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[114750];
static void c_emlrt_marshallIn(const mxArray *Text, const char_T *identifier,
  char_T y_data[], int32_T y_size[2]);
static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, char_T y_data[], int32_T y_size[2]);
static uint8_T (*e_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId))[114750];
static uint8_T (*emlrt_marshallIn(const mxArray *VidFrameCrop, const char_T
  *identifier))[114750];
static void emlrt_marshallOut(const uint8_T u[114750], const mxArray *y);
static void f_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, char_T ret_data[], int32_T ret_size[2]);

/* Function Definitions */
static uint8_T (*b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[114750]
{
  uint8_T (*y)[114750];
  y = e_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static void c_emlrt_marshallIn(const mxArray *Text, const char_T *identifier,
  char_T y_data[], int32_T y_size[2])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(emlrtAlias(Text), &thisId, y_data, y_size);
  emlrtDestroyArray(&Text);
}

static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, char_T y_data[], int32_T y_size[2])
{
  f_emlrt_marshallIn(emlrtAlias(u), parentId, y_data, y_size);
  emlrtDestroyArray(&u);
}

static uint8_T (*e_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId))[114750]
{
  uint8_T (*ret)[114750];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint8", false, 3U,
    iv1);
  ret = (uint8_T (*)[114750])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static uint8_T (*emlrt_marshallIn(const mxArray *VidFrameCrop, const char_T
  *identifier))[114750]
{
  uint8_T (*y)[114750];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(emlrtAlias(VidFrameCrop), &thisId);
  emlrtDestroyArray(&VidFrameCrop);
  return y;
}

static void emlrt_marshallOut(const uint8_T u[114750], const mxArray *y)
{
  emlrtMxSetData((mxArray *)y, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)y, iv1, 3);
}

static void f_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, char_T ret_data[], int32_T ret_size[2])
{
  static const int32_T dims[2] = { 1, 125 };

  const boolean_T bv[2] = { false, true };

  int32_T b_iv[2];
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "char", false, 2U,
    dims, &bv[0], b_iv);
  ret_size[0] = b_iv[0];
  ret_size[1] = b_iv[1];
  emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, (void *)ret_data, 1, false);
  emlrtDestroyArray(&src);
}

void insertTextFast_PulseRate20_api(const mxArray * const prhs[2], int32_T nlhs,
  const mxArray *plhs[1])
{
  const mxArray *prhs_copy_idx_0;
  uint8_T (*VidFrameCrop)[114750];
  char_T Text_data[125];
  int32_T Text_size[2];
  (void)nlhs;
  prhs_copy_idx_0 = emlrtProtectR2012b(prhs[0], 0, true, -1);

  /* Marshall function inputs */
  VidFrameCrop = emlrt_marshallIn(emlrtAlias(prhs_copy_idx_0), "VidFrameCrop");
  c_emlrt_marshallIn(emlrtAliasP(prhs[1]), "Text", Text_data, Text_size);

  /* Invoke the target function */
  insertTextFast_PulseRate20(*VidFrameCrop, Text_data, Text_size);

  /* Marshall function outputs */
  emlrt_marshallOut(*VidFrameCrop, prhs_copy_idx_0);
  plhs[0] = prhs_copy_idx_0;
}

/* End of code generation (_coder_insertTextFast_PulseRate20_api.c) */
