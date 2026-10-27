#include <stdio.h>

int main() {
    int v1[10], v2[10];

    // 1. Preenche o primeiro vetor pedindo os valores ao usuário
    for (int i = 0; i < 10; i++) {
        printf("Digite o %dº valor: ", i + 1);
        scanf("%d", &v1[i]);
    }

    // 2. Calcula e salva no segundo vetor o quadrado de cada elemento do primeiro
    for (int i = 0; i < 10; i++) {
        v2[i] = v1[i] * v1[i];
    }

    // 3. Imprime os dois vetores
    printf("\nPrimeiro vetor (v1): ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", v1[i]);
    }

    printf("\nSegundo vetor (v2 - ao quadrado): ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", v2[i]);
    }
    printf("\n");

    return 0;
}