/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * WriteFaceVideo_MaskOverlay.h
 *
 * Code generation for function 'WriteFaceVideo_MaskOverlay'
 *
 */

#pragma once

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mex.h"
#include "emlrt.h"
#include "rtwtypes.h"
#include "WriteFaceVideo_MaskOverlay_types.h"

/* Function Declarations */
void WriteFaceVideo_MaskOverlay(emxArray_uint8_T *VidFrameROI, real32_T
  Transparency, const emxArray_boolean_T *IsSkinMask_Inverted, const real_T
  Color[3], uint16_T nRows, uint16_T nCols);

/* End of code generation (WriteFaceVideo_MaskOverlay.h) */
