#include <stdio.h>
#include <stdlib.h>

int main(){ // Aula 57 - Estrutura de seleção switch case.

    int codigo = 1;

    switch(codigo){
    case 1:
        printf("Janeiro\n");
        break;
    case 2:
        printf("Fevereiro\n");
        break;
    case 3:
        printf("Marco\n");
        break;
    default:
        printf("Valor inesperado!\n");
        break;
    }

    return 0;
}