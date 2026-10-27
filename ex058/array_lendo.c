#include <stdio.h>
#include <stdlib.h>

int main(){ // Aula 107 Como ler um vetor (array) a partir do teclado com a linguagem de programação C?

    int i, num[5];

    for(i = 0; i < 5; i++){
        printf("\tDigite um valor da posicao %d: ", i);
        scanf("%d", &num[i]);
    }

    printf("\n\t");
    for(i = 0; i < 5; i++)
        printf("%d, ", num[i]);

    return 0;
}