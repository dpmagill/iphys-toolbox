/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imerode.h
 *
 * Code generation for function 'imerode'
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
#include "omp.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_types.h"

/* Function Declarations */
void b_imerode(const emxArray_uint32_T *A, real_T varargin_2, emxArray_uint32_T *
               B);
void imerode(const emxArray_uint32_T *A, real_T varargin_2, emxArray_uint32_T *B);

/* End of code generation (imerode.h) */
