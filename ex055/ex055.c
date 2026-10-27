#include <stdio.h>
#include <stdlib.h>

int main() { // Aula 85 - Exercício 7: Leia um valor inteiro N e apresente o quadrado de cada valor par de 1 até N

    int n, i, quadrado;

    printf("Digite um valor inteiro: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        if (i % 2 == 0) { // Verifica se é par (resto da divisão por 2 é zero)
            quadrado = i * i; // Calcula o quadrado correto
            printf("%d elevado ao quadrado e: %d\n", i, quadrado);
        }
    }

    return 0;
}