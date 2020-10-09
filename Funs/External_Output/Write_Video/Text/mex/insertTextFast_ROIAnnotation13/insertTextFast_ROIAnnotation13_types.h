/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertTextFast_ROIAnnotation13_types.h
 *
 * Code generation for function 'insertTextFast_ROIAnnotation13_types'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_char_T_1x125
#define struct_emxArray_char_T_1x125

struct emxArray_char_T_1x125
{
  char_T data[125];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_char_T_1x125*/

#ifndef typedef_emxArray_char_T_1x125
#define typedef_emxArray_char_T_1x125

typedef struct emxArray_char_T_1x125 emxArray_char_T_1x125;

#endif                                 /*typedef_emxArray_char_T_1x125*/

#ifndef typedef_cell_wrap_0
#define typedef_cell_wrap_0

typedef struct {
  emxArray_char_T_1x125 f1;
} cell_wrap_0;

#endif                                 /*typedef_cell_wrap_0*/

/* End of code generation (insertTextFast_ROIAnnotation13_types.h) */
