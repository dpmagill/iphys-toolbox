/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect_RegionBoundariesByCategory.h
 *
 * Code generation for function 'SkinDetect_RegionBoundariesByCategory'
 *
 */

#pragma once

/* Include files */
#include "SkinDetect_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void c_SkinDetect_RegionBoundariesBy(emlrtCTX aTLS, boolean_T
  RegionSelectedAnyTF, uint16_T NRegionsCandidate, uint16_T NRegionsRejected,
  const uint16_T RegionSelectedLinIdx_data[], const b_struct_T
  RegionIndices_data[], const uint16_T RegionsCandidateLinIdx_data[], const
  uint16_T RegionsRejectedLinIdx_data[], int16_T VidObjHeight, const int16_T
  BoundingBoxSkin[4], const real32_T RegionNPixels_data[], int16_T
  nRows_IsSkinMask, int16_T nCols_IsSkinMask, cell_wrap_32 RegionBoundaries[3]);

/* End of code generation (SkinDetect_RegionBoundariesByCategory.h) */
