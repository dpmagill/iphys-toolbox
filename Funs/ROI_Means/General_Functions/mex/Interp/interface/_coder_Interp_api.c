/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_Interp_api.c
 *
 * Code generation for function '_coder_Interp_api'
 *
 */

/* Include files */
#include "_coder_Interp_api.h"
#include "Interp.h"
#include "Interp_data.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T **y_data, int32_T y_size[1]);
static void c_emlrt_marshallIn(const mxArray *y, const char_T *identifier,
  int16_T **y_data, int32_T y_size[2]);
static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, int16_T **y_data, int32_T y_size[2]);
static boolean_T e_emlrt_marshallIn(const mxArray *LinearExtrapTF, const char_T *
  identifier);
static void emlrt_marshallIn(const mxArray *x, const char_T *identifier,
  real32_T **y_data, int32_T y_size[1]);
static const mxArray *emlrt_marshallOut(const int16_T u_data[], const int32_T
  u_size[2]);
static boolean_T f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static int16_T g_emlrt_marshallIn(const mxArray *DiffMaxActual, const char_T
  *identifier);
static int16_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void i_emlrt_marshallIn(const mxArray *YArbitrary, const char_T
  *identifier, int16_T **y_data, int32_T y_size[2]);
static void j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, int16_T **y_data, int32_T y_size[2]);
static void k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T **ret_data, int32_T ret_size[1]);
static void l_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, int16_T **ret_data, int32_T ret_size[2]);
static boolean_T m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static int16_T n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static void o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, int16_T **ret_data, int32_T ret_size[2]);

/* Function Definitions */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T **y_data, int32_T y_size[1])
{
  k_emlrt_marshallIn(emlrtAlias(u), parentId, y_data, y_size);
  emlrtDestroyArray(&u);
}

static void c_emlrt_marshallIn(const mxArray *y, const char_T *identifier,
  int16_T **y_data, int32_T y_size[2])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(emlrtAlias(y), &thisId, y_data, y_size);
  emlrtDestroyArray(&y);
}

static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, int16_T **y_data, int32_T y_size[2])
{
  l_emlrt_marshallIn(emlrtAlias(u), parentId, y_data, y_size);
  emlrtDestroyArray(&u);
}

static boolean_T e_emlrt_marshallIn(const mxArray *LinearExtrapTF, const char_T *
  identifier)
{
  boolean_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(emlrtAlias(LinearExtrapTF), &thisId);
  emlrtDestroyArray(&LinearExtrapTF);
  return y;
}

static void emlrt_marshallIn(const mxArray *x, const char_T *identifier,
  real32_T **y_data, int32_T y_size[1])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(x), &thisId, y_data, y_size);
  emlrtDestroyArray(&x);
}

static const mxArray *emlrt_marshallOut(const int16_T u_data[], const int32_T
  u_size[2])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 0, 0 };

  y = NULL;
  m = emlrtCreateNumericArray(2, &iv[0], mxINT16_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m, u_size, 2);
  emlrtAssign(&y, m);
  return y;
}

static boolean_T f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  boolean_T y;
  y = m_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static int16_T g_emlrt_marshallIn(const mxArray *DiffMaxActual, const char_T
  *identifier)
{
  int16_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = h_emlrt_marshallIn(emlrtAlias(DiffMaxActual), &thisId);
  emlrtDestroyArray(&DiffMaxActual);
  return y;
}

static int16_T h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  int16_T y;
  y = n_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void i_emlrt_marshallIn(const mxArray *YArbitrary, const char_T
  *identifier, int16_T **y_data, int32_T y_size[2])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  j_emlrt_marshallIn(emlrtAlias(YArbitrary), &thisId, y_data, y_size);
  emlrtDestroyArray(&YArbitrary);
}

static void j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, int16_T **y_data, int32_T y_size[2])
{
  o_emlrt_marshallIn(emlrtAlias(u), parentId, y_data, y_size);
  emlrtDestroyArray(&u);
}

static void k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T **ret_data, int32_T ret_size[1])
{
  static const int32_T dims[1] = { 50 };

  const boolean_T bv[1] = { true };

  int32_T iv[1];
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 1U,
    dims, &bv[0], iv);
  ret_size[0] = iv[0];
  *ret_data = (real32_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
}

static void l_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, int16_T **ret_data, int32_T ret_size[2])
{
  static const int32_T dims[2] = { 50, 4 };

  const boolean_T bv[2] = { true, true };

  int32_T iv[2];
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int16", false, 2U,
    dims, &bv[0], iv);
  ret_size[0] = iv[0];
  ret_size[1] = iv[1];
  *ret_data = (int16_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
}

static boolean_T m_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static int16_T n_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static void o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, int16_T **ret_data, int32_T ret_size[2])
{
  static const int32_T dims[2] = { 1, 2 };

  const boolean_T bv[2] = { true, false };

  int32_T iv[2];
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int16", false, 2U,
    dims, &bv[0], iv);
  ret_size[0] = iv[0];
  ret_size[1] = iv[1];
  *ret_data = (int16_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
}

void Interp_api(const mxArray * const prhs[10], int32_T nlhs, const mxArray
                *plhs[1])
{
  int16_T (*yi_data)[200];
  real32_T (*x_data)[50];
  int32_T x_size[1];
  int16_T (*y_data)[200];
  int32_T y_size[2];
  real32_T (*xi_data)[50];
  int32_T xi_size[1];
  boolean_T LinearExtrapTF;
  boolean_T ValidityChecksTF;
  int16_T DiffMaxActual;
  int16_T (*YArbitrary_data)[2];
  int32_T YArbitrary_size[2];
  int16_T DiffMaxArbitrary;
  int16_T VidObjWidth;
  int16_T VidObjHeight;
  int32_T yi_size[2];
  (void)nlhs;
  yi_data = (int16_T (*)[200])mxMalloc(sizeof(int16_T [200]));

  /* Marshall function inputs */
  emlrt_marshallIn(emlrtAlias(prhs[0]), "x", (real32_T **)&x_data, x_size);
  c_emlrt_marshallIn(emlrtAlias(prhs[1]), "y", (int16_T **)&y_data, y_size);
  emlrt_marshallIn(emlrtAlias(prhs[2]), "xi", (real32_T **)&xi_data, xi_size);
  LinearExtrapTF = e_emlrt_marshallIn(emlrtAliasP(prhs[3]), "LinearExtrapTF");
  ValidityChecksTF = e_emlrt_marshallIn(emlrtAliasP(prhs[4]), "ValidityChecksTF");
  DiffMaxActual = g_emlrt_marshallIn(emlrtAliasP(prhs[5]), "DiffMaxActual");
  i_emlrt_marshallIn(emlrtAlias(prhs[6]), "YArbitrary", (int16_T **)
                     &YArbitrary_data, YArbitrary_size);
  DiffMaxArbitrary = g_emlrt_marshallIn(emlrtAliasP(prhs[7]), "DiffMaxArbitrary");
  VidObjWidth = g_emlrt_marshallIn(emlrtAliasP(prhs[8]), "VidObjWidth");
  VidObjHeight = g_emlrt_marshallIn(emlrtAliasP(prhs[9]), "VidObjHeight");

  /* Invoke the target function */
  Interp(*x_data, x_size, *y_data, y_size, *xi_data, xi_size, LinearExtrapTF,
         ValidityChecksTF, DiffMaxActual, *YArbitrary_data, YArbitrary_size,
         DiffMaxArbitrary, VidObjWidth, VidObjHeight, *yi_data, yi_size);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*yi_data, yi_size);
}

/* End of code generation (_coder_Interp_api.c) */
