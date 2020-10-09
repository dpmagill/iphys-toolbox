/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_SkinDetect_api.c
 *
 * Code generation for function '_coder_SkinDetect_api'
 *
 */

/* Include files */
#include "_coder_SkinDetect_api.h"
#include "SkinDetect.h"
#include "SkinDetect_data.h"
#include "SkinDetect_emxutil.h"
#include "SkinDetect_types.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void ab_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real_T *y);
static void ac_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[2]);
static int32_T b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void bb_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real_T *y);
static real32_T bc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static void c_emlrt_marshallIn(const mxArray *VidFrame, const char_T *identifier,
  emxArray_uint8_T *y);
static const mxArray *c_emlrt_marshallOut(const int16_T u_data[], const int32_T
  u_size[2]);
static void cb_emlrt_marshallIn(const mxArray *SkinDetectConfig, const char_T
  *identifier, struct6_T *y);
static void cc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[9]);
static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y);
static const mxArray *d_emlrt_marshallOut(const boolean_T u);
static void db_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct6_T *y);
static void dc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, int32_T ret[2]);
static int16_T e_emlrt_marshallIn(const mxArray *VideoReadConfig_VidObjWidth,
  const char_T *identifier);
static const mxArray *e_emlrt_marshallOut(const struct8_T *u);
static void eb_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct7_T *y);
static void ec_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real_T *ret);
static int32_T emlrt_marshallIn(const mxArray *i, const char_T *identifier);
static int16_T f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static const mxArray *f_emlrt_marshallOut(const int16_T u_data[], const int32_T
  u_size[2]);
static void fb_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[4]);
static void fc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real_T *ret);
static void g_emlrt_marshallIn(const mxArray *SkinSegmentConfig, const char_T
  *identifier, struct0_T *y);
static const mxArray *g_emlrt_marshallOut(const uint8_T u_data[], const int32_T
  u_size[2]);
static boolean_T gb_emlrt_marshallIn(const mxArray
  *c_OutputConfig_WriteVideoShowRO, const char_T *identifier);
static void gc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[4]);
static void h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct0_T *y);
static const mxArray *h_emlrt_marshallOut(const real32_T u_data[], const int32_T
  u_size[2]);
static int16_T (*hb_emlrt_marshallIn(const mxArray *BoundingBoxSkin, const
  char_T *identifier))[4];
static int16_T (*hc_emlrt_marshallIn(const mxArray *src, const
  emlrtMsgIdentifier *msgId))[4];
static boolean_T i_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static const mxArray *i_emlrt_marshallOut(const real32_T u_data[], const int32_T
  u_size[2]);
static int16_T (*ib_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[4];
static void ic_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, int16_T **ret_data, int32_T ret_size[2]);
static real_T j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static const mxArray *j_emlrt_marshallOut(const emxArray_uint32_T *u);
static void jb_emlrt_marshallIn(const mxArray *ROI_SR_ith, const char_T
  *identifier, int16_T **y_data, int32_T y_size[2]);
static void jc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_int32_T *ret);
static void k_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct1_T *y);
static const mxArray *k_emlrt_marshallOut(const uint32_T u);
static void kb_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, int16_T **y_data, int32_T y_size[2]);
static uint64_T kc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[7]);
static void lb_emlrt_marshallIn(const mxArray *FramesToProcessLinIdx_SR, const
  char_T *identifier, emxArray_int32_T *y);
static void m_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[2]);
static void mb_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int32_T *y);
static void n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[8]);
static uint64_T nb_emlrt_marshallIn(const mxArray
  *Notifications_LoopStartTime_SR, const char_T *identifier);
static void o_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[3]);
static uint64_T ob_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static uint8_T p_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static int32_T pb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);
static void q_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct2_T *y);
static void qb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret);
static void r_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[2]);
static int16_T rb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);
static struct3_T s_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static boolean_T sb_emlrt_marshallIn(const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real32_T t_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static real_T tb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static void u_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct4_T *y);
static void ub_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[7]);
static void v_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[9]);
static void vb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[2]);
static void w_emlrt_marshallIn(const mxArray *ROIGeneralConfig, const char_T
  *identifier, struct5_T *y);
static void wb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[8]);
static void x_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct5_T *y);
static void xb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[3]);
static void y_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, int32_T y[2]);
static uint8_T yb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId);

/* Function Definitions */
static void ab_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real_T *y)
{
  ec_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void ac_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[2])
{
  static const int32_T dims[2] = { 1, 2 };

  real_T (*r)[2];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 2U,
    dims);
  r = (real_T (*)[2])emlrtMxGetData(src);
  ret[0] = (*r)[0];
  ret[1] = (*r)[1];
  emlrtDestroyArray(&src);
}

static int32_T b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  int32_T y;
  y = pb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void bb_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real_T *y)
{
  fc_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real32_T bc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static void c_emlrt_marshallIn(const mxArray *VidFrame, const char_T *identifier,
  emxArray_uint8_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(emlrtAlias(VidFrame), &thisId, y);
  emlrtDestroyArray(&VidFrame);
}

static const mxArray *c_emlrt_marshallOut(const int16_T u_data[], const int32_T
  u_size[2])
{
  static const int32_T iv[2] = { 0, 0 };

  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(2, &iv[0], mxINT16_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m, u_size, 2);
  emlrtAssign(&y, m);
  return y;
}

static void cb_emlrt_marshallIn(const mxArray *SkinDetectConfig, const char_T
  *identifier, struct6_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  db_emlrt_marshallIn(emlrtAlias(SkinDetectConfig), &thisId, y);
  emlrtDestroyArray(&SkinDetectConfig);
}

static void cc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[9])
{
  static const int32_T dims[2] = { 1, 9 };

  int32_T i;
  real32_T (*r)[9];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 2U,
    dims);
  r = (real32_T (*)[9])emlrtMxGetData(src);
  for (i = 0; i < 9; i++) {
    ret[i] = (*r)[i];
  }

  emlrtDestroyArray(&src);
}

static void d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_uint8_T *y)
{
  qb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *d_emlrt_marshallOut(const boolean_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateLogicalScalar(u);
  emlrtAssign(&y, m);
  return y;
}

static void db_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct6_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[15] = { "ROISkinTF", "Thresholds",
    "ROISkinSkipFrameThreshold", "ROISkin_BoundingBoxGrowthThreshold",
    "ROISkin_BoundingBoxGrowthFactor", "ROISkin_InitialBoundingBoxScale",
    "ROISkinRegionMinSizeFactor", "ROISkinRegionProximityWeight",
    "ROISkinSmoothingWindow", "PartitionColInterval", "PartitionRowInterval",
    "SkinDetectionReadyTF", "ROISkin_BoundingBoxEnlargementFactor",
    "ROISkinSkipFrameThreshold_adjusted", "UseCompiledFunctionsTF" };

  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 15, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "ROISkinTF";
  y->ROISkinTF = i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 0, "ROISkinTF")), &thisId);
  thisId.fIdentifier = "Thresholds";
  eb_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
    "Thresholds")), &thisId, &y->Thresholds);
  thisId.fIdentifier = "ROISkinSkipFrameThreshold";
  y->ROISkinSkipFrameThreshold = b_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 2,
    "ROISkinSkipFrameThreshold")), &thisId);
  thisId.fIdentifier = "ROISkin_BoundingBoxGrowthThreshold";
  y->c_ROISkin_BoundingBoxGrowthThre = b_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 3,
    "ROISkin_BoundingBoxGrowthThreshold")), &thisId);
  thisId.fIdentifier = "ROISkin_BoundingBoxGrowthFactor";
  y->ROISkin_BoundingBoxGrowthFactor = j_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 4,
    "ROISkin_BoundingBoxGrowthFactor")), &thisId);
  thisId.fIdentifier = "ROISkin_InitialBoundingBoxScale";
  y->ROISkin_InitialBoundingBoxScale = j_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 5,
    "ROISkin_InitialBoundingBoxScale")), &thisId);
  thisId.fIdentifier = "ROISkinRegionMinSizeFactor";
  y->ROISkinRegionMinSizeFactor = t_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 6,
    "ROISkinRegionMinSizeFactor")), &thisId);
  thisId.fIdentifier = "ROISkinRegionProximityWeight";
  y->ROISkinRegionProximityWeight = j_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 7,
    "ROISkinRegionProximityWeight")), &thisId);
  thisId.fIdentifier = "ROISkinSmoothingWindow";
  y->ROISkinSmoothingWindow = j_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 8, "ROISkinSmoothingWindow")), &thisId);
  thisId.fIdentifier = "PartitionColInterval";
  y->PartitionColInterval = f_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 9, "PartitionColInterval")), &thisId);
  thisId.fIdentifier = "PartitionRowInterval";
  y->PartitionRowInterval = f_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 10, "PartitionRowInterval")), &thisId);
  thisId.fIdentifier = "SkinDetectionReadyTF";
  y->SkinDetectionReadyTF = i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 11, "SkinDetectionReadyTF")), &thisId);
  thisId.fIdentifier = "ROISkin_BoundingBoxEnlargementFactor";
  y->c_ROISkin_BoundingBoxEnlargemen = j_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 12,
    "ROISkin_BoundingBoxEnlargementFactor")), &thisId);
  thisId.fIdentifier = "ROISkinSkipFrameThreshold_adjusted";
  y->c_ROISkinSkipFrameThreshold_adj = b_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 13,
    "ROISkinSkipFrameThreshold_adjusted")), &thisId);
  thisId.fIdentifier = "UseCompiledFunctionsTF";
  y->UseCompiledFunctionsTF = i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 14, "UseCompiledFunctionsTF")), &thisId);
  emlrtDestroyArray(&u);
}

static void dc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, int32_T ret[2])
{
  static const int32_T dims[2] = { 1, 2 };

  int32_T (*r)[2];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int32", false, 2U,
    dims);
  r = (int32_T (*)[2])emlrtMxGetData(src);
  ret[0] = (*r)[0];
  ret[1] = (*r)[1];
  emlrtDestroyArray(&src);
}

static int16_T e_emlrt_marshallIn(const mxArray *VideoReadConfig_VidObjWidth,
  const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  int16_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(emlrtAlias(VideoReadConfig_VidObjWidth), &thisId);
  emlrtDestroyArray(&VideoReadConfig_VidObjWidth);
  return y;
}

static const mxArray *e_emlrt_marshallOut(const struct8_T *u)
{
  static const char_T *sv[22] = { "RegionSkinROIAttempted", "BBox_Scan_SkinAlg",
    "RegionAnyAvailable", "RegionNPixels_RejectedN",
    "RegionNPixels_RejectedLowNTF", "RegionCentroids_SelectedXY",
    "RegionCentroids_CandidateXY", "RegionCentroids_RejectedXY",
    "PredictedROI_center", "RegionScores_SelectedRGBProb",
    "RegionScores_CandidateRGBProb", "RegionScores_RejectedRGBProb",
    "RegionScores_SelectedYCbCrZ", "RegionScores_CandidateYCbCrZ",
    "RegionScores_RejectedYCbCrZ", "RegionRankings_CandidateHi2Lo",
    "RegionCrSDScores_RejectedCrSDLinIdx", "RegionCrSDScores_RejectedCrSD",
    "ProportionSkinPixelsTooLow", "RegionBoundaries_SelectedLinIdx",
    "RegionBoundaries_CandidateLinIdx", "RegionBoundaries_RejectedLinIdx" };

  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *f_y;
  const mxArray *g_y;
  const mxArray *h_y;
  const mxArray *i_y;
  const mxArray *m;
  const mxArray *y;
  int32_T iv[2];
  int32_T b_i;
  int32_T c_i;
  int32_T i;
  real32_T *e_pData;
  uint32_T *b_pData;
  int16_T *c_pData;
  uint16_T *pData;
  uint8_T *d_pData;
  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 22, sv));
  emlrtSetFieldR2017b(y, 0, "RegionSkinROIAttempted", d_emlrt_marshallOut
                      (u->RegionSkinROIAttempted), 0);
  b_y = NULL;
  iv[0] = u->BBox_Scan_SkinAlg.size[0];
  iv[1] = u->BBox_Scan_SkinAlg.size[1];
  m = emlrtCreateNumericArray(2, &iv[0], mxUINT16_CLASS, mxREAL);
  pData = (uint16_T *)emlrtMxGetData(m);
  i = 0;
  for (b_i = 0; b_i < u->BBox_Scan_SkinAlg.size[1]; b_i++) {
    c_i = 0;
    while (c_i < u->BBox_Scan_SkinAlg.size[0]) {
      pData[i] = u->BBox_Scan_SkinAlg.data[u->BBox_Scan_SkinAlg.size[0] * b_i];
      i++;
      c_i = 1;
    }
  }

  emlrtAssign(&b_y, m);
  emlrtSetFieldR2017b(y, 0, "BBox_Scan_SkinAlg", b_y, 1);
  emlrtSetFieldR2017b(y, 0, "RegionAnyAvailable", d_emlrt_marshallOut
                      (u->RegionAnyAvailable), 2);
  c_y = NULL;
  iv[0] = u->RegionNPixels_RejectedN.size[0];
  iv[1] = u->RegionNPixels_RejectedN.size[1];
  m = emlrtCreateNumericArray(2, &iv[0], mxUINT32_CLASS, mxREAL);
  b_pData = (uint32_T *)emlrtMxGetData(m);
  i = 0;
  b_i = 0;
  while (b_i < u->RegionNPixels_RejectedN.size[1]) {
    for (b_i = 0; b_i < u->RegionNPixels_RejectedN.size[0]; b_i++) {
      b_pData[i] = u->RegionNPixels_RejectedN.data[b_i];
      i++;
    }

    b_i = 1;
  }

  emlrtAssign(&c_y, m);
  emlrtSetFieldR2017b(y, 0, "RegionNPixels_RejectedN", c_y, 3);
  d_y = NULL;
  iv[0] = u->RegionNPixels_RejectedLowNTF.size[0];
  iv[1] = u->RegionNPixels_RejectedLowNTF.size[1];
  m = emlrtCreateLogicalArray(2, &iv[0]);
  emlrtInitLogicalArray(u->RegionNPixels_RejectedLowNTF.size[0] *
                        u->RegionNPixels_RejectedLowNTF.size[1], m,
                        &u->RegionNPixels_RejectedLowNTF.data[0]);
  emlrtAssign(&d_y, m);
  emlrtSetFieldR2017b(y, 0, "RegionNPixels_RejectedLowNTF", d_y, 4);
  e_y = NULL;
  iv[0] = u->RegionCentroids_SelectedXY.size[0];
  iv[1] = u->RegionCentroids_SelectedXY.size[1];
  m = emlrtCreateNumericArray(2, &iv[0], mxINT16_CLASS, mxREAL);
  c_pData = (int16_T *)emlrtMxGetData(m);
  i = 0;
  for (b_i = 0; b_i < u->RegionCentroids_SelectedXY.size[1]; b_i++) {
    c_i = 0;
    while (c_i < u->RegionCentroids_SelectedXY.size[0]) {
      c_pData[i] = u->RegionCentroids_SelectedXY.data
        [u->RegionCentroids_SelectedXY.size[0] * b_i];
      i++;
      c_i = 1;
    }
  }

  emlrtAssign(&e_y, m);
  emlrtSetFieldR2017b(y, 0, "RegionCentroids_SelectedXY", e_y, 5);
  emlrtSetFieldR2017b(y, 0, "RegionCentroids_CandidateXY", f_emlrt_marshallOut
                      (u->RegionCentroids_CandidateXY.data,
                       u->RegionCentroids_CandidateXY.size), 6);
  emlrtSetFieldR2017b(y, 0, "RegionCentroids_RejectedXY", f_emlrt_marshallOut
                      (u->RegionCentroids_RejectedXY.data,
                       u->RegionCentroids_RejectedXY.size), 7);
  f_y = NULL;
  iv[0] = u->PredictedROI_center.size[0];
  iv[1] = u->PredictedROI_center.size[1];
  m = emlrtCreateNumericArray(2, &iv[0], mxUINT16_CLASS, mxREAL);
  pData = (uint16_T *)emlrtMxGetData(m);
  i = 0;
  for (b_i = 0; b_i < u->PredictedROI_center.size[1]; b_i++) {
    c_i = 0;
    while (c_i < u->PredictedROI_center.size[0]) {
      pData[i] = u->PredictedROI_center.data[u->PredictedROI_center.size[0] *
        b_i];
      i++;
      c_i = 1;
    }
  }

  emlrtAssign(&f_y, m);
  emlrtSetFieldR2017b(y, 0, "PredictedROI_center", f_y, 8);
  g_y = NULL;
  iv[0] = u->RegionScores_SelectedRGBProb.size[0];
  iv[1] = u->RegionScores_SelectedRGBProb.size[1];
  m = emlrtCreateNumericArray(2, &iv[0], mxUINT8_CLASS, mxREAL);
  d_pData = (uint8_T *)emlrtMxGetData(m);
  i = 0;
  b_i = 0;
  while (b_i < u->RegionScores_SelectedRGBProb.size[1]) {
    b_i = 0;
    while (b_i < u->RegionScores_SelectedRGBProb.size[0]) {
      d_pData[i] = u->RegionScores_SelectedRGBProb.data[0];
      i++;
      b_i = 1;
    }

    b_i = 1;
  }

  emlrtAssign(&g_y, m);
  emlrtSetFieldR2017b(y, 0, "RegionScores_SelectedRGBProb", g_y, 9);
  emlrtSetFieldR2017b(y, 0, "RegionScores_CandidateRGBProb", g_emlrt_marshallOut
                      (u->RegionScores_CandidateRGBProb.data,
                       u->RegionScores_CandidateRGBProb.size), 10);
  emlrtSetFieldR2017b(y, 0, "RegionScores_RejectedRGBProb", g_emlrt_marshallOut
                      (u->RegionScores_RejectedRGBProb.data,
                       u->RegionScores_RejectedRGBProb.size), 11);
  h_y = NULL;
  iv[0] = u->RegionScores_SelectedYCbCrZ.size[0];
  iv[1] = u->RegionScores_SelectedYCbCrZ.size[1];
  m = emlrtCreateNumericArray(2, &iv[0], mxSINGLE_CLASS, mxREAL);
  e_pData = (real32_T *)emlrtMxGetData(m);
  i = 0;
  for (b_i = 0; b_i < u->RegionScores_SelectedYCbCrZ.size[1]; b_i++) {
    c_i = 0;
    while (c_i < u->RegionScores_SelectedYCbCrZ.size[0]) {
      e_pData[i] = u->RegionScores_SelectedYCbCrZ.data
        [u->RegionScores_SelectedYCbCrZ.size[0] * b_i];
      i++;
      c_i = 1;
    }
  }

  emlrtAssign(&h_y, m);
  emlrtSetFieldR2017b(y, 0, "RegionScores_SelectedYCbCrZ", h_y, 12);
  emlrtSetFieldR2017b(y, 0, "RegionScores_CandidateYCbCrZ", h_emlrt_marshallOut
                      (u->RegionScores_CandidateYCbCrZ.data,
                       u->RegionScores_CandidateYCbCrZ.size), 13);
  emlrtSetFieldR2017b(y, 0, "RegionScores_RejectedYCbCrZ", h_emlrt_marshallOut
                      (u->RegionScores_RejectedYCbCrZ.data,
                       u->RegionScores_RejectedYCbCrZ.size), 14);
  emlrtSetFieldR2017b(y, 0, "RegionRankings_CandidateHi2Lo", i_emlrt_marshallOut
                      (u->RegionRankings_CandidateHi2Lo.data,
                       u->RegionRankings_CandidateHi2Lo.size), 15);
  i_y = NULL;
  iv[0] = u->c_RegionCrSDScores_RejectedCrSD.size[0];
  iv[1] = u->c_RegionCrSDScores_RejectedCrSD.size[1];
  m = emlrtCreateNumericArray(2, &iv[0], mxUINT16_CLASS, mxREAL);
  pData = (uint16_T *)emlrtMxGetData(m);
  i = 0;
  b_i = 0;
  while (b_i < u->c_RegionCrSDScores_RejectedCrSD.size[1]) {
    for (b_i = 0; b_i < u->c_RegionCrSDScores_RejectedCrSD.size[0]; b_i++) {
      pData[i] = u->c_RegionCrSDScores_RejectedCrSD.data[b_i];
      i++;
    }

    b_i = 1;
  }

  emlrtAssign(&i_y, m);
  emlrtSetFieldR2017b(y, 0, "RegionCrSDScores_RejectedCrSDLinIdx", i_y, 16);
  emlrtSetFieldR2017b(y, 0, "RegionCrSDScores_RejectedCrSD", i_emlrt_marshallOut
                      (u->RegionCrSDScores_RejectedCrSD.data,
                       u->RegionCrSDScores_RejectedCrSD.size), 17);
  emlrtSetFieldR2017b(y, 0, "ProportionSkinPixelsTooLow", d_emlrt_marshallOut
                      (u->ProportionSkinPixelsTooLow), 18);
  emlrtSetFieldR2017b(y, 0, "RegionBoundaries_SelectedLinIdx",
                      j_emlrt_marshallOut(u->RegionBoundaries_SelectedLinIdx),
                      19);
  emlrtSetFieldR2017b(y, 0, "RegionBoundaries_CandidateLinIdx",
                      j_emlrt_marshallOut(u->c_RegionBoundaries_CandidateLin),
                      20);
  emlrtSetFieldR2017b(y, 0, "RegionBoundaries_RejectedLinIdx",
                      j_emlrt_marshallOut(u->RegionBoundaries_RejectedLinIdx),
                      21);
  return y;
}

static void eb_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct7_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[16] = { "SetTF", "SkinColorSamples_NThreshold",
    "SkinColorSamples_NThresholdPassedTF", "SkinColorSamples_HighNThreshold",
    "SkinColorSamples_HighNThresholdPassedTF",
    "SkinColorSamples_HighNThresholdIdx", "ColorThreshold",
    "ColorThresholdHighN", "RecentThresholdOpsFrameIdx", "ThresholdOpsInterval",
    "ThresholdOpsRunCurrentFrameTF", "ColorSDThreshold", "RGBProbTheta",
    "YCbCrMeanOfMeans", "YCbCrStdDevOfMeans", "RegionNThreshold" };

  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 16, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "SetTF";
  y->SetTF = i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 0, "SetTF")), &thisId);
  thisId.fIdentifier = "SkinColorSamples_NThreshold";
  y->SkinColorSamples_NThreshold = j_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
    "SkinColorSamples_NThreshold")), &thisId);
  thisId.fIdentifier = "SkinColorSamples_NThresholdPassedTF";
  y->c_SkinColorSamples_NThresholdPa = i_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 2,
    "SkinColorSamples_NThresholdPassedTF")), &thisId);
  thisId.fIdentifier = "SkinColorSamples_HighNThreshold";
  y->SkinColorSamples_HighNThreshold = j_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 3,
    "SkinColorSamples_HighNThreshold")), &thisId);
  thisId.fIdentifier = "SkinColorSamples_HighNThresholdPassedTF";
  y->b_SkinColorSamples_HighNThresho = i_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 4,
    "SkinColorSamples_HighNThresholdPassedTF")), &thisId);
  thisId.fIdentifier = "SkinColorSamples_HighNThresholdIdx";
  y->c_SkinColorSamples_HighNThresho = b_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 5,
    "SkinColorSamples_HighNThresholdIdx")), &thisId);
  thisId.fIdentifier = "ColorThreshold";
  o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 6,
    "ColorThreshold")), &thisId, y->ColorThreshold);
  thisId.fIdentifier = "ColorThresholdHighN";
  o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 7,
    "ColorThresholdHighN")), &thisId, y->ColorThresholdHighN);
  thisId.fIdentifier = "RecentThresholdOpsFrameIdx";
  y->RecentThresholdOpsFrameIdx = b_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 8,
    "RecentThresholdOpsFrameIdx")), &thisId);
  thisId.fIdentifier = "ThresholdOpsInterval";
  y->ThresholdOpsInterval = b_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 9, "ThresholdOpsInterval")), &thisId);
  thisId.fIdentifier = "ThresholdOpsRunCurrentFrameTF";
  y->ThresholdOpsRunCurrentFrameTF = i_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 10,
    "ThresholdOpsRunCurrentFrameTF")), &thisId);
  thisId.fIdentifier = "ColorSDThreshold";
  y->ColorSDThreshold = t_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 11, "ColorSDThreshold")), &thisId);
  thisId.fIdentifier = "RGBProbTheta";
  fb_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
    12, "RGBProbTheta")), &thisId, y->RGBProbTheta);
  thisId.fIdentifier = "YCbCrMeanOfMeans";
  o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 13,
    "YCbCrMeanOfMeans")), &thisId, y->YCbCrMeanOfMeans);
  thisId.fIdentifier = "YCbCrStdDevOfMeans";
  o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 14,
    "YCbCrStdDevOfMeans")), &thisId, y->YCbCrStdDevOfMeans);
  thisId.fIdentifier = "RegionNThreshold";
  y->RegionNThreshold = t_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 15, "RegionNThreshold")), &thisId);
  emlrtDestroyArray(&u);
}

static void ec_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[2] = { -1, 5 };

  int32_T iv[2];
  int32_T i;
  const boolean_T bv[2] = { true, false };

  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 2U,
    dims, &bv[0], iv);
  i = ret->size[0] * ret->size[1];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  emxEnsureCapacity_real_T(ret, i);
  emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, ret->data, 8, false);
  emlrtDestroyArray(&src);
}

static int32_T emlrt_marshallIn(const mxArray *i, const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  int32_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(emlrtAlias(i), &thisId);
  emlrtDestroyArray(&i);
  return y;
}

static int16_T f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  int16_T y;
  y = rb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *f_emlrt_marshallOut(const int16_T u_data[], const int32_T
  u_size[2])
{
  const mxArray *m;
  const mxArray *y;
  int32_T iv[2];
  int32_T b_i;
  int32_T c_i;
  int32_T i;
  int16_T *pData;
  y = NULL;
  iv[0] = u_size[0];
  iv[1] = u_size[1];
  m = emlrtCreateNumericArray(2, &iv[0], mxINT16_CLASS, mxREAL);
  pData = (int16_T *)emlrtMxGetData(m);
  i = 0;
  for (b_i = 0; b_i < u_size[1]; b_i++) {
    for (c_i = 0; c_i < u_size[0]; c_i++) {
      pData[i] = u_data[c_i + u_size[0] * b_i];
      i++;
    }
  }

  emlrtAssign(&y, m);
  return y;
}

static void fb_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[4])
{
  gc_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void fc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[1] = { -1 };

  int32_T iv[1];
  int32_T i;
  const boolean_T bv[1] = { true };

  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 1U,
    dims, &bv[0], iv);
  i = ret->size[0];
  ret->size[0] = iv[0];
  emxEnsureCapacity_real_T(ret, i);
  emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, ret->data, 8, false);
  emlrtDestroyArray(&src);
}

static void g_emlrt_marshallIn(const mxArray *SkinSegmentConfig, const char_T
  *identifier, struct0_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  h_emlrt_marshallIn(emlrtAlias(SkinSegmentConfig), &thisId, y);
  emlrtDestroyArray(&SkinSegmentConfig);
}

static const mxArray *g_emlrt_marshallOut(const uint8_T u_data[], const int32_T
  u_size[2])
{
  const mxArray *m;
  const mxArray *y;
  int32_T iv[2];
  int32_T b_i;
  int32_T i;
  uint8_T *pData;
  y = NULL;
  iv[0] = u_size[0];
  iv[1] = u_size[1];
  m = emlrtCreateNumericArray(2, &iv[0], mxUINT8_CLASS, mxREAL);
  pData = (uint8_T *)emlrtMxGetData(m);
  i = 0;
  b_i = 0;
  while (b_i < u_size[1]) {
    for (b_i = 0; b_i < u_size[0]; b_i++) {
      pData[i] = u_data[b_i];
      i++;
    }

    b_i = 1;
  }

  emlrtAssign(&y, m);
  return y;
}

static boolean_T gb_emlrt_marshallIn(const mxArray
  *c_OutputConfig_WriteVideoShowRO, const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  boolean_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = i_emlrt_marshallIn(emlrtAlias(c_OutputConfig_WriteVideoShowRO), &thisId);
  emlrtDestroyArray(&c_OutputConfig_WriteVideoShowRO);
  return y;
}

static void gc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[4])
{
  static const int32_T dims[1] = { 4 };

  real_T (*r)[4];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 1U,
    dims);
  r = (real_T (*)[4])emlrtMxGetData(src);
  ret[0] = (*r)[0];
  ret[1] = (*r)[1];
  ret[2] = (*r)[2];
  ret[3] = (*r)[3];
  emlrtDestroyArray(&src);
}

static void h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct0_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[9] = { "SkinSegmentTF",
    "SkinSegmentSeverityFactor", "MorphCloseSEMediumWidth",
    "MorphCloseSELargeWidth", "UseCompiledFunctionsTF", "Args", "TailoredData",
    "ConfirmSkin", "OverSegmentedCheck" };

  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 9, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "SkinSegmentTF";
  y->SkinSegmentTF = i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 0, "SkinSegmentTF")), &thisId);
  thisId.fIdentifier = "SkinSegmentSeverityFactor";
  y->SkinSegmentSeverityFactor = j_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
    "SkinSegmentSeverityFactor")), &thisId);
  thisId.fIdentifier = "MorphCloseSEMediumWidth";
  y->MorphCloseSEMediumWidth = j_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 2, "MorphCloseSEMediumWidth")), &thisId);
  thisId.fIdentifier = "MorphCloseSELargeWidth";
  y->MorphCloseSELargeWidth = j_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 3, "MorphCloseSELargeWidth")), &thisId);
  thisId.fIdentifier = "UseCompiledFunctionsTF";
  y->UseCompiledFunctionsTF = i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 4, "UseCompiledFunctionsTF")), &thisId);
  thisId.fIdentifier = "Args";
  k_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 5,
    "Args")), &thisId, &y->Args);
  thisId.fIdentifier = "TailoredData";
  q_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 6,
    "TailoredData")), &thisId, &y->TailoredData);
  thisId.fIdentifier = "ConfirmSkin";
  y->ConfirmSkin = s_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 7, "ConfirmSkin")), &thisId);
  thisId.fIdentifier = "OverSegmentedCheck";
  u_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 8,
    "OverSegmentedCheck")), &thisId, &y->OverSegmentedCheck);
  emlrtDestroyArray(&u);
}

static const mxArray *h_emlrt_marshallOut(const real32_T u_data[], const int32_T
  u_size[2])
{
  const mxArray *m;
  const mxArray *y;
  int32_T iv[2];
  int32_T b_i;
  int32_T c_i;
  int32_T i;
  real32_T *pData;
  y = NULL;
  iv[0] = u_size[0];
  iv[1] = u_size[1];
  m = emlrtCreateNumericArray(2, &iv[0], mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)emlrtMxGetData(m);
  i = 0;
  for (b_i = 0; b_i < u_size[1]; b_i++) {
    for (c_i = 0; c_i < u_size[0]; c_i++) {
      pData[i] = u_data[c_i + u_size[0] * b_i];
      i++;
    }
  }

  emlrtAssign(&y, m);
  return y;
}

static int16_T (*hb_emlrt_marshallIn(const mxArray *BoundingBoxSkin, const
  char_T *identifier))[4]
{
  emlrtMsgIdentifier thisId;
  int16_T (*y)[4];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = ib_emlrt_marshallIn(emlrtAlias(BoundingBoxSkin), &thisId);
  emlrtDestroyArray(&BoundingBoxSkin);
  return y;
}
  static int16_T (*hc_emlrt_marshallIn(const mxArray *src, const
  emlrtMsgIdentifier *msgId))[4]
{
  static const int32_T dims[2] = { 1, 4 };

  int16_T (*ret)[4];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int16", false, 2U,
    dims);
  ret = (int16_T (*)[4])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static boolean_T i_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  boolean_T y;
  y = sb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *i_emlrt_marshallOut(const real32_T u_data[], const int32_T
  u_size[2])
{
  const mxArray *m;
  const mxArray *y;
  int32_T iv[2];
  int32_T b_i;
  int32_T i;
  real32_T *pData;
  y = NULL;
  iv[0] = u_size[0];
  iv[1] = u_size[1];
  m = emlrtCreateNumericArray(2, &iv[0], mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)emlrtMxGetData(m);
  i = 0;
  b_i = 0;
  while (b_i < u_size[1]) {
    for (b_i = 0; b_i < u_size[0]; b_i++) {
      pData[i] = u_data[b_i];
      i++;
    }

    b_i = 1;
  }

  emlrtAssign(&y, m);
  return y;
}

static int16_T (*ib_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[4]
{
  int16_T (*y)[4];
  y = hc_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static void ic_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, int16_T **ret_data, int32_T ret_size[2])
{
  static const int32_T dims[2] = { 1, 4 };

  int32_T iv[2];
  const boolean_T bv[2] = { true, false };

  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "int16", false, 2U,
    dims, &bv[0], iv);
  ret_size[0] = iv[0];
  ret_size[1] = iv[1];
  *ret_data = (int16_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
}

static real_T j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  real_T y;
  y = tb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *j_emlrt_marshallOut(const emxArray_uint32_T *u)
{
  const mxArray *m;
  const mxArray *y;
  int32_T iv[2];
  int32_T b_i;
  int32_T i;
  uint32_T *pData;
  y = NULL;
  iv[0] = u->size[0];
  iv[1] = u->size[1];
  m = emlrtCreateNumericArray(2, &iv[0], mxUINT32_CLASS, mxREAL);
  pData = (uint32_T *)emlrtMxGetData(m);
  i = 0;
  b_i = 0;
  while (b_i < u->size[1]) {
    for (b_i = 0; b_i < u->size[0]; b_i++) {
      pData[i] = u->data[b_i];
      i++;
    }

    b_i = 1;
  }

  emlrtAssign(&y, m);
  return y;
}

static void jb_emlrt_marshallIn(const mxArray *ROI_SR_ith, const char_T
  *identifier, int16_T **y_data, int32_T y_size[2])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  kb_emlrt_marshallIn(emlrtAlias(ROI_SR_ith), &thisId, y_data, y_size);
  emlrtDestroyArray(&ROI_SR_ith);
}

static void jc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static void k_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct1_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[11] = { "SkinColorSamples_NThresholdPassedTF",
    "YCbCrThresholdsGeneric", "HSThresholdsGeneric", "YCbCrThresholdsTailored",
    "YCbCrThresholdsTailored_Sev", "HSThresholdsTailored",
    "HSThresholdsTailored_Sev", "RangeSEWidth", "RangeThreshold",
    "MorphCloseSEMediumWidth_Tuned", "MorphCloseSELargeWidth_Tuned" };

  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 11, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "SkinColorSamples_NThresholdPassedTF";
  y->c_SkinColorSamples_NThresholdPa = i_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 0,
    "SkinColorSamples_NThresholdPassedTF")), &thisId);
  thisId.fIdentifier = "YCbCrThresholdsGeneric";
  l_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
    "YCbCrThresholdsGeneric")), &thisId, y->YCbCrThresholdsGeneric);
  thisId.fIdentifier = "HSThresholdsGeneric";
  m_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 2,
    "HSThresholdsGeneric")), &thisId, y->HSThresholdsGeneric);
  thisId.fIdentifier = "YCbCrThresholdsTailored";
  n_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 3,
    "YCbCrThresholdsTailored")), &thisId, y->YCbCrThresholdsTailored);
  thisId.fIdentifier = "YCbCrThresholdsTailored_Sev";
  n_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 4,
    "YCbCrThresholdsTailored_Sev")), &thisId, y->YCbCrThresholdsTailored_Sev);
  thisId.fIdentifier = "HSThresholdsTailored";
  o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 5,
    "HSThresholdsTailored")), &thisId, y->HSThresholdsTailored);
  thisId.fIdentifier = "HSThresholdsTailored_Sev";
  o_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 6,
    "HSThresholdsTailored_Sev")), &thisId, y->HSThresholdsTailored_Sev);
  thisId.fIdentifier = "RangeSEWidth";
  y->RangeSEWidth = f_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 7, "RangeSEWidth")), &thisId);
  thisId.fIdentifier = "RangeThreshold";
  y->RangeThreshold = p_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 8, "RangeThreshold")), &thisId);
  thisId.fIdentifier = "MorphCloseSEMediumWidth_Tuned";
  y->MorphCloseSEMediumWidth_Tuned = f_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 9,
    "MorphCloseSEMediumWidth_Tuned")), &thisId);
  thisId.fIdentifier = "MorphCloseSELargeWidth_Tuned";
  y->MorphCloseSELargeWidth_Tuned = f_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 10,
    "MorphCloseSELargeWidth_Tuned")), &thisId);
  emlrtDestroyArray(&u);
}

static const mxArray *k_emlrt_marshallOut(const uint32_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
  *(uint32_T *)emlrtMxGetData(m) = u;
  emlrtAssign(&y, m);
  return y;
}

static void kb_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, int16_T **y_data, int32_T y_size[2])
{
  ic_emlrt_marshallIn(emlrtAlias(u), parentId, y_data, y_size);
  emlrtDestroyArray(&u);
}

static uint64_T kc_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId)
{
  static const int32_T dims = 0;
  uint64_T ret;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint64", false, 0U,
    &dims);
  ret = *(uint64_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[7])
{
  ub_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void lb_emlrt_marshallIn(const mxArray *FramesToProcessLinIdx_SR, const
  char_T *identifier, emxArray_int32_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  mb_emlrt_marshallIn(emlrtAlias(FramesToProcessLinIdx_SR), &thisId, y);
  emlrtDestroyArray(&FramesToProcessLinIdx_SR);
}

static void m_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[2])
{
  vb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void mb_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_int32_T *y)
{
  jc_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[8])
{
  wb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static uint64_T nb_emlrt_marshallIn(const mxArray
  *Notifications_LoopStartTime_SR, const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  uint64_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = ob_emlrt_marshallIn(emlrtAlias(Notifications_LoopStartTime_SR), &thisId);
  emlrtDestroyArray(&Notifications_LoopStartTime_SR);
  return y;
}

static void o_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[3])
{
  xb_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static uint64_T ob_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  uint64_T y;
  y = kc_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static uint8_T p_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  uint8_T y;
  y = yb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static int32_T pb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
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

static void q_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct2_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[13] = { "OpsReadyTF",
    "RecentThresholdOpsFrameIdx", "ThresholdOpsInterval",
    "ThresholdOpsRunCurrentFrameTF", "SkinColorSamples_NThreshold",
    "RangePercentile_YCbCrH", "RangePercentile_S",
    "SkinColorSamples_HighNThreshold", "SkinColorSamples_HighNThresholdPassedTF",
    "RangePercentileHighN_YCbCrH", "RangePercentileHighN_S",
    "RangePercentileSev_YCbCrH", "RangePercentileSev_S" };

  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 13, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "OpsReadyTF";
  y->OpsReadyTF = i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 0, "OpsReadyTF")), &thisId);
  thisId.fIdentifier = "RecentThresholdOpsFrameIdx";
  y->RecentThresholdOpsFrameIdx = b_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
    "RecentThresholdOpsFrameIdx")), &thisId);
  thisId.fIdentifier = "ThresholdOpsInterval";
  y->ThresholdOpsInterval = b_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 2, "ThresholdOpsInterval")), &thisId);
  thisId.fIdentifier = "ThresholdOpsRunCurrentFrameTF";
  y->ThresholdOpsRunCurrentFrameTF = i_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 3,
    "ThresholdOpsRunCurrentFrameTF")), &thisId);
  thisId.fIdentifier = "SkinColorSamples_NThreshold";
  y->SkinColorSamples_NThreshold = j_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 4,
    "SkinColorSamples_NThreshold")), &thisId);
  thisId.fIdentifier = "RangePercentile_YCbCrH";
  r_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 5,
    "RangePercentile_YCbCrH")), &thisId, y->RangePercentile_YCbCrH);
  thisId.fIdentifier = "RangePercentile_S";
  r_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 6,
    "RangePercentile_S")), &thisId, y->RangePercentile_S);
  thisId.fIdentifier = "SkinColorSamples_HighNThreshold";
  y->SkinColorSamples_HighNThreshold = j_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 7,
    "SkinColorSamples_HighNThreshold")), &thisId);
  thisId.fIdentifier = "SkinColorSamples_HighNThresholdPassedTF";
  y->b_SkinColorSamples_HighNThresho = i_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 8,
    "SkinColorSamples_HighNThresholdPassedTF")), &thisId);
  thisId.fIdentifier = "RangePercentileHighN_YCbCrH";
  r_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 9,
    "RangePercentileHighN_YCbCrH")), &thisId, y->RangePercentileHighN_YCbCrH);
  thisId.fIdentifier = "RangePercentileHighN_S";
  r_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 10,
    "RangePercentileHighN_S")), &thisId, y->RangePercentileHighN_S);
  thisId.fIdentifier = "RangePercentileSev_YCbCrH";
  r_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 11,
    "RangePercentileSev_YCbCrH")), &thisId, y->RangePercentileSev_YCbCrH);
  thisId.fIdentifier = "RangePercentileSev_S";
  r_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 12,
    "RangePercentileSev_S")), &thisId, y->RangePercentileSev_S);
  emlrtDestroyArray(&u);
}

static void qb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_uint8_T *ret)
{
  static const int32_T dims[3] = { -1, -1, 3 };

  int32_T iv[3];
  int32_T i;
  const boolean_T bv[3] = { true, true, false };

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

static void r_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[2])
{
  ac_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static int16_T rb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
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

static struct3_T s_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[5] = { "ProportionThresholdPrimary",
    "ProportionThresholdSecondary1", "ProportionThresholdSecondary2",
    "ProportionThresholdSkin", "ProportionThresholdMeans" };

  emlrtMsgIdentifier thisId;
  struct3_T y;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 5, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "ProportionThresholdPrimary";
  y.ProportionThresholdPrimary = t_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 0,
    "ProportionThresholdPrimary")), &thisId);
  thisId.fIdentifier = "ProportionThresholdSecondary1";
  y.ProportionThresholdSecondary1 = t_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
    "ProportionThresholdSecondary1")), &thisId);
  thisId.fIdentifier = "ProportionThresholdSecondary2";
  y.ProportionThresholdSecondary2 = t_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 2,
    "ProportionThresholdSecondary2")), &thisId);
  thisId.fIdentifier = "ProportionThresholdSkin";
  y.ProportionThresholdSkin = t_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 3, "ProportionThresholdSkin")), &thisId);
  thisId.fIdentifier = "ProportionThresholdMeans";
  y.ProportionThresholdMeans = t_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 4, "ProportionThresholdMeans")), &thisId);
  emlrtDestroyArray(&u);
  return y;
}

static boolean_T sb_emlrt_marshallIn(const mxArray *src, const
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

static real32_T t_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  real32_T y;
  y = bc_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T tb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 0U,
    &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void u_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct4_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[14] = { "CheckTF",
    "ProportionThresholdPrimary", "ProportionThresholdSecondary1",
    "ProportionThresholdSecondary2", "FramesLowSkinProportionThreshold",
    "NFramesLowSkinProportionStatus", "MorphReductionAmount",
    "NMorphReductionLimit", "NMorphReductions", "DarknessThreshold",
    "BelowDarknessThresholdTF", "NFramesYSingleMean", "PixelColorsAdjustedTF",
    "ColorThresAdjustTo" };

  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 14, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "CheckTF";
  y->CheckTF = i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 0, "CheckTF")), &thisId);
  thisId.fIdentifier = "ProportionThresholdPrimary";
  y->ProportionThresholdPrimary = t_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
    "ProportionThresholdPrimary")), &thisId);
  thisId.fIdentifier = "ProportionThresholdSecondary1";
  y->ProportionThresholdSecondary1 = t_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 2,
    "ProportionThresholdSecondary1")), &thisId);
  thisId.fIdentifier = "ProportionThresholdSecondary2";
  y->ProportionThresholdSecondary2 = t_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 3,
    "ProportionThresholdSecondary2")), &thisId);
  thisId.fIdentifier = "FramesLowSkinProportionThreshold";
  y->c_FramesLowSkinProportionThresh = j_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 4,
    "FramesLowSkinProportionThreshold")), &thisId);
  thisId.fIdentifier = "NFramesLowSkinProportionStatus";
  y->NFramesLowSkinProportionStatus = j_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 5,
    "NFramesLowSkinProportionStatus")), &thisId);
  thisId.fIdentifier = "MorphReductionAmount";
  y->MorphReductionAmount = j_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 6, "MorphReductionAmount")), &thisId);
  thisId.fIdentifier = "NMorphReductionLimit";
  y->NMorphReductionLimit = b_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 7, "NMorphReductionLimit")), &thisId);
  thisId.fIdentifier = "NMorphReductions";
  y->NMorphReductions = b_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 8, "NMorphReductions")), &thisId);
  thisId.fIdentifier = "DarknessThreshold";
  y->DarknessThreshold = t_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 9, "DarknessThreshold")), &thisId);
  thisId.fIdentifier = "BelowDarknessThresholdTF";
  y->BelowDarknessThresholdTF = i_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 10,
    "BelowDarknessThresholdTF")), &thisId);
  thisId.fIdentifier = "NFramesYSingleMean";
  y->NFramesYSingleMean = t_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 11, "NFramesYSingleMean")), &thisId);
  thisId.fIdentifier = "PixelColorsAdjustedTF";
  y->PixelColorsAdjustedTF = i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 12, "PixelColorsAdjustedTF")), &thisId);
  thisId.fIdentifier = "ColorThresAdjustTo";
  v_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 13,
    "ColorThresAdjustTo")), &thisId, y->ColorThresAdjustTo);
  emlrtDestroyArray(&u);
}

static void ub_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[7])
{
  static const int32_T dims[2] = { 1, 7 };

  int32_T i;
  real32_T (*r)[7];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 2U,
    dims);
  r = (real32_T (*)[7])emlrtMxGetData(src);
  for (i = 0; i < 7; i++) {
    ret[i] = (*r)[i];
  }

  emlrtDestroyArray(&src);
}

static void v_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real32_T y[9])
{
  cc_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void vb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[2])
{
  static const int32_T dims[2] = { 1, 2 };

  real32_T (*r)[2];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 2U,
    dims);
  r = (real32_T (*)[2])emlrtMxGetData(src);
  ret[0] = (*r)[0];
  ret[1] = (*r)[1];
  emlrtDestroyArray(&src);
}

static void w_emlrt_marshallIn(const mxArray *ROIGeneralConfig, const char_T
  *identifier, struct5_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  x_emlrt_marshallIn(emlrtAlias(ROIGeneralConfig), &thisId, y);
  emlrtDestroyArray(&ROIGeneralConfig);
}

static void wb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[8])
{
  static const int32_T dims[2] = { 1, 8 };

  int32_T i;
  real32_T (*r)[8];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 2U,
    dims);
  r = (real32_T (*)[8])emlrtMxGetData(src);
  for (i = 0; i < 8; i++) {
    ret[i] = (*r)[i];
  }

  emlrtDestroyArray(&src);
}

static void x_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, struct5_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[17] = { "ROIMinWidthProportion",
    "ROIMinHeightProportion", "ROIWidthResizeFactor", "ROIHeightResizeFactor",
    "ROIFinalSmoothingWindows", "ROISkipFrameThreshold_adjusted",
    "ROIMSIR_DiffMaxDetection", "ROIMSIR_DiffMaxAdjacent",
    "ROIMSIR_FirstFrameIdx", "FrameCacheMaxFrames",
    "ROIMeansOperationsReadyFirstReadTF",
    "ROIMeansMaxFrameToProcessSecondReadLinIdx", "ROISpecifyByArgument",
    "ROIIgnoreByArgument", "RecursiveTF", "ReturnAllTF",
    "UseCompiledFunctionsTF" };

  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 17, fieldNames, 0U,
    &dims);
  thisId.fIdentifier = "ROIMinWidthProportion";
  y->ROIMinWidthProportion = j_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 0, "ROIMinWidthProportion")), &thisId);
  thisId.fIdentifier = "ROIMinHeightProportion";
  y->ROIMinHeightProportion = j_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 1, "ROIMinHeightProportion")), &thisId);
  thisId.fIdentifier = "ROIWidthResizeFactor";
  y->ROIWidthResizeFactor = j_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 2, "ROIWidthResizeFactor")), &thisId);
  thisId.fIdentifier = "ROIHeightResizeFactor";
  y->ROIHeightResizeFactor = j_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 3, "ROIHeightResizeFactor")), &thisId);
  thisId.fIdentifier = "ROIFinalSmoothingWindows";
  y_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 4,
    "ROIFinalSmoothingWindows")), &thisId, y->ROIFinalSmoothingWindows);
  thisId.fIdentifier = "ROISkipFrameThreshold_adjusted";
  y->ROISkipFrameThreshold_adjusted = b_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 5,
    "ROISkipFrameThreshold_adjusted")), &thisId);
  thisId.fIdentifier = "ROIMSIR_DiffMaxDetection";
  y->ROIMSIR_DiffMaxDetection = f_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 6, "ROIMSIR_DiffMaxDetection")),
    &thisId);
  thisId.fIdentifier = "ROIMSIR_DiffMaxAdjacent";
  y->ROIMSIR_DiffMaxAdjacent = f_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 7, "ROIMSIR_DiffMaxAdjacent")), &thisId);
  thisId.fIdentifier = "ROIMSIR_FirstFrameIdx";
  y->ROIMSIR_FirstFrameIdx = b_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 8, "ROIMSIR_FirstFrameIdx")), &thisId);
  thisId.fIdentifier = "FrameCacheMaxFrames";
  y->FrameCacheMaxFrames = b_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 9, "FrameCacheMaxFrames")), &thisId);
  thisId.fIdentifier = "ROIMeansOperationsReadyFirstReadTF";
  y->c_ROIMeansOperationsReadyFirstR = i_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 10,
    "ROIMeansOperationsReadyFirstReadTF")), &thisId);
  thisId.fIdentifier = "ROIMeansMaxFrameToProcessSecondReadLinIdx";
  y->c_ROIMeansMaxFrameToProcessSeco = b_emlrt_marshallIn(emlrtAlias
    (emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 11,
    "ROIMeansMaxFrameToProcessSecondReadLinIdx")), &thisId);
  thisId.fIdentifier = "ROISpecifyByArgument";
  ab_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
    12, "ROISpecifyByArgument")), &thisId, y->ROISpecifyByArgument);
  thisId.fIdentifier = "ROIIgnoreByArgument";
  bb_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0,
    13, "ROIIgnoreByArgument")), &thisId, y->ROIIgnoreByArgument);
  thisId.fIdentifier = "RecursiveTF";
  y->RecursiveTF = i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 14, "RecursiveTF")), &thisId);
  thisId.fIdentifier = "ReturnAllTF";
  y->ReturnAllTF = i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 15, "ReturnAllTF")), &thisId);
  thisId.fIdentifier = "UseCompiledFunctionsTF";
  y->UseCompiledFunctionsTF = i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b
    (emlrtRootTLSGlobal, u, 0, 16, "UseCompiledFunctionsTF")), &thisId);
  emlrtDestroyArray(&u);
}

static void xb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real32_T ret[3])
{
  static const int32_T dims[2] = { 1, 3 };

  real32_T (*r)[3];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "single", false, 2U,
    dims);
  r = (real32_T (*)[3])emlrtMxGetData(src);
  ret[0] = (*r)[0];
  ret[1] = (*r)[1];
  ret[2] = (*r)[2];
  emlrtDestroyArray(&src);
}

static void y_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, int32_T y[2])
{
  dc_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static uint8_T yb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId)
{
  static const int32_T dims = 0;
  uint8_T ret;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint8", false, 0U,
    &dims);
  ret = *(uint8_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void SkinDetect_api(const mxArray * const prhs[16], int32_T nlhs, const mxArray *
                    plhs[5])
{
  emxArray_int32_T *FramesToProcessLinIdx_SR;
  emxArray_uint8_T *VidFrame;
  struct0_T SkinSegmentConfig;
  struct5_T ROIGeneralConfig;
  struct6_T SkinDetectConfig;
  struct8_T ROIDiagnostic_ROISkin_ith;
  uint64_T Notifications_LoopStartTime_SR;
  int32_T ROI_SR_ith_size[2];
  int32_T ROI_Selected_ith_size[2];
  int32_T Notifications_Interval_SR;
  int32_T Notifications_LoopCounter_SR;
  int32_T i;
  uint32_T LoopCounter;
  int16_T (*BoundingBoxSkin)[4];
  int16_T (*ROIForBoundingBoxSkin_FR)[4];
  int16_T (*ROI_SR_ith_data)[4];
  int16_T (*ROI_Selected_ith_data)[4];
  int16_T VideoReadConfig_VidObjHeight;
  int16_T VideoReadConfig_VidObjWidth;
  boolean_T FirstReadSkinTF;
  boolean_T HasROITF_SkinNotPresent_ith;
  boolean_T SkinTF_ith;
  boolean_T c_OutputConfig_WriteVideoShowRO;
  ROI_Selected_ith_data = (int16_T (*)[4])mxMalloc(sizeof(int16_T [4]));
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint8_T(emlrtRootTLSGlobal, &VidFrame, 3, true);
  emxInitStruct_struct5_T(&ROIGeneralConfig, true);
  emxInit_int32_T(&FramesToProcessLinIdx_SR, 2, true);
  emxInitStruct_struct8_T(&ROIDiagnostic_ROISkin_ith, true);

  /* Marshall function inputs */
  i = emlrt_marshallIn(emlrtAliasP(prhs[0]), "i");
  VidFrame->canFreeData = false;
  c_emlrt_marshallIn(emlrtAlias(prhs[1]), "VidFrame", VidFrame);
  VideoReadConfig_VidObjWidth = e_emlrt_marshallIn(emlrtAliasP(prhs[2]),
    "VideoReadConfig_VidObjWidth");
  VideoReadConfig_VidObjHeight = e_emlrt_marshallIn(emlrtAliasP(prhs[3]),
    "VideoReadConfig_VidObjHeight");
  g_emlrt_marshallIn(emlrtAliasP(prhs[4]), "SkinSegmentConfig",
                     &SkinSegmentConfig);
  w_emlrt_marshallIn(emlrtAliasP(prhs[5]), "ROIGeneralConfig", &ROIGeneralConfig);
  cb_emlrt_marshallIn(emlrtAliasP(prhs[6]), "SkinDetectConfig",
                      &SkinDetectConfig);
  c_OutputConfig_WriteVideoShowRO = gb_emlrt_marshallIn(emlrtAliasP(prhs[7]),
    "OutputConfig_WriteVideoShowROISkinDiagnosisTF");
  BoundingBoxSkin = hb_emlrt_marshallIn(emlrtAlias(prhs[8]), "BoundingBoxSkin");
  FirstReadSkinTF = gb_emlrt_marshallIn(emlrtAliasP(prhs[9]), "FirstReadSkinTF");
  ROIForBoundingBoxSkin_FR = hb_emlrt_marshallIn(emlrtAlias(prhs[10]),
    "ROIForBoundingBoxSkin_FR");
  jb_emlrt_marshallIn(emlrtAlias(prhs[11]), "ROI_SR_ith", (int16_T **)
                      &ROI_SR_ith_data, ROI_SR_ith_size);
  FramesToProcessLinIdx_SR->canFreeData = false;
  lb_emlrt_marshallIn(emlrtAlias(prhs[12]), "FramesToProcessLinIdx_SR",
                      FramesToProcessLinIdx_SR);
  Notifications_Interval_SR = emlrt_marshallIn(emlrtAliasP(prhs[13]),
    "Notifications_Interval_SR");
  Notifications_LoopStartTime_SR = nb_emlrt_marshallIn(emlrtAliasP(prhs[14]),
    "Notifications_LoopStartTime_SR");
  Notifications_LoopCounter_SR = emlrt_marshallIn(emlrtAliasP(prhs[15]),
    "Notifications_LoopCounter_SR");

  /* Invoke the target function */
  SkinDetect(i, VidFrame, VideoReadConfig_VidObjWidth,
             VideoReadConfig_VidObjHeight, &SkinSegmentConfig, &ROIGeneralConfig,
             &SkinDetectConfig, c_OutputConfig_WriteVideoShowRO,
             *BoundingBoxSkin, FirstReadSkinTF, *ROIForBoundingBoxSkin_FR,
             *ROI_SR_ith_data, ROI_SR_ith_size, FramesToProcessLinIdx_SR,
             Notifications_Interval_SR, Notifications_LoopStartTime_SR,
             Notifications_LoopCounter_SR, *ROI_Selected_ith_data,
             ROI_Selected_ith_size, &SkinTF_ith, &HasROITF_SkinNotPresent_ith,
             &ROIDiagnostic_ROISkin_ith, &LoopCounter);

  /* Marshall function outputs */
  plhs[0] = c_emlrt_marshallOut(*ROI_Selected_ith_data, ROI_Selected_ith_size);
  emxFree_int32_T(&FramesToProcessLinIdx_SR);
  emxFreeStruct_struct5_T(&ROIGeneralConfig);
  emxFree_uint8_T(&VidFrame);
  if (nlhs > 1) {
    plhs[1] = d_emlrt_marshallOut(SkinTF_ith);
  }

  if (nlhs > 2) {
    plhs[2] = d_emlrt_marshallOut(HasROITF_SkinNotPresent_ith);
  }

  if (nlhs > 3) {
    plhs[3] = e_emlrt_marshallOut(&ROIDiagnostic_ROISkin_ith);
  }

  emxFreeStruct_struct8_T(&ROIDiagnostic_ROISkin_ith);
  if (nlhs > 4) {
    plhs[4] = k_emlrt_marshallOut(LoopCounter);
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_SkinDetect_api.c) */
