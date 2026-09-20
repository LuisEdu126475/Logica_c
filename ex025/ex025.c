#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
int main (){
    setlocale(LC_ALL,"Portuguese");
    float reais, dolares;
    printf("Digite quantos reais voce quer converter em dolar");
    scanf("%f", reais);
    dolares = reais /5.30;
    printf("R$5%.2f corresponde a $%.2f\n",reais, dolares);

    return 0;
}