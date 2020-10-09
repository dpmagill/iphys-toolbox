/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * regionprops.h
 *
 * Code generation for function 'regionprops'
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
void regionprops(const real_T varargin_1_ImageSize[2], real_T
                 varargin_1_NumObjects, const emxArray_real_T
                 *varargin_1_RegionIndices, const emxArray_int32_T
                 *varargin_1_RegionLengths, emxArray_struct_T *outstats);

/* End of code generation (regionprops.h) */
