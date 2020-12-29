#ifndef _MMULT_
#define _MMULT_

#include "ap_axi_sdata.h"
#include "ap_int.h"
#include <inttypes.h>

#define N 128
#define N2 16384 // N*N

#define DWIDTH 512
typedef ap_axiu<DWIDTH, 0, 0, 0> axis_t;

typedef ap_uint<512> uint512_t;
typedef float DataType;

const int DataTypeSize = sizeof(DataType) * 8;

typedef ap_uint<DataTypeSize> DataTypeInt;

typedef union converter {
  DataType d;
  uint32_t i;
} converter_t;

template <typename T> void kernel_mmult(T a[N2], T b[N2], T c[N2]);

#endif
