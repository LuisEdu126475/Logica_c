#include <stdio.h>

int main(void) {
    int a[3][3], b[3][3], c[3][3];
    int l, j;

    for (l = 0; l < 3; l++) {
        for (j = 0; j < 3; j++) {
            printf("Digite o valor de A[%d][%d]: ", l, j);
            scanf("%d", &a[l][j]);

            printf("Digite o valor de B[%d][%d]: ", l, j);
            scanf("%d", &b[l][j]);

            c[l][j] = a[l][j] + b[l][j];
        }
    }

    printf("\nMatriz A:\n");
    for (l = 0; l < 3; l++) {
        for (j = 0; j < 3; j++) {
            printf("%d\t", a[l][j]);
        }
        printf("\n");
    }

    printf("\nMatriz B:\n");
    for (l = 0; l < 3; l++) {
        for (j = 0; j < 3; j++) {
            printf("%d\t", b[l][j]);
        }
        printf("\n");
    }

    printf("\nMatriz C (A + B):\n");
    for (l = 0; l < 3; l++) {
        for (j = 0; j < 3; j++) {
            printf("%d\t", c[l][j]);
        }
        printf("\n");
    }

    return 0;
}