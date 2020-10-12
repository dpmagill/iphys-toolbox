/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertShapeNoValidation.h
 *
 * Code generation for function 'insertShapeNoValidation'
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
#include "insertShapeFast_FilledCircles_types.h"

/* Function Declarations */
void validateAndParseInputs(const int16_T position_data[], const int32_T
  position_size[2], int32_T positionOut_data[], int32_T positionOut_size[2],
  uint8_T colorOut_data[], int32_T colorOut_size[2]);

/* End of code generation (insertShapeNoValidation.h) */
