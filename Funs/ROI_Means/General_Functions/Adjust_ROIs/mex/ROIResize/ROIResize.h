/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIResize.h
 *
 * Code generation for function 'ROIResize'
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
#include "ROIResize_types.h"

/* Function Declarations */
void ROIResize(const emxArray_int16_T *ROI, const emxArray_int32_T
               *ROIsToResizeLinIdx, real_T ROIWidthResizeFactor, real_T
               ROIHeightResizeFactor, int16_T VidObjWidth, int16_T VidObjHeight,
               emxArray_int16_T *b_ROIResize);

/* End of code generation (ROIResize.h) */
