/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imdilate.h
 *
 * Code generation for function 'imdilate'
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
void b_imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B);
void c_imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B);
void d_imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B);
void imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B);

/* End of code generation (imdilate.h) */
