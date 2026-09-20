#include <stdio.h>
#include <stdlib.h>

int main(){ // Aula 56 - Estrutura de decisão else if encadeados na linguagem C.

    int z = 0;

    if(z > 0)
        printf("Positivo!\n");
    else if(z < 0)
        printf("Negativo!\n");
    else
        printf("Zero!\n");

    return 0;
}