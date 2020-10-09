/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertShapeFast_FilledCircles.c
 *
 * Code generation for function 'insertShapeFast_FilledCircles'
 *
 */

/* Include files */
#include "insertShapeFast_FilledCircles.h"
#include "insertShapeFast_FilledCircles_data.h"
#include "insertShapeFast_FilledCircles_emxutil.h"
#include "insertShapeNoValidation.h"
#include "insertShapeUtilsCore_api.hpp"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void insertShapeFast_FilledCircles(emxArray_uint8_T *FrameCropped_BulletPoints,
  const int16_T BulletPointsXYR_Cropped_data[], const int32_T
  BulletPointsXYR_Cropped_size[2])
{
  emxArray_uint8_T *tmpRGB;
  int32_T i;
  int32_T loop_ub;
  int32_T positionOut_data[150];
  int32_T positionOut_size[2];
  uint8_T color_data[150];
  int32_T color_size[2];
  int16_T numRow;
  int16_T numCol;
  int16_T dimens1;
  int16_T numFillColor;
  int16_T pixCountSize;
  uint8_T pixCount_data[32767];
  void* ptrObj;
  void* posPtr;
  boolean_T isInitialise;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint8_T(&tmpRGB, 3, true);

  /* insertShapeFast_FilledCircles    Code generation for function insertShape for inserting black */
  /*                                  filled circles. */
  /*  */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by function WriteFaceVideo_SkinDetectDiagnosis. */
  /*  */
  /*     Code generation: This function intended only for code generation (C language). */
  /*  */
  /*     Compiled file:  */
  /*  */
  /*      - The compiled file included in folder FacePulseRate     */
  /*        (insertShapeFast_FilledCircles_mex.mexw64) only compatible on Windows platforms.  */
  /*      - This function uses a bounded variable size for variable BulletPointsXYR_Cropped to improve   */
  /*        efficiency. Ensure that this variable does not exceed these bounds. */
  /* Specify inlining for faster code execution */
  /* Specify variable-size output arguments  */
  /* For variable 'bulletpointPointsXY', set a bound on the number of rows (which corresponds to the */
  /* number of bullet points) to prevent dynamic memory allocation, which should increase performance. */
  /*                                            Upp. Bounds     Var. Size (T/F) */
  /* Insert filled circles (bullet points) corresponding to the positions of the text labels */
  /* Note: function insertShapeNoValidation is a custom version of function insertShape with input */
  /* validation and unused options removed for efficiency. */
  /*  specify image where shape annotation inserted */
  /*  shape */
  /*  M-by-3 matrix; row = [X, Y, radius] */
  /*  shape color: black */
  /*  opacity of 1 is a solid color */
  i = tmpRGB->size[0] * tmpRGB->size[1] * tmpRGB->size[2];
  tmpRGB->size[0] = FrameCropped_BulletPoints->size[0];
  tmpRGB->size[1] = FrameCropped_BulletPoints->size[1];
  tmpRGB->size[2] = 3;
  emxEnsureCapacity_uint8_T(tmpRGB, i);
  loop_ub = FrameCropped_BulletPoints->size[0] * FrameCropped_BulletPoints->
    size[1] * FrameCropped_BulletPoints->size[2];
  for (i = 0; i < loop_ub; i++) {
    tmpRGB->data[i] = FrameCropped_BulletPoints->data[i];
  }

  validateAndParseInputs(BulletPointsXYR_Cropped_data,
    BulletPointsXYR_Cropped_size, positionOut_data, positionOut_size, color_data,
    color_size);
  numRow = (int16_T)tmpRGB->size[0];
  numCol = (int16_T)tmpRGB->size[1];
  i = FrameCropped_BulletPoints->size[0] * FrameCropped_BulletPoints->size[1] *
    FrameCropped_BulletPoints->size[2];
  FrameCropped_BulletPoints->size[0] = tmpRGB->size[0];
  FrameCropped_BulletPoints->size[1] = tmpRGB->size[1];
  FrameCropped_BulletPoints->size[2] = 3;
  emxEnsureCapacity_uint8_T(FrameCropped_BulletPoints, i);
  dimens1 = (int16_T)positionOut_size[0];
  numFillColor = (int16_T)color_size[0];
  if ((int16_T)tmpRGB->size[0] > (int16_T)tmpRGB->size[1]) {
    pixCountSize = (int16_T)tmpRGB->size[0];
  } else {
    pixCountSize = (int16_T)tmpRGB->size[1];
  }

  loop_ub = pixCountSize;
  if (0 <= loop_ub - 1) {
    memset(&pixCount_data[0], 0, loop_ub * sizeof(uint8_T));
  }

  ptrObj = NULL;
  constructDrawBaseObjectShape(&ptrObj);
  posPtr = NULL;
  getPositionDataPointer(&posPtr, &positionOut_data[0], (uint32_T)
    positionOut_size[0], 3U);
  isInitialise = initialiseDrawbaseShape(ptrObj, 0, 4);
  if (!isInitialise) {
    instantiateDrawBaseShape_uint8(ptrObj, &FrameCropped_BulletPoints->data[0],
      &tmpRGB->data[0], posPtr, &color_data[0], 1.0, 1, 4, false, numRow, numCol,
      3, 2, dimens1, 3, numFillColor, true, false, &pixCount_data[0], 0);
  }

  isInitialise = initialiseDrawbaseShape(ptrObj, 1, 4);
  if (!isInitialise) {
    instantiateDrawBaseShape_uint8(ptrObj, &FrameCropped_BulletPoints->data[0],
      &tmpRGB->data[0], posPtr, &color_data[0], 1.0, 1, 4, false, numRow, numCol,
      3, 2, dimens1, 3, numFillColor, true, true, &pixCount_data[0], 1);
  }

  emxFree_uint8_T(&tmpRGB);
  mDrawShapes(ptrObj, true, false, 4, 1, (int32_T)numRow, (int32_T)numCol);
  deallocateMemoryShape(ptrObj);
  deletePositionDataPointer(posPtr);

  /*    disable anti-aliasing filter to save processing time     */
  /* end function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (insertShapeFast_FilledCircles_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Modify function files for performance %%%%%% */
  /*  */
  /* Before running code generation, input validation was removed from the file for function  */
  /* insertShape. The modified file was saved as insertShapeNoValidation.p, which is located in  */
  /* folder 'Validation_Removed'. The code is obscured (a p-code )to comply with the Matlab licensing  */
  /* agreement, which does not permit the distribution of Matlab source code. To permit code generation  */
  /* from the p-code, the statement coder.allowpcode('plain') was included in insertShapeNoValidation.m  */
  /* before obfuscation. DPM possesses the un-obfuscated files. */
  /*  */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /*                                               Example Code                  Upp. Bounds      Var. Size (T/F)  Type */
  /* FrameCropped_BulletPointsCode  = coder.typeof( zeros(500, 500, 3, 'uint8'),  [inf, inf, 3],   [1, 1, 0] );     %uint8 */
  /* BulletPointsXYR_CroppedCode    = coder.typeof( zeros(50, 3, 'int16'),        [50, 3],         [1, 0] );        %int16                   */
  /*   */
  /*  */
  /* %%%%% Set configurations to increase performance %%%%%% */
  /*  */
  /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
  /* "Optimization Strategies" */
  /*  */
  /* "Optimization Strategies" */
  /* cfg = coder.config('mex'); */
  /* cfg.SaturateOnIntegerOverflow = false; */
  /* cfg.IntegrityChecks = false; */
  /* Note: the following options were not changed because they were observed to add a slight increase */
  /* in execution time: */
  /* cfg.GlobalDataSyncMethod = 'NoSync'; */
  /* cfg.ConstantInputs = 'IgnoreValues'; */
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
  /* Second argument: specify a cell array of compiler-specific flags, where each flag is a each  */
  /* character vector. As function setbuildargs will be evaluated from text, use double ' quotes for  */
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
  /* codegen insertShapeFast_FilledCircles.m -report -config cfg -args {FrameCropped_BulletPointsCode, BulletPointsXYR_CroppedCode} */
  /*  */
  /* } */
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (insertShapeFast_FilledCircles.c) */
