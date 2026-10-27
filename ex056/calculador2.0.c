#include <stdio.h>
#include <stdlib.h>

int main(){

    int opcao;
    float n1, n2;

    do {
        printf("\n\t--- MENU CALCULADORA ---\n");
        printf("\t1 - SOMAR\n");
        printf("\t2 - SUBTRAIR\n");
        printf("\t3 - MULTIPLICAR\n");
        printf("\t4 - DIVIDIR\n");
        printf("\t5 - SAIR\n");
        printf("\tEscolha uma opcao: ");
        scanf("%d", &opcao);

        // Corrigido: era 'operacao', mudei para 'opcao'
        if (opcao >= 1 && opcao <= 4) {
            printf("\tDigite os dois valores: ");
            scanf("%f %f", &n1, &n2);
        }

        switch (opcao)
        {
        case 1:
            printf("\n\tResultado da Soma: %.2f\n", n1 + n2);
            break;

        case 2: 
            printf("\n\tResultado da Subtracao: %.2f\n", n1 - n2);
            break;

        case 3: 
            printf("\n\tResultado da Multiplicacao: %.2f\n", n1 * n2);
            break;

        case 4: 
            if (n2 != 0) {
                printf("\n\tResultado da Divisao: %.2f\n", n1 / n2);
            } else {
                printf("\n\tErro: Divisao por zero nao e permitida!\n");
            }
            break;

        case 5:
            printf("\n\tSaindo do programa... Ater logo!\n");
            break;

        default:
            printf("\n\tOpcao invalida! Tente novamente.\n");
            break;
        }

    } while (opcao != 5); // Corrigido: adicionado o ';' no final do do-while

    return 0;
}