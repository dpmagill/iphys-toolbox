/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertTextFast_PulseRate13.c
 *
 * Code generation for function 'insertTextFast_PulseRate13'
 *
 */

/* Include files */
#include "insertTextFast_PulseRate13.h"
#include "insertTextNoValidation.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void insertTextFast_PulseRate13(uint8_T VidFrameCrop[50025], const char_T
  Text_data[], const int32_T Text_size[2])
{
  real_T dv[2];
  static const real_T dv1[3] = { 189.0, 233.0, 255.0 };

  int32_T position[2];
  cell_wrap_0 text[1];
  uint8_T boxColor[3];
  int32_T thisTextU16_size[2];
  int32_T loop_ub;
  int32_T endR;
  uint16_T thisTextU16_data[125];
  int32_T endC;
  int32_T c;
  int32_T r;
  uint8_T tmp11;
  uint8_T tmp22;

  /* insertTextFast_PulseRate13   Code generation for function insertText for an image cropped to the */
  /*                              size of the pulse rate annotation with font size 13.                              */
  /*  */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by function WriteFaceVideo_PulseRate. */
  /*  */
  /*     Code generation: This function intended only for code generation (C language). */
  /*  */
  /*     Compiled file:  */
  /*  */
  /*      - The compiled file included in folder FacePulseRate     */
  /*        (insertTextFast_PulseRate13_mex.mexw64) only compatible on Windows platforms.  */
  /*      - This function uses bounded variable sizes for input variables to improve efficiency. Ensure  */
  /*        that the input variables do not exceed these bounds. */
  /* Specify flag to minGW compiler to optimize execution speed */
  /* Matlab: https://www.mathworks.com/help/coder/ref/coder.updatebuildinfo.html */
  /* Matlab: within link, see section "addCompileFlags": https://www.mathworks.com/help/coder/ug/customizing-the-post-code-generation-build-process.html */
  /* minGW: https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html  */
  /*  note: for more than one: '-Ofast -fschedule-fusion' */
  /* Specify inlining for faster code execution */
  /* Specify variable-size output arguments */
  /* For variable 'Text', set a bound on the length of text to prevent dynamic memory allocation, which */
  /* should increase performance. */
  /*                          Upp. Bounds     Var. Size (T/F) */
  /* Note: function insertTextNoValidation is a custom version of function insertText with input  */
  /* validation removed for efficiency. */
  /*  [X, Y] coordinates: top-left of indexed area */
  /*  text */
  /*  font type; must be compile-time constant */
  /*  font size; must be compile-time constant */
  /*  box background color: light blue */
  /*  [X, Y] coordinates position relative to text */
  /* insertText Insert text in image or video stream. */
  /*  */
  /*   NOTE: To increase performance, this function has been modified by DPM not to     */
  /*         include input validation. Proceed with caution. */
  /*         As this function is intended to be compiled without calling external functions, */
  /*         it should be safe from any potential modications made to function insertText. */
  /*  */
  /*   This function inserts text into an image or video. You can use it with */
  /*   either a grayscale or truecolor image input.  */
  /*  */
  /*   RGB = insertText(I, position, textString) returns a truecolor image */
  /*   with text string inserted into it. The input image, I, can be either a */
  /*   truecolor or grayscale image. position is an M-by-2 matrix of [x y] */
  /*   coordinates of the upper-left corner of the text bounding box. The input */
  /*   textString can be a single UNICODE text string or a cell array of */
  /*   UNICODE strings of length M, where M is the number of rows in position. */
  /*   If a single text string is provided it is used for all positions. */
  /*  */
  /*   RGB = insertText(I, position, numericValue) returns a truecolor image */
  /*   with numeric values inserted into it. numericValue can be a scalar or a */
  /*   vector of length M. If a scalar value is provided it is used for all */
  /*   positions. Numeric values are converted to string using format '%0.5g' */
  /*   as used by SPRINTF. */
  /*  */
  /*   RGB = insertText(..., Name, Value) */
  /*   specifies additional name-value pair arguments described below: */
  /*  */
  /*   'Font'          Font face of text. Specify the font of the text as one  */
  /*                   of the available truetype fonts installed on your */
  /*                   system. To get a list of available fonts, type */
  /*                   'listTrueTypeFonts' in the command prompt. */
  /*  */
  /*                   Default: 'LucidaSansRegular' */
  /*  */
  /*   'FontSize'      Font size, specified in points, as a positive integer  */
  /*                   value. Value must be between 1 and 200. */
  /*  */
  /*                   Default: 12 */
  /*  */
  /*   'TextColor'     Color for the text string. You can specify a different */
  /*                   color for each string, or one color for all the strings. */
  /*                   - To specify a color for each text string, set */
  /*                     'TextColor' to a cell array of M strings or an M-by-3 */
  /*                     matrix of RGB values. */
  /*                   - To specify one color for all text strings, set */
  /*                     'TextColor' to either a color string or an [R G B] */
  /*                     vector. */
  /*                   RGB values must be in the range of the image data type. */
  /*                   Supported color strings are, 'blue', 'green', 'red', */
  /*                   'cyan', 'magenta', 'yellow', 'black', 'white' */
  /*  */
  /*                   Default: 'black' */
  /*  */
  /*   'BoxColor'      Color of the text box. Specify the color in the same way */
  /*                   as the 'TextColor'. */
  /*     */
  /*                   Default: 'yellow' */
  /*  */
  /*   'BoxOpacity'    A scalar value from 0 to 1 defining the opacity of the */
  /*                   text box. 0 corresponds to fully transparent and 1 to */
  /*                   fully opaque. No text box appears when BoxOpacity is 0. */
  /*                           */
  /*                   Default: 0.6 */
  /*   */
  /*   'AnchorPoint'   Defines the relative location of a point on the text */
  /*                   box. Text box for each text string is positioned by */
  /*                   placing the reference point (called anchor point) of the */
  /*                   text box at point [x y] defined by a row in 'position'. */
  /*                   AnchorPoint can be one of the following strings: */
  /*                   'LeftTop',    'CenterTop',    'RightTop',  */
  /*                   'LeftCenter', 'Center',       'RightCenter',  */
  /*                   'LeftBottom', 'CenterBottom', 'RightBottom'                     */
  /*     */
  /*                   Default: 'LeftTop' */
  /*  */
  /*   Note */
  /*   ---- */
  /*   For code generation, only ASCII or extended ASCII textString is supported. */
  /*  */
  /*   Class Support */
  /*   ------------- */
  /*   The class of input I can be uint8, uint16, int16, double, single. Output */
  /*   RGB matches the class of I. */
  /*  */
  /*   Example 1: Insert numeric values and Non-ASCII character */
  /*   -------------------------------------------------------- */
  /*   I = imread('peppers.png'); */
  /*   position =  [1 50; 100 50]; % [x y] */
  /*   value = [555 pi]; */
  /*   */
  /*   % Display numeric values */
  /*   RGB = insertText(I, position, value, 'Font', 'LucidaSansRegular', ... */
  /*                    'AnchorPoint', 'LeftBottom'); */
  /*   % Display non-ASCII character (U+014C) */
  /*   OWithMacron=native2unicode([hex2dec('C5') hex2dec('8C')],'UTF-8'); */
  /*   RGB = insertText(RGB, [256 50], OWithMacron, 'BoxColor', 'w'); */
  /*   figure */
  /*   imshow(RGB) */
  /*   title('Numeric values and Non-ASCII character') */
  /*  */
  /*   Example 2: Insert numbers and strings */
  /*   ------------------------------------- */
  /*   I = imread('board.tif'); */
  /*   % Create texts with fractional values */
  /*   text_str = cell(3,1); */
  /*   conf_val = [85.212 98.76 78.342]; % Detection confidence */
  /*   for ii=1:3 */
  /*      text_str{ii} = ['Confidence: ' num2str(conf_val(ii),'%0.2f') '%']; */
  /*   end */
  /*   position = [23 373; 35 185; 77 107]; % [x y] */
  /*   box_color = {'red','green','yellow'}; */
  /*   */
  /*   RGB = insertText(I, position, text_str, 'FontSize', 18, ... */
  /*          'BoxColor', box_color, 'BoxOpacity', 0.4); */
  /*   figure */
  /*   imshow(RGB) */
  /*   title('Board') */
  /*  */
  /*   See also insertShape, insertMarker, insertObjectAnnotation, */
  /*      listTrueTypeFonts */
  /*  included shapeWidth, shapeHeight parameter to control text box width */
  /*  for insertObjectAnnotation */
  /*  == Parse inputs and validate == */
  /* { */
  /* narginchk(3,19); */
  /* } */
  dv[0] = 1.0;
  dv[1] = 1.0;
  validateAndParseInputs(dv, Text_data, Text_size, dv1, position, text, boxColor);

  /*  handle empty I or empty position */
  /*  == get glyph info == */
  /* thisText = getTextStr(text, textIdx); */
  thisTextU16_size[0] = 1;
  thisTextU16_size[1] = text[0].f1.size[1];
  loop_ub = text[0].f1.size[0] * text[0].f1.size[1];
  for (endR = 0; endR < loop_ub; endR++) {
    thisTextU16_data[endR] = (uint8_T)text[0].f1.data[endR];
  }

  if (text[0].f1.size[1] != 0) {
    /*         %% == Output == */
    /*             %% == insert text box == */
    /* ========================================================================== */
    /*  Step-1: get compact textbox width and height */
    /*  position is an M-by-2 matrix of [x y] coordinates of the upper-left */
    /*  corner of the text bounding box. */
    getTextboxWidthHeight(thisTextU16_data, thisTextU16_size, &endC, &loop_ub);

    /*  Step-2: add margin to textbox width and height */
    /*  used 3 before */
    /*  used 3 before */
    /*  only add left/right margin if the text extends past the shapeWidth */
    if (endC > 0) {
      endC += 14;
    }

    /*  Step-3: Consider anchor point and get text box top-left corner position */
    /*  % Step-3a: Shift left appropriate amount, if needed. If tbTopLeftX + */
    /*  % tbWidth is larger than RGB dimensions, shift tbTopLeftX */
    /*  if tbTopLeftX + tbWidth > size(RGB, 2) */
    /*      % Calculate excess width beyond image width */
    /*      excessWidth = tbTopLeftX + tbWidth - size(RGB, 2); */
    /*      if excessWidth > tbTopLeftX */
    /*          tbTopLeftX = 0; */
    /*      else */
    /*          tbTopLeftX = tbTopLeftX - excessWidth; */
    /*      end */
    /*  end */
    /*  Step-4: get outputs */
    /* ========================================================================== */
    endR = loop_ub + 14;
    if (endC >= 1) {
      if (loop_ub + 14 > 29) {
        endR = 29;
      }

      if (endC > 575) {
        endC = 575;
      }

      for (loop_ub = 0; loop_ub < 3; loop_ub++) {
        for (c = 1; c <= endC; c++) {
          for (r = 1; r <= endR; r++) {
            /* {    */
            /* end */
            /*   */
            /* mClassName = class(RGB); */
            /*  */
            /* if isa(RGB, 'double') */
            /*     cClassName = 'real_T'; */
            /* elseif isa(RGB, 'single') */
            /*     cClassName = 'real32_T';   */
            /* else */
            /*     */
            /*     cClassName = [mClassName '_T']; */
            /*      */
            /*      */
            /* end */
            /* } */
            tmp11 = (uint8_T)(0.6 * (real_T)boxColor[loop_ub] + 0.5);

            /* {    */
            /* end */
            /*   */
            /* mClassName = class(RGB); */
            /*  */
            /* if isa(RGB, 'double') */
            /*     cClassName = 'real_T'; */
            /* elseif isa(RGB, 'single') */
            /*     cClassName = 'real32_T';   */
            /* else */
            /*     */
            /*     cClassName = [mClassName '_T']; */
            /*      */
            /*      */
            /* end */
            /* } */
            tmp22 = (uint8_T)(0.4 * (real_T)VidFrameCrop[((r + 29 * (c - 1)) +
              16675 * loop_ub) - 1] + 0.5);
            VidFrameCrop[((r + 29 * (c - 1)) + 16675 * loop_ub) - 1] = (uint8_T)
              ((uint32_T)tmp11 + tmp22);
          }
        }
      }
    }

    insertGlyphs(VidFrameCrop, thisTextU16_data, thisTextU16_size);
  }

  /* end function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (insertTextFast_PulseRate13_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Modify function files for performance %%%%%% */
  /*  */
  /* Before running code generation, input validation was removed from the file for function  */
  /* insertText. The modified file was saved as insertTextNoValidation.p, which is located in folder */
  /* 'Validation_Removed'. The code is obscured to comply with the Matlab licensing agreement, which */
  /* does not permit the distribution of Matlab source code. */
  /*  */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /*                                   Example Code    Upp. Bounds   Var. Size (T/F)  Type */
  /* TextCode           = coder.typeof( ' ',            [1, 125],     [0, 1] );        %char */
  /*                    */
  /*  */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /* VidFrameCropCode   = zeros(29, 575, 3, 'uint8'); %uint8 */
  /*  */
  /*  */
  /* %%%%% Set configurations to increase performance %%%%%% */
  /*  */
  /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
  /* "Optimization Strategies" */
  /* cfg = coder.config('mex'); */
  /* cfg.GlobalDataSyncMethod = 'NoSync'; */
  /* cfg.ConstantInputs = 'IgnoreValues'; */
  /* cfg.ExtrinsicCalls = false; */
  /* cfg.SaturateOnIntegerOverflow = false; */
  /* cfg.IntegrityChecks = false; */
  /* cfg.ResponsivenessChecks = false; */
  /* cfg.DynamicMemoryAllocation = 'off'; %disabled as all variables have bounded size */
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
  /* Second argument: specify a cell array of compiler-specific flags, where each flag is a character */
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
  /* codegen insertTextFast_PulseRate13.m -report -config cfg -args {VidFrameCropCode, TextCode} */
  /*  */
  /* } */
}

/* End of code generation (insertTextFast_PulseRate13.c) */
