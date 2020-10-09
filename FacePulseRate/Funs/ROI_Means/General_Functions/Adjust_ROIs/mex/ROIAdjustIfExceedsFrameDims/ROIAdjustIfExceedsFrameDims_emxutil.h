/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIAdjustIfExceedsFrameDims_emxutil.h
 *
 * Code generation for function 'ROIAdjustIfExceedsFrameDims_emxutil'
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
#include "ROIAdjustIfExceedsFrameDims_types.h"

/* Function Declarations */
void emxEnsureCapacity_int16_T(emxArray_int16_T *emxArray, int32_T oldNumel);
void emxFree_int16_T(emxArray_int16_T **pEmxArray);
void emxInit_int16_T(emxArray_int16_T **pEmxArray, int32_T numDimensions,
                     boolean_T doPush);

/* End of code generation (ROIAdjustIfExceedsFrameDims_emxutil.h) */
