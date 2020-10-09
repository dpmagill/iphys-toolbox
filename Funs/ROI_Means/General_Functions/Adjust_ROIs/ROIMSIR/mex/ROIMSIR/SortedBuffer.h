/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SortedBuffer.h
 *
 * Code generation for function 'SortedBuffer'
 *
 */

#pragma once

/* Include files */
#include "ROIMSIR_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void SortedBuffer_insert(coder_internal_SortedBuffer *obj, int16_T x);
int32_T SortedBuffer_locateElement(const emxArray_int16_T *obj_buf, int32_T
  obj_nbuf, int16_T x);
int16_T SortedBuffer_median(const emxArray_int16_T *obj_buf, int32_T obj_nbuf);
void SortedBuffer_replace(coder_internal_SortedBuffer *obj, int16_T xold,
  int16_T xnew);

/* End of code generation (SortedBuffer.h) */
