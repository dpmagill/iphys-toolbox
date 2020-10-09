/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ConfirmSkinPresent_SkinDetectReject_types.h
 *
 * Code generation for function 'ConfirmSkinPresent_SkinDetectReject_types'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
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

#ifndef typedef_struct1_T
#define typedef_struct1_T

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
} struct1_T;

#endif                                 /*typedef_struct1_T*/

#ifndef typedef_struct0_T
#define typedef_struct0_T

typedef struct {
  boolean_T ROISkinTF;
  struct1_T Thresholds;
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
} struct0_T;

#endif                                 /*typedef_struct0_T*/

/* End of code generation (ConfirmSkinPresent_SkinDetectReject_types.h) */
