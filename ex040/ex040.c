#include<stdio.h>
int main(){
    int opcao;
    float real,dolar;
    printf("\n---MENU---\n");
    printf("1-Dolar para Real.\n");\
    printf("2-Real para Dolar.\n");
    printf("Digite uma opcao:");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        printf("Digite quantos reais para dolar:");
        scanf("%f",&real);
        real = real/5.30;
        printf("O valor de reais para dolar foi:%.2f",real);
        break;
        case 2:
        printf("Digite quantos dolares para reais:");
        scanf("%f",&dolar);
        dolar = dolar *5.30;
        printf("O valor de dolar para reais foi:%.2f",dolar);
        break;
    default:
    printf("Opcao invalida");
        break;
    }







}