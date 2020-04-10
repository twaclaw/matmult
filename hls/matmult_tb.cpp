#include "matmult.h"
#include <stdio.h>
#include <stdlib.h>


typedef float T;

void mmult_sw(T a[N][N], T b[N][N], T out[N][N]) {
  // matrix multiplication of a A*B matrix
  for (int ia = 0; ia < N; ++ia)
    for (int ib = 0; ib < N; ++ib) {

      float sum = 0;

      for (int id = 0; id < N; ++id)

        sum += a[ia][id] * b[id][ib];

      out[ia][ib] = sum;
    }
}

int main(void) {

  int ret_val = 0;

  int i, j, err;

  T matOp1[N][N];
  T matOp2[N][N];
  T matMult_sw[N][N];
  T matMult_hw[N][N];

  /** Matrix Initiation */
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      matOp1[i][j] = (float)(i + j);

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      matOp2[i][j] = (float)(i * j);
  /** End of Initiation */

  printf("NORMAL MODE\r\n");
  mmult_hw(matOp1, matOp2, matMult_hw);

  /* reference Matrix Multiplication */
  mmult_sw(matOp1, matOp2, matMult_sw);

  /** Matrix comparison */
  err = 0;
  for (i = 0; (i < N && !err); i++)
    for (j = 0; (j < N && !err); j++)
      if (matMult_sw[i][j] != matMult_hw[i][j])
        err++;

  if (err == 0)
    printf("Matrixes identical ... Test successful!\r\n");
  else
    printf("Test failed!\r\n");

  return err;
}
