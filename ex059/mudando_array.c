#include <stdio.h>
#include <stdlib.h>

int main(){ // Aula 108 - Como alterar o conteúdo de um vetor (array) na linguagem de programação C?

    int i, valores[5] = {10,20,30,40,50};

    printf("Vetor antes da multiplicacao...\n");
    for(i = 0; i < 5; i++)
        printf("%d, ", valores[i]);

    for(i = 0; i < 5; i++)
        valores[i] = valores[i] * 2;

    printf("\nVetor apos a multiplicacao...\n");
    for(i = 0; i < 5; i++)
        printf("%d, ", valores[i]);

    return 0;
}