#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
int main(){

    setlocale(LC_ALL,"Portuguese");
    int valor1, valor2, copia;

    printf("\t\nDigite o valor1 e valor 2:");
    scanf("%d%d", &valor1, &valor2);
    copia = valor1;
    valor1=valor2;
    valor2=copia;
    printf("\n Valor 1:%d\t Valor 2:%d\n", valor1, valor2);



    
}