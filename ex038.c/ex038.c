#include <stdio.h>
#include <stdlib.h>

int main(){ // Aula 61 - Exercício 3: Leia um número e informe se ele é divisível...

    int valor;

    printf("Digite um valor: ");
    scanf("%d", &valor);

    if(valor % 2 == 0)
        printf("%d eh divisivel por 2\n", valor);
    else
        printf("%d nao eh divisivel por 2\n", valor);

    if(valor % 3 == 0)
        printf("%d eh divisivel por 3\n", valor);
    else
        printf("%d nao eh divisivel por 3\n", valor);

    if(valor % 5 == 0)
        printf("%d eh divisivel por 5\n", valor);
    else
        printf("%d nao eh divisivel por 5\n", valor);

    return 0;
}