/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * IndexAndMean_LogIdx.c
 *
 * Code generation for function 'IndexAndMean_LogIdx'
 *
 */

/* Include files */
#include "IndexAndMean_LogIdx.h"
#include "IndexAndMean_LogIdx_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void IndexAndMean_LogIdx(emlrtCTX aTLS, const emxArray_uint8_T *R_Uint8, const
  emxArray_uint8_T *G_Uint8, const emxArray_uint8_T *B_Uint8, const
  emxArray_real32_T *Luminance_Single, const emxArray_boolean_T *LogIdx, int32_T
  NRows, int32_T NCols, uint32_T TrueCount, boolean_T TakeLuminanceMeanTF,
  real_T RGBMeans_Double[3], real_T *LuminanceMean_Double)
{
  int32_T NElements;
  real32_T SumR;
  real32_T SumG;
  uint32_T SumR_uint32;
  real32_T SumB;
  uint32_T SumG_uint32;
  int32_T i;
  uint32_T SumB_uint32;
  real32_T SumL;
  real32_T SumBPrime;
  real32_T SumGPrime;
  uint32_T SumB_uint32Prime;
  real32_T SumRPrime;
  uint32_T SumG_uint32Prime;
  real32_T SumLPrime;
  uint32_T SumR_uint32Prime;
  int32_T b_i;
  jmp_buf * volatile emlrtJBStack;

  /* IndexAndMean_LogIdx   Take the mean of each of four matrices according to a logical index.                         */
  /*   */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by function ROIMeans_TakeMeans.     */
  /*  */
  /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*     Description: */
  /*  */
  /*     Take the mean of each of three matrices of type uint8 according to a logical index. */
  /*                          */
  /*     Inputs */
  /*  */
  /*         R_Uint8,  */
  /*         G_Uint8,  */
  /*         B_Uint8                = R, G, and B color channels from which to take means. M x N   */
  /*                                  matrices, type uint8. */
  /*         Luminance_Single       = Luminance channel from which to take mean. M x N matrix, type  */
  /*                                  single. */
  /*         LogIdx                 = Logical matrix indicating elements from which to take means. M x    */
  /*                                  N matrix; type logical.  */
  /*         NRows                  = Number of rows of one of the above inputs. Scalar; type int32. */
  /*         NCols                  = Number of columns of one of the above inputs. Scalar; type int32. */
  /*         TrueCount              = Number of elements in LogIdx that are true. Scalar; type uint32. */
  /*         TakeLuminanceMeanTF    = Whether to take the mean of the luminance matrix. Scalar; type */
  /*                                  logical.                         */
  /*                                */
  /*     Outputs */
  /*  */
  /*         RGBMeans_Double      = Means of the R, G, and B color channels. 1 x 3 row vector; type  */
  /*                                double.  */
  /*         LuminanceMean_Double = Mean of the luminance channel. Scalar; type double. */
  /*  */
  /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
  /*     the Responsible AI License (RAIL). */
  /* Inline function */
  /* Preallocate outputs  */
  *LuminanceMean_Double = 0.0;

  /* The number of elements in an input matrix */
  /* Scalar; type int32. */
  NElements = NRows * NCols - 1;

  /* %%%%%% If taking the luminance mean is enabled %%%%%%% */
  if (TakeLuminanceMeanTF) {
    /* %%%%% --- Optimized with integer arithmetic %%%%%% */
    /* If matrix IsSkinMask is under specified size, use algorithm optimized with integer arithmetic. */
    if (NElements + 1 < 15686000) {
      /* Initialize accumulating variables */
      /* Use a type that is large enought to prevent overflow. */
      /* Note: for LuminanceMatrix_Single, which is of type single, it less efficient to cast to */
      /* type uint32 than to stay in type single. */
      SumR_uint32 = 0U;
      SumG_uint32 = 0U;
      SumB_uint32 = 0U;
      SumL = 0.0F;
      emlrtEnterParallelRegion(aTLS, omp_in_parallel());
      emlrtPushJmpBuf(aTLS, &emlrtJBStack);

#pragma omp parallel \
 num_threads(emlrtAllocRegionTLSs(aTLS, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs())) \
 private(SumLPrime,SumB_uint32Prime,SumG_uint32Prime,SumR_uint32Prime,b_i)

      {
        SumR_uint32Prime = 0U;
        SumG_uint32Prime = 0U;
        SumB_uint32Prime = 0U;
        SumLPrime = 0.0F;

#pragma omp for nowait

        for (i = 0; i <= NElements; i++) {
          b_i = i + 1;

          /* Loop across elements, accumulating sum */
          /* If element classified as skin */
          if (LogIdx->data[b_i - 1]) {
            /* Accumulate */
            /* Cast elements of type uint8 to type uint32. */
            SumR_uint32Prime += R_Uint8->data[b_i - 1];
            SumG_uint32Prime += G_Uint8->data[b_i - 1];
            SumB_uint32Prime += B_Uint8->data[b_i - 1];
            SumLPrime += Luminance_Single->data[b_i - 1];
          }
        }

        omp_set_nest_lock(&emlrtNestLockGlobal);

        {
          SumR_uint32 += SumR_uint32Prime;
          SumG_uint32 += SumG_uint32Prime;
          SumB_uint32 += SumB_uint32Prime;
          SumL += SumLPrime;
        }

        omp_unset_nest_lock(&emlrtNestLockGlobal);
      }

      emlrtPopJmpBuf(aTLS, &emlrtJBStack);
      emlrtExitParallelRegion(aTLS, omp_in_parallel());

      /* Take means and cast to double: */
      /* Cast to type double for use as denominator */
      RGBMeans_Double[0] = (real_T)SumR_uint32 / (real_T)TrueCount;
      RGBMeans_Double[1] = (real_T)SumG_uint32 / (real_T)TrueCount;
      RGBMeans_Double[2] = (real_T)SumB_uint32 / (real_T)TrueCount;
      *LuminanceMean_Double = SumL / (real_T)TrueCount;

      /* %%%%% --- Not optimized with integer arithmetic %%%%%%     */
    } else {
      /* Initialize accumulating variables */
      /* Use a type that is large enought to prevent overflow. */
      SumR = 0.0F;
      SumG = 0.0F;
      SumB = 0.0F;
      SumL = 0.0F;
      emlrtEnterParallelRegion(aTLS, omp_in_parallel());
      emlrtPushJmpBuf(aTLS, &emlrtJBStack);

#pragma omp parallel \
 num_threads(emlrtAllocRegionTLSs(aTLS, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs())) \
 private(SumLPrime,SumBPrime,SumGPrime,SumRPrime)

      {
        SumRPrime = 0.0F;
        SumGPrime = 0.0F;
        SumBPrime = 0.0F;
        SumLPrime = 0.0F;

#pragma omp for nowait

        for (i = 0; i <= NElements; i++) {
          /* Loop across elements, accumulating sum */
          /* If element classified as skin */
          if (LogIdx->data[i]) {
            /* Cast to type single and accumulate */
            SumRPrime += (real32_T)R_Uint8->data[i];
            SumGPrime += (real32_T)G_Uint8->data[i];
            SumBPrime += (real32_T)B_Uint8->data[i];
            SumLPrime += Luminance_Single->data[i];
          }
        }

        omp_set_nest_lock(&emlrtNestLockGlobal);

        {
          SumR += SumRPrime;
          SumG += SumGPrime;
          SumB += SumBPrime;
          SumL += SumLPrime;
        }

        omp_unset_nest_lock(&emlrtNestLockGlobal);
      }

      emlrtPopJmpBuf(aTLS, &emlrtJBStack);
      emlrtExitParallelRegion(aTLS, omp_in_parallel());

      /* Take means and cast to double: */
      /* Cast to type double for use as denominator */
      RGBMeans_Double[0] = SumR / (real_T)TrueCount;
      RGBMeans_Double[1] = SumG / (real_T)TrueCount;
      RGBMeans_Double[2] = SumB / (real_T)TrueCount;
      *LuminanceMean_Double = SumL / (real_T)TrueCount;
    }

    /* %%%%%% If taking the luminance mean is not enabled %%%%%%% */
  } else {
    /* %%%%% --- Optimized with integer arithmetic %%%%%% */
    /* If matrix IsSkinMask is under specified size, use algorithm optimized with integer arithmetic. */
    if (NElements + 1 < 15686000) {
      /* Initialize accumulating variables */
      /* Use a type that is large enought to prevent overflow. */
      SumR_uint32 = 0U;
      SumG_uint32 = 0U;
      SumB_uint32 = 0U;
      emlrtEnterParallelRegion(aTLS, omp_in_parallel());
      emlrtPushJmpBuf(aTLS, &emlrtJBStack);

#pragma omp parallel \
 num_threads(emlrtAllocRegionTLSs(aTLS, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs())) \
 private(SumB_uint32Prime,SumG_uint32Prime,SumR_uint32Prime,b_i)

      {
        SumR_uint32Prime = 0U;
        SumG_uint32Prime = 0U;
        SumB_uint32Prime = 0U;

#pragma omp for nowait

        for (i = 0; i <= NElements; i++) {
          b_i = i + 1;

          /* Loop across elements, accumulating sum */
          /* If element classified as skin */
          if (LogIdx->data[b_i - 1]) {
            /* Cast to type uint32 and accumulate */
            SumR_uint32Prime += R_Uint8->data[b_i - 1];
            SumG_uint32Prime += G_Uint8->data[b_i - 1];
            SumB_uint32Prime += B_Uint8->data[b_i - 1];
          }
        }

        omp_set_nest_lock(&emlrtNestLockGlobal);

        {
          SumR_uint32 += SumR_uint32Prime;
          SumG_uint32 += SumG_uint32Prime;
          SumB_uint32 += SumB_uint32Prime;
        }

        omp_unset_nest_lock(&emlrtNestLockGlobal);
      }

      emlrtPopJmpBuf(aTLS, &emlrtJBStack);
      emlrtExitParallelRegion(aTLS, omp_in_parallel());

      /* Take means and cast to double: */
      /* Cast to type double for use as denominator */
      RGBMeans_Double[0] = (real_T)SumR_uint32 / (real_T)TrueCount;
      RGBMeans_Double[1] = (real_T)SumG_uint32 / (real_T)TrueCount;
      RGBMeans_Double[2] = (real_T)SumB_uint32 / (real_T)TrueCount;

      /* %%%%% --- Not optimized with integer arithmetic %%%%%%     */
    } else {
      /* Initialize accumulating variables */
      SumR = 0.0F;
      SumG = 0.0F;
      SumB = 0.0F;
      emlrtEnterParallelRegion(aTLS, omp_in_parallel());
      emlrtPushJmpBuf(aTLS, &emlrtJBStack);

#pragma omp parallel \
 num_threads(emlrtAllocRegionTLSs(aTLS, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs())) \
 private(SumBPrime,SumGPrime,SumRPrime)

      {
        SumRPrime = 0.0F;
        SumGPrime = 0.0F;
        SumBPrime = 0.0F;

#pragma omp for nowait

        for (i = 0; i <= NElements; i++) {
          /* Loop across elements, accumulating sum */
          /* If element classified as skin */
          if (LogIdx->data[i]) {
            /* Cast to type single and accumulate */
            SumRPrime += (real32_T)R_Uint8->data[i];
            SumGPrime += (real32_T)G_Uint8->data[i];
            SumBPrime += (real32_T)B_Uint8->data[i];
          }
        }

        omp_set_nest_lock(&emlrtNestLockGlobal);

        {
          SumR += SumRPrime;
          SumG += SumGPrime;
          SumB += SumBPrime;
        }

        omp_unset_nest_lock(&emlrtNestLockGlobal);
      }

      emlrtPopJmpBuf(aTLS, &emlrtJBStack);
      emlrtExitParallelRegion(aTLS, omp_in_parallel());

      /* Take means and cast to double: */
      /* Cast to type double for use as denominator */
      RGBMeans_Double[0] = SumR / (real_T)TrueCount;
      RGBMeans_Double[1] = SumG / (real_T)TrueCount;
      RGBMeans_Double[2] = SumB / (real_T)TrueCount;
    }
  }

  /* end function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (IndexAndMean_Uint8_LogIdx_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /*                                     Example Code                 Upp. Bounds    Var. Size (T/F)   Type */
  /* Matrix1_Uint8Code    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],    [1, 1] );         %uint8 */
  /* Matrix2_Uint8Code    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],    [1, 1] );         %uint8 */
  /* Matrix3_Uint8Code    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],    [1, 1] );         %uint8 */
  /* Luminance_SingleCode = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],    [1, 1] );         %single */
  /* LogIdxCode           = coder.typeof( false(500, 500),             [inf, inf],    [1, 1] );         %logical  */
  /*  */
  /*  */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /* NRowsCode               = int32(0); */
  /* NColsCode               = int32(0); */
  /* TrueCountCode           = uint32(0); */
  /* TakeLuminanceMeanTFCode = false; */
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
  /* Second argument: specify a cell array of compiler-specific flags, where each flag is a character */
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
  /* codegen IndexAndMean_LogIdx.m -report -config cfg -args {Matrix1_Uint8Code, Matrix2_Uint8Code, Matrix3_Uint8Code, Luminance_SingleCode, LogIdxCode, NRowsCode, NColsCode, TrueCountCode, TakeLuminanceMeanTFCode} */
  /*               */
  /* } */
}

/* End of code generation (IndexAndMean_LogIdx.c) */
