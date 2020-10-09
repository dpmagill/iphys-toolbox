/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * WriteFaceVideo_MaskOverlay.c
 *
 * Code generation for function 'WriteFaceVideo_MaskOverlay'
 *
 */

/* Include files */
#include "WriteFaceVideo_MaskOverlay.h"
#include "mwmathutil.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void ReturnOpacityValue(uint8_T RColor, uint8_T GColor, uint8_T BColor,
  real_T Opacity, uint8_T *RColorOpac, uint8_T *GColorOpac, uint8_T *BColorOpac);

/* Function Definitions */
static void ReturnOpacityValue(uint8_T RColor, uint8_T GColor, uint8_T BColor,
  real_T Opacity, uint8_T *RColorOpac, uint8_T *GColorOpac, uint8_T *BColorOpac)
{
  /* end main function */
  /* ============================================================================================= */
  /* Local Functions */
  /* ============================================================================================= */
  /* ============================================================================================= */
  /* ReturnOpacityValue   Return the R, G, and B opacity values.          */
  /*  */
  /*     Description: */
  /*  */
  /*     Return the R, G, and B opacity values.   */
  /*  */
  /*     Multiply the specified mask colors by the specified opacity. Then, subtract 1 in order to  */
  /*     prevent integer overflow. Note: if all calculations were conducted in floating point, the  */
  /*     maximum value any pixel could receive would be 255. However, rounding introduced by the use of  */
  /*     integers results in occassional values above 255, which wrap in compiled C. */
  /* Prevent inlining */
  /* It has been observed that code generation makes an optimization by inserting the subtraction */
  /* performed here into the loop, which results in the subtraction occurring on each iteration. Attemp */
  /* to prevent this optimization by restricting inlining. */
  /* Scalars; type uint8. */
  *RColorOpac = (uint8_T)((uint8_T)muDoubleScalarRound((real_T)RColor * Opacity)
    - 1U);
  *GColorOpac = (uint8_T)((uint8_T)muDoubleScalarRound((real_T)GColor * Opacity)
    - 1U);
  *BColorOpac = (uint8_T)((uint8_T)muDoubleScalarRound((real_T)BColor * Opacity)
    - 1U);

  /* end local function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (WriteFaceVideo_MaskOverlay_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /*                                              Example Code                 Upp. Bounds     Var. Size (T/F)  Type */
  /* VidFrameROICode               = coder.typeof( zeros(500, 500, 3, 'uint8'), [inf, inf, 3],  [1, 1, 0] );     %uint8 */
  /* IsSkinMaskCode                = coder.typeof( false(500, 500),             [inf, inf],     [1, 1] );        %logical */
  /*  */
  /*  */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /* TransparencyCode = single(0); */
  /* ColorCode        = zeros(1, 3, 'double');                                                                 */
  /* nRowsCode        = uint16(0); */
  /* nColsCode        = uint16(0); */
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
  /* cfg.ExtrinsicCalls = false;  */
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
  /* Argument buildInfo: this variable is assign by the caller (the codegen command executed  */
  /* below) and is not present in the base workspace. */
  /*  */
  /* Second argument: specify a cell array of compiler-specific flags, where each flag is a  */
  /* character vector. As function setbuildargs will be evaluated from text, use double ' quotes for  */
  /* each character vector to maintain the charater vector, */
  /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
  /*  */
  /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast'' ''-fsingle-precision-constant''})'; */
  /*  */
  /* Assign to code-generation configuration object */
  /* cfg.PostCodeGenCommand = setbuildargsAsText; */
  /*  */
  /*  */
  /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
  /*  */
  /* codegen WriteFaceVideo_MaskOverlay.m -report -config cfg -args {VidFrameROICode, TransparencyCode, IsSkinMaskCode, ColorCode, nRowsCode, nColsCode} */
  /*               */
  /* } */
}

void WriteFaceVideo_MaskOverlay(emxArray_uint8_T *VidFrameROI, real32_T
  Transparency, const emxArray_boolean_T *IsSkinMask_Inverted, const real_T
  Color[3], uint16_T nRows, uint16_T nCols)
{
  uint8_T RColorOpac;
  uint8_T GColorOpac;
  uint8_T BColorOpac;
  int32_T NEl;
  int32_T NEl2;
  int32_T i;
  int32_T idx;

  /* WriteFaceVideo_MaskOverlay   Overlay color on image indicating pixels corresponding to inverted  */
  /*                              skin-segmentation mask. */
  /*     */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by function WriteFaceVideo_OverlaySkinSegmentation.  */
  /*  */
  /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*     Compiled file: The compiled file included in folder FacePulseRate  */
  /*     (WriteFaceVideo_MaskOverlay_mex.mexw64) only compatible on Windows platforms.     */
  /*  */
  /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
  /*     the Responsible AI License (RAIL). */
  /* %%%%% Setup %%%%%% */
  /* Mask colors per channel */
  /* Scalars; type uint8. */
  /* Convert to opacity */
  /* Scalar; type double. */
  /* Opacity values per channel */
  /* Local function. */
  /* Scalars; type uint8. */
  ReturnOpacityValue((uint8_T)muDoubleScalarRound(Color[0]), (uint8_T)
                     muDoubleScalarRound(Color[1]), (uint8_T)muDoubleScalarRound
                     (Color[2]), 1.0 - Transparency, &RColorOpac, &GColorOpac,
                     &BColorOpac);

  /* %%%%% Code generation running %%%%%% */
  /* Use a for-loop version for code generation and a vectorized version for Matlab code. */
  /* Number of elements in inverted skin-segmentation mask */
  /* Cast to type int32 to prevent integer overflow. */
  /* Scalar; int32. */
  NEl = nRows * nCols;

  /* Loop index for page 3 (the blue channel) */
  NEl2 = NEl << 1;

  /* Loop across pixels */
  for (i = 0; i < NEl; i++) {
    /* Convert to mask pixel if IsSkinMask_Inverted(i) is true (non-skin) */
    if (IsSkinMask_Inverted->data[i]) {
      /* Cast video frame element from type uint8 to a floating-point type to permit */
      /* multiplication by a decimal (Transparency). Cast to type single for efficiency.              */
      /* Red channel: */
      VidFrameROI->data[i] = (uint8_T)((uint32_T)(uint8_T)muSingleScalarFloor
        ((real32_T)VidFrameROI->data[i] * Transparency) + RColorOpac);

      /* Green channel: */
      idx = i + NEl;
      VidFrameROI->data[idx] = (uint8_T)((uint32_T)(uint8_T)muSingleScalarFloor
        ((real32_T)VidFrameROI->data[idx] * Transparency) + GColorOpac);

      /* Blue channel: */
      idx = i + NEl2;
      VidFrameROI->data[idx] = (uint8_T)((uint32_T)(uint8_T)muSingleScalarFloor
        ((real32_T)VidFrameROI->data[idx] * Transparency) + BColorOpac);
    }
  }

  /* %%%%% Code generation not running %%%%%%     */
}

/* End of code generation (WriteFaceVideo_MaskOverlay.c) */
