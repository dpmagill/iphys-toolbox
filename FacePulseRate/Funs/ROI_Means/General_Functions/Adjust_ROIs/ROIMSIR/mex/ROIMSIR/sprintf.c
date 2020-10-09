/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sprintf.c
 *
 * Code generation for function 'sprintf'
 *
 */

/* Include files */
#include "sprintf.h"
#include "ROIMSIR_data.h"
#include "ROIMSIR_emxutil.h"
#include "ROIMSIR_mexutil.h"
#include "ROIMSIR_types.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtMCInfo d_emlrtMCI = { 52,  /* lineNo */
  14,                                  /* colNo */
  "nonConstPrint",                     /* fName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\lib\\matlab\\strfun\\sprintf.m"/* pName */
};

static emlrtMCInfo e_emlrtMCI = { 54,  /* lineNo */
  15,                                  /* colNo */
  "nonConstPrint",                     /* fName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\lib\\matlab\\strfun\\sprintf.m"/* pName */
};

/* Function Declarations */
static void c_emlrt_marshallIn(const mxArray *tmpStr, const char_T *identifier,
  emxArray_char_T *y);
static void cb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_char_T *ret);
static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_char_T *y);
static const mxArray *feval(const mxArray *b, const mxArray *c, const mxArray *d,
  emlrtMCInfo *location);
static const mxArray *length(const mxArray *b, emlrtMCInfo *location);

/* Function Definitions */
static void c_emlrt_marshallIn(const mxArray *tmpStr, const char_T *identifier,
  emxArray_char_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(emlrtAlias(tmpStr), &thisId, y);
  emlrtDestroyArray(&tmpStr);
}

static void cb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_char_T *ret)
{
  static const int32_T dims[2] = { 1, -1 };

  int32_T iv[2];
  int32_T i;
  const boolean_T bv[2] = { false, true };

  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "char", false, 2U,
    dims, &bv[0], iv);
  i = ret->size[0] * ret->size[1];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  emxEnsureCapacity_char_T(ret, i);
  emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, ret->data, 1, false);
  emlrtDestroyArray(&src);
}

static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_char_T *y)
{
  cb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *feval(const mxArray *b, const mxArray *c, const mxArray *d,
  emlrtMCInfo *location)
{
  const mxArray *pArrays[3];
  const mxArray *m;
  pArrays[0] = b;
  pArrays[1] = c;
  pArrays[2] = d;
  return emlrtCallMATLABR2012b(emlrtRootTLSGlobal, 1, &m, 3, pArrays, "feval",
    true, location);
}

static const mxArray *length(const mxArray *b, emlrtMCInfo *location)
{
  const mxArray *m;
  const mxArray *pArray;
  pArray = b;
  return emlrtCallMATLABR2012b(emlrtRootTLSGlobal, 1, &m, 1, &pArray, "length",
    true, location);
}

void b_sprintf(int32_T varargin_1, emxArray_char_T *str)
{
  static const int32_T iv[2] = { 1, 7 };

  static const int32_T iv1[2] = { 1, 2 };

  static const char_T u[7] = { 's', 'p', 'r', 'i', 'n', 't', 'f' };

  static const char_T formatSpec[2] = { '%', 'd' };

  const mxArray *b_y;
  const mxArray *m;
  const mxArray *tmpStr;
  const mxArray *y;
  tmpStr = NULL;
  y = NULL;
  m = emlrtCreateCharArray(2, &iv[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
  emlrtAssign(&y, m);
  b_y = NULL;
  m = emlrtCreateCharArray(2, &iv1[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 2, m, &formatSpec[0]);
  emlrtAssign(&b_y, m);
  emlrtAssign(&tmpStr, feval(y, b_y, d_emlrt_marshallOut(varargin_1),
    &d_emlrtMCI));
  emlrt_marshallIn(length(emlrtAlias(tmpStr), &e_emlrtMCI), "<output of length>");
  c_emlrt_marshallIn(emlrtAlias(tmpStr), "tmpStr", str);
  emlrtDestroyArray(&tmpStr);
}

/* End of code generation (sprintf.c) */
