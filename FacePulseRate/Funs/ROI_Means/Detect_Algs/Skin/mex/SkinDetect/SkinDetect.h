/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect.h
 *
 * Code generation for function 'SkinDetect'
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
void SkinDetect(int32_T i, const emxArray_uint8_T *VidFrame, int16_T
                VideoReadConfig_VidObjWidth, int16_T
                VideoReadConfig_VidObjHeight, const struct0_T *SkinSegmentConfig,
                const struct5_T *ROIGeneralConfig, const struct6_T
                *SkinDetectConfig, boolean_T c_OutputConfig_WriteVideoShowRO,
                const int16_T BoundingBoxSkin[4], boolean_T FirstReadSkinTF,
                const int16_T ROIForBoundingBoxSkin_FR[4], const int16_T
                ROI_SR_ith_data[], const int32_T ROI_SR_ith_size[2], const
                emxArray_int32_T *FramesToProcessLinIdx_SR, int32_T
                Notifications_Interval_SR, uint64_T
                Notifications_LoopStartTime_SR, int32_T
                Notifications_LoopCounter_SR, int16_T ROI_Selected_ith_data[],
                int32_T ROI_Selected_ith_size[2], boolean_T *SkinTF_ith,
                boolean_T *HasROITF_SkinNotPresent_ith, struct8_T
                *ROIDiagnostic_ROISkin_ith, uint32_T *LoopCounter);
emlrtCTX emlrtGetRootTLSGlobal(void);
void emlrtLockerFunction(EmlrtLockeeFunction aLockee, const emlrtConstCTX aTLS,
  void *aData);

/* End of code generation (SkinDetect.h) */
