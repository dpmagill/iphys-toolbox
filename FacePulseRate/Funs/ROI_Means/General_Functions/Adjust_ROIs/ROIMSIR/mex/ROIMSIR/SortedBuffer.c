/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SortedBuffer.c
 *
 * Code generation for function 'SortedBuffer'
 *
 */

/* Include files */
#include "SortedBuffer.h"
#include "ROIMSIR_emxutil.h"
#include "ROIMSIR_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void SortedBuffer_insert(coder_internal_SortedBuffer *obj, int16_T x)
{
  int32_T b_i;
  int32_T i;
  int32_T i1;
  int32_T k;
  if (obj->nbuf >= obj->buf->size[0]) {
    i = obj->buf->size[0];
    i1 = obj->buf->size[0];
    obj->buf->size[0] = i + 256;
    emxEnsureCapacity_int16_T(obj->buf, i1);
    for (i1 = 0; i1 < 256; i1++) {
      obj->buf->data[i + i1] = 0;
    }
  }

  if (obj->nbuf == 0) {
    obj->buf->data[0] = x;
    obj->nbuf = 1;
  } else {
    b_i = SortedBuffer_locateElement(obj->buf, obj->nbuf, x);
    if (b_i == 0) {
      i = obj->nbuf;
      for (k = i; k >= 1; k--) {
        obj->buf->data[k] = obj->buf->data[k - 1];
      }

      obj->buf->data[0] = x;
      obj->nbuf++;
    } else if (b_i >= obj->nbuf) {
      obj->nbuf++;
      obj->buf->data[obj->nbuf - 1] = x;
    } else {
      i = obj->nbuf;
      i1 = b_i + 1;
      for (k = i; k >= i1; k--) {
        obj->buf->data[k] = obj->buf->data[k - 1];
      }

      obj->buf->data[b_i] = x;
      obj->nbuf++;
    }
  }
}

int32_T SortedBuffer_locateElement(const emxArray_int16_T *obj_buf, int32_T
  obj_nbuf, int16_T x)
{
  int32_T i;
  int32_T ip1;
  int32_T m;
  int32_T upper;
  if ((obj_nbuf == 0) || (x < obj_buf->data[0])) {
    i = 0;
  } else if (x < obj_buf->data[obj_nbuf - 1]) {
    i = 1;
    ip1 = 2;
    upper = obj_nbuf;
    while (upper > ip1) {
      m = (i + upper) >> 1;
      if (x < obj_buf->data[m - 1]) {
        upper = m;
      } else {
        i = m;
        ip1 = m + 1;
      }
    }
  } else {
    i = obj_nbuf;
  }

  return i;
}

int16_T SortedBuffer_median(const emxArray_int16_T *obj_buf, int32_T obj_nbuf)
{
  int32_T i;
  int32_T mid;
  int16_T m;
  int16_T x;
  int16_T z;
  uint16_T b_x;
  uint16_T q;
  if (obj_nbuf == 0) {
    m = 0;
  } else {
    mid = obj_nbuf >> 1;
    if ((obj_nbuf & 1) == 1) {
      m = obj_buf->data[mid];
    } else {
      i = obj_buf->data[mid - 1];
      if (i < 0) {
        if (obj_buf->data[mid] >= 0) {
          x = (int16_T)(obj_buf->data[mid - 1] + obj_buf->data[mid]);
          if (x >= 0) {
            b_x = (uint16_T)x;
          } else if (x == -32768) {
            b_x = 32768U;
          } else {
            b_x = (uint16_T)-x;
          }

          q = (uint16_T)((uint32_T)b_x >> 1);
          b_x = (uint16_T)((uint32_T)b_x - (q << 1));
          if (b_x > 0) {
            q++;
          }

          m = (int16_T)q;
          if (x < 0) {
            m = (int16_T)-q;
          }
        } else if (obj_buf->data[mid] < i) {
          x = (int16_T)(obj_buf->data[mid] - obj_buf->data[mid - 1]);
          if (x >= 0) {
            b_x = (uint16_T)x;
          } else if (x == -32768) {
            b_x = 32768U;
          } else {
            b_x = (uint16_T)-x;
          }

          q = (uint16_T)((uint32_T)b_x >> 1);
          b_x = (uint16_T)((uint32_T)b_x - (q << 1));
          if (b_x > 0) {
            q++;
          }

          z = (int16_T)q;
          if (x < 0) {
            z = (int16_T)-q;
          }

          m = (int16_T)(z + i);
        } else {
          x = (int16_T)(obj_buf->data[mid - 1] - obj_buf->data[mid]);
          if (x >= 0) {
            b_x = (uint16_T)x;
          } else if (x == -32768) {
            b_x = 32768U;
          } else {
            b_x = (uint16_T)-x;
          }

          q = (uint16_T)((uint32_T)b_x >> 1);
          b_x = (uint16_T)((uint32_T)b_x - (q << 1));
          if (b_x > 0) {
            q++;
          }

          z = (int16_T)q;
          if (x < 0) {
            z = (int16_T)-q;
          }

          m = (int16_T)(z + obj_buf->data[mid]);
        }
      } else if (obj_buf->data[mid] < 0) {
        x = (int16_T)(i + obj_buf->data[mid]);
        if (x >= 0) {
          b_x = (uint16_T)x;
        } else if (x == -32768) {
          b_x = 32768U;
        } else {
          b_x = (uint16_T)-x;
        }

        q = (uint16_T)((uint32_T)b_x >> 1);
        b_x = (uint16_T)((uint32_T)b_x - (q << 1));
        if (b_x > 0) {
          q++;
        }

        m = (int16_T)q;
        if (x < 0) {
          m = (int16_T)-q;
        }
      } else if (i < obj_buf->data[mid]) {
        x = (int16_T)(obj_buf->data[mid] - i);
        if (x >= 0) {
          b_x = (uint16_T)x;
        } else if (x == -32768) {
          b_x = 32768U;
        } else {
          b_x = (uint16_T)-x;
        }

        q = (uint16_T)((uint32_T)b_x >> 1);
        b_x = (uint16_T)((uint32_T)b_x - (q << 1));
        if (b_x > 0) {
          q++;
        }

        z = (int16_T)q;
        if (x < 0) {
          z = (int16_T)-q;
        }

        m = (int16_T)(z + i);
      } else {
        x = (int16_T)(i - obj_buf->data[mid]);
        if (x >= 0) {
          b_x = (uint16_T)x;
        } else if (x == -32768) {
          b_x = 32768U;
        } else {
          b_x = (uint16_T)-x;
        }

        q = (uint16_T)((uint32_T)b_x >> 1);
        b_x = (uint16_T)((uint32_T)b_x - (q << 1));
        if (b_x > 0) {
          q++;
        }

        z = (int16_T)q;
        if (x < 0) {
          z = (int16_T)-q;
        }

        m = (int16_T)(z + obj_buf->data[mid]);
      }
    }
  }

  return m;
}

void SortedBuffer_replace(coder_internal_SortedBuffer *obj, int16_T xold,
  int16_T xnew)
{
  int32_T i;
  int32_T inew;
  int32_T iold;
  int32_T k;
  iold = SortedBuffer_locateElement(obj->buf, obj->nbuf, xold);
  if ((iold > 0) && (obj->buf->data[iold - 1] == xold)) {
    inew = SortedBuffer_locateElement(obj->buf, obj->nbuf, xnew);
    if (iold <= inew) {
      i = inew - 1;
      for (k = iold; k <= i; k++) {
        obj->buf->data[k - 1] = obj->buf->data[k];
      }

      obj->buf->data[inew - 1] = xnew;
    } else if (iold == inew + 1) {
      obj->buf->data[iold - 1] = xnew;
    } else {
      i = inew + 2;
      for (k = iold; k >= i; k--) {
        obj->buf->data[k - 1] = obj->buf->data[k - 2];
      }

      obj->buf->data[inew] = xnew;
    }
  } else {
    SortedBuffer_insert(obj, xnew);
  }
}

/* End of code generation (SortedBuffer.c) */
