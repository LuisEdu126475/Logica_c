#include<stdio.h>
int main(){
    int x;
    do
    {
        printf("Digite um valor entre 1 e 99:");
    scanf("%d", &x);
    } while (x<1||x>99);
    
    
    pritnf("Valor Digitado:%d\n",x); 
}