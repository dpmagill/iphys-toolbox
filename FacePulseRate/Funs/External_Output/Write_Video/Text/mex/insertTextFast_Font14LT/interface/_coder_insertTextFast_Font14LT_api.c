/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_insertTextFast_Font14LT_api.c
 *
 * Code generation for function '_coder_insertTextFast_Font14LT_api'
 *
 */

/* Include files */
#include "_coder_insertTextFast_Font14LT_api.h"
#include "insertTextFast_Font14LT.h"
#include "insertTextFast_Font14LT_data.h"
#include "insertTextFast_Font14LT_emxutil.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y);
static void c_emlrt_marshallIn(const mxArray *TextXY, const char_T *identifier,
  emxArray_int16_T *y);
static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int16_T *y);
static void e_emlrt_marshallIn(const mxArray *Text, const char_T *identifier,
  emxArray_cell_wrap_0 *y);
static void emlrt_marshallIn(const mxArray *VidFrame, const char_T *identifier,
  emxArray_uint8_T *y);
static void emlrt_marshallOut(const emxArray_uint8_T *u, const mxArray *y);
static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_cell_wrap_0 *y);
static void g_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_char_T *y);
static void h_emlrt_marshallIn(const mxArray *textColor, const char_T
  *identifier, emxArray_real_T *y);
static void i_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real_T *y);
static real_T (*j_emlrt_marshallIn(const mxArray *BoxColor, const char_T
  *identifier))[3];
static real_T (*k_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[3];
static void l_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret);
static void m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int16_T *ret);
static void n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_char_T *ret);
static void o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real_T *ret);
static real_T (*p_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[3];

/* Function Definitions */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y)
{
  l_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void c_emlrt_marshallIn(const mxArray *TextXY, const char_T *identifier,
  emxArray_int16_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(emlrtAlias(TextXY), &thisId, y);
  emlrtDestroyArray(&TextXY);
}

static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int16_T *y)
{
  m_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void e_emlrt_marshallIn(const mxArray *Text, const char_T *identifier,
  emxArray_cell_wrap_0 *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(emlrtAlias(Text), &thisId, y);
  emlrtDestroyArray(&Text);
}

static void emlrt_marshallIn(const mxArray *VidFrame, const char_T *identifier,
  emxArray_uint8_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(VidFrame), &thisId, y);
  emlrtDestroyArray(&VidFrame);
}

static void emlrt_marshallOut(const emxArray_uint8_T *u, const mxArray *y)
{
  emlrtMxSetData((mxArray *)y, &u->data[0]);
  emlrtSetDimensions((mxArray *)y, u->size, 3);
}

static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_cell_wrap_0 *y)
{
  emlrtMsgIdentifier thisId;
  int32_T n[1];
  boolean_T bv[1];
  int32_T sizes[1];
  int32_T i;
  char_T str[11];
  thisId.fParent = parentId;
  thisId.bParentIsCell = true;
  n[0] = -1;
  bv[0] = true;
  emlrtCheckVsCell(emlrtRootTLSGlobal, parentId, u, 1U, n, bv, sizes);
  i = y->size[0];
  y->size[0] = sizes[0];
  emxEnsureCapacity_cell_wrap_0(y, i);
  for (i = 0; i < sizes[0]; i++) {
    sprintf(&str[0], "%d", i + 1);
    thisId.fIdentifier = &str[0];
    g_emlrt_marshallIn(emlrtAlias(emlrtGetCell(emlrtRootTLSGlobal, parentId, u,
      i)), &thisId, y->data[i].f1);
  }

  emlrtDestroyArray(&u);
}

static void g_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_char_T *y)
{
  n_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void h_emlrt_marshallIn(const mxArray *textColor, const char_T
  *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  i_emlrt_marshallIn(emlrtAlias(textColor), &thisId, y);
  emlrtDestroyArray(&textColor);
}

static void i_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real_T *y)
{
  o_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real_T (*j_emlrt_marshallIn(const mxArray *BoxColor, const char_T
  *identifier))[3]
{
  real_T (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = k_emlrt_marshallIn(emlrtAlias(BoxColor), &thisId);
  emlrtDestroyArray(&BoxColor);
  return y;
}
  static real_T (*k_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[3]
{
  real_T (*y)[3];
  y = p_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void l_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret)
{
  static const int32_T dims[3] = { -1, -1, 3 };

  const boolean_T bv[3] = { true, true, false };

  int32_T b_iv[3];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint8", false, 3U,
    dims, &bv[0], b_iv);
  ret->allocatedSize = b_iv[0] * b_iv[1] * b_iv[2];
  i = ret->size[0] * ret->size[1] * ret->size[2];
  ret->size[0] = b_iv[0];
  ret->size[1] = b_iv[1];
  ret->size[2] = b_iv[2];
  emxEnsureCapacity_uint8_T(ret, i);
  ret->data = (uint8_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int16_T *ret)
{
  static const int32_T dims[2] = { -1, 2 };

  const boolean_T bv[2] = { true, false };

  int32_T b_iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int16", false, 2U,
    dims, &bv[0], b_iv);
  ret->allocatedSize = b_iv[0] * b_iv[1];
  i = ret->size[0] * ret->size[1];
  ret->size[0] = b_iv[0];
  ret->size[1] = b_iv[1];
  emxEnsureCapacity_int16_T(ret, i);
  ret->data = (int16_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_char_T *ret)
{
  static const int32_T dims[2] = { 1, -1 };

  const boolean_T bv[2] = { false, true };

  int32_T b_iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "char", false, 2U,
    dims, &bv[0], b_iv);
  i = ret->size[0] * ret->size[1];
  ret->size[0] = b_iv[0];
  ret->size[1] = b_iv[1];
  emxEnsureCapacity_char_T(ret, i);
  emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, ret->data, 1, false);
  emlrtDestroyArray(&src);
}

static void o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[2] = { -1, 3 };

  const boolean_T bv[2] = { true, false };

  int32_T b_iv[2];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 2U,
    dims, &bv[0], b_iv);
  ret->allocatedSize = b_iv[0] * b_iv[1];
  i = ret->size[0] * ret->size[1];
  ret->size[0] = b_iv[0];
  ret->size[1] = b_iv[1];
  emxEnsureCapacity_real_T(ret, i);
  ret->data = (real_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static real_T (*p_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
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
  void insertTextFast_Font14LT_api(const mxArray * const prhs[5], int32_T nlhs,
  const mxArray *plhs[1])
{
  emxArray_uint8_T *VidFrame;
  emxArray_int16_T *TextXY;
  emxArray_cell_wrap_0 *Text;
  emxArray_real_T *textColor;
  const mxArray *prhs_copy_idx_0;
  real_T (*BoxColor)[3];
  (void)nlhs;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint8_T(&VidFrame, 3, true);
  emxInit_int16_T(&TextXY, 2, true);
  emxInit_cell_wrap_0(&Text, 1, true);
  emxInit_real_T(&textColor, 2, true);
  prhs_copy_idx_0 = emlrtProtectR2012b(prhs[0], 0, true, -1);

  /* Marshall function inputs */
  VidFrame->canFreeData = false;
  emlrt_marshallIn(emlrtAlias(prhs_copy_idx_0), "VidFrame", VidFrame);
  TextXY->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[1]), "TextXY", TextXY);
  e_emlrt_marshallIn(emlrtAliasP(prhs[2]), "Text", Text);
  textColor->canFreeData = false;
  h_emlrt_marshallIn(emlrtAlias(prhs[3]), "textColor", textColor);
  BoxColor = j_emlrt_marshallIn(emlrtAlias(prhs[4]), "BoxColor");

  /* Invoke the target function */
  insertTextFast_Font14LT(VidFrame, TextXY, Text, textColor, *BoxColor);

  /* Marshall function outputs */
  VidFrame->canFreeData = false;
  emlrt_marshallOut(VidFrame, prhs_copy_idx_0);
  plhs[0] = prhs_copy_idx_0;
  emxFree_real_T(&textColor);
  emxFree_cell_wrap_0(&Text);
  emxFree_int16_T(&TextXY);
  emxFree_uint8_T(&VidFrame);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_insertTextFast_Font14LT_api.c) */
