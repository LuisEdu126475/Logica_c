#include <stdio.h>
#include <stdlib.h>

int main(){
    int p1, p2, p3;
    float n1, n2, n3, media;
    int opcao; // Corrigido: adicionado o ponto e vírgula ';'

    printf("\n---MENU DE NOTAS---\n");
    printf("1- Media aritmetica\n");
    printf("2- Media ponderada\n");
    printf("Digite uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        printf("\nDigite a primeira nota: ");
        scanf("%f", &n1);
        printf("Digite a segunda nota: ");
        scanf("%f", &n2);
        printf("Digite a terceira nota: ");
        scanf("%f", &n3);
        
        media = (n1 + n2 + n3) / 3.0;
        printf("\nResultado da sua media foi: %.2f\n", media);
        break;

    case 2:
        printf("\nDigite a primeira nota: ");
        scanf("%f", &n1);
        printf("Digite a segunda nota: ");
        scanf("%f", &n2);
        printf("Digite a terceira nota: ");
        scanf("%f", &n3);

        printf("\nDigite o peso da primeira nota: ");
        scanf("%d", &p1); // Corrigido: %d para int
        printf("Digite o peso da segunda nota: ");
        scanf("%d", &p2); // Corrigido: %d para int
        printf("Digite o peso da terceira nota: ");
        scanf("%d", &p3);

        media = (n1 * p1 + n2 * p2 + n3 * p3) / (float)(p1 + p2 + p3);
        printf("\nResultado da sua media foi: %.2f\n", media);
        break; // Corrigido: adicionado o break aqui!

    default:
        printf("\nOpcao invalida!\n");
        break;
    }

    return 0;
}