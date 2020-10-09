/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * bwconncomp.c
 *
 * Code generation for function 'bwconncomp'
 *
 */

/* Include files */
#include "bwconncomp.h"
#include "SkinDetect_data.h"
#include "SkinDetect_emxutil.h"
#include "SkinDetect_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void bwconncomp(const emxArray_boolean_T *varargin_1, real_T *CC_Connectivity,
                real_T CC_ImageSize[2], real_T *CC_NumObjects, emxArray_real_T
                *CC_RegionIndices, emxArray_int32_T *CC_RegionLengths)
{
  emxArray_int16_T *endRow;
  emxArray_int16_T *startCol;
  emxArray_int16_T *startRow;
  emxArray_int32_T *idxCount;
  emxArray_int32_T *labelsRenumbered;
  emxArray_int32_T *pixelIdxList;
  emxArray_int32_T *x;
  real_T numComponents;
  real_T y;
  int32_T currentColumn;
  int32_T firstRunOnThisColumn;
  int32_T k;
  int32_T lastRunOnPreviousColumn;
  int32_T numRuns;
  int32_T p;
  int32_T root_k;
  int32_T root_p;
  int32_T row;
  int32_T runCounter;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  numRuns = 0;
  if ((varargin_1->size[0] != 0) && (varargin_1->size[1] != 0)) {
    firstRunOnThisColumn = varargin_1->size[1];
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn <
         firstRunOnThisColumn; lastRunOnPreviousColumn++) {
      if (varargin_1->data[varargin_1->size[0] * lastRunOnPreviousColumn]) {
        numRuns++;
      }

      row = varargin_1->size[0];
      for (k = 0; k <= row - 2; k++) {
        if (varargin_1->data[(k + varargin_1->size[0] * lastRunOnPreviousColumn)
            + 1] && (!varargin_1->data[k + varargin_1->size[0] *
                     lastRunOnPreviousColumn])) {
          numRuns++;
        }
      }
    }
  }

  emxInit_int16_T(&startRow, 1, true);
  emxInit_int16_T(&endRow, 1, true);
  emxInit_int16_T(&startCol, 1, true);
  if (numRuns == 0) {
    CC_ImageSize[0] = varargin_1->size[0];
    CC_ImageSize[1] = varargin_1->size[1];
    numComponents = 0.0;
    CC_RegionIndices->size[0] = 0;
    firstRunOnThisColumn = CC_RegionLengths->size[0];
    CC_RegionLengths->size[0] = 1;
    emxEnsureCapacity_int32_T(CC_RegionLengths, firstRunOnThisColumn);
    CC_RegionLengths->data[0] = 0;
  } else {
    firstRunOnThisColumn = startRow->size[0];
    startRow->size[0] = numRuns;
    emxEnsureCapacity_int16_T(startRow, firstRunOnThisColumn);
    firstRunOnThisColumn = endRow->size[0];
    endRow->size[0] = numRuns;
    emxEnsureCapacity_int16_T(endRow, firstRunOnThisColumn);
    firstRunOnThisColumn = startCol->size[0];
    startCol->size[0] = numRuns;
    emxEnsureCapacity_int16_T(startCol, firstRunOnThisColumn);
    currentColumn = varargin_1->size[0];
    runCounter = 0;
    firstRunOnThisColumn = varargin_1->size[1];
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn <
         firstRunOnThisColumn; lastRunOnPreviousColumn++) {
      row = 1;
      while (row <= currentColumn) {
        while ((row <= currentColumn) && (!varargin_1->data[(row +
                 varargin_1->size[0] * lastRunOnPreviousColumn) - 1])) {
          row++;
        }

        if ((row <= currentColumn) && varargin_1->data[(row + varargin_1->size[0]
             * lastRunOnPreviousColumn) - 1]) {
          startCol->data[runCounter] = (int16_T)(lastRunOnPreviousColumn + 1);
          startRow->data[runCounter] = (int16_T)row;
          while ((row <= currentColumn) && varargin_1->data[(row +
                  varargin_1->size[0] * lastRunOnPreviousColumn) - 1]) {
            row++;
          }

          endRow->data[runCounter] = (int16_T)(row - 1);
          runCounter++;
        }
      }
    }

    firstRunOnThisColumn = CC_RegionLengths->size[0];
    CC_RegionLengths->size[0] = numRuns;
    emxEnsureCapacity_int32_T(CC_RegionLengths, firstRunOnThisColumn);
    for (firstRunOnThisColumn = 0; firstRunOnThisColumn < numRuns;
         firstRunOnThisColumn++) {
      CC_RegionLengths->data[firstRunOnThisColumn] = 0;
    }

    k = 0;
    currentColumn = 1;
    runCounter = 1;
    row = -1;
    lastRunOnPreviousColumn = -1;
    firstRunOnThisColumn = 0;
    while (k + 1 <= numRuns) {
      if (startCol->data[k] == currentColumn + 1) {
        row = firstRunOnThisColumn + 1;
        firstRunOnThisColumn = k;
        lastRunOnPreviousColumn = k;
        currentColumn = startCol->data[k];
      } else {
        if (startCol->data[k] > currentColumn + 1) {
          row = -1;
          lastRunOnPreviousColumn = -1;
          firstRunOnThisColumn = k;
          currentColumn = startCol->data[k];
        }
      }

      if (row >= 0) {
        for (p = row - 1; p < lastRunOnPreviousColumn; p++) {
          if ((endRow->data[k] >= startRow->data[p] - 1) && (startRow->data[k] <=
               endRow->data[p] + 1)) {
            if (CC_RegionLengths->data[k] == 0) {
              CC_RegionLengths->data[k] = CC_RegionLengths->data[p];
              runCounter++;
            } else {
              if (CC_RegionLengths->data[k] != CC_RegionLengths->data[p]) {
                for (root_k = k; root_k + 1 != CC_RegionLengths->data[root_k];
                     root_k = CC_RegionLengths->data[root_k] - 1) {
                  CC_RegionLengths->data[root_k] = CC_RegionLengths->
                    data[CC_RegionLengths->data[root_k] - 1];
                }

                for (root_p = p; root_p + 1 != CC_RegionLengths->data[root_p];
                     root_p = CC_RegionLengths->data[root_p] - 1) {
                  CC_RegionLengths->data[root_p] = CC_RegionLengths->
                    data[CC_RegionLengths->data[root_p] - 1];
                }

                if (root_k + 1 != root_p + 1) {
                  if (root_p + 1 < root_k + 1) {
                    CC_RegionLengths->data[root_k] = root_p + 1;
                    CC_RegionLengths->data[k] = root_p + 1;
                  } else {
                    CC_RegionLengths->data[root_p] = root_k + 1;
                    CC_RegionLengths->data[p] = root_k + 1;
                  }
                }
              }
            }
          }
        }
      }

      if (CC_RegionLengths->data[k] == 0) {
        CC_RegionLengths->data[k] = runCounter;
        runCounter++;
      }

      k++;
    }

    emxInit_int32_T(&labelsRenumbered, 1, true);
    firstRunOnThisColumn = labelsRenumbered->size[0];
    labelsRenumbered->size[0] = CC_RegionLengths->size[0];
    emxEnsureCapacity_int32_T(labelsRenumbered, firstRunOnThisColumn);
    numComponents = 0.0;
    for (k = 0; k < numRuns; k++) {
      if (CC_RegionLengths->data[k] == k + 1) {
        numComponents++;
        labelsRenumbered->data[k] = (int32_T)numComponents;
      }

      labelsRenumbered->data[k] = labelsRenumbered->data[CC_RegionLengths->
        data[k] - 1];
    }

    firstRunOnThisColumn = CC_RegionLengths->size[0];
    CC_RegionLengths->size[0] = (int32_T)numComponents;
    emxEnsureCapacity_int32_T(CC_RegionLengths, firstRunOnThisColumn);
    currentColumn = (int32_T)numComponents;
    for (firstRunOnThisColumn = 0; firstRunOnThisColumn < currentColumn;
         firstRunOnThisColumn++) {
      CC_RegionLengths->data[firstRunOnThisColumn] = 0;
    }

    for (k = 0; k < numRuns; k++) {
      CC_RegionLengths->data[labelsRenumbered->data[k] - 1] =
        ((CC_RegionLengths->data[labelsRenumbered->data[k] - 1] + endRow->data[k])
         - startRow->data[k]) + 1;
    }

    currentColumn = CC_RegionLengths->size[0];
    if (CC_RegionLengths->size[0] == 0) {
      y = 0.0;
    } else {
      y = CC_RegionLengths->data[0];
      for (k = 2; k <= currentColumn; k++) {
        y += (real_T)CC_RegionLengths->data[k - 1];
      }
    }

    emxInit_int32_T(&pixelIdxList, 1, true);
    emxInit_int32_T(&x, 1, true);
    firstRunOnThisColumn = pixelIdxList->size[0];
    pixelIdxList->size[0] = (int32_T)y;
    emxEnsureCapacity_int32_T(pixelIdxList, firstRunOnThisColumn);
    firstRunOnThisColumn = x->size[0];
    x->size[0] = CC_RegionLengths->size[0];
    emxEnsureCapacity_int32_T(x, firstRunOnThisColumn);
    currentColumn = CC_RegionLengths->size[0];
    for (firstRunOnThisColumn = 0; firstRunOnThisColumn < currentColumn;
         firstRunOnThisColumn++) {
      x->data[firstRunOnThisColumn] = CC_RegionLengths->
        data[firstRunOnThisColumn];
    }

    if ((CC_RegionLengths->size[0] != 1) && (CC_RegionLengths->size[0] != 0) &&
        (CC_RegionLengths->size[0] != 1)) {
      firstRunOnThisColumn = CC_RegionLengths->size[0];
      for (k = 0; k <= firstRunOnThisColumn - 2; k++) {
        x->data[k + 1] += x->data[k];
      }
    }

    emxInit_int32_T(&idxCount, 1, true);
    firstRunOnThisColumn = idxCount->size[0];
    idxCount->size[0] = x->size[0] + 1;
    emxEnsureCapacity_int32_T(idxCount, firstRunOnThisColumn);
    idxCount->data[0] = 0;
    currentColumn = x->size[0];
    for (firstRunOnThisColumn = 0; firstRunOnThisColumn < currentColumn;
         firstRunOnThisColumn++) {
      idxCount->data[firstRunOnThisColumn + 1] = x->data[firstRunOnThisColumn];
    }

    emxFree_int32_T(&x);
    for (k = 0; k < numRuns; k++) {
      currentColumn = (startCol->data[k] - 1) * varargin_1->size[0];
      runCounter = labelsRenumbered->data[k] - 1;
      firstRunOnThisColumn = startRow->data[k];
      row = endRow->data[k];
      for (lastRunOnPreviousColumn = firstRunOnThisColumn;
           lastRunOnPreviousColumn <= row; lastRunOnPreviousColumn++) {
        idxCount->data[runCounter]++;
        pixelIdxList->data[idxCount->data[runCounter] - 1] =
          lastRunOnPreviousColumn + currentColumn;
      }
    }

    emxFree_int32_T(&idxCount);
    emxFree_int32_T(&labelsRenumbered);
    CC_ImageSize[0] = varargin_1->size[0];
    CC_ImageSize[1] = varargin_1->size[1];
    firstRunOnThisColumn = CC_RegionIndices->size[0];
    CC_RegionIndices->size[0] = pixelIdxList->size[0];
    emxEnsureCapacity_real_T(CC_RegionIndices, firstRunOnThisColumn);
    currentColumn = pixelIdxList->size[0];
    for (firstRunOnThisColumn = 0; firstRunOnThisColumn < currentColumn;
         firstRunOnThisColumn++) {
      CC_RegionIndices->data[firstRunOnThisColumn] = pixelIdxList->
        data[firstRunOnThisColumn];
    }

    emxFree_int32_T(&pixelIdxList);
  }

  emxFree_int16_T(&startCol);
  emxFree_int16_T(&endRow);
  emxFree_int16_T(&startRow);
  *CC_Connectivity = 8.0;
  *CC_NumObjects = numComponents;
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (bwconncomp.c) */
