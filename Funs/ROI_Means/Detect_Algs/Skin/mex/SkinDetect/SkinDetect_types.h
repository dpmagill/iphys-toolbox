/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect_types.h
 *
 * Code generation for function 'SkinDetect'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef typedef_struct3_T
#define typedef_struct3_T

typedef struct {
  real32_T ProportionThresholdPrimary;
  real32_T ProportionThresholdSecondary1;
  real32_T ProportionThresholdSecondary2;
  real32_T ProportionThresholdSkin;
  real32_T ProportionThresholdMeans;
} struct3_T;

#endif                                 /*typedef_struct3_T*/

#ifndef typedef_struct_T
#define typedef_struct_T

typedef struct {
  real_T Centroid[2];
} struct_T;

#endif                                 /*typedef_struct_T*/

#ifndef struct_emxArray_uint8_T
#define struct_emxArray_uint8_T

struct emxArray_uint8_T
{
  uint8_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_uint8_T*/

#ifndef typedef_emxArray_uint8_T
#define typedef_emxArray_uint8_T

typedef struct emxArray_uint8_T emxArray_uint8_T;

#endif                                 /*typedef_emxArray_uint8_T*/

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int32_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_int32_T*/

#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T

typedef struct emxArray_int32_T emxArray_int32_T;

#endif                                 /*typedef_emxArray_int32_T*/

#ifndef struct_emxArray_uint16_T_1x4
#define struct_emxArray_uint16_T_1x4

struct emxArray_uint16_T_1x4
{
  uint16_T data[4];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_uint16_T_1x4*/

#ifndef typedef_emxArray_uint16_T_1x4
#define typedef_emxArray_uint16_T_1x4

typedef struct emxArray_uint16_T_1x4 emxArray_uint16_T_1x4;

#endif                                 /*typedef_emxArray_uint16_T_1x4*/

#ifndef struct_emxArray_uint32_T_400x1
#define struct_emxArray_uint32_T_400x1

struct emxArray_uint32_T_400x1
{
  uint32_T data[400];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_uint32_T_400x1*/

#ifndef typedef_emxArray_uint32_T_400x1
#define typedef_emxArray_uint32_T_400x1

typedef struct emxArray_uint32_T_400x1 emxArray_uint32_T_400x1;

#endif                                 /*typedef_emxArray_uint32_T_400x1*/

#ifndef struct_emxArray_boolean_T_400x1
#define struct_emxArray_boolean_T_400x1

struct emxArray_boolean_T_400x1
{
  boolean_T data[400];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_boolean_T_400x1*/

#ifndef typedef_emxArray_boolean_T_400x1
#define typedef_emxArray_boolean_T_400x1

typedef struct emxArray_boolean_T_400x1 emxArray_boolean_T_400x1;

#endif                                 /*typedef_emxArray_boolean_T_400x1*/

#ifndef struct_emxArray_int16_T_1x2
#define struct_emxArray_int16_T_1x2

struct emxArray_int16_T_1x2
{
  int16_T data[2];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_int16_T_1x2*/

#ifndef typedef_emxArray_int16_T_1x2
#define typedef_emxArray_int16_T_1x2

typedef struct emxArray_int16_T_1x2 emxArray_int16_T_1x2;

#endif                                 /*typedef_emxArray_int16_T_1x2*/

#ifndef struct_emxArray_int16_T_400x2
#define struct_emxArray_int16_T_400x2

struct emxArray_int16_T_400x2
{
  int16_T data[800];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_int16_T_400x2*/

#ifndef typedef_emxArray_int16_T_400x2
#define typedef_emxArray_int16_T_400x2

typedef struct emxArray_int16_T_400x2 emxArray_int16_T_400x2;

#endif                                 /*typedef_emxArray_int16_T_400x2*/

#ifndef struct_emxArray_uint16_T_1x2
#define struct_emxArray_uint16_T_1x2

struct emxArray_uint16_T_1x2
{
  uint16_T data[2];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_uint16_T_1x2*/

#ifndef typedef_emxArray_uint16_T_1x2
#define typedef_emxArray_uint16_T_1x2

typedef struct emxArray_uint16_T_1x2 emxArray_uint16_T_1x2;

#endif                                 /*typedef_emxArray_uint16_T_1x2*/

#ifndef struct_emxArray_uint8_T_1x1
#define struct_emxArray_uint8_T_1x1

struct emxArray_uint8_T_1x1
{
  uint8_T data[1];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_uint8_T_1x1*/

#ifndef typedef_emxArray_uint8_T_1x1
#define typedef_emxArray_uint8_T_1x1

typedef struct emxArray_uint8_T_1x1 emxArray_uint8_T_1x1;

#endif                                 /*typedef_emxArray_uint8_T_1x1*/

#ifndef struct_emxArray_uint8_T_400x1
#define struct_emxArray_uint8_T_400x1

struct emxArray_uint8_T_400x1
{
  uint8_T data[400];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_uint8_T_400x1*/

#ifndef typedef_emxArray_uint8_T_400x1
#define typedef_emxArray_uint8_T_400x1

typedef struct emxArray_uint8_T_400x1 emxArray_uint8_T_400x1;

#endif                                 /*typedef_emxArray_uint8_T_400x1*/

#ifndef struct_emxArray_real32_T_1x3
#define struct_emxArray_real32_T_1x3

struct emxArray_real32_T_1x3
{
  real32_T data[3];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_real32_T_1x3*/

#ifndef typedef_emxArray_real32_T_1x3
#define typedef_emxArray_real32_T_1x3

typedef struct emxArray_real32_T_1x3 emxArray_real32_T_1x3;

#endif                                 /*typedef_emxArray_real32_T_1x3*/

#ifndef struct_emxArray_real32_T_400x3
#define struct_emxArray_real32_T_400x3

struct emxArray_real32_T_400x3
{
  real32_T data[1200];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_real32_T_400x3*/

#ifndef typedef_emxArray_real32_T_400x3
#define typedef_emxArray_real32_T_400x3

typedef struct emxArray_real32_T_400x3 emxArray_real32_T_400x3;

#endif                                 /*typedef_emxArray_real32_T_400x3*/

#ifndef struct_emxArray_real32_T_400x1
#define struct_emxArray_real32_T_400x1

struct emxArray_real32_T_400x1
{
  real32_T data[400];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_real32_T_400x1*/

#ifndef typedef_emxArray_real32_T_400x1
#define typedef_emxArray_real32_T_400x1

typedef struct emxArray_real32_T_400x1 emxArray_real32_T_400x1;

#endif                                 /*typedef_emxArray_real32_T_400x1*/

#ifndef struct_emxArray_uint16_T_400x1
#define struct_emxArray_uint16_T_400x1

struct emxArray_uint16_T_400x1
{
  uint16_T data[400];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_uint16_T_400x1*/

#ifndef typedef_emxArray_uint16_T_400x1
#define typedef_emxArray_uint16_T_400x1

typedef struct emxArray_uint16_T_400x1 emxArray_uint16_T_400x1;

#endif                                 /*typedef_emxArray_uint16_T_400x1*/

#ifndef struct_emxArray_uint32_T
#define struct_emxArray_uint32_T

struct emxArray_uint32_T
{
  uint32_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_uint32_T*/

#ifndef typedef_emxArray_uint32_T
#define typedef_emxArray_uint32_T

typedef struct emxArray_uint32_T emxArray_uint32_T;

#endif                                 /*typedef_emxArray_uint32_T*/

#ifndef typedef_b_struct_T
#define typedef_b_struct_T

typedef struct {
  emxArray_uint32_T *PixelIdxList;
} b_struct_T;

#endif                                 /*typedef_b_struct_T*/

#ifndef typedef_emxArray_struct_T_400
#define typedef_emxArray_struct_T_400

typedef struct {
  b_struct_T data[400];
  int32_T size[1];
} emxArray_struct_T_400;

#endif                                 /*typedef_emxArray_struct_T_400*/

#ifndef typedef_cell_wrap_32
#define typedef_cell_wrap_32

typedef struct {
  emxArray_uint32_T *f1;
} cell_wrap_32;

#endif                                 /*typedef_cell_wrap_32*/

#ifndef typedef_emxArray_struct_T
#define typedef_emxArray_struct_T

typedef struct {
  struct_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
} emxArray_struct_T;

#endif                                 /*typedef_emxArray_struct_T*/

#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T

struct emxArray_boolean_T
{
  boolean_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_boolean_T*/

#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T

typedef struct emxArray_boolean_T emxArray_boolean_T;

#endif                                 /*typedef_emxArray_boolean_T*/

#ifndef struct_emxArray_real32_T
#define struct_emxArray_real32_T

struct emxArray_real32_T
{
  real32_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real32_T*/

#ifndef typedef_emxArray_real32_T
#define typedef_emxArray_real32_T

typedef struct emxArray_real32_T emxArray_real32_T;

#endif                                 /*typedef_emxArray_real32_T*/

#ifndef struct_emxArray_int16_T
#define struct_emxArray_int16_T

struct emxArray_int16_T
{
  int16_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_int16_T*/

#ifndef typedef_emxArray_int16_T
#define typedef_emxArray_int16_T

typedef struct emxArray_int16_T emxArray_int16_T;

#endif                                 /*typedef_emxArray_int16_T*/

#ifndef typedef_cell_wrap_1
#define typedef_cell_wrap_1

typedef struct {
  emxArray_real32_T *f1;
} cell_wrap_1;

#endif                                 /*typedef_cell_wrap_1*/

#ifndef typedef_cell_wrap_2
#define typedef_cell_wrap_2

typedef struct {
  cell_wrap_1 f1[5];
} cell_wrap_2;

#endif                                 /*typedef_cell_wrap_2*/

#ifndef typedef_cell_wrap_3
#define typedef_cell_wrap_3

typedef struct {
  emxArray_boolean_T *f1;
} cell_wrap_3;

#endif                                 /*typedef_cell_wrap_3*/

#ifndef struct_emxArray_boolean_T_0x0
#define struct_emxArray_boolean_T_0x0

struct emxArray_boolean_T_0x0
{
  int32_T size[2];
};

#endif                                 /*struct_emxArray_boolean_T_0x0*/

#ifndef typedef_emxArray_boolean_T_0x0
#define typedef_emxArray_boolean_T_0x0

typedef struct emxArray_boolean_T_0x0 emxArray_boolean_T_0x0;

#endif                                 /*typedef_emxArray_boolean_T_0x0*/

#ifndef struct_emxArray_real_T_0
#define struct_emxArray_real_T_0

struct emxArray_real_T_0
{
  int32_T size[1];
};

#endif                                 /*struct_emxArray_real_T_0*/

#ifndef typedef_emxArray_real_T_0
#define typedef_emxArray_real_T_0

typedef struct emxArray_real_T_0 emxArray_real_T_0;

#endif                                 /*typedef_emxArray_real_T_0*/

#ifndef struct_emxArray_real_T_1x0
#define struct_emxArray_real_T_1x0

struct emxArray_real_T_1x0
{
  int32_T size[2];
};

#endif                                 /*struct_emxArray_real_T_1x0*/

#ifndef typedef_emxArray_real_T_1x0
#define typedef_emxArray_real_T_1x0

typedef struct emxArray_real_T_1x0 emxArray_real_T_1x0;

#endif                                 /*typedef_emxArray_real_T_1x0*/

#ifndef typedef_c_struct_T
#define typedef_c_struct_T

typedef struct {
  real_T Area;
  real_T Centroid[2];
  real_T BoundingBox[4];
  real_T MajorAxisLength;
  real_T MinorAxisLength;
  real_T Eccentricity;
  real_T Orientation;
  emxArray_boolean_T_0x0 Image;
  emxArray_boolean_T_0x0 FilledImage;
  real_T FilledArea;
  real_T EulerNumber;
  real_T Extrema[16];
  real_T EquivDiameter;
  real_T Extent;
  emxArray_real_T *PixelIdxList;
  emxArray_real_T *PixelList;
  real_T Perimeter;
  real_T Circularity;
  emxArray_real_T_0 PixelValues;
  real_T WeightedCentroid[2];
  real_T MeanIntensity;
  real_T MinIntensity;
  real_T MaxIntensity;
  emxArray_real_T_1x0 SubarrayIdx;
  real_T SubarrayIdxLengths[2];
} c_struct_T;

#endif                                 /*typedef_c_struct_T*/

#ifndef typedef_b_emxArray_struct_T
#define typedef_b_emxArray_struct_T

typedef struct {
  c_struct_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
} b_emxArray_struct_T;

#endif                                 /*typedef_b_emxArray_struct_T*/

#ifndef typedef_struct8_T
#define typedef_struct8_T

typedef struct {
  boolean_T RegionSkinROIAttempted;
  emxArray_uint16_T_1x4 BBox_Scan_SkinAlg;
  boolean_T RegionAnyAvailable;
  emxArray_uint32_T_400x1 RegionNPixels_RejectedN;
  emxArray_boolean_T_400x1 RegionNPixels_RejectedLowNTF;
  emxArray_int16_T_1x2 RegionCentroids_SelectedXY;
  emxArray_int16_T_400x2 RegionCentroids_CandidateXY;
  emxArray_int16_T_400x2 RegionCentroids_RejectedXY;
  emxArray_uint16_T_1x2 PredictedROI_center;
  emxArray_uint8_T_1x1 RegionScores_SelectedRGBProb;
  emxArray_uint8_T_400x1 RegionScores_CandidateRGBProb;
  emxArray_uint8_T_400x1 RegionScores_RejectedRGBProb;
  emxArray_real32_T_1x3 RegionScores_SelectedYCbCrZ;
  emxArray_real32_T_400x3 RegionScores_CandidateYCbCrZ;
  emxArray_real32_T_400x3 RegionScores_RejectedYCbCrZ;
  emxArray_real32_T_400x1 RegionRankings_CandidateHi2Lo;
  emxArray_uint16_T_400x1 c_RegionCrSDScores_RejectedCrSD;
  emxArray_real32_T_400x1 RegionCrSDScores_RejectedCrSD;
  boolean_T ProportionSkinPixelsTooLow;
  emxArray_uint32_T *RegionBoundaries_SelectedLinIdx;
  emxArray_uint32_T *c_RegionBoundaries_CandidateLin;
  emxArray_uint32_T *RegionBoundaries_RejectedLinIdx;
} struct8_T;

#endif                                 /*typedef_struct8_T*/

#ifndef typedef_d_struct_T
#define typedef_d_struct_T

typedef struct {
  boolean_T RegionSkinROIAttempted;
  emxArray_uint16_T_1x4 BBox_Scan_SkinAlg;
  boolean_T RegionAnyAvailable;
  emxArray_uint32_T_400x1 RegionNPixels_RejectedN;
  emxArray_boolean_T_400x1 RegionNPixels_RejectedLowNTF;
  emxArray_int16_T_1x2 RegionCentroids_SelectedXY;
  emxArray_int16_T_400x2 RegionCentroids_CandidateXY;
  emxArray_int16_T_400x2 RegionCentroids_RejectedXY;
  emxArray_uint16_T_1x2 PredictedROI_center;
  emxArray_uint8_T_1x1 RegionScores_SelectedRGBProb;
  emxArray_uint8_T_400x1 RegionScores_CandidateRGBProb;
  emxArray_uint8_T_400x1 RegionScores_RejectedRGBProb;
  emxArray_real32_T_1x3 RegionScores_SelectedYCbCrZ;
  emxArray_real32_T_400x3 RegionScores_CandidateYCbCrZ;
  emxArray_real32_T_400x3 RegionScores_RejectedYCbCrZ;
  emxArray_real32_T_400x1 RegionRankings_CandidateHi2Lo;
  emxArray_uint16_T_400x1 c_RegionCrSDScores_RejectedCrSD;
  emxArray_real32_T_400x1 RegionCrSDScores_RejectedCrSD;
  boolean_T ProportionSkinPixelsTooLow;
  emxArray_uint32_T *RegionBoundaries_SelectedLinIdx;
  emxArray_uint32_T *c_RegionBoundaries_CandidateLin;
  emxArray_uint32_T *RegionBoundaries_RejectedLinIdx;
} d_struct_T;

#endif                                 /*typedef_d_struct_T*/

#ifndef typedef_struct7_T
#define typedef_struct7_T

typedef struct {
  boolean_T SetTF;
  real_T SkinColorSamples_NThreshold;
  boolean_T c_SkinColorSamples_NThresholdPa;
  real_T SkinColorSamples_HighNThreshold;
  boolean_T b_SkinColorSamples_HighNThresho;
  int32_T c_SkinColorSamples_HighNThresho;
  real32_T ColorThreshold[3];
  real32_T ColorThresholdHighN[3];
  int32_T RecentThresholdOpsFrameIdx;
  int32_T ThresholdOpsInterval;
  boolean_T ThresholdOpsRunCurrentFrameTF;
  real32_T ColorSDThreshold;
  real_T RGBProbTheta[4];
  real32_T YCbCrMeanOfMeans[3];
  real32_T YCbCrStdDevOfMeans[3];
  real32_T RegionNThreshold;
} struct7_T;

#endif                                 /*typedef_struct7_T*/

#ifndef typedef_struct6_T
#define typedef_struct6_T

typedef struct {
  boolean_T ROISkinTF;
  struct7_T Thresholds;
  int32_T ROISkinSkipFrameThreshold;
  int32_T c_ROISkin_BoundingBoxGrowthThre;
  real_T ROISkin_BoundingBoxGrowthFactor;
  real_T ROISkin_InitialBoundingBoxScale;
  real32_T ROISkinRegionMinSizeFactor;
  real_T ROISkinRegionProximityWeight;
  real_T ROISkinSmoothingWindow;
  int16_T PartitionColInterval;
  int16_T PartitionRowInterval;
  boolean_T SkinDetectionReadyTF;
  real_T c_ROISkin_BoundingBoxEnlargemen;
  int32_T c_ROISkinSkipFrameThreshold_adj;
  boolean_T UseCompiledFunctionsTF;
} struct6_T;

#endif                                 /*typedef_struct6_T*/

#ifndef typedef_struct1_T
#define typedef_struct1_T

typedef struct {
  boolean_T c_SkinColorSamples_NThresholdPa;
  real32_T YCbCrThresholdsGeneric[7];
  real32_T HSThresholdsGeneric[2];
  real32_T YCbCrThresholdsTailored[8];
  real32_T YCbCrThresholdsTailored_Sev[8];
  real32_T HSThresholdsTailored[3];
  real32_T HSThresholdsTailored_Sev[3];
  int16_T RangeSEWidth;
  uint8_T RangeThreshold;
  int16_T MorphCloseSEMediumWidth_Tuned;
  int16_T MorphCloseSELargeWidth_Tuned;
} struct1_T;

#endif                                 /*typedef_struct1_T*/

#ifndef typedef_struct5_T
#define typedef_struct5_T

typedef struct {
  real_T ROIMinWidthProportion;
  real_T ROIMinHeightProportion;
  real_T ROIWidthResizeFactor;
  real_T ROIHeightResizeFactor;
  int32_T ROIFinalSmoothingWindows[2];
  int32_T ROISkipFrameThreshold_adjusted;
  int16_T ROIMSIR_DiffMaxDetection;
  int16_T ROIMSIR_DiffMaxAdjacent;
  int32_T ROIMSIR_FirstFrameIdx;
  int32_T FrameCacheMaxFrames;
  boolean_T c_ROIMeansOperationsReadyFirstR;
  int32_T c_ROIMeansMaxFrameToProcessSeco;
  emxArray_real_T *ROISpecifyByArgument;
  emxArray_real_T *ROIIgnoreByArgument;
  boolean_T RecursiveTF;
  boolean_T ReturnAllTF;
  boolean_T UseCompiledFunctionsTF;
} struct5_T;

#endif                                 /*typedef_struct5_T*/

#ifndef typedef_struct2_T
#define typedef_struct2_T

typedef struct {
  boolean_T OpsReadyTF;
  int32_T RecentThresholdOpsFrameIdx;
  int32_T ThresholdOpsInterval;
  boolean_T ThresholdOpsRunCurrentFrameTF;
  real_T SkinColorSamples_NThreshold;
  real_T RangePercentile_YCbCrH[2];
  real_T RangePercentile_S[2];
  real_T SkinColorSamples_HighNThreshold;
  boolean_T b_SkinColorSamples_HighNThresho;
  real_T RangePercentileHighN_YCbCrH[2];
  real_T RangePercentileHighN_S[2];
  real_T RangePercentileSev_YCbCrH[2];
  real_T RangePercentileSev_S[2];
} struct2_T;

#endif                                 /*typedef_struct2_T*/

#ifndef typedef_struct4_T
#define typedef_struct4_T

typedef struct {
  boolean_T CheckTF;
  real32_T ProportionThresholdPrimary;
  real32_T ProportionThresholdSecondary1;
  real32_T ProportionThresholdSecondary2;
  real_T c_FramesLowSkinProportionThresh;
  real_T NFramesLowSkinProportionStatus;
  real_T MorphReductionAmount;
  int32_T NMorphReductionLimit;
  int32_T NMorphReductions;
  real32_T DarknessThreshold;
  boolean_T BelowDarknessThresholdTF;
  real32_T NFramesYSingleMean;
  boolean_T PixelColorsAdjustedTF;
  real32_T ColorThresAdjustTo[9];
} struct4_T;

#endif                                 /*typedef_struct4_T*/

#ifndef typedef_struct0_T
#define typedef_struct0_T

typedef struct {
  boolean_T SkinSegmentTF;
  real_T SkinSegmentSeverityFactor;
  real_T MorphCloseSEMediumWidth;
  real_T MorphCloseSELargeWidth;
  boolean_T UseCompiledFunctionsTF;
  struct1_T Args;
  struct2_T TailoredData;
  struct3_T ConfirmSkin;
  struct4_T OverSegmentedCheck;
} struct0_T;

#endif                                 /*typedef_struct0_T*/

/* End of code generation (SkinDetect_types.h) */
