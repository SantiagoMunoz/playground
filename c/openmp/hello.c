#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    #pragma omp parallel num_threads(3)
    printf("hello\n");
}
