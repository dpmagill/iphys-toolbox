/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect.c
 *
 * Code generation for function 'SkinDetect'
 *
 */

/* Include files */
#include "SkinDetect.h"
#include "SkinDetect_PartitionRegions.h"
#include "SkinDetect_ROIValidate.h"
#include "SkinDetect_RegionBoundariesByCategory.h"
#include "SkinDetect_RegionMetrics.h"
#include "SkinDetect_data.h"
#include "SkinDetect_emxutil.h"
#include "SkinDetect_types.h"
#include "SkinSegmentMask_Threshold.h"
#include "abs.h"
#include "any.h"
#include "bwconncomp.h"
#include "bwpack.h"
#include "bwunpack.h"
#include "exp.h"
#include "find.h"
#include "ifWhileCond.h"
#include "imdilate.h"
#include "imerode.h"
#include "mtimes.h"
#include "regionprops.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "mwmathutil.h"
#include <string.h>

/* Variable Definitions */
static emlrtMCInfo emlrtMCI = { 203,   /* lineNo */
  5,                                   /* colNo */
  "SkinDetect_PartitionRegions",       /* fName */
  "G:\\My Drive\\Articles\\topics\\physio\\Articles Chapters\\Measures\\Autonomic NS (GSR HR)\\HR\\HR webcam\\FacePulseRate\\Funs\\ROI_Means\\De"
  "tect_Algs\\Skin\\SkinDetect_PartitionRegions.m"/* pName */
};

/* Function Declarations */
static void b_cast(const struct8_T *b, d_struct_T *c);
static const mxArray *b_emlrt_marshallOut(const char_T u[111]);
static void c_cast(const d_struct_T *b, struct8_T *c);
static void cast(const b_struct_T _data[], const int32_T _size[1], b_struct_T
                 b__data[], int32_T b__size[1]);
static void d_cast(const int32_T _size[1], b_struct_T _data[], int32_T b__size[1]);
static void e_cast(const b_struct_T _data[], const int32_T _size[1], b_struct_T
                   b__data[], int32_T b__size[1]);
static const mxArray *emlrt_marshallOut(const char_T u[23]);
static void error(const mxArray *b, const mxArray *c, emlrtMCInfo *location);

/* Function Definitions */
static void b_cast(const struct8_T *b, d_struct_T *c)
{
  int32_T i;
  int32_T loop_ub;
  c->RegionSkinROIAttempted = b->RegionSkinROIAttempted;
  c->BBox_Scan_SkinAlg.size[0] = b->BBox_Scan_SkinAlg.size[0];
  c->BBox_Scan_SkinAlg.size[1] = b->BBox_Scan_SkinAlg.size[1];
  loop_ub = b->BBox_Scan_SkinAlg.size[0] * b->BBox_Scan_SkinAlg.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->BBox_Scan_SkinAlg.data[0], &b->BBox_Scan_SkinAlg.data[0], loop_ub
           * sizeof(uint16_T));
  }

  c->RegionAnyAvailable = b->RegionAnyAvailable;
  c->RegionNPixels_RejectedN.size[0] = b->RegionNPixels_RejectedN.size[0];
  c->RegionNPixels_RejectedN.size[1] = b->RegionNPixels_RejectedN.size[1];
  loop_ub = b->RegionNPixels_RejectedN.size[0] * b->
    RegionNPixels_RejectedN.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionNPixels_RejectedN.data[0], &b->
           RegionNPixels_RejectedN.data[0], loop_ub * sizeof(uint32_T));
  }

  c->RegionNPixels_RejectedLowNTF.size[0] = b->
    RegionNPixels_RejectedLowNTF.size[0];
  c->RegionNPixels_RejectedLowNTF.size[1] = b->
    RegionNPixels_RejectedLowNTF.size[1];
  loop_ub = b->RegionNPixels_RejectedLowNTF.size[0] *
    b->RegionNPixels_RejectedLowNTF.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionNPixels_RejectedLowNTF.data[0],
           &b->RegionNPixels_RejectedLowNTF.data[0], loop_ub * sizeof(boolean_T));
  }

  c->RegionCentroids_SelectedXY.size[0] = b->RegionCentroids_SelectedXY.size[0];
  c->RegionCentroids_SelectedXY.size[1] = b->RegionCentroids_SelectedXY.size[1];
  loop_ub = b->RegionCentroids_SelectedXY.size[0] *
    b->RegionCentroids_SelectedXY.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionCentroids_SelectedXY.data[0],
           &b->RegionCentroids_SelectedXY.data[0], loop_ub * sizeof(int16_T));
  }

  c->RegionCentroids_CandidateXY.size[0] = b->RegionCentroids_CandidateXY.size[0];
  c->RegionCentroids_CandidateXY.size[1] = b->RegionCentroids_CandidateXY.size[1];
  loop_ub = b->RegionCentroids_CandidateXY.size[0] *
    b->RegionCentroids_CandidateXY.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionCentroids_CandidateXY.data[0],
           &b->RegionCentroids_CandidateXY.data[0], loop_ub * sizeof(int16_T));
  }

  c->RegionCentroids_RejectedXY.size[0] = b->RegionCentroids_RejectedXY.size[0];
  c->RegionCentroids_RejectedXY.size[1] = b->RegionCentroids_RejectedXY.size[1];
  loop_ub = b->RegionCentroids_RejectedXY.size[0] *
    b->RegionCentroids_RejectedXY.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionCentroids_RejectedXY.data[0],
           &b->RegionCentroids_RejectedXY.data[0], loop_ub * sizeof(int16_T));
  }

  c->PredictedROI_center.size[0] = b->PredictedROI_center.size[0];
  c->PredictedROI_center.size[1] = b->PredictedROI_center.size[1];
  loop_ub = b->PredictedROI_center.size[0] * b->PredictedROI_center.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->PredictedROI_center.data[0], &b->PredictedROI_center.data[0],
           loop_ub * sizeof(uint16_T));
  }

  c->RegionScores_SelectedRGBProb.size[0] = b->
    RegionScores_SelectedRGBProb.size[0];
  c->RegionScores_SelectedRGBProb.size[1] = b->
    RegionScores_SelectedRGBProb.size[1];
  loop_ub = b->RegionScores_SelectedRGBProb.size[0] *
    b->RegionScores_SelectedRGBProb.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionScores_SelectedRGBProb.data[0],
           &b->RegionScores_SelectedRGBProb.data[0], loop_ub * sizeof(uint8_T));
  }

  c->RegionScores_CandidateRGBProb.size[0] =
    b->RegionScores_CandidateRGBProb.size[0];
  c->RegionScores_CandidateRGBProb.size[1] =
    b->RegionScores_CandidateRGBProb.size[1];
  loop_ub = b->RegionScores_CandidateRGBProb.size[0] *
    b->RegionScores_CandidateRGBProb.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionScores_CandidateRGBProb.data[0],
           &b->RegionScores_CandidateRGBProb.data[0], loop_ub * sizeof(uint8_T));
  }

  c->RegionScores_RejectedRGBProb.size[0] = b->
    RegionScores_RejectedRGBProb.size[0];
  c->RegionScores_RejectedRGBProb.size[1] = b->
    RegionScores_RejectedRGBProb.size[1];
  loop_ub = b->RegionScores_RejectedRGBProb.size[0] *
    b->RegionScores_RejectedRGBProb.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionScores_RejectedRGBProb.data[0],
           &b->RegionScores_RejectedRGBProb.data[0], loop_ub * sizeof(uint8_T));
  }

  c->RegionScores_SelectedYCbCrZ.size[0] = b->RegionScores_SelectedYCbCrZ.size[0];
  c->RegionScores_SelectedYCbCrZ.size[1] = b->RegionScores_SelectedYCbCrZ.size[1];
  loop_ub = b->RegionScores_SelectedYCbCrZ.size[0] *
    b->RegionScores_SelectedYCbCrZ.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionScores_SelectedYCbCrZ.data[0],
           &b->RegionScores_SelectedYCbCrZ.data[0], loop_ub * sizeof(real32_T));
  }

  c->RegionScores_CandidateYCbCrZ.size[0] = b->
    RegionScores_CandidateYCbCrZ.size[0];
  c->RegionScores_CandidateYCbCrZ.size[1] = b->
    RegionScores_CandidateYCbCrZ.size[1];
  loop_ub = b->RegionScores_CandidateYCbCrZ.size[0] *
    b->RegionScores_CandidateYCbCrZ.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionScores_CandidateYCbCrZ.data[0],
           &b->RegionScores_CandidateYCbCrZ.data[0], loop_ub * sizeof(real32_T));
  }

  c->RegionScores_RejectedYCbCrZ.size[0] = b->RegionScores_RejectedYCbCrZ.size[0];
  c->RegionScores_RejectedYCbCrZ.size[1] = b->RegionScores_RejectedYCbCrZ.size[1];
  loop_ub = b->RegionScores_RejectedYCbCrZ.size[0] *
    b->RegionScores_RejectedYCbCrZ.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionScores_RejectedYCbCrZ.data[0],
           &b->RegionScores_RejectedYCbCrZ.data[0], loop_ub * sizeof(real32_T));
  }

  c->RegionRankings_CandidateHi2Lo.size[0] =
    b->RegionRankings_CandidateHi2Lo.size[0];
  c->RegionRankings_CandidateHi2Lo.size[1] =
    b->RegionRankings_CandidateHi2Lo.size[1];
  loop_ub = b->RegionRankings_CandidateHi2Lo.size[0] *
    b->RegionRankings_CandidateHi2Lo.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionRankings_CandidateHi2Lo.data[0],
           &b->RegionRankings_CandidateHi2Lo.data[0], loop_ub * sizeof(real32_T));
  }

  c->c_RegionCrSDScores_RejectedCrSD.size[0] =
    b->c_RegionCrSDScores_RejectedCrSD.size[0];
  c->c_RegionCrSDScores_RejectedCrSD.size[1] =
    b->c_RegionCrSDScores_RejectedCrSD.size[1];
  loop_ub = b->c_RegionCrSDScores_RejectedCrSD.size[0] *
    b->c_RegionCrSDScores_RejectedCrSD.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->c_RegionCrSDScores_RejectedCrSD.data[0],
           &b->c_RegionCrSDScores_RejectedCrSD.data[0], loop_ub * sizeof
           (uint16_T));
  }

  c->RegionCrSDScores_RejectedCrSD.size[0] =
    b->RegionCrSDScores_RejectedCrSD.size[0];
  c->RegionCrSDScores_RejectedCrSD.size[1] =
    b->RegionCrSDScores_RejectedCrSD.size[1];
  loop_ub = b->RegionCrSDScores_RejectedCrSD.size[0] *
    b->RegionCrSDScores_RejectedCrSD.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionCrSDScores_RejectedCrSD.data[0],
           &b->RegionCrSDScores_RejectedCrSD.data[0], loop_ub * sizeof(real32_T));
  }

  c->ProportionSkinPixelsTooLow = b->ProportionSkinPixelsTooLow;
  i = c->RegionBoundaries_SelectedLinIdx->size[0] *
    c->RegionBoundaries_SelectedLinIdx->size[1];
  c->RegionBoundaries_SelectedLinIdx->size[0] =
    b->RegionBoundaries_SelectedLinIdx->size[0];
  c->RegionBoundaries_SelectedLinIdx->size[1] =
    b->RegionBoundaries_SelectedLinIdx->size[1];
  emxEnsureCapacity_uint32_T(c->RegionBoundaries_SelectedLinIdx, i);
  loop_ub = b->RegionBoundaries_SelectedLinIdx->size[0] *
    b->RegionBoundaries_SelectedLinIdx->size[1];
  for (i = 0; i < loop_ub; i++) {
    c->RegionBoundaries_SelectedLinIdx->data[i] =
      b->RegionBoundaries_SelectedLinIdx->data[i];
  }

  i = c->c_RegionBoundaries_CandidateLin->size[0] *
    c->c_RegionBoundaries_CandidateLin->size[1];
  c->c_RegionBoundaries_CandidateLin->size[0] =
    b->c_RegionBoundaries_CandidateLin->size[0];
  c->c_RegionBoundaries_CandidateLin->size[1] =
    b->c_RegionBoundaries_CandidateLin->size[1];
  emxEnsureCapacity_uint32_T(c->c_RegionBoundaries_CandidateLin, i);
  loop_ub = b->c_RegionBoundaries_CandidateLin->size[0] *
    b->c_RegionBoundaries_CandidateLin->size[1];
  for (i = 0; i < loop_ub; i++) {
    c->c_RegionBoundaries_CandidateLin->data[i] =
      b->c_RegionBoundaries_CandidateLin->data[i];
  }

  i = c->RegionBoundaries_RejectedLinIdx->size[0] *
    c->RegionBoundaries_RejectedLinIdx->size[1];
  c->RegionBoundaries_RejectedLinIdx->size[0] =
    b->RegionBoundaries_RejectedLinIdx->size[0];
  c->RegionBoundaries_RejectedLinIdx->size[1] =
    b->RegionBoundaries_RejectedLinIdx->size[1];
  emxEnsureCapacity_uint32_T(c->RegionBoundaries_RejectedLinIdx, i);
  loop_ub = b->RegionBoundaries_RejectedLinIdx->size[0] *
    b->RegionBoundaries_RejectedLinIdx->size[1];
  for (i = 0; i < loop_ub; i++) {
    c->RegionBoundaries_RejectedLinIdx->data[i] =
      b->RegionBoundaries_RejectedLinIdx->data[i];
  }
}

static const mxArray *b_emlrt_marshallOut(const char_T u[111])
{
  static const int32_T iv[2] = { 1, 111 };

  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateCharArray(2, &iv[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 111, m, &u[0]);
  emlrtAssign(&y, m);
  return y;
}

static void c_cast(const d_struct_T *b, struct8_T *c)
{
  int32_T i;
  int32_T loop_ub;
  c->RegionSkinROIAttempted = b->RegionSkinROIAttempted;
  c->BBox_Scan_SkinAlg.size[0] = 1;
  c->BBox_Scan_SkinAlg.size[1] = 4;
  c->BBox_Scan_SkinAlg.data[0] = b->BBox_Scan_SkinAlg.data[0];
  c->BBox_Scan_SkinAlg.data[1] = b->BBox_Scan_SkinAlg.data[1];
  c->BBox_Scan_SkinAlg.data[2] = b->BBox_Scan_SkinAlg.data[2];
  c->BBox_Scan_SkinAlg.data[3] = b->BBox_Scan_SkinAlg.data[3];
  c->RegionAnyAvailable = b->RegionAnyAvailable;
  c->RegionNPixels_RejectedN.size[0] = b->RegionNPixels_RejectedN.size[0];
  c->RegionNPixels_RejectedN.size[1] = 1;
  loop_ub = b->RegionNPixels_RejectedN.size[0] * b->
    RegionNPixels_RejectedN.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionNPixels_RejectedN.data[0], &b->
           RegionNPixels_RejectedN.data[0], loop_ub * sizeof(uint32_T));
  }

  c->RegionNPixels_RejectedLowNTF.size[0] = b->
    RegionNPixels_RejectedLowNTF.size[0];
  c->RegionNPixels_RejectedLowNTF.size[1] = 1;
  loop_ub = b->RegionNPixels_RejectedLowNTF.size[0] *
    b->RegionNPixels_RejectedLowNTF.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionNPixels_RejectedLowNTF.data[0],
           &b->RegionNPixels_RejectedLowNTF.data[0], loop_ub * sizeof(boolean_T));
  }

  c->RegionCentroids_SelectedXY.size[0] = b->RegionCentroids_SelectedXY.size[0];
  c->RegionCentroids_SelectedXY.size[1] = 2;
  loop_ub = b->RegionCentroids_SelectedXY.size[0] *
    b->RegionCentroids_SelectedXY.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionCentroids_SelectedXY.data[0],
           &b->RegionCentroids_SelectedXY.data[0], loop_ub * sizeof(int16_T));
  }

  c->RegionCentroids_CandidateXY.size[0] = b->RegionCentroids_CandidateXY.size[0];
  c->RegionCentroids_CandidateXY.size[1] = 2;
  loop_ub = b->RegionCentroids_CandidateXY.size[0] *
    b->RegionCentroids_CandidateXY.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionCentroids_CandidateXY.data[0],
           &b->RegionCentroids_CandidateXY.data[0], loop_ub * sizeof(int16_T));
  }

  c->RegionCentroids_RejectedXY.size[0] = b->RegionCentroids_RejectedXY.size[0];
  c->RegionCentroids_RejectedXY.size[1] = 2;
  loop_ub = b->RegionCentroids_RejectedXY.size[0] *
    b->RegionCentroids_RejectedXY.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionCentroids_RejectedXY.data[0],
           &b->RegionCentroids_RejectedXY.data[0], loop_ub * sizeof(int16_T));
  }

  c->PredictedROI_center.size[0] = 1;
  c->PredictedROI_center.size[1] = 2;
  c->PredictedROI_center.data[0] = b->PredictedROI_center.data[0];
  c->PredictedROI_center.data[1] = b->PredictedROI_center.data[1];
  c->RegionScores_SelectedRGBProb.size[0] = b->
    RegionScores_SelectedRGBProb.size[0];
  c->RegionScores_SelectedRGBProb.size[1] = b->
    RegionScores_SelectedRGBProb.size[1];
  loop_ub = b->RegionScores_SelectedRGBProb.size[0] *
    b->RegionScores_SelectedRGBProb.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionScores_SelectedRGBProb.data[0],
           &b->RegionScores_SelectedRGBProb.data[0], loop_ub * sizeof(uint8_T));
  }

  c->RegionScores_CandidateRGBProb.size[0] =
    b->RegionScores_CandidateRGBProb.size[0];
  c->RegionScores_CandidateRGBProb.size[1] =
    b->RegionScores_CandidateRGBProb.size[1];
  loop_ub = b->RegionScores_CandidateRGBProb.size[0] *
    b->RegionScores_CandidateRGBProb.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionScores_CandidateRGBProb.data[0],
           &b->RegionScores_CandidateRGBProb.data[0], loop_ub * sizeof(uint8_T));
  }

  c->RegionScores_RejectedRGBProb.size[0] = b->
    RegionScores_RejectedRGBProb.size[0];
  c->RegionScores_RejectedRGBProb.size[1] = b->
    RegionScores_RejectedRGBProb.size[1];
  loop_ub = b->RegionScores_RejectedRGBProb.size[0] *
    b->RegionScores_RejectedRGBProb.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionScores_RejectedRGBProb.data[0],
           &b->RegionScores_RejectedRGBProb.data[0], loop_ub * sizeof(uint8_T));
  }

  c->RegionScores_SelectedYCbCrZ.size[0] = b->RegionScores_SelectedYCbCrZ.size[0];
  c->RegionScores_SelectedYCbCrZ.size[1] = b->RegionScores_SelectedYCbCrZ.size[1];
  loop_ub = b->RegionScores_SelectedYCbCrZ.size[0] *
    b->RegionScores_SelectedYCbCrZ.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionScores_SelectedYCbCrZ.data[0],
           &b->RegionScores_SelectedYCbCrZ.data[0], loop_ub * sizeof(real32_T));
  }

  c->RegionScores_CandidateYCbCrZ.size[0] = b->
    RegionScores_CandidateYCbCrZ.size[0];
  c->RegionScores_CandidateYCbCrZ.size[1] = b->
    RegionScores_CandidateYCbCrZ.size[1];
  loop_ub = b->RegionScores_CandidateYCbCrZ.size[0] *
    b->RegionScores_CandidateYCbCrZ.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionScores_CandidateYCbCrZ.data[0],
           &b->RegionScores_CandidateYCbCrZ.data[0], loop_ub * sizeof(real32_T));
  }

  c->RegionScores_RejectedYCbCrZ.size[0] = b->RegionScores_RejectedYCbCrZ.size[0];
  c->RegionScores_RejectedYCbCrZ.size[1] = b->RegionScores_RejectedYCbCrZ.size[1];
  loop_ub = b->RegionScores_RejectedYCbCrZ.size[0] *
    b->RegionScores_RejectedYCbCrZ.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionScores_RejectedYCbCrZ.data[0],
           &b->RegionScores_RejectedYCbCrZ.data[0], loop_ub * sizeof(real32_T));
  }

  c->RegionRankings_CandidateHi2Lo.size[0] =
    b->RegionRankings_CandidateHi2Lo.size[0];
  c->RegionRankings_CandidateHi2Lo.size[1] =
    b->RegionRankings_CandidateHi2Lo.size[1];
  loop_ub = b->RegionRankings_CandidateHi2Lo.size[0] *
    b->RegionRankings_CandidateHi2Lo.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionRankings_CandidateHi2Lo.data[0],
           &b->RegionRankings_CandidateHi2Lo.data[0], loop_ub * sizeof(real32_T));
  }

  c->c_RegionCrSDScores_RejectedCrSD.size[0] =
    b->c_RegionCrSDScores_RejectedCrSD.size[0];
  c->c_RegionCrSDScores_RejectedCrSD.size[1] =
    b->c_RegionCrSDScores_RejectedCrSD.size[1];
  loop_ub = b->c_RegionCrSDScores_RejectedCrSD.size[0] *
    b->c_RegionCrSDScores_RejectedCrSD.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->c_RegionCrSDScores_RejectedCrSD.data[0],
           &b->c_RegionCrSDScores_RejectedCrSD.data[0], loop_ub * sizeof
           (uint16_T));
  }

  c->RegionCrSDScores_RejectedCrSD.size[0] =
    b->RegionCrSDScores_RejectedCrSD.size[0];
  c->RegionCrSDScores_RejectedCrSD.size[1] =
    b->RegionCrSDScores_RejectedCrSD.size[1];
  loop_ub = b->RegionCrSDScores_RejectedCrSD.size[0] *
    b->RegionCrSDScores_RejectedCrSD.size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&c->RegionCrSDScores_RejectedCrSD.data[0],
           &b->RegionCrSDScores_RejectedCrSD.data[0], loop_ub * sizeof(real32_T));
  }

  c->ProportionSkinPixelsTooLow = b->ProportionSkinPixelsTooLow;
  i = c->RegionBoundaries_SelectedLinIdx->size[0] *
    c->RegionBoundaries_SelectedLinIdx->size[1];
  c->RegionBoundaries_SelectedLinIdx->size[0] =
    b->RegionBoundaries_SelectedLinIdx->size[0];
  c->RegionBoundaries_SelectedLinIdx->size[1] =
    b->RegionBoundaries_SelectedLinIdx->size[1];
  emxEnsureCapacity_uint32_T(c->RegionBoundaries_SelectedLinIdx, i);
  loop_ub = b->RegionBoundaries_SelectedLinIdx->size[0] *
    b->RegionBoundaries_SelectedLinIdx->size[1];
  for (i = 0; i < loop_ub; i++) {
    c->RegionBoundaries_SelectedLinIdx->data[i] =
      b->RegionBoundaries_SelectedLinIdx->data[i];
  }

  i = c->c_RegionBoundaries_CandidateLin->size[0] *
    c->c_RegionBoundaries_CandidateLin->size[1];
  c->c_RegionBoundaries_CandidateLin->size[0] =
    b->c_RegionBoundaries_CandidateLin->size[0];
  c->c_RegionBoundaries_CandidateLin->size[1] =
    b->c_RegionBoundaries_CandidateLin->size[1];
  emxEnsureCapacity_uint32_T(c->c_RegionBoundaries_CandidateLin, i);
  loop_ub = b->c_RegionBoundaries_CandidateLin->size[0] *
    b->c_RegionBoundaries_CandidateLin->size[1];
  for (i = 0; i < loop_ub; i++) {
    c->c_RegionBoundaries_CandidateLin->data[i] =
      b->c_RegionBoundaries_CandidateLin->data[i];
  }

  i = c->RegionBoundaries_RejectedLinIdx->size[0] *
    c->RegionBoundaries_RejectedLinIdx->size[1];
  c->RegionBoundaries_RejectedLinIdx->size[0] =
    b->RegionBoundaries_RejectedLinIdx->size[0];
  c->RegionBoundaries_RejectedLinIdx->size[1] =
    b->RegionBoundaries_RejectedLinIdx->size[1];
  emxEnsureCapacity_uint32_T(c->RegionBoundaries_RejectedLinIdx, i);
  loop_ub = b->RegionBoundaries_RejectedLinIdx->size[0] *
    b->RegionBoundaries_RejectedLinIdx->size[1];
  for (i = 0; i < loop_ub; i++) {
    c->RegionBoundaries_RejectedLinIdx->data[i] =
      b->RegionBoundaries_RejectedLinIdx->data[i];
  }
}

static void cast(const b_struct_T _data[], const int32_T _size[1], b_struct_T
                 b__data[], int32_T b__size[1])
{
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T loop_ub;
  i = b__size[0];
  b__size[0] = _size[0];
  emxEnsureCapacity_struct_T(b__data, b__size, i);
  i = _size[0];
  for (i1 = 0; i1 < i; i1++) {
    i2 = b__data[i1].PixelIdxList->size[0] * b__data[i1].PixelIdxList->size[1];
    b__data[i1].PixelIdxList->size[0] = _data[i1].PixelIdxList->size[0];
    b__data[i1].PixelIdxList->size[1] = _data[i1].PixelIdxList->size[1];
    emxEnsureCapacity_uint32_T(b__data[i1].PixelIdxList, i2);
    loop_ub = _data[i1].PixelIdxList->size[0] * _data[i1].PixelIdxList->size[1];
    for (i2 = 0; i2 < loop_ub; i2++) {
      b__data[i1].PixelIdxList->data[i2] = _data[i1].PixelIdxList->data[i2];
    }
  }
}

static void d_cast(const int32_T _size[1], b_struct_T _data[], int32_T b__size[1])
{
  int32_T i;
  int32_T i1;
  i = b__size[0];
  b__size[0] = _size[0];
  emxEnsureCapacity_struct_T(_data, b__size, i);
  i = _size[0];
  for (i1 = 0; i1 < i; i1++) {
    _data[i1].PixelIdxList->size[0] = 0;
    _data[i1].PixelIdxList->size[1] = 1;
  }
}

static void e_cast(const b_struct_T _data[], const int32_T _size[1], b_struct_T
                   b__data[], int32_T b__size[1])
{
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T loop_ub;
  i = b__size[0];
  b__size[0] = _size[0];
  emxEnsureCapacity_struct_T(b__data, b__size, i);
  i = _size[0];
  for (i1 = 0; i1 < i; i1++) {
    i2 = b__data[i1].PixelIdxList->size[0] * b__data[i1].PixelIdxList->size[1];
    b__data[i1].PixelIdxList->size[0] = _data[i1].PixelIdxList->size[0];
    b__data[i1].PixelIdxList->size[1] = 1;
    emxEnsureCapacity_uint32_T(b__data[i1].PixelIdxList, i2);
    loop_ub = _data[i1].PixelIdxList->size[0] * _data[i1].PixelIdxList->size[1];
    for (i2 = 0; i2 < loop_ub; i2++) {
      b__data[i1].PixelIdxList->data[i2] = _data[i1].PixelIdxList->data[i2];
    }
  }
}

static const mxArray *emlrt_marshallOut(const char_T u[23])
{
  static const int32_T iv[2] = { 1, 23 };

  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateCharArray(2, &iv[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 23, m, &u[0]);
  emlrtAssign(&y, m);
  return y;
}

static void error(const mxArray *b, const mxArray *c, emlrtMCInfo *location)
{
  const mxArray *pArrays[2];
  pArrays[0] = b;
  pArrays[1] = c;
  emlrtCallMATLABR2012b(emlrtRootTLSGlobal, 0, NULL, 2, pArrays, "error", true,
                        location);
}

void SkinDetect(int32_T i, const emxArray_uint8_T *VidFrame, int16_T
                VideoReadConfig_VidObjWidth, int16_T
                VideoReadConfig_VidObjHeight, const struct0_T *SkinSegmentConfig,
                const struct5_T *ROIGeneralConfig, const struct6_T
                *SkinDetectConfig, boolean_T c_OutputConfig_WriteVideoShowRO,
                const int16_T BoundingBoxSkin[4], boolean_T FirstReadSkinTF,
                const int16_T ROIForBoundingBoxSkin_FR[4], const int16_T
                ROI_SR_ith_data[], const int32_T ROI_SR_ith_size[2], const
                emxArray_int32_T *FramesToProcessLinIdx_SR, int32_T
                Notifications_Interval_SR, uint64_T
                Notifications_LoopStartTime_SR, int32_T
                Notifications_LoopCounter_SR, int16_T ROI_Selected_ith_data[],
                int32_T ROI_Selected_ith_size[2], boolean_T *SkinTF_ith,
                boolean_T *HasROITF_SkinNotPresent_ith, struct8_T
                *ROIDiagnostic_ROISkin_ith, uint32_T *LoopCounter)
{
  static const char_T cv1[111] = { 'I', 'n', 't', 'e', 'r', 'n', 'a', 'l', ' ',
    'E', 'r', 'r', 'o', 'r', ' ', '(', 'S', 'k', 'i', 'n', 'D', 'e', 't', 'e',
    'c', 't', '_', 'P', 'a', 'r', 't', 'i', 't', 'i', 'o', 'n', 'R', 'e', 'g',
    'i', 'o', 'n', 's', ')', ':', ' ', 'N', 'u', 'm', 'b', 'e', 'r', ' ', 'o',
    'f', ' ', 'r', 'e', 'g', 'i', 'o', 'n', 's', ' ', 'e', 'x', 'c', 'e', 'e',
    'd', 's', ' ', 'u', 'p', 'p', 'e', 'r', ' ', ' ', 'b', 'o', 'u', 'n', 'd',
    's', ' ', 's', 'e', 't', ' ', 'f', 'o', 'r', ' ', 'c', 'o', 'm', 'p', 'i',
    'l', 'e', 'd', ' ', 'f', 'u', 'n', 'c', 't', 'i', 'o', 'n' };

  static const char_T cv[23] = { 'C', 'o', 'm', 'p', 'o', 'n', 'e', 'n', 't',
    ':', 'I', 'n', 't', 'e', 'r', 'n', 'a', 'l', 'E', 'r', 'r', 'o', 'r' };

  cell_wrap_32 RegionBoundaries[3];
  d_struct_T b_ROIDiagnostic_ROISkin_ith;
  emxArray_boolean_T *IsSkinMask;
  emxArray_boolean_T *IsSkinMask_ROISelected;
  emxArray_boolean_T *IsSkinMask_Range;
  emxArray_boolean_T *b_IsSkinMask_Range;
  emxArray_int32_T *t1_RegionLengths;
  emxArray_real32_T *CbBounded_Single;
  emxArray_real32_T *CrBounded_Single;
  emxArray_real32_T *YBounded_Single;
  emxArray_real_T *t1_RegionIndices;
  emxArray_struct_T *Centroids_Struct;
  emxArray_struct_T_400 RegionIndices;
  emxArray_struct_T_400 b_RegionIndices;
  emxArray_struct_T_400 r;
  emxArray_uint32_T *IsSkinMask_PixelColorPacked;
  emxArray_uint32_T *c_IsSkinMask_PixelColor_ErodePa;
  emxArray_uint8_T *BBounded_Uint8;
  emxArray_uint8_T *BUint8;
  emxArray_uint8_T *GBounded_Uint8;
  emxArray_uint8_T *GUint8;
  emxArray_uint8_T *RBounded_Uint8;
  emxArray_uint8_T *RUint8;
  real_T tmp_data[1600];
  real_T RegionRGBMeans_data[1200];
  real_T RegionDistance_LinIdx_data[400];
  real_T RegionRGBProbSkin_data[400];
  real_T t1_ImageSize[2];
  real_T t1_Connectivity;
  real_T t1_NumObjects;
  int32_T iidx_data[400];
  int32_T CrBounded_Single_size[2];
  int32_T HBounded_Single_size[2];
  int32_T RegionRGBMeans_size[2];
  int32_T RegionSelectedLinIdx_size[2];
  int32_T SBounded_Single_size[2];
  int32_T i_size[2];
  int32_T tmp_size[2];
  int32_T RegionDistance_LinIdx_size[1];
  int32_T RegionNPixels_size[1];
  int32_T RegionPoints_Proximity_size[1];
  int32_T RegionPoints_RGBProbSkin_size[1];
  int32_T RegionSD_Cr_size[1];
  int32_T RegionZ_Cr_size[1];
  int32_T RegionZ_Difference_size[1];
  int32_T d_RegionPassAllThresholdsTF_Lin[1];
  int32_T d_RegionPassAllThresholdsTF_Log[1];
  int32_T distances_size[1];
  int32_T s_size[1];
  int32_T ElementIdx;
  int32_T NCentroids;
  int32_T NRegions;
  int32_T NRegions_ith;
  int32_T RegionBeginIndex_ith;
  int32_T RegionCentroids_size_idx_0;
  int32_T RegionEndIndex_ith;
  int32_T b_i;
  int32_T c_RegionSD_Cr_PassThresholdTF_L;
  int32_T c_i;
  real32_T c_RegionScores_CandidateYCbCrZ_[1200];
  real32_T RegionNPixels_data[400];
  real32_T RegionSD_Cr_data[400];
  real32_T RegionZ_Cb_Standardized_data[400];
  real32_T RegionZ_Cb_data[400];
  real32_T RegionZ_Cr_Standardized_data[400];
  real32_T RegionZ_Cr_data[400];
  real32_T RegionZ_Difference_data[400];
  real32_T RegionZ_Y_Standardized_data[400];
  real32_T RegionZ_Y_data[400];
  real32_T YCbCrThresholds_Generic[7];
  real32_T HSThresholds_Generic[2];
  real32_T b_HSThresholds_Generic[2];
  real32_T CbBounded_Single_data[1];
  real32_T CrBounded_Single_data[1];
  real32_T HBounded_Single_data[1];
  real32_T SBounded_Single_data[1];
  real32_T YBounded_Single_data[1];
  real32_T ThresholdRGBProb;
  real32_T ThresholdZScoreCb;
  real32_T ThresholdZScoreCr;
  uint32_T RegionNPixels_RejectedN_data[400];
  uint32_T b_TrueCount_data[1];
  uint32_T ColMax;
  uint32_T ColMin;
  uint32_T RowMax;
  uint32_T b_r;
  uint32_T nRows;
  uint32_T z;
  int16_T RegionCentroids_Uncrop_data[800];
  int16_T RegionCentroids_data[800];
  int16_T c_tmp_data[400];
  int16_T distances_data[400];
  int16_T ROIPredicted_data[4];
  int16_T ROIRegionSelected_FullFrame[4];
  int16_T c_ROISpecifiedFrames_center_XY_[2];
  int16_T d_ROISpecifiedFrames_center_XY_[2];
  int16_T d_tmp_data[2];
  int16_T Diff12;
  int16_T Diff22;
  int16_T Diff32;
  int16_T ROIPredicted_CenterX;
  int16_T ROIPredicted_CenterY;
  int16_T functionWidthToUse;
  int16_T nRows_IsSkinMask;
  uint16_T RegionPoints_Proximity_data[400];
  uint16_T RegionPoints_RGBProbSkin_data[400];
  uint16_T RegionPoints_data[400];
  uint16_T b_RegionPoints_data[400];
  uint16_T c_RegionPassAllThresholdsTF_Lin[400];
  uint16_T c_RegionNotPassAllThresholdsTF_[399];
  uint16_T RegionSelectedLinIdx_data[1];
  uint16_T Counter_False;
  uint16_T Counter_True;
  uint16_T MaxPoints;
  uint16_T j;
  int8_T b_input_sizes_idx_1;
  int8_T input_sizes_idx_1;
  int8_T sizes_idx_1;
  uint8_T b_tmp_data[400];
  boolean_T c_RegionNPixels_PassNThresholdT[400];
  boolean_T c_RegionPassAllThresholdsTF_Log[400];
  boolean_T d_RegionSD_Cr_PassThresholdTF_L[400];
  boolean_T TrueCount_data[1];
  boolean_T CompletelyContainedTF;
  boolean_T RegionSelectedAnyTF;
  boolean_T RegionsCandidateAnyTF;
  boolean_T RegionsRejectedAnyTF;
  boolean_T exitg1;
  (void)i;
  (void)FramesToProcessLinIdx_SR;
  (void)Notifications_Interval_SR;
  (void)Notifications_LoopStartTime_SR;
  (void)Notifications_LoopCounter_SR;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint8_T(emlrtRootTLSGlobal, &RBounded_Uint8, 2, true);
  emxInit_uint8_T(emlrtRootTLSGlobal, &GBounded_Uint8, 2, true);
  emxInit_uint8_T(emlrtRootTLSGlobal, &BBounded_Uint8, 2, true);

  /* SkinDetect   Identify an ROI for a frame using a skin-detection algorithm.                   */
  /*  */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, called by functions ROIMeans_FirstRead_AlgSelector_Skin and  */
  /*     ROIMeans_SecondRead_SkinDetect. */
  /*  */
  /*  */
  /*     Code Generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*  */
  /*     Description */
  /*     ----------- */
  /*  */
  /*     This function conducts the skin-detection algorithm. As function FacePulseRate already  */
  /*     utilizes the face-detection method, which has a strong accuracy rate for frontal-face  */
  /*     orientations, the primary purpose of the present function is to identify skin regions where  */
  /*     the face-detection method is not successful, which may occur, in particular, in   */
  /*     non-frontal-face orientations, for example, in profile-face orientations.  */
  /*  */
  /*     The input of functions directly related to the skin-detection algorithm is used. These    */
  /*     functions include SkinDetect_ConfigSetup, ROIMeans_FirstRead_CollectSkinColorSamples, and  */
  /*     SkinDetect_SetThresholds.  */
  /*  */
  /*     - Function SkinDetect_ConfigSetup: assigned many of the skin-detection settings used here,  */
  /*       which are contained in struct SkinDetectConfig. This function was called by function */
  /*       ValidateAndConfigure.  */
  /*     - Function ROIMeans_FirstRead_CollectSkinColorSamples: collected skin-color samples from the  */
  /*       face in the video. These samples were used to set skin-color thresholds to be used in the  */
  /*       skin-detection algorithm. This function was called by function ROIMeans_FirstRead.   */
  /*     - Function SkinDetect_SetThresholds: set the skin-color thresholds from skin-color samples */
  /*       supplied by function ROIMeans_FirstRead_CollectSkinColorSamples. This function was called by  */
  /*       function ROIMeans_FirstRead.   */
  /*  */
  /*     The skin-detection algorithm can be unsuccessful (i.e., return a value of false for variable */
  /*     SkinTF_ith) for the following reasons: */
  /*  */
  /*     - The bounding box did not contain a skin region. */
  /*     - The portion of the frame submitted to the skin-detection algorithm was completely segmented   */
  /*       by the skin-segmentation algorithm. */
  /*     - All regions within the portion of the frame submitted to the skin-detection algorithm were */
  /*       rejected. */
  /*     - Rejected by function ConfirmSkinPresent. */
  /*  */
  /*  */
  /*     Extended Description */
  /*     -------------------- */
  /*  */
  /*  */
  /*     -- Partitioning bounding box into regions to classify -- */
  /*  */
  /*     See function SkinDetect_PartitionRegions, which is called by the current function. */
  /*   */
  /*     The area within the bounding box is partitioned into regions so that each region can be  */
  /*     assessed as being skin. By the completion of the algorithm, one region (or no regions) will be */
  /*     selected as the skin detection. */
  /*  */
  /*     - Bounding box: */
  /*  */
  /*     Using a bounding box may reduce false positive skin detections by focusing on an area of the  */
  /*     frame potentially more likely to contain skin. Using a bounding box may also reduce  */
  /*     computational time because less area needs to be assessed by the skin-detection algorithm. The  */
  /*     size and position of the bounding box are determined by the size and position of ROIs from  */
  /*     previous and subsequent frames. The ROIs from these other frames will be the result of  */
  /*     detections from the face-detection algorithm and interpolation where the face-detection  */
  /*     algorithm did not make a detection or where the face-detection algorithm was skipped for  */
  /*     efficiency. In the first-read operations, the bounding box is set by function  */
  /*     ROIMeans_FirstRead_SetBoundingBoxes. In the second-read operations, the bounding box is set by */
  /*     function ROIMeans_SecondRead_SkinDetect.  */
  /*        */
  /*     - Skin segmentation: */
  /*  */
  /*     Within the bounding box, skin segmentation (see function SkinSegmentMask) is applied to remove  */
  /*     areas less likely to be skin. The term "skin segmentation" is used to define the operations */
  /*     conducted by function SkinSegmentMask, although many operations in the current function have */
  /*     the effect of segmenting skin as well. The thresholds used by function SkinSegmentMask differ  */
  /*     from the thresholds used directly in the skin-detection algorithm because the thresholds used  */
  /*     by SkinSegmentMask apply to the properties of individual pixels. In constrast, the thresholds  */
  /*     used in the skin-detection algorithm apply to the properties of regions of pixels. For  */
  /*     example, in skin segmentation, the threholds include minimum and maximum pixel color values, */
  /*     e.g., for color channel Cr, the default mimimum is 131 and the default maximum is 173. In the */
  /*     skin-detection algorithm, the thresholds include the minimum and maximum difference from the  */
  /*     means of regions of the face in the video (which are taken from skin-color samples of the  */
  /*     face). Assessing regions of pixels may provide information to supplement information found by  */
  /*     assessing individual pixels. */
  /*  */
  /*     - Partitioning: */
  /*  */
  /*     Skin segmentation returns a two-dimension logical matrix, where true values indicate pixels */
  /*     classified as skin. This matrix, or mask, typically consists of several contingous regions of */
  /*     true values. These regions are further broken down before being submitted to further  */
  /*     skin-detection algorithm operations. The matrix is broken down, or partitioned, simply by  */
  /*     applying a grid of dividing lines to the matrix. Specifically, vertical lines are inserted at  */
  /*     specified intervals of columns (SkinDetectConfig.PartitionColInterval) and horizontal lines  */
  /*     are inserted at specified intervals of rows (SkinDetectConfig.PartitionRowInterval). These  */
  /*     lines, along with the pixels classified as non-skin by skin segmentation, are logical false  */
  /*     values. The true values that remain are distinguished as groups according to regions of  */
  /*     connected pixels (the criteria of 8-connectivity is used; see Matlab function bwconncomp). */
  /*  */
  /*     One purpose of breaking down contiguous regions into smaller regions is to improve  */
  /*     discrimination between skin and non-skin regions; these non-skin regions are portions */
  /*     misclassified as skin by the skin-segmentation procedure. After breaking up the regions, the   */
  /*     misclassified portions may end up in regions separate from correctely-classified portions. If */
  /*     this is the case, the high proportion of non-skin pixels in these regions may make it easier */
  /*     for the skin-detection algorithm to correctly discriminate between skin and non-skin regions. */
  /*     */
  /*     The other purpose of breaking down continguous regions into smaller regions is to make the  */
  /*     centroid-distance criteria (see section "Selecting one region out of candidates") more  */
  /*     effective. The distance between the centroid of a region and the center of the ROI assuming no */
  /*     skin-detection is conducted is used to help spacially stablize the region selected across   */
  /*     frames. Stability is enhanced across frames because the centroid-distance criteria favors   */
  /*     regions that occur in similar spacial areas across frames. Smaller regions increase the  */
  /*     stability resulting from this criteria because smaller regions permit greater distance  */
  /*     discrimination among regions.  */
  /*  */
  /*     For example, suppose that the tip of the nose is the center of the ROI assuming no  */
  /*     skin-detection is conducted. Suppose that selection is down to two regions, one of which  */
  /*     comprises the forehead and one a cheek. Finally, suppose that the distance between the  */
  /*     forehead-region centroid and the tip of the nose is nearly equal to the distance between the  */
  /*     cheek-region centroid and the tip of the nose. If these two regions continue to be the top  */
  /*     candidates across frames, on some occassions the forehead-region may be selected and on some  */
  /*     occassions the cheek-region may be selected depending on small deviations in  */
  /*     centroid-distance. If the selected region alternates more or less between these two regions  */
  /*     across frames, this will result in high fluctuation of the ROI as it moves between the  */
  /*     forehead and the cheek across frames. By using smaller regions, the centroid-distance will  */
  /*     have higher discrimination among regions. For example, with smaller regions, the forehead now  */
  /*     consists of many regions, as does the cheek. The centroid-distance may now favor the lower */
  /*     forehead and the region of the cheek close to the nose. Fluctuation between these two regions */
  /*     across frames will be less than the flucuation between the entire forehead and the entire  */
  /*     cheek. */
  /*      */
  /*     The regions resulting from partitioning are termed "candidate regions" as some will be   */
  /*     rejected and only one will be seleted. */
  /*  */
  /*     Note: this partitioning procedure may appear similar to that of dividing an image into  */
  /*     superpixels (regions  of pixels) for use in classification. One rational for using superpixels   */
  /*     is that fewer areas within an image need to be assessed for classification compared to an   */
  /*     operation using a moving window (see Matlab documentation under the title "Plot Land    */
  /*     Classification with Color Features and Superpixels"). However, the use of regions in the   */
  /*     current operation is simply to take advantage of assessing regions of pixels compared to  */
  /*     assessing individual pixels. */
  /*  */
  /*  */
  /*     -- Rejecting Regions -- */
  /*  */
  /*     See function SkinDetect_RejectRegions, which is called by the current function. */
  /*  */
  /*     Candidate skin regions must pass certain rejection criteria to be considered. These rejection  */
  /*     criteria include the size of the region; the probability of skin color according to RGB   */
  /*     references samples; the similarity to the mean Cb and Cr skin colors collected from the video  */
  /*     frames; and the standard deviation of the Cr colors. */
  /*   */
  /*     - RGB Probability: */
  /*       */
  /*     The RGB probability is calculated RGB reference samples from both samples collected current  */
  /*     video and samples from a population of individuals; the population samples are included to  */
  /*     increase heterogeneity, which is intended to make the probability parameters more robust. The  */
  /*     population samples are also included because they include negative samples, whereas the  */
  /*     samples collected from the current video are all positive samples. For details on the  */
  /*     collection of skin-color samples from the video, see function  */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples.    */
  /*  */
  /*     The frame means are collected by function ROIMeans_FirstRead_CollectSkinColorSamples, which is   */
  /*     called in function ROIMeans_FirstRead. Function SkinDetect_RGBProbSkin is called within the */
  /*     function SkinDetect_RejectRegions to calculate the probability of skin for each region. This   */
  /*     function is supplied with theta parameters, which were calculated from RGB color means from     */
  /*     the video and from external sources. The theta parameters were returned by function    */
  /*     SkinDetect_RGBProbSkinTrain, which was called by function SkinDetect_SetThresholds, which was    */
  /*     called by function ROIMeans_FirstRead. */
  /*  */
  /*     The RGB skin-classification functions (SkinDetect_RGBProbSkinTrain and SkinDetect_RGBProbSkin) */
  /*     are adapted from the Skin Segmentation toolbox, which was obtained from Madhav Rajan (2014).   */
  /*     See discussion on Github (https://github.com/madhrajan91/Skin-Segmentation).       */
  /*  */
  /*     The external (population) data for producing the RGB skin-classification theta values are from  */
  /*     two sources: */
  /*  */
  /*         In part from Bhatt and Dhall 2009, 'Skin Segmentation Dataset', UCI Machine Learning   */
  /*         Repository. See discussion in Bhatt, Sharma, Dhall, Chaudhury (2009). Efficient skin   */
  /*         region segmentation using low complexity fuzzy decision tree model. IEEE-INDICON, Dec  */
  /*         16-18, Ahmedabad, India, pp. 1-4. See also Dhall, Sharma, Bhatt, and Khan (2009). Adaptive  */
  /*         Digital Makeup, Proc. of International Symposium on Visual Computing (ISVC), Nov. 30 -Dec.  */
  /*         02, Las Vegas, Nevada, USA, Lecture Notes in Computer Science, Vol. 5876, pp. 728-736. */
  /*  */
  /*         In part from  Douglas Magill (2020). These data are included under the license for   */
  /*         function FacePulseRate. */
  /*  */
  /*     The threshold outside of which regions are rejected is specified as an argument  */
  /*     (SkinClassifyRegionColorThresholds(1)) to function FacePulseRate. A Larger threshold value may    */
  /*     decrease false positives but increase false negatives. */
  /*  */
  /*     - Cb, Cr Mean: */
  /*  */
  /*     Regarding the YCbCr color space, only Cb and Cr are used for rejection thresholds because of */
  /*     greater luminance invariance compared to Y. The Cb and Cr similarities are quanitifed as  */
  /*     z-scores, one for each dimension (Cb and Cr). The z-scores are calulated according to the  */
  /*     overall Cb and Cr means across ROIs from the primary face-detection algorithm and the standard  */
  /*     deviations of  these means. The means across the primary face-detection algorithm ROIs are   */
  /*     collected by function ROIMeans_FirstRead_CollectSkinColorSamples, which is called by function   */
  /*     ROIMeans_FirstRead. The overall means and standard deviations of these means are returned by  */
  /*     function SkinDetect_SetThresholds, which is called by function ROIMeans_FirstRead. The   */
  /*     thresholds outside of which regions are rejected are specified as an argument to function */
  /*     FacePulseRate: SkinClassifyRegionColorThresholds(2) = Cb z-score threshold;  */
  /*     SkinClassifyRegionColorThresholds(3) = Cr z-score threshold. Smaller threshold values may   */
  /*     decrease false positives but increase false negatives. */
  /*  */
  /*    - Pixel Count: */
  /*  */
  /*     In addition to assessing regions by their means, they are also assessed by their pixel counts, */
  /*     with the assumption that small pixel counts indicate non-skin as skin is assumed to be present  */
  /*     in contiguous regions. Using regions with larger pixel counts may also enhance the advantage  */
  /*     of mean comparison. The threshold below which regions are rejected is specified by  */
  /*     RegionNThreshold, which is specified by function SkinDetect_ConfigSetup. A Larger threshold  */
  /*     value may decrease false positives but increase false negatives.   */
  /*  */
  /*     - Standard Deviation of Cr: */
  /*  */
  /*     The standard deviation of colors within a region can be an indication that the region is not */
  /*     skin as it has been observed that skin regions have fairly homogeneous color ranges, which  */
  /*     results in a low standard deviation. Hence, a threshold is applied above which regions are   */
  /*     rejected as skin. */
  /*  */
  /*  */
  /*     -- Selecting one region out of candidates (regions that were not rejected) -- */
  /*  */
  /*     See function SkinDetect_SelectRegion, which is called by the current function. */
  /*  */
  /*     If no candidate region passes the rejection thresholds, skin detection moves to the next  */
  /*     frame. If more than one candidate region passes all the rejection thresholds, one candidate   */
  /*     region is selected based upon the ranking of regions on 3 additional criteria: (1) the   */
  /*     proximity to the predicted-ROI center, (2) higher probability of skin compared to RGB  */
  /*     references samples, and (3) the similarity to YCbCr overall means (including Y) across  */
  /*     reference samples.  */
  /*  */
  /*     - Proximity to the predicted ROI: */
  /*  */
  /*     Proximity to the predicted-ROI center is used to increase the stability of the ROI positions   */
  /*     across frames; as the predicted ROIs are based upon face detections, whose positions across   */
  /*     frames are assumed to be relatively stable, proximity to these stable detections would, in  */
  /*     turn, increase the stability of the positions of selected skin regions across frames. Also,   */
  /*     the face-detection algorithms mainly detect the frontal face, whereas the skin-detection  */
  /*     algorithm detects skin wherever it is (e.g., the neck, hands, etc.). Part of the purpose of     */
  /*     using the skin-detection algorithm is to capture skin when the face is not frontal, for  */
  /*     example, turned to the side, etc; however, if the face is frontal (but the face-detection  */
  /*     algorithm(s) failed to detect it), it is preferable to have the skin-detection algorithm focus  */
  /*     on the face rather than other skin areas for consistency. Toward this end, weighting toward  */
  /*     the face-detection algorithm ROIs helps guide the skin detections toward the frontal face  */
  /*     rather than other areas. */
  /*      */
  /*     - RGB probability: */
  /*  */
  /*     RGB probability is calculated in the method described above under "rejection thresholds".    */
  /*  */
  /*     - YCbCr similarity: */
  /*  */
  /*     The YCbCr similarity is quanitifed as a composite of three z-scores, one for each channel (Y, */
  /*     Cb, and Cr). The z-scores are calulated according to the overall Y, Cb, and Cr means across */
  /*     all frames and the standard deviations of Y, Cb, and Cr means across all frames. The z-score  */
  /*     for each channel is then standardized in comparison to the other regions in the frame to    */
  /*     balance out the contribution of each channel (otherwise, the Y-channel tends to have a much   */
  /*     higher z-score). Finally, a single composite similarity score is assigned by summing the  */
  /*     absolute values of the standarized z-scores.            */
  /*  */
  /*     - Combined skin-similarity score: */
  /*  */
  /*     The scores based upon skin color (RGB probability and YCbCr similarity) are then combined,  */
  /*     with equal weight, to one score.  */
  /*  */
  /*     - Apply weights to proximity and skin-similarity scores: */
  /*  */
  /*     The proximity score and the skin color score are then assigned weights, specified as an  */
  /*     argument, ROISkinRegionProximityWeight, to function FacePulseRate. Specifically, this argument */
  /*     specifies the relative weight to apply to proximity compared to skin color similarity. */
  /*  */
  /*     - Determining ROI box from the selected region: */
  /*  */
  /*     The ROI from the selected candidate region is determined based upon the X and Y extrema of the  */
  /*     region. The size of this ROI is then increased to 25% above the minimum ROI size dimensions  */
  /*     specified as arguments to function FacePulseRate, if it is not as large. This ROI increase is */
  /*     based upon the assumption that regions detected by the skin-detection algorithm are smaller  */
  /*     than the size of ROIs returned by the face-detection algorithm(s); the increase is intended to  */
  /*     capture the entire face if the face is frontal. This expansion is returned by function */
  /*     SkinDetect_EnlargeROI, which is called by function SkinDetect_SelectRegion. */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
  /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
  /*     licensing, please contact the author.      */
  /* %%%%% Code-generation settings %%%%%% */
  /* Called during code generation */
  /* code generation running */
  /* Inline function */
  /* Declare variables: */
  /* Note: for many, set bounds so that these variables do not use dynamic memory allocation, */
  /* increasing efficiency. */
  /*                                                                               Upp. Bounds  Var. Size (T/F) */
  /* Preallocate variables: */
  RegionSelectedLinIdx_size[0] = 0;
  RegionSelectedLinIdx_size[1] = 0;
  c_RegionSD_Cr_PassThresholdTF_L = 0;
  *HasROITF_SkinNotPresent_ith = false;
  *SkinTF_ith = false;
  ROI_Selected_ith_size[0] = 0;
  ROI_Selected_ith_size[1] = 4;

  /* Preallocate struct for diagnostic data */
  /* Local function. */
  /* %%%%% Input validation %%%%%% */
  /* Validate whether inputs BoundingBoxSkin and ROI_SR_ith are type int16. */
  /* Should be type int16 because the function is implemented to assign values of this type. */
  /* Must be an integer type because no rounding is conducted. */
  /* A non-matching type would be due to an implementation error. */
  /* Note: ROI_SR_ith will be empty during first-read operations */
  /* %%%%% Assign logical value that skin-detection algorithm was attempted for ith frame %%%%%% */
  ROIDiagnostic_ROISkin_ith->RegionSkinROIAttempted = true;

  /* %%%%% Partition bounded area of frame into regions %%%%%% */
  /* Partition bounded area of frame into regions for preparation to submit the regions to the  */
  /* skin-detection algorithm. The frame is partitioned through skin segmentation and the superposition  */
  /* of grid lines.  */
  /* Record bounding box used for scan for display on output video     */
  /* Convert from type int16 to type uint16 because signed operations not conducted with this variable. */
  ROIDiagnostic_ROISkin_ith->BBox_Scan_SkinAlg.size[0] = 1;
  ROIDiagnostic_ROISkin_ith->BBox_Scan_SkinAlg.size[1] = 4;
  ROIDiagnostic_ROISkin_ith->BBox_Scan_SkinAlg.data[0] = (uint16_T)
    BoundingBoxSkin[0];
  ROIDiagnostic_ROISkin_ith->BBox_Scan_SkinAlg.data[1] = (uint16_T)
    BoundingBoxSkin[1];
  ROIDiagnostic_ROISkin_ith->BBox_Scan_SkinAlg.data[2] = (uint16_T)
    BoundingBoxSkin[2];
  ROIDiagnostic_ROISkin_ith->BBox_Scan_SkinAlg.data[3] = (uint16_T)
    BoundingBoxSkin[3];

  /* Note: 'SkinDetect_PartitionRegions' is a custom function located within folder 'FacePulseRate'. */
  /*  Logical matrix (i.e, skin-segmentation mask) from skin segmentation where */
  /*  pixels classified as skin == true. */
  /*  N x 1 non-scalar struct with field 'PixelIdxList', where N equals the */
  /*  number of regions. Each row consists of linear indices, of type uint32, */
  /*  corresponding to the pixels of a given region. */
  /*  Number of regions. Scalar; int32. */
  /*  N x 1 column vector indicating the number of pixels of each region, where */
  /*  N equals the number of regions; type single. */
  /*  N x 2 matrix of the centroids (X, Y) of each region, where N equals the */
  /*  number of regions; type int16. */
  /*  Bounded area in RGB colorspace, separated by channel; type uint8. */
  /*  Bounded area in YCbCr colorspace, separated by channel; type single. */
  /*  Skin-segmentation mask dimensions. */
  /* SkinDetect_PartitionRegions    Partition bounded area of a frame into regions that will be   */
  /*                                submitted to steps of the skin-detection algorithm.  */
  /*  */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, called by function SkinDetect. */
  /*  */
  /*  */
  /*     Code Generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*  */
  /*     Description */
  /*     ----------- */
  /*  */
  /*     Partition bounded area of a frame into two-dimensional regions for use in steps of the skin- */
  /*     detection algorithm, which is conducted by function SkinDetect.  */
  /*  */
  /*     Before partitioning, crop the frame to a bounded area specified by a bounding box  */
  /*     (BoundingBoxSkin). In the first-read operations, the bounding box is set by function  */
  /*     ROIMeans_FirstRead_SetBoundingBoxes; in the second-read operations, the bounding box is set by  */
  /*     function ROIMeans_SecondRead_SkinDetect.  */
  /*      */
  /*     To partition, first apply skin segmentation and return a logical matrix (also termed a      */
  /*     skin-segmentation mask) where pixels classified as skin = true. Then, break regions of true  */
  /*     values into smaller regions by applying grid lines at specified intervals of rows and columns.  */
  /*     As the grid lines consist of false values, this has the effect of breaking regions into  */
  /*     regions that fit within the grid lines. */
  /*     */
  /*     The skin segmentation mask with gridlines superimposed (IsSkinMask) is assigned as output.  */
  /*     Additionally, an index of pixels corresponding to each region and the centroids of each region */
  /*     are assigned as output. Regarding the centroids, note that a centroid may actually fall on a  */
  /*     pixel marked as non-skin by the skin-segmentation mask if this pixel is the centroid of a  */
  /*     region. */
  /*  */
  /*     Additionally, the output of intermediate operations, such as color channels of the bounded  */
  /*     frame, is returned for reuse by other steps of the skin-detection algorithm.    */
  /*  */
  /*     For further description of purpose of partitioning, see section "Partitioning frame into  */
  /*     regions to classify" in the notes of function SkinDetect. */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
  /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
  /*     licensing, please contact the author.    */
  /* %%%%% Code-generation settings %%%%%% */
  /* Inline function */
  /* Call function as extrinsic so that stack trace can be displayed */
  /* Declare variables: */
  /*                                              Upp. Bounds  Var. Size (T/F) */
  /* %%%%% Bound ith frame and return skin-segmentation mask %%%%%% */
  /* For the bounded area of the frame, conduct skin-segmentation to return a 2-dimensional logical    */
  /* matrix where pixels classified as skin are true. */
  /* The skin-segmentation function converts the frame to YCbCr color channels for its operations; for */
  /* efficiency, return these color channels for reuse by other functions that require these channels */
  /* because the YCbCr conversion is computationally expensive. */
  /* Height and width of bounding box */
  nRows_IsSkinMask = BoundingBoxSkin[3];

  /* Prevent dynamic memory allocation from colon operator by asserting lengths */
  /* Note: these values also constrain the maximum frame dimensions that can be used in function */
  /* FacePulseRate. If modified, modify the maximum frame dimensions stated in the description in */
  /* function FacePulseRate. */
  /* Arguments to function SkinSegmentMask, which returns the skin-segmentation mask: */
  /*  - Bound frame, separate by colorspace channels, and convert to type single */
  /*    These channels are also used for function SkinDetect_RegionMetrics, which is called by function */
  /*    SkinDetect_RejectRegions.  */
  /*    Local function. */
  BoundSeparateChannels(emlrtRootTLSGlobal, VidFrame, BoundingBoxSkin,
                        BoundingBoxSkin[3], BoundingBoxSkin[2],
                        VideoReadConfig_VidObjWidth,
                        VideoReadConfig_VidObjHeight, RBounded_Uint8,
                        GBounded_Uint8, BBounded_Uint8);

  /*  - Assign as a variable rather than a constant for code-generation purposes */
  /* Note: SkinSegmentMask is a custom function located within folder 'FacePulseRate'.  */
  /*  logical matrix where pixels classified as skin = true */
  /*  bounded frame in YCbCr colorspace, separated by channel; type single */
  /*  Bounded frame in RGB colorspace separated by */
  /*  channel; type uint8. */
  /*  Unused arguments */
  /*  Number of rows of an input matrix */
  /*  Number of columns of an input matrix */
  /*  Whether to return a count of pixels classified */
  /*  as skin. */
  /*  Whether to use thresholds that are tailored */
  /*  Whether to return Y channel of the YCbCr */
  /*  colorspace. */
  /*  Whether to return Cb and Cr channels of the */
  /*  YCbCr colorspace. */
  /*  Whether to return the H and S channels of the */
  /*  HSV colorspace (HSingle). */
  /*  Whether to use severe tailored thresholds */
  /*  Whether the morphological close operation will */
  /*  be conducted with a high level of severity. */
  /*  Optional X-coordinate offset; use -1 to */
  /*  ignore; type int32. */
  /*  Optional Y-coordinate offset; use -1 to */
  /*  ignore; type int32. */
  /*  Configurations */
  /*  Whether to use compiled functions */
  /* SkinSegmentMask   Return logical matrix, or skin-segmentation mask, where pixels classified as  */
  /*                   skin are true. Wrapper function for function SkinSegmentMask_Ops. */
  /*    */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, this function is called by functions ... */
  /*         - ConfirmSkinPresent (which is called by functions FaceDetect_ROIValidate,   */
  /*           SkinDetect_SelectedRegionROI, and ROIMeans_TakeMeans) */
  /*         - SkinDetect_PartitionRegions (which is called by function SkinDetect)           */
  /*         - ROIMeans_TakeMeans (which is called by functions ROIMeans_FirstRead_TakeMeans and */
  /*           ROIMeans_SecondRead_TakeMeans) */
  /*         - ROIMeans_FirstRead_CollectSkinColorSamples (which is called by function */
  /*           ROIMeans_FirstRead) */
  /*  */
  /*  */
  /*     Code Generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*  */
  /*     Description */
  /*     ----------- */
  /*  */
  /*     Return logical matrix, or skin-segmentation mask, where pixels classified as skin are true. */
  /*     This is a wrapper function for function SkinSegmentMask_Ops. For a description of the  */
  /*     skin-segmentation operations, see function SkinSegmentMask_Ops. */
  /*  */
  /*     Execute either the compiled or non-compiled function depending on argument  */
  /*     UseCompiledFunctionsTF. */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
  /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
  /*     licensing, please contact the author.  */
  /* %%%%% Code-generation settings %%%%%% */
  /* Inline function */
  /* Compiled functions enabled and code generation not running */
  /* Value of SkinSegmentConfig.UseCompiledFunctionsTF assigned in function  */
  /* SkinSegment_ConfigSetup.  */
  /* Note: SkinSegmentMask_Ops is a custom function located within folder FacePulseRate. */
  /* SkinSegmentMask_Ops   Return logical matrix, or skin-segmentation mask, where pixels classified as   */
  /*                       skin are true. */
  /*                                                */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, called by function SkinSegmentMask. */
  /*  */
  /*  */
  /*     Code generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*     Compiled file: The compiled file included in folder FacePulseRate  */
  /*     (SkinSegmentMask_Ops_mex.mexw64) only compatible on Windows platforms.        */
  /*  */
  /*  */
  /*     Description */
  /*     ----------- */
  /*  */
  /*     -- Combined Use of YCbCr and HSV Colorspaces for Pixel-Color Thresholds -- */
  /*  */
  /*     The combined used of the YCbCr and HSV colorspaces is based on ... */
  /*     (1) Dahmani et al. (2020), who found that using both improved skin classification compared to */
  /*         the use of either alone. */
  /*     (2) The observation that using only the YCbCr colorspace did not permit enough diversity of */
  /*         individual differences in skin color. Specifically, Y-minimum and Cr-minimum must be at  */
  /*         least as low as the defaults to avoid oversegmentation in individuals with darker average */
  /*         skin colors when ambient illumination is rather low. However, these defaults also permit  */
  /*         pixel values from objects that should be segmented out; for example, the Cr-minimum at  */
  /*         this level permits pixel values from overhead lamps. Applying the HSV thresholds in  */
  /*         addition to the YCbCr thresholds segmented out these extraneous objects. */
  /*  */
  /*     -- YCbCr Pixel-Color Thresholds --  */
  /*  */
  /*     YCbCr color thresholds in use: */
  /*  */
  /*     - Y-channel minimum */
  /*     - Y-channel maximum (tailored-thresholds only) */
  /*     - Cb-channel minimum */
  /*     - Cb-channel maximum  */
  /*     - Cr-channel minimum */
  /*     - Cr-channel maximum  */
  /*  */
  /*     Apply color thresholds to individual pixels from the luminance (Y), Cb chroma (Cb), and Cr  */
  /*     chroma (Cr) channels of the YCbCr colorspace. */
  /*  */
  /*     Use either the generic YCbCr color thresholds or tailored YCbCr color thresholds. The use of */
  /*     tailored thresholds is specified by argument TailoredThresholdsTF. However, generic thresholds */
  /*     are used when TailoredThresholdsTF is true if the criterion for using tailored thresholds has */
  /*     not been satisfied, which is indicated by DontUseTailoredTF == true.  */
  /*  */
  /*         Generic Thresholds */
  /*  */
  /*     The YCbCr generic color thresholds (SkinSegmentArgs.YCbCrThresholdsGeneric) are used when */
  /*     TailoredThresholdsTF is set to false. Thresholds include a Y-channel minimum, Cb-channel  */
  /*     minimum and maximum, Cr-channel minimum and maximum, and Cb-to-Cr ratio minimum and maximum. */
  /*      */
  /*     The threshold values are set by an argument, SkinSegmentYCbCrThresholdsGeneric, to function  */
  /*     FacePulseRate. If the argument is not specified, default values are used. The default Y, Cb,   */
  /*     and Cr minimums and maximums are based on a consultation of the values provided in iphys  */
  /*     toolbox (McDuff & Blackford, 2019). These values were modified somewhat as a result of   */
  /*     testing. The Cb-to-Cr ratio minimum and maximum and not used in iphys toolbox; these values  */
  /*     were developed through testing. */
  /*       */
  /*     Function SkinSegment_ConfigSetup sets the values for SkinSegmentArgs.YCbCrThresholdsGeneric */
  /*     based on argument SkinSegmentThresholdsGenericYCbCr.     */
  /*  */
  /*     Within the current function, the YCbCr generic threshold operations are conducted by function   */
  /*     SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold. */
  /*  */
  /*         Tailored Thresholds */
  /*  */
  /*     The YCbCr tailored thresholds (SkinSegmentArgs.YCbCrThresholdsGeneric) are used when */
  /*     TailoredThresholdsTF is set to true. The threshold values are set based upon skin-color   */
  /*     samples collected from the input video. The threshold types include those used in the generic */
  /*     thresholds as well as a Y-channel maximum. The Y-channel maximum may be more sensitive than */
  /*     other thresholds to individual differences in facial colors. Due to this sensitivity, this */
  /*     value is not used for generic thresholds but is used for tailored thresholds as tailored */
  /*     thresholds are based upon the face in the video. */
  /*  */
  /*     The skin-color samples are collected from the input video. For details on the collection of  */
  /*     skin-color samples, see function ROIMeans_FirstRead_CollectSkinColorSamples. Before a */
  /*     sample is collected by function ROIMeans_FirstRead_CollectSkinColorSamples, function  */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples calls function SkinSegmentMask to attempt to  */
  /*     isolate pixel colors corresponding to skin. When SkinSegmentMask is called by function  */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples samples, TailoredThresholdsTF is set to false; that  */
  /*     is, generic thresholds are used. As tailored thresholds are based upon skin-color samples that */
  /*     were filtered by the generic thresholds, the tailored thresholds can be expected to be more */
  /*     stringent compared to the generic thresholds. The term "sample" refers to two values taken  */
  /*     from each YCbCr color channel of skin-segmented ROI. Specifically, the the minimum and maximum */
  /*     color values are taken from each channel.  */
  /*      */
  /*     Skin-color samples used for tailored YCbCr thresholds are collected by function  */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples, which is called by function ROIMeans_FirstRead.  */
  /*     For details on the collection of skin-color samples, see function  */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples.  */
  /*  */
  /*     After a certain number of samples has been collected, the samples are used to set the tailored  */
  /*     threshold values. The setting of thresholds from skin-color samples is conduted by function */
  /*     SkinSegment_SetThresholds. The number of samples required to set the tailored threshold  */
  /*     values, SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold, is specified by function  */
  /*     SkinSegment_ConfigSetup. This value can only be modified by adjusting the code within this */
  /*     function.  */
  /*  */
  /*     It has been observed that if the skin-color samples are too heavily concentrated within a  */
  /*     particular portion of the video, the thresholds that come from them can be too restrictive.  */
  /*     This is likey because samples limited to a brief portion of the video do not contain a */
  /*     sufficient level enough heterogeneity to reflect the color variations across the video. To  */
  /*     address this restrictiveness, the thresholds are reset periodically. Specifically, the  */
  /*     thresholds are reset after a specified number of frames has elapsed since the thresholds were  */
  /*     last set or reset. This number of frames is specified by  */
  /*     SkinSegmentConfig.TailoredData.ThresholdOpsInterval, which is set by function */
  /*     SkinSegment_ConfigSetup. This value can only be modified by adjusting the code within function */
  /*     SkinSegment_ConfigSetup. */
  /*  */
  /*     Although resetting the thresholds addresses the lack of heterogeneity across most of the  */
  /*     video, heterogeneity may still be unacceptably low between the first setting of the thresholds */
  /*     and the first resetting of the thresholds. This may occur if the skin-color samples are */
  /*     collected within close proximity. One condition that causes samples to be collected within  */
  /*     close proximity is a low frame-skipping rate (ROIGeneralConfig.ROISkipFrameThreshold; see */
  /*     function ROIGeneralConfig_Setup). To increase the heterogeneity in this case, the number of  */
  /*     skin-color samples required before the first thresholds are set  */
  /*     (SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold) is increased when the   */
  /*     frame-skipping rate is relatively low (see funtion SkinSegment_ConfigSetup).  */
  /*  */
  /*     Before the required number of skin-color samples has been collected, generic thresholds are */
  /*     used in place of tailored thresholds. If argument TailoredThresholdsTF is set to true,  */
  /*     specifying that tailored thresholds should be used, generic thresholds will be used if the  */
  /*     required number of samples has not been collected. Within the current function, the flag */
  /*     DontUseTailoredTF is set to true in this case to indicate that generic thresholds should be   */
  /*     used in place of tailored thresholds. */
  /*      */
  /*     For each skin-color sample, minimums and maximums are taken from each colorspace channel.  */
  /*     These values are set aside until the thresholds are to be set or reset. When setting or  */
  /*     resetting occurs, percentiles are applied to these values to extract the values at lower and */
  /*     upper percentiles. The value at the lower percentile becomes the lower threshold and the */
  /*     value at the upper percentile becomes the upper percentile. For example, suppose the lower and  */
  /*     upper percentiles are specified as 1.5 and 98.5, respecively. From all skin-color samples */
  /*     previously collected, the sample values from each channel that occur at the 1.5th percentile   */
  /*     and 98.5th percentile become the lower the upper thresholds, respectively. One point of  */
  /*     confusion may be that the terms "minimum" and "maximum" are used for two purposes here. */
  /*     The first use is in taking the minimum and maximum of each skin-color sample. These minimums */
  /*     and maximums are set aside until the percentiles are applied. When the percentiles are  */
  /*     applied, the lower percentile becomes the lower threshold and the upper percentile becomes the */
  /*     upper threshold. Although the terms "upper" and "lower" and used to refer to these thresholds */
  /*     for clarity, the terms "minimum" and "maximum" would also be appropriate. That is, the lower, */
  /*     or minimum, threshold is selected from a collection of minimum values; the upper, or maximum, */
  /*     threshold is selected from a collection of maximum values. */
  /*  */
  /*     One set of percentiles is used for the Y, Cb, Cr, Cb-to-Cr ratio, and H thresholds, and a  */
  /*     separate set of percentiles is used for the S thresholds. A separate set of percentiles is  */
  /*     used for the S thresholds because it has been observed that a wider range is appropriate for */
  /*     the S color channel. These percentiles are specified by function SkinSegmentConfig_Setup. The */
  /*     percentiles can be modified only by adjusting the code within SkinSegmentConfig_Setup. */
  /*  */
  /*     Within the current function, the YCbCr tailored threshold operations are conducted by function   */
  /*     SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold. */
  /*  */
  /*     -- HSV Pixel-Color Thresholds -- */
  /*    */
  /*     HSV color thresholds in use: */
  /*  */
  /*     - H-channel maximum */
  /*     - S-channel minimum */
  /*     - S-channel maximum (tailored-thresholds only) */
  /*  */
  /*     Apply color thresholds to individual pixels from the hue (H) and saturation (S) channels of   */
  /*     the HSV colorspace. */
  /*      */
  /*     Use either the generic HSV color thresholds or tailored HSV color thresholds. The use of */
  /*     tailored thresholds is specified by argument TailoredThresholdsTF. However, generic  */
  /*     thresholds are used when TailoredThresholdsTF is true if the criterion for using tailored  */
  /*     thresholds has not been satisfied, which is indicated by DontUseTailoredTF == true. */
  /*  */
  /*         Generic Thresholds */
  /*  */
  /*     The HSV generic color thresholds (SkinSegmentArgs.HSVThresholdsGeneric) are used when */
  /*     TailoredThresholdsTF is set to false. Thresholds include an H-channel maximum and an S-channel */
  /*     minimum. */
  /*      */
  /*     The threshold values are set by an argument, SkinSegmentThresholdsGenericHSV, to function  */
  /*     FacePulseRate. If the argument is not specified, default values are used. The default H and S   */
  /*     minimums and maximums are based on testing by DPM.  */
  /*       */
  /*     Function SkinSegment_ConfigSetup sets the values for SkinSegmentArgs.HSVThresholdsGeneric */
  /*     based on argument SkinSegmentThresholdsGenericHSV.     */
  /*  */
  /*     Within the current function, the HSV generic threshold operations are conducted by function   */
  /*     SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold. */
  /*  */
  /*         Tailored Thresholds */
  /*  */
  /*     The H and S tailored color thresholds (SkinSegmentArgs.HSThresholdsTailored) are used when */
  /*     TailoredThresholdsTF is set to true. The combination of a maximum for the H channel and a   */
  /*     minimum and a maximum for the S channel is based on Dahmani et al. (2020).  */
  /*      */
  /*     As with the tailored YCbCr thresholds, these thresholds are set based upon skin-color samples  */
  /*     collected from the input video. The process of setting the H and S tailored thresholds is   */
  /*     identical to the process of setting the tailored YCbCr thresholds.  */
  /*  */
  /*     If argument TailoredThresholdsTF is specified as true but the required number of samples has */
  /*     not been acquired, the H and S tailored thresholds will not be used. As with the tailored  */
  /*     YCbCr thresholds, the flag DontUseTailoredTF will be set to true to cause the H and S tailored  */
  /*     thresholds not to be used. */
  /*  */
  /*     Within the current function, the H and S tailored threshold operations are conducted by    */
  /*     function SkinSegmentMask_Threshold_Colors, which is called by function  */
  /*     SkinSegmentMask_Threshold. */
  /*  */
  /*     -- Low- and High-Severity Tailored Thresholds --  */
  /*  */
  /*     When TailoredThresholdsSevereTF == true, high-severity thresholds are used when conducting */
  /*     segmentation with the tailored YCbCr and HSV thresholds. High-severity thresholds are used for  */
  /*     applications where the priority is to reduce false positives (pixels incorrectly classified as */
  /*     skin) at the expense of a greater number false negatives (pixels incorrectly classified as  */
  /*     non-skin). When false, low-severity thresholds are used. Low-severity thresholds are used for  */
  /*     applications where a balance is desired between false positives and false negatives.      */
  /*  */
  /*     -- Local-Range Pixel Threshold --  */
  /*  */
  /*     The local-range pixel threshold classifies pixels based upon the homogeneity of color values */
  /*     of nearby, or local, pixels. When the local range is relatively homogeneous rather than */
  /*     heterogeneous, the value of the local range will be lower. A relatively homogeneous color  */
  /*     range of a given pixel is used as a heuristic of a pixel corresponding to skin. This is based   */
  /*     on the assumption that true skin tends to occur in regions of homogeneous color. When the  */
  /*     local range of a pixel falls below a specified threshold (SkinSegmentArgs.HThresholdTailored),  */
  /*     the pixel is classified as skin. */
  /*  */
  /*     The threshold for local range is a static value; that is, it is not set by assessment of color  */
  /*     samples. The threshold value is set by function SkinSegmentConfig_Setup. The value can only be  */
  /*     modified by adjusting the code within SkinSegmentConfig_Setup. The effectiveness of the value  */
  /*     used was established through testing.  */
  /*  */
  /*     Within the current function, the local-range pixel threshold operations are conducted by    */
  /*     function SkinSegmentMask_Threshold_Range, which is called by function  */
  /*     SkinSegmentMask_Threshold. */
  /*  */
  /*     -- Morphological Close of Patchy Regions --  */
  /*  */
  /*     Following the application of these thresholds, a two-dimensional logical matrix is assigned  */
  /*     where pixels that satisfied all thresholds are classified as true and pixels that did not are */
  /*     classified as false. A morphological close operation is then applied to the logical matrix.  */
  /*     The morphological close tends to fill in classification holes, where a hole is loosely defined  */
  /*     as a region of pixels classified as true that are enclosed by pixels classified as false.   */
  /*     Holes are filled in based on the assumption that true skin tends to be distributed in the face   */
  /*     in contiguous, rather than patchy, regions. */
  /*      */
  /*     The morphological close fills in holes only below a certain shape and size, which are    */
  /*     determined by the shape and size of the morphological structuring element, such that many  */
  /*     holes are not filled. Otherwise, large regions classified as true -- which are assumed to be  */
  /*     regions of skin -- may be erroneously filled. For a description on the choice of structuring  */
  /*     element used, see function SkinSegmentMask_MorphClose.  */
  /*  */
  /*     Within the current function, the morphological close operations are conducted by function   */
  /*     SkinSegmentMask_Threshold_MorphClose, which is called by function SkinSegmentMask_Threshold. */
  /*  */
  /*     -- Return Skin-Segmentation Mask Without Performing Colorspace Conversion -- */
  /*  */
  /*     To return a skin-segmentation mask without performing colorspace conversion, the colorspaces */
  /*     needed for skin-segmentation can be entered as input. These include YSingle, CbSingle,  */
  /*     CrSingle, HSingle, and SSingle. If all of these color channels are non-empty, colorspace */
  /*     conversion will not be performed. */
  /*  */
  /*     Additionally, IsSkinMask_Range, a skin-segmentation based upon the local range, can also be */
  /*     be entered as input.  */
  /*  */
  /*     A case where these may be entered is where skin segmentation is first run with either tailored */
  /*     thresholds on or off and it is desired to rerun the skin segmentation using tailored or non- */
  /*     tailored thresholds. In this case, the color channels and IsSkinMask_Range would have been */
  /*     assigned previously and can be reused. */
  /*  */
  /*     -- Color Channel Return Values -- */
  /*  */
  /*     The H and S channels of the HSV colorspace and the Y, Cb, and Cr channels of the YCbCr  */
  /*     colorspace are assigned during the operations of function SkinSegmentMask_Threshold. For  */
  /*     efficiency, these channels can be returned for reuse by other functions within function  */
  /*     FacePulseRate. One use of these values by another function is to periodically reset the color   */
  /*     thresholds (YCbCrThresholds_Tailored, HSThresholds_Tailored) used by the current function;   */
  /*     this is conducted by function SkinSegment_SetThresholds. To return these channels for reuse by */
  /*     other functions, the values are assigned to matrices, which are quite large due to the number  */
  /*     of pixels processed. Assignment to these large matrices may incur additional processing time.  */
  /*     To avoid this processing time when values are not to be reused, whether the channels are  */
  /*     returned can be controlled by arguments.  */
  /*  */
  /*     Argument ReturnYTF determines whether the Y channel is returned. Argument ReturnCbCrTF  */
  /*     determines whether the Cb and Cr channels are returned. Argument ReturnHSTF determines whether  */
  /*     the H and S channels are returned.     */
  /*            */
  /*  */
  /*     Notes */
  /*     ----- */
  /*  */
  /*     For detailed descriptions of the implementation of settings used in this function, see  */
  /*     function SkinSegmentConfig_Setup, which sets the settings. */
  /*  */
  /*     To view an image segmented with the skin-segmentation mask returned by this function, run the */
  /*     following code. The resulting image will be segmented in the same manner it is segmented in */
  /*     function FacePulseRate. */
  /*     SkinSegmented =        ... Segmented image */
  /*         AreaToSegment .*   ... Original image prior to segmentation */
  /*         uint8(IsSkinMask); %   Segmentation mask */
  /*  */
  /*  */
  /*     Requires */
  /*     -------- */
  /*  */
  /*         - Image Processing Toolbox (when non-compiled functions are used) */
  /*  */
  /*  */
  /*     References */
  /*     ---------- */
  /*  */
  /*     For helpful Matlab documentation on image segmentation operations, see the Matlab   */
  /*     documentation topic "image segmentation". */
  /*  */
  /*     Dahmani, D., Cheref, M., & Larabi, S. (2020). Zero-sum game theory model for segmenting skin  */
  /*     regions. Image and Vision Computing, 103925. */
  /*  */
  /*     McDuff, D., & Blackford, E. (2019, July). iphys: An open non-contact imaging-based  */
  /*     physiological measurement toolbox. In 2019 41st Annual International Conference of the IEEE  */
  /*     Engineering in Medicine and Biology Society (EMBC) (pp. 6521-6524). IEEE. */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
  /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
  /*     licensing, please contact the author. */
  /* %%%%% Code generation specifications %%%%%% */
  /* Inline function */
  /* Declare variables: */
  /*                               Upp. Bounds    Var. Size (T/F) */
  /* %%%%% Parse input arguments %%%%%% */
  /* Note: SkinSegmentMask_ParseArgs is a custom function located within folder FacePulseRate. */
  /* SkinSegmentMask_ParseArgs   Parse imput arguments to function SkinSegmentMask_Ops.  */
  /*                                                */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, called by function SkinSegmentMask_Ops. */
  /*  */
  /*  */
  /*     Code generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation.     */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
  /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
  /*     licensing, please contact the author.  */
  /* Inline function */
  /* %%%%% Local range %%%%%% */
  /*  - Structuring element width for calculating local range for a given pixel */
  /* Value assigned in function SkinSegment_ConfigSetup. */
  /*  - Individual pixel local color range threshold  */
  /* Value assigned in function SkinSegment_ConfigSetup. */
  /* Should be type uint8 for fastest evaluation.  */
  /* %%%%% Color thresholds %%%%%% */
  /*  - Individual pixel YCbCr colorspace skin-segmentation generic thresholds */
  /* Values assigned in function SkinSegment_ConfigSetup.   */
  /* Note: these should be in type single for fastest evaluation. */
  for (b_i = 0; b_i < 7; b_i++) {
    YCbCrThresholds_Generic[b_i] =
      SkinSegmentConfig->Args.YCbCrThresholdsGeneric[b_i];
  }

  emxInit_boolean_T(emlrtRootTLSGlobal, &IsSkinMask, 2, true);
  emxInit_real32_T(&YBounded_Single, 2, true);
  emxInit_real32_T(&CbBounded_Single, 2, true);
  emxInit_real32_T(&CrBounded_Single, 2, true);
  emxInit_boolean_T(emlrtRootTLSGlobal, &IsSkinMask_Range, 2, true);
  emxInit_boolean_T(emlrtRootTLSGlobal, &IsSkinMask_ROISelected, 2, true);

  /* Function SkinSegmentMask_Threshold_Colors will only use < and > rather than <= and >=, so these  */
  /* values are adjusted so that < and > are equivalent to <= and >=, respectively. */
  YCbCrThresholds_Generic[0] = SkinSegmentConfig->Args.YCbCrThresholdsGeneric[0]
    - 1.0F;

  /* Y min */
  YCbCrThresholds_Generic[1] = SkinSegmentConfig->Args.YCbCrThresholdsGeneric[1]
    - 1.0F;

  /* Cb min */
  /* Cr min */
  YCbCrThresholds_Generic[5] = SkinSegmentConfig->Args.YCbCrThresholdsGeneric[5]
    - 0.1F;

  /* Cb-to-Cr ratio min */
  YCbCrThresholds_Generic[2] = SkinSegmentConfig->Args.YCbCrThresholdsGeneric[2]
    + 1.0F;

  /* Cb max */
  YCbCrThresholds_Generic[4] = SkinSegmentConfig->Args.YCbCrThresholdsGeneric[4]
    + 1.0F;

  /* Cr max */
  YCbCrThresholds_Generic[3] = (SkinSegmentConfig->Args.YCbCrThresholdsGeneric[3]
    - 1.0F) + 0.1F;

  /* Cb-to-Cr ratio max */
  /*  - Individual pixel HSV colorspace skin-segmentation generic thresholds */
  /* Values assigned in function SkinSegment_ConfigSetup.   */
  /* Note: these should be in type single for fastest evaluation. */
  /* Function SkinSegmentMask_Threshold_Colors will only use < and > rather than <= and >=, so these  */
  /* values are adjusted so that < and > are equivalent to <= and >=, respectively. */
  HSThresholds_Generic[1] = SkinSegmentConfig->Args.HSThresholdsGeneric[1] -
    0.1F;

  /* S min */
  HSThresholds_Generic[0] = SkinSegmentConfig->Args.HSThresholdsGeneric[0] +
    0.1F;

  /* H max */
  /*  - Individual pixel YCbCr and HSV colorspaces skin-segmentation tailored thresholds */
  /* Values assigned in function SkinSegment_SetThresholds. */
  /* Note: a threshold is not used for the value (V) channel of the HSV colorspace.  */
  /* Note: these should be in type single for fastest evaluation.  */
  /*    - Low-severity tailored thresholds */
  /* YCbCr channels */
  /* H and S channels */
  /*  - Flag not to use tailored thresholds */
  /* Whether a sufficient number of skin-color samples was collected to activate tailored skin */
  /* segmentation. For details on the collection skin-color samples, see function */
  /* ROIMeans_FirstRead_CollectSkinColorSamples. */
  /* Value assigned by function SkinSegment_SetThresholds. */
  /* %%%%% Morphological close %%%%%% */
  /*  - Severity of morphological close */
  /*    - High severity of morphological close operation */
  /*    - Low severity of morphological close operation */
  /* %%%%% Number of elements in input matrices %%%%%% */
  /* Number of elements of a given matrix */
  /* Scalar; type int32. */
  /* end function */
  /* %%%%% Apply pixel-color and pixel-color local range thresholds %%%%%% */
  /* Apply individual pixel-color and pixel-color local range thresholds to assign a skin-segmentation  */
  /* mask. */
  /* Note: SkinSegmentMask_Threshold is a custom function located within folder FacePulseRate. */
  IsSkinMask_Range->size[0] = 0;
  IsSkinMask_Range->size[1] = 0;
  SkinSegmentMask_Threshold(emlrtRootTLSGlobal, RBounded_Uint8, GBounded_Uint8,
    BBounded_Uint8, IsSkinMask_Range, BoundingBoxSkin[3], BoundingBoxSkin[2],
    BoundingBoxSkin[3] * BoundingBoxSkin[2], YCbCrThresholds_Generic,
    !SkinSegmentConfig->Args.c_SkinColorSamples_NThresholdPa,
    SkinSegmentConfig->Args.YCbCrThresholdsTailored_Sev, HSThresholds_Generic,
    SkinSegmentConfig->Args.HSThresholdsTailored_Sev,
    SkinSegmentConfig->Args.RangeSEWidth, SkinSegmentConfig->Args.RangeThreshold,
    IsSkinMask, YBounded_Single, CbBounded_Single, CrBounded_Single,
    HBounded_Single_data, HBounded_Single_size, SBounded_Single_data,
    SBounded_Single_size);

  /* %%%%% Morphologically close skin-segmentation mask regions with patchy classifications %%%%%% */
  /* Note: SkinSegmentMask_MorphClose is a custom function located within folder FacePulseRate. */
  b_i = IsSkinMask_ROISelected->size[0] * IsSkinMask_ROISelected->size[1];
  IsSkinMask_ROISelected->size[0] = IsSkinMask->size[0];
  IsSkinMask_ROISelected->size[1] = IsSkinMask->size[1];
  emxEnsureCapacity_boolean_T(IsSkinMask_ROISelected, b_i);
  NCentroids = IsSkinMask->size[0] * IsSkinMask->size[1];
  emxFree_boolean_T(&IsSkinMask_Range);
  for (b_i = 0; b_i < NCentroids; b_i++) {
    IsSkinMask_ROISelected->data[b_i] = IsSkinMask->data[b_i];
  }

  emxInit_uint32_T(&IsSkinMask_PixelColorPacked, 2, true);

  /* SkinSegmentMask_MorphClose    Morphologically close regions with patchy skin classification to  */
  /*                               refine the skin-segmentation mask previously assigned by comparison  */
  /*                               to thresholds. */
  /*                                                                            */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by function SkinSegmentMask_Ops. */
  /*  */
  /*  */
  /*     Code Generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*  */
  /*     Description */
  /*     ----------- */
  /*  */
  /*     For a description of the assumptions behind the use of a morphological close to classify */
  /*     pixels as skin, see function SkinSegmentMask_Ops.   */
  /*  */
  /*     Apply a morphological close operation to the skin-segmentation mask resulting from thresholds */
  /*     previously applied (by function SkinSegmentMask_Threshold). The morphological close tends to  */
  /*     fill in classification holes, where a hole is loosely defined as a region of pixels classified  */
  /*     as true that are enclosed by pixels classified as false. The morphological close fills in  */
  /*     holes only below a specified size (specified by a morphological structuring element), such  */
  /*     that many holes are not filled.     */
  /*       */
  /*     A morphological dilation followed by a morphological erosion is conducted to perform the   */
  /*     morphological close. These operations are conducted by Matlab functions imerode and imdilate. */
  /*     Although a Matlab function is available to conduct a close (imclose), it has been observed   */
  /*     that using imerode followed by imdilate is more efficient. */
  /*  */
  /*     For a description of the choice of structuring element used in the morphological close, see  */
  /*     the description below in section "Assign structuring element".   */
  /*  */
  /*     -- Structuring Element Specifications -- */
  /*  */
  /*     - Severity == high: */
  /*  */
  /*     Use liberal dilation and erosion to mask non-skin pixels  */
  /*     Do so by using a large morphological structuring element (SE), which specifies the size of     */
  /*     dilation and erosion to carry out on each pixel (where pixel == 0). High severity may favor */
  /*     the rejection of non-skin pixels over the retention of of true-skin pixels. Function  */
  /*     FaceDetect and SkinDetect specify skin segmentation with high severity. This severity may be   */
  /*     useful for these functions because the priority in these functions is avoiding non-skin  */
  /*     pixels rather than retaining as many pixels as possible that are actually skin.     */
  /*  */
  /*     - Severity == low: */
  /*  */
  /*     Use moderate dilation and erosion to mask non-skin pixels. */
  /*     Do so by using a medium morphological structuring element (SE), which specifies the size of   */
  /*     dilation to carry out on each pixel (where pixel == 0). Compared to high severity, low  */
  /*     severity is intended to strike a balance between rejecting pixels and accepting pixels that    */
  /*     are actually skin. Function ROIMeans_TakeMeans specifies skin segmentation with low severity.  */
  /*     This low severity may be useful for the purpose of function ROIMeans_TakeMeans, which is to    */
  /*     calculate the accurate mean of an ROI. The ROIs that ROIMeans_TakeMeans processes have been  */
  /*     previously processed by functions FaceDetect and SkinDetect, which specify high severity, so  */
  /*     these ROIs may already be expected to have benefited from adjustment based upon avoidance of   */
  /*     non-skin pixels. */
  /*  */
  /*     -- Notes --  */
  /*  */
  /*     By default, Matlab's morphological operations act on true values, not false values, although */
  /*     false values (non-skin) are the target. */
  /*     */
  /*     For Matlab documentation discussing removal of patchy regions, see the Matlab documentation */
  /*     topic "Detect Cell Using Edge Detection and Morphology"  */
  /*     (https://www.mathworks.com/help/images/detecting-a-cell-using-image-segmentation.html). */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
  /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
  /*     licensing, please contact the author. */
  /* %%%%% Code-generation settings %%%%%% */
  /* Inline function */
  /* %%%%% Binary Packing %%%%%% */
  /* Note: For use as a Matlab function rather than code generation for a mex function, it is faster  */
  /* not to pack the logical matrix. */
  /* Pack logical image for increased performance of morphological functions  */
  bwpack(IsSkinMask, IsSkinMask_PixelColorPacked);

  /* %%%%% Assign structuring element %%%%%% */
  /* Because structuring element objects are compile-time constants, a fixed number of structuring   */
  /* element objects are made available, each of which has a corresponding function. The function   */
  /* with the structuring element closest in size to the specified structuring element size is used.   */
  /* Select function from available functions */
  /* Select the function with the SE width most similar to the specified SE width. */
  /* Local function. */
  /* Scalar; type int16. */
  /* end main function */
  /* ============================================================================================= */
  /* Local functions  */
  /* ============================================================================================= */
  /* ============================================================================================= */
  /* SelectFunction    Select the function with the SE width most similar to  */
  /*                   MorphCloseNeighborhoodWidth.    */
  /*  */
  /*     Description: */
  /*  */
  /*     Select the size of the structuring element to use. The size is partly determined according to */
  /*     MorphCloseSevereTF.  */
  /* Inline function */
  /* %%%%% High severity %%%%%% */
  /* Scalars; type int16. */
  if ((int16_T)(12 - SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned) < 0)
  {
    Diff12 = (int16_T)(SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned - 12);
  } else {
    Diff12 = (int16_T)(12 - SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned);
  }

  if ((int16_T)(22 - SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned) < 0)
  {
    Diff22 = (int16_T)(SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned - 22);
  } else {
    Diff22 = (int16_T)(22 - SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned);
  }

  if ((int16_T)(32 - SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned) < 0)
  {
    Diff32 = (int16_T)(SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned - 32);
  } else {
    Diff32 = (int16_T)(32 - SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned);
  }

  if (Diff12 < Diff22) {
    functionWidthToUse = 12;
    Diff22 = Diff12;
  } else {
    functionWidthToUse = 22;
  }

  if (Diff32 < Diff22) {
    functionWidthToUse = 32;
    Diff22 = Diff32;
  }

  if ((int16_T)(50 - SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned) < 0)
  {
    b_i = (int16_T)(SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned - 50);
  } else {
    b_i = (int16_T)(50 - SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned);
  }

  if (b_i < Diff22) {
    functionWidthToUse = 50;
  }

  /* Note: Use this pattern for adding additional SEs */
  /*     %{ */
  /*     if DiffX < Diff */
  /*  */
  /*         functionWidthToUse = int16(X); */
  /*      */
  /*         Diff = DiffX; %include this line if this is not the last condition */
  /*     end */
  /*     %} */
  /* %%%%% Low severity %%%%%% */
  /* %%%%% Erosion followed by dilation %%%%%% */
  /* Cast to type double for use by function imerode */
  /* Scalar; type double. */
  /* %%%%% --- High severity erosion and dilation %%%%%%  */
  /* Use function corresponding to closest SE width */
  emxInit_uint32_T(&c_IsSkinMask_PixelColor_ErodePa, 2, true);
  switch (functionWidthToUse) {
   case 12:
    /* Square structuring element with width of 12 pixels     */
    /* Packed binary image */
    /* Local function. */
    /* Type uint32. */
    /* end local function */
    /* ============================================================================================= */
    /* ErodeAndDilate_SESquare12    Erode and dilate with square structuring element of width 12. */
    /* Inline function */
    /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
    /* Type uint32. */
    /*  eroded logical image */
    /*  logical image */
    /*  structuring element */
    /*  flag for packed image */
    /*  number of rows in unpacked image */
    imerode(IsSkinMask_PixelColorPacked, BoundingBoxSkin[3],
            c_IsSkinMask_PixelColor_ErodePa);

    /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
    /* Type uint32. */
    /*  dilated logical image */
    /*  structuring element */
    /*  flag for packed image */
    imdilate(c_IsSkinMask_PixelColor_ErodePa, IsSkinMask_PixelColorPacked);

    /* Square structuring element with width of 22 pixels     */
    /* %%%%% --- Low severity erosion and dilation %%%%%%    */
    /* %%%%% --- Unpack %%%%%%    */
    /* Unpack packed binary image */
    /* M x N matrix; type logical. */
    bwunpack(IsSkinMask_PixelColorPacked, BoundingBoxSkin[3],
             IsSkinMask_ROISelected);
    break;

   case 22:
    /* Packed binary image */
    /* Local function. */
    /* Type uint32. */
    /* end local function */
    /* ============================================================================================= */
    /* ErodeAndDilate_SESquare22    Erode and dilate with square structuring element of width 22. */
    /* Inline function */
    /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
    /* Type uint32. */
    /*  eroded logical image */
    /*  logical image */
    /*  structuring element */
    /*  flag for packed image */
    /*  number of rows in unpacked image */
    b_imerode(IsSkinMask_PixelColorPacked, BoundingBoxSkin[3],
              c_IsSkinMask_PixelColor_ErodePa);

    /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
    /* Type uint32. */
    /*  dilated logical image */
    /*  structuring element */
    /*  flag for packed image */
    b_imdilate(c_IsSkinMask_PixelColor_ErodePa, IsSkinMask_PixelColorPacked);

    /* Square structuring element with width of 32 pixels     */
    /* %%%%% --- Low severity erosion and dilation %%%%%%    */
    /* %%%%% --- Unpack %%%%%%    */
    /* Unpack packed binary image */
    /* M x N matrix; type logical. */
    bwunpack(IsSkinMask_PixelColorPacked, BoundingBoxSkin[3],
             IsSkinMask_ROISelected);
    break;

   case 32:
    /* Packed binary image */
    /* Local function. */
    /* Type uint32. */
    /* end local function */
    /* ============================================================================================= */
    /* ErodeAndDilate_SESquare32    Erode and dilate with square structuring element of width 32. */
    /* Inline function */
    /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
    /* Type uint32. */
    /*  eroded logical image */
    /*  logical image */
    /*  structuring element */
    /*  flag for packed image */
    /*  number of rows in unpacked image */
    c_imerode(IsSkinMask_PixelColorPacked, BoundingBoxSkin[3],
              c_IsSkinMask_PixelColor_ErodePa);

    /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
    /* Type uint32. */
    /*  dilated logical image */
    /*  structuring element */
    /*  flag for packed image */
    c_imdilate(c_IsSkinMask_PixelColor_ErodePa, IsSkinMask_PixelColorPacked);

    /* Square structuring element with width of 50 pixels     */
    /* %%%%% --- Low severity erosion and dilation %%%%%%    */
    /* %%%%% --- Unpack %%%%%%    */
    /* Unpack packed binary image */
    /* M x N matrix; type logical. */
    bwunpack(IsSkinMask_PixelColorPacked, BoundingBoxSkin[3],
             IsSkinMask_ROISelected);
    break;

   case 50:
    /* Packed binary image */
    /* Local function. */
    /* Type uint32. */
    /* end local function */
    /* ============================================================================================= */
    /* ErodeAndDilate_SESquare50    Erode and dilate with square structuring element of width 50. */
    /* Inline function */
    /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
    /* Type uint32. */
    /*  eroded packed logical image */
    /*  packed logical image */
    /*  structuring element */
    /*  flag for packed image */
    /*  number of rows in unpacked image */
    d_imerode(IsSkinMask_PixelColorPacked, BoundingBoxSkin[3],
              c_IsSkinMask_PixelColor_ErodePa);

    /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
    /* Type uint32. */
    /*  dilated packed logical image */
    /*  packed logical image */
    /*  structuring element */
    /*  flag for packed image */
    d_imdilate(c_IsSkinMask_PixelColor_ErodePa, IsSkinMask_PixelColorPacked);

    /* (Required for code generation)     */
    /* %%%%% --- Low severity erosion and dilation %%%%%%    */
    /* %%%%% --- Unpack %%%%%%    */
    /* Unpack packed binary image */
    /* M x N matrix; type logical. */
    bwunpack(IsSkinMask_PixelColorPacked, BoundingBoxSkin[3],
             IsSkinMask_ROISelected);
    break;
  }

  b_i = IsSkinMask->size[0] * IsSkinMask->size[1];
  IsSkinMask->size[0] = IsSkinMask_ROISelected->size[0];
  IsSkinMask->size[1] = IsSkinMask_ROISelected->size[1];
  emxEnsureCapacity_boolean_T(IsSkinMask, b_i);
  NCentroids = IsSkinMask_ROISelected->size[0] * IsSkinMask_ROISelected->size[1];
  for (b_i = 0; b_i < NCentroids; b_i++) {
    IsSkinMask->data[b_i] = IsSkinMask_ROISelected->data[b_i];
  }

  /* %%%%% Count the number of pixels classified as skin (true) %%%%%% */
  /* If returning a count of the pixels classified as true is enabled */
  /* end function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (SkinSegmentMask_Ops_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Modify function files for performance %%%%%% */
  /*  */
  /* Before running code generation, input validation was removed from the files for the  */
  /* following functions: */
  /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\bwpack.m */
  /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\bwunpack.m */
  /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\+images\+internal\+coder\morphop.m  */
  /*  */
  /* Specifically, in these files, the following validation functions were commented out: */
  /*  - narginchk */
  /*  - validateattributes */
  /*  */
  /* Note: Seperate files for these functions with these changes could not be made because code   */
  /* generation for these functions expects specific file names. Hence, after code generation, the   */
  /* input validation was added back to the files. */
  /* Note: as these files are located in 'Program Files', admin access is required to edit them. */
  /*  */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /*                                              Example Code                 Upp. Bounds  Var. Size (T/F)  Type */
  /* RUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8 */
  /* GUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8 */
  /* BUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8 */
  /* YSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single                       */
  /* CbSingleCode                  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single */
  /* CrSingleCode                  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single */
  /* HSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single                                  */
  /* SSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single  */
  /* IsSkinMask_RangeCode          = coder.typeof( false(500, 500),             [inf, inf],  [1, 1] );        %logical            */
  /*                   */
  /*                      */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /* NRows_MatrixCode               = int32(0); */
  /* NCols_MatrixCode               = int32(0); */
  /* CountTrueTFCode                = false; */
  /* TailoredThresholdsTFCode       = false; */
  /* ReturnYTFCode                  = false; */
  /* ReturnCbCrTFCode               = false; */
  /* ReturnHSTFCode                 = false; */
  /* TailoredThresholdsSevereTFCode = false; */
  /* MorphCloseSevereTFCode         = false; */
  /* XOffsetCode                    = int32(0); */
  /* YOffsetCode                    = int32(0); */
  /*  */
  /* Struct with fixed-size fields */
  /* Note: the order and names of fields are compile-time constants. */
  /*  */
  /* SkinSegmentArgsCode = ...                                                                                               */
  /*     struct( ... */
  /*         'SkinColorSamples_NThresholdPassedTF', false, ... */
  /*         'YCbCrThresholdsGeneric', zeros(1, 7, 'single'), ... */
  /*         'HSThresholdsGeneric', zeros(1, 2, 'single'), ... */
  /*         'YCbCrThresholdsTailored', zeros(1, 8, 'single'), ... */
  /*         'YCbCrThresholdsTailored_Sev', zeros(1, 8, 'single'), ... */
  /*         'HSThresholdsTailored', zeros(1, 3, 'single'), ... */
  /*         'HSThresholdsTailored_Sev', zeros(1, 3, 'single'), ... */
  /*         'RangeSEWidth', int16(0), ... */
  /*         'RangeThreshold', uint8(0), ... */
  /*         'MorphCloseSEMediumWidth_Tuned', int16(0), ... */
  /*         'MorphCloseSELargeWidth_Tuned', int16(0) ...    */
  /*     );                                                                    */
  /*  */
  /*  */
  /* %%%%% Set configurations to increase performance %%%%%% */
  /*  */
  /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
  /* "Optimization Strategies" */
  /*  */
  /* cfg = coder.config('mex'); */
  /* cfg.GlobalDataSyncMethod = 'NoSync'; */
  /* cfg.ConstantInputs = 'IgnoreValues'; */
  /* cfg.ExtrinsicCalls = false;  */
  /* cfg.SaturateOnIntegerOverflow = false; */
  /* cfg.IntegrityChecks = false; */
  /* cfg.ResponsivenessChecks = false; */
  /*  */
  /*  */
  /* %%%%% Specify flags to minGW compiler to optimize execution speed %%%%%% */
  /*  */
  /* For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html */
  /*  */
  /* The flags are specified as part of the code-generation configuration object. A custom function, */
  /* setbuildargs, is used to specify these flags. For details on the function implementation, see the  */
  /* function file, which is located within folder FacePulseRate. This custom function is based upon  */
  /* Matlab guidance found in */
  /* https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function */
  /*  */
  /* setbuildargs will be evaluated from text within the code-generation object, so it is converted to  */
  /* a character vector prior to execution of the codegen command. */
  /*  */
  /* %%%%% --- Specify the flags as arguments to function setbuildargs %%%%%% */
  /*  */
  /* Argument buildInfo: this variable is assign by the caller (the codegen command executed  */
  /* below) and is not present in the base workspace. */
  /*  */
  /* Second argument: specify a cell array of compiler-specific flags, where each flag is a  */
  /* character vector. As function setbuildargs will be evaluated from text, use double ' quotes for  */
  /* each character vector to maintain the charater vector, */
  /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
  /*  */
  /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})'; */
  /*  */
  /* Assign to code-generation configuration object */
  /* cfg.PostCodeGenCommand = setbuildargsAsText; */
  /*  */
  /*  */
  /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
  /*  */
  /* codegen SkinSegmentMask_Ops.m -report -config cfg -args {RUint8Code, GUint8Code, BUint8Code, YSingleCode, CbSingleCode, CrSingleCode, HSingleCode, SSingleCode, IsSkinMask_RangeCode, NRows_MatrixCode, NCols_MatrixCode, CountTrueTFCode, TailoredThresholdsTFCode, ReturnYTFCode, ReturnCbCrTFCode, ReturnHSTFCode, TailoredThresholdsSevereTFCode, MorphCloseSevereTFCode, XOffsetCode, YOffsetCode, SkinSegmentArgsCode} */
  /*               */
  /* } */
  /* end function */
  /* %%%%% Partition skin-segmentation mask into smaller regions using grid lines %%%%%% */
  /* Specify the intervals to use to partition the skin-segmentation mask */
  /* Scalar; type single. */
  /* Note: Values specified in function SkinDetectConfig_Setup. */
  /* Insert vertical lines: */
  for (Diff22 = 1; Diff22 <= BoundingBoxSkin[2]; Diff22 +=
       SkinDetectConfig->PartitionColInterval) {
    b_i = nRows_IsSkinMask;
    for (NRegions_ith = 0; NRegions_ith < b_i; NRegions_ith++) {
      IsSkinMask->data[NRegions_ith + IsSkinMask->size[0] * (Diff22 - 1)] =
        false;
    }
  }

  /* Insert horizontal lines:  */
  /* Preallocate for code-generation purposes */
  b_i = BoundingBoxSkin[2];
  for (c_i = 0; c_i < b_i; c_i++) {
    for (Diff12 = 1; Diff12 <= nRows_IsSkinMask; Diff12 +=
         SkinDetectConfig->PartitionRowInterval) {
      IsSkinMask->data[(Diff12 + IsSkinMask->size[0] * c_i) - 1] = false;
    }
  }

  /* %%%%% --- Verify number of potential regions is at or below expected number %%%%%% */
  /* If the number of regions is potentially greater than the upper bounds used in the compiled  */
  /* functions. Such an error would be the result of an implementation error. */
  /* Find the number of column partitions and the number of row partitions */
  /* Local function. */
  /* end local function */
  /* ============================================================================================= */
  /* FindNPartitions   Find the number of column partitions and the number of row partitions. */
  /* Inline function */
  /* Number of column partitions: */
  if (Diff22 > BoundingBoxSkin[2]) {
    Diff22 -= SkinDetectConfig->PartitionColInterval;
  } else {
    Diff22 = Diff12;
  }

  if (SkinDetectConfig->PartitionColInterval == 0) {
    if (Diff22 == 0) {
      Diff32 = 0;
    } else if (Diff22 < 0) {
      Diff32 = MIN_int16_T;
    } else {
      Diff32 = MAX_int16_T;
    }
  } else if (SkinDetectConfig->PartitionColInterval == 1) {
    Diff32 = Diff22;
  } else if (SkinDetectConfig->PartitionColInterval == -1) {
    Diff32 = (int16_T)-Diff22;
  } else {
    if (Diff22 >= 0) {
      Counter_True = (uint16_T)Diff22;
    } else if (Diff22 == -32768) {
      Counter_True = 32768U;
    } else {
      Counter_True = (uint16_T)-Diff22;
    }

    if (SkinDetectConfig->PartitionColInterval >= 0) {
      Counter_False = (uint16_T)SkinDetectConfig->PartitionColInterval;
    } else if (SkinDetectConfig->PartitionColInterval == -32768) {
      Counter_False = 32768U;
    } else {
      Counter_False = (uint16_T)-SkinDetectConfig->PartitionColInterval;
    }

    if (Counter_False == 0U) {
      MaxPoints = MAX_uint16_T;
    } else {
      MaxPoints = (uint16_T)((uint32_T)Counter_True / Counter_False);
    }

    Counter_True = (uint16_T)((uint32_T)Counter_True - (uint16_T)((uint32_T)
      MaxPoints * Counter_False));
    if ((Counter_True > 0) && (Counter_True >= (int32_T)((uint32_T)Counter_False
          >> 1) + (Counter_False & 1))) {
      MaxPoints++;
    }

    Diff32 = (int16_T)MaxPoints;
    if ((Diff22 < 0) != (SkinDetectConfig->PartitionColInterval < 0)) {
      Diff32 = (int16_T)-(int16_T)MaxPoints;
    }
  }

  /* Number of row partitions: */
  if (Diff12 > SkinDetectConfig->PartitionRowInterval) {
    Diff22 = (int16_T)(Diff12 - BoundingBoxSkin[3]);
  } else {
    Diff22 = Diff12;
  }

  if (BoundingBoxSkin[3] == 0) {
    if (Diff22 == 0) {
      Diff12 = 0;
    } else if (Diff22 < 0) {
      Diff12 = MIN_int16_T;
    } else {
      Diff12 = MAX_int16_T;
    }
  } else if (BoundingBoxSkin[3] == 1) {
    Diff12 = Diff22;
  } else if (BoundingBoxSkin[3] == -1) {
    Diff12 = (int16_T)-Diff22;
  } else {
    if (Diff22 >= 0) {
      Counter_True = (uint16_T)Diff22;
    } else if (Diff22 == -32768) {
      Counter_True = 32768U;
    } else {
      Counter_True = (uint16_T)-Diff22;
    }

    if (BoundingBoxSkin[3] >= 0) {
      Counter_False = (uint16_T)BoundingBoxSkin[3];
    } else if (BoundingBoxSkin[3] == -32768) {
      Counter_False = 32768U;
    } else {
      Counter_False = (uint16_T)-BoundingBoxSkin[3];
    }

    if (Counter_False == 0U) {
      MaxPoints = MAX_uint16_T;
    } else {
      MaxPoints = (uint16_T)((uint32_T)Counter_True / Counter_False);
    }

    Counter_True = (uint16_T)((uint32_T)Counter_True - (uint16_T)((uint32_T)
      MaxPoints * Counter_False));
    if ((Counter_True > 0) && (Counter_True >= (int32_T)((uint32_T)Counter_False
          >> 1) + (Counter_False & 1))) {
      MaxPoints++;
    }

    Diff12 = (int16_T)MaxPoints;
    if ((Diff22 < 0) != (BoundingBoxSkin[3] < 0)) {
      Diff12 = (int16_T)-(int16_T)MaxPoints;
    }
  }

  /* end local function */
  /* Note: NColPartitions * NRowPartitions approximates the number of regions; 250 is added because  */
  /* many possible regions will likely have been removed by skin segmentation. */
  /* Note: if frame dimensions exceed 5000 x 5000, integer overflow is possible in this calculation. */
  if ((int16_T)((int16_T)(Diff32 + 1) * (int16_T)(Diff12 + 1)) > 650) {
    /* Throw error  */
    /* Called as extrinsic so that stack trace can be displayed. */
    error(emlrt_marshallOut(cv), b_emlrt_marshallOut(cv1), &emlrtMCI);
  }

  emxInit_real_T(&t1_RegionIndices, 1, true);
  emxInit_int32_T(&t1_RegionLengths, 1, true);

  /* %%%%% Return region information  %%%%%% */
  /* Find connected areas (i.e, regions) */
  /* Find connected areas, using connection criteria of 8. Return information about each of the  */
  /* regions, including the linear indices corresponding to the pixels in each region, the number of */
  /* regions, the number of pixels in each region, and the centroids of each region. */
  /* Note: a centroid may fall on a pixel marked as non-skin by the skin-segmentation mask if the pixel   */
  /* is the centroid of a region.      */
  /* Note: function SkinDetect_RegionInfo is a custom function located within folder 'FacePulseRate'. */
  /*  Linear indices of pixels corresponding to each region */
  /*  (RegionIndices.PixelIdxList). */
  /*  M regions x 1 non-scalar struct; elements: N pixels x 1, type uint32. */
  /*  Number of regions; scalar, type int32. */
  /*  The number of pixels (i.e., area) of each region. M regions x 1 column */
  /*  vector; type single. */
  /*  Centroids (X, Y) of each region. M regions x 2 matrix; type int32. */
  /* SkinDetect_RegionInfo   Find connected regions in skin-segmentation mask and return pixel indices,  */
  /*                         centroids, and other region information.                 */
  /*  */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by function SkinDetect_PartitionRegions. */
  /*  */
  /*  */
  /*     Code Generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*     Compiled file:  */
  /*  */
  /*      - The compiled file included in folder FacePulseRate (SkinDetect_RegionInfo_mex.mexw64)     */
  /*        only compatible on Windows platforms.  */
  /*      - This function uses a bounded variable size for variable NPixelsEachRegion_SingleCode to  */
  /*        improve efficiency. Ensure that this input does not exceed these bounds. */
  /*  */
  /*  */
  /*     Description */
  /*     ----------- */
  /*  */
  /*     Find connected regions in skin-segmentation mask and return pixel indices corresponding to  */
  /*     each region, the cetroid of each region, and other region information. */
  /*  */
  /*     Regarding the centroids, they will be used as part of the skin-detection algorithm to select  */
  /*     one region considered as the skin-detection (see function SkinDetect_SelectRegion). */
  /*     Additionally, centroids of all regions, including those will be rejected, will be used for */
  /*     diagnostic purposes on the output video. Centroids for use on the output video are recorded by   */
  /*     function SkinDetect_RecordDiagnosticData. */
  /*  */
  /*     Different code is used depending on whether code generation is used. This is because function  */
  /*     bwconncomp returns a struct with different fields depending on whether code generation is  */
  /*     used. */
  /*  */
  /*   */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
  /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
  /*     licensing, please contact the author. */
  /* %%%%% Code generation not running %%%%%% */
  /* %%%%% --- Code generation settings %%%%%% */
  /* Specify inlining for faster code execution */
  /* Declare variable-size variables: */
  /*                                               Upp. Bounds    Var. Size (T/F) */
  /* %%%%% --- Find connected regions and return pixel indices and pixel counts corresponding to each region %%%%%% */
  /* Group pixels into connected regions, using the connection criteria of 8, which is the default    */
  /* setting for function bwconncomp.      */
  bwconncomp(IsSkinMask, &t1_Connectivity, t1_ImageSize, &t1_NumObjects,
             t1_RegionIndices, t1_RegionLengths);

  /* Output indicating the number of pixels in each region */
  /* Convert to type single for use in other functions. */
  /* M regions x 1 column vector; type single. */
  RegionNPixels_size[0] = t1_RegionLengths->size[0];
  NCentroids = t1_RegionLengths->size[0];
  for (b_i = 0; b_i < NCentroids; b_i++) {
    RegionNPixels_data[b_i] = (real32_T)t1_RegionLengths->data[b_i];
  }

  emxInit_struct_T_400(&RegionIndices);
  emxInit_struct_T(&Centroids_Struct, 1, true);
  emxInit_struct_T_400(&r);

  /* Output indicating number of regions */
  /* Scalar; type int32. */
  NRegions = RegionNPixels_size[0];

  /* Prevent dynamic memory allocation from colon operator by asserting maximum value */
  /* Preallocate non-scalar struct output for linear indices of pixels in each region */
  /* M regions x 1 non-scalar struct. Elements of type uint32. */
  repmat(RegionNPixels_size[0], RegionZ_Cr_size);
  s_size[0] = RegionZ_Cr_size[0];
  d_cast(s_size, r.data, r.size);
  b_i = RegionIndices.size[0];
  RegionIndices.size[0] = r.size[0];
  emxEnsureCapacity_struct_T(RegionIndices.data, RegionIndices.size, b_i);

  /* %%%%% --- Return centroids of connected regions %%%%%% */
  /* The centroids of each region */
  /* Pass output from function bwconncomp to function. */
  /* M regions x 1 non-scalar struct. Elements of type double. */
  regionprops(t1_ImageSize, t1_NumObjects, t1_RegionIndices, t1_RegionLengths,
              Centroids_Struct);

  /* Number of centroids */
  /* Note: sometimes, the number of centroids may be less than the number of regions. */
  /* This might occur if one or more regions were quite small. */
  NCentroids = Centroids_Struct->size[0];

  /* %%%%% --- Return region indices and centroids output %%%%%% */
  /* If at least 1 region and at least one centroid */
  /* Note: sometimes, one or more regions can be present while no centroids exist. This might occur  */
  /* if the region(s) are quite small. */
  emxFree_int32_T(&t1_RegionLengths);
  if ((RegionNPixels_size[0] > 0) && (Centroids_Struct->size[0] > 0)) {
    /* Preallocate centroids output */
    /* Use type int16 for use in other functions. */
    /* M regions by 2 matrix; type int32. */
    RegionCentroids_size_idx_0 = Centroids_Struct->size[0];

    /* Initialize the last linear index of the ith region */
    RegionEndIndex_ith = 0;

    /* Loop across regions */
    /* Set Centroids_Struct_Length, the length of Centroids_Struct.Centroid, as the maximum  */
    /* iteration because sometimes the length of Centroids_Struct.Centroid can be less than the  */
    /* length of RegionIndices.PixelIdxList.  */
    for (c_i = 0; c_i < NCentroids; c_i++) {
      /* The number of pixels in the ith region */
      /* Cast to type int32. */
      /* Scalar; type int32. */
      NRegions_ith = (int32_T)RegionNPixels_data[c_i];

      /* The first linear index of the ith region */
      /* Scalar; type int32. */
      RegionBeginIndex_ith = RegionEndIndex_ith + 1;

      /* The last linear index of the ith region: */
      /* Scalar; type int32. */
      RegionEndIndex_ith += NRegions_ith;

      /* Assign pixel indices output */
      /* Assign the pixel linear indices of a region to its corresponding row in the non-scalar  */
      /* struct. */
      /* Also cast from type double to type uint32. Although this casting increases  */
      /* computational time, this casting would be conducted anyway in function  */
      /* SkinDetect_RecordDiagnosticData. By casting now, the indices can be used in some */
      /* functions with a smaller type size. */
      /* Preallocate pixel indices for the ith region */
      b_i = RegionIndices.data[c_i].PixelIdxList->size[0] *
        RegionIndices.data[c_i].PixelIdxList->size[1];
      RegionIndices.data[c_i].PixelIdxList->size[0] = NRegions_ith;
      RegionIndices.data[c_i].PixelIdxList->size[1] = 1;
      emxEnsureCapacity_uint32_T(RegionIndices.data[c_i].PixelIdxList, b_i);

      /* Initialize index for pixel indices */
      ElementIdx = -1;

      /* Loop across pixels indices of ith region */
      for (NRegions_ith = RegionBeginIndex_ith; NRegions_ith <=
           RegionEndIndex_ith; NRegions_ith++) {
        ElementIdx++;

        /* Cast to type uint32. */
        /* M regions x 1 non-scalar struct. Elements of type uint32. */
        RegionIndices.data[c_i].PixelIdxList->data[ElementIdx] = (uint32_T)
          muDoubleScalarRound(t1_RegionIndices->data[NRegions_ith - 1]);
      }

      /* Assign centroids output */
      /* Assign the centroids of a region to its corresponding row in the matrix.  */
      /* Cast to type uint32. */
      /* M regions x 2 matrix; type int16. */
      RegionCentroids_data[c_i] = (int16_T)muDoubleScalarRound
        (Centroids_Struct->data[c_i].Centroid[0]);

      /* Cast to type uint32. */
      /* M regions x 2 matrix; type int16. */
      RegionCentroids_data[c_i + RegionCentroids_size_idx_0] = (int16_T)
        muDoubleScalarRound(Centroids_Struct->data[c_i].Centroid[1]);
    }

    /* If the length of RegionIndices.PixelIdxList (NRegions) is greater than the length of  */
    /* Centroids_Struct.Centroid (Centroids_Struct_Length). */
    /* As the previous loop only iterated to the length of Centroids_Struct.Centroid, more  */
    /* iterations will be required to finish looping across RegionIndices.PixelIdxList.  */
    if (RegionNPixels_size[0] > Centroids_Struct->size[0]) {
      /* Loop across remaining regions */
      b_i = Centroids_Struct->size[0] + 1;
      for (c_i = b_i; c_i <= NRegions; c_i++) {
        /* The number of pixels in the ith region */
        /* Cast to type int32. */
        /* Scalar; type int32. */
        NRegions_ith = (int32_T)RegionNPixels_data[c_i - 1];

        /* The first linear index of the ith region */
        /* Scalar; type int32. */
        RegionBeginIndex_ith = RegionEndIndex_ith + 1;

        /* The last linear index of the ith region */
        /* Scalar; type int32. */
        RegionEndIndex_ith += NRegions_ith;

        /* Assign pixel indices output */
        /* Assign the pixel linear indices of a region to its corresponding row in the non-scalar  */
        /* struct.                             */
        /* Preallocate pixel indices for the ith region */
        ElementIdx = RegionIndices.data[c_i - 1].PixelIdxList->size[0] *
          RegionIndices.data[c_i - 1].PixelIdxList->size[1];
        RegionIndices.data[c_i - 1].PixelIdxList->size[0] = NRegions_ith;
        RegionIndices.data[c_i - 1].PixelIdxList->size[1] = 1;
        emxEnsureCapacity_uint32_T(RegionIndices.data[c_i - 1].PixelIdxList,
          ElementIdx);

        /* Initialize index for pixel indices */
        ElementIdx = -1;

        /* Loop across pixels indices of ith region                */
        for (NRegions_ith = RegionBeginIndex_ith; NRegions_ith <=
             RegionEndIndex_ith; NRegions_ith++) {
          ElementIdx++;

          /* Cast to type uint32. */
          /* M regions x 1 non-scalar struct. Elements of type uint32. */
          RegionIndices.data[c_i - 1].PixelIdxList->data[ElementIdx] = (uint32_T)
            muDoubleScalarRound(t1_RegionIndices->data[NRegions_ith - 1]);
        }
      }
    }

    /* No regions present or no centroids present  */
    /* Assign output indicating no regions are available. */
    /* If a region(s) exists but there are no centroids, assign the output for regions as if no  */
    /* regions exist. This will simplify the use of these outputs in other functions. */
  } else {
    /* Number of regions */
    NRegions = 0;

    /* Number of pixels in each region output */
    RegionNPixels_size[0] = 0;

    /* Pixel indices output */
    /* Note: this must be a 1 x 1 struct in order for elements to be of type uint32 rather than */
    /* of type double. */
    b_i = RegionIndices.size[0];
    RegionIndices.size[0] = 1;
    emxEnsureCapacity_struct_T(RegionIndices.data, RegionIndices.size, b_i);

    /* Centroids output */
    RegionCentroids_size_idx_0 = 0;
  }

  emxFree_real_T(&t1_RegionIndices);
  emxFree_struct_T(&Centroids_Struct);
  emxInit_struct_T_400(&b_RegionIndices);

  /* end function */
  /* ================================================================================================= */
  /* Code-generation and build script */
  /* ================================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (SkinDetect_RegionInfo_mex) of the function. */
  /* { */
  /*  */
  /* Note: at present, a separate compiled version of this function is not used as it is compiled  */
  /* within function SkinDetect. */
  /*  */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /*                               Example Code         Upp. Bounds      Var. Size (T/F)  Type */
  /* IsSkinMaskCode = coder.typeof( false(500, 500),     [inf, inf],      [1, 1] );        %logical */
  /*      */
  /*        */
  /* %%%%% Set configurations to increase performance %%%%%% */
  /*  */
  /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
  /* "Optimization Strategies" */
  /*  */
  /* cfg = coder.config('mex'); */
  /* cfg.GlobalDataSyncMethod = 'NoSync'; */
  /* cfg.ConstantInputs = 'IgnoreValues'; */
  /* cfg.ExtrinsicCalls = false; */
  /* cfg.SaturateOnIntegerOverflow = false; */
  /* cfg.IntegrityChecks = false; */
  /* cfg.ResponsivenessChecks = false; */
  /*  */
  /*  */
  /* %%%%% Specify flags to minGW compiler to optimize execution speed %%%%%% */
  /*  */
  /* For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html */
  /*  */
  /* The flags are specified as part of the code-generation configuration object. A custom function, */
  /* setbuildargs, is used to specify these flags. For details on the function implementation, see the  */
  /* function file, which is located within folder FacePulseRate. This custom function is based upon  */
  /* Matlab guidance found in */
  /* https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function */
  /*  */
  /* setbuildargs will be evaluated from text within the code-generation object, so it is converted to  */
  /* a character vector prior to execution of the codegen command. */
  /*  */
  /* %%%%% --- Specify the flags as arguments to function setbuildargs %%%%%% */
  /*  */
  /* Argument buildInfo: this variable is assign by the caller (the codegen command executed below) and  */
  /* is not present in the base workspace. */
  /*  */
  /* Second argument: specify a cell array of compiler-specific flags, where each flag is a character */
  /* vector. As function setbuildargs will be evaluated from text, use double ' quotes for each */
  /* character vector to maintain the charater vector, */
  /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
  /*  */
  /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast'' ''-fsingle-precision-constant''})'; */
  /*  */
  /* Assign to code-generation configuration object */
  /* cfg.PostCodeGenCommand = setbuildargsAsText; */
  /*  */
  /*  */
  /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
  /*  */
  /* codegen SkinDetect_RegionInfo.m -report -config cfg -args {IsSkinMaskCode} */
  /*  */
  /* }         */
  /*  <<<<< For tesing purposes: View centroids superimposed on image >>>>> */
  /* { */
  /*  */
  /* convert centroid (X, Y) coordinates to a linear index */
  /* centroids_per_region_mat_r = round(centroids_per_region_mat, 0); */
  /* centroids_cols = centroids_per_region_mat_r(:, 1); */
  /* centroids_rows = centroids_per_region_mat_r(:, 2); */
  /* centroids_per_region_linearIdx = sub2ind(size(IsSkinMask), centroids_rows, centroids_cols); */
  /*  */
  /* mark centroids by black (0) */
  /* IsSkinMaskTest = IsSkinMask; */
  /* IsSkinMaskTest(centroids_per_region_linearIdx) = 0; */
  /*  */
  /* view centroids superimposed on image */
  /* imtool(IsSkinMaskTest) */
  /*  */
  /* } */
  /*  <<<<<     .     .     .     .     .     .     .     .     .     >>>>>  */
  cast(RegionIndices.data, RegionIndices.size, b_RegionIndices.data,
       b_RegionIndices.size);
  e_cast(b_RegionIndices.data, b_RegionIndices.size, r.data, r.size);
  cast(r.data, r.size, b_RegionIndices.data, b_RegionIndices.size);

  /* %%%%% Assess the partitioned regions %%%%%% */
  /* If no regions found, skip region assessment */
  /* No regions found would likely be due to complete skin segmentation of ROI. */
  emxFree_struct_T_400(&r);
  emxFree_struct_T_400(&RegionIndices);
  emxInitStruct_struct_T1(&b_ROIDiagnostic_ROISkin_ith, true);
  if (NRegions != 0) {
    /* %%%%% --- Reject regions according to specified thresholds %%%%%%    */
    /* Note: 'SkinDetect_RejectRegions' is a custom function located within folder 'FacePulseRate'.  */
    /* SkinDetect_RejectRegions    Apply skin-detection rejection thresholds to partitioned regions.  */
    /*                                    */
    /*  */
    /*     Helper function to function FacePulseRate.  */
    /*     Within function FacePulseRate, called by function SkinDetect. */
    /*  */
    /*  */
    /*     Code Generation */
    /*     --------------- */
    /*  */
    /*     Can be called as a Matlab function or used for C-language code generation. */
    /*  */
    /*  */
    /*     Description */
    /*     ----------- */
    /*  */
    /*     Apply thresholds to regions, which were partitioned by function SkinDetect_PartitionRegions,  */
    /*     to determine which regions to reject. The output of intermediate operations, such as color  */
    /*     z-scores, is returned for reuse by other steps of the skin-detection algorithm. */
    /*   */
    /*     For further discussion, see the description of the skin-detection algorithm in the file of */
    /*     function SkinDetect. */
    /*  */
    /*  */
    /*     Copyright */
    /*     --------- */
    /*  */
    /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
    /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
    /*     licensing, please contact the author.    */
    /* %%%%% Code-generation settings %%%%%% */
    /* Inline function */
    /* Declare variables: */
    /* Note: set bounds so that these variables do not use dynamic memory allocation, increasing  */
    /* efficiency. */
    /*                                                       Upp. Bounds  Var. Size (T/F) */
    /* %%%%% Extract information for the rejection thresholds %%%%%% */
    /* Note: values assigned by function SkinDetectConfig_Setup. */
    /* %%%%% --- Color thresholds %%%%%% */
    /* If the color thresholds were based upon a large number of skin-color samples present, narrow some */
    /* color thresholds. Whether there is a large number of skin-color samples present is determined by */
    /* SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdPassedTF. This is conducted because  */
    /* when there is a greater number of ROIs, the standard deviations of color samples may become more   */
    /* expansive, requiring more narrow thresholds to reduce false positives (classifying non-skin as  */
    /* skin). SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdPassedTF is assigned by function */
    /* SkinDetect_SetThresholds. For details on the collection of skin-color samples, see function  */
    /* ROIMeans_FirstRead_CollectSkinColorSamples. */
    /* If there are a large number of skin-color samples  */
    if (SkinDetectConfig->Thresholds.b_SkinColorSamples_HighNThresho) {
      /* RGB probability threshold */
      /* Scalar; type single. */
      ThresholdRGBProb = SkinDetectConfig->Thresholds.ColorThresholdHighN[0];

      /* Cb and Cr z-score thresholds */
      /* Scalars; type single. */
      ThresholdZScoreCb = SkinDetectConfig->Thresholds.ColorThresholdHighN[1];
      ThresholdZScoreCr = SkinDetectConfig->Thresholds.ColorThresholdHighN[2];

      /* If there is not a large number of skin-color samples */
    } else {
      /* RGB probability threshold */
      /* Scalar; type single. */
      ThresholdRGBProb = SkinDetectConfig->Thresholds.ColorThreshold[0];

      /* Cb and Cr z-score thresholds */
      /* Scalars; type single. */
      ThresholdZScoreCb = SkinDetectConfig->Thresholds.ColorThreshold[1];
      ThresholdZScoreCr = SkinDetectConfig->Thresholds.ColorThreshold[2];
    }

    /* Cr standard deviation threshold */
    /* Scalar; type single. */
    /* %%%%% --- Region pixel count threshold %%%%%% */
    /* Scalar; type single. */
    /* %%%%% --- Theta values for determining RGB probability %%%%%% */
    /* Note: values assigned by function function SkinDetect_RGBProbSkinTrain. */
    /* 4 x 1 column vector; type double. */
    /* %%%%% --- Reference means and standard deviations for determining Y, Cb, and Cr z-scores of each region %%%%%% */
    /* Note: values assigned by function SkinDetect_SetThresholds.  */
    /* Scalars; type single. */
    /* %%%%% Apply pixel-count threshold %%%%%% */
    /* Assign a logical vector indicating whether (pass/not pass) the region has a quantity of pixels  */
    /* greater than or equal to the threshold for minimum quantity of pixels. */
    /* Variable specifying threshold (RegionNThreshold) assigned at top. */
    /* M regions x 1 column vector; type logical. */
    NRegions_ith = RegionNPixels_size[0];
    NCentroids = RegionNPixels_size[0];
    for (b_i = 0; b_i < NCentroids; b_i++) {
      c_RegionNPixels_PassNThresholdT[b_i] = (RegionNPixels_data[b_i] >
        SkinDetectConfig->Thresholds.RegionNThreshold);
    }

    /* %%%%% Calculate region RGB probability and YCbCr z-scores %%%%%% */
    /* %%%%% --- Calculate RGB means and YCbCr z-scores %%%%%% */
    /* Regarding YCbCr z-scores, the z-score for a region is calculated by subtracting its mean from the  */
    /* mean across ROIs identified by the primary face-detection algorithm algorithm and dividing this by   */
    /* the standard deviation of means across ROIs identified by the primary algorithm. The Y-color  */
    /* dimension is not used for the rejected thresholds but is used later for determining the selected   */
    /* skin region out of skin region candidates. */
    /* The means and standard deviations across ROIs were returned as output by function */
    /* SkinDetect_SetThresholds. The linear index of a given region is used to specify the pixels that    */
    /* comprise each region. */
    /* Note: 'SkinDetect_RegionMetrics' is a custom function located within folder 'FacePulseRate'.   */
    /*  M regions x 3 matrix; type double */
    /*  M regions x 1 column vector; type single */
    /*  M regions x 1 column vector; type single */
    /*  M regions x 1 column vector; type single */
    /*  M regions x 1 column vector; type single */
    SkinDetect_RegionMetrics(emlrtRootTLSGlobal, b_RegionIndices.data, NRegions,
      RegionNPixels_data, RBounded_Uint8, GBounded_Uint8, BBounded_Uint8,
      YBounded_Single, CbBounded_Single, CrBounded_Single,
      SkinDetectConfig->Thresholds.YCbCrMeanOfMeans[0],
      SkinDetectConfig->Thresholds.YCbCrMeanOfMeans[1],
      SkinDetectConfig->Thresholds.YCbCrMeanOfMeans[2],
      SkinDetectConfig->Thresholds.YCbCrStdDevOfMeans[0],
      SkinDetectConfig->Thresholds.YCbCrStdDevOfMeans[1],
      SkinDetectConfig->Thresholds.YCbCrStdDevOfMeans[2], RegionRGBMeans_data,
      RegionRGBMeans_size, RegionZ_Y_data, s_size, RegionZ_Cb_data,
      RegionNPixels_size, RegionZ_Cr_data, RegionZ_Cr_size, RegionSD_Cr_data,
      RegionSD_Cr_size);

    /* %%%%% --- Calculate RGB probabilities; assign logical vector indicating regions that pass thresholds %%%%%% */
    /* Return probabilities for each region that ROI RGB means are skin (as vector with each row   */
    /* referencing a region). */
    /* To do so, use function SkinDetect_RGBProbSkin. This function is also supplied with theta  */
    /* parameters, which were calculated from color means across ROIs from the primary face-detection  */
    /* algorithm and from colors means from external sources. The theta parameters were returned by  */
    /* function SkinDetect_RGBProbSkinTrain, which was called by function SkinDetect_SetThresholds, which  */
    /* was called by function ROIMeans_FirstRead_SetThresholds.  */
    /* M regions x 1 column vector; type double. */
    /* Note: 'SkinDetect_RGBProbSkin' is a custom function located within folder 'FacePulseRate'.   */
    /* SkinDetect_RGBProbSkin   Estimate probability that mean RGB of an ROI is skin. */
    /*     */
    /*     Helper function to function FacePulseRate. */
    /*     Within function FacePulseRate, called by function SkinDetect_RejectRegions. */
    /*  */
    /*  */
    /*     Code Generation */
    /*     --------------- */
    /*  */
    /*     Can be called as a Matlab function or used for C-language code generation. */
    /*  */
    /*  */
    /*     Description */
    /*     ----------- */
    /*  */
    /*     Estimate probability that mean RGB of an ROI is skin. */
    /*  */
    /*     This function is adapted from the Skin Segmentation toolbox, which was obtained from Madhav */
    /*     Rajan (2014). See discussion on Github (https://github.com/madhrajan91/Skin-Segmentation). For  */
    /*     usage notes in toolbox FacePulseRate, see function SkinDetect_RGBProbSkinTrain. */
    /*  */
    /*     Note: The theta parameters used by the function are supplied by function */
    /*     SkinDetect_RGBProbSkinTrain. */
    /*  */
    /*     Input: */
    /*  */
    /*         RGB_mean   = N-by-3 matrix of skin sample RGB means. Each row corresponds to a skin sample  */
    /*                      and the columns correspond to means of R, G, and B, respectively.                    */
    /*         theta      = Probability criteria. */
    /*  */
    /*     Output: */
    /*  */
    /*         prob_skin  = The probability(ies) that the means of R, G and B represent skin, based upon */
    /*                      theta, which was produced by training with a sample of skin and non-skin  */
    /*                      means.  */
    /*  */
    /*  */
    /*     Copyright */
    /*     --------- */
    /*  */
    /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
    /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
    /*     licensing, please contact the author. */
    /* Inline function */
    /* Add column to right equal to 1 */
    /* Calculate probability that means of R, G, and B do not represent skin */
    tmp_size[0] = RegionRGBMeans_size[0];
    tmp_size[1] = 4;
    NCentroids = RegionRGBMeans_size[0];
    for (b_i = 0; b_i < NCentroids; b_i++) {
      tmp_data[b_i] = 1.0;
    }

    NCentroids = RegionRGBMeans_size[0];
    for (b_i = 0; b_i < 3; b_i++) {
      for (ElementIdx = 0; ElementIdx < NCentroids; ElementIdx++) {
        tmp_data[ElementIdx + tmp_size[0] * (b_i + 1)] =
          RegionRGBMeans_data[ElementIdx + RegionRGBMeans_size[0] * b_i];
      }
    }

    mtimes(tmp_data, tmp_size, SkinDetectConfig->Thresholds.RGBProbTheta,
           RegionRGBProbSkin_data, s_size);

    /* SIGMOID   Compute sigmoid function. */
    /*  */
    /*    Helper function to function FacePulseRate. */
    /*    Within function FacePulseRate, called by functions SkinDetect_RGBProbSkinTrain and */
    /*    SkinDetect_RGBProbSkin. */
    /*  */
    /*    Code generation: Can be called as a Matlab function or used for C-language code generation. */
    /*  */
    /*    Description: */
    /*  */
    /*    J = SIGMOID(z) computes the sigmoid/ Logistic function of z. */
    /*  */
    /*    Adapted from the Skin Segmentation toolbox, which was obtained from Madhav */
    /*    Rajan (2014). See discussion on Github (https://github.com/madhrajan91/Skin-Segmentation). */
    /* Inline function */
    /* end function */
    /* Convert to probabilty of skin */
    NCentroids = s_size[0];
    for (b_i = 0; b_i < NCentroids; b_i++) {
      RegionRGBProbSkin_data[b_i] = -RegionRGBProbSkin_data[b_i];
    }

    b_exp(RegionRGBProbSkin_data, s_size);
    NCentroids = s_size[0];
    for (b_i = 0; b_i < NCentroids; b_i++) {
      RegionRGBProbSkin_data[b_i] = 1.0 - 1.0 / (RegionRGBProbSkin_data[b_i] +
        1.0);
    }

    /* end function */
    /* Assign a logical vector indicating whether (pass/not pass) the region is above the RGB probability  */
    /* threshold. */
    /* This threshold is specified as an argument (SkinClassifyRegionColorThresholds(1)) to function */
    /* FacePulseRate. */
    /* M regions x 1 column vector; type logical. */
    /* %%%%% --- Assign logical vector indicating regions that pass YCbCr z-score thresholds %%%%%% */
    /* See notes in function SkinDetect. */
    /* Skin-detection candidates are rejected if outside thresholds, which are determined by the mean +/- */
    /* a specified standard deviation; however, thresholds are only used for Cb and Cr because of greater */
    /* luminance invariance compared to Y. */
    /* Also, skin-detection candidates that pass the thresholds are given more weight toward selection if  */
    /* they are closer to these means; for these weights, Y is used. */
    /* Assign a logical vector indicating whether (pass/not pass) the region is within the CbCr  */
    /* thresholds. These thresholds are specified as an argument (SkinClassifyRegionColorThresholds(2:3)) */
    /* to function FacePulseRate.  */
    /* M regions x 1 column vector; type logical. */
    /*  compare against Cb z-score threshold */
    /*    compare against Cr z-score threshold */
    /* %%%%% --- Assign logical vector indicating regions that pass Cr standard deviation threshold %%%%%% */
    /* M regions x 1 column vector; type logical. */
    c_RegionSD_Cr_PassThresholdTF_L = RegionSD_Cr_size[0];
    NCentroids = RegionSD_Cr_size[0];
    for (b_i = 0; b_i < NCentroids; b_i++) {
      d_RegionSD_Cr_PassThresholdTF_L[b_i] = (RegionSD_Cr_data[b_i] <
        SkinDetectConfig->Thresholds.ColorSDThreshold);
    }

    /* %%%%% Assign logical vector indicating regions that passed all thresholds %%%%%% */
    /* Assign logical vector indicating whether a region passed all thresholds */
    /* M regions x 1 column vector; type logical. */
    b_abs(RegionZ_Cb_data, RegionNPixels_size, RegionZ_Y_Standardized_data,
          s_size);
    b_abs(RegionZ_Cr_data, RegionZ_Cr_size, RegionZ_Cb_Standardized_data, s_size);
    for (b_i = 0; b_i < NRegions_ith; b_i++) {
      c_RegionPassAllThresholdsTF_Log[b_i] =
        (c_RegionNPixels_PassNThresholdT[b_i] && (RegionRGBProbSkin_data[b_i] >=
          ThresholdRGBProb) && ((RegionZ_Y_Standardized_data[b_i] <=
           ThresholdZScoreCb) && (RegionZ_Cb_Standardized_data[b_i] <=
           ThresholdZScoreCr)) && d_RegionSD_Cr_PassThresholdTF_L[b_i]);
    }

    /* Number of regions that passed the thresholds */
    /* Scalar; type uint16. */
    /* Initialize accumulator */
    j = 0U;
    for (c_i = 0; c_i < NRegions; c_i++) {
      if (c_RegionPassAllThresholdsTF_Log[c_i]) {
        j++;
      }
    }

    /* end function */
    /* %%%%% --- Select the partitioned region that appears the most likely to be skin %%%%%% */
    /* Proceed with region selection if at least one region passed the rejection thresholds. */
    /* Otherwise, skip further evaluation and proceed to recording values that can be displayed on */
    /* the output video for potential diagnosis.  */
    if (j > 0) {
      /* Note: 'SkinDetect_SelectRegion' is a custom function located within folder  */
      /* 'FacePulseRate'. */
      /* SkinDetect_SelectRegion   Select the partitioned region that appears the most likely to be skin. */
      /*    */
      /*     Helper function to function FacePulseRate.  */
      /*     Within function FacePulseRate, called by function SkinDetect. */
      /*  */
      /*  */
      /*     Code Generation */
      /*     --------------- */
      /*  */
      /*     Can be called as a Matlab function or used for C-language code generation. */
      /*  */
      /*  */
      /*     Description */
      /*     ----------- */
      /*  */
      /*     Following rejection of some regions (see function SkinDetect_RejectRegions), select one of the */
      /*     remaining regions as the skin detection. */
      /*  */
      /*     For further discussion of the selection process, see the description of the skin-detection  */
      /*     algorithm in the file of function SkinDetect. */
      /*     */
      /*     Then, determine the ROI values, ROI_Selected_ith, of the selected region. Determining the ROI  */
      /*     values includes expanding the size of the region to result in a size that captures more of the  */
      /*     face. Additionally, run additional checks to determine whether the ROI contains skin. A true  */
      /*     return value for SkinTF_ith indicates that the ROI passed these checks. If SkinTF_ith is true,  */
      /*     ProportionSkinPixelsTooLowTF_ith will be false and vice versa. */
      /*  */
      /*  */
      /*     Copyright */
      /*     --------- */
      /*  */
      /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
      /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
      /*     licensing, please contact the author.    */
      /* %%%%% Code-generation settings %%%%%% */
      /* Inline function */
      /* Declare variables: */
      /* Note: set bounds so that these variables do not use dynamic memory allocation, increasing  */
      /* efficiency. */
      /*                                                       Upp. Bounds  Var. Size (T/F) */
      /* %%%%% Setup %%%%%% */
      /* Assert value to limit dynamic memory when using the colon operation with this variable. */
      /* Convert variable RegionPassAllThresholdsTF_LogIdx to linear indices for indexing efficiency */
      /* Local function. */
      /* Type uint16. */
      /* end main function */
      /* ============================================================================================= */
      /* Local functions */
      /* ============================================================================================= */
      /* ============================================================================================= */
      /* LogToLin   Convert a logical index to linear indices. */
      /*  */
      /*     Description: */
      /*  */
      /*     Assign a linear index, LinIdx_True, to correspond to elements of the logical index that equal */
      /*     true. Assign a linear index, LinIdx_False, to correspond to elements of the logical index that  */
      /*     equal false. */
      /* Inline function */
      Counter_True = 0U;
      Counter_False = 0U;
      ElementIdx = (uint16_T)((uint32_T)(uint16_T)NRegions - j);
      for (c_i = 0; c_i < NRegions; c_i++) {
        if (c_RegionPassAllThresholdsTF_Log[(uint16_T)(c_i + 1) - 1]) {
          Counter_True++;
          c_RegionPassAllThresholdsTF_Lin[Counter_True - 1] = (uint16_T)(c_i + 1);
        } else {
          Counter_False++;
          c_RegionNotPassAllThresholdsTF_[Counter_False - 1] = (uint16_T)(c_i +
            1);
        }
      }

      /* %%%%% Assign selection points: Proximity to predicted ROI %%%%%% */
      /* Assign selection points to regions based upon proximity to ROI predicted from face-detection  */
      /* algorithms. */
      /* %%%%% --- Find the center point of the ROI used as the basis for the current bounding box %%%%%% */
      /* Find the center point of the ROI used as the basis for the current bounding box. */
      /* In the case of the first read, the ROI is the median of the last few ROIs detected by the  */
      /* face-detection algorithms (for details, see function ROIMeans_FirstRead_SetBoundingBoxes). In the  */
      /* case of the second read, the ROI is interpolated from ROIs detected by the face-detection */
      /* algorithms from nearby frames. This interpolated ROI may also be interpolated from skin-detection  */
      /* ROIs from the first read if the current frame is near where the first-read skin detection became     */
      /* enabled. */
      /* ROI used as the basis for the current bounding box: */
      /* If first read */
      if (FirstReadSkinTF) {
        /* Rename for current use. */
        /* Median ROI from last few frames */
        /* This ROI was assigned in function ROIMeans_FirstRead_SetBoundingBoxes, which was */
        /* called by function ROIMeans_FirstRead. */
        ROIPredicted_data[0] = ROIForBoundingBoxSkin_FR[0];
        ROIPredicted_data[1] = ROIForBoundingBoxSkin_FR[1];
        ROIPredicted_data[2] = ROIForBoundingBoxSkin_FR[2];
        ROIPredicted_data[3] = ROIForBoundingBoxSkin_FR[3];

        /* If second read     */
      } else {
        /* Interpolated ROI for current frame */
        /* This ROI was assigned by function ROIMSIR, which was called in function  */
        /* ROIMeans_FirstRead_TakeMeans.  */
        /* 1 x 4 row vector; type int16. */
        NCentroids = ROI_SR_ith_size[0] * ROI_SR_ith_size[1];
        if (0 <= NCentroids - 1) {
          memcpy(&ROIPredicted_data[0], &ROI_SR_ith_data[0], NCentroids * sizeof
                 (int16_T));
        }
      }

      /* Adjust upper-left-hand X- and Y-coordinates of predicted ROI to coordinates of bounding box.  */
      /* 1 x 4 row vector; type int16. */
      ROIPredicted_data[0] = (int16_T)((int16_T)(ROIPredicted_data[0] -
        BoundingBoxSkin[0]) + 1);

      /* adjust X-left */
      ROIPredicted_data[1] = (int16_T)((int16_T)(ROIPredicted_data[1] -
        BoundingBoxSkin[1]) + 1);

      /* adjust Y-upper */
      /* Find center of predicted ROI */
      /* Optimize division by 2 by bit-wise operation. */
      /* Scalars; type int16. */
      ROIPredicted_CenterX = (int16_T)(ROIPredicted_data[0] +
        (ROIPredicted_data[2] >> 1));

      /* X-left + width / 2     */
      ROIPredicted_CenterY = (int16_T)(ROIPredicted_data[1] +
        (ROIPredicted_data[3] >> 1));

      /* Y-upper + height / 2 */
      /* %%%%% --- Compare center coordinates of predicted ROI to centroids to assign points %%%%%% */
      /* Find distance between the center point of the predicted ROI and the centroid of each region  */
      /* (distance formula). */
      /* P non-rejected regions x 1 colum vector; type int16. */
      distances_size[0] = j;
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        /* Scalars; type int16. */
        NRegions_ith = c_RegionPassAllThresholdsTF_Lin[c_i] - 1;
        Diff22 = (int16_T)(RegionCentroids_data[NRegions_ith] -
                           ROIPredicted_CenterX);
        Diff12 = (int16_T)(RegionCentroids_data[NRegions_ith +
                           RegionCentroids_size_idx_0] - ROIPredicted_CenterY);

        /* Cast to type int32 to prevent integer overflow during multiplication */
        /* Scalars; type int32. */
        /* Note: multiply is used in place of ^2 for efficiency. */
        /* Also, type must be at least 32 bits to prevent integer overflow. */
        /* Cast to single as floating-point type required for function sqrt */
        distances_data[c_i] = (int16_T)muSingleScalarRound(muSingleScalarSqrt
          ((real32_T)(Diff22 * Diff22 + Diff12 * Diff12)));
      }

      /* Assign points according to rank order of distances */
      /* The region with the best (smallest) distance gets points equal to the number of non-rejected  */
      /* regions. That is, if there are 33 regions that were not rejected, the best region gets 33 points  */
      /* and the worst region gets 1 point. */
      /* Order distances (only non-rejected) from larger to smallest  */
      /* P non-rejected regions x 1 colum vector; type double. */
      sort(distances_data, distances_size, iidx_data, s_size);
      NCentroids = s_size[0];
      for (b_i = 0; b_i < NCentroids; b_i++) {
        RegionDistance_LinIdx_data[b_i] = iidx_data[b_i];
      }

      /* Preallocate points vector for proximity */
      /* P non-rejected regions x 1 colum vector; type uint16. */
      /* Order points by ordered distances index  */
      /* P non-rejected regions x 1 colum vector; type uint16. */
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        RegionPoints_Proximity_data[(int32_T)RegionDistance_LinIdx_data[c_i] - 1]
          = (uint16_T)(c_i + 1);
      }

      /* %%%%% Assign selection points: RGB probability %%%%%%      */
      /* Assign selection points to regions based upon RGB probability */
      /* Note: see notes in function SkinDetect. */
      /* Assign points according to rank order of RegionRGBProbSkin */
      /* The region with the best (greatest) RegionRGBProbSkin gets points equal to the number of */
      /* non-rejected regions. That is, if there are 33 regions that were not rejected, the best region */
      /* gets 33 points and the worst region gets 1 point. */
      /* Order RegionRGBProbSkin (only non-rejected regions) from smallest to largest */
      /* P non-rejected regions x 1 colum vector; type double. */
      RegionDistance_LinIdx_size[0] = j;
      NCentroids = j;
      for (b_i = 0; b_i < NCentroids; b_i++) {
        RegionDistance_LinIdx_data[b_i] =
          RegionRGBProbSkin_data[c_RegionPassAllThresholdsTF_Lin[b_i] - 1];
      }

      b_sort(RegionDistance_LinIdx_data, RegionDistance_LinIdx_size, iidx_data,
             s_size);
      NCentroids = s_size[0];
      for (b_i = 0; b_i < NCentroids; b_i++) {
        RegionDistance_LinIdx_data[b_i] = iidx_data[b_i];
      }

      /* Preallocate points vector for RGB probability skin */
      /* Specify type uint16 for faster evaluation where used. */
      /* P non-rejected regions x 1 colum vector; type uint16. */
      /* Order points by ordered RegionRGBProbSkin_LinIdx index  */
      /* P non-rejected regions x 1 colum vector; type uint16. */
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        RegionPoints_RGBProbSkin_data[(int32_T)RegionDistance_LinIdx_data[c_i] -
          1] = (uint16_T)(c_i + 1);
      }

      /* %%%%% Assign selection points: YCbCr means similarity %%%%%%  */
      /* Assign selection points to regions for similarity of YCbCr means to the grand YCbCr means from  */
      /* primary face-detection algorithm ROIs.  */
      /* %%%%% --- Standardize z-scores to balance the contribution of dimensions %%%%%% */
      /* Standardize Y, Cb, and Cr z-score vectors  */
      /* Exclude rejected regions.  */
      /* P non-rejected regions x 1 colum vectors; type single. */
      /* Cast to type single for use in function Standardize */
      /* Local function. */
      /* end local function */
      /* ============================================================================================= */
      /* Standardize    Conduct standardization.   */
      /* Inline function */
      /* %%%%% Mean of indexed vector %%%%%% */
      /* Preallocate accumulator */
      ThresholdRGBProb = 0.0F;
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        ThresholdRGBProb += RegionZ_Y_data[c_RegionPassAllThresholdsTF_Lin[c_i]
          - 1];
      }

      /* Take mean */
      ThresholdZScoreCr = ThresholdRGBProb / (real32_T)j;

      /* %%%%% Standard deviation of indexed vector %%%%%% */
      /* Preallocate accumulator */
      ThresholdRGBProb = 0.0F;
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        ThresholdZScoreCb = RegionZ_Y_data[c_RegionPassAllThresholdsTF_Lin[c_i]
          - 1] - ThresholdZScoreCr;

        /* Note: multiply used in place of ^2 for efficiency */
        ThresholdZScoreCb *= ThresholdZScoreCb;
        ThresholdRGBProb += ThresholdZScoreCb;
      }

      ThresholdRGBProb = muSingleScalarSqrt(ThresholdRGBProb / ((real32_T)j -
        1.0F));

      /* %%%%% Standardized scores of indexed vector %%%%%% */
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        RegionZ_Y_Standardized_data[c_i] =
          (RegionZ_Y_data[c_RegionPassAllThresholdsTF_Lin[c_i] - 1] -
           ThresholdZScoreCr) / ThresholdRGBProb;
      }

      /* end local function */
      /* end local function */
      /* ============================================================================================= */
      /* Standardize    Conduct standardization.   */
      /* Inline function */
      /* %%%%% Mean of indexed vector %%%%%% */
      /* Preallocate accumulator */
      ThresholdRGBProb = 0.0F;
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        ThresholdRGBProb += RegionZ_Cb_data[c_RegionPassAllThresholdsTF_Lin[c_i]
          - 1];
      }

      /* Take mean */
      ThresholdZScoreCr = ThresholdRGBProb / (real32_T)j;

      /* %%%%% Standard deviation of indexed vector %%%%%% */
      /* Preallocate accumulator */
      ThresholdRGBProb = 0.0F;
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        ThresholdZScoreCb = RegionZ_Cb_data[c_RegionPassAllThresholdsTF_Lin[c_i]
          - 1] - ThresholdZScoreCr;

        /* Note: multiply used in place of ^2 for efficiency */
        ThresholdZScoreCb *= ThresholdZScoreCb;
        ThresholdRGBProb += ThresholdZScoreCb;
      }

      ThresholdRGBProb = muSingleScalarSqrt(ThresholdRGBProb / ((real32_T)j -
        1.0F));

      /* %%%%% Standardized scores of indexed vector %%%%%% */
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        RegionZ_Cb_Standardized_data[c_i] =
          (RegionZ_Cb_data[c_RegionPassAllThresholdsTF_Lin[c_i] - 1] -
           ThresholdZScoreCr) / ThresholdRGBProb;
      }

      /* end local function */
      /* end local function */
      /* ============================================================================================= */
      /* Standardize    Conduct standardization.   */
      /* Inline function */
      /* %%%%% Mean of indexed vector %%%%%% */
      /* Preallocate accumulator */
      ThresholdRGBProb = 0.0F;
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        ThresholdRGBProb += RegionZ_Cr_data[c_RegionPassAllThresholdsTF_Lin[c_i]
          - 1];
      }

      /* Take mean */
      ThresholdZScoreCr = ThresholdRGBProb / (real32_T)j;

      /* %%%%% Standard deviation of indexed vector %%%%%% */
      /* Preallocate accumulator */
      ThresholdRGBProb = 0.0F;
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        ThresholdZScoreCb = RegionZ_Cr_data[c_RegionPassAllThresholdsTF_Lin[c_i]
          - 1] - ThresholdZScoreCr;

        /* Note: multiply used in place of ^2 for efficiency */
        ThresholdZScoreCb *= ThresholdZScoreCb;
        ThresholdRGBProb += ThresholdZScoreCb;
      }

      ThresholdRGBProb = muSingleScalarSqrt(ThresholdRGBProb / ((real32_T)j -
        1.0F));

      /* %%%%% Standardized scores of indexed vector %%%%%% */
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        RegionZ_Cr_Standardized_data[c_i] =
          (RegionZ_Cr_data[c_RegionPassAllThresholdsTF_Lin[c_i] - 1] -
           ThresholdZScoreCr) / ThresholdRGBProb;
      }

      /* end local function */
      /* %%%%% --- Composite scores %%%%%% */
      /* Sum absolute values of standardized z-scores across Y, Cb, and Cr dimensions for composite  */
      /* difference score. */
      /* P non-rejected regions x 1 colum vector; type single. */
      RegionZ_Difference_size[0] = j;
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        RegionZ_Difference_data[c_i] = (muSingleScalarAbs
          (RegionZ_Y_Standardized_data[c_i]) + muSingleScalarAbs
          (RegionZ_Cb_Standardized_data[c_i])) + muSingleScalarAbs
          (RegionZ_Cr_Standardized_data[c_i]);
      }

      /* %%%%% --- Assign selected points %%%%%% */
      /* Assign points according to the rank order of the difference. The region with the best (least)  */
      /* difference gets points equal to the number of non-rejected regions. For example, if there are 33  */
      /* regions that were not rejected, the best region gets 33 points and the worst region gets 1 point. */
      /* Order difference (only non-rejected) from smallest to largest absolute difference */
      /* P non-rejected regions x 1 colum vector; type double. */
      c_sort(RegionZ_Difference_data, RegionZ_Difference_size, iidx_data, s_size);
      NCentroids = s_size[0];
      for (b_i = 0; b_i < NCentroids; b_i++) {
        RegionDistance_LinIdx_data[b_i] = iidx_data[b_i];
      }

      /* Preallocate vector */
      /* Specify type uint16 for faster evaluation where used. */
      /* P non-rejected regions x 1 colum vector; type uint16. */
      /* Order points by absolute difference index  */
      /* P non-rejected regions x 1 colum vector; type uint16. */
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        RegionPoints_data[(int32_T)RegionDistance_LinIdx_data[c_i] - 1] =
          (uint16_T)(c_i + 1);
      }

      /* %%%%% Determine selected region based upon region with highest points %%%%%% */
      /* Select region with highest points (out of passing regions). */
      /* Note: see notes in function SkinDetect. */
      /* %%%%% --- Apply weights and sum %%%%%% */
      /* Specify weight to apply to proximity relative to skin similarity */
      /* This weight is specified as an argument to function FacePulseRate. */
      /* Scalar; type single. */
      /* Preallocate vector for sum of selection points for each region  */
      /* Specify type uint16 for faster evaluation where used. */
      /* P non-rejected regions x 1 colum vector; type uint16. */
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        /* Combine points (to the mean) from RGB probability and YCbCr likeness */
        /* Optimize division by 2 by bit-wise operation. */
        /* Apply weight to proximity scores */
        /* Cast to type single for calculation. */
        b_RegionPoints_data[c_i] = (uint16_T)((uint16_T)muSingleScalarRound
          ((real32_T)RegionPoints_Proximity_data[c_i] * (real32_T)
           SkinDetectConfig->ROISkinRegionProximityWeight) + ((uint32_T)
          (RegionPoints_RGBProbSkin_data[c_i] + RegionPoints_data[c_i]) >> 1));
      }

      /* %%%%% --- Select region with highest points %%%%%%     */
      /* Assign linear index indicating the region with the maximum points */
      /* Initialize value of region with the most points  */
      /* Assign a starting value that is lower than the lowest possible points of any region. */
      MaxPoints = 0U;

      /* Initialize index corresponding to the region with the most points */
      Counter_True = 0U;
      b_i = j;
      for (c_i = 0; c_i < b_i; c_i++) {
        Counter_False = b_RegionPoints_data[c_i];
        if (Counter_False > MaxPoints) {
          MaxPoints = Counter_False;
          Counter_True = (uint16_T)(c_i + 1);
        }
      }

      /* Align index out of index of all regions (not just passing regions) */
      /* Cast to type uint16. */
      /* Scalar; type uint16. */
      Counter_True = c_RegionPassAllThresholdsTF_Lin[Counter_True - 1];

      /* Demonstrate to code generation that variable is scalar */
      /* This variable needs to be a scalar to index into a non-scalar struct. */
      /* %%%%% --- Adjust region points vector to align with all regions (not just passing regions) %%%%%% */
      /* This adjusted vector will be returned for use in a later function. */
      NCentroids = j;
      for (b_i = 0; b_i < NCentroids; b_i++) {
        iidx_data[b_i] = c_RegionPassAllThresholdsTF_Lin[b_i];
      }

      NCentroids = j;
      for (b_i = 0; b_i < NCentroids; b_i++) {
        RegionPoints_data[iidx_data[b_i] - 1] = b_RegionPoints_data[b_i];
      }

      /* Assign zeros to elements corresponding to non-passing regions */
      for (b_i = 0; b_i < ElementIdx; b_i++) {
        iidx_data[b_i] = c_RegionNotPassAllThresholdsTF_[b_i];
      }

      for (b_i = 0; b_i < ElementIdx; b_i++) {
        RegionPoints_data[iidx_data[b_i] - 1] = 0U;
      }

      /* %%%%% Determine ROI of selected region %%%%%%  */
      /* Determine the ROI values, ROI_Selected_ith, of the selected region. Determining the ROI values */
      /* includes expanding the size of the region to result in a size that captures more of the face. */
      /* Additionally, run additional checks to determine whether the ROI contains skin. A true return  */
      /* value for SkinTF_ith and HasROITF_SkinPresent_ith indicates that the ROI passed these checks.  */
      /* Note: SkinDetect_SelectedRegionROI is a custom function located within folder 'FacePulseRate'.  */
      /* SkinDetect_SelectedRegionROI   Determine ROI of the selected region. */
      /*    */
      /*     Helper function to function FacePulseRate.  */
      /*     Within function FacePulseRate, called by function SkinDetect_SelectRegion. */
      /*  */
      /*  */
      /*     Code Generation */
      /*     --------------- */
      /*  */
      /*     Can be called as a Matlab function or used for C-language code generation. */
      /*  */
      /*  */
      /*     Description */
      /*     ----------- */
      /*  */
      /*     Determine the ROI values, ROI_Selected_ith, of the selected region. Determining the ROI values */
      /*     includes expanding the size of the region to result in a size that captures more of the face. */
      /*     Additionally, run additional checks to determine whether the ROI contains skin. A true return  */
      /*     value for SkinTF_ith indicates that the ROI passed these checks. If SkinTF_ith is true,  */
      /*     ProportionSkinPixelsTooLowTF_ith will be false and vice versa. */
      /*  */
      /*  */
      /*     Copyright */
      /*     --------- */
      /*  */
      /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
      /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
      /*     licensing, please contact the author. */
      /* %%%%% Code-generation settings %%%%%% */
      /* Inline function */
      /* %%%%% Determine ROI based on extrema of selected region %%%%%%  */
      /* Find the minimum and maximum extrema of the selected region as row and column subscripts. */
      /* Note: because [X, Y] coordinates are interchangeable with [row, column] coordinates, this implies */
      /* that higher Y values are spatially lower on the Y axis. */
      /* Initialize minimum and maximum row and column extrema  */
      /* For the minimum, these values should be smaller than any possible values. */
      /* For the maximum, these values should be larger than any possible values. */
      NRegions_ith = 5001;
      RowMax = 1U;
      ColMin = 5001U;
      ColMax = 1U;
      nRows = (uint32_T)BoundingBoxSkin[3];

      /* Loop across pixel linear indices of the selected region to ... */
      /*  - Convert to row and column subscripts */
      /*  - Find the minimum extrema (row and column subscript minimums) */
      /*  - Find the maximum extrema (row and column subscript maximums) */
      /* Note: linear index to subscript algorithm adapted from Matlab function ind2sub. */
      b_i = (int32_T)RegionNPixels_data[Counter_True - 1];
      for (c_i = 0; c_i < b_i; c_i++) {
        /* Extract ith pixel linear index  */
        /* Scalar; type uint32. */
        /* Note: RegionIndices.PixelIdxList is an M regions x 1 non-scalar struct; each row consists of   */
        /* an N x 1 column vector (type uint32) of linear indices corresponding to the pixels of a  */
        /* region. */
        /* Convert to row subscript */
        if (nRows == 0U) {
          b_r = 1U;
        } else {
          b_r = (b_RegionIndices.data[Counter_True - 1].PixelIdxList->data
                 [(int32_T)((real32_T)c_i + 1.0F) - 1] - 1U) % nRows + 1U;
        }

        /* Assign as minimum row if smallest row value encountered */
        if (b_r < (uint32_T)NRegions_ith) {
          NRegions_ith = (int32_T)b_r;
        }

        /* Assign as maximum row if largest row value encountered */
        if (b_r > RowMax - 1U) {
          RowMax = b_r + 1U;
        }

        /* Convert to column subscript */
        b_r = b_RegionIndices.data[Counter_True - 1].PixelIdxList->data[(int32_T)
          ((real32_T)c_i + 1.0F) - 1] - b_r;
        if (nRows == 0U) {
          if (b_r == 0U) {
            z = 0U;
          } else {
            z = MAX_uint32_T;
          }
        } else {
          z = b_r / nRows;
          b_r -= z * nRows;
          if ((b_r > 0U) && (b_r >= (nRows >> 1U) + (nRows & 1U))) {
            z++;
          }
        }

        /* Assign as minimum column if smallest column value encountered */
        if (z + 1U < ColMin) {
          ColMin = z + 1U;
        }

        /* Assign as maximum column if largest column value encountered     */
        if (z + 1U > ColMax - 1U) {
          ColMax = z + 2U;
        }
      }

      /* Assign values of ROI based on extrema */
      /* Cast to type int16. */
      /* Scalars; type int16. */
      ROIRegionSelected_FullFrame[2] = (int16_T)(ColMax - ColMin);
      ROIRegionSelected_FullFrame[3] = (int16_T)(RowMax - NRegions_ith);

      /* %%%%% Adjust coordinates to the coordinate plane of the full frame %%%%%% */
      /* Adjust the [X, Y] coordinates to undo change to [X, Y] as a result of cropping. This adjustment */
      /* will place [X, Y] in the coordinate plane of the full (uncropped) frame so that [X, Y] can be used  */
      /* in the output video. To do so, add back distances of X and Y that were changed by cropping. */
      /* Note: 1 pixel length is subtracted from the [X, Y] that is added back because the previous  */
      /* cropping changed [Xoriginal, Yoriginal] to [1, 1]; that is, the cropping moved the coordinates a */
      /* distance of Xoriginal - 1 and Yoriginal - 1. */
      /* 1 x 4 row vector; type int16. */
      ROIRegionSelected_FullFrame[0] = (int16_T)((int16_T)((int16_T)ColMin +
        BoundingBoxSkin[0]) - 1);
      ROIRegionSelected_FullFrame[1] = (int16_T)((int16_T)(NRegions_ith +
        BoundingBoxSkin[1]) - 1);

      /* %%%%% Expand width and/or height of ROI according to specified thresholds %%%%%% */
      /* The ROI is expanded to increase coverage of the face or skin because skin regions, especially  */
      /* after partitioning, is likely quite small. */
      /* The ROI is expanded according to minimums specified by ROIWidthMin and ROIHeightMin, which are  */
      /* arguments to function FacePulseRate used to specify the minimum face size. The ROI values are set */
      /* to be 25% larger than ROIMinWidthProportion and ROIMinHeightProportion. Rather than expand the ROI  */
      /* up to the minimum face size, it is expanded to be 25% larger than these minimums based on the   */
      /* assumption that the size of face will be larger than the minimums for most frames.  */
      /* Specify arguments to function SkinDetect_EnlargeROI: */
      /* ROIWidthMin: width minimum, which is 25% larger than the value of ROIMinWidthProportion  */
      /* Type int16 because VidObjWidth type int16. */
      Diff32 = (int16_T)muDoubleScalarRound
        (ROIGeneralConfig->ROIMinWidthProportion * 1.25 * (real_T)
         VideoReadConfig_VidObjWidth);

      /* ROIHeightMin: height minimum, which is 25% larger than the value of ROIMinHeightProportion */
      /* Type int16 because VidObjHeight type int16. */
      functionWidthToUse = (int16_T)muDoubleScalarRound
        (ROIGeneralConfig->ROIMinHeightProportion * 1.25 * (real_T)
         VideoReadConfig_VidObjHeight);

      /* Expand ROI */
      /* Function SkinDetect_EnlargeROI enlarges the ROI as specified and also prevents the enlarged ROI     */
      /* from exceeding frame dimensions. */
      /* 1 x 4 row vector; type int16. */
      /* Note: SkinDetect_EnlargeROI is a custom function located within folder 'FacePulseRate'.         */
      /*  Enlarged ROI */
      /*  ROI to enlarge */
      /*  minimum width to apply */
      /*  minimum height to apply */
      /*  frame width to prevent ROI from exceeding frame width */
      /* SkinDetect_EnlargeROI   Expand width and height of skin-detection algorithm ROI if below minimum. */
      /*  */
      /*     Helper function to function FacePulseRate. */
      /*     Within function FacePulseRate, called by function SkinDetect_SelectedRegionROI. */
      /*  */
      /*  */
      /*     Code Generation */
      /*     --------------- */
      /*  */
      /*     Can be called as a Matlab function or used for C-language code generation. */
      /*  */
      /*  */
      /*     Description */
      /*     ----------- */
      /*  */
      /*     Expanding ROIs is intended to increase coverage of the face or skin, especially if the ROI is  */
      /*     quite small but larger regions or the face or skin are known to exist about it. ROIs are  */
      /*     expanded according to the arguments ROIWidthMin and ROIHeightMin.    */
      /*  */
      /*     Inputs: */
      /*  */
      /*         ROIMat         = M-by-4 matrix. Should be of an integer type to ensure no decimals are */
      /*                          included in the assignment; this is because no rounding is conducted. The */
      /*                          columns in the ROI matrix indicate x-upper-left corner, y-upper-left  */
      /*                          corner (larger y-values are lower on the y-axis), width, and height, in   */
      /*                          pixels. */
      /*                          Frames can be non-consecutive.  */
      /*         ROIWidthMin    = The minimum ROI width, specified as an integer type.  */
      /*                          Widths less than this value will be expanded up to this value.                                            */
      /*         ROIHeightMin   = The minimum ROI height, specified as an integer type.  */
      /*                          Heights less than this value will be expanded up to this value.                                                                      */
      /*  */
      /*     Note: this function is compatible with code generation. This compatability was used for  */
      /*     testing purposes, but a compiled funtion is not used in FacePulseRate toolbox. See function */
      /*     SkinDetect for notes. */
      /*  */
      /*  */
      /*     Copyright */
      /*     --------- */
      /*  */
      /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
      /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
      /*     licensing, please contact the author. */
      /* %%%%% Code generation specifications %%%%%% */
      /* Inline function */
      /* %%%%% Input validation %%%%%% */
      /* Should be of an integer type  */
      /* This is to ensure no decimals are included in the assignment; this is because no rounding is  */
      /* conducted. This error would likely be due to an implementation error. */
      /* %%%%% Expand specified ROI widths if less than specified minimum %%%%%% */
      /* Description: Make adjustments to widths (and, consequently, X-coordinate) if lower than specified */
      /* minimum. */
      /* %%%%% --- Identify ROIs with widths below minimum %%%%%% */
      /* Extract width columns from ROIs */
      /* Assign logical index of ROI widths that are below minimum */
      /* %%%%% --- Assign new widths for ROIs below minimum %%%%%% */
      /* Assign the specified minimum width for all ROIs below the minimum width. */
      /* Assign to vector with length the number of ROIs below minimum. */
      /* %%%%% --- Assign new left-side X-coordinates as a result of width expansion %%%%%% */
      /* Find X-coordinates of center points of ROIs with widths that were below minimum */
      /* (The centerpoints for the adjusted ROIs are the same as those for the original ROIs). */
      /* Note: ROIFindCenterPoint is a custom function located within folder 'FacePulseRate'. */
      CompletelyContainedTF = (ROIRegionSelected_FullFrame[2] < Diff32);

      /* ROIFindCenterPoint   Find center point of one or more ROIs and return as X- and Y-coordinates.                               */
      /*              */
      /*     Helper function to function FacePulseRate. */
      /*  */
      /*  */
      /*     Code Generation */
      /*     --------------- */
      /*  */
      /*     Can be called as a Matlab function or used for C-language code generation. */
      /*  */
      /*  */
      /*     Description */
      /*     ----------- */
      /*      */
      /*     Find center point of one or more ROIs and return as X- and Y-coordinates. */
      /*  */
      /*     Inputs: */
      /*  */
      /*         ROI       = ROI matrix of an integer type. The columns in the ROI matrix indicate  */
      /*                     x-upper-left corner, y-upper-left corner (higher y-values are lower on the                   */
      /*                     Matlab y-axis), width, and height, in pixels.                                                                                               */
      /*         FramesIdx = A linear index of frame(s) cooresponding to ROI(s). Frames can be  */
      /*                     non-consecutive. */
      /*                      */
      /*     Outputs: */
      /*  */
      /*         ROISpecifiedFrames_center_X = X-coordinate(s) of center point(s) of ROI(s).  */
      /*         ROISpecifiedFrames_center_Y = Y-coordinate(s) of center point(s) of ROI(s). */
      /*  */
      /*     -- Note --  */
      /*  */
      /*     Intended only for use with integer types as rounding is not conducted. For modification for  */
      /*     use with floating-point types, rounding would be necessary as ROI values should be integers. */
      /*      */
      /*  */
      /*     Copyright */
      /*     --------- */
      /*  */
      /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
      /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
      /*     licensing, please contact the author. */
      /* Inline function */
      /* ROI center X- and Y-coordinate(s) of specified ROI row(s)  */
      /* Sum X and Y-upper-left-hand corners of ROI(s) (columns 1 and 2) with half of the width(s) and  */
      /* height(s) (columns 3 and 4).  */
      /* Optimize division by 2 by bit-wise operations. */
      NCentroids = 0;
      if (CompletelyContainedTF) {
        NCentroids = 1;
      }

      ElementIdx = 0;
      if (CompletelyContainedTF) {
        ElementIdx = 1;
      }

      if (0 <= NCentroids - 1) {
        d_tmp_data[0] = (int16_T)(ROIRegionSelected_FullFrame[2] >> 1);
      }

      if (0 <= ElementIdx - 1) {
        c_ROISpecifiedFrames_center_XY_[0] = (int16_T)
          (ROIRegionSelected_FullFrame[0] + d_tmp_data[0]);
      }

      if (0 <= NCentroids - 1) {
        d_tmp_data[NCentroids] = (int16_T)(ROIRegionSelected_FullFrame[3] >> 1);
      }

      if (0 <= ElementIdx - 1) {
        c_ROISpecifiedFrames_center_XY_[ElementIdx] = (int16_T)
          (ROIRegionSelected_FullFrame[1] + d_tmp_data[NCentroids]);
      }

      /* Separate to X- and Y-coordinates */
      /* end function */
      /* Assign new left-side X-coordinates as a result of expanding width from centerpoint */
      /* Optimize division by 2 by bit-wise operation. */
      Diff12 = (int16_T)(Diff32 >> 1);

      /* %%%%% Expand ROI heights if less than specified minimum %%%%%% */
      /* Description: Make adjustments to height (and, consequently, Y-coordinate) if lower than specified */
      /* minimum.  */
      /* %%%%% --- Identify ROIs with heights below minimum %%%%%% */
      /* Extract height columns specified ROIs */
      /* Assign logical index of specified ROI heights that are below minimum */
      /* %%%%% --- Assign new heights for ROIs below minimum %%%%%% */
      /* Assign the specified minimum height for all ROIs below the minimum height. */
      /* Assign to vector with length the number of ROIs below minimum. */
      /* %%%%% --- Assign new upper-side Y-coordinates as a result of height expansion %%%%%% */
      /* Find Y-coordinates of center points of specified ROIs with heights that were below minimum */
      /* (The centerpoints for the adjusted ROIs are the same as those for the original ROIs). */
      /* Note: ROIFindCenterPoint is a custom function located within folder 'FacePulseRate'. */
      CompletelyContainedTF = (ROIRegionSelected_FullFrame[3] <
        functionWidthToUse);

      /* ROIFindCenterPoint   Find center point of one or more ROIs and return as X- and Y-coordinates.                               */
      /*              */
      /*     Helper function to function FacePulseRate. */
      /*  */
      /*  */
      /*     Code Generation */
      /*     --------------- */
      /*  */
      /*     Can be called as a Matlab function or used for C-language code generation. */
      /*  */
      /*  */
      /*     Description */
      /*     ----------- */
      /*      */
      /*     Find center point of one or more ROIs and return as X- and Y-coordinates. */
      /*  */
      /*     Inputs: */
      /*  */
      /*         ROI       = ROI matrix of an integer type. The columns in the ROI matrix indicate  */
      /*                     x-upper-left corner, y-upper-left corner (higher y-values are lower on the                   */
      /*                     Matlab y-axis), width, and height, in pixels.                                                                                               */
      /*         FramesIdx = A linear index of frame(s) cooresponding to ROI(s). Frames can be  */
      /*                     non-consecutive. */
      /*                      */
      /*     Outputs: */
      /*  */
      /*         ROISpecifiedFrames_center_X = X-coordinate(s) of center point(s) of ROI(s).  */
      /*         ROISpecifiedFrames_center_Y = Y-coordinate(s) of center point(s) of ROI(s). */
      /*  */
      /*     -- Note --  */
      /*  */
      /*     Intended only for use with integer types as rounding is not conducted. For modification for  */
      /*     use with floating-point types, rounding would be necessary as ROI values should be integers. */
      /*      */
      /*  */
      /*     Copyright */
      /*     --------- */
      /*  */
      /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
      /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
      /*     licensing, please contact the author. */
      /* Inline function */
      /* ROI center X- and Y-coordinate(s) of specified ROI row(s)  */
      /* Sum X and Y-upper-left-hand corners of ROI(s) (columns 1 and 2) with half of the width(s) and  */
      /* height(s) (columns 3 and 4).  */
      /* Optimize division by 2 by bit-wise operations. */
      NCentroids = 0;
      if (CompletelyContainedTF) {
        NCentroids = 1;
      }

      NRegions_ith = 0;
      if (CompletelyContainedTF) {
        NRegions_ith = 1;
      }

      if (0 <= NCentroids - 1) {
        d_tmp_data[0] = (int16_T)(ROIRegionSelected_FullFrame[2] >> 1);
      }

      if (0 <= NRegions_ith - 1) {
        d_ROISpecifiedFrames_center_XY_[0] = (int16_T)
          (ROIRegionSelected_FullFrame[0] + d_tmp_data[0]);
      }

      if (0 <= NCentroids - 1) {
        d_tmp_data[NCentroids] = (int16_T)(ROIRegionSelected_FullFrame[3] >> 1);
      }

      if (0 <= NRegions_ith - 1) {
        d_ROISpecifiedFrames_center_XY_[NRegions_ith] = (int16_T)
          (ROIRegionSelected_FullFrame[1] + d_tmp_data[NCentroids]);
      }

      /* Separate to X- and Y-coordinates */
      /* end function */
      /* Assign upper-side Y-coordinates as a result of expanding height from centerpoint */
      /* Optimize division by 2 by bit-wise operation. */
      Diff22 = (int16_T)(functionWidthToUse >> 1);

      /* %%%%% Verify adjustments are within frame dimensions; Adjust if necessary to conform %%%%%% */
      /* Function ROIAdjustIfExceedsFrameDims verifies if adjusted ROIs are within frame dimensions and, if */
      /* not, adjusts the ROI values to conform to frame dimensions. */
      /* Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder 'FacePulseRate'.  */
      if (0 <= ElementIdx - 1) {
        ROIPredicted_data[0] = (int16_T)(c_ROISpecifiedFrames_center_XY_[0] -
          Diff12);
      }

      if (0 <= NRegions_ith - 1) {
        ROIPredicted_data[1] = (int16_T)
          (d_ROISpecifiedFrames_center_XY_[NRegions_ith] - Diff22);
      }

      ROIPredicted_data[2] = Diff32;
      ROIPredicted_data[3] = functionWidthToUse;

      /* ROIAdjustIfExceedsFrameDims   Verify whether proposed widths and heights of ROIs exceed frame  */
      /*                               dimensions and, if so, modify them to conform to frame dimensions. */
      /*                                */
      /*     Helper function to function FacePulseRate. */
      /*     Within function FacePulseRate, called by functions ROIResize, ROIMeans_FirstRead_Extrapolate, */
      /*     SkinDetect_EnlargeROI, ROIMSIR, ROIMSIR_MatchSize, ROIMSIR_DetectionSmooth,   */
      /*     ROIMSIR_Interpolate, and ROIMSIR_FrameByFrameSmooth.    */
      /*  */
      /*  */
      /*     Code Generation */
      /*     --------------- */
      /*  */
      /*     Can be called as a Matlab function or used for C-language code generation. */
      /*  */
      /*  */
      /*     Description */
      /*     ----------- */
      /*  */
      /*     This function verifies that ROIs that have had modifications to their sizes are still within */
      /*     the dimensions of the frame. If not, this function adjusts the dimensions (and, consequently,   */
      /*     the spatial coordinates) to conform to the frame dimensions. */
      /*  */
      /*     -- Note --  */
      /*  */
      /*     Intended only for use with integer types as rounding is not conducted. For modification for  */
      /*     use with floating-point types, rounding would be necessary as ROI values should be integers. */
      /*  */
      /*  */
      /*     Copyright */
      /*     --------- */
      /*  */
      /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
      /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
      /*     licensing, please contact the author. */
      /* %%%%% Validate inputs %%%%%% */
      /* Exit if empty */
      /* Validate whether input ROIsProposed is type int16. */
      /* Must be an integer type because no rounding is conducted. */
      /* Should be type int16 because the function is implemented to assign values of this type. */
      /* A non-matching type would be due to an implementation error. */
      /* %%%%% Running in code generation %%%%%% */
      /* When running in code generation, use for-loops. When running in Matlab code, use vectorization. */
      /* code generation running */
      /* Inline function */
      /* %%%%% --- Verify, and adjust if necessary, X-coordinates and widths %%%%%% */
      /* Adjust left-side X-coordinate if exceeds frame dimensions: */
      Diff12 = (int16_T)(ROIPredicted_data[0] - 1);
      if (ROIPredicted_data[0] < 1) {
        Diff12 = 0;

        /* recent code mod */
        ROIPredicted_data[0] = 1;
      } else {
        if (ROIPredicted_data[0] > VideoReadConfig_VidObjWidth) {
          Diff12 = (int16_T)(VideoReadConfig_VidObjWidth - 1);

          /* recent code mod */
          ROIPredicted_data[0] = VideoReadConfig_VidObjWidth;
        }
      }

      /* Adjust right-side X-coordinate if exceeds frame dimensions: */
      Diff22 = (int16_T)(Diff12 + Diff32);
      if (Diff22 > VideoReadConfig_VidObjWidth) {
        Diff22 = VideoReadConfig_VidObjWidth;
        ROIPredicted_data[2] = (int16_T)(VideoReadConfig_VidObjWidth - Diff12);
      } else {
        if (Diff22 < 1) {
          Diff22 = 1;
          Diff12 = 0;
          ROIPredicted_data[0] = 1;
          ROIPredicted_data[2] = 1;
        }
      }

      /* Adjust width if exceeds frame dimensions: */
      Diff12 = (int16_T)(Diff22 - Diff12);
      if (Diff12 > VideoReadConfig_VidObjWidth) {
        ROIPredicted_data[2] = VideoReadConfig_VidObjWidth;
      } else {
        if (Diff12 < 1) {
          ROIPredicted_data[2] = 1;
        }
      }

      /* %%%%% --- Verify, and adjust if necessary, Y-coordinates and heights %%%%%% */
      /* Adjust top-side Y-coordinate if exceeds frame dimensions: */
      Diff12 = (int16_T)(ROIPredicted_data[1] - 1);
      if (ROIPredicted_data[1] < 1) {
        Diff12 = 0;

        /* recent code mod */
        ROIPredicted_data[1] = 1;
      } else {
        if (ROIPredicted_data[1] > VideoReadConfig_VidObjHeight) {
          Diff12 = (int16_T)(VideoReadConfig_VidObjHeight - 1);

          /* recent code mod */
          ROIPredicted_data[1] = VideoReadConfig_VidObjHeight;
        }
      }

      /* Adjust bottom-side Y-coordinate if exceeds frame dimensions: */
      Diff22 = (int16_T)(Diff12 + functionWidthToUse);
      if (Diff22 > VideoReadConfig_VidObjHeight) {
        Diff22 = VideoReadConfig_VidObjHeight;
        ROIPredicted_data[3] = (int16_T)(VideoReadConfig_VidObjHeight - Diff12);
      } else {
        if (Diff22 < 1) {
          Diff22 = 1;
          Diff12 = 0;
          ROIPredicted_data[1] = 1;
          ROIPredicted_data[3] = 1;
        }
      }

      /* Adjust height value if exceeds frame dimensions: */
      Diff12 = (int16_T)(Diff22 - Diff12);
      if (Diff12 > VideoReadConfig_VidObjHeight) {
        ROIPredicted_data[3] = VideoReadConfig_VidObjHeight;
      } else {
        if (Diff12 < 1) {
          ROIPredicted_data[3] = 1;
        }
      }

      /* %%%%% Code generation not running %%%%%% */
      /* end function */
      /* ============================================================================================= */
      /* Code-generation and build script */
      /* ============================================================================================= */
      /* Code-generation and build script used to generate C-language code and create the compiled version  */
      /* (ROIAdjustIfExceedsFrameDims_mex) of the function. */
      /* { */
      /*  */
      /* %%%%% Specify variable-size input arguments %%%%%% */
      /*  */
      /* See Matlab documentation for coder.typeof. */
      /*  */
      /*                                   Example Code               Upp. Bounds   Var. Size (T/F)  Type */
      /* ROIsProposedCode   = coder.typeof( zeros(500, 4, 'int16'),    [inf, 4],     [1, 0] );        %int16 */
      /*            */
      /*        */
      /* %%%%% Specify fixed-size input arguments %%%%%% */
      /*  */
      /* VidObjWidthCode  = int16(0);          */
      /* VidObjHeightCode = int16(0); */
      /*                    */
      /*  */
      /* %%%%% Set configurations to increase performance %%%%%% */
      /*  */
      /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
      /* "Optimization Strategies" */
      /*  */
      /* cfg = coder.config('mex'); */
      /* cfg.GlobalDataSyncMethod = 'NoSync'; */
      /* cfg.ConstantInputs = 'IgnoreValues'; */
      /* cfg.ExtrinsicCalls = true; %permit to show assert error */
      /* cfg.SaturateOnIntegerOverflow = false; */
      /* cfg.IntegrityChecks = false; */
      /* cfg.ResponsivenessChecks = false; */
      /*  */
      /*  */
      /* %%%%% Specify flags to minGW compiler to optimize execution speed %%%%%% */
      /*  */
      /* For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html */
      /*  */
      /* The flags are specified as part of the code-generation configuration object. A custom function, */
      /* setbuildargs, is used to specify these flags. For details on the function implementation, see the  */
      /* function file, which is located within folder FacePulseRate. This custom function is based upon  */
      /* Matlab guidance found in */
      /* https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function */
      /*  */
      /* setbuildargs will be evaluated from text within the code-generation object, so it is converted to  */
      /* a character vector prior to execution of the codegen command. */
      /*  */
      /* %%%%% --- Specify the flags as arguments to function setbuildargs %%%%%% */
      /*  */
      /* Argument buildInfo: this variable is assign by the caller (the codegen command executed below) and  */
      /* is not present in the base workspace. */
      /*  */
      /* Second argument: specify a cell array of compiler-specific flags, where each flag is a character  */
      /* vector. As function setbuildargs will be evaluated from text, use double ' quotes for each */
      /* character vector to maintain the charater vector, */
      /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
      /*  */
      /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})'; */
      /*  */
      /* Assign to code-generation configuration object */
      /* cfg.PostCodeGenCommand = setbuildargsAsText; */
      /*  */
      /*  */
      /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
      /*  */
      /* codegen ROIAdjustIfExceedsFrameDims.m -report -config cfg -args {ROIsProposedCode, VidObjWidthCode, VidObjHeightCode} */
      /*                  */
      /* } */
      /* %%%%% Assign adjusted ROIs to ROI matrix %%%%%% */
      /* Assign new left-side X-coordinates, which were modified as a result of width expansion, to ROI */
      /* matrix.  */
      NCentroids = 0;
      if (ROIRegionSelected_FullFrame[2] < Diff32) {
        NCentroids = 1;
      }

      if (0 <= NCentroids - 1) {
        ROIRegionSelected_FullFrame[0] = ROIPredicted_data[0];
      }

      /* Assign new upper-size Y-coordinates, which were modified as a result of height expansion, to ROI  */
      /* matrix.  */
      NCentroids = 0;
      if (ROIRegionSelected_FullFrame[3] < functionWidthToUse) {
        NCentroids = 1;
      }

      if (0 <= NCentroids - 1) {
        ROIRegionSelected_FullFrame[1] = ROIPredicted_data[1];
      }

      /* Assign expanded widths, where skin-detection ROI widths were below minimum, to ROI matrix  */
      NCentroids = 0;
      if (ROIRegionSelected_FullFrame[2] < Diff32) {
        NCentroids = 1;
      }

      if (0 <= NCentroids - 1) {
        ROIRegionSelected_FullFrame[2] = ROIPredicted_data[2];
      }

      /* Assign expanded heights, where skin-detection ROI heights were below minimum, to ROI matrix  */
      NCentroids = 0;
      if (ROIRegionSelected_FullFrame[3] < functionWidthToUse) {
        NCentroids = 1;
      }

      if (0 <= NCentroids - 1) {
        ROIRegionSelected_FullFrame[3] = ROIPredicted_data[3];
      }

      /* end function */
      /*    frame height to prevent ROI from exceeding frame height */
      /* %%%%% Verify the validity of ROI %%%%%%     */
      /* Note: SkinDetect_ROIValidate is a custom function located within folder 'FacePulseRate'. */
      /* SkinDetect_ROIValidate   Verify the validity of the ROI from the skin-detection algorithm. */
      /*    */
      /*     Helper function to function FacePulseRate.  */
      /*     Within function FacePulseRate, called by function SkinDetect_SelectRegionROI. */
      /*  */
      /*  */
      /*     Code Generation */
      /*     --------------- */
      /*  */
      /*     Can be called as a Matlab function or used for C-language code generation. */
      /*  */
      /*  */
      /*     Description */
      /*     ----------- */
      /*  */
      /*     Verify the validity of the ROI from the skin-detection algorithm. The ROI is considered valid  */
      /*     if the proportion of pixels classified as skin exceeds a specified threshold. The proportion  */
      /*     is calculated by inspecting the skin-segmentation mask that corresponds to the location of the  */
      /*     ROI. Specifically, in the portion of the skin-segmentation mask that corresponds to the ROI,  */
      /*     the number of elements classified as true is divided by the total number of elements. This  */
      /*     calculation is conducted by function ConfirmSkinPresent. This function returns a true / false  */
      /*     determination on whether the proportion exceeded the specified threshold.  */
      /*  */
      /*     If the ROI is completely contained within the skin-segmentation mask: */
      /*  */
      /*     The skin-segmentation mask will be cropped to the ROI dimensions and then passed to function */
      /*     ConfirmSkinSegment. The function will check the proportion of skin pixels and return a  */
      /*     validity determination. */
      /*  */
      /*     If the ROI is not completely contained within the skin-segmentation mask: */
      /*  */
      /*     In other words, all or some portion of the ROI is located outside of the existing  */
      /*     skin-segmentation mask. The full video frame will be passed to function ConfirmSkinPresent. */
      /*     The function will produce a skin-segmentation mask corresponding to the ROI and then check the  */
      /*     proportion of skin pixels and return a validity determination. This condition is less  */
      /*     efficient than the above condition because the skin-segmentation mask is recalculated rather  */
      /*     than just cropped. */
      /*  */
      /*  */
      /*     Copyright */
      /*     --------- */
      /*  */
      /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
      /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
      /*     licensing, please contact the author.    */
      /* %%%%% Code-generation settings %%%%%% */
      /* Inline function */
      /* %%%%% Specify algorithm for ROI verification %%%%%% */
      /* Indicate that the algorithm is the skin-detection algorithm.  */
      /* Note: This setting specifies which threshold is used from SkinSegmentConfig.ConfirmSkin.  */
      /* SkinSegmentConfig.ConfirmSkin is assigned by function SkinSegment_ConfigSetupConfirmSkinPresent. */
      /* %%%%% Determine whether ROI is completely contained within skin-segmentation mask %%%%%%  */
      /* Determine whether the ROI is completely contained within the skin-segmentation mask.  */
      /* This is true if no extrema of the ROI exceeds the bounds of the skin-segmentation mask. */
      /* Local function. */
      /* Scalar; type logical. */
      /* end main function */
      /* ============================================================================================= */
      /* Local functions */
      /* ============================================================================================= */
      /* ============================================================================================= */
      /* IsCompletelyContained   Determine whether the selected ROI is completely contained within the */
      /*                         skin-segmentation mask. */
      /* Inline function */
      /* XY-coordinates of extrema of the selected-region ROI: */
      /* Type int16. */
      /* X left */
      /* X right */
      /* Y top */
      /* Y bottom */
      /* Determine whether the ROI is completely contained within the skin-segmentation mask.  */
      /* This is true if no extrema of the ROI exceeds the bounds of the skin-segmentation mask. */
      /* Selected-region extrema            ...Skin-segmentation mask extrema */
      /*  X left within */
      /*  Y top within */
      /*  X right within */
      if ((ROIRegionSelected_FullFrame[0] > BoundingBoxSkin[0]) &&
          (ROIRegionSelected_FullFrame[1] > BoundingBoxSkin[1]) && ((int16_T)
           ((int16_T)(ROIRegionSelected_FullFrame[0] +
                      ROIRegionSelected_FullFrame[2]) - 1) < (int16_T)((int16_T)
            (BoundingBoxSkin[0] + BoundingBoxSkin[2]) - 1)) && ((int16_T)
           ((int16_T)(ROIRegionSelected_FullFrame[1] +
                      ROIRegionSelected_FullFrame[3]) - 1) < (int16_T)((int16_T)
            (BoundingBoxSkin[1] + BoundingBoxSkin[3]) - 1))) {
        CompletelyContainedTF = true;
      } else {
        CompletelyContainedTF = false;
      }

      /*    Y bottom within */
      /* %%%%% If completely contained: Crop ROI from skin-segmentation mask and check skin pixels %%%%%%         */
      if (CompletelyContainedTF) {
        /* Adjust X- and Y-coordinates of the selected-region ROI from the coordinate plane of the full  */
        /* frame to the coordinate plane of the bounding box. */
        /* Scalars; type int16. */
        /* X-coordinate  */
        Diff22 = (int16_T)(ROIRegionSelected_FullFrame[0] - BoundingBoxSkin[0]);

        /* Y-coordinate */
        Diff12 = (int16_T)(ROIRegionSelected_FullFrame[1] - BoundingBoxSkin[1]);

        /* Crop the skin-segmentation mask to correspond to the selected-region ROI  */
        /* M x N matrix; type logical. */
        /*  rows */
        /*  columns */
        b_i = IsSkinMask_ROISelected->size[0] * IsSkinMask_ROISelected->size[1];
        IsSkinMask_ROISelected->size[0] = (int16_T)(ROIRegionSelected_FullFrame
          [3] - 1) + 1;
        IsSkinMask_ROISelected->size[1] = (int16_T)(ROIRegionSelected_FullFrame
          [2] - 1) + 1;
        emxEnsureCapacity_boolean_T(IsSkinMask_ROISelected, b_i);
        NCentroids = (int16_T)(ROIRegionSelected_FullFrame[2] - 1);
        for (b_i = 0; b_i <= NCentroids; b_i++) {
          NRegions_ith = (int16_T)(ROIRegionSelected_FullFrame[3] - 1);
          for (ElementIdx = 0; ElementIdx <= NRegions_ith; ElementIdx++) {
            IsSkinMask_ROISelected->data[ElementIdx +
              IsSkinMask_ROISelected->size[0] * b_i] = IsSkinMask->data
              [((int16_T)((int16_T)(ElementIdx + Diff12) + 1) + IsSkinMask->
                size[0] * ((int16_T)((int16_T)(b_i + Diff22) + 1) - 1)) - 1];
          }
        }

        /* Determine whether the proportion of pixels classified as skin is considered valid: */
        /* Dimensions of the cropped skin-segmentation mask */
        /* Return true / false determination on whether the proportion of skin pixels is considered  */
        /* valid. */
        /* Scalar; type logical. */
        /* Note: 'ConfirmSkinPresent' is a custom function located within folder 'FacePulseRate'. */
        /*  configurations */
        /*  unused argument */
        /* ConfirmSkinPresent   Determine whether an ROI should be considered valid based upon the proportion */
        /*                      of pixels classified as skin within the ROI. */
        /*      */
        /*     Helper function to function FacePulseRate. */
        /*     Within function FacePulseRate, called by functions FaceDetect_ROIValidate,    */
        /*     SkinDetect_ROIValidate, and ROIMeans_TakeMeans. */
        /*  */
        /*  */
        /*     Code Generation */
        /*     --------------- */
        /*  */
        /*     Can be called as a Matlab function or used for C-language code generation. */
        /*  */
        /*  */
        /*     Description */
        /*     ----------- */
        /*  */
        /*     Return a true/false determination on whether an ROI is valid by determining whether the */
        /*     proportion of pixels classified as skin within the ROI is above the specified threshold. */
        /*  */
        /*     The number of inputs to the function is variable. The number of inputs depends on the  */
        /*     information currently available regarding the classification of pixels in the ROI as skin or  */
        /*     non-skin. If the classification has already been conducted, this is entered as input to the  */
        /*     function, and the function moves to calculate the proportion of pixels classified as skin out  */
        /*     of all pixels. This is termed "condition 1". If the classification is not available,  */
        /*     information needed to conduct the classification is entered as input to the function, and the  */
        /*     classification is conducted before calculating the proportion. This is termed "condition 2".  */
        /*  */
        /*     If condition 2 is used, an additional skin-classification method can be specified,   */
        /*     specifically, the use of the skin-detection algorithm to refine the skin-segmentation mask. If  */
        /*     argument SkinDetectionThresholdsTF is true, the skin-detection algorithm will be used.  */
        /*  */
        /*     If condition 2 is used, the color channels produced during the classification operation will  */
        /*     be returned as they can be reused in other functions. */
        /*     */
        /*  */
        /*     Accuracy */
        /*     -------- */
        /*  */
        /*     If there are fewer skin-color samples than required for tailored skin segmentation, the  */
        /*     proportion of pixels may be less accurate (less conservative). Whether the required number of  */
        /*     skin-color samples has been satisfied is indicated by  */
        /*     SkinSegmentConfig.TailoredData.OpsReadyTF. */
        /*  */
        /*     If there are fewer skin-color samples than required for skin detection (see function  */
        /*     ConfirmSkinPresent_SkinDetectReject), the proportion of pixels may be less accurate (less  */
        /*     conservative. Whether the required number of skin-color samples has been satisfied is  */
        /*     indicated by SkinDetectConfig.Thresholds.SkinColorSamples_NThresholdPassedTF. */
        /*  */
        /*  */
        /*     Copyright */
        /*     --------- */
        /*  */
        /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
        /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
        /*     licensing, please contact the author. */
        /* %%%%% Code-generation settings %%%%%% */
        /* Inline function */
        /* Declare variables: */
        /*                                     Upp. Bounds    Var. Size (T/F) */
        /* %%%%% Parse inputs %%%%%% */
        /* %%%%% --- Determine whether to use condition 1 or condition 2 %%%%%% */
        /* In condition 1, skin-classification infomation is provided as input. This information can either  */
        /* be the number of pixels classified as skin or the skin-segmentation mask, from which the number of  */
        /* pixels classified as skin can be obtained. In condition 2, information to conduct the skin  */
        /* classification, namely, the color channels of the ROI, is provided as input. The condition can be  */
        /* determined according to the number of inputs to the function. */
        /* Number of inputs */
        /* Note: variable NArgin is used in two places in the function. */
        /* Condition according to the number of inputs */
        /* If the number of inputs is 6, condition 1 is used. */
        /* Note: variable Condition1TF is used in two places in the function. */
        /* %%%%% Condition 1: Classification information available %%%%%% */
        /* Determine the proportion of pixels classified as skin within the ROI. If the number of pixels  */
        /* classified as skin was not provided as input, then the skin-segmentation mask would have been */
        /* provided as input. In the latter case, obtain the number of pixels classified as skin from the */
        /* skin-segmentation mask. */
        /* If condition 1 */
        /* Argument 3 */
        /* Skin-segmentation mask. */
        /* Type logical. */
        /* Argument 4 */
        /* Count of pixels classified as true by skin-segmentation mask */
        /* This can be provided in place of providing the skin-segmentation mask. */
        /* -1 is used to ignore. */
        /* Type single. */
        /* Argument 5 */
        /* Number of rows of the skin-segmentation mask. */
        /* Argument 6 */
        /* Number of columns of the skin-segmentation mask. */
        /* Count of pixels classified as skin     */
        /* If count of pixels classified as skin not provided */
        /* (-1 is flag that count is not provided). */
        NRegions_ith = 0;
        b_i = ((int16_T)(ROIRegionSelected_FullFrame[3] - 1) + 1) * ((int16_T)
          (ROIRegionSelected_FullFrame[2] - 1) + 1);
        for (ElementIdx = 0; ElementIdx < b_i; ElementIdx++) {
          if (IsSkinMask_ROISelected->data[ElementIdx]) {
            NRegions_ith++;
          }
        }

        /* %%%%% Condition 2: Classification information not available; assign here %%%%%%     */
        /* In this condition, neither then number of pixels classified as skin nor the skin-segmentation mask */
        /* was provided as input. In this case, assign the skin-segmentation mask necessary to calculate the */
        /* number of pixels classified as skin. The skin-segmentation mask is assigned by the  */
        /* skin-segmentation algorithm. */
        /* If this condition is used, an additional skin-classification method can be specified,   */
        /* specifically, the use of the skin-detection algorithm to refine the skin-segmentation mask. If  */
        /* argument SkinDetectionThresholdsTF is true, the skin-detection algorithm will be used. The  */
        /* skin-detection algorithm is applied by function ConfirmSkinPresent_SkinDetectReject. */
        /* If condition 2     */
        /* %%%%% Determine whether ROI contains skin %%%%%% */
        /* %%%%% --- Determine proportion of ROI classified as skin %%%%%% */
        /* Determine the proportion of pixels classified as skin out of all pixels of the ROI. */
        /* Cast to a floating-point type to permit decimal. */
        /* Scalar; type single. */
        /* Note: NRows_Matrix and NCols_Matrix are type int32. */
        /* %%%%% --- Specify minimum-proportion threshold to apply %%%%%% */
        /* Specify the minimum proportion of pixels classified as skin to use as the threshold. If the  */
        /* proportion of pixels is above this threshold, the ROI will be considered valid. */
        /* Specify the thresholds according to the detection algorithm by which the ROI was returned or the   */
        /* stage of ROI processing the ROI has undergone. The thresholds are set by function  */
        /* SkinSegment_ConfigSetup. For details on the thresholds used for each case, see function */
        /* SkinSegment_ConfigSetup. */
        /* ROI after all modifications when means are taken for pulse-rate purposes (see function  */
        /* ROIMeans_TakeMeans)     */
        /* %%%%% --- Make determination on whether the ROI is valid %%%%%% */
        /* Consider the ROI valid if the proportion of pixels classified as skin exceeds the specified  */
        /* threshold. */
        /* If the proportion exceeds the threshold */
        if ((real32_T)NRegions_ith / (real32_T)(ROIRegionSelected_FullFrame[3] *
             ROIRegionSelected_FullFrame[2]) >
            SkinSegmentConfig->ConfirmSkin.ProportionThresholdSkin) {
          /* Scalar; type logical. */
          CompletelyContainedTF = true;
        } else {
          CompletelyContainedTF = false;
        }

        /* %%%%% Assign output arguments %%%%%% */
        /* If condition 1 */
        /*  Determination on whether the ROI is valid; scalar, type logical */
        /*    The proportion of skin on which the determination was made; scalar,  */
        /*    type single. */
        /* If condition 2     */
        /* end function */
        /* %%%%% If not completely contained: Crop ROI from full frame and check skin-pixel proportion %%%%%%  */
        /* The skin-segmentation mask will be reassigned by function ConfirmSkinPresent. */
      } else {
        emxInit_uint8_T(emlrtRootTLSGlobal, &RUint8, 2, true);
        emxInit_uint8_T(emlrtRootTLSGlobal, &GUint8, 2, true);
        emxInit_uint8_T(emlrtRootTLSGlobal, &BUint8, 2, true);

        /* Crop VidFrame and separate into colorspace channels */
        /* Local function. */
        /* M x N matrices; type uint8. */
        /*  full frame */
        /*  ROI X-coordinate in coordinate plane of full frame */
        /*  ROI Y-coordinate in coordinate plane of full frame */
        /*  ROI width */
        /*  ROI height */
        /*  full-frame width; scalar, type int16 */
        /*  full-frame height */
        CropVidAndSeparateChannels(emlrtRootTLSGlobal, VidFrame,
          ROIRegionSelected_FullFrame[0], ROIRegionSelected_FullFrame[1],
          ROIRegionSelected_FullFrame[2], ROIRegionSelected_FullFrame[3],
          VideoReadConfig_VidObjWidth, VideoReadConfig_VidObjHeight, RUint8,
          GUint8, BUint8);

        /* Determine whether the proportion of pixels classified as skin is above the specified threshold: */
        /* Dimensions of ROI */
        /* Scalars; type int32 */
        /* Specify whether to use thresholds that are tailored */
        /* The use of tailored thresholds provides a more conservative assessment (more likely to decide  */
        /* that the ROI is not mostly skin). */
        /* Do not return the Y channel of the YCbCr colorspace */
        /* Do not return the Cb or Cr channels of the YCbCr colorspace */
        /* Do not return the H or S channels of the HSV colorspace */
        /* Do not apply thresholds from the skin-detection algorithm to refine the inspection. */
        /* This option is intended to be used in functions where the skin-detection algorithm is not */
        /* otherwise used in order to refine the confirmation decision. As the skin-detection algorithm */
        /* has already influenced the selected region, it is not applied used here. */
        /* Return true / false determination on whether the proportion of skin pixels is considered  */
        /* valid.  */
        /* Scalar; type logical. */
        /* Note: 'ConfirmSkinPresent' is a custom function located within folder 'FacePulseRate'.  */
        /*  configurations */
        /* ConfirmSkinPresent   Determine whether an ROI should be considered valid based upon the proportion */
        /*                      of pixels classified as skin within the ROI. */
        /*      */
        /*     Helper function to function FacePulseRate. */
        /*     Within function FacePulseRate, called by functions FaceDetect_ROIValidate,    */
        /*     SkinDetect_ROIValidate, and ROIMeans_TakeMeans. */
        /*  */
        /*  */
        /*     Code Generation */
        /*     --------------- */
        /*  */
        /*     Can be called as a Matlab function or used for C-language code generation. */
        /*  */
        /*  */
        /*     Description */
        /*     ----------- */
        /*  */
        /*     Return a true/false determination on whether an ROI is valid by determining whether the */
        /*     proportion of pixels classified as skin within the ROI is above the specified threshold. */
        /*  */
        /*     The number of inputs to the function is variable. The number of inputs depends on the  */
        /*     information currently available regarding the classification of pixels in the ROI as skin or  */
        /*     non-skin. If the classification has already been conducted, this is entered as input to the  */
        /*     function, and the function moves to calculate the proportion of pixels classified as skin out  */
        /*     of all pixels. This is termed "condition 1". If the classification is not available,  */
        /*     information needed to conduct the classification is entered as input to the function, and the  */
        /*     classification is conducted before calculating the proportion. This is termed "condition 2".  */
        /*  */
        /*     If condition 2 is used, an additional skin-classification method can be specified,   */
        /*     specifically, the use of the skin-detection algorithm to refine the skin-segmentation mask. If  */
        /*     argument SkinDetectionThresholdsTF is true, the skin-detection algorithm will be used.  */
        /*  */
        /*     If condition 2 is used, the color channels produced during the classification operation will  */
        /*     be returned as they can be reused in other functions. */
        /*     */
        /*  */
        /*     Accuracy */
        /*     -------- */
        /*  */
        /*     If there are fewer skin-color samples than required for tailored skin segmentation, the  */
        /*     proportion of pixels may be less accurate (less conservative). Whether the required number of  */
        /*     skin-color samples has been satisfied is indicated by  */
        /*     SkinSegmentConfig.TailoredData.OpsReadyTF. */
        /*  */
        /*     If there are fewer skin-color samples than required for skin detection (see function  */
        /*     ConfirmSkinPresent_SkinDetectReject), the proportion of pixels may be less accurate (less  */
        /*     conservative. Whether the required number of skin-color samples has been satisfied is  */
        /*     indicated by SkinDetectConfig.Thresholds.SkinColorSamples_NThresholdPassedTF. */
        /*  */
        /*  */
        /*     Copyright */
        /*     --------- */
        /*  */
        /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
        /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
        /*     licensing, please contact the author. */
        /* %%%%% Code-generation settings %%%%%% */
        /* Inline function */
        /* Declare variables: */
        /*                                     Upp. Bounds    Var. Size (T/F) */
        /* %%%%% Parse inputs %%%%%% */
        /* %%%%% --- Determine whether to use condition 1 or condition 2 %%%%%% */
        /* In condition 1, skin-classification infomation is provided as input. This information can either  */
        /* be the number of pixels classified as skin or the skin-segmentation mask, from which the number of  */
        /* pixels classified as skin can be obtained. In condition 2, information to conduct the skin  */
        /* classification, namely, the color channels of the ROI, is provided as input. The condition can be  */
        /* determined according to the number of inputs to the function. */
        /* Number of inputs */
        /* Note: variable NArgin is used in two places in the function. */
        /* Condition according to the number of inputs */
        /* If the number of inputs is 6, condition 1 is used. */
        /* Note: variable Condition1TF is used in two places in the function. */
        /* %%%%% Condition 1: Classification information available %%%%%% */
        /* Determine the proportion of pixels classified as skin within the ROI. If the number of pixels  */
        /* classified as skin was not provided as input, then the skin-segmentation mask would have been */
        /* provided as input. In the latter case, obtain the number of pixels classified as skin from the */
        /* skin-segmentation mask. */
        /* If condition 1 */
        /* Arguments 3 to 5 */
        /* Input image, in RGB colorspace channels, to be segmented; M x N matrices; type uint8. */
        /* Argument 6 */
        /* Number of rows of an input matrix. */
        /* Argument 7 */
        /* Number of columns of an input matrix. */
        /* Argument 8 */
        /* Flag whether to use tailored thresholds during segmentation. */
        /* Tailored thresholds include the tailored-YCbCr thresholds and the tailored-HS tresholds. */
        /* Argument 9 */
        /* Flag whether to return the Y channel of the YCbCr colorspace after segmentation. This */
        /* variable is assigned during a step of the skin-segmentation operation. For efficiency, it can */
        /* returned to be reused in other functions that use this color information. */
        /* Scalar; type logical. */
        /* Argument 10     */
        /* Flag whether to return the Cb and Cr channels of the YCbCr colorspace after segmentation. This */
        /* variable is assigned during a step of the skin-segmentation operation. For efficiency, it can */
        /* returned to be reused in other functions that use this color information.  */
        /* Scalar; type logical. */
        /* Argument 11 */
        /* Flag whether to return the H and S channels of the HSV colorspace after segmentation. This */
        /* variable is produced during a step of the skin-segmentation operation. For efficiency, it can */
        /* returned to be reused in other functions that use this color information.  */
        /* Scalar; type logical. */
        /* Argument 12   */
        /* Flag whether to apply thresholds from the skin-detection algorithm to refine the inspection */
        /* Scalar; type logical.     */
        /* Argument 13 */
        /* Configurations for the skin-detection algorithm, which are used if SkinDetectionThresholdsTF  */
        /* is true. */
        /* %%%%% --- Assign skin-segmentation mask %%%%%% */
        /* Return a logical matrix, i.e., a skin-segmentation mask, where pixels classified as skin are  */
        /* true. Also return ImageToInspect broken down by channel in the YCbCr colorspace for reuse by  */
        /* other functions. */
        /* Arguments to function SkinSegmentMask, which returns the skin-segmentation mask: */
        /* Argument TailoredThresholdsTF is specified as an argument to the current function. */
        /* This argument specifies whether tailored thresholds should be used for skin segmentation. */
        /* Argument ReturnYTF is specified as an argument to the current function. */
        /* This argument specifies whether the Y channel of the YCbCr colorspace should be returned.  */
        /* This channels, assigned during skin-segmentation operations, would be returned so that it */
        /* could be reused by other functions.     */
        /* Argument ReturnCbCrTF is specified as an argument to the current function. */
        /* This argument specifies whether the Cb and Cr channels of the YCbCr colorspace should be  */
        /* returned. These channels, assigned during skin-segmentation operations, would be returned so */
        /* that they could be reused by other functions.  */
        /* Argument ReturnHSTF is specified as an argument to the current function. */
        /* This argument specifies whether the H and S channel sof the HSV colorspace should be returned.   */
        /* These channels, assigned during skin-segmentation operations, would be returned so that they  */
        /* could be reused by other functions.  */
        /* Assign as variable for code-generation purpose */
        /* Note: SkinSegmentMask is a custom function located within folder FacePulseRate. */
        /*  Skin-segmentation mask; M x N matrix, type logical */
        /*  Count of pixels classified as skin; scalar, type uint32 */
        /*  Y channel of the YCbCr colorspace; M x N matrix, type single */
        /*  Cb channel of the YCbCr colorspace; M x N matrix, type single */
        /*  Cr channel of the YCbCr colorspace; M x N matrix, type single */
        /*  H channel of the HSV colorspace; M x N matrix, type single */
        /*  S channel of the HSV colorspace; M x N matrix, type single */
        /*  Skin-segmentation mask based upon local range threshold; M x N matrix, */
        /*  type logical. */
        /*  Bounded frame in RGB colorspace separated */
        /*  by channel; type uint8. */
        /*  Unused arguments */
        /*  Number of rows of an input matrix */
        /*  Number of columns of an input matrix */
        /*  Whether to return a count of pixels */
        /*  classified as skin. */
        /*  Whether to use YCbCr thresholds that are */
        /*  tailored. */
        /*  Whether to return Y channel of the YCbCr */
        /*  colorspace. */
        /*  Whether to return Cb and Cr channels of */
        /*  the YCbCr colorspace. */
        /*  Whether to return the H and S channels of */
        /*  the HSV colorspace. */
        /*  Whether to use severe tailored thresholds */
        /*  Whether the morphological close operation */
        /*  will be conducted with a high level of */
        /*  severity. */
        /*  Optional X-coordinate offset; specify -1 */
        /*  to ignore; type int32. */
        /*  Optional Y-coordinate offset; specify -1 */
        /*  to ignore; type int32. */
        /*  Skin-segmentation configurations */
        /*  Whether to use compiled functions */
        /* SkinSegmentMask   Return logical matrix, or skin-segmentation mask, where pixels classified as  */
        /*                   skin are true. Wrapper function for function SkinSegmentMask_Ops. */
        /*    */
        /*     Helper function to function FacePulseRate.  */
        /*     Within function FacePulseRate, this function is called by functions ... */
        /*         - ConfirmSkinPresent (which is called by functions FaceDetect_ROIValidate,   */
        /*           SkinDetect_SelectedRegionROI, and ROIMeans_TakeMeans) */
        /*         - SkinDetect_PartitionRegions (which is called by function SkinDetect)           */
        /*         - ROIMeans_TakeMeans (which is called by functions ROIMeans_FirstRead_TakeMeans and */
        /*           ROIMeans_SecondRead_TakeMeans) */
        /*         - ROIMeans_FirstRead_CollectSkinColorSamples (which is called by function */
        /*           ROIMeans_FirstRead) */
        /*  */
        /*  */
        /*     Code Generation */
        /*     --------------- */
        /*  */
        /*     Can be called as a Matlab function or used for C-language code generation. */
        /*  */
        /*  */
        /*     Description */
        /*     ----------- */
        /*  */
        /*     Return logical matrix, or skin-segmentation mask, where pixels classified as skin are true. */
        /*     This is a wrapper function for function SkinSegmentMask_Ops. For a description of the  */
        /*     skin-segmentation operations, see function SkinSegmentMask_Ops. */
        /*  */
        /*     Execute either the compiled or non-compiled function depending on argument  */
        /*     UseCompiledFunctionsTF. */
        /*  */
        /*  */
        /*     Copyright */
        /*     --------- */
        /*  */
        /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
        /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
        /*     licensing, please contact the author.  */
        /* %%%%% Code-generation settings %%%%%% */
        /* Inline function */
        /* Compiled functions enabled and code generation not running */
        /* Value of SkinSegmentConfig.UseCompiledFunctionsTF assigned in function  */
        /* SkinSegment_ConfigSetup.  */
        /* Note: SkinSegmentMask_Ops is a custom function located within folder FacePulseRate. */
        /* SkinSegmentMask_Ops   Return logical matrix, or skin-segmentation mask, where pixels classified as   */
        /*                       skin are true. */
        /*                                                */
        /*     Helper function to function FacePulseRate.  */
        /*     Within function FacePulseRate, called by function SkinSegmentMask. */
        /*  */
        /*  */
        /*     Code generation */
        /*     --------------- */
        /*  */
        /*     Can be called as a Matlab function or used for C-language code generation. */
        /*  */
        /*     Compiled file: The compiled file included in folder FacePulseRate  */
        /*     (SkinSegmentMask_Ops_mex.mexw64) only compatible on Windows platforms.        */
        /*  */
        /*  */
        /*     Description */
        /*     ----------- */
        /*  */
        /*     -- Combined Use of YCbCr and HSV Colorspaces for Pixel-Color Thresholds -- */
        /*  */
        /*     The combined used of the YCbCr and HSV colorspaces is based on ... */
        /*     (1) Dahmani et al. (2020), who found that using both improved skin classification compared to */
        /*         the use of either alone. */
        /*     (2) The observation that using only the YCbCr colorspace did not permit enough diversity of */
        /*         individual differences in skin color. Specifically, Y-minimum and Cr-minimum must be at  */
        /*         least as low as the defaults to avoid oversegmentation in individuals with darker average */
        /*         skin colors when ambient illumination is rather low. However, these defaults also permit  */
        /*         pixel values from objects that should be segmented out; for example, the Cr-minimum at  */
        /*         this level permits pixel values from overhead lamps. Applying the HSV thresholds in  */
        /*         addition to the YCbCr thresholds segmented out these extraneous objects. */
        /*  */
        /*     -- YCbCr Pixel-Color Thresholds --  */
        /*  */
        /*     YCbCr color thresholds in use: */
        /*  */
        /*     - Y-channel minimum */
        /*     - Y-channel maximum (tailored-thresholds only) */
        /*     - Cb-channel minimum */
        /*     - Cb-channel maximum  */
        /*     - Cr-channel minimum */
        /*     - Cr-channel maximum  */
        /*  */
        /*     Apply color thresholds to individual pixels from the luminance (Y), Cb chroma (Cb), and Cr  */
        /*     chroma (Cr) channels of the YCbCr colorspace. */
        /*  */
        /*     Use either the generic YCbCr color thresholds or tailored YCbCr color thresholds. The use of */
        /*     tailored thresholds is specified by argument TailoredThresholdsTF. However, generic thresholds */
        /*     are used when TailoredThresholdsTF is true if the criterion for using tailored thresholds has */
        /*     not been satisfied, which is indicated by DontUseTailoredTF == true.  */
        /*  */
        /*         Generic Thresholds */
        /*  */
        /*     The YCbCr generic color thresholds (SkinSegmentArgs.YCbCrThresholdsGeneric) are used when */
        /*     TailoredThresholdsTF is set to false. Thresholds include a Y-channel minimum, Cb-channel  */
        /*     minimum and maximum, Cr-channel minimum and maximum, and Cb-to-Cr ratio minimum and maximum. */
        /*      */
        /*     The threshold values are set by an argument, SkinSegmentYCbCrThresholdsGeneric, to function  */
        /*     FacePulseRate. If the argument is not specified, default values are used. The default Y, Cb,   */
        /*     and Cr minimums and maximums are based on a consultation of the values provided in iphys  */
        /*     toolbox (McDuff & Blackford, 2019). These values were modified somewhat as a result of   */
        /*     testing. The Cb-to-Cr ratio minimum and maximum and not used in iphys toolbox; these values  */
        /*     were developed through testing. */
        /*       */
        /*     Function SkinSegment_ConfigSetup sets the values for SkinSegmentArgs.YCbCrThresholdsGeneric */
        /*     based on argument SkinSegmentThresholdsGenericYCbCr.     */
        /*  */
        /*     Within the current function, the YCbCr generic threshold operations are conducted by function   */
        /*     SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold. */
        /*  */
        /*         Tailored Thresholds */
        /*  */
        /*     The YCbCr tailored thresholds (SkinSegmentArgs.YCbCrThresholdsGeneric) are used when */
        /*     TailoredThresholdsTF is set to true. The threshold values are set based upon skin-color   */
        /*     samples collected from the input video. The threshold types include those used in the generic */
        /*     thresholds as well as a Y-channel maximum. The Y-channel maximum may be more sensitive than */
        /*     other thresholds to individual differences in facial colors. Due to this sensitivity, this */
        /*     value is not used for generic thresholds but is used for tailored thresholds as tailored */
        /*     thresholds are based upon the face in the video. */
        /*  */
        /*     The skin-color samples are collected from the input video. For details on the collection of  */
        /*     skin-color samples, see function ROIMeans_FirstRead_CollectSkinColorSamples. Before a */
        /*     sample is collected by function ROIMeans_FirstRead_CollectSkinColorSamples, function  */
        /*     ROIMeans_FirstRead_CollectSkinColorSamples calls function SkinSegmentMask to attempt to  */
        /*     isolate pixel colors corresponding to skin. When SkinSegmentMask is called by function  */
        /*     ROIMeans_FirstRead_CollectSkinColorSamples samples, TailoredThresholdsTF is set to false; that  */
        /*     is, generic thresholds are used. As tailored thresholds are based upon skin-color samples that */
        /*     were filtered by the generic thresholds, the tailored thresholds can be expected to be more */
        /*     stringent compared to the generic thresholds. The term "sample" refers to two values taken  */
        /*     from each YCbCr color channel of skin-segmented ROI. Specifically, the the minimum and maximum */
        /*     color values are taken from each channel.  */
        /*      */
        /*     Skin-color samples used for tailored YCbCr thresholds are collected by function  */
        /*     ROIMeans_FirstRead_CollectSkinColorSamples, which is called by function ROIMeans_FirstRead.  */
        /*     For details on the collection of skin-color samples, see function  */
        /*     ROIMeans_FirstRead_CollectSkinColorSamples.  */
        /*  */
        /*     After a certain number of samples has been collected, the samples are used to set the tailored  */
        /*     threshold values. The setting of thresholds from skin-color samples is conduted by function */
        /*     SkinSegment_SetThresholds. The number of samples required to set the tailored threshold  */
        /*     values, SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold, is specified by function  */
        /*     SkinSegment_ConfigSetup. This value can only be modified by adjusting the code within this */
        /*     function.  */
        /*  */
        /*     It has been observed that if the skin-color samples are too heavily concentrated within a  */
        /*     particular portion of the video, the thresholds that come from them can be too restrictive.  */
        /*     This is likey because samples limited to a brief portion of the video do not contain a */
        /*     sufficient level enough heterogeneity to reflect the color variations across the video. To  */
        /*     address this restrictiveness, the thresholds are reset periodically. Specifically, the  */
        /*     thresholds are reset after a specified number of frames has elapsed since the thresholds were  */
        /*     last set or reset. This number of frames is specified by  */
        /*     SkinSegmentConfig.TailoredData.ThresholdOpsInterval, which is set by function */
        /*     SkinSegment_ConfigSetup. This value can only be modified by adjusting the code within function */
        /*     SkinSegment_ConfigSetup. */
        /*  */
        /*     Although resetting the thresholds addresses the lack of heterogeneity across most of the  */
        /*     video, heterogeneity may still be unacceptably low between the first setting of the thresholds */
        /*     and the first resetting of the thresholds. This may occur if the skin-color samples are */
        /*     collected within close proximity. One condition that causes samples to be collected within  */
        /*     close proximity is a low frame-skipping rate (ROIGeneralConfig.ROISkipFrameThreshold; see */
        /*     function ROIGeneralConfig_Setup). To increase the heterogeneity in this case, the number of  */
        /*     skin-color samples required before the first thresholds are set  */
        /*     (SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold) is increased when the   */
        /*     frame-skipping rate is relatively low (see funtion SkinSegment_ConfigSetup).  */
        /*  */
        /*     Before the required number of skin-color samples has been collected, generic thresholds are */
        /*     used in place of tailored thresholds. If argument TailoredThresholdsTF is set to true,  */
        /*     specifying that tailored thresholds should be used, generic thresholds will be used if the  */
        /*     required number of samples has not been collected. Within the current function, the flag */
        /*     DontUseTailoredTF is set to true in this case to indicate that generic thresholds should be   */
        /*     used in place of tailored thresholds. */
        /*      */
        /*     For each skin-color sample, minimums and maximums are taken from each colorspace channel.  */
        /*     These values are set aside until the thresholds are to be set or reset. When setting or  */
        /*     resetting occurs, percentiles are applied to these values to extract the values at lower and */
        /*     upper percentiles. The value at the lower percentile becomes the lower threshold and the */
        /*     value at the upper percentile becomes the upper percentile. For example, suppose the lower and  */
        /*     upper percentiles are specified as 1.5 and 98.5, respecively. From all skin-color samples */
        /*     previously collected, the sample values from each channel that occur at the 1.5th percentile   */
        /*     and 98.5th percentile become the lower the upper thresholds, respectively. One point of  */
        /*     confusion may be that the terms "minimum" and "maximum" are used for two purposes here. */
        /*     The first use is in taking the minimum and maximum of each skin-color sample. These minimums */
        /*     and maximums are set aside until the percentiles are applied. When the percentiles are  */
        /*     applied, the lower percentile becomes the lower threshold and the upper percentile becomes the */
        /*     upper threshold. Although the terms "upper" and "lower" and used to refer to these thresholds */
        /*     for clarity, the terms "minimum" and "maximum" would also be appropriate. That is, the lower, */
        /*     or minimum, threshold is selected from a collection of minimum values; the upper, or maximum, */
        /*     threshold is selected from a collection of maximum values. */
        /*  */
        /*     One set of percentiles is used for the Y, Cb, Cr, Cb-to-Cr ratio, and H thresholds, and a  */
        /*     separate set of percentiles is used for the S thresholds. A separate set of percentiles is  */
        /*     used for the S thresholds because it has been observed that a wider range is appropriate for */
        /*     the S color channel. These percentiles are specified by function SkinSegmentConfig_Setup. The */
        /*     percentiles can be modified only by adjusting the code within SkinSegmentConfig_Setup. */
        /*  */
        /*     Within the current function, the YCbCr tailored threshold operations are conducted by function   */
        /*     SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold. */
        /*  */
        /*     -- HSV Pixel-Color Thresholds -- */
        /*    */
        /*     HSV color thresholds in use: */
        /*  */
        /*     - H-channel maximum */
        /*     - S-channel minimum */
        /*     - S-channel maximum (tailored-thresholds only) */
        /*  */
        /*     Apply color thresholds to individual pixels from the hue (H) and saturation (S) channels of   */
        /*     the HSV colorspace. */
        /*      */
        /*     Use either the generic HSV color thresholds or tailored HSV color thresholds. The use of */
        /*     tailored thresholds is specified by argument TailoredThresholdsTF. However, generic  */
        /*     thresholds are used when TailoredThresholdsTF is true if the criterion for using tailored  */
        /*     thresholds has not been satisfied, which is indicated by DontUseTailoredTF == true. */
        /*  */
        /*         Generic Thresholds */
        /*  */
        /*     The HSV generic color thresholds (SkinSegmentArgs.HSVThresholdsGeneric) are used when */
        /*     TailoredThresholdsTF is set to false. Thresholds include an H-channel maximum and an S-channel */
        /*     minimum. */
        /*      */
        /*     The threshold values are set by an argument, SkinSegmentThresholdsGenericHSV, to function  */
        /*     FacePulseRate. If the argument is not specified, default values are used. The default H and S   */
        /*     minimums and maximums are based on testing by DPM.  */
        /*       */
        /*     Function SkinSegment_ConfigSetup sets the values for SkinSegmentArgs.HSVThresholdsGeneric */
        /*     based on argument SkinSegmentThresholdsGenericHSV.     */
        /*  */
        /*     Within the current function, the HSV generic threshold operations are conducted by function   */
        /*     SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold. */
        /*  */
        /*         Tailored Thresholds */
        /*  */
        /*     The H and S tailored color thresholds (SkinSegmentArgs.HSThresholdsTailored) are used when */
        /*     TailoredThresholdsTF is set to true. The combination of a maximum for the H channel and a   */
        /*     minimum and a maximum for the S channel is based on Dahmani et al. (2020).  */
        /*      */
        /*     As with the tailored YCbCr thresholds, these thresholds are set based upon skin-color samples  */
        /*     collected from the input video. The process of setting the H and S tailored thresholds is   */
        /*     identical to the process of setting the tailored YCbCr thresholds.  */
        /*  */
        /*     If argument TailoredThresholdsTF is specified as true but the required number of samples has */
        /*     not been acquired, the H and S tailored thresholds will not be used. As with the tailored  */
        /*     YCbCr thresholds, the flag DontUseTailoredTF will be set to true to cause the H and S tailored  */
        /*     thresholds not to be used. */
        /*  */
        /*     Within the current function, the H and S tailored threshold operations are conducted by    */
        /*     function SkinSegmentMask_Threshold_Colors, which is called by function  */
        /*     SkinSegmentMask_Threshold. */
        /*  */
        /*     -- Low- and High-Severity Tailored Thresholds --  */
        /*  */
        /*     When TailoredThresholdsSevereTF == true, high-severity thresholds are used when conducting */
        /*     segmentation with the tailored YCbCr and HSV thresholds. High-severity thresholds are used for  */
        /*     applications where the priority is to reduce false positives (pixels incorrectly classified as */
        /*     skin) at the expense of a greater number false negatives (pixels incorrectly classified as  */
        /*     non-skin). When false, low-severity thresholds are used. Low-severity thresholds are used for  */
        /*     applications where a balance is desired between false positives and false negatives.      */
        /*  */
        /*     -- Local-Range Pixel Threshold --  */
        /*  */
        /*     The local-range pixel threshold classifies pixels based upon the homogeneity of color values */
        /*     of nearby, or local, pixels. When the local range is relatively homogeneous rather than */
        /*     heterogeneous, the value of the local range will be lower. A relatively homogeneous color  */
        /*     range of a given pixel is used as a heuristic of a pixel corresponding to skin. This is based   */
        /*     on the assumption that true skin tends to occur in regions of homogeneous color. When the  */
        /*     local range of a pixel falls below a specified threshold (SkinSegmentArgs.HThresholdTailored),  */
        /*     the pixel is classified as skin. */
        /*  */
        /*     The threshold for local range is a static value; that is, it is not set by assessment of color  */
        /*     samples. The threshold value is set by function SkinSegmentConfig_Setup. The value can only be  */
        /*     modified by adjusting the code within SkinSegmentConfig_Setup. The effectiveness of the value  */
        /*     used was established through testing.  */
        /*  */
        /*     Within the current function, the local-range pixel threshold operations are conducted by    */
        /*     function SkinSegmentMask_Threshold_Range, which is called by function  */
        /*     SkinSegmentMask_Threshold. */
        /*  */
        /*     -- Morphological Close of Patchy Regions --  */
        /*  */
        /*     Following the application of these thresholds, a two-dimensional logical matrix is assigned  */
        /*     where pixels that satisfied all thresholds are classified as true and pixels that did not are */
        /*     classified as false. A morphological close operation is then applied to the logical matrix.  */
        /*     The morphological close tends to fill in classification holes, where a hole is loosely defined  */
        /*     as a region of pixels classified as true that are enclosed by pixels classified as false.   */
        /*     Holes are filled in based on the assumption that true skin tends to be distributed in the face   */
        /*     in contiguous, rather than patchy, regions. */
        /*      */
        /*     The morphological close fills in holes only below a certain shape and size, which are    */
        /*     determined by the shape and size of the morphological structuring element, such that many  */
        /*     holes are not filled. Otherwise, large regions classified as true -- which are assumed to be  */
        /*     regions of skin -- may be erroneously filled. For a description on the choice of structuring  */
        /*     element used, see function SkinSegmentMask_MorphClose.  */
        /*  */
        /*     Within the current function, the morphological close operations are conducted by function   */
        /*     SkinSegmentMask_Threshold_MorphClose, which is called by function SkinSegmentMask_Threshold. */
        /*  */
        /*     -- Return Skin-Segmentation Mask Without Performing Colorspace Conversion -- */
        /*  */
        /*     To return a skin-segmentation mask without performing colorspace conversion, the colorspaces */
        /*     needed for skin-segmentation can be entered as input. These include YSingle, CbSingle,  */
        /*     CrSingle, HSingle, and SSingle. If all of these color channels are non-empty, colorspace */
        /*     conversion will not be performed. */
        /*  */
        /*     Additionally, IsSkinMask_Range, a skin-segmentation based upon the local range, can also be */
        /*     be entered as input.  */
        /*  */
        /*     A case where these may be entered is where skin segmentation is first run with either tailored */
        /*     thresholds on or off and it is desired to rerun the skin segmentation using tailored or non- */
        /*     tailored thresholds. In this case, the color channels and IsSkinMask_Range would have been */
        /*     assigned previously and can be reused. */
        /*  */
        /*     -- Color Channel Return Values -- */
        /*  */
        /*     The H and S channels of the HSV colorspace and the Y, Cb, and Cr channels of the YCbCr  */
        /*     colorspace are assigned during the operations of function SkinSegmentMask_Threshold. For  */
        /*     efficiency, these channels can be returned for reuse by other functions within function  */
        /*     FacePulseRate. One use of these values by another function is to periodically reset the color   */
        /*     thresholds (YCbCrThresholds_Tailored, HSThresholds_Tailored) used by the current function;   */
        /*     this is conducted by function SkinSegment_SetThresholds. To return these channels for reuse by */
        /*     other functions, the values are assigned to matrices, which are quite large due to the number  */
        /*     of pixels processed. Assignment to these large matrices may incur additional processing time.  */
        /*     To avoid this processing time when values are not to be reused, whether the channels are  */
        /*     returned can be controlled by arguments.  */
        /*  */
        /*     Argument ReturnYTF determines whether the Y channel is returned. Argument ReturnCbCrTF  */
        /*     determines whether the Cb and Cr channels are returned. Argument ReturnHSTF determines whether  */
        /*     the H and S channels are returned.     */
        /*            */
        /*  */
        /*     Notes */
        /*     ----- */
        /*  */
        /*     For detailed descriptions of the implementation of settings used in this function, see  */
        /*     function SkinSegmentConfig_Setup, which sets the settings. */
        /*  */
        /*     To view an image segmented with the skin-segmentation mask returned by this function, run the */
        /*     following code. The resulting image will be segmented in the same manner it is segmented in */
        /*     function FacePulseRate. */
        /*     SkinSegmented =        ... Segmented image */
        /*         AreaToSegment .*   ... Original image prior to segmentation */
        /*         uint8(IsSkinMask); %   Segmentation mask */
        /*  */
        /*  */
        /*     Requires */
        /*     -------- */
        /*  */
        /*         - Image Processing Toolbox (when non-compiled functions are used) */
        /*  */
        /*  */
        /*     References */
        /*     ---------- */
        /*  */
        /*     For helpful Matlab documentation on image segmentation operations, see the Matlab   */
        /*     documentation topic "image segmentation". */
        /*  */
        /*     Dahmani, D., Cheref, M., & Larabi, S. (2020). Zero-sum game theory model for segmenting skin  */
        /*     regions. Image and Vision Computing, 103925. */
        /*  */
        /*     McDuff, D., & Blackford, E. (2019, July). iphys: An open non-contact imaging-based  */
        /*     physiological measurement toolbox. In 2019 41st Annual International Conference of the IEEE  */
        /*     Engineering in Medicine and Biology Society (EMBC) (pp. 6521-6524). IEEE. */
        /*  */
        /*  */
        /*     Copyright */
        /*     --------- */
        /*  */
        /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
        /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
        /*     licensing, please contact the author. */
        /* %%%%% Code generation specifications %%%%%% */
        /* Inline function */
        /* Declare variables: */
        /*                               Upp. Bounds    Var. Size (T/F) */
        /* %%%%% Parse input arguments %%%%%% */
        /* Note: SkinSegmentMask_ParseArgs is a custom function located within folder FacePulseRate. */
        /* SkinSegmentMask_ParseArgs   Parse imput arguments to function SkinSegmentMask_Ops.  */
        /*                                                */
        /*     Helper function to function FacePulseRate.  */
        /*     Within function FacePulseRate, called by function SkinSegmentMask_Ops. */
        /*  */
        /*  */
        /*     Code generation */
        /*     --------------- */
        /*  */
        /*     Can be called as a Matlab function or used for C-language code generation.     */
        /*  */
        /*  */
        /*     Copyright */
        /*     --------- */
        /*  */
        /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
        /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
        /*     licensing, please contact the author.  */
        /* Inline function */
        /* %%%%% Local range %%%%%% */
        /*  - Structuring element width for calculating local range for a given pixel */
        /* Value assigned in function SkinSegment_ConfigSetup. */
        /*  - Individual pixel local color range threshold  */
        /* Value assigned in function SkinSegment_ConfigSetup. */
        /* Should be type uint8 for fastest evaluation.  */
        /* %%%%% Color thresholds %%%%%% */
        /*  - Individual pixel YCbCr colorspace skin-segmentation generic thresholds */
        /* Values assigned in function SkinSegment_ConfigSetup.   */
        /* Note: these should be in type single for fastest evaluation. */
        for (b_i = 0; b_i < 7; b_i++) {
          YCbCrThresholds_Generic[b_i] =
            SkinSegmentConfig->Args.YCbCrThresholdsGeneric[b_i];
        }

        emxInit_boolean_T(emlrtRootTLSGlobal, &b_IsSkinMask_Range, 2, true);

        /* Function SkinSegmentMask_Threshold_Colors will only use < and > rather than <= and >=, so these  */
        /* values are adjusted so that < and > are equivalent to <= and >=, respectively. */
        YCbCrThresholds_Generic[0] =
          SkinSegmentConfig->Args.YCbCrThresholdsGeneric[0] - 1.0F;

        /* Y min */
        YCbCrThresholds_Generic[1] =
          SkinSegmentConfig->Args.YCbCrThresholdsGeneric[1] - 1.0F;

        /* Cb min */
        /* Cr min */
        YCbCrThresholds_Generic[5] =
          SkinSegmentConfig->Args.YCbCrThresholdsGeneric[5] - 0.1F;

        /* Cb-to-Cr ratio min */
        YCbCrThresholds_Generic[2] =
          SkinSegmentConfig->Args.YCbCrThresholdsGeneric[2] + 1.0F;

        /* Cb max */
        YCbCrThresholds_Generic[4] =
          SkinSegmentConfig->Args.YCbCrThresholdsGeneric[4] + 1.0F;

        /* Cr max */
        YCbCrThresholds_Generic[3] =
          (SkinSegmentConfig->Args.YCbCrThresholdsGeneric[3] - 1.0F) + 0.1F;

        /* Cb-to-Cr ratio max */
        /*  - Individual pixel HSV colorspace skin-segmentation generic thresholds */
        /* Values assigned in function SkinSegment_ConfigSetup.   */
        /* Note: these should be in type single for fastest evaluation. */
        /* Function SkinSegmentMask_Threshold_Colors will only use < and > rather than <= and >=, so these  */
        /* values are adjusted so that < and > are equivalent to <= and >=, respectively. */
        b_HSThresholds_Generic[1] = SkinSegmentConfig->Args.HSThresholdsGeneric
          [1] - 0.1F;

        /* S min */
        b_HSThresholds_Generic[0] = SkinSegmentConfig->Args.HSThresholdsGeneric
          [0] + 0.1F;

        /* H max */
        /*  - Individual pixel YCbCr and HSV colorspaces skin-segmentation tailored thresholds */
        /* Values assigned in function SkinSegment_SetThresholds. */
        /* Note: a threshold is not used for the value (V) channel of the HSV colorspace.  */
        /* Note: these should be in type single for fastest evaluation.  */
        /*    - Low-severity tailored thresholds */
        /* YCbCr channels */
        /* H and S channels */
        /*  - Flag not to use tailored thresholds */
        /* Whether a sufficient number of skin-color samples was collected to activate tailored skin */
        /* segmentation. For details on the collection skin-color samples, see function */
        /* ROIMeans_FirstRead_CollectSkinColorSamples. */
        /* Value assigned by function SkinSegment_SetThresholds. */
        /* %%%%% Morphological close %%%%%% */
        /*  - Severity of morphological close */
        /*    - High severity of morphological close operation */
        /*    - Low severity of morphological close operation */
        /* %%%%% Number of elements in input matrices %%%%%% */
        /* Number of elements of a given matrix */
        /* Scalar; type int32. */
        NRegions_ith = ROIRegionSelected_FullFrame[3] *
          ROIRegionSelected_FullFrame[2];

        /* end function */
        /* %%%%% Apply pixel-color and pixel-color local range thresholds %%%%%% */
        /* Apply individual pixel-color and pixel-color local range thresholds to assign a skin-segmentation  */
        /* mask. */
        /* Note: SkinSegmentMask_Threshold is a custom function located within folder FacePulseRate. */
        b_IsSkinMask_Range->size[0] = 0;
        b_IsSkinMask_Range->size[1] = 0;
        b_SkinSegmentMask_Threshold(emlrtRootTLSGlobal, RUint8, GUint8, BUint8,
          b_IsSkinMask_Range, ROIRegionSelected_FullFrame[3],
          ROIRegionSelected_FullFrame[2], NRegions_ith, YCbCrThresholds_Generic,
          !SkinSegmentConfig->Args.c_SkinColorSamples_NThresholdPa,
          SkinSegmentConfig->Args.YCbCrThresholdsTailored_Sev,
          b_HSThresholds_Generic,
          SkinSegmentConfig->Args.HSThresholdsTailored_Sev,
          SkinSegmentConfig->Args.RangeSEWidth,
          SkinSegmentConfig->Args.RangeThreshold, IsSkinMask_ROISelected,
          YBounded_Single_data, RegionRGBMeans_size, CbBounded_Single_data,
          tmp_size, CrBounded_Single_data, CrBounded_Single_size,
          HBounded_Single_data, HBounded_Single_size, SBounded_Single_data,
          SBounded_Single_size);

        /* %%%%% Morphologically close skin-segmentation mask regions with patchy classifications %%%%%% */
        /* Note: SkinSegmentMask_MorphClose is a custom function located within folder FacePulseRate. */
        /* SkinSegmentMask_MorphClose    Morphologically close regions with patchy skin classification to  */
        /*                               refine the skin-segmentation mask previously assigned by comparison  */
        /*                               to thresholds. */
        /*                                                                            */
        /*     Helper function to function FacePulseRate. */
        /*     Within function FacePulseRate, called by function SkinSegmentMask_Ops. */
        /*  */
        /*  */
        /*     Code Generation */
        /*     --------------- */
        /*  */
        /*     Can be called as a Matlab function or used for C-language code generation. */
        /*  */
        /*  */
        /*     Description */
        /*     ----------- */
        /*  */
        /*     For a description of the assumptions behind the use of a morphological close to classify */
        /*     pixels as skin, see function SkinSegmentMask_Ops.   */
        /*  */
        /*     Apply a morphological close operation to the skin-segmentation mask resulting from thresholds */
        /*     previously applied (by function SkinSegmentMask_Threshold). The morphological close tends to  */
        /*     fill in classification holes, where a hole is loosely defined as a region of pixels classified  */
        /*     as true that are enclosed by pixels classified as false. The morphological close fills in  */
        /*     holes only below a specified size (specified by a morphological structuring element), such  */
        /*     that many holes are not filled.     */
        /*       */
        /*     A morphological dilation followed by a morphological erosion is conducted to perform the   */
        /*     morphological close. These operations are conducted by Matlab functions imerode and imdilate. */
        /*     Although a Matlab function is available to conduct a close (imclose), it has been observed   */
        /*     that using imerode followed by imdilate is more efficient. */
        /*  */
        /*     For a description of the choice of structuring element used in the morphological close, see  */
        /*     the description below in section "Assign structuring element".   */
        /*  */
        /*     -- Structuring Element Specifications -- */
        /*  */
        /*     - Severity == high: */
        /*  */
        /*     Use liberal dilation and erosion to mask non-skin pixels  */
        /*     Do so by using a large morphological structuring element (SE), which specifies the size of     */
        /*     dilation and erosion to carry out on each pixel (where pixel == 0). High severity may favor */
        /*     the rejection of non-skin pixels over the retention of of true-skin pixels. Function  */
        /*     FaceDetect and SkinDetect specify skin segmentation with high severity. This severity may be   */
        /*     useful for these functions because the priority in these functions is avoiding non-skin  */
        /*     pixels rather than retaining as many pixels as possible that are actually skin.     */
        /*  */
        /*     - Severity == low: */
        /*  */
        /*     Use moderate dilation and erosion to mask non-skin pixels. */
        /*     Do so by using a medium morphological structuring element (SE), which specifies the size of   */
        /*     dilation to carry out on each pixel (where pixel == 0). Compared to high severity, low  */
        /*     severity is intended to strike a balance between rejecting pixels and accepting pixels that    */
        /*     are actually skin. Function ROIMeans_TakeMeans specifies skin segmentation with low severity.  */
        /*     This low severity may be useful for the purpose of function ROIMeans_TakeMeans, which is to    */
        /*     calculate the accurate mean of an ROI. The ROIs that ROIMeans_TakeMeans processes have been  */
        /*     previously processed by functions FaceDetect and SkinDetect, which specify high severity, so  */
        /*     these ROIs may already be expected to have benefited from adjustment based upon avoidance of   */
        /*     non-skin pixels. */
        /*  */
        /*     -- Notes --  */
        /*  */
        /*     By default, Matlab's morphological operations act on true values, not false values, although */
        /*     false values (non-skin) are the target. */
        /*     */
        /*     For Matlab documentation discussing removal of patchy regions, see the Matlab documentation */
        /*     topic "Detect Cell Using Edge Detection and Morphology"  */
        /*     (https://www.mathworks.com/help/images/detecting-a-cell-using-image-segmentation.html). */
        /*  */
        /*  */
        /*     Copyright */
        /*     --------- */
        /*  */
        /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
        /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
        /*     licensing, please contact the author. */
        /* %%%%% Code-generation settings %%%%%% */
        /* Inline function */
        /* %%%%% Binary Packing %%%%%% */
        /* Note: For use as a Matlab function rather than code generation for a mex function, it is faster  */
        /* not to pack the logical matrix. */
        /* Pack logical image for increased performance of morphological functions  */
        bwpack(IsSkinMask_ROISelected, IsSkinMask_PixelColorPacked);

        /* %%%%% Assign structuring element %%%%%% */
        /* Because structuring element objects are compile-time constants, a fixed number of structuring   */
        /* element objects are made available, each of which has a corresponding function. The function   */
        /* with the structuring element closest in size to the specified structuring element size is used.   */
        /* Select function from available functions */
        /* Select the function with the SE width most similar to the specified SE width. */
        /* Local function. */
        /* Scalar; type int16. */
        /* end main function */
        /* ============================================================================================= */
        /* Local functions  */
        /* ============================================================================================= */
        /* ============================================================================================= */
        /* SelectFunction    Select the function with the SE width most similar to  */
        /*                   MorphCloseNeighborhoodWidth.    */
        /*  */
        /*     Description: */
        /*  */
        /*     Select the size of the structuring element to use. The size is partly determined according to */
        /*     MorphCloseSevereTF.  */
        /* Inline function */
        /* %%%%% High severity %%%%%% */
        /* Scalars; type int16. */
        if ((int16_T)(12 - SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned)
            < 0) {
          Diff12 = (int16_T)
            (SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned - 12);
        } else {
          Diff12 = (int16_T)(12 -
                             SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned);
        }

        if ((int16_T)(22 - SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned)
            < 0) {
          Diff22 = (int16_T)
            (SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned - 22);
        } else {
          Diff22 = (int16_T)(22 -
                             SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned);
        }

        if ((int16_T)(32 - SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned)
            < 0) {
          Diff32 = (int16_T)
            (SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned - 32);
        } else {
          Diff32 = (int16_T)(32 -
                             SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned);
        }

        emxFree_boolean_T(&b_IsSkinMask_Range);
        emxFree_uint8_T(&BUint8);
        emxFree_uint8_T(&GUint8);
        emxFree_uint8_T(&RUint8);
        if (Diff12 < Diff22) {
          functionWidthToUse = 12;
          Diff22 = Diff12;
        } else {
          functionWidthToUse = 22;
        }

        if (Diff32 < Diff22) {
          functionWidthToUse = 32;
          Diff22 = Diff32;
        }

        if ((int16_T)(50 - SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned)
            < 0) {
          b_i = (int16_T)(SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned -
                          50);
        } else {
          b_i = (int16_T)(50 -
                          SkinSegmentConfig->Args.MorphCloseSELargeWidth_Tuned);
        }

        if (b_i < Diff22) {
          functionWidthToUse = 50;
        }

        /* Note: Use this pattern for adding additional SEs */
        /*     %{ */
        /*     if DiffX < Diff */
        /*  */
        /*         functionWidthToUse = int16(X); */
        /*      */
        /*         Diff = DiffX; %include this line if this is not the last condition */
        /*     end */
        /*     %} */
        /* %%%%% Low severity %%%%%% */
        /* %%%%% Erosion followed by dilation %%%%%% */
        /* Cast to type double for use by function imerode */
        /* Scalar; type double. */
        /* %%%%% --- High severity erosion and dilation %%%%%%  */
        /* Use function corresponding to closest SE width */
        switch (functionWidthToUse) {
         case 12:
          /* Square structuring element with width of 12 pixels     */
          /* Packed binary image */
          /* Local function. */
          /* Type uint32. */
          /* end local function */
          /* ============================================================================================= */
          /* ErodeAndDilate_SESquare12    Erode and dilate with square structuring element of width 12. */
          /* Inline function */
          /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
          /* Type uint32. */
          /*  eroded logical image */
          /*  logical image */
          /*  structuring element */
          /*  flag for packed image */
          /*  number of rows in unpacked image */
          imerode(IsSkinMask_PixelColorPacked, ROIRegionSelected_FullFrame[3],
                  c_IsSkinMask_PixelColor_ErodePa);

          /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
          /* Type uint32. */
          /*  dilated logical image */
          /*  structuring element */
          /*  flag for packed image */
          imdilate(c_IsSkinMask_PixelColor_ErodePa, IsSkinMask_PixelColorPacked);

          /* Square structuring element with width of 22 pixels     */
          /* %%%%% --- Low severity erosion and dilation %%%%%%    */
          /* %%%%% --- Unpack %%%%%%    */
          /* Unpack packed binary image */
          /* M x N matrix; type logical. */
          bwunpack(IsSkinMask_PixelColorPacked, ROIRegionSelected_FullFrame[3],
                   IsSkinMask_ROISelected);
          break;

         case 22:
          /* Packed binary image */
          /* Local function. */
          /* Type uint32. */
          /* end local function */
          /* ============================================================================================= */
          /* ErodeAndDilate_SESquare22    Erode and dilate with square structuring element of width 22. */
          /* Inline function */
          /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
          /* Type uint32. */
          /*  eroded logical image */
          /*  logical image */
          /*  structuring element */
          /*  flag for packed image */
          /*  number of rows in unpacked image */
          b_imerode(IsSkinMask_PixelColorPacked, ROIRegionSelected_FullFrame[3],
                    c_IsSkinMask_PixelColor_ErodePa);

          /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
          /* Type uint32. */
          /*  dilated logical image */
          /*  structuring element */
          /*  flag for packed image */
          b_imdilate(c_IsSkinMask_PixelColor_ErodePa,
                     IsSkinMask_PixelColorPacked);

          /* Square structuring element with width of 32 pixels     */
          /* %%%%% --- Low severity erosion and dilation %%%%%%    */
          /* %%%%% --- Unpack %%%%%%    */
          /* Unpack packed binary image */
          /* M x N matrix; type logical. */
          bwunpack(IsSkinMask_PixelColorPacked, ROIRegionSelected_FullFrame[3],
                   IsSkinMask_ROISelected);
          break;

         case 32:
          /* Packed binary image */
          /* Local function. */
          /* Type uint32. */
          /* end local function */
          /* ============================================================================================= */
          /* ErodeAndDilate_SESquare32    Erode and dilate with square structuring element of width 32. */
          /* Inline function */
          /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
          /* Type uint32. */
          /*  eroded logical image */
          /*  logical image */
          /*  structuring element */
          /*  flag for packed image */
          /*  number of rows in unpacked image */
          c_imerode(IsSkinMask_PixelColorPacked, ROIRegionSelected_FullFrame[3],
                    c_IsSkinMask_PixelColor_ErodePa);

          /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
          /* Type uint32. */
          /*  dilated logical image */
          /*  structuring element */
          /*  flag for packed image */
          c_imdilate(c_IsSkinMask_PixelColor_ErodePa,
                     IsSkinMask_PixelColorPacked);

          /* Square structuring element with width of 50 pixels     */
          /* %%%%% --- Low severity erosion and dilation %%%%%%    */
          /* %%%%% --- Unpack %%%%%%    */
          /* Unpack packed binary image */
          /* M x N matrix; type logical. */
          bwunpack(IsSkinMask_PixelColorPacked, ROIRegionSelected_FullFrame[3],
                   IsSkinMask_ROISelected);
          break;

         case 50:
          /* Packed binary image */
          /* Local function. */
          /* Type uint32. */
          /* end local function */
          /* ============================================================================================= */
          /* ErodeAndDilate_SESquare50    Erode and dilate with square structuring element of width 50. */
          /* Inline function */
          /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
          /* Type uint32. */
          /*  eroded packed logical image */
          /*  packed logical image */
          /*  structuring element */
          /*  flag for packed image */
          /*  number of rows in unpacked image */
          d_imerode(IsSkinMask_PixelColorPacked, ROIRegionSelected_FullFrame[3],
                    c_IsSkinMask_PixelColor_ErodePa);

          /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
          /* Type uint32. */
          /*  dilated packed logical image */
          /*  packed logical image */
          /*  structuring element */
          /*  flag for packed image */
          d_imdilate(c_IsSkinMask_PixelColor_ErodePa,
                     IsSkinMask_PixelColorPacked);

          /* (Required for code generation)     */
          /* %%%%% --- Low severity erosion and dilation %%%%%%    */
          /* %%%%% --- Unpack %%%%%%    */
          /* Unpack packed binary image */
          /* M x N matrix; type logical. */
          bwunpack(IsSkinMask_PixelColorPacked, ROIRegionSelected_FullFrame[3],
                   IsSkinMask_ROISelected);
          break;
        }

        /* %%%%% Count the number of pixels classified as skin (true) %%%%%% */
        /* If returning a count of the pixels classified as true is enabled */
        b_TrueCount_data[0] = 0U;
        for (c_i = 0; c_i < NRegions_ith; c_i++) {
          if (IsSkinMask_ROISelected->data[c_i]) {
            for (b_i = 0; b_i < 1; b_i++) {
              b_TrueCount_data[0]++;
            }
          }
        }

        /* end function */
        /* ============================================================================================= */
        /* Code-generation and build script */
        /* ============================================================================================= */
        /* Code-generation and build script used to generate C-language code and create the compiled version  */
        /* (SkinSegmentMask_Ops_mex) of the function. */
        /* { */
        /*  */
        /* %%%%% Modify function files for performance %%%%%% */
        /*  */
        /* Before running code generation, input validation was removed from the files for the  */
        /* following functions: */
        /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\bwpack.m */
        /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\bwunpack.m */
        /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\+images\+internal\+coder\morphop.m  */
        /*  */
        /* Specifically, in these files, the following validation functions were commented out: */
        /*  - narginchk */
        /*  - validateattributes */
        /*  */
        /* Note: Seperate files for these functions with these changes could not be made because code   */
        /* generation for these functions expects specific file names. Hence, after code generation, the   */
        /* input validation was added back to the files. */
        /* Note: as these files are located in 'Program Files', admin access is required to edit them. */
        /*  */
        /*  */
        /* %%%%% Specify variable-size input arguments %%%%%% */
        /*  */
        /* See Matlab documentation for coder.typeof. */
        /*  */
        /*                                              Example Code                 Upp. Bounds  Var. Size (T/F)  Type */
        /* RUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8 */
        /* GUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8 */
        /* BUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8 */
        /* YSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single                       */
        /* CbSingleCode                  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single */
        /* CrSingleCode                  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single */
        /* HSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single                                  */
        /* SSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single  */
        /* IsSkinMask_RangeCode          = coder.typeof( false(500, 500),             [inf, inf],  [1, 1] );        %logical            */
        /*                   */
        /*                      */
        /* %%%%% Specify fixed-size input arguments %%%%%% */
        /*  */
        /* NRows_MatrixCode               = int32(0); */
        /* NCols_MatrixCode               = int32(0); */
        /* CountTrueTFCode                = false; */
        /* TailoredThresholdsTFCode       = false; */
        /* ReturnYTFCode                  = false; */
        /* ReturnCbCrTFCode               = false; */
        /* ReturnHSTFCode                 = false; */
        /* TailoredThresholdsSevereTFCode = false; */
        /* MorphCloseSevereTFCode         = false; */
        /* XOffsetCode                    = int32(0); */
        /* YOffsetCode                    = int32(0); */
        /*  */
        /* Struct with fixed-size fields */
        /* Note: the order and names of fields are compile-time constants. */
        /*  */
        /* SkinSegmentArgsCode = ...                                                                                               */
        /*     struct( ... */
        /*         'SkinColorSamples_NThresholdPassedTF', false, ... */
        /*         'YCbCrThresholdsGeneric', zeros(1, 7, 'single'), ... */
        /*         'HSThresholdsGeneric', zeros(1, 2, 'single'), ... */
        /*         'YCbCrThresholdsTailored', zeros(1, 8, 'single'), ... */
        /*         'YCbCrThresholdsTailored_Sev', zeros(1, 8, 'single'), ... */
        /*         'HSThresholdsTailored', zeros(1, 3, 'single'), ... */
        /*         'HSThresholdsTailored_Sev', zeros(1, 3, 'single'), ... */
        /*         'RangeSEWidth', int16(0), ... */
        /*         'RangeThreshold', uint8(0), ... */
        /*         'MorphCloseSEMediumWidth_Tuned', int16(0), ... */
        /*         'MorphCloseSELargeWidth_Tuned', int16(0) ...    */
        /*     );                                                                    */
        /*  */
        /*  */
        /* %%%%% Set configurations to increase performance %%%%%% */
        /*  */
        /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
        /* "Optimization Strategies" */
        /*  */
        /* cfg = coder.config('mex'); */
        /* cfg.GlobalDataSyncMethod = 'NoSync'; */
        /* cfg.ConstantInputs = 'IgnoreValues'; */
        /* cfg.ExtrinsicCalls = false;  */
        /* cfg.SaturateOnIntegerOverflow = false; */
        /* cfg.IntegrityChecks = false; */
        /* cfg.ResponsivenessChecks = false; */
        /*  */
        /*  */
        /* %%%%% Specify flags to minGW compiler to optimize execution speed %%%%%% */
        /*  */
        /* For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html */
        /*  */
        /* The flags are specified as part of the code-generation configuration object. A custom function, */
        /* setbuildargs, is used to specify these flags. For details on the function implementation, see the  */
        /* function file, which is located within folder FacePulseRate. This custom function is based upon  */
        /* Matlab guidance found in */
        /* https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function */
        /*  */
        /* setbuildargs will be evaluated from text within the code-generation object, so it is converted to  */
        /* a character vector prior to execution of the codegen command. */
        /*  */
        /* %%%%% --- Specify the flags as arguments to function setbuildargs %%%%%% */
        /*  */
        /* Argument buildInfo: this variable is assign by the caller (the codegen command executed  */
        /* below) and is not present in the base workspace. */
        /*  */
        /* Second argument: specify a cell array of compiler-specific flags, where each flag is a  */
        /* character vector. As function setbuildargs will be evaluated from text, use double ' quotes for  */
        /* each character vector to maintain the charater vector, */
        /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
        /*  */
        /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})'; */
        /*  */
        /* Assign to code-generation configuration object */
        /* cfg.PostCodeGenCommand = setbuildargsAsText; */
        /*  */
        /*  */
        /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
        /*  */
        /* codegen SkinSegmentMask_Ops.m -report -config cfg -args {RUint8Code, GUint8Code, BUint8Code, YSingleCode, CbSingleCode, CrSingleCode, HSingleCode, SSingleCode, IsSkinMask_RangeCode, NRows_MatrixCode, NCols_MatrixCode, CountTrueTFCode, TailoredThresholdsTFCode, ReturnYTFCode, ReturnCbCrTFCode, ReturnHSTFCode, TailoredThresholdsSevereTFCode, MorphCloseSevereTFCode, XOffsetCode, YOffsetCode, SkinSegmentArgsCode} */
        /*               */
        /* } */
        /* end function */
        /* %%%%% --- Determine the number of pixels classified as skin %%%%%% */
        /* %%%%% >>>>>> Refine classification with the skin-detection algorithm %%%%%% */
        /* Apply thresholds from the skin-detection algorithm to refine the skin-segmentation mask. */
        /* Return the number of pixels present after this refinement. */
        /* If refinement of the skin-segmentation mask by the skin-detection algorithm is enabled */
        /* Number of pixels classified as skin  */
        /* Scalar; type single. */
        /* %%%%% Determine whether ROI contains skin %%%%%% */
        /* %%%%% --- Determine proportion of ROI classified as skin %%%%%% */
        /* Determine the proportion of pixels classified as skin out of all pixels of the ROI. */
        /* Cast to a floating-point type to permit decimal. */
        /* Scalar; type single. */
        /* Note: NRows_Matrix and NCols_Matrix are type int32. */
        ThresholdRGBProb = (real32_T)(ROIRegionSelected_FullFrame[3] *
          ROIRegionSelected_FullFrame[2]);

        /* %%%%% --- Specify minimum-proportion threshold to apply %%%%%% */
        /* Specify the minimum proportion of pixels classified as skin to use as the threshold. If the  */
        /* proportion of pixels is above this threshold, the ROI will be considered valid. */
        /* Specify the thresholds according to the detection algorithm by which the ROI was returned or the   */
        /* stage of ROI processing the ROI has undergone. The thresholds are set by function  */
        /* SkinSegment_ConfigSetup. For details on the thresholds used for each case, see function */
        /* SkinSegment_ConfigSetup. */
        /* ROI after all modifications when means are taken for pulse-rate purposes (see function  */
        /* ROIMeans_TakeMeans)     */
        /* %%%%% --- Make determination on whether the ROI is valid %%%%%% */
        /* Consider the ROI valid if the proportion of pixels classified as skin exceeds the specified  */
        /* threshold. */
        /* If the proportion exceeds the threshold */
        TrueCount_data[0] = ((real32_T)b_TrueCount_data[0] / ThresholdRGBProb >
                             SkinSegmentConfig->ConfirmSkin.ProportionThresholdSkin);
        if (ifWhileCond(TrueCount_data)) {
          /* Scalar; type logical. */
          CompletelyContainedTF = true;
        } else {
          CompletelyContainedTF = false;
        }

        /* %%%%% Assign output arguments %%%%%% */
        /* If condition 1 */
        /*  Determination on whether the ROI is valid; scalar, type logical */
        /*  The proportion of skin on which the determination was made; scalar, */
        /*  type single. */
        /*  The following variables were assigned for the skin-segmentation operations; they are */
        /*  returned so that other functions can reuse this information: */
        /*  Skin-segmentation mask; M x N matrix, type logical */
        /*  ImageToInspect in YCbCr colorspace; M x N matrices, type single */
        /*  H channel of ImageToInspect in HSV colorspace; M x N matrix, type */
        /*  single. */
        /*  S channel of ImageToInspect in HSV colorspace; M x N matrix, type */
        /*  single. */
        /*    Skin-segmentation mask based only on local range; M x N matrix,  */
        /*    type logical. */
        /* end function */
      }

      /* %%%%% Assign selected ROI %%%%%% */
      /* If a sufficient number of pixels within the ROI are classified as skin */
      if (CompletelyContainedTF) {
        /* Note: if this point is reached, the ith frame contains a skin-detection ROI considered to be */
        /* successful. */
        /* Indicate that the ROI passed the threshold applied by function ConfirmSkinPresent */
        /* Note: this value will be the opposite of value SkinColorTF. If true, then SkinTF_ith will be  */
        /* false. However, SkinTF_ith can be false without HasROITF_SkinNotPresent_ith being true.     */
        *HasROITF_SkinNotPresent_ith = false;

        /* Assign successful detection status */
        *SkinTF_ith = true;

        /* Assign selected ROI */
        /* 1 x 4 row vector; type int16. */
        ROI_Selected_ith_size[0] = 1;
        ROI_Selected_ith_size[1] = 4;
        ROI_Selected_ith_data[0] = ROIRegionSelected_FullFrame[0];
        ROI_Selected_ith_data[1] = ROIRegionSelected_FullFrame[1];
        ROI_Selected_ith_data[2] = ROIRegionSelected_FullFrame[2];
        ROI_Selected_ith_data[3] = ROIRegionSelected_FullFrame[3];

        /* If the proportion of pixels classified as skin was below the specified threshold */
      } else {
        /* Indicate that the ROI did not pass the threshold applied by function ConfirmSkinPresent     */
        /* Note: this value will be the opposite of value SkinColorTF. If true, then SkinTF_ith will be  */
        /* false. However, SkinTF_ith can be false without HasROITF_SkinNotPresent_ith being true.  */
        /* and SkinTF_ith. */
        *HasROITF_SkinNotPresent_ith = true;

        /* Assign unsuccessful detection status */
        /* Assign empty value for selected ROI */
        ROI_Selected_ith_size[0] = 0;
        ROI_Selected_ith_size[1] = 4;
      }

      /* end function */
      RegionSelectedLinIdx_size[0] = 1;
      RegionSelectedLinIdx_size[1] = 1;
      RegionSelectedLinIdx_data[0] = Counter_True;

      /* If the proportion of pixels classified as skin was below the specified threshold        */
      if (*HasROITF_SkinNotPresent_ith) {
        /* Record status */
        ROIDiagnostic_ROISkin_ith->ProportionSkinPixelsTooLow = true;

        /* Initialize fields in struct ROIDiagnostic_ROISkin_ith: */
        /* Local function. */
        b_cast(ROIDiagnostic_ROISkin_ith, &b_ROIDiagnostic_ROISkin_ith);

        /* end local function */
        /* ============================================================================================= */
        /* ROIDiagnosticInitialize   Assign uninitialized values for ROIDiagnostic_ROISkin_ith.     */
        /*  */
        /*     Description: */
        /*  */
        /*     If the compiled version of function SkinDetect is being used, all fields in struct    */
        /*     ROIDiagnostic_ROISkin_ith must be initialized because the struct was preallocated by a call to   */
        /*     function nullcopy. The variables must be initialized because nullcopy preallocates but does */
        /*     not initialize. The fields are initialized by the current function. They are initialied here  */
        /*     because certain fields, depending on EntryFlag, will not be initialized by function  */
        /*     SkinDetect_RecordDiagnosticData.     */
        /*  */
        /*     Note: if the Matlab version of function SkinDetect is being used, function nullcopy has no    */
        /*     effect and variables are always initialized; hence, assignment here is not necessary.    */
        /* Inline function */
        b_ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo.size[0] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo.size[1] = 0;
        b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.size[0] = 1;
        b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.size[1] = 2;
        b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.data[0] = 0U;
        b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.data[1] = 0U;

        /*  'NoRegions' */
        /*    'ProportionSkinPixelsTooLow' */
        b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx->size[0] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx->size[1] = 0;
        b_ROIDiagnostic_ROISkin_ith.c_RegionBoundaries_CandidateLin->size[0] = 0;
        b_ROIDiagnostic_ROISkin_ith.c_RegionBoundaries_CandidateLin->size[1] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx->size[0] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx->size[1] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedRGBProb.size[0] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedRGBProb.size[1] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateRGBProb.size[0] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateRGBProb.size[1] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedRGBProb.size[0] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedRGBProb.size[1] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ.size[0] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ.size[1] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateYCbCrZ.size[0] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateYCbCrZ.size[1] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedYCbCrZ.size[0] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedYCbCrZ.size[1] = 0;
        b_ROIDiagnostic_ROISkin_ith.c_RegionCrSDScores_RejectedCrSD.size[0] = 0;
        b_ROIDiagnostic_ROISkin_ith.c_RegionCrSDScores_RejectedCrSD.size[1] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSD.size[0] = 0;
        b_ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSD.size[1] = 0;

        /* end local function */
        /* ============================================================================================= */
        /* Code-generation and build script */
        /* ============================================================================================= */
        /* Code-generation and build script used to generate C-language code and create the compiled version  */
        /* (SkinDetect_mex) of the function. */
        /* { */
        /*  */
        /* %%%%% Specify variable-size input arguments %%%%%% */
        /*  */
        /* See Matlab documentation for coder.typeof. */
        /*                                                                   */
        /*                                             Example Code                    Upp. Bounds       Var. Size (T/F)    Type */
        /* VidFrameCode                 = coder.typeof( zeros(500, 500, 3, 'uint8'),    [inf, inf, 3],    [1, 1, 0] );       %uint8  */
        /* ROI_SRCode                   = coder.typeof( zeros(1, 4, 'int16'),           [1, 4],           [1, 0] );          %int16 */
        /* FramesToProcessLinIdx_SRCode = coder.typeof( zeros(1, 500, 'int32'),         [1, inf],         [0, 1] );          %uint32  */
        /*           */
        /*        */
        /* %%%%% Specify fixed-size input arguments %%%%%% */
        /*  */
        /* iCode                                             = int32(0); */
        /* BoundingBoxSkinCode                               = zeros(1, 4, 'int16'); */
        /* ROIForBoundingBoxSkin_FRCode                      = zeros(1, 4, 'int16'); */
        /* VideoReadConfig_VidObjWidthCode                   = int16(0); */
        /* VideoReadConfig_VidObjHeightCode                  = int16(0); */
        /* OutputConfig_WriteVideoShowROISkinDiagnosisTFCode = false; */
        /* FirstReadSkinTFCode                               = false; */
        /* Notifications_Interval_SRCode                     = int32(0); */
        /* Notifications_LoopStartTime_SRCode                = uint64(0);  */
        /* Notifications_LoopCounter_SRCode                  = int32(0);                 */
        /*  */
        /* Note: the number, names, and order of struct fields are compile-time constants. */
        /*  */
        /* %%%%% --- ROIGeneralConfigCode struct %%%%%% */
        /*  */
        /*                         Example Code              Upp. Bounds    Var. Size (T/F)   Type */
        /* Element1 = coder.typeof( zeros(10, 5, 'double'),   [inf, 5],      [1, 0] );         %double */
        /*  */
        /* Element2 = coder.typeof( zeros(10, 1, 'double'),   [inf, 1],      [1, 0] );         %double */
        /*  */
        /* ROIGeneralConfigCode = ... */
        /*     struct( ... */
        /*         'ROIMinWidthProportion',                      double(0), ...                           */
        /*         'ROIMinHeightProportion',                     double(0), ...  */
        /*         'ROIWidthResizeFactor',                       double(0), ... */
        /*         'ROIHeightResizeFactor',                      double(0), ...             */
        /*         'ROIFinalSmoothingWindows',                   zeros(1, 2, 'int32'), ... */
        /*         'ROISkipFrameThreshold_adjusted',             int32(0), ... */
        /*         'ROIMSIR_DiffMaxDetection',                   int16(0), ... */
        /*         'ROIMSIR_DiffMaxAdjacent',                    int16(0), ... */
        /*         'ROIMSIR_FirstFrameIdx',                      int32(0), ... */
        /*         'FrameCacheMaxFrames',                        int32(0), ... */
        /*         'ROIMeansOperationsReadyFirstReadTF',         false, ... */
        /*         'ROIMeansMaxFrameToProcessSecondReadLinIdx',  int32(0), ... */
        /*         'ROISpecifyByArgument',                       Element1, ... */
        /*         'ROIIgnoreByArgument',                        Element2, ... */
        /*         'RecursiveTF',                                false, ... */
        /*         'ReturnAllTF',                                false, ... */
        /*         'UseCompiledFunctionsTF',                     false ... */
        /*     ); */
        /*  */
        /* %%%%% --- SkinSegmentConfig struct %%%%%%  */
        /*  */
        /* SkinSegmentConfigCode = ... */
        /*     struct( ... */
        /*         'SkinSegmentTF', false, ... Whether skin segmentation enabled */
        /*         'SkinSegmentSeverityFactor', double(0), ... For tuning severity of skin segmentation */
        /*         'MorphCloseSEMediumWidth', double(0), ... Width of structuring element for medium  */
        /*                                               ... morphological close before tuning. */
        /*         'MorphCloseSELargeWidth', double(0), ... Width of structuring element for large  */
        /*                                              ... morphological close before tuning.         */
        /*         'UseCompiledFunctionsTF', false, ... Whether to use compiled functions         */
        /*         'Args', ... Arguments to fuction SkinSegmentMask  */
        /*         struct( ... */
        /*             'SkinColorSamples_NThresholdPassedTF', false, ... */
        /*             'YCbCrThresholdsGeneric', zeros(1, 7, 'single'), ... */
        /*             'HSThresholdsGeneric', zeros(1, 2, 'single'), ... */
        /*             'YCbCrThresholdsTailored', zeros(1, 8, 'single'), ... */
        /*             'YCbCrThresholdsTailored_Sev', zeros(1, 8, 'single'), ... */
        /*             'HSThresholdsTailored', zeros(1, 3, 'single'), ... */
        /*             'HSThresholdsTailored_Sev', zeros(1, 3, 'single'), ... */
        /*             'RangeSEWidth', int16(0), ... */
        /*             'RangeThreshold', uint8(0), ... */
        /*             'MorphCloseSEMediumWidth_Tuned', int16(0), ... */
        /*             'MorphCloseSELargeWidth_Tuned', int16(0) ... */
        /*         ), ...  */
        /*         'TailoredData', ... Tailored skin-segmentation settings */
        /*         struct( ... */
        /*             ... Properties determining whether SkinSegment_SetThresholds will be called in function */
        /*             ... ROIMeans_FirstRead: */
        /*             'OpsReadyTF', false, ... */
        /*             'RecentThresholdOpsFrameIdx', int32(0), ... */
        /*             'ThresholdOpsInterval', int32(0), ... */
        /*             'ThresholdOpsRunCurrentFrameTF', false, ... */
        /*             ... Arguments to function SkinSegment_SetThresholds, which sets thresholds for the */
        /*             ... "tailored" option used by function SkinSegmentMask: */
        /*             'SkinColorSamples_NThreshold', double(0), ... */
        /*             'RangePercentile_YCbCrH', zeros(1, 2, 'double'), ... */
        /*             'RangePercentile_S', zeros(1, 2, 'double'), ... */
        /*             'SkinColorSamples_HighNThreshold', double(0), ... */
        /*             'SkinColorSamples_HighNThresholdPassedTF', false, ... */
        /*             'RangePercentileHighN_YCbCrH', zeros(1, 2, 'double'), ... */
        /*             'RangePercentileHighN_S', zeros(1, 2, 'double'), ... */
        /*             'RangePercentileSev_YCbCrH', zeros(1, 2, 'double'), ... */
        /*             'RangePercentileSev_S', zeros(1, 2, 'double') ... */
        /*         ), ... */
        /*         ... Values used by function ConfirmSkinPresent depending on the argument  */
        /*         ... PixelColorThresholdsType: */
        /*         'ConfirmSkin', ...  */
        /*         struct( ... */
        /*             'ProportionThresholdPrimary',    single(0), ... */
        /*             'ProportionThresholdSecondary1', single(0), ... */
        /*             'ProportionThresholdSecondary2', single(0), ... */
        /*             'ProportionThresholdSkin',       single(0), ... */
        /*             'ProportionThresholdMeans',      single(0)  ... */
        /*         ), ... */
        /*         'OverSegmentedCheck', ... */
        /*         struct( ... */
        /*             'CheckTF',                          false, ... */
        /*             'ProportionThresholdPrimary',       single(0), ... */
        /*             'ProportionThresholdSecondary1',    single(0), ... */
        /*             'ProportionThresholdSecondary2',    single(0), ... */
        /*             'FramesLowSkinProportionThreshold', double(0), ... */
        /*             'NFramesLowSkinProportionStatus',   double(0), ... */
        /*             'MorphReductionAmount',             double(0), ... */
        /*             'NMorphReductionLimit',             int32(0), ... */
        /*             'NMorphReductions',                 int32(0), ... */
        /*             'DarknessThreshold',                single(0), ... */
        /*             'BelowDarknessThresholdTF',         false, ... */
        /*             'NFramesYSingleMean',               single(0), ... */
        /*             'PixelColorsAdjustedTF',            false, ... */
        /*             'ColorThresAdjustTo',               zeros(1, 9, 'single') ...                */
        /*         ) ... */
        /*     );        */
        /*  */
        /* %%%%% --- SkinDetectConfig struct %%%%%% */
        /*  */
        /* SkinDetectConfigCode = ...  */
        /*     struct( ... */
        /*         'ROISkinTF', false, ... */
        /*         'Thresholds', ... */
        /*         struct( ...    */
        /*             'SetTF', false, ... */
        /*             'SkinColorSamples_NThreshold', double(0), ... */
        /*             'SkinColorSamples_NThresholdPassedTF', false, ... */
        /*             'SkinColorSamples_HighNThreshold', double(0), ...  */
        /*             'SkinColorSamples_HighNThresholdPassedTF', false, ... */
        /*             'SkinColorSamples_HighNThresholdIdx', int32(0), ...  */
        /*             'ColorThreshold', zeros(1, 3, 'single'), ... */
        /*             'ColorThresholdHighN', zeros(1, 3, 'single'), ... */
        /*             'RecentThresholdOpsFrameIdx', int32(0), ... */
        /*             'ThresholdOpsInterval', int32(0), ... */
        /*             'ThresholdOpsRunCurrentFrameTF', false, ... */
        /*             'ColorSDThreshold', single(0), ... */
        /*             'RGBProbTheta', zeros(4, 1, 'double'), ... */
        /*             'YCbCrMeanOfMeans', zeros(1, 3, 'single'), ... */
        /*             'YCbCrStdDevOfMeans', zeros(1, 3, 'single'), ... */
        /*             'RegionNThreshold', single(0) ... */
        /*         ), ... */
        /*         'ROISkinSkipFrameThreshold', int32(0), ... */
        /*         'ROISkin_BoundingBoxGrowthThreshold', int32(0), ... */
        /*         'ROISkin_BoundingBoxGrowthFactor', double(0), ... */
        /*         'ROISkin_InitialBoundingBoxScale', double(0), ... */
        /*         'ROISkinRegionMinSizeFactor', single(0), ... */
        /*         'ROISkinRegionProximityWeight', double(0), ... */
        /*         'ROISkinSmoothingWindow', double(0), ... */
        /*         'PartitionColInterval', int16(0), ... */
        /*         'PartitionRowInterval', int16(0), ... */
        /*         'SkinDetectionReadyTF', false, ... */
        /*         'ROISkin_BoundingBoxEnlargementFactor', double(0), ... */
        /*         'ROISkinSkipFrameThreshold_adjusted', int32(0), ... */
        /*         'UseCompiledFunctionsTF', false ... */
        /*     ); */
        /*  */
        /*  */
        /* %%%%% Set configurations to increase performance %%%%%% */
        /*  */
        /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
        /* "Optimization Strategies" */
        /*  */
        /* cfg = coder.config('mex'); */
        /* cfg.GlobalDataSyncMethod = 'NoSync'; */
        /* cfg.ConstantInputs = 'IgnoreValues'; */
        /* cfg.ExtrinsicCalls = true; %true to permit display of errors */
        /* cfg.SaturateOnIntegerOverflow = false; */
        /* cfg.IntegrityChecks = false; */
        /* cfg.ResponsivenessChecks = false; */
        /*  */
        /*  */
        /* %%%%% Specify flags to minGW compiler to optimize execution speed %%%%%% */
        /*  */
        /* For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html */
        /*  */
        /* The flags are specified as part of the code-generation configuration object. A custom function, */
        /* setbuildargs, is used to specify these flags. For details on the function implementation, see the  */
        /* function file, which is located within folder FacePulseRate. This custom function is based upon  */
        /* Matlab guidance found in */
        /* https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function */
        /*  */
        /* setbuildargs will be evaluated from text within the code-generation object, so it is converted to  */
        /* a character vector prior to execution of the codegen command. */
        /*  */
        /* %%%%% --- Specify the flags as arguments to function setbuildargs %%%%%% */
        /*  */
        /* Argument buildInfo: this variable is assign by the caller (the codegen command executed  */
        /* below) and is not present in the base workspace. */
        /*  */
        /* Second argument: specify a cell array of compiler-specific flags, where each flag is a  */
        /* character vector. As function setbuildargs will be evaluated from text, use double ' quotes for  */
        /* each character vector to maintain the charater vector, */
        /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
        /*  */
        /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})'; */
        /*  */
        /* Assign to code-generation configuration object */
        /* cfg.PostCodeGenCommand = setbuildargsAsText; */
        /*  */
        /*  */
        /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
        /*  */
        /* codegen SkinDetect.m -report -config cfg -args {iCode, VidFrameCode, VideoReadConfig_VidObjWidthCode, VideoReadConfig_VidObjHeightCode, SkinSegmentConfigCode, ROIGeneralConfigCode, SkinDetectConfigCode, OutputConfig_WriteVideoShowROISkinDiagnosisTFCode, BoundingBoxSkinCode, FirstReadSkinTFCode, ROIForBoundingBoxSkin_FRCode, ROI_SRCode, FramesToProcessLinIdx_SRCode, Notifications_Interval_SRCode, Notifications_LoopStartTime_SRCode, Notifications_LoopCounter_SRCode} */
        /*                  */
        /* } */
        c_cast(&b_ROIDiagnostic_ROISkin_ith, ROIDiagnostic_ROISkin_ith);
      } else {
        /* Record status         */
        /* Note: If the compiled version of function SkinDetect is being used, the variable below   */
        /* must be initialized because the variable was preallocated by a call to function   */
        /* nullcopy. The variable must be initialized because nullcopy preallocates but does not */
        /* initialize. The variable is initialized by the assignment below. Note that if the   */
        /* Matlab version of function SkinDetect is being used, function nullcopy has no effect   */
        /* and variables are always initialized; hence, the assignment below is not necessary.   */
        ROIDiagnostic_ROISkin_ith->ProportionSkinPixelsTooLow = false;
      }

      /* No regions passed the rejection thresholds or a centroid was not able to be calculated for any */
      /* region.  */
      /* Note: this should be relatively uncommon. */
    } else {
      /* Assign false, zero, or empty values for use in function SkinDetect_RecordDiagnosticData */
      /* For code generation purposes, specify the corresponding types.                */
      ROIPredicted_CenterX = 0;
      ROIPredicted_CenterY = 0;

      /* Initialize fields in struct ROIDiagnostic_ROISkin_ith: */
      /* Local function. */
      b_cast(ROIDiagnostic_ROISkin_ith, &b_ROIDiagnostic_ROISkin_ith);

      /* end local function */
      /* ============================================================================================= */
      /* ROIDiagnosticInitialize   Assign uninitialized values for ROIDiagnostic_ROISkin_ith.     */
      /*  */
      /*     Description: */
      /*  */
      /*     If the compiled version of function SkinDetect is being used, all fields in struct    */
      /*     ROIDiagnostic_ROISkin_ith must be initialized because the struct was preallocated by a call to   */
      /*     function nullcopy. The variables must be initialized because nullcopy preallocates but does */
      /*     not initialize. The fields are initialized by the current function. They are initialied here  */
      /*     because certain fields, depending on EntryFlag, will not be initialized by function  */
      /*     SkinDetect_RecordDiagnosticData.     */
      /*  */
      /*     Note: if the Matlab version of function SkinDetect is being used, function nullcopy has no    */
      /*     effect and variables are always initialized; hence, assignment here is not necessary.    */
      /* Inline function */
      b_ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo.size[0] = 0;
      b_ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo.size[1] = 0;
      b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.size[0] = 1;
      b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.size[1] = 2;
      b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.data[0] = 0U;
      b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.data[1] = 0U;

      /*  'NoRegions' */
      /* end local function */
      /* ============================================================================================= */
      /* Code-generation and build script */
      /* ============================================================================================= */
      /* Code-generation and build script used to generate C-language code and create the compiled version  */
      /* (SkinDetect_mex) of the function. */
      /* { */
      /*  */
      /* %%%%% Specify variable-size input arguments %%%%%% */
      /*  */
      /* See Matlab documentation for coder.typeof. */
      /*                                                                   */
      /*                                             Example Code                    Upp. Bounds       Var. Size (T/F)    Type */
      /* VidFrameCode                 = coder.typeof( zeros(500, 500, 3, 'uint8'),    [inf, inf, 3],    [1, 1, 0] );       %uint8  */
      /* ROI_SRCode                   = coder.typeof( zeros(1, 4, 'int16'),           [1, 4],           [1, 0] );          %int16 */
      /* FramesToProcessLinIdx_SRCode = coder.typeof( zeros(1, 500, 'int32'),         [1, inf],         [0, 1] );          %uint32  */
      /*           */
      /*        */
      /* %%%%% Specify fixed-size input arguments %%%%%% */
      /*  */
      /* iCode                                             = int32(0); */
      /* BoundingBoxSkinCode                               = zeros(1, 4, 'int16'); */
      /* ROIForBoundingBoxSkin_FRCode                      = zeros(1, 4, 'int16'); */
      /* VideoReadConfig_VidObjWidthCode                   = int16(0); */
      /* VideoReadConfig_VidObjHeightCode                  = int16(0); */
      /* OutputConfig_WriteVideoShowROISkinDiagnosisTFCode = false; */
      /* FirstReadSkinTFCode                               = false; */
      /* Notifications_Interval_SRCode                     = int32(0); */
      /* Notifications_LoopStartTime_SRCode                = uint64(0);  */
      /* Notifications_LoopCounter_SRCode                  = int32(0);                 */
      /*  */
      /* Note: the number, names, and order of struct fields are compile-time constants. */
      /*  */
      /* %%%%% --- ROIGeneralConfigCode struct %%%%%% */
      /*  */
      /*                         Example Code              Upp. Bounds    Var. Size (T/F)   Type */
      /* Element1 = coder.typeof( zeros(10, 5, 'double'),   [inf, 5],      [1, 0] );         %double */
      /*  */
      /* Element2 = coder.typeof( zeros(10, 1, 'double'),   [inf, 1],      [1, 0] );         %double */
      /*  */
      /* ROIGeneralConfigCode = ... */
      /*     struct( ... */
      /*         'ROIMinWidthProportion',                      double(0), ...                           */
      /*         'ROIMinHeightProportion',                     double(0), ...  */
      /*         'ROIWidthResizeFactor',                       double(0), ... */
      /*         'ROIHeightResizeFactor',                      double(0), ...             */
      /*         'ROIFinalSmoothingWindows',                   zeros(1, 2, 'int32'), ... */
      /*         'ROISkipFrameThreshold_adjusted',             int32(0), ... */
      /*         'ROIMSIR_DiffMaxDetection',                   int16(0), ... */
      /*         'ROIMSIR_DiffMaxAdjacent',                    int16(0), ... */
      /*         'ROIMSIR_FirstFrameIdx',                      int32(0), ... */
      /*         'FrameCacheMaxFrames',                        int32(0), ... */
      /*         'ROIMeansOperationsReadyFirstReadTF',         false, ... */
      /*         'ROIMeansMaxFrameToProcessSecondReadLinIdx',  int32(0), ... */
      /*         'ROISpecifyByArgument',                       Element1, ... */
      /*         'ROIIgnoreByArgument',                        Element2, ... */
      /*         'RecursiveTF',                                false, ... */
      /*         'ReturnAllTF',                                false, ... */
      /*         'UseCompiledFunctionsTF',                     false ... */
      /*     ); */
      /*  */
      /* %%%%% --- SkinSegmentConfig struct %%%%%%  */
      /*  */
      /* SkinSegmentConfigCode = ... */
      /*     struct( ... */
      /*         'SkinSegmentTF', false, ... Whether skin segmentation enabled */
      /*         'SkinSegmentSeverityFactor', double(0), ... For tuning severity of skin segmentation */
      /*         'MorphCloseSEMediumWidth', double(0), ... Width of structuring element for medium  */
      /*                                               ... morphological close before tuning. */
      /*         'MorphCloseSELargeWidth', double(0), ... Width of structuring element for large  */
      /*                                              ... morphological close before tuning.         */
      /*         'UseCompiledFunctionsTF', false, ... Whether to use compiled functions         */
      /*         'Args', ... Arguments to fuction SkinSegmentMask  */
      /*         struct( ... */
      /*             'SkinColorSamples_NThresholdPassedTF', false, ... */
      /*             'YCbCrThresholdsGeneric', zeros(1, 7, 'single'), ... */
      /*             'HSThresholdsGeneric', zeros(1, 2, 'single'), ... */
      /*             'YCbCrThresholdsTailored', zeros(1, 8, 'single'), ... */
      /*             'YCbCrThresholdsTailored_Sev', zeros(1, 8, 'single'), ... */
      /*             'HSThresholdsTailored', zeros(1, 3, 'single'), ... */
      /*             'HSThresholdsTailored_Sev', zeros(1, 3, 'single'), ... */
      /*             'RangeSEWidth', int16(0), ... */
      /*             'RangeThreshold', uint8(0), ... */
      /*             'MorphCloseSEMediumWidth_Tuned', int16(0), ... */
      /*             'MorphCloseSELargeWidth_Tuned', int16(0) ... */
      /*         ), ...  */
      /*         'TailoredData', ... Tailored skin-segmentation settings */
      /*         struct( ... */
      /*             ... Properties determining whether SkinSegment_SetThresholds will be called in function */
      /*             ... ROIMeans_FirstRead: */
      /*             'OpsReadyTF', false, ... */
      /*             'RecentThresholdOpsFrameIdx', int32(0), ... */
      /*             'ThresholdOpsInterval', int32(0), ... */
      /*             'ThresholdOpsRunCurrentFrameTF', false, ... */
      /*             ... Arguments to function SkinSegment_SetThresholds, which sets thresholds for the */
      /*             ... "tailored" option used by function SkinSegmentMask: */
      /*             'SkinColorSamples_NThreshold', double(0), ... */
      /*             'RangePercentile_YCbCrH', zeros(1, 2, 'double'), ... */
      /*             'RangePercentile_S', zeros(1, 2, 'double'), ... */
      /*             'SkinColorSamples_HighNThreshold', double(0), ... */
      /*             'SkinColorSamples_HighNThresholdPassedTF', false, ... */
      /*             'RangePercentileHighN_YCbCrH', zeros(1, 2, 'double'), ... */
      /*             'RangePercentileHighN_S', zeros(1, 2, 'double'), ... */
      /*             'RangePercentileSev_YCbCrH', zeros(1, 2, 'double'), ... */
      /*             'RangePercentileSev_S', zeros(1, 2, 'double') ... */
      /*         ), ... */
      /*         ... Values used by function ConfirmSkinPresent depending on the argument  */
      /*         ... PixelColorThresholdsType: */
      /*         'ConfirmSkin', ...  */
      /*         struct( ... */
      /*             'ProportionThresholdPrimary',    single(0), ... */
      /*             'ProportionThresholdSecondary1', single(0), ... */
      /*             'ProportionThresholdSecondary2', single(0), ... */
      /*             'ProportionThresholdSkin',       single(0), ... */
      /*             'ProportionThresholdMeans',      single(0)  ... */
      /*         ), ... */
      /*         'OverSegmentedCheck', ... */
      /*         struct( ... */
      /*             'CheckTF',                          false, ... */
      /*             'ProportionThresholdPrimary',       single(0), ... */
      /*             'ProportionThresholdSecondary1',    single(0), ... */
      /*             'ProportionThresholdSecondary2',    single(0), ... */
      /*             'FramesLowSkinProportionThreshold', double(0), ... */
      /*             'NFramesLowSkinProportionStatus',   double(0), ... */
      /*             'MorphReductionAmount',             double(0), ... */
      /*             'NMorphReductionLimit',             int32(0), ... */
      /*             'NMorphReductions',                 int32(0), ... */
      /*             'DarknessThreshold',                single(0), ... */
      /*             'BelowDarknessThresholdTF',         false, ... */
      /*             'NFramesYSingleMean',               single(0), ... */
      /*             'PixelColorsAdjustedTF',            false, ... */
      /*             'ColorThresAdjustTo',               zeros(1, 9, 'single') ...                */
      /*         ) ... */
      /*     );        */
      /*  */
      /* %%%%% --- SkinDetectConfig struct %%%%%% */
      /*  */
      /* SkinDetectConfigCode = ...  */
      /*     struct( ... */
      /*         'ROISkinTF', false, ... */
      /*         'Thresholds', ... */
      /*         struct( ...    */
      /*             'SetTF', false, ... */
      /*             'SkinColorSamples_NThreshold', double(0), ... */
      /*             'SkinColorSamples_NThresholdPassedTF', false, ... */
      /*             'SkinColorSamples_HighNThreshold', double(0), ...  */
      /*             'SkinColorSamples_HighNThresholdPassedTF', false, ... */
      /*             'SkinColorSamples_HighNThresholdIdx', int32(0), ...  */
      /*             'ColorThreshold', zeros(1, 3, 'single'), ... */
      /*             'ColorThresholdHighN', zeros(1, 3, 'single'), ... */
      /*             'RecentThresholdOpsFrameIdx', int32(0), ... */
      /*             'ThresholdOpsInterval', int32(0), ... */
      /*             'ThresholdOpsRunCurrentFrameTF', false, ... */
      /*             'ColorSDThreshold', single(0), ... */
      /*             'RGBProbTheta', zeros(4, 1, 'double'), ... */
      /*             'YCbCrMeanOfMeans', zeros(1, 3, 'single'), ... */
      /*             'YCbCrStdDevOfMeans', zeros(1, 3, 'single'), ... */
      /*             'RegionNThreshold', single(0) ... */
      /*         ), ... */
      /*         'ROISkinSkipFrameThreshold', int32(0), ... */
      /*         'ROISkin_BoundingBoxGrowthThreshold', int32(0), ... */
      /*         'ROISkin_BoundingBoxGrowthFactor', double(0), ... */
      /*         'ROISkin_InitialBoundingBoxScale', double(0), ... */
      /*         'ROISkinRegionMinSizeFactor', single(0), ... */
      /*         'ROISkinRegionProximityWeight', double(0), ... */
      /*         'ROISkinSmoothingWindow', double(0), ... */
      /*         'PartitionColInterval', int16(0), ... */
      /*         'PartitionRowInterval', int16(0), ... */
      /*         'SkinDetectionReadyTF', false, ... */
      /*         'ROISkin_BoundingBoxEnlargementFactor', double(0), ... */
      /*         'ROISkinSkipFrameThreshold_adjusted', int32(0), ... */
      /*         'UseCompiledFunctionsTF', false ... */
      /*     ); */
      /*  */
      /*  */
      /* %%%%% Set configurations to increase performance %%%%%% */
      /*  */
      /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
      /* "Optimization Strategies" */
      /*  */
      /* cfg = coder.config('mex'); */
      /* cfg.GlobalDataSyncMethod = 'NoSync'; */
      /* cfg.ConstantInputs = 'IgnoreValues'; */
      /* cfg.ExtrinsicCalls = true; %true to permit display of errors */
      /* cfg.SaturateOnIntegerOverflow = false; */
      /* cfg.IntegrityChecks = false; */
      /* cfg.ResponsivenessChecks = false; */
      /*  */
      /*  */
      /* %%%%% Specify flags to minGW compiler to optimize execution speed %%%%%% */
      /*  */
      /* For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html */
      /*  */
      /* The flags are specified as part of the code-generation configuration object. A custom function, */
      /* setbuildargs, is used to specify these flags. For details on the function implementation, see the  */
      /* function file, which is located within folder FacePulseRate. This custom function is based upon  */
      /* Matlab guidance found in */
      /* https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function */
      /*  */
      /* setbuildargs will be evaluated from text within the code-generation object, so it is converted to  */
      /* a character vector prior to execution of the codegen command. */
      /*  */
      /* %%%%% --- Specify the flags as arguments to function setbuildargs %%%%%% */
      /*  */
      /* Argument buildInfo: this variable is assign by the caller (the codegen command executed  */
      /* below) and is not present in the base workspace. */
      /*  */
      /* Second argument: specify a cell array of compiler-specific flags, where each flag is a  */
      /* character vector. As function setbuildargs will be evaluated from text, use double ' quotes for  */
      /* each character vector to maintain the charater vector, */
      /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
      /*  */
      /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})'; */
      /*  */
      /* Assign to code-generation configuration object */
      /* cfg.PostCodeGenCommand = setbuildargsAsText; */
      /*  */
      /*  */
      /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
      /*  */
      /* codegen SkinDetect.m -report -config cfg -args {iCode, VidFrameCode, VideoReadConfig_VidObjWidthCode, VideoReadConfig_VidObjHeightCode, SkinSegmentConfigCode, ROIGeneralConfigCode, SkinDetectConfigCode, OutputConfig_WriteVideoShowROISkinDiagnosisTFCode, BoundingBoxSkinCode, FirstReadSkinTFCode, ROIForBoundingBoxSkin_FRCode, ROI_SRCode, FramesToProcessLinIdx_SRCode, Notifications_Interval_SRCode, Notifications_LoopStartTime_SRCode, Notifications_LoopCounter_SRCode} */
      /*                  */
      /* } */
      c_cast(&b_ROIDiagnostic_ROISkin_ith, ROIDiagnostic_ROISkin_ith);
    }

    /* No regions were available */
    /* Note: this should be relatively uncommon. */
  } else {
    /* Initialize fields in struct ROIDiagnostic_ROISkin_ith: */
    /* Local function. */
    b_cast(ROIDiagnostic_ROISkin_ith, &b_ROIDiagnostic_ROISkin_ith);

    /* end local function */
    /* ============================================================================================= */
    /* ROIDiagnosticInitialize   Assign uninitialized values for ROIDiagnostic_ROISkin_ith.     */
    /*  */
    /*     Description: */
    /*  */
    /*     If the compiled version of function SkinDetect is being used, all fields in struct    */
    /*     ROIDiagnostic_ROISkin_ith must be initialized because the struct was preallocated by a call to   */
    /*     function nullcopy. The variables must be initialized because nullcopy preallocates but does */
    /*     not initialize. The fields are initialized by the current function. They are initialied here  */
    /*     because certain fields, depending on EntryFlag, will not be initialized by function  */
    /*     SkinDetect_RecordDiagnosticData.     */
    /*  */
    /*     Note: if the Matlab version of function SkinDetect is being used, function nullcopy has no    */
    /*     effect and variables are always initialized; hence, assignment here is not necessary.    */
    /* Inline function */
    b_ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo.size[0] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo.size[1] = 0;
    b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.size[0] = 1;
    b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.size[1] = 2;
    b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.data[0] = 0U;
    b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.data[1] = 0U;

    /*  'NoRegions' */
    /*    'ProportionSkinPixelsTooLow' */
    b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx->size[0] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx->size[1] = 0;
    b_ROIDiagnostic_ROISkin_ith.c_RegionBoundaries_CandidateLin->size[0] = 0;
    b_ROIDiagnostic_ROISkin_ith.c_RegionBoundaries_CandidateLin->size[1] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx->size[0] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx->size[1] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedRGBProb.size[0] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedRGBProb.size[1] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateRGBProb.size[0] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateRGBProb.size[1] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedRGBProb.size[0] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedRGBProb.size[1] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ.size[0] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ.size[1] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateYCbCrZ.size[0] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateYCbCrZ.size[1] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedYCbCrZ.size[0] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedYCbCrZ.size[1] = 0;
    b_ROIDiagnostic_ROISkin_ith.c_RegionCrSDScores_RejectedCrSD.size[0] = 0;
    b_ROIDiagnostic_ROISkin_ith.c_RegionCrSDScores_RejectedCrSD.size[1] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSD.size[0] = 0;
    b_ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSD.size[1] = 0;

    /* 'NoRegions' */
    b_ROIDiagnostic_ROISkin_ith.RegionAnyAvailable = false;

    /* end local function */
    /* ============================================================================================= */
    /* Code-generation and build script */
    /* ============================================================================================= */
    /* Code-generation and build script used to generate C-language code and create the compiled version  */
    /* (SkinDetect_mex) of the function. */
    /* { */
    /*  */
    /* %%%%% Specify variable-size input arguments %%%%%% */
    /*  */
    /* See Matlab documentation for coder.typeof. */
    /*                                                                   */
    /*                                             Example Code                    Upp. Bounds       Var. Size (T/F)    Type */
    /* VidFrameCode                 = coder.typeof( zeros(500, 500, 3, 'uint8'),    [inf, inf, 3],    [1, 1, 0] );       %uint8  */
    /* ROI_SRCode                   = coder.typeof( zeros(1, 4, 'int16'),           [1, 4],           [1, 0] );          %int16 */
    /* FramesToProcessLinIdx_SRCode = coder.typeof( zeros(1, 500, 'int32'),         [1, inf],         [0, 1] );          %uint32  */
    /*           */
    /*        */
    /* %%%%% Specify fixed-size input arguments %%%%%% */
    /*  */
    /* iCode                                             = int32(0); */
    /* BoundingBoxSkinCode                               = zeros(1, 4, 'int16'); */
    /* ROIForBoundingBoxSkin_FRCode                      = zeros(1, 4, 'int16'); */
    /* VideoReadConfig_VidObjWidthCode                   = int16(0); */
    /* VideoReadConfig_VidObjHeightCode                  = int16(0); */
    /* OutputConfig_WriteVideoShowROISkinDiagnosisTFCode = false; */
    /* FirstReadSkinTFCode                               = false; */
    /* Notifications_Interval_SRCode                     = int32(0); */
    /* Notifications_LoopStartTime_SRCode                = uint64(0);  */
    /* Notifications_LoopCounter_SRCode                  = int32(0);                 */
    /*  */
    /* Note: the number, names, and order of struct fields are compile-time constants. */
    /*  */
    /* %%%%% --- ROIGeneralConfigCode struct %%%%%% */
    /*  */
    /*                         Example Code              Upp. Bounds    Var. Size (T/F)   Type */
    /* Element1 = coder.typeof( zeros(10, 5, 'double'),   [inf, 5],      [1, 0] );         %double */
    /*  */
    /* Element2 = coder.typeof( zeros(10, 1, 'double'),   [inf, 1],      [1, 0] );         %double */
    /*  */
    /* ROIGeneralConfigCode = ... */
    /*     struct( ... */
    /*         'ROIMinWidthProportion',                      double(0), ...                           */
    /*         'ROIMinHeightProportion',                     double(0), ...  */
    /*         'ROIWidthResizeFactor',                       double(0), ... */
    /*         'ROIHeightResizeFactor',                      double(0), ...             */
    /*         'ROIFinalSmoothingWindows',                   zeros(1, 2, 'int32'), ... */
    /*         'ROISkipFrameThreshold_adjusted',             int32(0), ... */
    /*         'ROIMSIR_DiffMaxDetection',                   int16(0), ... */
    /*         'ROIMSIR_DiffMaxAdjacent',                    int16(0), ... */
    /*         'ROIMSIR_FirstFrameIdx',                      int32(0), ... */
    /*         'FrameCacheMaxFrames',                        int32(0), ... */
    /*         'ROIMeansOperationsReadyFirstReadTF',         false, ... */
    /*         'ROIMeansMaxFrameToProcessSecondReadLinIdx',  int32(0), ... */
    /*         'ROISpecifyByArgument',                       Element1, ... */
    /*         'ROIIgnoreByArgument',                        Element2, ... */
    /*         'RecursiveTF',                                false, ... */
    /*         'ReturnAllTF',                                false, ... */
    /*         'UseCompiledFunctionsTF',                     false ... */
    /*     ); */
    /*  */
    /* %%%%% --- SkinSegmentConfig struct %%%%%%  */
    /*  */
    /* SkinSegmentConfigCode = ... */
    /*     struct( ... */
    /*         'SkinSegmentTF', false, ... Whether skin segmentation enabled */
    /*         'SkinSegmentSeverityFactor', double(0), ... For tuning severity of skin segmentation */
    /*         'MorphCloseSEMediumWidth', double(0), ... Width of structuring element for medium  */
    /*                                               ... morphological close before tuning. */
    /*         'MorphCloseSELargeWidth', double(0), ... Width of structuring element for large  */
    /*                                              ... morphological close before tuning.         */
    /*         'UseCompiledFunctionsTF', false, ... Whether to use compiled functions         */
    /*         'Args', ... Arguments to fuction SkinSegmentMask  */
    /*         struct( ... */
    /*             'SkinColorSamples_NThresholdPassedTF', false, ... */
    /*             'YCbCrThresholdsGeneric', zeros(1, 7, 'single'), ... */
    /*             'HSThresholdsGeneric', zeros(1, 2, 'single'), ... */
    /*             'YCbCrThresholdsTailored', zeros(1, 8, 'single'), ... */
    /*             'YCbCrThresholdsTailored_Sev', zeros(1, 8, 'single'), ... */
    /*             'HSThresholdsTailored', zeros(1, 3, 'single'), ... */
    /*             'HSThresholdsTailored_Sev', zeros(1, 3, 'single'), ... */
    /*             'RangeSEWidth', int16(0), ... */
    /*             'RangeThreshold', uint8(0), ... */
    /*             'MorphCloseSEMediumWidth_Tuned', int16(0), ... */
    /*             'MorphCloseSELargeWidth_Tuned', int16(0) ... */
    /*         ), ...  */
    /*         'TailoredData', ... Tailored skin-segmentation settings */
    /*         struct( ... */
    /*             ... Properties determining whether SkinSegment_SetThresholds will be called in function */
    /*             ... ROIMeans_FirstRead: */
    /*             'OpsReadyTF', false, ... */
    /*             'RecentThresholdOpsFrameIdx', int32(0), ... */
    /*             'ThresholdOpsInterval', int32(0), ... */
    /*             'ThresholdOpsRunCurrentFrameTF', false, ... */
    /*             ... Arguments to function SkinSegment_SetThresholds, which sets thresholds for the */
    /*             ... "tailored" option used by function SkinSegmentMask: */
    /*             'SkinColorSamples_NThreshold', double(0), ... */
    /*             'RangePercentile_YCbCrH', zeros(1, 2, 'double'), ... */
    /*             'RangePercentile_S', zeros(1, 2, 'double'), ... */
    /*             'SkinColorSamples_HighNThreshold', double(0), ... */
    /*             'SkinColorSamples_HighNThresholdPassedTF', false, ... */
    /*             'RangePercentileHighN_YCbCrH', zeros(1, 2, 'double'), ... */
    /*             'RangePercentileHighN_S', zeros(1, 2, 'double'), ... */
    /*             'RangePercentileSev_YCbCrH', zeros(1, 2, 'double'), ... */
    /*             'RangePercentileSev_S', zeros(1, 2, 'double') ... */
    /*         ), ... */
    /*         ... Values used by function ConfirmSkinPresent depending on the argument  */
    /*         ... PixelColorThresholdsType: */
    /*         'ConfirmSkin', ...  */
    /*         struct( ... */
    /*             'ProportionThresholdPrimary',    single(0), ... */
    /*             'ProportionThresholdSecondary1', single(0), ... */
    /*             'ProportionThresholdSecondary2', single(0), ... */
    /*             'ProportionThresholdSkin',       single(0), ... */
    /*             'ProportionThresholdMeans',      single(0)  ... */
    /*         ), ... */
    /*         'OverSegmentedCheck', ... */
    /*         struct( ... */
    /*             'CheckTF',                          false, ... */
    /*             'ProportionThresholdPrimary',       single(0), ... */
    /*             'ProportionThresholdSecondary1',    single(0), ... */
    /*             'ProportionThresholdSecondary2',    single(0), ... */
    /*             'FramesLowSkinProportionThreshold', double(0), ... */
    /*             'NFramesLowSkinProportionStatus',   double(0), ... */
    /*             'MorphReductionAmount',             double(0), ... */
    /*             'NMorphReductionLimit',             int32(0), ... */
    /*             'NMorphReductions',                 int32(0), ... */
    /*             'DarknessThreshold',                single(0), ... */
    /*             'BelowDarknessThresholdTF',         false, ... */
    /*             'NFramesYSingleMean',               single(0), ... */
    /*             'PixelColorsAdjustedTF',            false, ... */
    /*             'ColorThresAdjustTo',               zeros(1, 9, 'single') ...                */
    /*         ) ... */
    /*     );        */
    /*  */
    /* %%%%% --- SkinDetectConfig struct %%%%%% */
    /*  */
    /* SkinDetectConfigCode = ...  */
    /*     struct( ... */
    /*         'ROISkinTF', false, ... */
    /*         'Thresholds', ... */
    /*         struct( ...    */
    /*             'SetTF', false, ... */
    /*             'SkinColorSamples_NThreshold', double(0), ... */
    /*             'SkinColorSamples_NThresholdPassedTF', false, ... */
    /*             'SkinColorSamples_HighNThreshold', double(0), ...  */
    /*             'SkinColorSamples_HighNThresholdPassedTF', false, ... */
    /*             'SkinColorSamples_HighNThresholdIdx', int32(0), ...  */
    /*             'ColorThreshold', zeros(1, 3, 'single'), ... */
    /*             'ColorThresholdHighN', zeros(1, 3, 'single'), ... */
    /*             'RecentThresholdOpsFrameIdx', int32(0), ... */
    /*             'ThresholdOpsInterval', int32(0), ... */
    /*             'ThresholdOpsRunCurrentFrameTF', false, ... */
    /*             'ColorSDThreshold', single(0), ... */
    /*             'RGBProbTheta', zeros(4, 1, 'double'), ... */
    /*             'YCbCrMeanOfMeans', zeros(1, 3, 'single'), ... */
    /*             'YCbCrStdDevOfMeans', zeros(1, 3, 'single'), ... */
    /*             'RegionNThreshold', single(0) ... */
    /*         ), ... */
    /*         'ROISkinSkipFrameThreshold', int32(0), ... */
    /*         'ROISkin_BoundingBoxGrowthThreshold', int32(0), ... */
    /*         'ROISkin_BoundingBoxGrowthFactor', double(0), ... */
    /*         'ROISkin_InitialBoundingBoxScale', double(0), ... */
    /*         'ROISkinRegionMinSizeFactor', single(0), ... */
    /*         'ROISkinRegionProximityWeight', double(0), ... */
    /*         'ROISkinSmoothingWindow', double(0), ... */
    /*         'PartitionColInterval', int16(0), ... */
    /*         'PartitionRowInterval', int16(0), ... */
    /*         'SkinDetectionReadyTF', false, ... */
    /*         'ROISkin_BoundingBoxEnlargementFactor', double(0), ... */
    /*         'ROISkinSkipFrameThreshold_adjusted', int32(0), ... */
    /*         'UseCompiledFunctionsTF', false ... */
    /*     ); */
    /*  */
    /*  */
    /* %%%%% Set configurations to increase performance %%%%%% */
    /*  */
    /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
    /* "Optimization Strategies" */
    /*  */
    /* cfg = coder.config('mex'); */
    /* cfg.GlobalDataSyncMethod = 'NoSync'; */
    /* cfg.ConstantInputs = 'IgnoreValues'; */
    /* cfg.ExtrinsicCalls = true; %true to permit display of errors */
    /* cfg.SaturateOnIntegerOverflow = false; */
    /* cfg.IntegrityChecks = false; */
    /* cfg.ResponsivenessChecks = false; */
    /*  */
    /*  */
    /* %%%%% Specify flags to minGW compiler to optimize execution speed %%%%%% */
    /*  */
    /* For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html */
    /*  */
    /* The flags are specified as part of the code-generation configuration object. A custom function, */
    /* setbuildargs, is used to specify these flags. For details on the function implementation, see the  */
    /* function file, which is located within folder FacePulseRate. This custom function is based upon  */
    /* Matlab guidance found in */
    /* https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function */
    /*  */
    /* setbuildargs will be evaluated from text within the code-generation object, so it is converted to  */
    /* a character vector prior to execution of the codegen command. */
    /*  */
    /* %%%%% --- Specify the flags as arguments to function setbuildargs %%%%%% */
    /*  */
    /* Argument buildInfo: this variable is assign by the caller (the codegen command executed  */
    /* below) and is not present in the base workspace. */
    /*  */
    /* Second argument: specify a cell array of compiler-specific flags, where each flag is a  */
    /* character vector. As function setbuildargs will be evaluated from text, use double ' quotes for  */
    /* each character vector to maintain the charater vector, */
    /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
    /*  */
    /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})'; */
    /*  */
    /* Assign to code-generation configuration object */
    /* cfg.PostCodeGenCommand = setbuildargsAsText; */
    /*  */
    /*  */
    /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
    /*  */
    /* codegen SkinDetect.m -report -config cfg -args {iCode, VidFrameCode, VideoReadConfig_VidObjWidthCode, VideoReadConfig_VidObjHeightCode, SkinSegmentConfigCode, ROIGeneralConfigCode, SkinDetectConfigCode, OutputConfig_WriteVideoShowROISkinDiagnosisTFCode, BoundingBoxSkinCode, FirstReadSkinTFCode, ROIForBoundingBoxSkin_FRCode, ROI_SRCode, FramesToProcessLinIdx_SRCode, Notifications_Interval_SRCode, Notifications_LoopStartTime_SRCode, Notifications_LoopCounter_SRCode} */
    /*                  */
    /* } */
    c_cast(&b_ROIDiagnostic_ROISkin_ith, ROIDiagnostic_ROISkin_ith);
  }

  emxFree_uint32_T(&c_IsSkinMask_PixelColor_ErodePa);
  emxFree_uint32_T(&IsSkinMask_PixelColorPacked);
  emxFree_boolean_T(&IsSkinMask_ROISelected);
  emxFree_real32_T(&CrBounded_Single);
  emxFree_real32_T(&CbBounded_Single);
  emxFree_real32_T(&YBounded_Single);
  emxFree_boolean_T(&IsSkinMask);
  emxFree_uint8_T(&BBounded_Uint8);
  emxFree_uint8_T(&GBounded_Uint8);
  emxFree_uint8_T(&RBounded_Uint8);

  /* %%%%% Record data for use in skin-detection diagnostics %%%%%% */
  /* Record data to be displayed on the output video for the purpose of assessing the effectiveness of  */
  /* the skin-detection algorithm. */
  /* If including skin-detection algorithm diagnostic information on output video is enabled */
  /* Also, proceed only if at least one region was available to the skin-detection algorithm. */
  /* If no regions are available, this is likely due to skin segmentation classifying all pixels as  */
  /* non-skin. */
  emxInitMatrix_cell_wrap_32(RegionBoundaries, true);
  if (c_OutputConfig_WriteVideoShowRO && (NRegions > 0)) {
    /* at least one region available */
    /* Scalar struct. */
    /* Note: 'SkinDetect_RecordDiagnosticData' is a custom function located within folder  */
    /* 'FacePulseRate'. */
    b_cast(ROIDiagnostic_ROISkin_ith, &b_ROIDiagnostic_ROISkin_ith);

    /* SkinDetect_RecordDiagnosticData   Record various metrics to determine effectiveness of the skin-  */
    /*                                   detection algorithm on each frame assessed. */
    /*  */
    /*     Helper function to function FacePulseRate.  */
    /*     Within function FacePulseRate, called by function SkinDetect.   */
    /*  */
    /*  */
    /*     Code Generation */
    /*     --------------- */
    /*  */
    /*     Can be called as a Matlab function or used for C-language code generation. */
    /*  */
    /*  */
    /*     Description */
    /*     ----------- */
    /*  */
    /*     Collect frame-by-frame diagnostic information regarding the performance of the skin-detection  */
    /*     algorithm. This information will be displayed on the output video (by function WriteFaceVideo  */
    /*     and, more specifically, WriteFaceVideo_SkinDetectDiagnosis).  */
    /*  */
    /*     Four states are possible from function SkinDetect, from which the current function is called. */
    /*  */
    /*     The first state is a successful ROI detection. In this state, region borders are shown for all  */
    /*     regions, with the regions color coded depending on whether the region corresponds to a  */
    /*     rejected, candidate, or selected region. Other information is also shown.  */
    /*  */
    /*     The second state is a region selected that fails the skin proportion test (see function  */
    /*     ConfirmSkinPresent). In this state, borders and other information are not shown but a message  */
    /*     is displayed on the output video indicating this result.  */
    /*  */
    /*     The third state is when all regions fail the rejection thresholds (see function  */
    /*     SkinDetect_RejectRegions). In this state, region borders of the rejected region(s) are shown  */
    /*     on the output video along with other information.      */
    /*  */
    /*     The forth state is when no regions are available for classification, likely because of  */
    /*     complete, or near complete, skin segmentation of the bounding box area. In this state, borders  */
    /*     and other information are not shown but a message is displayed on the output video indicating  */
    /*     this result. For more information on the diagnostic information displayed on the output video,  */
    /*     see functions WriteFaceVideo and WriteFaceVideo_SkinDetectDiagnosis. */
    /*  */
    /*  */
    /*     Copyright */
    /*     --------- */
    /*  */
    /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
    /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
    /*     licensing, please contact the author. */
    /* %%%%% Code-generation settings %%%%% */
    /* Inline function */
    /* Declare variable-size variables: */
    /*                                          Upp. Bounds   Var. Size (T/F) */
    /* cell array */
    /* cell array element */
    /* %%%%% Setup %%%%%% */
    /* Record that at least one region was available for skin detection for ith frame */
    /* Note: a false value will be present if the area corresponding to the skin-detection bounding box  */
    /* was completely segmented and, hence, has no regions available. Note that a false value will also  */
    /* be present if the frame did not have the skin-detection algorithm applied on it, that is, if  */
    /* function SkinDetect was not used for the frame.  */
    b_ROIDiagnostic_ROISkin_ith.RegionAnyAvailable = true;

    /* Proceed if the proportion of pixels classified as skin within the ROI from the selected region was  */
    /* above the specified threshold. If not, it is likely that skin-segmentation completely segmented  */
    /* the ROI. If not, diagnostic information is not displayed to avoid confusion because the depiction */
    /* of candidate regions and a selected region may make it appear that the skin-detection algorithm  */
    /* was successful for the ith frame. */
    if (!b_ROIDiagnostic_ROISkin_ith.ProportionSkinPixelsTooLow) {
      /* %%%%% Assign linear indices and flags to specify region status (candidate, rejected) %%%%%% */
      /* Note: RegionSelectedLinIdx already assigned. */
      /* Flag indicating a region was selected  */
      RegionSelectedAnyTF = ((RegionSelectedLinIdx_size[0] != 0) &&
        (RegionSelectedLinIdx_size[1] != 0));

      /* Linear index of rejected regions */
      /* Local function. */
      /*  column vector; type uint16 */
      /*  scalar; type uint16 */
      /* end main function */
      /* ============================================================================================= */
      /* Local functions */
      /* ============================================================================================= */
      /* ============================================================================================= */
      /* FindRejectedRegions   Return a linear index of rejected regions. */
      /*  */
      /*     Note: The linear index will be in the order of least to greatest. */
      /* Inline function */
      Counter_True = 0U;
      for (c_i = 0; c_i < NRegions; c_i++) {
        /* If false value */
        if (!c_RegionPassAllThresholdsTF_Log[c_i]) {
          Counter_True++;
          RegionPoints_RGBProbSkin_data[Counter_True - 1] = (uint16_T)(c_i + 1);
        }
      }

      /* Trim unassigned preallocated elements */
      if (Counter_True == 0) {
        RegionPoints_RGBProbSkin_size[0] = 0;
      } else {
        RegionPoints_RGBProbSkin_size[0] = Counter_True;
      }

      /* Assign number of rejected regions */
      /* Flag indicating at least one region was rejected  */
      RegionsRejectedAnyTF = (Counter_True != 0);

      /* Assert value to prevent dynamic memory allocation */
      /* Linear index of candidate regions */
      /* Local function. */
      /*  column vector; type uint16 */
      /*  scalar; type uint16 */
      /* end local function */
      /* ============================================================================================= */
      /* FindCandidateRegions   Return a linear index of candidate regions. */
      /*  */
      /*     Description: */
      /*  */
      /*     Return a linear index of candidate regions. Determine whether a region is a candidate region  */
      /*     by determining whether the linear index of the region does not correspond to that of a  */
      /*     selected region or a rejected region. */
      /*  */
      /*     The linear index will be in the order of least to greatest. */
      /*  */
      /*     Restrictions: */
      /*  */
      /*     - RegionSelectedLinIdx must be of length 0 or 1. */
      /*     - RegionsRejectedLinIdx must contain non-repeating values and monotonically increase. */
      /*     - The values of RegionSelectedLinIdx and RegionsRejectedLinIdx must be mutually exclusive. */
      /* Inline function */
      d_RegionPassAllThresholdsTF_Lin[0] = NRegions;

      /* If at least one rejected region */
      if (Counter_True != 0) {
        /* If at least one region is not rejected */
        if (Counter_True != NRegions) {
          MaxPoints = 0U;
          Counter_False = 0U;
          for (c_i = 0; c_i < NRegions; c_i++) {
            j = MaxPoints;
            CompletelyContainedTF = false;
            exitg1 = false;
            while ((!exitg1) && (j < Counter_True)) {
              j++;
              if (c_i + 1 == RegionPoints_RGBProbSkin_data[j - 1]) {
                CompletelyContainedTF = true;
                MaxPoints = j;
                exitg1 = true;
              }
            }

            if (!CompletelyContainedTF) {
              /* If at least one selected region */
              if ((RegionSelectedLinIdx_size[0] != 0) &&
                  (RegionSelectedLinIdx_size[1] != 0)) {
                /* If linear index is not the index of the selected region */
                i_size[0] = 1;
                i_size[1] = 1;
                TrueCount_data[0] = (c_i + 1 != RegionSelectedLinIdx_data[0]);
                if (b_ifWhileCond(TrueCount_data, i_size)) {
                  Counter_False++;

                  /* Add linear index as candidate linear index */
                  c_RegionPassAllThresholdsTF_Lin[Counter_False - 1] = (uint16_T)
                    (c_i + 1);
                }

                /* If no region was selected     */
              } else {
                Counter_False++;

                /* Add linear index as candidate linear index */
                c_RegionPassAllThresholdsTF_Lin[Counter_False - 1] = (uint16_T)
                  (c_i + 1);
              }
            }
          }

          /* Trim unused preallocated elements */
          if (Counter_False == 0) {
            d_RegionPassAllThresholdsTF_Lin[0] = 0;
          } else {
            d_RegionPassAllThresholdsTF_Lin[0] = Counter_False;
          }

          /* Assign number of candidate regions */
          /* If all regions rejected          */
        } else {
          d_RegionPassAllThresholdsTF_Lin[0] = 0;

          /* Assign number of candidate regions */
          Counter_False = 0U;
        }

        /* If no rejected regions     */
      } else {
        /* If at least one selected region */
        if ((RegionSelectedLinIdx_size[0] != 0) && (RegionSelectedLinIdx_size[1]
             != 0)) {
          /* Note: length is NRegions - 1 because there can only be one selected region. */
          d_RegionPassAllThresholdsTF_Lin[0] = NRegions - 1;
          Counter_False = 0U;
          if (0 <= NRegions - 1) {
            i_size[0] = 1;
            i_size[1] = 1;
          }

          for (c_i = 0; c_i < NRegions; c_i++) {
            TrueCount_data[0] = (c_i + 1 != RegionSelectedLinIdx_data[0]);
            if (b_ifWhileCond(TrueCount_data, i_size)) {
              Counter_False++;
              c_RegionPassAllThresholdsTF_Lin[Counter_False - 1] = (uint16_T)
                (c_i + 1);
            }
          }

          /* Assign number of candidate regions */
          /* If no region was selected */
        } else {
          for (c_i = 0; c_i < NRegions; c_i++) {
            c_RegionPassAllThresholdsTF_Lin[c_i] = (uint16_T)(c_i + 1);
          }

          /* Assign number of candidate regions */
          Counter_False = (uint16_T)NRegions;
        }
      }

      /* end local function */
      /* Flag indicating at least one region is a candidate region  */
      RegionsCandidateAnyTF = (Counter_False != 0);

      /* Assert value to prevent dynamic memory allocation */
      /* %%%%% Record Boundaries of Regions %%%%%% */
      /* Return an index of the pixels that lie on the external (perimeter) and internal (holes) */
      /* boundaries for each region. As the pixels have been dilated (for visibility on the output   */
      /* video), the pixels include pixels near the boundary as well. */
      /* 1 x 3 cell array; elements: N pixels x 1 column vector, type uint32. */
      /* Note: SkinDetect_RegionBoundariesByCategory is a custom function located within folder    */
      /* 'FacePulseRate'.     */
      c_SkinDetect_RegionBoundariesBy(emlrtRootTLSGlobal, RegionSelectedAnyTF,
        Counter_False, Counter_True, RegionSelectedLinIdx_data,
        b_RegionIndices.data, c_RegionPassAllThresholdsTF_Lin,
        RegionPoints_RGBProbSkin_data, VideoReadConfig_VidObjHeight,
        BoundingBoxSkin, RegionNPixels_data, BoundingBoxSkin[3],
        BoundingBoxSkin[2], RegionBoundaries);

      /* Store linear index of boundary pixels for later use for displaying skin regions on output  */
      /* video:  */
      /* Selected region */
      if (RegionSelectedAnyTF) {
        /* Assign boundary index to struct   */
        /* N pixels x 1 column vector; type uint32. */
        b_i = b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx->size
          [0] *
          b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx->size[1];
        b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx->size[0] =
          RegionBoundaries[0].f1->size[0];
        b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx->size[1] = 1;
        emxEnsureCapacity_uint32_T
          (b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx, b_i);
        NCentroids = RegionBoundaries[0].f1->size[0];
        for (b_i = 0; b_i < NCentroids; b_i++) {
          b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx->data[b_i]
            = RegionBoundaries[0].f1->data[b_i];
        }
      }

      /* Candidate regions */
      if (RegionsCandidateAnyTF) {
        /* Assign boundary index to struct   */
        /* N pixels x 1 column vector; type uint32. */
        b_i = b_ROIDiagnostic_ROISkin_ith.c_RegionBoundaries_CandidateLin->size
          [0] *
          b_ROIDiagnostic_ROISkin_ith.c_RegionBoundaries_CandidateLin->size[1];
        b_ROIDiagnostic_ROISkin_ith.c_RegionBoundaries_CandidateLin->size[0] =
          RegionBoundaries[1].f1->size[0];
        b_ROIDiagnostic_ROISkin_ith.c_RegionBoundaries_CandidateLin->size[1] = 1;
        emxEnsureCapacity_uint32_T
          (b_ROIDiagnostic_ROISkin_ith.c_RegionBoundaries_CandidateLin, b_i);
        NCentroids = RegionBoundaries[1].f1->size[0];
        for (b_i = 0; b_i < NCentroids; b_i++) {
          b_ROIDiagnostic_ROISkin_ith.c_RegionBoundaries_CandidateLin->data[b_i]
            = RegionBoundaries[1].f1->data[b_i];
        }
      }

      /* Rejected regions */
      if (RegionsRejectedAnyTF) {
        /* Assign boundary index to struct   */
        /* N pixels x 1 column vector; type uint32. */
        b_i = b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx->size
          [0] *
          b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx->size[1];
        b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx->size[0] =
          RegionBoundaries[2].f1->size[0];
        b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx->size[1] = 1;
        emxEnsureCapacity_uint32_T
          (b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx, b_i);
        NCentroids = RegionBoundaries[2].f1->size[0];
        for (b_i = 0; b_i < NCentroids; b_i++) {
          b_ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx->data[b_i]
            = RegionBoundaries[2].f1->data[b_i];
        }
      }

      /* %%%%% Record Centroids of Regions %%%%%% */
      /* Adjust the [X, Y] coordinates to undo change to [X, Y] as a result of cropping. This  */
      /* adjustment will place [X, Y] in the coordinate plane of the full (uncropped) frame so that  */
      /* [X, Y] can be used in the output video. To do so, add back distances of X and Y that were  */
      /* changed by cropping. */
      /* Note: 1 pixel length is subtracted from the [X, Y] that is added back because the previous  */
      /* cropping changed [Xoriginal, Yoriginal] to [1, 1]; that is, the cropping moved the coordinates  */
      /* a distance of Xoriginal - 1 and Yoriginal - 1. */
      /* Called during code generation */
      /* M regions x 2 matrix; type int16 */
      /* Scalars; type int16. */
      /* The X-coordinate column */
      for (c_i = 0; c_i < NRegions; c_i++) {
        RegionCentroids_Uncrop_data[c_i] = (int16_T)((int16_T)
          (RegionCentroids_data[c_i] + BoundingBoxSkin[0]) - 1);
        RegionCentroids_Uncrop_data[c_i + NRegions] = (int16_T)((int16_T)
          (RegionCentroids_data[c_i + RegionCentroids_size_idx_0] +
           BoundingBoxSkin[1]) - 1);
      }

      /* Called outsize of code generation            */
      /* Assign [X, Y] coordinates of region centroids to ith row of nested-struct RegionCentroids; */
      /* assign to the field corresponding to regions status (selected, candidate, rejected). */
      /* Type uint16. */
      if (RegionSelectedAnyTF) {
        /* if at least one region */
        /* 1 selected region x 2 row vector; type uint16. */
        NRegions_ith = RegionSelectedLinIdx_size[0] * RegionSelectedLinIdx_size
          [1];
        b_ROIDiagnostic_ROISkin_ith.RegionCentroids_SelectedXY.size[0] =
          NRegions_ith;
        b_ROIDiagnostic_ROISkin_ith.RegionCentroids_SelectedXY.size[1] = 2;
        if (0 <= NRegions_ith - 1) {
          b_ROIDiagnostic_ROISkin_ith.RegionCentroids_SelectedXY.data[0] =
            RegionCentroids_Uncrop_data[RegionSelectedLinIdx_data[0] - 1];
          b_ROIDiagnostic_ROISkin_ith.RegionCentroids_SelectedXY.data[NRegions_ith]
            = RegionCentroids_Uncrop_data[(RegionSelectedLinIdx_data[0] +
            NRegions) - 1];
        }
      }

      if (RegionsCandidateAnyTF) {
        /* if at least one region */
        /* M candidate regions x 2 matrix; type uint16. */
        b_ROIDiagnostic_ROISkin_ith.RegionCentroids_CandidateXY.size[0] =
          d_RegionPassAllThresholdsTF_Lin[0];
        b_ROIDiagnostic_ROISkin_ith.RegionCentroids_CandidateXY.size[1] = 2;
        NCentroids = d_RegionPassAllThresholdsTF_Lin[0];
        for (b_i = 0; b_i < NCentroids; b_i++) {
          b_ROIDiagnostic_ROISkin_ith.RegionCentroids_CandidateXY.data[b_i] =
            RegionCentroids_Uncrop_data[c_RegionPassAllThresholdsTF_Lin[b_i] - 1];
        }

        for (b_i = 0; b_i < NCentroids; b_i++) {
          b_ROIDiagnostic_ROISkin_ith.RegionCentroids_CandidateXY.data[b_i +
            b_ROIDiagnostic_ROISkin_ith.RegionCentroids_CandidateXY.size[0]] =
            RegionCentroids_Uncrop_data[(c_RegionPassAllThresholdsTF_Lin[b_i] +
            NRegions) - 1];
        }
      }

      if (RegionsRejectedAnyTF) {
        /* if at least one region */
        /* M rejected regions x 2 matrix; type uint16. */
        b_ROIDiagnostic_ROISkin_ith.RegionCentroids_RejectedXY.size[0] =
          RegionPoints_RGBProbSkin_size[0];
        b_ROIDiagnostic_ROISkin_ith.RegionCentroids_RejectedXY.size[1] = 2;
        NCentroids = RegionPoints_RGBProbSkin_size[0];
        for (b_i = 0; b_i < NCentroids; b_i++) {
          b_ROIDiagnostic_ROISkin_ith.RegionCentroids_RejectedXY.data[b_i] =
            RegionCentroids_Uncrop_data[RegionPoints_RGBProbSkin_data[b_i] - 1];
        }

        for (b_i = 0; b_i < NCentroids; b_i++) {
          b_ROIDiagnostic_ROISkin_ith.RegionCentroids_RejectedXY.data[b_i +
            b_ROIDiagnostic_ROISkin_ith.RegionCentroids_RejectedXY.size[0]] =
            RegionCentroids_Uncrop_data[(RegionPoints_RGBProbSkin_data[b_i] +
            NRegions) - 1];
        }
      }

      /* %%%%% Record the center point [X, Y] coordinates of the predicted ROI %%%%%% */
      /* Record the center point [X, Y] coordinates of the predicted ROI for the use of diagnosing  */
      /* skin-detection errors later. The predicted ROI will be superimposed on the output video if  */
      /* WriteVideoShowROISkinDiagnosisTF, which is an argument to function FacePulseRate, is true. In  */
      /* diagnosis, the proximity of the centroid of the selected region to the predicted-ROI center is  */
      /* inspected. This proximity is used, in part, to determine which of the candidate regions is */
      /* selected. Inspection can determine whether the proximity weight should be fine tuned depending  */
      /* on the desirability of the selected skin region. */
      /* Adjust the [X, Y] coordinates to undo change to [X, Y] as a result of cropping. This  */
      /* adjustment will place [X, Y] in the coordinate plane of the full (uncropped) frame so that  */
      /* [X, Y] can be used in the output video. To do so, add back distances of X and Y that were  */
      /* changed by cropping. */
      /* Convert from type int16 to type uint16 because signed operations not conducted with this */
      /* variable. */
      /* If at least one region passed the rejection thresholds (resulting in at least one selected or */
      /* candidate region). Otherwise, this information wasn't used in the assessment of regions for  */
      /* this frame. */
      if (RegionSelectedAnyTF || RegionsCandidateAnyTF) {
        /* 1 x 2 row vector; type uint16. */
        b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.size[0] = 1;
        b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.size[1] = 2;
        b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.data[0] = (uint16_T)
          ((int16_T)(ROIPredicted_CenterX + BoundingBoxSkin[0]) - 1);
        b_ROIDiagnostic_ROISkin_ith.PredictedROI_center.data[1] = (uint16_T)
          ((int16_T)(ROIPredicted_CenterY + BoundingBoxSkin[1]) - 1);
      }

      /* %%%%% Record RGB probabilities of regions %%%%%% */
      /* Assign probabilities of regions to ith row of nested-struct RegionScores; assign to the RGB */
      /* probability field corresponding to region status (selected, candidate, rejected).  */
      /* To conserve memory, convert RGB probability to type uint8 (multiply by 100 to remove  */
      /* fraction); uint8 conversion automatically rounds value to integer, which is necessary later   */
      /* when using the values as indices. */
      if (RegionSelectedAnyTF) {
        /* if at least one region */
        /* Scalar; type uint8. */
        b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedRGBProb.size[0] =
          RegionSelectedLinIdx_size[0];
        b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedRGBProb.size[1] =
          RegionSelectedLinIdx_size[1];
        NCentroids = RegionSelectedLinIdx_size[0] * RegionSelectedLinIdx_size[1];
        if (0 <= NCentroids - 1) {
          b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedRGBProb.data[0] =
            (uint8_T)muDoubleScalarRound
            (RegionRGBProbSkin_data[RegionSelectedLinIdx_data[0] - 1] * 100.0);
        }
      }

      if (RegionsCandidateAnyTF) {
        /* if at least one region */
        /* M candidate regions x 1 column vector; type uint8. */
        NRegions_ith = d_RegionPassAllThresholdsTF_Lin[0];
        NCentroids = d_RegionPassAllThresholdsTF_Lin[0];
        for (b_i = 0; b_i < NCentroids; b_i++) {
          b_tmp_data[b_i] = (uint8_T)muDoubleScalarRound
            (RegionRGBProbSkin_data[c_RegionPassAllThresholdsTF_Lin[b_i] - 1] *
             100.0);
        }

        b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateRGBProb.size[0] =
          d_RegionPassAllThresholdsTF_Lin[0];
        b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateRGBProb.size[1] = 1;
        if (0 <= NRegions_ith - 1) {
          memcpy
            (&b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateRGBProb.data[0],
             &b_tmp_data[0], NRegions_ith * sizeof(uint8_T));
        }
      }

      if (RegionsRejectedAnyTF) {
        /* if at least one region */
        /* M rejected regions x 1 column vector; type uint8. */
        NRegions_ith = RegionPoints_RGBProbSkin_size[0];
        NCentroids = RegionPoints_RGBProbSkin_size[0];
        for (b_i = 0; b_i < NCentroids; b_i++) {
          b_tmp_data[b_i] = (uint8_T)muDoubleScalarRound
            (RegionRGBProbSkin_data[RegionPoints_RGBProbSkin_data[b_i] - 1] *
             100.0);
        }

        b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedRGBProb.size[0] =
          RegionPoints_RGBProbSkin_size[0];
        b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedRGBProb.size[1] = 1;
        if (0 <= NRegions_ith - 1) {
          memcpy(&b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedRGBProb.data
                 [0], &b_tmp_data[0], NRegions_ith * sizeof(uint8_T));
        }
      }

      /* %%%%% Record YCbCr Z-Scores of Regions %%%%%% */
      /* Assign z-scores of regions to ith row of nested-struct RegionScores; assign to the YCbCr  */
      /* z-scores field corresponding to region status (selected, candidate, rejected). */
      /* Round to 2 decimal places for presentation purposes. The round(X * 100) * .01 is used because  */
      /* code generation does not support round(X, 2). */
      if (RegionSelectedAnyTF) {
        /* if at least one region */
        /* 1 selected region x 3 row vector; type single.         */
        NCentroids = RegionSelectedLinIdx_size[0] * RegionSelectedLinIdx_size[1];
        if (0 <= NCentroids - 1) {
          HBounded_Single_data[0] = RegionZ_Y_data[RegionSelectedLinIdx_data[0]
            - 1] * 100.0F;
        }

        NRegions_ith = RegionSelectedLinIdx_size[0] * RegionSelectedLinIdx_size
          [1];
        for (ElementIdx = 0; ElementIdx < NRegions_ith; ElementIdx++) {
          HBounded_Single_data[0] = muSingleScalarRound(HBounded_Single_data[0]);
        }

        for (b_i = 0; b_i < NRegions_ith; b_i++) {
          HBounded_Single_data[0] *= 0.01F;
        }

        NCentroids = RegionSelectedLinIdx_size[0] * RegionSelectedLinIdx_size[1];
        if (0 <= NCentroids - 1) {
          SBounded_Single_data[0] = RegionZ_Cb_data[RegionSelectedLinIdx_data[0]
            - 1] * 100.0F;
        }

        NRegions_ith = RegionSelectedLinIdx_size[0] * RegionSelectedLinIdx_size
          [1];
        for (ElementIdx = 0; ElementIdx < NRegions_ith; ElementIdx++) {
          SBounded_Single_data[0] = muSingleScalarRound(SBounded_Single_data[0]);
        }

        for (b_i = 0; b_i < NRegions_ith; b_i++) {
          SBounded_Single_data[0] *= 0.01F;
        }

        NCentroids = RegionSelectedLinIdx_size[0] * RegionSelectedLinIdx_size[1];
        if (0 <= NCentroids - 1) {
          YBounded_Single_data[0] = RegionZ_Cr_data[RegionSelectedLinIdx_data[0]
            - 1] * 100.0F;
        }

        NRegions_ith = RegionSelectedLinIdx_size[0] * RegionSelectedLinIdx_size
          [1];
        for (ElementIdx = 0; ElementIdx < NRegions_ith; ElementIdx++) {
          YBounded_Single_data[0] = muSingleScalarRound(YBounded_Single_data[0]);
        }

        for (b_i = 0; b_i < NRegions_ith; b_i++) {
          YBounded_Single_data[0] *= 0.01F;
        }

        if ((RegionSelectedLinIdx_size[0] != 0) && (RegionSelectedLinIdx_size[1]
             != 0)) {
          NRegions_ith = 1;
        } else if ((RegionSelectedLinIdx_size[0] != 0) &&
                   (RegionSelectedLinIdx_size[1] != 0)) {
          NRegions_ith = 1;
        } else if ((RegionSelectedLinIdx_size[0] != 0) &&
                   (RegionSelectedLinIdx_size[1] != 0)) {
          NRegions_ith = 1;
        } else {
          NRegions_ith = (RegionSelectedLinIdx_size[0] > 0);
          if (RegionSelectedLinIdx_size[0] > NRegions_ith) {
            NRegions_ith = 1;
          }

          if (RegionSelectedLinIdx_size[0] > NRegions_ith) {
            NRegions_ith = 1;
          }
        }

        CompletelyContainedTF = (NRegions_ith == 0);
        if (CompletelyContainedTF || ((RegionSelectedLinIdx_size[0] != 0) &&
             (RegionSelectedLinIdx_size[1] != 0))) {
          input_sizes_idx_1 = (int8_T)RegionSelectedLinIdx_size[1];
        } else {
          input_sizes_idx_1 = 0;
        }

        if (CompletelyContainedTF || ((RegionSelectedLinIdx_size[0] != 0) &&
             (RegionSelectedLinIdx_size[1] != 0))) {
          b_input_sizes_idx_1 = (int8_T)RegionSelectedLinIdx_size[1];
        } else {
          b_input_sizes_idx_1 = 0;
        }

        if (CompletelyContainedTF || ((RegionSelectedLinIdx_size[0] != 0) &&
             (RegionSelectedLinIdx_size[1] != 0))) {
          sizes_idx_1 = (int8_T)RegionSelectedLinIdx_size[1];
        } else {
          sizes_idx_1 = 0;
        }

        b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ.size[0] =
          NRegions_ith;
        b_i = input_sizes_idx_1 + b_input_sizes_idx_1;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ.size[1] = b_i +
          sizes_idx_1;
        NCentroids = input_sizes_idx_1;
        if ((0 <= NCentroids - 1) && (0 <= NRegions_ith - 1)) {
          b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ.data[0] =
            HBounded_Single_data[0];
        }

        NCentroids = b_input_sizes_idx_1;
        if ((0 <= NCentroids - 1) && (0 <= NRegions_ith - 1)) {
          b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ.data[NRegions_ith
            * input_sizes_idx_1] = SBounded_Single_data[0];
        }

        NCentroids = sizes_idx_1;
        if ((0 <= NCentroids - 1) && (0 <= NRegions_ith - 1)) {
          b_ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ.data[NRegions_ith
            * b_i] = YBounded_Single_data[0];
        }
      }

      if (RegionsCandidateAnyTF) {
        /* if at least one region   */
        /* M candidate regions x 3 matrix; type single. */
        b_i = Counter_False;
        for (c_i = 0; c_i < b_i; c_i++) {
          NRegions_ith = c_RegionPassAllThresholdsTF_Lin[c_i] - 1;
          c_RegionScores_CandidateYCbCrZ_[c_i] = muSingleScalarRound
            (RegionZ_Y_data[NRegions_ith] * 100.0F) * 0.01F;
          c_RegionScores_CandidateYCbCrZ_[c_i + Counter_False] =
            muSingleScalarRound(RegionZ_Cb_data[NRegions_ith] * 100.0F) * 0.01F;
          c_RegionScores_CandidateYCbCrZ_[c_i + Counter_False * 2] =
            muSingleScalarRound(RegionZ_Cr_data[NRegions_ith] * 100.0F) * 0.01F;
        }

        /* Assign to struct */
        b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateYCbCrZ.size[0] =
          Counter_False;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateYCbCrZ.size[1] = 3;
        NCentroids = Counter_False * 3;
        if (0 <= NCentroids - 1) {
          memcpy(&b_ROIDiagnostic_ROISkin_ith.RegionScores_CandidateYCbCrZ.data
                 [0], &c_RegionScores_CandidateYCbCrZ_[0], NCentroids * sizeof
                 (real32_T));
        }
      }

      if (RegionsRejectedAnyTF) {
        /* if at least one region                      */
        /* M rejected regions x 3 matrix; type single. */
        b_i = Counter_True;
        for (c_i = 0; c_i < b_i; c_i++) {
          NRegions_ith = RegionPoints_RGBProbSkin_data[c_i] - 1;
          c_RegionScores_CandidateYCbCrZ_[c_i] = muSingleScalarRound
            (RegionZ_Y_data[NRegions_ith] * 100.0F) * 0.01F;
          c_RegionScores_CandidateYCbCrZ_[c_i + Counter_True] =
            muSingleScalarRound(RegionZ_Cb_data[NRegions_ith] * 100.0F) * 0.01F;
          c_RegionScores_CandidateYCbCrZ_[c_i + Counter_True * 2] =
            muSingleScalarRound(RegionZ_Cr_data[NRegions_ith] * 100.0F) * 0.01F;
        }

        /* Assign to struct */
        b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedYCbCrZ.size[0] =
          Counter_True;
        b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedYCbCrZ.size[1] = 3;
        NCentroids = Counter_True * 3;
        if (0 <= NCentroids - 1) {
          memcpy(&b_ROIDiagnostic_ROISkin_ith.RegionScores_RejectedYCbCrZ.data[0],
                 &c_RegionScores_CandidateYCbCrZ_[0], NCentroids * sizeof
                 (real32_T));
        }
      }

      /* %%%%% Record Rankings Index of Candidate Regions %%%%%%  */
      /* Rankings are recorded to enable a cleaner display on the output video. */
      /* For example, it may be most useful to show only the top couple and bottom couple of candidate  */
      /* regions. */
      /* Index candidate regions by selection points from largest to smallest */
      /* Convert to type single to conserve memory. */
      if (RegionsCandidateAnyTF) {
        /* if at least one region */
        /* Type double. */
        RegionPoints_Proximity_size[0] = d_RegionPassAllThresholdsTF_Lin[0];
        NCentroids = d_RegionPassAllThresholdsTF_Lin[0];
        for (b_i = 0; b_i < NCentroids; b_i++) {
          RegionPoints_Proximity_data[b_i] =
            RegionPoints_data[c_RegionPassAllThresholdsTF_Lin[b_i] - 1];
        }

        d_sort(RegionPoints_Proximity_data, RegionPoints_Proximity_size,
               iidx_data, s_size);
        NCentroids = s_size[0];
        for (b_i = 0; b_i < NCentroids; b_i++) {
          RegionDistance_LinIdx_data[b_i] = iidx_data[b_i];
        }

        /* M candidate regions x 1 column vector; type single. */
        b_ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo.size[0] =
          s_size[0];
        b_ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo.size[1] = 1;
        NCentroids = s_size[0];
        for (b_i = 0; b_i < NCentroids; b_i++) {
          b_ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo.data[b_i] =
            (real32_T)RegionDistance_LinIdx_data[b_i];
        }
      }

      /* %%%%% Record the Cr standard deviation of rejected regions %%%%%% */
      /* For regions rejected due to exceeding the Cr standard deviation, only Cr standard deviation  */
      /* information on the output video (RGB, YCbCr, and pixel-count values not displayed for these */
      /* regions).    */
      /* If at least one region rejected due to Cr SD */
      d_RegionPassAllThresholdsTF_Log[0] = c_RegionSD_Cr_PassThresholdTF_L;
      for (b_i = 0; b_i < c_RegionSD_Cr_PassThresholdTF_L; b_i++) {
        c_RegionPassAllThresholdsTF_Log[b_i] =
          !d_RegionSD_Cr_PassThresholdTF_L[b_i];
      }

      if (any(c_RegionPassAllThresholdsTF_Log, d_RegionPassAllThresholdsTF_Log))
      {
        /* Record index of regions rejected due to Cr SD */
        /* A linear index of uint16 will be used instead of a logical index because few regions are */
        /* expected to be rejected by this threshold. Storing a few linear indices of type uint16 */
        /* will use less memory than holding a logical value for each region. */
        /* M x 1 column vector; type uint16. */
        eml_find(c_RegionPassAllThresholdsTF_Log,
                 d_RegionPassAllThresholdsTF_Log, iidx_data, s_size);
        NCentroids = s_size[0];
        for (b_i = 0; b_i < NCentroids; b_i++) {
          c_RegionPassAllThresholdsTF_Lin[b_i] = (uint16_T)iidx_data[b_i];
        }

        b_ROIDiagnostic_ROISkin_ith.c_RegionCrSDScores_RejectedCrSD.size[0] =
          s_size[0];
        b_ROIDiagnostic_ROISkin_ith.c_RegionCrSDScores_RejectedCrSD.size[1] = 1;
        NCentroids = s_size[0];
        if (0 <= NCentroids - 1) {
          memcpy
            (&b_ROIDiagnostic_ROISkin_ith.c_RegionCrSDScores_RejectedCrSD.data[0],
             &c_RegionPassAllThresholdsTF_Lin[0], NCentroids * sizeof(uint16_T));
        }

        /* Record standard deviation of regions rejected due to Cr SD */
        /* M x 1 column vector; type single. */
        NRegions_ith = c_RegionSD_Cr_PassThresholdTF_L - 1;
        NCentroids = 0;
        ElementIdx = 0;
        for (c_i = 0; c_i <= NRegions_ith; c_i++) {
          if (!d_RegionSD_Cr_PassThresholdTF_L[c_i]) {
            NCentroids++;
            c_tmp_data[ElementIdx] = (int16_T)(c_i + 1);
            ElementIdx++;
          }
        }

        b_ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSD.size[0] =
          NCentroids;
        b_ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSD.size[1] = 1;
        for (b_i = 0; b_i < NCentroids; b_i++) {
          b_ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSD.data[b_i] =
            RegionSD_Cr_data[c_tmp_data[b_i] - 1];
        }
      }

      /* %%%%% Record the Number of Pixels of Rejected Regions %%%%%% */
      /* For regions rejected due to low pixel counts, only display the pixel count information on the */
      /* output video (RGB and YCbCr values not displayed for these regions). */
      /* This is conducted to enable a cleaner display. For example, if a region is rejected due to a  */
      /* low pixel count, this may be the only relevant information as a low pixel count tends to   */
      /* predict non-skin regions well. */
      if (RegionsRejectedAnyTF) {
        /* if at least one region */
        /* Assign number of pixels of regions to field RejectedN in ith row of nested-struct  */
        /* RegionNPixels. */
        /* Convert to type uint32 to conserve memory. */
        NRegions_ith = Counter_True;
        b_i = Counter_True;
        for (c_i = 0; c_i < b_i; c_i++) {
          RegionNPixels_RejectedN_data[c_i] = (uint32_T)
            RegionNPixels_data[RegionPoints_RGBProbSkin_data[c_i] - 1];
        }

        /* Assign to struct */
        b_ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedN.size[0] =
          Counter_True;
        b_ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedN.size[1] = 1;
        if (0 <= NRegions_ith - 1) {
          memcpy(&b_ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedN.data[0],
                 &RegionNPixels_RejectedN_data[0], NRegions_ith * sizeof
                 (uint32_T));
        }

        /* Record TF whether rejected region was rejected because n lower than minimum: */
        /* This information can be used in conjuction with the pixel count data. */
        d_RegionPassAllThresholdsTF_Log[0] = RegionPoints_RGBProbSkin_size[0];
        NCentroids = RegionPoints_RGBProbSkin_size[0];
        for (b_i = 0; b_i < NCentroids; b_i++) {
          c_RegionPassAllThresholdsTF_Log[b_i] =
            c_RegionNPixels_PassNThresholdT[RegionPoints_RGBProbSkin_data[b_i] -
            1];
        }

        if (any(c_RegionPassAllThresholdsTF_Log, d_RegionPassAllThresholdsTF_Log))
        {
          /* Assign to ith row of field RejectedLowNTF of nested-struct RegionNPixels */
          /* Type logical. */
          NCentroids = RegionPoints_RGBProbSkin_size[0];
          for (b_i = 0; b_i < NCentroids; b_i++) {
            c_RegionPassAllThresholdsTF_Log[b_i] =
              !c_RegionNPixels_PassNThresholdT[RegionPoints_RGBProbSkin_data[b_i]
              - 1];
          }

          b_ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedLowNTF.size[0] =
            RegionPoints_RGBProbSkin_size[0];
          b_ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedLowNTF.size[1] = 1;
          NCentroids = RegionPoints_RGBProbSkin_size[0];
          if (0 <= NCentroids - 1) {
            memcpy
              (&b_ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedLowNTF.data[0],
               &c_RegionPassAllThresholdsTF_Log[0], NCentroids * sizeof
               (boolean_T));
          }
        }
      }
    }

    c_cast(&b_ROIDiagnostic_ROISkin_ith, ROIDiagnostic_ROISkin_ith);
  }

  emxFreeMatrix_cell_wrap_32(RegionBoundaries);
  emxFreeStruct_struct_T1(&b_ROIDiagnostic_ROISkin_ith);
  emxFree_struct_T_400(&b_RegionIndices);

  /* %%%%% Display progress notifications %%%%%%     */
  /* Note: include the following statement immediately before loop: LoopStartTime = tic. */
  /* Only use when called in second read (called by function ROIMeans_SecondRead_SkinDetect). */
  /* Also, do not implement for generated code. Specifically, passing tic  */
  /* (Notifications_LoopStartTime_SR) from Matlab code to toc in compiled code not recommended by  */
  /* Matlab documentation.     */
  /*  second-read operations ongoing */
  *LoopCounter = 0U;
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

emlrtCTX emlrtGetRootTLSGlobal(void)
{
  return emlrtRootTLSGlobal;
}

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, const emlrtConstCTX aTLS,
  void *aData)
{
  omp_set_lock(&emlrtLockGlobal);
  emlrtCallLockeeFunction(aLockee, aTLS, aData);
  omp_unset_lock(&emlrtLockGlobal);
}

/* End of code generation (SkinDetect.c) */
