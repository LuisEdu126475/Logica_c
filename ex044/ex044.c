#include<stdio.h>
int main(){
    int a,b,c;
    printf("Informe o valor de a(Inteiros):");
    scanf("%d", &a);
    printf("Informe o valor de b(Inteiros):");
    scanf("%d", &b);
    printf("Informe o valor de c(Inteiros):");
    scanf("%d", &c);
    if(a+b>c && a+c>b&&b+c>a){
        if(a==b && a==c){
            printf("Equilatero!\n");
        }
        else if (a==b|| a==c|| b==c)
        {
            printf("Isosceles");
        }
        else{
            printf("Escaleno!");
        }
       
    }
     else{
            printf("Nao formam um triangulo");
        }





}