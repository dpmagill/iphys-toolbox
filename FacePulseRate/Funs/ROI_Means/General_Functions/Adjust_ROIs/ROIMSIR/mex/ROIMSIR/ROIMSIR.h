/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIMSIR.h
 *
 * Code generation for function 'ROIMSIR'
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
void ROIMSIR(const emxArray_int32_T *BlockFullLinIdx_In, emxArray_int16_T *ROI,
             emxArray_real32_T *Timestamp, struct0_T *HasROI_TF, int16_T
             c_ROIGeneralConfig_ROIMSIR_Diff, int16_T
             d_ROIGeneralConfig_ROIMSIR_Diff, real_T
             c_ROIGeneralConfig_ROIWidthResi, real_T
             c_ROIGeneralConfig_ROIHeightRes, real_T
             c_FaceDetectConfig_ROIFaceSmoot, boolean_T
             c_FaceDetectConfig_ROIFaceSecon, boolean_T
             d_FaceDetectConfig_ROIFaceSecon, real_T
             c_SkinDetectConfig_ROISkinSmoot, const int32_T
             c_ROIGeneralConfig_ROIFinalSmoo[2], int16_T VidObjWidth, int16_T
             VidObjHeight, boolean_T ExpectedBehaviorTestTF, boolean_T
             FirstReadTF, boolean_T FirstCallTF, emxArray_int32_T
             *VideoReadConfig_FrameIdx_FR, int32_T RowToReturnFullLinIdx_FR,
             int32_T ROIMSIR_FirstFrameLinIdx_FR, emxArray_int16_T *ROINoMods,
             emxArray_int16_T *ROINoResize, struct1_T *ROIMatchSizeData,
             boolean_T SecondReadPostProcessingTF, int16_T ROIOut_FR[4],
             emxArray_int16_T *ROIOut_SR, int32_T *InterpolatedLinIdx_FR,
             emxArray_int32_T *InterpolatedLinIdx_SR, int16_T
             c_ROIOutBeforeFrameByFrameSmoot[4], emxArray_int16_T
             *d_ROIOutBeforeFrameByFrameSmoot, int16_T ROIOutNoResize_FR[4]);

/* End of code generation (ROIMSIR.h) */
