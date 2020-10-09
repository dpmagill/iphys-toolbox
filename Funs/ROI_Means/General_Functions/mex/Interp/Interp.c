/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Interp.c
 *
 * Code generation for function 'Interp'
 *
 */

/* Include files */
#include "Interp.h"
#include "mwmathutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void Interp(const real32_T x_data[], const int32_T x_size[1], const int16_T
            y_data[], const int32_T y_size[2], const real32_T xi_data[], const
            int32_T xi_size[1], boolean_T LinearExtrapTF, boolean_T
            ValidityChecksTF, int16_T DiffMaxActual, const int16_T
            YArbitrary_data[], const int32_T YArbitrary_size[2], int16_T
            DiffMaxArbitrary, int16_T VidObjWidth, int16_T VidObjHeight, int16_T
            yi_data[], int32_T yi_size[2])
{
  boolean_T ArbitraryCheckTF;
  int32_T x_length;
  int32_T xi_length;
  int32_T nColsY;
  int32_T x_idx;
  int32_T xi_idx;
  real32_T f;
  int32_T exitg1;
  int32_T j;
  int16_T yi_ijth;
  real32_T x_before;
  real32_T x_after;
  int16_T yi_ith_data[4];
  real32_T r;
  int32_T yi_ijth_int32;
  int16_T y_before;
  int16_T y_after;
  int16_T Diff;

  /* Interp   Conduct linear interpolation/extrapolation or nearest-neighbor extrapolation. */
  /*  */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, called by functions ROIMeans_FirstRead_ExtrapolateROI,  */
  /*     ROIMSIR_Interpolate and ROIMSIR_FrameByFrameSmooth_InterpFR. */
  /*      */
  /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*     Description: */
  /*  */
  /*     When LinearExtrapTF == true, conduct linear interpolation or extrapolation.  */
  /*     When LinearExtrapTF == false, conduct linear interpolation only when xi falls within domain of  */
  /*     x. Otherwise, conduct nearest-neighbor extrapolation. */
  /*  */
  /*     When ValidityChecksTF == true, conduct checks and adjustments on values returned by linear */
  /*     interpolation / extrapolation. These checks and adjustments include ...   */
  /*  */
  /*     - Checking whether the difference between an interpolated value and a nearby actual value is */
  /*       within a specified threshold (DiffMaxActual). If not, this may be an indication of an   */
  /*       overshoot; in this case, the interpolated value is changed to the maximum value specified by  */
  /*       the threshold. This check and adjustment are only applied to an interpolated value  */
  /*       corresponding to the X- or Y-coordinate (rather than height or width) of the ROI. The check  */
  /*       is not applied to height or width as testing has indicated that an overshoot  is not as   */
  /*       common for height or width. */
  /*  */
  /*     - Checking whether an interpolated value corresponding to ROI height or width is above 20. If */
  /*       not, the interpolated value is recalculated by conducting nearest-neighbor extrapolation. A */
  /*       height or width below 20 is considered to be too small for the size of faces expected in a */
  /*       video. */
  /*  */
  /*     - Checking whether an interpolated value is within the frame dimensions (minimum of 1 and */
  /*       maximums of VidObjWidth and VidObjHeight). If not, the interpolated value is changed to be */
  /*       bounded by the frame dimensions. */
  /*  */
  /*     When YArbitrary is non-empty, conduct checks and adjustments on interpolated / extrapolated */
  /*     values. These checks and adjustments include ...   */
  /*  */
  /*     - Checking whether the difference between an interpolated value and a nearby arbitrary value  */
  /*       is within a specified threshold (DiffMaxArbitrary). If not, this may be an indication of an   */
  /*       overshoot; in this case, the interpolated value is changed to the maximum value specified by  */
  /*       the threshold. This check and adjustment are only applied to an interpolated value  */
  /*       corresponding to the X- or Y-coordinate (rather than height or width) of the ROI. The check  */
  /*       is not applied to height or width as testing has indicated that an overshoot is not as   */
  /*       common for height or width. */
  /*  */
  /*     Restrictions: */
  /*  */
  /*     - x is are assumed to increase monotonically and contain unique values. x must contain at */
  /*       least two elements. The number of elements must equal the number of elements of y.                         */
  /*     - xi is assumed to increase monotonically.  */
  /*     - y is assumed to have 4 columns. y must contain at least two elements. The number of elements  */
  /*       must equal the number of elements of x.  */
  /*  */
  /*     This function uses bounded variable sizes to improve efficiency. Ensure that inputs do not */
  /*     exceed the bounds. */
  /*  */
  /*     Inputs: */
  /*  */
  /*     x                = Time values that correspond to values of y. M x 1 column vector; type  */
  /*                        single. */
  /*     y                = Values from which to interpolate. M x :4 matrix; type int16.                    */
  /*     xi               = Time values at which interpolation will occur. The elements do not need to   */
  /*                        be unique. The number of values is not restricted. Column vector; type  */
  /*                        single.                                         */
  /*     LinearExtrapTF   = If true, use the linear method for extrapolation. If false, use the  */
  /*                        nearest-neighbor method. Scalar; type logical. */
  /*     ValidityChecksTF = If true, check whether the interpolated values appears valid. Scalar;  */
  /*                        type logical. */
  /*     DiffMaxActual    = The threshold specifying the maximum absolute-value difference between an  */
  /*                        interpolated / extrapolated value and a previous actual value. Scalar; type  */
  /*                        int16. Threshold only applied when InterpChecksTF == true;      */
  /*     DiffMaxArbitrary = The threshold specifying the maximum absolute-value difference between an  */
  /*                        interpolated / extrapolated value and an arbitrary X- or Y-coordinate   */
  /*                        value, which is specified by YArbitrary. Scalar; type int16.                      */
  /*     YArbitrary       = Arbitary X- and Y-coordinate values used with the threshold specified by  */
  /*                        DiffMaxArbitrary. To disable DiffMaxArbitrary checks, use 0 x 2 input.                         */
  /*                        0 x 2 or 1 x 2 row vector; type int16.                                                                                     */
  /*     VidObjWidth      = The frame width. Scalar; type int16. */
  /*     VidObjHeight     = The frame height. Scalar; type int16. */
  /* Inline function */
  /* Whether to conduct arbitrary value check */
  ArbitraryCheckTF = (YArbitrary_size[0] != 0);

  /* Length of input time points */
  x_length = x_size[0] - 1;

  /* Length of input interpolation timepoints */
  /* This length will equal the length of yi. */
  xi_length = xi_size[0];
  nColsY = y_size[1];

  /* Assert length to prevent dynamic memory allocation by colon operator */
  /* Preallocate output */
  yi_size[0] = xi_size[0];
  yi_size[1] = y_size[1];

  /* Initialize x_idx at 1  */
  /* x_idx is used to search for the value of x that is greater than xi. */
  /* In while loop, the first operation is to increment j by 1; hence, the effective use of x_idx */
  /* starts at 2. */
  /* By initializing x_idx here, rather than after each iteration of i, it is assumed that both x and   */
  /* xi are sorted in order from least to greatest. This assumption improves performance because values  */
  /* of x already matched are not researched (a qualification is that the implementation does research   */
  /* the immediately previous value of x -- see note within loop). If x or xi is not sorted, the    */
  /* initialization of x_idx (setting x_idx to 1) should occur after each iteration of i. */
  x_idx = 0;

  /* Loop across interpolation times points */
  for (xi_idx = 0; xi_idx < xi_length; xi_idx++) {
    /* The ith xi value (the ith interpolation point) */
    f = xi_data[xi_idx];

    /* Find the indices of x: x_before_idx and x_after_idx:       */
    /* If ith xi value is to left of domain of x */
    /* Case of extrapolation. */
    if (xi_data[xi_idx] < x_data[0]) {
      /* If linear extrapolation permitted */
      if (LinearExtrapTF) {
        /* Assign first and second indices of x */
        /* Linear extrapolation */
        /* Local function. */
        /* 1 x nColsY row vector; type int16. */
        /* end local function */
        /* ============================================================================================= */
        /* ExtrapLinear   Linear extrapolation of y at a single time point (xi). */
        /*  */
        /*     Note: */
        /*  */
        /*     Same as function InterpLinear except that an integer overflow check is also conducted. */
        /* Inline function */
        /* Preallocate output for ith yi values */
        /* Assign x values    */
        /* Scalars; type single. */
        x_before = x_data[0];
        x_after = x_data[1];

        /* Proportion of interpolated time interval to actual time interval */
        /* Scalar; type single. */
        r = (xi_data[xi_idx] - x_data[0]) / (x_data[1] - x_data[0]);

        /* Loop across columns of y */
        for (j = 0; j < nColsY; j++) {
          /* y value that comes before time point to be interpolated */
          /* Scalar; type int16. */
          yi_ijth_int32 = y_size[0] * j;
          y_before = y_data[yi_ijth_int32];

          /* y value that comes after time point to be interpolated */
          /* Scalar; type int16. */
          y_after = y_data[yi_ijth_int32 + 1];

          /* %%%%% Skip extrapolation %%%%%% */
          /* If y values same, assign one of them as extrapolated value */
          if (y_before == y_after) {
            yi_ijth = y_before;

            /* %%%%% Extrapolate %%%%%%          */
          } else {
            /* Step 1 */
            /* Extrapolated distance of y. */
            /* Multipy interpolated time-interval proportion by actual change in y. */
            /* Cast to floating-point type to multiply.  */
            /* Scalar; type single. */
            /* Step 2 */
            /* Add distance to most immediate previous actual y value. */
            /* As extrapolation could result in extreme value for y, conduct operation so that it can be */
            /* determined whether type int16 could overflow; specifically, cast to type int32 to prepare */
            /* for later check. */
            /* Scalar; type int32. */
            yi_ijth_int32 = y_before + (int32_T)muSingleScalarRound((real32_T)
              (int16_T)(y_after - y_before) * r);

            /* Check if extrapolated value will cause int16 type to overflow */
            /* If so, assign maximum or minimum value. */
            /* If positive value  */
            if (yi_ijth_int32 > 0) {
              /* If exceeds maximum value of type             */
              if (yi_ijth_int32 >= 32767) {
                yi_ijth_int32 = 32767;
              }

              /* If negative value */
            } else {
              /* If exceeds minimum value of type */
              if (yi_ijth_int32 <= -32767) {
                yi_ijth_int32 = -32767;
              }
            }

            /* Cast back to type int16 */
            yi_ijth = (int16_T)yi_ijth_int32;

            /* %%%%% --- Check whether interpolated value appears valid %%%%%% */
            if (ValidityChecksTF) {
              /* Local function. */
              /* Scalar; type int16. */
              /* end local function */
              /* ============================================================================================= */
              /* ValidityCheck   Check whether interpolated / extrapolated value appears valid. */
              /* Inline function */
              /* Switch according to column */
              switch (j + 1) {
               case 1:
                /* x-coordinate column */
                /* Local function. */
                /* end local function */
                /* ============================================================================================= */
                /* ValidityCheck_XY   Validity check for X- or Y-coordinate. */
                /*  */
                /*     Description: */
                /*  */
                /*     Check whether difference between before-value and interpolated / extrapolated value is greater   */
                /*     than specified threshold. If so, set value at maximum of threshold.  */
                /* Inline function */
                Diff = (int16_T)(yi_ijth_int32 - y_before);
                if (Diff > DiffMaxActual) {
                  yi_ijth = (int16_T)(y_before + DiffMaxActual);
                } else {
                  if (Diff < (int16_T)-DiffMaxActual) {
                    yi_ijth = (int16_T)(y_before - DiffMaxActual);
                  }
                }
                break;

               case 2:
                /* y-coordinate column */
                /* Local function. */
                /* end local function */
                /* ============================================================================================= */
                /* ValidityCheck_XY   Validity check for X- or Y-coordinate. */
                /*  */
                /*     Description: */
                /*  */
                /*     Check whether difference between before-value and interpolated / extrapolated value is greater   */
                /*     than specified threshold. If so, set value at maximum of threshold.  */
                /* Inline function */
                Diff = (int16_T)(yi_ijth_int32 - y_before);
                if (Diff > DiffMaxActual) {
                  yi_ijth = (int16_T)(y_before + DiffMaxActual);
                } else {
                  if (Diff < (int16_T)-DiffMaxActual) {
                    yi_ijth = (int16_T)(y_before - DiffMaxActual);
                  }
                }
                break;

               case 3:
                /* width column */
                /* Local function. */
                /* end local function */
                /* ============================================================================================= */
                /* ValidityCheck_WH   Validity check for width or height. */
                /*  */
                /*     Description: */
                /*  */
                /*     Check whether width or height value is less than 20. If so, then substitute the  */
                /*     nearest-neighbor method in place of the linear method. */
                /* Inline function */
                if (yi_ijth_int32 < 20) {
                  /* Determine whether x_after or x_before nearest and assign. */
                  /* x_after nearest */
                  if (muSingleScalarAbs(x_after - f) <= muSingleScalarAbs
                      (x_before - f)) {
                    yi_ijth = y_after;

                    /* x_before nearest */
                  } else {
                    yi_ijth = y_before;
                  }
                }
                break;

               default:
                /* height column */
                /* Local function. */
                /* end local function */
                /* ============================================================================================= */
                /* ValidityCheck_WH   Validity check for width or height. */
                /*  */
                /*     Description: */
                /*  */
                /*     Check whether width or height value is less than 20. If so, then substitute the  */
                /*     nearest-neighbor method in place of the linear method. */
                /* Inline function */
                if (yi_ijth_int32 < 20) {
                  /* Determine whether x_after or x_before nearest and assign. */
                  /* x_after nearest */
                  if (muSingleScalarAbs(x_after - f) <= muSingleScalarAbs
                      (x_before - f)) {
                    yi_ijth = y_after;

                    /* x_before nearest */
                  } else {
                    yi_ijth = y_before;
                  }
                }
                break;
              }
            }
          }

          /* %%%%% Check whether interpolated value within specified distance from arbitrary value %%%%%%  */
          /* If arbitary check enabled */
          if (ArbitraryCheckTF && (j + 1 < 3)) {
            /* Check whether the interpolated X- or Y-coordinate is within a specified distance  */
            /* (DiffMaxArbitrary) from a specified X- or Y-coordinate. */
            /* Local function. */
            /* Scalar; type int16. */
            /* end local function */
            /* ============================================================================================= */
            /* ArbitraryCheck_XY   Check whether the interpolated / extrapolated X- or Y-coordinate is within a  */
            /*                     specified distance (DiffMaxArbitrary) from a specified X- or Y-coordinate */
            /*                     ( YArbitrary(j) ). */
            /*  */
            /*     Description: */
            /*  */
            /*     Check whether the interpolated / extrapolated X- or Y-coordinate is within a specified  */
            /*     distance (DiffMaxArbitrary) from a specified for X- or Y-coordinate ( YArbitrary(j) ). If so,  */
            /*     set value at maximum of threshold.  */
            /*  */
            /*     Inputs (subset): */
            /*  */
            /*     YArbitrary(1) = Specified arbitrary X-coordinate. */
            /*     YArbitrary(2) = Specified arbitrary Y-coordinate. */
            /* Inline function */
            /* Index either X- or Y-coordinate from arbitrary ROI */
            Diff = (int16_T)(yi_ijth - YArbitrary_data[j]);
            if (Diff > DiffMaxArbitrary) {
              yi_ijth = (int16_T)(YArbitrary_data[j] + DiffMaxArbitrary);
            } else {
              if (Diff < (int16_T)-DiffMaxArbitrary) {
                yi_ijth = (int16_T)(YArbitrary_data[j] - DiffMaxArbitrary);
              }
            }

            /* end local function */
            /* ============================================================================================= */
            /* Code-generation and build script */
            /* ============================================================================================= */
            /* Code-generation and build script used to generate C-language code and create the compiled version  */
            /* (Interp_mex) of the function. */
            /* { */
            /*  */
            /* %%%%% Specify variable-size input arguments %%%%%% */
            /*  */
            /* See Matlab documentation for coder.typeof. */
            /*                                     Example Code                 Upp. Bounds    Var. Size (T/F)  Type */
            /* xCode                = coder.typeof( zeros(50, 1, 'single'),      [50, 1],       [1, 0] );        %single */
            /* yCode                = coder.typeof( zeros(50, 4, 'int16'),       [50, 4],       [1, 1] );        %int16 */
            /* xiCode               = coder.typeof( zeros(50, 1, 'single'),      [50, 1],       [1, 0] );        %single                                                         */
            /* YArbitraryCode       = coder.typeof( zeros(1, 2, 'int16'),        [1, 2],        [1, 0] );        %int16 */
            /*  */
            /*  */
            /* %%%%% Specify fixed-size input arguments %%%%%% */
            /*  */
            /* LinearExtrapTFCode   = false; */
            /* InterpChecksTFCode   = false; */
            /* DiffMaxActualCode    = int16(0);  */
            /* VidObjWidthCode      = int16(0); */
            /* VidObjHeightCode     = int16(0);            */
            /* DiffMaxArbitraryCode = int16(0);     */
            /*  */
            /*                  */
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
            /* cfg.DynamicMemoryAllocation = 'off'; %disabled to improve efficiency as all variables have bounded size */
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
            /* codegen Interp.m -report -config cfg -args {xCode, yCode, xiCode, LinearExtrapTFCode, InterpChecksTFCode, DiffMaxActualCode, YArbitraryCode, DiffMaxArbitraryCode, VidObjWidthCode, VidObjHeightCode} */
            /*   */
            /* } */
          }

          /* %%%%% Assign %%%%%% */
          /* Scalar; type int16. */
          yi_ith_data[j] = yi_ijth;
        }
      } else {
        /* Flag indicating ith xi value is to left of domain of x */
        /* Nearest-neighbor extrapolation */
        /* Local function. */
        /* 1 x nColsY row vector; type int16.    */
        /* end local function */
        /* ============================================================================================= */
        /* ExtrapNearest   Nearest-neighbor extrapolation of y at single time point (xi). */
        /* Inline function */
        /* Preallocate output for ith yi values */
        /* If ith xi value is to left of domain of x */
        /* Loop across columns of y */
        for (j = 0; j < nColsY; j++) {
          /* Assign from first row of y */
          yi_ijth = y_data[y_size[0] * j];

          /* If arbitary check enabled */
          if (ArbitraryCheckTF && (j + 1 < 3)) {
            /* Check whether the interpolated X- or Y-coordinate is within a specified distance  */
            /* (DiffMaxArbitrary) from a specified X- or Y-coordinate. */
            /* Local function. */
            /* Scalar; type int16.             */
            /* end local function */
            /* ============================================================================================= */
            /* ArbitraryCheck_XY   Check whether the interpolated / extrapolated X- or Y-coordinate is within a  */
            /*                     specified distance (DiffMaxArbitrary) from a specified X- or Y-coordinate */
            /*                     ( YArbitrary(j) ). */
            /*  */
            /*     Description: */
            /*  */
            /*     Check whether the interpolated / extrapolated X- or Y-coordinate is within a specified  */
            /*     distance (DiffMaxArbitrary) from a specified for X- or Y-coordinate ( YArbitrary(j) ). If so,  */
            /*     set value at maximum of threshold.  */
            /*  */
            /*     Inputs (subset): */
            /*  */
            /*     YArbitrary(1) = Specified arbitrary X-coordinate. */
            /*     YArbitrary(2) = Specified arbitrary Y-coordinate. */
            /* Inline function */
            /* Index either X- or Y-coordinate from arbitrary ROI */
            Diff = (int16_T)(yi_ijth - YArbitrary_data[j]);
            if (Diff > DiffMaxArbitrary) {
              yi_ijth = (int16_T)(YArbitrary_data[j] + DiffMaxArbitrary);
            } else {
              if (Diff < (int16_T)-DiffMaxArbitrary) {
                yi_ijth = (int16_T)(YArbitrary_data[j] - DiffMaxArbitrary);
              }
            }

            /* end local function */
            /* ============================================================================================= */
            /* Code-generation and build script */
            /* ============================================================================================= */
            /* Code-generation and build script used to generate C-language code and create the compiled version  */
            /* (Interp_mex) of the function. */
            /* { */
            /*  */
            /* %%%%% Specify variable-size input arguments %%%%%% */
            /*  */
            /* See Matlab documentation for coder.typeof. */
            /*                                     Example Code                 Upp. Bounds    Var. Size (T/F)  Type */
            /* xCode                = coder.typeof( zeros(50, 1, 'single'),      [50, 1],       [1, 0] );        %single */
            /* yCode                = coder.typeof( zeros(50, 4, 'int16'),       [50, 4],       [1, 1] );        %int16 */
            /* xiCode               = coder.typeof( zeros(50, 1, 'single'),      [50, 1],       [1, 0] );        %single                                                         */
            /* YArbitraryCode       = coder.typeof( zeros(1, 2, 'int16'),        [1, 2],        [1, 0] );        %int16 */
            /*  */
            /*  */
            /* %%%%% Specify fixed-size input arguments %%%%%% */
            /*  */
            /* LinearExtrapTFCode   = false; */
            /* InterpChecksTFCode   = false; */
            /* DiffMaxActualCode    = int16(0);  */
            /* VidObjWidthCode      = int16(0); */
            /* VidObjHeightCode     = int16(0);            */
            /* DiffMaxArbitraryCode = int16(0);     */
            /*  */
            /*                  */
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
            /* cfg.DynamicMemoryAllocation = 'off'; %disabled to improve efficiency as all variables have bounded size */
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
            /* codegen Interp.m -report -config cfg -args {xCode, yCode, xiCode, LinearExtrapTFCode, InterpChecksTFCode, DiffMaxActualCode, YArbitraryCode, DiffMaxArbitraryCode, VidObjWidthCode, VidObjHeightCode} */
            /*   */
            /* } */
          }

          yi_ith_data[j] = yi_ijth;
        }

        /* If ith xi value is to right of domain of x     */
      }

      /* If ith xi value is either within domain of x or to right of domain of x       */
    } else {
      /* If xi is within the domain of x, ... */
      /*  - x_before_idx is the index of x where x is less than xi. */
      /*  - x_after_idx is the index of x where x is greater than or equal to xi. */
      /* If xi is to right of the domain of x, ... */
      /*  - both x_before_idx and x_after_idx index x where x is less than xi.  */
      /*  - x at x_before_idx is less than x at x_after_idx. */
      do {
        exitg1 = 0;
        x_idx++;

        /* If ith xi value is to right of domain of x */
        /* Case of extrapolation. */
        if (x_idx + 1 >= x_length + 1) {
          /* If linear extrapolation permitted */
          if (LinearExtrapTF) {
            /* Assign x indices */
            /* Linear extrapolation */
            /* Local function. */
            /* 1 x nColsY row vector; type int16. */
            /* end local function */
            /* ============================================================================================= */
            /* ExtrapLinear   Linear extrapolation of y at a single time point (xi). */
            /*  */
            /*     Note: */
            /*  */
            /*     Same as function InterpLinear except that an integer overflow check is also conducted. */
            /* Inline function */
            /* Preallocate output for ith yi values */
            /* Assign x values    */
            /* Scalars; type single. */
            x_before = x_data[x_length - 1];
            x_after = x_data[x_length];

            /* Proportion of interpolated time interval to actual time interval */
            /* Scalar; type single. */
            r = (f - x_before) / (x_data[x_length] - x_before);

            /* Loop across columns of y */
            for (j = 0; j < nColsY; j++) {
              /* y value that comes before time point to be interpolated */
              /* Scalar; type int16. */
              yi_ijth_int32 = x_length + y_size[0] * j;
              y_before = y_data[yi_ijth_int32 - 1];

              /* y value that comes after time point to be interpolated */
              /* Scalar; type int16. */
              y_after = y_data[yi_ijth_int32];

              /* %%%%% Skip extrapolation %%%%%% */
              /* If y values same, assign one of them as extrapolated value */
              if (y_before == y_after) {
                yi_ijth = y_before;

                /* %%%%% Extrapolate %%%%%%          */
              } else {
                /* Step 1 */
                /* Extrapolated distance of y. */
                /* Multipy interpolated time-interval proportion by actual change in y. */
                /* Cast to floating-point type to multiply.  */
                /* Scalar; type single. */
                /* Step 2 */
                /* Add distance to most immediate previous actual y value. */
                /* As extrapolation could result in extreme value for y, conduct operation so that it can be */
                /* determined whether type int16 could overflow; specifically, cast to type int32 to prepare */
                /* for later check. */
                /* Scalar; type int32. */
                yi_ijth_int32 = y_before + (int32_T)muSingleScalarRound
                  ((real32_T)(int16_T)(y_after - y_before) * r);

                /* Check if extrapolated value will cause int16 type to overflow */
                /* If so, assign maximum or minimum value. */
                /* If positive value  */
                if (yi_ijth_int32 > 0) {
                  /* If exceeds maximum value of type             */
                  if (yi_ijth_int32 >= 32767) {
                    yi_ijth_int32 = 32767;
                  }

                  /* If negative value */
                } else {
                  /* If exceeds minimum value of type */
                  if (yi_ijth_int32 <= -32767) {
                    yi_ijth_int32 = -32767;
                  }
                }

                /* Cast back to type int16 */
                yi_ijth = (int16_T)yi_ijth_int32;

                /* %%%%% --- Check whether interpolated value appears valid %%%%%% */
                if (ValidityChecksTF) {
                  /* Local function. */
                  /* Scalar; type int16. */
                  /* end local function */
                  /* ============================================================================================= */
                  /* ValidityCheck   Check whether interpolated / extrapolated value appears valid. */
                  /* Inline function */
                  /* Switch according to column */
                  switch (j + 1) {
                   case 1:
                    /* x-coordinate column */
                    /* Local function. */
                    /* end local function */
                    /* ============================================================================================= */
                    /* ValidityCheck_XY   Validity check for X- or Y-coordinate. */
                    /*  */
                    /*     Description: */
                    /*  */
                    /*     Check whether difference between before-value and interpolated / extrapolated value is greater   */
                    /*     than specified threshold. If so, set value at maximum of threshold.  */
                    /* Inline function */
                    Diff = (int16_T)(yi_ijth_int32 - y_before);
                    if (Diff > DiffMaxActual) {
                      yi_ijth = (int16_T)(y_before + DiffMaxActual);
                    } else {
                      if (Diff < (int16_T)-DiffMaxActual) {
                        yi_ijth = (int16_T)(y_before - DiffMaxActual);
                      }
                    }
                    break;

                   case 2:
                    /* y-coordinate column */
                    /* Local function. */
                    /* end local function */
                    /* ============================================================================================= */
                    /* ValidityCheck_XY   Validity check for X- or Y-coordinate. */
                    /*  */
                    /*     Description: */
                    /*  */
                    /*     Check whether difference between before-value and interpolated / extrapolated value is greater   */
                    /*     than specified threshold. If so, set value at maximum of threshold.  */
                    /* Inline function */
                    Diff = (int16_T)(yi_ijth_int32 - y_before);
                    if (Diff > DiffMaxActual) {
                      yi_ijth = (int16_T)(y_before + DiffMaxActual);
                    } else {
                      if (Diff < (int16_T)-DiffMaxActual) {
                        yi_ijth = (int16_T)(y_before - DiffMaxActual);
                      }
                    }
                    break;

                   case 3:
                    /* width column */
                    /* Local function. */
                    /* end local function */
                    /* ============================================================================================= */
                    /* ValidityCheck_WH   Validity check for width or height. */
                    /*  */
                    /*     Description: */
                    /*  */
                    /*     Check whether width or height value is less than 20. If so, then substitute the  */
                    /*     nearest-neighbor method in place of the linear method. */
                    /* Inline function */
                    if (yi_ijth_int32 < 20) {
                      /* Determine whether x_after or x_before nearest and assign. */
                      /* x_after nearest */
                      if (muSingleScalarAbs(x_after - f) <= muSingleScalarAbs
                          (x_before - f)) {
                        yi_ijth = y_after;

                        /* x_before nearest */
                      } else {
                        yi_ijth = y_before;
                      }
                    }
                    break;

                   default:
                    /* height column */
                    /* Local function. */
                    /* end local function */
                    /* ============================================================================================= */
                    /* ValidityCheck_WH   Validity check for width or height. */
                    /*  */
                    /*     Description: */
                    /*  */
                    /*     Check whether width or height value is less than 20. If so, then substitute the  */
                    /*     nearest-neighbor method in place of the linear method. */
                    /* Inline function */
                    if (yi_ijth_int32 < 20) {
                      /* Determine whether x_after or x_before nearest and assign. */
                      /* x_after nearest */
                      if (muSingleScalarAbs(x_after - f) <= muSingleScalarAbs
                          (x_before - f)) {
                        yi_ijth = y_after;

                        /* x_before nearest */
                      } else {
                        yi_ijth = y_before;
                      }
                    }
                    break;
                  }
                }
              }

              /* %%%%% Check whether interpolated value within specified distance from arbitrary value %%%%%%  */
              /* If arbitary check enabled */
              if (ArbitraryCheckTF && (j + 1 < 3)) {
                /* Check whether the interpolated X- or Y-coordinate is within a specified distance  */
                /* (DiffMaxArbitrary) from a specified X- or Y-coordinate. */
                /* Local function. */
                /* Scalar; type int16. */
                /* end local function */
                /* ============================================================================================= */
                /* ArbitraryCheck_XY   Check whether the interpolated / extrapolated X- or Y-coordinate is within a  */
                /*                     specified distance (DiffMaxArbitrary) from a specified X- or Y-coordinate */
                /*                     ( YArbitrary(j) ). */
                /*  */
                /*     Description: */
                /*  */
                /*     Check whether the interpolated / extrapolated X- or Y-coordinate is within a specified  */
                /*     distance (DiffMaxArbitrary) from a specified for X- or Y-coordinate ( YArbitrary(j) ). If so,  */
                /*     set value at maximum of threshold.  */
                /*  */
                /*     Inputs (subset): */
                /*  */
                /*     YArbitrary(1) = Specified arbitrary X-coordinate. */
                /*     YArbitrary(2) = Specified arbitrary Y-coordinate. */
                /* Inline function */
                /* Index either X- or Y-coordinate from arbitrary ROI */
                Diff = (int16_T)(yi_ijth - YArbitrary_data[j]);
                if (Diff > DiffMaxArbitrary) {
                  yi_ijth = (int16_T)(YArbitrary_data[j] + DiffMaxArbitrary);
                } else {
                  if (Diff < (int16_T)-DiffMaxArbitrary) {
                    yi_ijth = (int16_T)(YArbitrary_data[j] - DiffMaxArbitrary);
                  }
                }

                /* end local function */
                /* ============================================================================================= */
                /* Code-generation and build script */
                /* ============================================================================================= */
                /* Code-generation and build script used to generate C-language code and create the compiled version  */
                /* (Interp_mex) of the function. */
                /* { */
                /*  */
                /* %%%%% Specify variable-size input arguments %%%%%% */
                /*  */
                /* See Matlab documentation for coder.typeof. */
                /*                                     Example Code                 Upp. Bounds    Var. Size (T/F)  Type */
                /* xCode                = coder.typeof( zeros(50, 1, 'single'),      [50, 1],       [1, 0] );        %single */
                /* yCode                = coder.typeof( zeros(50, 4, 'int16'),       [50, 4],       [1, 1] );        %int16 */
                /* xiCode               = coder.typeof( zeros(50, 1, 'single'),      [50, 1],       [1, 0] );        %single                                                         */
                /* YArbitraryCode       = coder.typeof( zeros(1, 2, 'int16'),        [1, 2],        [1, 0] );        %int16 */
                /*  */
                /*  */
                /* %%%%% Specify fixed-size input arguments %%%%%% */
                /*  */
                /* LinearExtrapTFCode   = false; */
                /* InterpChecksTFCode   = false; */
                /* DiffMaxActualCode    = int16(0);  */
                /* VidObjWidthCode      = int16(0); */
                /* VidObjHeightCode     = int16(0);            */
                /* DiffMaxArbitraryCode = int16(0);     */
                /*  */
                /*                  */
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
                /* cfg.DynamicMemoryAllocation = 'off'; %disabled to improve efficiency as all variables have bounded size */
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
                /* codegen Interp.m -report -config cfg -args {xCode, yCode, xiCode, LinearExtrapTFCode, InterpChecksTFCode, DiffMaxActualCode, YArbitraryCode, DiffMaxArbitraryCode, VidObjWidthCode, VidObjHeightCode} */
                /*   */
                /* } */
              }

              /* %%%%% Assign %%%%%% */
              /* Scalar; type int16. */
              yi_ith_data[j] = yi_ijth;
            }
          } else {
            /* Flag indicating ith xi value is to right of domain of x */
            /* Nearest-neighbor extrapolation */
            /* Local function. */
            /* 1 x nColsY row vector; type int16.    */
            /* end local function */
            /* ============================================================================================= */
            /* ExtrapNearest   Nearest-neighbor extrapolation of y at single time point (xi). */
            /* Inline function */
            /* Preallocate output for ith yi values */
            /* If ith xi value is to left of domain of x */
            /* Loop across columns of y */
            for (j = 0; j < nColsY; j++) {
              /* Assign from last row of y */
              yi_ijth = y_data[x_length + y_size[0] * j];

              /* If arbitary check enabled */
              if (ArbitraryCheckTF && (j + 1 < 3)) {
                /* Check whether the interpolated X- or Y-coordinate is within a specified distance  */
                /* (DiffMaxArbitrary) from a specified X- or Y-coordinate. */
                /* Local function. */
                /* Scalar; type int16. */
                /* end local function */
                /* ============================================================================================= */
                /* ArbitraryCheck_XY   Check whether the interpolated / extrapolated X- or Y-coordinate is within a  */
                /*                     specified distance (DiffMaxArbitrary) from a specified X- or Y-coordinate */
                /*                     ( YArbitrary(j) ). */
                /*  */
                /*     Description: */
                /*  */
                /*     Check whether the interpolated / extrapolated X- or Y-coordinate is within a specified  */
                /*     distance (DiffMaxArbitrary) from a specified for X- or Y-coordinate ( YArbitrary(j) ). If so,  */
                /*     set value at maximum of threshold.  */
                /*  */
                /*     Inputs (subset): */
                /*  */
                /*     YArbitrary(1) = Specified arbitrary X-coordinate. */
                /*     YArbitrary(2) = Specified arbitrary Y-coordinate. */
                /* Inline function */
                /* Index either X- or Y-coordinate from arbitrary ROI */
                Diff = (int16_T)(yi_ijth - YArbitrary_data[j]);
                if (Diff > DiffMaxArbitrary) {
                  yi_ijth = (int16_T)(YArbitrary_data[j] + DiffMaxArbitrary);
                } else {
                  if (Diff < (int16_T)-DiffMaxArbitrary) {
                    yi_ijth = (int16_T)(YArbitrary_data[j] - DiffMaxArbitrary);
                  }
                }

                /* end local function */
                /* ============================================================================================= */
                /* Code-generation and build script */
                /* ============================================================================================= */
                /* Code-generation and build script used to generate C-language code and create the compiled version  */
                /* (Interp_mex) of the function. */
                /* { */
                /*  */
                /* %%%%% Specify variable-size input arguments %%%%%% */
                /*  */
                /* See Matlab documentation for coder.typeof. */
                /*                                     Example Code                 Upp. Bounds    Var. Size (T/F)  Type */
                /* xCode                = coder.typeof( zeros(50, 1, 'single'),      [50, 1],       [1, 0] );        %single */
                /* yCode                = coder.typeof( zeros(50, 4, 'int16'),       [50, 4],       [1, 1] );        %int16 */
                /* xiCode               = coder.typeof( zeros(50, 1, 'single'),      [50, 1],       [1, 0] );        %single                                                         */
                /* YArbitraryCode       = coder.typeof( zeros(1, 2, 'int16'),        [1, 2],        [1, 0] );        %int16 */
                /*  */
                /*  */
                /* %%%%% Specify fixed-size input arguments %%%%%% */
                /*  */
                /* LinearExtrapTFCode   = false; */
                /* InterpChecksTFCode   = false; */
                /* DiffMaxActualCode    = int16(0);  */
                /* VidObjWidthCode      = int16(0); */
                /* VidObjHeightCode     = int16(0);            */
                /* DiffMaxArbitraryCode = int16(0);     */
                /*  */
                /*                  */
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
                /* cfg.DynamicMemoryAllocation = 'off'; %disabled to improve efficiency as all variables have bounded size */
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
                /* codegen Interp.m -report -config cfg -args {xCode, yCode, xiCode, LinearExtrapTFCode, InterpChecksTFCode, DiffMaxActualCode, YArbitraryCode, DiffMaxArbitraryCode, VidObjWidthCode, VidObjHeightCode} */
                /*   */
                /* } */
              }

              yi_ith_data[j] = yi_ijth;
            }
          }

          /* Set back x_idx by one for use for i+1th xi element. */
          /* xi is assumed to be sorted, but the values are not assumed to be unique, so x_idx */
          /* should start back by one in case the next value of xi is the same as the current. */
          /* Even is all values are unique, floating-point imprecision could effectively cause */
          /* some to be non-unique. */
          x_idx--;
          exitg1 = 1;
        } else {
          if (x_data[x_idx] >= f) {
            /* Assign x indices */
            /* Linear interpolation */
            /* Local function. */
            /* 1 x nColsY row vector; type int16.                 */
            /* end main function */
            /* ============================================================================================= */
            /* Local functions */
            /* ============================================================================================= */
            /* ============================================================================================= */
            /* InterpLinear   Linear interpolation of y at a single time point (xi). */
            /* Inline function */
            /* Preallocate output for ith yi values */
            /* Assign x values   */
            /* Scalars; type single. */
            x_before = x_data[x_idx - 1];
            x_after = x_data[x_idx];

            /* Proportion of interpolated time interval to actual time interval */
            /* Scalar; type single. */
            r = (f - x_before) / (x_data[x_idx] - x_before);

            /* Loop across columns of y */
            for (j = 0; j < nColsY; j++) {
              /* y value that comes before time point to be interpolated */
              /* Scalar; type int16. */
              yi_ijth_int32 = y_size[0] * j;
              y_before = y_data[(x_idx + yi_ijth_int32) - 1];

              /* y value that comes after time point to be interpolated */
              /* Scalar; type int16. */
              y_after = y_data[x_idx + yi_ijth_int32];

              /* %%%%% Skip interpolation %%%%%% */
              /* If y values same, assign one of them as interpolated value */
              if (y_before == y_after) {
                yi_ijth = y_before;

                /* %%%%% Interpolate %%%%%%          */
              } else {
                /* Step 1 */
                /* Interpolated distance of y. */
                /* Multipy interpolated time-interval proportion by actual change in y. */
                /* Cast to floating-point type to multiply.   */
                /* Step 2 */
                /* Add distance to most immediate previous actual y value. */
                yi_ijth = (int16_T)(y_before + (int16_T)muSingleScalarRound
                                    ((real32_T)(int16_T)(y_after - y_before) * r));

                /* %%%%% --- Check whether interpolated value appears valid %%%%%% */
                if (ValidityChecksTF) {
                  /* Local function. */
                  /* Scalar; type int16. */
                  /* end local function */
                  /* ============================================================================================= */
                  /* ValidityCheck   Check whether interpolated / extrapolated value appears valid. */
                  /* Inline function */
                  /* Switch according to column */
                  switch (j + 1) {
                   case 1:
                    /* x-coordinate column */
                    /* Local function. */
                    /* end local function */
                    /* ============================================================================================= */
                    /* ValidityCheck_XY   Validity check for X- or Y-coordinate. */
                    /*  */
                    /*     Description: */
                    /*  */
                    /*     Check whether difference between before-value and interpolated / extrapolated value is greater   */
                    /*     than specified threshold. If so, set value at maximum of threshold.  */
                    /* Inline function */
                    Diff = (int16_T)(yi_ijth - y_before);
                    if (Diff > DiffMaxActual) {
                      yi_ijth = (int16_T)(y_before + DiffMaxActual);
                    } else {
                      if (Diff < (int16_T)-DiffMaxActual) {
                        yi_ijth = (int16_T)(y_before - DiffMaxActual);
                      }
                    }
                    break;

                   case 2:
                    /* y-coordinate column */
                    /* Local function. */
                    /* end local function */
                    /* ============================================================================================= */
                    /* ValidityCheck_XY   Validity check for X- or Y-coordinate. */
                    /*  */
                    /*     Description: */
                    /*  */
                    /*     Check whether difference between before-value and interpolated / extrapolated value is greater   */
                    /*     than specified threshold. If so, set value at maximum of threshold.  */
                    /* Inline function */
                    Diff = (int16_T)(yi_ijth - y_before);
                    if (Diff > DiffMaxActual) {
                      yi_ijth = (int16_T)(y_before + DiffMaxActual);
                    } else {
                      if (Diff < (int16_T)-DiffMaxActual) {
                        yi_ijth = (int16_T)(y_before - DiffMaxActual);
                      }
                    }
                    break;

                   case 3:
                    /* width column */
                    /* Local function. */
                    /* end local function */
                    /* ============================================================================================= */
                    /* ValidityCheck_WH   Validity check for width or height. */
                    /*  */
                    /*     Description: */
                    /*  */
                    /*     Check whether width or height value is less than 20. If so, then substitute the  */
                    /*     nearest-neighbor method in place of the linear method. */
                    /* Inline function */
                    if (yi_ijth < 20) {
                      /* Determine whether x_after or x_before nearest and assign. */
                      /* x_after nearest */
                      if (muSingleScalarAbs(x_after - f) <= muSingleScalarAbs
                          (x_before - f)) {
                        yi_ijth = y_after;

                        /* x_before nearest */
                      } else {
                        yi_ijth = y_before;
                      }
                    }
                    break;

                   default:
                    /* height column */
                    /* Local function. */
                    /* end local function */
                    /* ============================================================================================= */
                    /* ValidityCheck_WH   Validity check for width or height. */
                    /*  */
                    /*     Description: */
                    /*  */
                    /*     Check whether width or height value is less than 20. If so, then substitute the  */
                    /*     nearest-neighbor method in place of the linear method. */
                    /* Inline function */
                    if (yi_ijth < 20) {
                      /* Determine whether x_after or x_before nearest and assign. */
                      /* x_after nearest */
                      if (muSingleScalarAbs(x_after - f) <= muSingleScalarAbs
                          (x_before - f)) {
                        yi_ijth = y_after;

                        /* x_before nearest */
                      } else {
                        yi_ijth = y_before;
                      }
                    }
                    break;
                  }
                }
              }

              /* %%%%% Check whether interpolated value within specified distance from arbitrary value %%%%%%  */
              /* If arbitary check enabled    */
              if (ArbitraryCheckTF && (j + 1 < 3)) {
                /* Check whether the interpolated X- or Y-coordinate is within a specified distance  */
                /* (DiffMaxArbitrary) from a specified X- or Y-coordinate. */
                /* Local function. */
                /* Scalar; type int16. */
                /* end local function */
                /* ============================================================================================= */
                /* ArbitraryCheck_XY   Check whether the interpolated / extrapolated X- or Y-coordinate is within a  */
                /*                     specified distance (DiffMaxArbitrary) from a specified X- or Y-coordinate */
                /*                     ( YArbitrary(j) ). */
                /*  */
                /*     Description: */
                /*  */
                /*     Check whether the interpolated / extrapolated X- or Y-coordinate is within a specified  */
                /*     distance (DiffMaxArbitrary) from a specified for X- or Y-coordinate ( YArbitrary(j) ). If so,  */
                /*     set value at maximum of threshold.  */
                /*  */
                /*     Inputs (subset): */
                /*  */
                /*     YArbitrary(1) = Specified arbitrary X-coordinate. */
                /*     YArbitrary(2) = Specified arbitrary Y-coordinate. */
                /* Inline function */
                /* Index either X- or Y-coordinate from arbitrary ROI */
                Diff = (int16_T)(yi_ijth - YArbitrary_data[j]);
                if (Diff > DiffMaxArbitrary) {
                  yi_ijth = (int16_T)(YArbitrary_data[j] + DiffMaxArbitrary);
                } else {
                  if (Diff < (int16_T)-DiffMaxArbitrary) {
                    yi_ijth = (int16_T)(YArbitrary_data[j] - DiffMaxArbitrary);
                  }
                }

                /* end local function */
                /* ============================================================================================= */
                /* Code-generation and build script */
                /* ============================================================================================= */
                /* Code-generation and build script used to generate C-language code and create the compiled version  */
                /* (Interp_mex) of the function. */
                /* { */
                /*  */
                /* %%%%% Specify variable-size input arguments %%%%%% */
                /*  */
                /* See Matlab documentation for coder.typeof. */
                /*                                     Example Code                 Upp. Bounds    Var. Size (T/F)  Type */
                /* xCode                = coder.typeof( zeros(50, 1, 'single'),      [50, 1],       [1, 0] );        %single */
                /* yCode                = coder.typeof( zeros(50, 4, 'int16'),       [50, 4],       [1, 1] );        %int16 */
                /* xiCode               = coder.typeof( zeros(50, 1, 'single'),      [50, 1],       [1, 0] );        %single                                                         */
                /* YArbitraryCode       = coder.typeof( zeros(1, 2, 'int16'),        [1, 2],        [1, 0] );        %int16 */
                /*  */
                /*  */
                /* %%%%% Specify fixed-size input arguments %%%%%% */
                /*  */
                /* LinearExtrapTFCode   = false; */
                /* InterpChecksTFCode   = false; */
                /* DiffMaxActualCode    = int16(0);  */
                /* VidObjWidthCode      = int16(0); */
                /* VidObjHeightCode     = int16(0);            */
                /* DiffMaxArbitraryCode = int16(0);     */
                /*  */
                /*                  */
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
                /* cfg.DynamicMemoryAllocation = 'off'; %disabled to improve efficiency as all variables have bounded size */
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
                /* codegen Interp.m -report -config cfg -args {xCode, yCode, xiCode, LinearExtrapTFCode, InterpChecksTFCode, DiffMaxActualCode, YArbitraryCode, DiffMaxArbitraryCode, VidObjWidthCode, VidObjHeightCode} */
                /*   */
                /* } */
              }

              /* %%%%% Assign %%%%%% */
              yi_ith_data[j] = yi_ijth;
            }

            /* Set back x_idx by one for use for i+1th xi element. */
            /* xi is assumed to be sorted, but the values are not assumed to be unique, so x_idx */
            /* should start back by one in case the next value of xi is the same as the current. */
            /* Even is all values are unique, floating-point imprecision could effectively cause */
            /* some to be non-unique. */
            x_idx--;
            exitg1 = 1;
          }
        }
      } while (exitg1 == 0);
    }

    /* Check whether interpolated values are within frame dimensions */
    /* If not, adjust to be within frame dimensions.         */
    if (ValidityChecksTF) {
      /* Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder */
      /* 'FacePulseRate'. */
      /* 1 x nColsY row vector; type int16. */
      /* ROIAdjustIfExceedsFrameDims   Verify whether proposed widths and heights of ROIs exceed frame  */
      /*                               dimensions and, if so, modify them to conform to frame dimensions. */
      /*                                */
      /*     Helper function to function FacePulseRate. */
      /*     Within function FacePulseRate, called by functions ROIResize, ROIMeans_FirstRead_Extrapolate, */
      /*     SkinDetect_EnlargeROI, ROIMSIR, ROIMSIR_MatchSize, ROIMSIR_DetectionSmooth,   */
      /*     ROIMSIR_Interpolate, and ROIMSIR_FrameByFrameSmooth.    */
      /*  */
      /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
      /*  */
      /*     Description: */
      /*  */
      /*     This function verifies that ROIs that have had modifications to their sizes are still within */
      /*     the dimensions of the frame. If not, this function adjusts the dimensions (and, consequently,   */
      /*     the spatial coordinates) to conform to the frame dimensions. */
      /*  */
      /*     Note:  */
      /*  */
      /*     Intended only for use with integer types as rounding is not conducted. For modification for  */
      /*     use with floating-point types, rounding would be necessary as ROI values should be integers. */
      /*  */
      /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
      /*     the Responsible AI License (RAIL). */
      /* %%%%% Validate inputs %%%%%% */
      /* Exit if empty */
      if (nColsY != 0) {
        /* Validate whether input ROIsProposed is type int16. */
        /* Must be an integer type because no rounding is conducted. */
        /* Should be type int16 because the function is implemented to assign values of this type. */
        /* A non-matching type would be due to an implementation error. */
        /* %%%%% Running in code generation %%%%%% */
        /* When running in code generation, use for-loops. When running in Matlab code, use vectorization. */
        /* code generation running */
        /* Inline function */
        /* %%%%% --- Verify, and adjust if necessary, X-coordinates and widths %%%%%% */
        /* Adjust left-side X-coordinate if exceeds frame dimensions: */
        y_after = yi_ith_data[0];
        if (yi_ith_data[0] < 1) {
          y_after = 1;

          /* recent code mod */
          yi_ith_data[0] = 1;
        } else {
          if (yi_ith_data[0] > VidObjWidth) {
            y_after = VidObjWidth;

            /* recent code mod */
            yi_ith_data[0] = VidObjWidth;
          }
        }

        /* Adjust right-side X-coordinate if exceeds frame dimensions: */
        Diff = (int16_T)((int16_T)(y_after + yi_ith_data[2]) - 1);
        if (Diff > VidObjWidth) {
          Diff = VidObjWidth;
          yi_ith_data[2] = (int16_T)((int16_T)(VidObjWidth - y_after) + 1);
        } else {
          if (Diff < 1) {
            Diff = 1;
            y_after = 1;
            yi_ith_data[0] = 1;
            yi_ith_data[2] = 1;
          }
        }

        /* Adjust width if exceeds frame dimensions: */
        y_after = (int16_T)((int16_T)(Diff - y_after) + 1);
        if (y_after > VidObjWidth) {
          yi_ith_data[2] = VidObjWidth;
        } else {
          if (y_after < 1) {
            yi_ith_data[2] = 1;
          }
        }

        /* %%%%% --- Verify, and adjust if necessary, Y-coordinates and heights %%%%%% */
        /* Adjust top-side Y-coordinate if exceeds frame dimensions: */
        y_after = yi_ith_data[1];
        if (yi_ith_data[1] < 1) {
          y_after = 1;

          /* recent code mod */
          yi_ith_data[1] = 1;
        } else {
          if (yi_ith_data[1] > VidObjHeight) {
            y_after = VidObjHeight;

            /* recent code mod */
            yi_ith_data[1] = VidObjHeight;
          }
        }

        /* Adjust bottom-side Y-coordinate if exceeds frame dimensions: */
        Diff = (int16_T)((int16_T)(y_after + yi_ith_data[3]) - 1);
        if (Diff > VidObjHeight) {
          Diff = VidObjHeight;
          yi_ith_data[3] = (int16_T)((int16_T)(VidObjHeight - y_after) + 1);
        } else {
          if (Diff < 1) {
            Diff = 1;
            y_after = 1;
            yi_ith_data[1] = 1;
            yi_ith_data[3] = 1;
          }
        }

        /* Adjust height value if exceeds frame dimensions: */
        y_after = (int16_T)((int16_T)(Diff - y_after) + 1);
        if (y_after > VidObjHeight) {
          yi_ith_data[3] = VidObjHeight;
        } else {
          if (y_after < 1) {
            yi_ith_data[3] = 1;
          }
        }

        /* %%%%% Code generation not running %%%%%% */
      } else {
        /* Exit function */
      }

      /* end function */
      /* ============================================================================================= */
      /* Code-generation and build script */
      /* ============================================================================================= */
      /* Code-generation and build script used to generate C-language code and create the compiled version  */
      /* (ROIAdjustIfExceedsFrameDims_mex) of the function. */
      /* { */
      /*  */
      /* %%%%% Specify variable-size input arguments %%%%%% */
      /*  */
      /* See Matlab documentation for coder.typeof. */
      /*  */
      /*                                   Example Code               Upp. Bounds   Var. Size (T/F)  Type */
      /* ROIsProposedCode   = coder.typeof( zeros(500, 4, 'int16'),    [inf, 4],     [1, 0] );        %int16 */
      /*            */
      /*        */
      /* %%%%% Specify fixed-size input arguments %%%%%% */
      /*  */
      /* VidObjWidthCode  = int16(0);          */
      /* VidObjHeightCode = int16(0); */
      /*                    */
      /*  */
      /* %%%%% Set configurations to increase performance %%%%%% */
      /*  */
      /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
      /* "Optimization Strategies" */
      /*  */
      /* cfg = coder.config('mex'); */
      /* cfg.GlobalDataSyncMethod = 'NoSync'; */
      /* cfg.ConstantInputs = 'IgnoreValues'; */
      /* cfg.ExtrinsicCalls = true; %permit to show assert error */
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
      /* vector. As function setbuildargs will be evaluated from text, use double ' quotes for each */
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
      /* codegen ROIAdjustIfExceedsFrameDims.m -report -config cfg -args {ROIsProposedCode, VidObjWidthCode, VidObjHeightCode} */
      /*                  */
      /* } */
    }

    /* Assign interpolated / extrapolated values of yi at xi */
    for (yi_ijth_int32 = 0; yi_ijth_int32 < nColsY; yi_ijth_int32++) {
      yi_data[xi_idx + yi_size[0] * yi_ijth_int32] = yi_ith_data[yi_ijth_int32];
    }
  }
}

/* End of code generation (Interp.c) */
