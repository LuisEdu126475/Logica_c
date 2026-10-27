#include <stdio.h>

int main(){
    int i, j, soma = 0, matriz[3][4];

    for (i = 0; i < 3; i++) {
        printf("\nDigite 4 numeros inteiros para a linha %d:\n", i + 1);
        for (j = 0; j < 4; j++) {
            printf("Numero %d: ", j + 1);
            scanf("%d", &matriz[i][j]);
            soma += matriz[i][j];
        }
    }

    printf("\nA soma da matriz e: %d\n", soma);
    return 0;
}


