#include "matmult.h"

void mmult_sw(DataType a[N2], DataType b[N2], DataType out[N2])
{
  for (int ia = 0; ia < N; ++ia)
    for (int ib = 0; ib < N; ++ib)
    {
      float sum = 0;
      for (int id = 0; id < N; ++id)
        sum += a[ia * N + id] * b[id * N + ib];

      out[ia * N + ib] = sum;
    }
}

int main(void)
{

  int ret_val = 0;

  int i, j, err;

  DataType matOp1[N2];
  DataType matOp2[N2];
  DataType matMult_sw[N2];
  DataType matMult_hw[N2];

  /** Matrix Initiation */
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      matOp1[i * N + j] = (DataType)(i + j);

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      matOp2[i * N + j] = (DataType)(i * j);
  /** End of Initiation */

  kernel_mmult<DataType>(matOp1, matOp2, matMult_hw);

  /* reference Matrix Multiplication */
  mmult_sw(matOp1, matOp2, matMult_sw);

  /** Matrix comparison */
  err = 0;
  for (i = 0; (i < N && !err); i++)
    for (j = 0; (j < N && !err); j++)
      if (matMult_sw[i * N + j] != matMult_hw[i * N + j])
        err++;

  if (err == 0)
    printf("Matrixes identical ... Test successful!\r\n");
  else
    printf("Test failed!\r\n");

  return err;
}
