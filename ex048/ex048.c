#include<stdio.h>
int main(){
    int x;
    printf("Digite um valor entre 1 e 99:");
    scanf("%d", &x);
    while (x<1||x>99)
    {
        printf("Invalido Digite um valor entre 1 e 99:");
    scanf("%d", &x);
    }
    
    pritnf("Valor Digitado:%d\n",x); 
















    return 0;
}