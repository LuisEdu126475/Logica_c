#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
int main(){

    setlocale(LC_ALL,"Portuguese");
    int valor1, valor2;

    printf("Digite dois valores:");
    scanf("%d%d",&valor1, &valor2);

    valor1 = valor1+valor2;
    valor2 = valor1-valor2;
    valor1= valor1-valor2;

    printf("\n Valor 1:%d\tValor 2:%d\n",valor1,valor2);
}