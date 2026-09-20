#include <stdio.h>
#include <stdlib.h>

int main(){ // Aula 58 - Estrutura de seleção switch case com caracteres.

    char opcao = 'z';

    switch(opcao){
    case 'a':
        printf("Cadastrar cliente\n");
        break;
    case 'b':
        printf("Imprimir clinetes\n");
        break;
    default:
        printf("Valor incorreto\n");
    }

    return 0;
}