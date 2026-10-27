#include<stdio.h>
#include<stdlib.h>
int main(){
    int i,valorInicial=1, valorFinal=1;
    printf("---O QUANTO VOCE GUARDOU---\n");
    for ( i = 1; i <= 30; i++)
    {
        valorInicial = valorInicial *2;
        valorFinal += valorInicial;
    }
    printf("\t Total em centavos:%d\n",valorFinal);
    printf("\t Total em reais R$%f\n", (float) valorFinal/100);
    






}