#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
int main (){
    setlocale(LC_ALL,"Portuguese");
    int dia;
    float valorRecebido ;
    printf("Informe a quantidade de dias trabalhados:");
    scanf("%d", &dia);
    valorRecebido = 45.0 * dia;
    valorRecebido = valorRecebido-valorRecebido*8/100;

    printf("\t Valor a ser pago R$%.2f\n", valorRecebido);



    return 0;
}