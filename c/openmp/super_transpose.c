#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
#include <time.h>
#include <string.h>

#define ROWS    4096*8
#define COLS    1024*8

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
    clock_t start, end;
    double cpu_time;
    int i,j;
    //Matrix initialization
    float* matrix;
    float* transpose; 
    float* transpose_ref;
    int lda = ROUND_UP(ROWS, 32);
    int ldb = ROUND_UP(COLS, 32);

    matrix = (float*)malloc(lda*ldb*sizeof(float));
    transpose = (float*)malloc(lda*ldb*sizeof(float));
    transpose_ref = (float*)malloc(lda*ldb*sizeof(float));
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
    end = clock();
    cpu_time = 1000*((double)(end - start))/CLOCKS_PER_SEC;
    printf("SSE (block size 32) transpose took %f ms\n", cpu_time);
    //Check everything is correct
    int error = 0;
    for(i=0;i<lda;i++){
        for(j=0;j<ldb;j++){
            if( transpose_ref[i*ldb+j] != transpose[i*ldb+j] )
                error = 1;    
        }
    }
    if(error == 1){
        printf("oups...\n");
    }
}


