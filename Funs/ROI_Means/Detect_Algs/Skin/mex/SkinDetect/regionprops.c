/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * regionprops.c
 *
 * Code generation for function 'regionprops'
 *
 */

/* Include files */
#include "regionprops.h"
#include "SkinDetect_data.h"
#include "SkinDetect_emxutil.h"
#include "SkinDetect_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Declarations */
static int32_T div_s32(int32_T numerator, int32_T denominator);

/* Function Definitions */
static int32_T div_s32(int32_T numerator, int32_T denominator)
{
  int32_T quotient;
  uint32_T b_denominator;
  uint32_T b_numerator;
  if (denominator == 0) {
    emlrtDivisionByZeroErrorR2012b(NULL, emlrtRootTLSGlobal);
  } else {
    if (numerator < 0) {
      b_numerator = ~(uint32_T)numerator + 1U;
    } else {
      b_numerator = (uint32_T)numerator;
    }

    if (denominator < 0) {
      b_denominator = ~(uint32_T)denominator + 1U;
    } else {
      b_denominator = (uint32_T)denominator;
    }

    b_numerator /= b_denominator;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -(int32_T)b_numerator;
    } else {
      quotient = (int32_T)b_numerator;
    }
  }

  return quotient;
}

void regionprops(const real_T varargin_1_ImageSize[2], real_T
                 varargin_1_NumObjects, const emxArray_real_T
                 *varargin_1_RegionIndices, const emxArray_int32_T
                 *varargin_1_RegionLengths, emxArray_struct_T *outstats)
{
  b_emxArray_struct_T *stats;
  c_struct_T statsOneObj;
  emxArray_int32_T *v1;
  emxArray_int32_T *vk;
  struct_T s;
  real_T y_idx_0;
  real_T y_idx_1;
  int32_T idxCount_data[401];
  int32_T b_k;
  int32_T i;
  int32_T i1;
  int32_T k;
  int32_T xpageoffset;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  s.Centroid[0] = 0.0;
  s.Centroid[1] = 0.0;
  i = outstats->size[0];
  outstats->size[0] = (int32_T)varargin_1_NumObjects;
  emxEnsureCapacity_struct_T1(outstats, i);
  xpageoffset = (int32_T)varargin_1_NumObjects;
  for (i = 0; i < xpageoffset; i++) {
    outstats->data[i] = s;
  }

  emxInitStruct_struct_T2(&statsOneObj, true);
  statsOneObj.Area = 0.0;
  statsOneObj.Centroid[0] = 0.0;
  statsOneObj.Centroid[1] = 0.0;
  statsOneObj.BoundingBox[0] = 0.0;
  statsOneObj.BoundingBox[1] = 0.0;
  statsOneObj.BoundingBox[2] = 0.0;
  statsOneObj.BoundingBox[3] = 0.0;
  statsOneObj.MajorAxisLength = 0.0;
  statsOneObj.MinorAxisLength = 0.0;
  statsOneObj.Eccentricity = 0.0;
  statsOneObj.Orientation = 0.0;
  statsOneObj.Image.size[0] = 0;
  statsOneObj.Image.size[1] = 0;
  statsOneObj.FilledImage.size[0] = 0;
  statsOneObj.FilledImage.size[1] = 0;
  statsOneObj.FilledArea = 0.0;
  statsOneObj.EulerNumber = 0.0;
  memset(&statsOneObj.Extrema[0], 0, 16U * sizeof(real_T));
  emxInit_struct_T1(&stats, 1, true);
  statsOneObj.EquivDiameter = 0.0;
  statsOneObj.Extent = 0.0;
  statsOneObj.PixelIdxList->size[0] = 0;
  statsOneObj.PixelList->size[0] = 0;
  statsOneObj.PixelList->size[1] = 2;
  statsOneObj.Perimeter = 0.0;
  statsOneObj.Circularity = 0.0;
  statsOneObj.PixelValues.size[0] = 0;
  statsOneObj.MeanIntensity = 0.0;
  statsOneObj.MinIntensity = 0.0;
  statsOneObj.MaxIntensity = 0.0;
  statsOneObj.SubarrayIdx.size[0] = 1;
  statsOneObj.SubarrayIdx.size[1] = 0;
  statsOneObj.WeightedCentroid[0] = 0.0;
  statsOneObj.SubarrayIdxLengths[0] = 0.0;
  statsOneObj.WeightedCentroid[1] = 0.0;
  statsOneObj.SubarrayIdxLengths[1] = 0.0;
  i = stats->size[0];
  stats->size[0] = (int32_T)varargin_1_NumObjects;
  emxEnsureCapacity_struct_T2(stats, i);
  xpageoffset = (int32_T)varargin_1_NumObjects;
  for (i = 0; i < xpageoffset; i++) {
    emxCopyStruct_struct_T(&stats->data[i], &statsOneObj);
  }

  emxFreeStruct_struct_T2(&statsOneObj);
  emxInit_int32_T(&v1, 1, true);
  if (varargin_1_NumObjects != 0.0) {
    i = v1->size[0];
    v1->size[0] = varargin_1_RegionLengths->size[0];
    emxEnsureCapacity_int32_T(v1, i);
    xpageoffset = varargin_1_RegionLengths->size[0];
    for (i = 0; i < xpageoffset; i++) {
      v1->data[i] = varargin_1_RegionLengths->data[i];
    }

    if ((varargin_1_RegionLengths->size[0] != 1) &&
        (varargin_1_RegionLengths->size[0] != 0) &&
        (varargin_1_RegionLengths->size[0] != 1)) {
      i = varargin_1_RegionLengths->size[0];
      for (k = 0; k <= i - 2; k++) {
        v1->data[k + 1] += v1->data[k];
      }
    }

    idxCount_data[0] = 0;
    xpageoffset = v1->size[0];
    for (i = 0; i < xpageoffset; i++) {
      idxCount_data[i + 1] = v1->data[i];
    }

    i = (int32_T)varargin_1_NumObjects;
    for (k = 0; k < i; k++) {
      i1 = idxCount_data[k + 1];
      b_k = idxCount_data[k];
      if (b_k + 1 > i1) {
        b_k = 0;
        i1 = 0;
      }

      xpageoffset = i1 - b_k;
      i1 = stats->data[k].PixelIdxList->size[0];
      stats->data[k].PixelIdxList->size[0] = xpageoffset;
      emxEnsureCapacity_real_T(stats->data[k].PixelIdxList, i1);
      for (i1 = 0; i1 < xpageoffset; i1++) {
        stats->data[k].PixelIdxList->data[i1] = varargin_1_RegionIndices->
          data[b_k + i1];
      }
    }
  }

  i = stats->size[0];
  emxInit_int32_T(&vk, 1, true);
  for (k = 0; k < i; k++) {
    xpageoffset = stats->data[k].PixelIdxList->size[0];
    if (stats->data[k].PixelIdxList->size[0] != 0) {
      i1 = v1->size[0];
      v1->size[0] = stats->data[k].PixelIdxList->size[0];
      emxEnsureCapacity_int32_T(v1, i1);
      for (i1 = 0; i1 < xpageoffset; i1++) {
        v1->data[i1] = (int32_T)stats->data[k].PixelIdxList->data[i1] - 1;
      }

      i1 = vk->size[0];
      vk->size[0] = v1->size[0];
      emxEnsureCapacity_int32_T(vk, i1);
      xpageoffset = v1->size[0];
      for (i1 = 0; i1 < xpageoffset; i1++) {
        vk->data[i1] = div_s32(v1->data[i1], (int32_T)varargin_1_ImageSize[0]);
      }

      xpageoffset = v1->size[0];
      for (i1 = 0; i1 < xpageoffset; i1++) {
        v1->data[i1] -= vk->data[i1] * (int32_T)varargin_1_ImageSize[0];
      }

      i1 = stats->data[k].PixelList->size[0] * stats->data[k].PixelList->size[1];
      stats->data[k].PixelList->size[0] = vk->size[0];
      stats->data[k].PixelList->size[1] = 2;
      emxEnsureCapacity_real_T(stats->data[k].PixelList, i1);
      xpageoffset = vk->size[0];
      for (i1 = 0; i1 < xpageoffset; i1++) {
        stats->data[k].PixelList->data[i1] = vk->data[i1] + 1;
      }

      xpageoffset = v1->size[0];
      for (i1 = 0; i1 < xpageoffset; i1++) {
        stats->data[k].PixelList->data[i1 + stats->data[k].PixelList->size[0]] =
          v1->data[i1] + 1;
      }
    } else {
      stats->data[k].PixelList->size[0] = 0;
      stats->data[k].PixelList->size[1] = 2;
    }
  }

  emxFree_int32_T(&vk);
  emxFree_int32_T(&v1);
  i = stats->size[0];
  for (k = 0; k < i; k++) {
    i1 = stats->data[k].PixelList->size[0];
    if (stats->data[k].PixelList->size[0] == 0) {
      y_idx_0 = 0.0;
      y_idx_1 = 0.0;
    } else {
      y_idx_0 = (int32_T)stats->data[k].PixelList->data[0];
      for (b_k = 2; b_k <= i1; b_k++) {
        y_idx_0 += (real_T)(int32_T)stats->data[k].PixelList->data[b_k - 1];
      }

      xpageoffset = stats->data[k].PixelList->size[0];
      y_idx_1 = (int32_T)stats->data[k].PixelList->data[xpageoffset];
      for (b_k = 2; b_k <= i1; b_k++) {
        y_idx_1 += (real_T)(int32_T)stats->data[k].PixelList->data[(xpageoffset
          + b_k) - 1];
      }
    }

    stats->data[k].Centroid[0] = y_idx_0 / (real_T)stats->data[k]
      .PixelList->size[0];
    stats->data[k].Centroid[1] = y_idx_1 / (real_T)stats->data[k]
      .PixelList->size[0];
  }

  i = stats->size[0];
  for (k = 0; k < i; k++) {
    outstats->data[k].Centroid[0] = stats->data[k].Centroid[0];
    outstats->data[k].Centroid[1] = stats->data[k].Centroid[1];
  }

  emxFree_struct_T1(&stats);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (regionprops.c) */
