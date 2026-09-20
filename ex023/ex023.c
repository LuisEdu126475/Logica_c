#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
int main(){

    setlocale(LC_ALL,"Portuguese");
    float valorConta;
    short pessoas, gorjeta;

    printf("\nQual o valor da despesa do restaurante:");
    scanf("%f", &valorConta);
    printf("Digite o valor da gorjeta:\n");
    scanf("%d", &gorjeta);
    printf("Numero de pessoas para dividir a conta:\n");
    scanf("%f", &pessoas);

    valorConta = valorConta +(valorConta*gorjeta/100);

    printf("\t Valor da conta:R$%.2f\t Valor por pessoa:R$%.2f\n", valorConta, valorConta/pessoas);
}