#include<stdio.h>
#include<stdlib.h>
void main(){
    int y,x=35;
    y= x++; //x=x+1 se o incremento estiver na esquerda ele incrementa primeiro para usar o valor na variavel x 

    printf("O valor de y:%d\n\t Valor de x:%d\n\n\n",y,x);




    return 0;
}