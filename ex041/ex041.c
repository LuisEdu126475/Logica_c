#include <stdio.h>
#include <stdlib.h>

int main(){
    float peso, altura, imc;

    printf("Digite o seu peso (em kg): ");
    scanf("%f", &peso);

    printf("Digite a sua altura (em metros, ex: 1.75): ");
    scanf("%f", &altura);

    imc = peso / (altura * altura);


    if (imc < 18.5) {
        printf("Abaixo do peso\n");
    }
    else if (imc < 25.0) {
        printf("Peso normal\n"); // Corrigido
    }
    else if (imc < 30.0) {
        printf("Sobrepeso\n");
    }
    else if (imc < 35.0) {
        printf("Obesidade Grau I\n");
    }
    else if (imc < 40.0) {
        printf("Obesidade Grau II\n");
    }
    else {
        printf("Obesidade Grau III (Morbida)\n");
    }
       printf("\nSeu IMC e: %.2f\n", imc);

    return 0;
}