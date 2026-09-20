#include <stdio.h>
#include <stdlib.h>

int main(){

    // Aula 51 - Operador ternário aninhado na linguagem C.

    int x = -10;
    x > 15 ? printf("Verdadeiro\n") : x < 0 ? printf("Negatico\n") : printf("Positivo ou zero\n");

    return 0;
}