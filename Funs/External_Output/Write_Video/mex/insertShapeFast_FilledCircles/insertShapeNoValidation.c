/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertShapeNoValidation.c
 *
 * Code generation for function 'insertShapeNoValidation'
 *
 */

/* Include files */
#include "insertShapeNoValidation.h"
#include "insertShapeFast_FilledCircles.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void validateAndParseInputs(const int16_T position_data[], const int32_T
  position_size[2], int32_T positionOut_data[], int32_T positionOut_size[2],
  uint8_T colorOut_data[], int32_T colorOut_size[2])
{
  int32_T ntilerows;
  int32_T ibmat;
  int32_T jcol;
  positionOut_size[0] = position_size[0];
  positionOut_size[1] = 3;
  ntilerows = position_size[0] * position_size[1];
  for (ibmat = 0; ibmat < ntilerows; ibmat++) {
    positionOut_data[ibmat] = position_data[ibmat];
  }

  colorOut_size[0] = (int8_T)position_size[0];
  colorOut_size[1] = 3;
  ntilerows = (int8_T)position_size[0];
  for (jcol = 0; jcol < 3; jcol++) {
    ibmat = jcol * ntilerows;
    if (0 <= ntilerows - 1) {
      memset(&colorOut_data[ibmat], 0, ((ntilerows + ibmat) - ibmat) * sizeof
             (uint8_T));
    }
  }
}

/* End of code generation (insertShapeNoValidation.c) */
