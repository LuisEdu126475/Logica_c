#include <stdio.h>
#include <stdlib.h>

int main(){ // Aula 106 - Como imprimir o conteúdo de um vetor (array) com a linguagem de programação C?

    int i, idades[5] = {15,47,85,39};
    char nome[] = {'W','a','g','n','e','r'};

    for(i = 0; i < 5; i++)
        printf("%d\n", idades[i]);

    for(i = 0; i < 6; i++)
        printf("%c", nome[i]);

    return 0;
}