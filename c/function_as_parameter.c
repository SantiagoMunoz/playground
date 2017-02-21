#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void my_print(char *buffer, int length){
    int i;

    for(i=0; i< length; i++){
        printf("%c", buffer[i]);
    }
    printf("\n");
    return; 
}

void my_function( void (*f)(char*, int) ){
    char buffer[8] = "MOGAMBO\n";

    (*f)(buffer,8);
    return;
}

int main(){

    my_function(my_print);
    return 0;
}
