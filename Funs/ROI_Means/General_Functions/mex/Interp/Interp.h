/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Interp.h
 *
 * Code generation for function 'Interp'
 *
 */

#pragma once

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mex.h"
#include "emlrt.h"
#include "rtwtypes.h"
#include "Interp_types.h"

/* Function Declarations */
void Interp(const real32_T x_data[], const int32_T x_size[1], const int16_T
            y_data[], const int32_T y_size[2], const real32_T xi_data[], const
            int32_T xi_size[1], boolean_T LinearExtrapTF, boolean_T
            ValidityChecksTF, int16_T DiffMaxActual, const int16_T
            YArbitrary_data[], const int32_T YArbitrary_size[2], int16_T
            DiffMaxArbitrary, int16_T VidObjWidth, int16_T VidObjHeight, int16_T
            yi_data[], int32_T yi_size[2]);

/* End of code generation (Interp.h) */
