/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertTextFast_Font13LT.c
 *
 * Code generation for function 'insertTextFast_Font13LT'
 *
 */

/* Include files */
#include "insertTextFast_Font13LT.h"
#include "insertTextFast_Font13LT_data.h"
#include "insertTextFast_Font13LT_emxutil.h"
#include "insertTextNoValidation.h"
#include "mwmathutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void insertTextFast_Font13LT(emxArray_uint8_T *VidFrame, const emxArray_int16_T *
  TextXY, const emxArray_cell_wrap_0 *Text, const emxArray_real_T *textColor,
  const real_T BoxColor[3])
{
  boolean_T isEmpty;
  emxArray_uint8_T *colorRGB;
  int32_T i;
  int32_T ntilerows;
  emxArray_uint8_T *boxColor;
  uint8_T b_colorRGB[3];
  int32_T jcol;
  int32_T ibmat;
  int32_T imSize_idx_1;
  boolean_T isScalarText;
  int32_T textIdx;
  emxArray_uint16_T *thisTextU16;
  int32_T ii;
  int16_T i1;
  int32_T startR;
  int32_T endR;
  int16_T i2;
  int32_T startC;
  uint8_T tmp11;
  uint8_T tmp22;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

  /* insertTextFast_Font13LT   Code-generation version of insertText function using font size of 13 and */
  /*                           positioned such that the [X, Y] coordinates are to the left-top relative  */
  /*                           to the text.                           */
  /*                                        */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, called by function WriteFaceVideo_SkinDetectDiagnosis. */
  /*   */
  /*     Code generation: This function only intended to be used for code generation (C-language). */
  /*  */
  /*     Compiled file: The compiled file included in folder FacePulseRate     */
  /*     (insertTextFast_Font13LT_mex.mexw64) only compatible on Windows platforms. */
  /* Note: in this case, using the same variable name for the input and output arguments results in */
  /* faster code execution. This may be because the variable is passed by reference rather than value.  */
  /* Specify inlining for faster code execution */
  /* Specify variable output arguments for use in compilation */
  /*                                   Upp. Bounds       Var. Size (T/F) */
  /* Insert text labels on the video frame */
  /* Note: function insertTextNoValidation is a custom version of function insertText with  */
  /* input validation removed for efficiency. */
  /*  specify image where text annotation inserted */
  /*  [X, Y] coordinates for M regions: M-by-2 matrix */
  /*  text for M regions: M-by-1 cell array */
  /*  colors for M regions: M-by-3 matrix */
  /*  font size; must be constant for code generation. */
  /*  background opacity: 1 indicates a solid color */
  /*  Note: white has been observed to cause unexpected colors to appear. */
  if ((VidFrame->size[0] == 0) || (VidFrame->size[1] == 0) || (TextXY->size[0] ==
       0)) {
    isEmpty = true;
  } else {
    isEmpty = false;
  }

  emxInit_uint8_T(&colorRGB, 2, true);
  i = colorRGB->size[0] * colorRGB->size[1];
  colorRGB->size[0] = textColor->size[0];
  colorRGB->size[1] = 3;
  emxEnsureCapacity_uint8_T(colorRGB, i);
  ntilerows = textColor->size[0] * textColor->size[1];
  for (i = 0; i < ntilerows; i++) {
    colorRGB->data[i] = (uint8_T)muDoubleScalarRound(textColor->data[i]);
  }

  if (colorRGB->size[0] == 1) {
    ntilerows = colorRGB->size[0] * colorRGB->size[1];
    for (i = 0; i < ntilerows; i++) {
      b_colorRGB[i] = colorRGB->data[i];
    }

    i = colorRGB->size[0] * colorRGB->size[1];
    colorRGB->size[0] = TextXY->size[0];
    colorRGB->size[1] = 3;
    emxEnsureCapacity_uint8_T(colorRGB, i);
    ntilerows = TextXY->size[0];
    for (jcol = 0; jcol < 3; jcol++) {
      ibmat = jcol * ntilerows;
      for (imSize_idx_1 = 0; imSize_idx_1 < ntilerows; imSize_idx_1++) {
        colorRGB->data[ibmat + imSize_idx_1] = b_colorRGB[jcol];
      }
    }
  }

  emxInit_uint8_T(&boxColor, 2, true);
  b_colorRGB[0] = (uint8_T)muDoubleScalarRound(BoxColor[0]);
  b_colorRGB[1] = (uint8_T)muDoubleScalarRound(BoxColor[1]);
  b_colorRGB[2] = (uint8_T)muDoubleScalarRound(BoxColor[2]);
  i = boxColor->size[0] * boxColor->size[1];
  boxColor->size[0] = TextXY->size[0];
  boxColor->size[1] = 3;
  emxEnsureCapacity_uint8_T(boxColor, i);
  ntilerows = TextXY->size[0];
  for (jcol = 0; jcol < 3; jcol++) {
    ibmat = jcol * ntilerows;
    for (imSize_idx_1 = 0; imSize_idx_1 < ntilerows; imSize_idx_1++) {
      boxColor->data[ibmat + imSize_idx_1] = b_colorRGB[jcol];
    }
  }

  isScalarText = (Text->size[0] == 1);
  if (!isEmpty) {
    textIdx = 0;
    i = TextXY->size[0];
    emxInit_uint16_T(&thisTextU16, 2, true);
    for (ii = 0; ii < i; ii++) {
      if (!isScalarText) {
        textIdx = ii;
      }

      ibmat = thisTextU16->size[0] * thisTextU16->size[1];
      thisTextU16->size[0] = 1;
      thisTextU16->size[1] = Text->data[textIdx].f1->size[1];
      emxEnsureCapacity_uint16_T(thisTextU16, ibmat);
      ntilerows = Text->data[textIdx].f1->size[0] * Text->data[textIdx].f1->
        size[1];
      for (ibmat = 0; ibmat < ntilerows; ibmat++) {
        thisTextU16->data[ibmat] = (uint8_T)Text->data[textIdx].f1->data[ibmat];
      }

      if (thisTextU16->size[1] != 0) {
        b_colorRGB[0] = boxColor->data[ii];
        b_colorRGB[1] = boxColor->data[ii + boxColor->size[0]];
        b_colorRGB[2] = boxColor->data[ii + boxColor->size[0] * 2];
        getTextboxWidthHeight(thisTextU16, &ntilerows, &ibmat);
        jcol = ntilerows - 1;
        if (ntilerows > 0) {
          jcol = ntilerows + 7;
        }

        ntilerows = VidFrame->size[0];
        imSize_idx_1 = VidFrame->size[1];
        i1 = TextXY->data[ii + TextXY->size[0]];
        startR = i1;
        endR = (i1 + ibmat) + 7;
        i2 = TextXY->data[ii];
        startC = i2;
        ibmat = i2 + jcol;
        if ((i1 <= ntilerows) && (endR >= 1) && (i2 <= imSize_idx_1) && (ibmat >=
             1)) {
          if (i1 < 1) {
            startR = 1;
          }

          if (endR > ntilerows) {
            endR = ntilerows;
          }

          if (i2 < 1) {
            startC = 1;
          }

          if (ibmat > imSize_idx_1) {
            ibmat = imSize_idx_1;
          }

          for (ntilerows = 0; ntilerows < 3; ntilerows++) {
            for (jcol = startC; jcol <= ibmat; jcol++) {
              for (imSize_idx_1 = startR; imSize_idx_1 <= endR; imSize_idx_1++)
              {
                tmp11 = (uint8_T)(0.5 * (real_T)b_colorRGB[ntilerows] + 0.5);
                tmp22 = (uint8_T)(0.5 * (real_T)VidFrame->data[((imSize_idx_1 +
                  VidFrame->size[0] * (jcol - 1)) + VidFrame->size[0] *
                  VidFrame->size[1] * ntilerows) - 1] + 0.5);
                VidFrame->data[((imSize_idx_1 + VidFrame->size[0] * (jcol - 1))
                                + VidFrame->size[0] * VidFrame->size[1] *
                                ntilerows) - 1] = (uint8_T)((uint32_T)tmp11 +
                  tmp22);
              }
            }
          }
        }

        b_colorRGB[0] = colorRGB->data[ii];
        b_colorRGB[1] = colorRGB->data[ii + colorRGB->size[0]];
        b_colorRGB[2] = colorRGB->data[ii + colorRGB->size[0] * 2];
        insertGlyphs(VidFrame, thisTextU16, TextXY->data[ii] + 4, TextXY->
                     data[ii + TextXY->size[0]] + 4, b_colorRGB);
      }
    }

    emxFree_uint16_T(&thisTextU16);
  }

  emxFree_uint8_T(&colorRGB);
  emxFree_uint8_T(&boxColor);

  /*    [X, Y] coordinates position relative to text; must be   */
  /*    constant for code generation. */
  /* end function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (insertTextFast_Font13LT_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Modify function files for performance %%%%%% */
  /*  */
  /* Before running code generation, input validation was removed from the file for function  */
  /* insertText. The modified file was saved as insertTextNoValidation.p, which is located in folder */
  /* 'Validation_Removed'. The code is obscured (as p-code) to comply with the Matlab licensing  */
  /* agreement, which does not permit the distribution of Matlab source code. To permit code generation  */
  /* from the p-code, the statement coder.allowpcode('plain') was included in insertTextNoValidation.m  */
  /* before obfuscation.  */
  /*  */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /* Specify cell array element properties */
  /* Note: the cell array will have the following properties: */
  /*    :inf×1 homogeneous cell  */
  /*         base: 1×:inf char */
  /* Element1 = ... */
  /*     coder.typeof('',      ... example code */
  /*                  [1 inf], ... upper bounds */
  /*                  [0, 1]   ... variable size (T/F) */
  /*     ); */
  /*  */
  /*                                   Example Code                  Upp. Bounds      Var. Size (T/F)  Type */
  /* VidFrameCode       = coder.typeof( zeros(500, 500, 3, 'uint8'),  [inf, inf, 3],   [1, 1, 0] );     %uint8 */
  /* TextXYCode         = coder.typeof( zeros(5, 2, 'int16'),         [inf, 2],        [1, 0] );        %int16 */
  /* TextCode           = coder.typeof( {Element1},                   [inf, 1],        [1, 0] );        %cell; elements: char */
  /* textColorCode      = coder.typeof( zeros(5, 3),                  [inf, 3],        [1, 0] );        %double */
  /*              */
  /*  */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /* BoxColorCode       = double([1, 1, 1]); %double */
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
  /* vector. As function setbuildargs will be evaluated from text, use double ' quotes for each  */
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
  /* codegen insertTextFast_Font13LT.m -report -config cfg -args {VidFrameCode, TextXYCode, TextCode, textColorCode, BoxColorCode} */
  /*  */
  /* } */
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (insertTextFast_Font13LT.c) */
