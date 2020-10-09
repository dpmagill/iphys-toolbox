/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ROIMSIR_api.c
 *
 * Code generation for function '_coder_ROIMSIR_api'
 *
 */

/* Include files */
#include "_coder_ROIMSIR_api.h"
#include "ROIMSIR.h"
#include "ROIMSIR_data.h"
#include "ROIMSIR_emxutil.h"
#include "ROIMSIR_mexutil.h"
#include "ROIMSIR_types.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static real32_T ab_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void db_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int32_T *ret);
static void e_emlrt_marshallIn(const mxArray *BlockFullLinIdx_In, const char_T
  *identifier, emxArray_int32_T *y);
static void eb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int16_T *ret);
static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int32_T *y);
static void fb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real32_T *ret);
static void g_emlrt_marshallIn(const mxArray *ROI, const char_T *identifier,
  emxArray_int16_T *y);
static void gb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_boolean_T *ret);
static void h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int16_T *y);
static int16_T hb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);
static void i_emlrt_marshallIn(const mxArray *Timestamp, const char_T
  *identifier, emxArray_real32_T *y);
static boolean_T ib_emlrt_marshallIn(const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static void j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real32_T *y);
static int32_T (*jb_emlrt_marshallIn(const mxArray *src, const
  emlrtMsgIdentifier *msgId))[2];
static void k_emlrt_marshallIn(const mxArray *HasROI_TF, const char_T
  *identifier, struct0_T *y);
static void kb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int32_T *ret);
static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct0_T *y);
static int32_T lb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);
static void m_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_boolean_T *y);
static real32_T mb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static int16_T n_emlrt_marshallIn(const mxArray *c_ROIGeneralConfig_ROIMSIR_Diff,
  const char_T *identifier);
static const mxArray *n_emlrt_marshallOut(const int16_T u[4]);
static int16_T o_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static const mxArray *o_emlrt_marshallOut(const emxArray_int16_T *u);
static boolean_T p_emlrt_marshallIn(const mxArray
  *c_FaceDetectConfig_ROIFaceSecon, const char_T *identifier);
static const mxArray *p_emlrt_marshallOut(const emxArray_int32_T *u);
static boolean_T q_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static const mxArray *q_emlrt_marshallOut(const struct1_T *u);
static int32_T (*r_emlrt_marshallIn(const mxArray
  *c_ROIGeneralConfig_ROIFinalSmoo, const char_T *identifier))[2];
static int32_T (*s_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[2];
static void t_emlrt_marshallIn(const mxArray *VideoReadConfig_FrameIdx_FR, const
  char_T *identifier, emxArray_int32_T *y);
static void u_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int32_T *y);
static int32_T v_emlrt_marshallIn(const mxArray *RowToReturnFullLinIdx_FR, const
  char_T *identifier);
static int32_T w_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void x_emlrt_marshallIn(const mxArray *ROIMatchSizeData, const char_T
  *identifier, struct1_T *y);
static void y_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct1_T *y);

/* Function Definitions */
static real32_T ab_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  real32_T y;
  y = mb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void db_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int32_T *ret)
{
  static const int32_T dims[1] = { -1 };

  int32_T iv[1];
  int32_T i;
  const boolean_T bv[1] = { true };

  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int32", false, 1U,
    dims, &bv[0], iv);
  ret->allocatedSize = iv[0];
  i = ret->size[0];
  ret->size[0] = iv[0];
  emxEnsureCapacity_int32_T(ret, i);
  ret->data = (int32_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void e_emlrt_marshallIn(const mxArray *BlockFullLinIdx_In, const char_T
  *identifier, emxArray_int32_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(emlrtAlias(BlockFullLinIdx_In), &thisId, y);
  emlrtDestroyArray(&BlockFullLinIdx_In);
}

static void eb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int16_T *ret)
{
  static const int32_T dims[2] = { -1, 4 };

  int32_T iv[2];
  int32_T i;
  const boolean_T bv[2] = { true, false };

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

static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int32_T *y)
{
  db_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void fb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real32_T *ret)
{
  static const int32_T dims[1] = { -1 };

  int32_T iv[1];
  int32_T i;
  const boolean_T bv[1] = { true };

  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 1U,
    dims, &bv[0], iv);
  ret->allocatedSize = iv[0];
  i = ret->size[0];
  ret->size[0] = iv[0];
  emxEnsureCapacity_real32_T(ret, i);
  ret->data = (real32_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void g_emlrt_marshallIn(const mxArray *ROI, const char_T *identifier,
  emxArray_int16_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  h_emlrt_marshallIn(emlrtAlias(ROI), &thisId, y);
  emlrtDestroyArray(&ROI);
}

static void gb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_boolean_T *ret)
{
  static const int32_T dims[1] = { -1 };

  int32_T iv[1];
  int32_T i;
  const boolean_T bv[1] = { true };

  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "logical", false, 1U,
    dims, &bv[0], iv);
  i = ret->size[0];
  ret->size[0] = iv[0];
  emxEnsureCapacity_boolean_T(ret, i);
  emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, ret->data, 1, false);
  emlrtDestroyArray(&src);
}

static void h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int16_T *y)
{
  eb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int16_T hb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId)
{
  static const int32_T dims = 0;
  int16_T ret;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int16", false, 0U,
    &dims);
  ret = *(int16_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void i_emlrt_marshallIn(const mxArray *Timestamp, const char_T
  *identifier, emxArray_real32_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  j_emlrt_marshallIn(emlrtAlias(Timestamp), &thisId, y);
  emlrtDestroyArray(&Timestamp);
}

static boolean_T ib_emlrt_marshallIn(const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  boolean_T ret;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "logical", false, 0U,
    &dims);
  ret = *emlrtMxGetLogicals(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real32_T *y)
{
  fb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int32_T (*jb_emlrt_marshallIn(const mxArray *src, const
  emlrtMsgIdentifier *msgId))[2]
{
  static const int32_T dims[2] = { 1, 2 };

  int32_T (*ret)[2];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int32", false, 2U,
    dims);
  ret = (int32_T (*)[2])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static void k_emlrt_marshallIn(const mxArray *HasROI_TF, const char_T
  *identifier, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  l_emlrt_marshallIn(emlrtAlias(HasROI_TF), &thisId, y);
  emlrtDestroyArray(&HasROI_TF);
}

static void kb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int32_T *ret)
{
  static const int32_T dims[2] = { 1, -1 };

  int32_T iv[2];
  int32_T i;
  const boolean_T bv[2] = { false, true };

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

static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct0_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[20] = { "FacePrimary", "FacePrimaryAttempted",
    "SkinNotPresent_Pri", "ProfileEyesPresent_Pri", "FaceSecondary1",
    "FaceSecondary1Attempted", "SkinNotPresent_Sec1", "ProfileEyesPresent_Sec1",
    "FaceSecondary2", "FaceSecondary2Attempted", "SkinNotPresent_Sec2",
    "ProfileEyesPresent_Sec2", "Skipped", "Skin", "SkinAttempted",
    "SkinNotPresent_Skin", "Interpolated", "AdjustedBecauseLowSkinProportion",
    "ROISpecifiedByArgument", "ROIIgnoreByArgument" };

  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 20, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "FacePrimary";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 0,
    "FacePrimary")), &thisId, y->FacePrimary);
  thisId.fIdentifier = "FacePrimaryAttempted";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
    "FacePrimaryAttempted")), &thisId, y->FacePrimaryAttempted);
  thisId.fIdentifier = "SkinNotPresent_Pri";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 2,
    "SkinNotPresent_Pri")), &thisId, y->SkinNotPresent_Pri);
  thisId.fIdentifier = "ProfileEyesPresent_Pri";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 3,
    "ProfileEyesPresent_Pri")), &thisId, y->ProfileEyesPresent_Pri);
  thisId.fIdentifier = "FaceSecondary1";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 4,
    "FaceSecondary1")), &thisId, y->FaceSecondary1);
  thisId.fIdentifier = "FaceSecondary1Attempted";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 5,
    "FaceSecondary1Attempted")), &thisId, y->FaceSecondary1Attempted);
  thisId.fIdentifier = "SkinNotPresent_Sec1";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 6,
    "SkinNotPresent_Sec1")), &thisId, y->SkinNotPresent_Sec1);
  thisId.fIdentifier = "ProfileEyesPresent_Sec1";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 7,
    "ProfileEyesPresent_Sec1")), &thisId, y->ProfileEyesPresent_Sec1);
  thisId.fIdentifier = "FaceSecondary2";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 8,
    "FaceSecondary2")), &thisId, y->FaceSecondary2);
  thisId.fIdentifier = "FaceSecondary2Attempted";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 9,
    "FaceSecondary2Attempted")), &thisId, y->FaceSecondary2Attempted);
  thisId.fIdentifier = "SkinNotPresent_Sec2";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 10,
    "SkinNotPresent_Sec2")), &thisId, y->SkinNotPresent_Sec2);
  thisId.fIdentifier = "ProfileEyesPresent_Sec2";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 11,
    "ProfileEyesPresent_Sec2")), &thisId, y->ProfileEyesPresent_Sec2);
  thisId.fIdentifier = "Skipped";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 12,
    "Skipped")), &thisId, y->Skipped);
  thisId.fIdentifier = "Skin";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 13,
    "Skin")), &thisId, y->Skin);
  thisId.fIdentifier = "SkinAttempted";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 14,
    "SkinAttempted")), &thisId, y->SkinAttempted);
  thisId.fIdentifier = "SkinNotPresent_Skin";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 15,
    "SkinNotPresent_Skin")), &thisId, y->SkinNotPresent_Skin);
  thisId.fIdentifier = "Interpolated";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 16,
    "Interpolated")), &thisId, y->Interpolated);
  thisId.fIdentifier = "AdjustedBecauseLowSkinProportion";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 17,
    "AdjustedBecauseLowSkinProportion")), &thisId,
                     y->c_AdjustedBecauseLowSkinProport);
  thisId.fIdentifier = "ROISpecifiedByArgument";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 18,
    "ROISpecifiedByArgument")), &thisId, y->ROISpecifiedByArgument);
  thisId.fIdentifier = "ROIIgnoreByArgument";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 19,
    "ROIIgnoreByArgument")), &thisId, y->ROIIgnoreByArgument);
  emlrtDestroyArray(&u);
}

static int32_T lb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId)
{
  static const int32_T dims = 0;
  int32_T ret;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int32", false, 0U,
    &dims);
  ret = *(int32_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void m_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_boolean_T *y)
{
  gb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real32_T mb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId)
{
  static const int32_T dims = 0;
  real32_T ret;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 0U,
    &dims);
  ret = *(real32_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static int16_T n_emlrt_marshallIn(const mxArray *c_ROIGeneralConfig_ROIMSIR_Diff,
  const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  int16_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = o_emlrt_marshallIn(emlrtAlias(c_ROIGeneralConfig_ROIMSIR_Diff), &thisId);
  emlrtDestroyArray(&c_ROIGeneralConfig_ROIMSIR_Diff);
  return y;
}

static const mxArray *n_emlrt_marshallOut(const int16_T u[4])
{
  static const int32_T iv[2] = { 0, 0 };

  static const int32_T iv1[2] = { 1, 4 };

  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(2, &iv[0], mxINT16_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, iv1, 2);
  emlrtAssign(&y, m);
  return y;
}

static int16_T o_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  int16_T y;
  y = hb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *o_emlrt_marshallOut(const emxArray_int16_T *u)
{
  static const int32_T iv[2] = { 0, 0 };

  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(2, &iv[0], mxINT16_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &u->data[0]);
  emlrtSetDimensions((mxArray *)m, u->size, 2);
  emlrtAssign(&y, m);
  return y;
}

static boolean_T p_emlrt_marshallIn(const mxArray
  *c_FaceDetectConfig_ROIFaceSecon, const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  boolean_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = q_emlrt_marshallIn(emlrtAlias(c_FaceDetectConfig_ROIFaceSecon), &thisId);
  emlrtDestroyArray(&c_FaceDetectConfig_ROIFaceSecon);
  return y;
}

static const mxArray *p_emlrt_marshallOut(const emxArray_int32_T *u)
{
  static const int32_T iv[1] = { 0 };

  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(1, &iv[0], mxINT32_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &u->data[0]);
  emlrtSetDimensions((mxArray *)m, u->size, 1);
  emlrtAssign(&y, m);
  return y;
}

static boolean_T q_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  boolean_T y;
  y = ib_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *q_emlrt_marshallOut(const struct1_T *u)
{
  static const char_T *sv[20] = { "SumW_Pri", "SumH_Pri", "AlgN_Pri",
    "ROIMeanWidthPri", "ROIMeanHeightPri", "SumW_Sec1", "SumH_Sec1", "AlgN_Sec1",
    "ROIMeanWidthSec1", "ROIMeanHeightSec1", "SumW_Sec2", "SumH_Sec2",
    "AlgN_Sec2", "ROIMeanWidthSec2", "ROIMeanHeightSec2", "SumW_Skin",
    "SumH_Skin", "AlgN_Skin", "ROIMeanWidthSkin", "ROIMeanHeightSkin" };

  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *f_y;
  const mxArray *g_y;
  const mxArray *h_y;
  const mxArray *i_y;
  const mxArray *j_y;
  const mxArray *k_y;
  const mxArray *l_y;
  const mxArray *m;
  const mxArray *m_y;
  const mxArray *n_y;
  const mxArray *o_y;
  const mxArray *p_y;
  const mxArray *q_y;
  const mxArray *r_y;
  const mxArray *s_y;
  const mxArray *t_y;
  const mxArray *u_y;
  const mxArray *y;
  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 20, sv));
  b_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->SumW_Pri;
  emlrtAssign(&b_y, m);
  emlrtSetFieldR2017b(y, 0, "SumW_Pri", b_y, 0);
  c_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->SumH_Pri;
  emlrtAssign(&c_y, m);
  emlrtSetFieldR2017b(y, 0, "SumH_Pri", c_y, 1);
  d_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->AlgN_Pri;
  emlrtAssign(&d_y, m);
  emlrtSetFieldR2017b(y, 0, "AlgN_Pri", d_y, 2);
  e_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->ROIMeanWidthPri;
  emlrtAssign(&e_y, m);
  emlrtSetFieldR2017b(y, 0, "ROIMeanWidthPri", e_y, 3);
  f_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->ROIMeanHeightPri;
  emlrtAssign(&f_y, m);
  emlrtSetFieldR2017b(y, 0, "ROIMeanHeightPri", f_y, 4);
  g_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->SumW_Sec1;
  emlrtAssign(&g_y, m);
  emlrtSetFieldR2017b(y, 0, "SumW_Sec1", g_y, 5);
  h_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->SumH_Sec1;
  emlrtAssign(&h_y, m);
  emlrtSetFieldR2017b(y, 0, "SumH_Sec1", h_y, 6);
  i_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->AlgN_Sec1;
  emlrtAssign(&i_y, m);
  emlrtSetFieldR2017b(y, 0, "AlgN_Sec1", i_y, 7);
  j_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->ROIMeanWidthSec1;
  emlrtAssign(&j_y, m);
  emlrtSetFieldR2017b(y, 0, "ROIMeanWidthSec1", j_y, 8);
  k_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->ROIMeanHeightSec1;
  emlrtAssign(&k_y, m);
  emlrtSetFieldR2017b(y, 0, "ROIMeanHeightSec1", k_y, 9);
  l_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->SumW_Sec2;
  emlrtAssign(&l_y, m);
  emlrtSetFieldR2017b(y, 0, "SumW_Sec2", l_y, 10);
  m_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->SumH_Sec2;
  emlrtAssign(&m_y, m);
  emlrtSetFieldR2017b(y, 0, "SumH_Sec2", m_y, 11);
  n_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->AlgN_Sec2;
  emlrtAssign(&n_y, m);
  emlrtSetFieldR2017b(y, 0, "AlgN_Sec2", n_y, 12);
  o_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->ROIMeanWidthSec2;
  emlrtAssign(&o_y, m);
  emlrtSetFieldR2017b(y, 0, "ROIMeanWidthSec2", o_y, 13);
  p_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->ROIMeanHeightSec2;
  emlrtAssign(&p_y, m);
  emlrtSetFieldR2017b(y, 0, "ROIMeanHeightSec2", p_y, 14);
  q_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->SumW_Skin;
  emlrtAssign(&q_y, m);
  emlrtSetFieldR2017b(y, 0, "SumW_Skin", q_y, 15);
  r_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->SumH_Skin;
  emlrtAssign(&r_y, m);
  emlrtSetFieldR2017b(y, 0, "SumH_Skin", r_y, 16);
  s_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->AlgN_Skin;
  emlrtAssign(&s_y, m);
  emlrtSetFieldR2017b(y, 0, "AlgN_Skin", s_y, 17);
  t_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->ROIMeanWidthSkin;
  emlrtAssign(&t_y, m);
  emlrtSetFieldR2017b(y, 0, "ROIMeanWidthSkin", t_y, 18);
  u_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = u->ROIMeanHeightSkin;
  emlrtAssign(&u_y, m);
  emlrtSetFieldR2017b(y, 0, "ROIMeanHeightSkin", u_y, 19);
  return y;
}

static int32_T (*r_emlrt_marshallIn(const mxArray
  *c_ROIGeneralConfig_ROIFinalSmoo, const char_T *identifier))[2]
{
  emlrtMsgIdentifier thisId;
  int32_T (*y)[2];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = s_emlrt_marshallIn(emlrtAlias(c_ROIGeneralConfig_ROIFinalSmoo), &thisId);
  emlrtDestroyArray(&c_ROIGeneralConfig_ROIFinalSmoo);
  return y;
}
  static int32_T (*s_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[2]
{
  int32_T (*y)[2];
  y = jb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void t_emlrt_marshallIn(const mxArray *VideoReadConfig_FrameIdx_FR, const
  char_T *identifier, emxArray_int32_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  u_emlrt_marshallIn(emlrtAlias(VideoReadConfig_FrameIdx_FR), &thisId, y);
  emlrtDestroyArray(&VideoReadConfig_FrameIdx_FR);
}

static void u_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int32_T *y)
{
  kb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int32_T v_emlrt_marshallIn(const mxArray *RowToReturnFullLinIdx_FR, const
  char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  int32_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = w_emlrt_marshallIn(emlrtAlias(RowToReturnFullLinIdx_FR), &thisId);
  emlrtDestroyArray(&RowToReturnFullLinIdx_FR);
  return y;
}

static int32_T w_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  int32_T y;
  y = lb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void x_emlrt_marshallIn(const mxArray *ROIMatchSizeData, const char_T
  *identifier, struct1_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y_emlrt_marshallIn(emlrtAlias(ROIMatchSizeData), &thisId, y);
  emlrtDestroyArray(&ROIMatchSizeData);
}

static void y_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct1_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[20] = { "SumW_Pri", "SumH_Pri", "AlgN_Pri",
    "ROIMeanWidthPri", "ROIMeanHeightPri", "SumW_Sec1", "SumH_Sec1", "AlgN_Sec1",
    "ROIMeanWidthSec1", "ROIMeanHeightSec1", "SumW_Sec2", "SumH_Sec2",
    "AlgN_Sec2", "ROIMeanWidthSec2", "ROIMeanHeightSec2", "SumW_Skin",
    "SumH_Skin", "AlgN_Skin", "ROIMeanWidthSkin", "ROIMeanHeightSkin" };

  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 20, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "SumW_Pri";
  y->SumW_Pri = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 0, "SumW_Pri")), &thisId);
  thisId.fIdentifier = "SumH_Pri";
  y->SumH_Pri = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 1, "SumH_Pri")), &thisId);
  thisId.fIdentifier = "AlgN_Pri";
  y->AlgN_Pri = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 2, "AlgN_Pri")), &thisId);
  thisId.fIdentifier = "ROIMeanWidthPri";
  y->ROIMeanWidthPri = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 3, "ROIMeanWidthPri")), &thisId);
  thisId.fIdentifier = "ROIMeanHeightPri";
  y->ROIMeanHeightPri = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 4, "ROIMeanHeightPri")), &thisId);
  thisId.fIdentifier = "SumW_Sec1";
  y->SumW_Sec1 = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 5, "SumW_Sec1")), &thisId);
  thisId.fIdentifier = "SumH_Sec1";
  y->SumH_Sec1 = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 6, "SumH_Sec1")), &thisId);
  thisId.fIdentifier = "AlgN_Sec1";
  y->AlgN_Sec1 = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 7, "AlgN_Sec1")), &thisId);
  thisId.fIdentifier = "ROIMeanWidthSec1";
  y->ROIMeanWidthSec1 = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 8, "ROIMeanWidthSec1")), &thisId);
  thisId.fIdentifier = "ROIMeanHeightSec1";
  y->ROIMeanHeightSec1 = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 9, "ROIMeanHeightSec1")), &thisId);
  thisId.fIdentifier = "SumW_Sec2";
  y->SumW_Sec2 = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 10, "SumW_Sec2")), &thisId);
  thisId.fIdentifier = "SumH_Sec2";
  y->SumH_Sec2 = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 11, "SumH_Sec2")), &thisId);
  thisId.fIdentifier = "AlgN_Sec2";
  y->AlgN_Sec2 = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 12, "AlgN_Sec2")), &thisId);
  thisId.fIdentifier = "ROIMeanWidthSec2";
  y->ROIMeanWidthSec2 = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 13, "ROIMeanWidthSec2")), &thisId);
  thisId.fIdentifier = "ROIMeanHeightSec2";
  y->ROIMeanHeightSec2 = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 14, "ROIMeanHeightSec2")), &thisId);
  thisId.fIdentifier = "SumW_Skin";
  y->SumW_Skin = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 15, "SumW_Skin")), &thisId);
  thisId.fIdentifier = "SumH_Skin";
  y->SumH_Skin = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 16, "SumH_Skin")), &thisId);
  thisId.fIdentifier = "AlgN_Skin";
  y->AlgN_Skin = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 17, "AlgN_Skin")), &thisId);
  thisId.fIdentifier = "ROIMeanWidthSkin";
  y->ROIMeanWidthSkin = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 18, "ROIMeanWidthSkin")), &thisId);
  thisId.fIdentifier = "ROIMeanHeightSkin";
  y->ROIMeanHeightSkin = ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 19, "ROIMeanHeightSkin")), &thisId);
  emlrtDestroyArray(&u);
}

void ROIMSIR_api(const mxArray * const prhs[25], int32_T nlhs, const mxArray
                 *plhs[8])
{
  emxArray_int16_T *ROI;
  emxArray_int16_T *ROINoMods;
  emxArray_int16_T *ROINoResize;
  emxArray_int16_T *ROIOut_SR;
  emxArray_int16_T *d_ROIOutBeforeFrameByFrameSmoot;
  emxArray_int32_T *BlockFullLinIdx_In;
  emxArray_int32_T *InterpolatedLinIdx_SR;
  emxArray_int32_T *VideoReadConfig_FrameIdx_FR;
  emxArray_real32_T *Timestamp;
  const mxArray *prhs_copy_idx_1;
  const mxArray *prhs_copy_idx_18;
  const mxArray *prhs_copy_idx_2;
  const mxArray *prhs_copy_idx_21;
  const mxArray *prhs_copy_idx_22;
  struct0_T HasROI_TF;
  struct0_T b_HasROI_TF;
  struct1_T ROIMatchSizeData;
  real_T c_FaceDetectConfig_ROIFaceSmoot;
  real_T c_ROIGeneralConfig_ROIHeightRes;
  real_T c_ROIGeneralConfig_ROIWidthResi;
  real_T c_SkinDetectConfig_ROISkinSmoot;
  int32_T (*c_ROIGeneralConfig_ROIFinalSmoo)[2];
  int32_T InterpolatedLinIdx_FR;
  int32_T ROIMSIR_FirstFrameLinIdx_FR;
  int32_T RowToReturnFullLinIdx_FR;
  int16_T (*ROIOutNoResize_FR)[4];
  int16_T (*ROIOut_FR)[4];
  int16_T (*c_ROIOutBeforeFrameByFrameSmoot)[4];
  int16_T VidObjHeight;
  int16_T VidObjWidth;
  int16_T c_ROIGeneralConfig_ROIMSIR_Diff;
  int16_T d_ROIGeneralConfig_ROIMSIR_Diff;
  boolean_T ExpectedBehaviorTestTF;
  boolean_T FirstCallTF;
  boolean_T FirstReadTF;
  boolean_T SecondReadPostProcessingTF;
  boolean_T c_FaceDetectConfig_ROIFaceSecon;
  boolean_T d_FaceDetectConfig_ROIFaceSecon;
  ROIOut_FR = (int16_T (*)[4])mxMalloc(sizeof(int16_T [4]));
  c_ROIOutBeforeFrameByFrameSmoot = (int16_T (*)[4])mxMalloc(sizeof(int16_T [4]));
  ROIOutNoResize_FR = (int16_T (*)[4])mxMalloc(sizeof(int16_T [4]));
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_int32_T(&BlockFullLinIdx_In, 1, true);
  emxInit_int16_T(&ROI, 2, true);
  emxInit_real32_T(&Timestamp, 1, true);
  emxInitStruct_struct0_T(&HasROI_TF, true);
  emxInit_int32_T(&VideoReadConfig_FrameIdx_FR, 2, true);
  emxInit_int16_T(&ROINoMods, 2, true);
  emxInit_int16_T(&ROINoResize, 2, true);
  emxInit_int16_T(&ROIOut_SR, 2, true);
  emxInit_int32_T(&InterpolatedLinIdx_SR, 1, true);
  emxInit_int16_T(&d_ROIOutBeforeFrameByFrameSmoot, 2, true);
  prhs_copy_idx_1 = emlrtProtectR2012b(prhs[1], 1, false, -1);
  prhs_copy_idx_2 = emlrtProtectR2012b(prhs[2], 2, false, -1);
  prhs_copy_idx_18 = emlrtProtectR2012b(prhs[18], 18, false, -1);
  prhs_copy_idx_21 = emlrtProtectR2012b(prhs[21], 21, false, -1);
  prhs_copy_idx_22 = emlrtProtectR2012b(prhs[22], 22, false, -1);

  /* Marshall function inputs */
  BlockFullLinIdx_In->canFreeData = false;
  e_emlrt_marshallIn(emlrtAlias(prhs[0]), "BlockFullLinIdx_In",
                     BlockFullLinIdx_In);
  ROI->canFreeData = false;
  g_emlrt_marshallIn(emlrtAlias(prhs_copy_idx_1), "ROI", ROI);
  Timestamp->canFreeData = false;
  i_emlrt_marshallIn(emlrtAlias(prhs_copy_idx_2), "Timestamp", Timestamp);
  k_emlrt_marshallIn(emlrtAliasP(prhs[3]), "HasROI_TF", &HasROI_TF);
  c_ROIGeneralConfig_ROIMSIR_Diff = n_emlrt_marshallIn(emlrtAliasP(prhs[4]),
    "ROIGeneralConfig_ROIMSIR_DiffMaxDetection");
  d_ROIGeneralConfig_ROIMSIR_Diff = n_emlrt_marshallIn(emlrtAliasP(prhs[5]),
    "ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent");
  c_ROIGeneralConfig_ROIWidthResi = emlrt_marshallIn(emlrtAliasP(prhs[6]),
    "ROIGeneralConfig_ROIWidthResizeFactor");
  c_ROIGeneralConfig_ROIHeightRes = emlrt_marshallIn(emlrtAliasP(prhs[7]),
    "ROIGeneralConfig_ROIHeightResizeFactor");
  c_FaceDetectConfig_ROIFaceSmoot = emlrt_marshallIn(emlrtAliasP(prhs[8]),
    "FaceDetectConfig_ROIFaceSmoothingWindow");
  c_FaceDetectConfig_ROIFaceSecon = p_emlrt_marshallIn(emlrtAliasP(prhs[9]),
    "FaceDetectConfig_ROIFaceSecondary1TF");
  d_FaceDetectConfig_ROIFaceSecon = p_emlrt_marshallIn(emlrtAliasP(prhs[10]),
    "FaceDetectConfig_ROIFaceSecondary2TF");
  c_SkinDetectConfig_ROISkinSmoot = emlrt_marshallIn(emlrtAliasP(prhs[11]),
    "SkinDetectConfig_ROISkinSmoothingWindow");
  c_ROIGeneralConfig_ROIFinalSmoo = r_emlrt_marshallIn(emlrtAlias(prhs[12]),
    "ROIGeneralConfig_ROIFinalSmoothingWindows");
  VidObjWidth = n_emlrt_marshallIn(emlrtAliasP(prhs[13]), "VidObjWidth");
  VidObjHeight = n_emlrt_marshallIn(emlrtAliasP(prhs[14]), "VidObjHeight");
  ExpectedBehaviorTestTF = p_emlrt_marshallIn(emlrtAliasP(prhs[15]),
    "ExpectedBehaviorTestTF");
  FirstReadTF = p_emlrt_marshallIn(emlrtAliasP(prhs[16]), "FirstReadTF");
  FirstCallTF = p_emlrt_marshallIn(emlrtAliasP(prhs[17]), "FirstCallTF");
  VideoReadConfig_FrameIdx_FR->canFreeData = false;
  t_emlrt_marshallIn(emlrtAlias(prhs_copy_idx_18), "VideoReadConfig_FrameIdx_FR",
                     VideoReadConfig_FrameIdx_FR);
  RowToReturnFullLinIdx_FR = v_emlrt_marshallIn(emlrtAliasP(prhs[19]),
    "RowToReturnFullLinIdx_FR");
  ROIMSIR_FirstFrameLinIdx_FR = v_emlrt_marshallIn(emlrtAliasP(prhs[20]),
    "ROIMSIR_FirstFrameLinIdx_FR");
  ROINoMods->canFreeData = false;
  g_emlrt_marshallIn(emlrtAlias(prhs_copy_idx_21), "ROINoMods", ROINoMods);
  ROINoResize->canFreeData = false;
  g_emlrt_marshallIn(emlrtAlias(prhs_copy_idx_22), "ROINoResize", ROINoResize);
  x_emlrt_marshallIn(emlrtAliasP(prhs[23]), "ROIMatchSizeData",
                     &ROIMatchSizeData);
  SecondReadPostProcessingTF = p_emlrt_marshallIn(emlrtAliasP(prhs[24]),
    "SecondReadPostProcessingTF");

  /* Invoke the target function */
  b_HasROI_TF = HasROI_TF;
  ROIMSIR(BlockFullLinIdx_In, ROI, Timestamp, &b_HasROI_TF,
          c_ROIGeneralConfig_ROIMSIR_Diff, d_ROIGeneralConfig_ROIMSIR_Diff,
          c_ROIGeneralConfig_ROIWidthResi, c_ROIGeneralConfig_ROIHeightRes,
          c_FaceDetectConfig_ROIFaceSmoot, c_FaceDetectConfig_ROIFaceSecon,
          d_FaceDetectConfig_ROIFaceSecon, c_SkinDetectConfig_ROISkinSmoot,
          *c_ROIGeneralConfig_ROIFinalSmoo, VidObjWidth, VidObjHeight,
          ExpectedBehaviorTestTF, FirstReadTF, FirstCallTF,
          VideoReadConfig_FrameIdx_FR, RowToReturnFullLinIdx_FR,
          ROIMSIR_FirstFrameLinIdx_FR, ROINoMods, ROINoResize, &ROIMatchSizeData,
          SecondReadPostProcessingTF, *ROIOut_FR, ROIOut_SR,
          &InterpolatedLinIdx_FR, InterpolatedLinIdx_SR,
          *c_ROIOutBeforeFrameByFrameSmoot, d_ROIOutBeforeFrameByFrameSmoot,
          *ROIOutNoResize_FR);

  /* Marshall function outputs */
  plhs[0] = n_emlrt_marshallOut(*ROIOut_FR);
  emxFree_int16_T(&ROINoResize);
  emxFree_int16_T(&ROINoMods);
  emxFree_int32_T(&VideoReadConfig_FrameIdx_FR);
  emxFreeStruct_struct0_T(&HasROI_TF);
  emxFree_real32_T(&Timestamp);
  emxFree_int16_T(&ROI);
  emxFree_int32_T(&BlockFullLinIdx_In);
  if (nlhs > 1) {
    ROIOut_SR->canFreeData = false;
    plhs[1] = o_emlrt_marshallOut(ROIOut_SR);
  }

  emxFree_int16_T(&ROIOut_SR);
  if (nlhs > 2) {
    plhs[2] = d_emlrt_marshallOut(InterpolatedLinIdx_FR);
  }

  if (nlhs > 3) {
    InterpolatedLinIdx_SR->canFreeData = false;
    plhs[3] = p_emlrt_marshallOut(InterpolatedLinIdx_SR);
  }

  emxFree_int32_T(&InterpolatedLinIdx_SR);
  if (nlhs > 4) {
    plhs[4] = n_emlrt_marshallOut(*c_ROIOutBeforeFrameByFrameSmoot);
  }

  if (nlhs > 5) {
    d_ROIOutBeforeFrameByFrameSmoot->canFreeData = false;
    plhs[5] = o_emlrt_marshallOut(d_ROIOutBeforeFrameByFrameSmoot);
  }

  emxFree_int16_T(&d_ROIOutBeforeFrameByFrameSmoot);
  if (nlhs > 6) {
    plhs[6] = n_emlrt_marshallOut(*ROIOutNoResize_FR);
  }

  if (nlhs > 7) {
    plhs[7] = q_emlrt_marshallOut(&ROIMatchSizeData);
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_ROIMSIR_api.c) */
