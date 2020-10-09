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
#include "insertTextFast_PulseRate13_types.h"

/* Function Declarations */
void getTextboxWidthHeight(const uint16_T ucTextU16_data[], const int32_T
  ucTextU16_size[2], int32_T *tbWidth, int32_T *tbHeight);
void insertGlyphs(uint8_T imgIn[50025], const uint16_T ucTextU16_data[], const
                  int32_T ucTextU16_size[2]);
void validateAndParseInputs(const real_T position[2], const char_T text_data[],
  const int32_T text_size[2], const real_T varargin_6[3], int32_T b_position[2],
  cell_wrap_0 outText[1], uint8_T boxColor[3]);

/* End of code generation (insertTextNoValidation.h) */
