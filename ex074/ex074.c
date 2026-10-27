#include <stdio.h>

int main() {
    int matriz[5][10];
    int somaLinhas[5] = {0};
    int somaColunas[10] = {0};
    int l, c;

    for (l = 0; l < 5; l++) {
        for (c = 0; c < 10; c++) {
            printf("Digite o valor da posicao [%d][%d]: ", l, c);
            scanf("%d", &matriz[l][c]);
            somaLinhas[l] += matriz[l][c];
        }
    }

    for (c = 0; c < 10; c++) {
        for (l = 0; l < 5; l++) {
            somaColunas[c] += matriz[l][c];
        }
    }

    printf("\nMatriz:\n");
    for (l = 0; l < 5; l++) {
        for (c = 0; c < 10; c++) {
            printf("%d\t", matriz[l][c]);
        }
        printf("\n");
    }

    printf("\nSoma das linhas:\n");
    for (l = 0; l < 5; l++) {
        printf("Linha %d: %d\n", l, somaLinhas[l]);
    }

    printf("\nSoma das colunas:\n");
    for (c = 0; c < 10; c++) {
        printf("Coluna %d: %d\n", c, somaColunas[c]);
    }

    return 0;
}