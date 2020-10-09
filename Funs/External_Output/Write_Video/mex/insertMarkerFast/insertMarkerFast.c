/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertMarkerFast.c
 *
 * Code generation for function 'insertMarkerFast'
 *
 */

/* Include files */
#include "insertMarkerFast.h"
#include "insertMarkerFast_data.h"
#include "insertMarkerFast_emxutil.h"
#include "insertMarkerUtilsCore_api.hpp"
#include "mwmathutil.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void insertMarkerFast(emxArray_uint8_T *FrameCropped_Markers, const int16_T
                      MarkerPointsXY_Cropped[4], real_T MarkerSize)
{
  emxArray_uint8_T *tmpRGB;
  int32_T i;
  int32_T loop_ub;
  int32_T position[4];
  uint8_T color[6];
  static const uint8_T colorRGB[6] = { 0U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    0U, MAX_uint8_T };

  int16_T numRow;
  int16_T numCol;
  uint8_T pixCount_data[32767];
  void* ptrObj;
  boolean_T isInitialise;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint8_T(&tmpRGB, 3, true);

  /* insertMarkerFast   Code-generation for function insertMarker for inserting green and white stars. */
  /*  */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by function WriteFaceVideo_SkinDetectDiagnosis. */
  /*  */
  /*     Code generation: This function intended only for code generation (C language). */
  /*  */
  /*     Compiled file: The compiled file included in folder FacePulseRate    */
  /*     (insertMarkerFast_mex.mexw64) only compatible on Windows platforms. */
  /* Specify inlining for faster code execution */
  /* Specify variable-size output arguments  */
  /*                                      Upp. Bounds     Var. Size (T/F) */
  /* Insert marker shapes to cropped frame */
  /* Note: function insertMarkerNoValidation is a custom version of function insertMarker with input */
  /* validation and unused options removed for efficiency. */
  /*  specify image where marker annotation inserted */
  /*  [X, Y] marker origins; Nmarkers-by-2 matrix */
  /*  marker type (star) */
  /*  colors of markers [green, white] */
  i = tmpRGB->size[0] * tmpRGB->size[1] * tmpRGB->size[2];
  tmpRGB->size[0] = FrameCropped_Markers->size[0];
  tmpRGB->size[1] = FrameCropped_Markers->size[1];
  tmpRGB->size[2] = 3;
  emxEnsureCapacity_uint8_T(tmpRGB, i);
  loop_ub = FrameCropped_Markers->size[0] * FrameCropped_Markers->size[1] *
    FrameCropped_Markers->size[2];
  for (i = 0; i < loop_ub; i++) {
    tmpRGB->data[i] = FrameCropped_Markers->data[i];
  }

  position[0] = MarkerPointsXY_Cropped[0];
  position[1] = MarkerPointsXY_Cropped[1];
  position[2] = MarkerPointsXY_Cropped[2];
  position[3] = MarkerPointsXY_Cropped[3];
  for (i = 0; i < 6; i++) {
    color[i] = colorRGB[i];
  }

  numRow = (int16_T)FrameCropped_Markers->size[0];
  numCol = (int16_T)FrameCropped_Markers->size[1];
  loop_ub = FrameCropped_Markers->size[1];
  i = FrameCropped_Markers->size[0] * FrameCropped_Markers->size[1] *
    FrameCropped_Markers->size[2];
  FrameCropped_Markers->size[1] = loop_ub;
  FrameCropped_Markers->size[2] = 3;
  emxEnsureCapacity_uint8_T(FrameCropped_Markers, i);
  if (numRow > numCol) {
    loop_ub = numRow;
  } else {
    loop_ub = numCol;
  }

  if (0 <= loop_ub - 1) {
    memset(&pixCount_data[0], 0, loop_ub * sizeof(uint8_T));
  }

  ptrObj = NULL;
  constructDrawBaseObjectMarker(&ptrObj);
  isInitialise = initialiseDrawbaseMarker(ptrObj, 0);
  if (!isInitialise) {
    instantiateDrawBaseMarker_uint8(ptrObj, &FrameCropped_Markers->data[0],
      &tmpRGB->data[0], position, color, 0.6, 4, (int32_T)muDoubleScalarRound
      (MarkerSize), numRow, numCol, 3, 2, 2, 2, 2, &pixCount_data[0], 0);
  }

  isInitialise = initialiseDrawbaseMarker(ptrObj, 1);
  if (!isInitialise) {
    instantiateDrawBaseMarker_uint8(ptrObj, &FrameCropped_Markers->data[0],
      &tmpRGB->data[0], position, color, 0.6, 4, (int32_T)muDoubleScalarRound
      (MarkerSize), numRow, numCol, 3, 2, 2, 2, 2, &pixCount_data[0], 1);
  }

  emxFree_uint8_T(&tmpRGB);
  deallocateMemoryMarker(ptrObj);

  /*    size of markers */
  /* end function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (insertMarkerFast_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Modify function files for performance %%%%%% */
  /*  */
  /* Before running code generation, input validation was removed from the file for function  */
  /* insertMarker. The modified file was saved as insertMarkerNoValidation.p, which is located in  */
  /* folder 'Validation_Removed'. The code is obscured (as p-code) to comply with the Matlab licensing  */
  /* agreement, which does not permit the distribution of Matlab source code. To permit code generation  */
  /* from the p-code, the statement coder.allowpcode('plain') was included in  */
  /* insertMarkerNoValidation.m before obfuscation. DPM possesses the un-obfuscated files. */
  /*  */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /*                                           Example Code                  Upp. Bounds      Var. Size (T/F)  Type */
  /* FrameCropped_MarkersCode   = coder.typeof( zeros(500, 500, 3, 'uint8'),  [inf, inf, 3],   [1, 1, 0] );     %uint8 */
  /*                      */
  /*  */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /* MarkerPointsXY_CroppedCode = zeros(2, 2, 'int16');                                             */
  /* MarkerSizeCode             = double(1);                                                                   */
  /*  */
  /*  */
  /* %%%%% Set configurations to increase performance %%%%%% */
  /*  */
  /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
  /* "Optimization Strategies" */
  /*  */
  /* cfg = coder.config('mex'); */
  /* cfg.GlobalDataSyncMethod = 'NoSync'; */
  /* cfg.ConstantInputs = 'IgnoreValues'; */
  /* cfg.ExtrinsicCalls = false; */
  /* cfg.SaturateOnIntegerOverflow = false; */
  /* cfg.IntegrityChecks = false; */
  /* cfg.ResponsivenessChecks = false; */
  /*  */
  /*  */
  /* %%%%% Specify flags to minGW compiler to optimize execution speed %%%%%% */
  /*  */
  /* For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html */
  /*  */
  /* The flags are specified as part of the code-generation configuration object. A custom function, */
  /* setbuildargs, is used to specify these flags. For details on the function implementation, see the  */
  /* function file, which is located within folder FacePulseRate. This custom function is based upon  */
  /* Matlab guidance found in */
  /* https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function */
  /*  */
  /* setbuildargs will be evaluated from text within the code-generation object, so it is converted to  */
  /* a character vector prior to execution of the codegen command. */
  /*  */
  /* %%%%% --- Specify the flags as arguments to function setbuildargs %%%%%% */
  /*  */
  /* Argument buildInfo: this variable is assign by the caller (the codegen command executed below) and  */
  /* is not present in the base workspace. */
  /*  */
  /* Second argument: specify a cell array of compiler-specific flags, where each flag is a character  */
  /* vector. As function setbuildargs will be evaluated from text, use double ' quotes for each   */
  /* character vector to maintain the charater vector, */
  /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
  /*  */
  /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})'; */
  /*  */
  /* Assign to code-generation configuration object */
  /* cfg.PostCodeGenCommand = setbuildargsAsText; */
  /*  */
  /*  */
  /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
  /*  */
  /* codegen insertMarkerFast.m -report -config cfg -args {FrameCropped_MarkersCode, MarkerPointsXY_CroppedCode, MarkerSizeCode} */
  /*  */
  /* } */
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (insertMarkerFast.c) */
