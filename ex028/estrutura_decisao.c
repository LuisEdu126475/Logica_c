#include <stdio.h>
#include <stdlib.h>

int main(){

    // Aula 50 - Decisão aninhada na lingu...

    int x = -5;

    if(x > 0){ // Se
        printf("\tPositivo\n\n");
        if(x < 100){
            printf("Valor entre 1 e 99\n");
        }
        else{
            printf("Valor maior ou igual a 100");
        }
    }
    else{ // senão
        printf("\tValores diferentes\n\n");
        if(x == 0)
            printf("Valor he zero!\n");
        else
            printf("Valor he negativo!\n");
    }

    printf("\tApos o if\n\n");

    return 0;
}