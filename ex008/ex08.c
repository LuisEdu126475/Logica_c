#include<stdio.h>
#include<stdlib.h>
int main(){
    char sexo;
    int idade; 
    float peso, altura;

    printf("\nDigite seu sexo: m para masculino e f para feminino:");
    sexo = fgetc(stdin);
    printf("\nDigite sua idade:");
    scanf("%d", &idade);
    printf("\nDigite seu peso:");
    scanf("%f", &peso);
    printf("\nDigite sua altura:");
    scanf("%f", &altura);

    printf("Seu sexo eh:%c, sua idade eh:%d, seu peso eh:%f e sua altura eh:%f", sexo, idade, peso, altura);






    return 0;
}