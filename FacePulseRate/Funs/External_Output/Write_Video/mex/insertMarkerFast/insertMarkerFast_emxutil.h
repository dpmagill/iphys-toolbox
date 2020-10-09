/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertMarkerFast_emxutil.h
 *
 * Code generation for function 'insertMarkerFast_emxutil'
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
#include "insertMarkerFast_types.h"

/* Function Declarations */
void emxEnsureCapacity_uint8_T(emxArray_uint8_T *emxArray, int32_T oldNumel);
void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
void emxInit_uint8_T(emxArray_uint8_T **pEmxArray, int32_T numDimensions,
                     boolean_T doPush);

/* End of code generation (insertMarkerFast_emxutil.h) */
