/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIMSIR_types.h
 *
 * Code generation for function 'ROIMSIR'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef typedef_struct1_T
#define typedef_struct1_T

typedef struct {
  real32_T SumW_Pri;
  real32_T SumH_Pri;
  real32_T AlgN_Pri;
  real32_T ROIMeanWidthPri;
  real32_T ROIMeanHeightPri;
  real32_T SumW_Sec1;
  real32_T SumH_Sec1;
  real32_T AlgN_Sec1;
  real32_T ROIMeanWidthSec1;
  real32_T ROIMeanHeightSec1;
  real32_T SumW_Sec2;
  real32_T SumH_Sec2;
  real32_T AlgN_Sec2;
  real32_T ROIMeanWidthSec2;
  real32_T ROIMeanHeightSec2;
  real32_T SumW_Skin;
  real32_T SumH_Skin;
  real32_T AlgN_Skin;
  real32_T ROIMeanWidthSkin;
  real32_T ROIMeanHeightSkin;
} struct1_T;

#endif                                 /*typedef_struct1_T*/

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int32_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_int32_T*/

#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T

typedef struct emxArray_int32_T emxArray_int32_T;

#endif                                 /*typedef_emxArray_int32_T*/

#ifndef struct_emxArray_real32_T
#define struct_emxArray_real32_T

struct emxArray_real32_T
{
  real32_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real32_T*/

#ifndef typedef_emxArray_real32_T
#define typedef_emxArray_real32_T

typedef struct emxArray_real32_T emxArray_real32_T;

#endif                                 /*typedef_emxArray_real32_T*/

#ifndef struct_emxArray_char_T
#define struct_emxArray_char_T

struct emxArray_char_T
{
  char_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_char_T*/

#ifndef typedef_emxArray_char_T
#define typedef_emxArray_char_T

typedef struct emxArray_char_T emxArray_char_T;

#endif                                 /*typedef_emxArray_char_T*/

#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T

struct emxArray_boolean_T
{
  boolean_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_boolean_T*/

#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T

typedef struct emxArray_boolean_T emxArray_boolean_T;

#endif                                 /*typedef_emxArray_boolean_T*/

#ifndef struct_emxArray_int16_T
#define struct_emxArray_int16_T

struct emxArray_int16_T
{
  int16_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_int16_T*/

#ifndef typedef_emxArray_int16_T
#define typedef_emxArray_int16_T

typedef struct emxArray_int16_T emxArray_int16_T;

#endif                                 /*typedef_emxArray_int16_T*/

#ifndef typedef_coder_internal_SortedBuffer
#define typedef_coder_internal_SortedBuffer

typedef struct {
  emxArray_int16_T *buf;
  int32_T nbuf;
} coder_internal_SortedBuffer;

#endif                                 /*typedef_coder_internal_SortedBuffer*/

#ifndef typedef_struct0_T
#define typedef_struct0_T

typedef struct {
  emxArray_boolean_T *FacePrimary;
  emxArray_boolean_T *FacePrimaryAttempted;
  emxArray_boolean_T *SkinNotPresent_Pri;
  emxArray_boolean_T *ProfileEyesPresent_Pri;
  emxArray_boolean_T *FaceSecondary1;
  emxArray_boolean_T *FaceSecondary1Attempted;
  emxArray_boolean_T *SkinNotPresent_Sec1;
  emxArray_boolean_T *ProfileEyesPresent_Sec1;
  emxArray_boolean_T *FaceSecondary2;
  emxArray_boolean_T *FaceSecondary2Attempted;
  emxArray_boolean_T *SkinNotPresent_Sec2;
  emxArray_boolean_T *ProfileEyesPresent_Sec2;
  emxArray_boolean_T *Skipped;
  emxArray_boolean_T *Skin;
  emxArray_boolean_T *SkinAttempted;
  emxArray_boolean_T *SkinNotPresent_Skin;
  emxArray_boolean_T *Interpolated;
  emxArray_boolean_T *c_AdjustedBecauseLowSkinProport;
  emxArray_boolean_T *ROISpecifiedByArgument;
  emxArray_boolean_T *ROIIgnoreByArgument;
} struct0_T;

#endif                                 /*typedef_struct0_T*/

/* End of code generation (ROIMSIR_types.h) */
