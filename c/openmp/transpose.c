#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ROWS    256*16
#define COLS    512*16
int main(){
    clock_t start, end;
    double cpu_time;
    int i,j;
    //Matrix initialization
    float** matrix;
    float** transpose; 

    matrix = (float**)malloc(ROWS*sizeof(float*));
    transpose = (float**)malloc(COLS*sizeof(float*));
    for(i=0;i<ROWS;i++){
        matrix[i] = (float*)malloc(COLS*sizeof(float));
    }
    for(i=0;i<COLS;i++){
        transpose[i] = (float*)malloc(ROWS*sizeof(float));
    }
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLS;j++)
            matrix[i][j] = (float)i*COLS+j;
    }
    
    
    //Serial computation
    start = clock();
    
    for(i=0;i<ROWS;i++)
        for(j=0;j<COLS;j++)
            transpose[j][i] = matrix[i][j];

    end  = clock();

    cpu_time = 1000*((double)(end - start))/CLOCKS_PER_SEC;
    printf("Serial transpose took %f ms\n", cpu_time);

    //naive openmp transpose
    start = clock();
    
    #pragma omp parallel num_threads(4) for collapse(2) private(i,j) schedule(static)
    for(i=0;i<ROWS;i++)
        for(j=0;j<COLS;j++)
            transpose[j][i] = matrix[i][j];

    end  = clock();

    cpu_time = 1000*((double)(end - start))/CLOCKS_PER_SEC;
    printf("omp (4 threads) transpose took %f ms\n", cpu_time);
  
    //openmp with more threads
     start = clock();
    
    #pragma omp parallel num_threads(4) for collapse(2) private(i,j) schedule(dynamic)
    for(i=0;i<ROWS;i++)
        for(j=0;j<COLS;j++)
            transpose[j][i] = matrix[i][j];

    end  = clock();

    cpu_time = 1000*((double)(end - start))/CLOCKS_PER_SEC;
    printf("omp (dynamic) transpose took %f ms\n", cpu_time);

    //openmp simd
    start = clock();
    
    #pragma omp simd collapse(2) 
    for(i=0;i<ROWS;i++)
        for(j=0;j<COLS;j++)
            transpose[j][i] = matrix[i][j];

    end  = clock();

    cpu_time = 1000*((double)(end - start))/CLOCKS_PER_SEC;
    printf("omp (simd) transpose took %f ms\n", cpu_time);

     //openmp simd for
    start = clock();
    
    #pragma omp parallel for simd collapse(2) private(i,j)
    for(i=0;i<ROWS;i++)
        for(j=0;j<COLS;j++)
            transpose[j][i] = matrix[i][j];

    end  = clock();

    cpu_time = 1000*((double)(end - start))/CLOCKS_PER_SEC;
    printf("omp (for simd) transpose took %f ms\n", cpu_time);
   
    //Cleanup
    for(i=0;i<ROWS;i++){
        free(matrix[i]);
    }
    for(i=0;i<COLS;i++){
        free(transpose[i]);
    }
    free(matrix);
    free(transpose);

}
