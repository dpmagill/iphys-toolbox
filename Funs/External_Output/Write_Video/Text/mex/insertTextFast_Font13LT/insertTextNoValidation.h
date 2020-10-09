/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertTextNoValidation.h
 *
 * Code generation for function 'insertTextNoValidation'
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
#include "insertTextFast_Font13LT_types.h"

/* Function Declarations */
void getTextboxWidthHeight(const emxArray_uint16_T *ucTextU16, int32_T *tbWidth,
  int32_T *tbHeight);
void insertGlyphs(emxArray_uint8_T *imgIn, const emxArray_uint16_T *ucTextU16,
                  int32_T textLocationXY_x, int32_T textLocationXY_y, const
                  uint8_T textColor_data[]);

/* End of code generation (insertTextNoValidation.h) */
