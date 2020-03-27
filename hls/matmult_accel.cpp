/***************************************************************************
Copyright (c) 2016, Xilinx, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors 
may be used to endorse or promote products derived from this software 
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/
#include "matmult.h"


// --------------------------------------------------------
// function to be accelerated in HW
template <typename T>
void mmult_hw(T a[N][N], T b[N][N], T out[N][N])
{
	// matrix multiplication of a A*B matrix
	L1:for (int ia = 0; ia < N; ++ia)
		L2:for (int ib = 0; ib < N; ++ib)
		{
			T sum = 0;
			L3:for (int id = 0; id < N; ++id)
				sum += a[ia][id] * b[id][ib];
			out[ia][ib] = sum;
		}

		return;
}


template<typename T>
void axis2Mat (axis_t *src, 
			     T A[N][N],
				 T B[N][N])
				 {
#pragma HLS inline off

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
#pragma HLS pipeline
#pragma HLS loop_flatten off
			int k = i*N + j;
			A[i][j] = src[k].data;
		}	
	}

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
#pragma HLS pipeline
#pragma HLS loop_flatten off
			int k = i*N + j;
			B[i][j] = src[k + SIZE].data; //TODO implement conversion
		}	
	}
}

template<typename T>
void Mat2axis (T C[N][N],
		 axis_t *dst
		 ) {
#pragma HLS inline off

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
#pragma HLS pipeline
#pragma HLS loop_flatten off
			ap_uint<1> tmp = 0;
			if ((i == N-1) && (j == N-1)) {
				tmp = 1;
			}
			dst[i*N+j].last = tmp;
			dst[i*N+j].data = C[i][j]; //TODO implement conversion
		}
	}
}

extern "C" {
void matmult_accel (axis_t *src, axis_t *dst) {
	
#pragma HLS INTERFACE axis port=src
#pragma HLS INTERFACE axis port=dst
#pragma HLS INTERFACE s_axilite port=return

#pragma HLS dataflow

	int A[N][N];
	int B[N][N];
	int C[N][N];

	axis2Mat(src, A, B);	

	mmult_hw(A, B, C);

	Mat2axis(C, dst);	
}
}
