#include "compute.h"
#include <math.h>
#include <smmintrin.h>
#include <stdio.h>

void multiply(int N, float* restrict A, float* restrict B, float* restrict C)
{
    int i, j, k;

    for (i = 0; i < N; i++) 
    {
        for (k = 0; k < N; k++) 
        {
            __m128 ra = _mm_set1_ps(A[i * N + k]);

            for (j = 0; j <= N - 8; j += 4) 
            {
                _mm_store_ps(C + i * N + j, _mm_add_ps(_mm_load_ps(C + i * N + j), _mm_mul_ps(_mm_load_ps(B + k * N + j), ra)));
            }

            for (; j < N; j++) 
            {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

void printMatrix(int N, float* matrix)
{
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%8.2f ", matrix[i * N + j]);
        }
        printf("\n");
    }
}