#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
#include <time.h>
#include <string.h>

#define ROWS    1024
#define COLS    4096*8

#define ROUND_UP(x, s) (((x)+((s)-1)) & -(s))

void transpose_f(float *src, float *dst, const int N, const int M) {
    #pragma omp parallel for
    for(int n = 0; n<N*M; n++) {
        int i = n/N;
        int j = n%N;
        dst[n] = src[M*j + i];
    }
}

void transpose4x4_SSE(float *A, float *B, const int lda, const int ldb) {
    __m128 row1 = _mm_load_ps(&A[0*lda]);
    __m128 row2 = _mm_load_ps(&A[1*lda]);
    __m128 row3 = _mm_load_ps(&A[2*lda]);
    __m128 row4 = _mm_load_ps(&A[3*lda]);
    _MM_TRANSPOSE4_PS(row1, row2, row3, row4);
    _mm_store_ps(&B[0*ldb], row1);
    _mm_store_ps(&B[1*ldb], row2);
    _mm_store_ps(&B[2*ldb], row3);
    _mm_store_ps(&B[3*ldb], row4);
}

void transpose_block_SSE4x4(float *A, float *B, const int n, const int m, const int lda, const int ldb ,const int block_size) {
    #pragma omp parallel for
    for(int i=0; i<n; i+=block_size) {
        for(int j=0; j<m; j+=block_size) {
            int max_i2 = i+block_size < n ? i + block_size : n;
            int max_j2 = j+block_size < m ? j + block_size : m;
            for(int i2=i; i2<max_i2; i2+=4) {
                for(int j2=j; j2<max_j2; j2+=4) {
                    transpose4x4_SSE(&A[i2*lda +j2], &B[j2*ldb + i2], lda, ldb);
                }
            }
        }
    }
}

int main(){
    clock_t start, middle1, middle2, end;
    double cpu_time;
    int i,j,k;
    //Matrix initialization
    float* matrix;
    float* transpose; 
    float* transpose_ref;
    float* final;

    int lda = ROUND_UP(ROWS, 32);
    int ldb = ROUND_UP(COLS, 32);

    matrix = (float*)malloc(lda*ldb*sizeof(float));
    transpose = (float*)malloc(lda*ldb*sizeof(float));
    transpose_ref = (float*)malloc(lda*ldb*sizeof(float));
    final = (float*)malloc(lda*ldb*sizeof(float));

    for(i=0;i<lda;i++){
        for(j=0;j<ldb;j++)
            matrix[i*ldb+j] = (float)i*ldb+j;
    }
    
    //OpenMP computation
    start = clock();
    transpose_f(matrix, transpose_ref, lda, ldb);
    end  = clock();

    cpu_time = 1000*((double)(end - start))/CLOCKS_PER_SEC;
    printf("OMP transpose took %f ms\n", cpu_time);

    //SSE
    start = clock();
    transpose_block_SSE4x4(matrix, transpose, lda, ldb, ldb, lda, 32);
    middle1 = clock();
    //Group memory by channels
    #pragma parallel for collapse(2)
    for(j=0;j<4;j++){   // 4= channels
        for(i=0;i<4096;i++){      // i = elements
            memcpy(final + j*4096*1024*2 + i*1024*2, 
                    transpose + j*1024*2 + i*4*1024*2, 
                    1024*2);
        } 
    } 
    middle2 = clock(); 
    //Shuffle Real and Imag parts back together
    #pragma parallel for collapse(3)
    for(j=0;j<4;j++){ //Channels   (4)
        for(k=0;k<4096;k++){    //Elements (4096)
            for(i=1;i<1024;i+=2){    //Elements  (Ramps)
                float temp = final[j*4096*1024 + k*1024*2 + 1024 + i];
                final[j*4096*2*1024 + k*1024*2 + i] = final[j*4096*2*1024 +k*1024*2 + i];
                final[j*4096*2*1024 +k*1024*2 + i] = temp;
            }
        }
    }
    end = clock();
    cpu_time = 1000*((double)(end - start))/CLOCKS_PER_SEC;
    printf("SSE (block size 32) full operation took %f ms\n", cpu_time);
    cpu_time = 1000*((double)(middle2 - middle1))/CLOCKS_PER_SEC;
    printf("Reorder took %f ms\n", cpu_time);
    cpu_time = 1000*((double)(end - middle2))/CLOCKS_PER_SEC;
    printf("Shuffle took %f ms\n", cpu_time);


    free(matrix);
    free(transpose);
    free(transpose_ref);
    free(final);
}
