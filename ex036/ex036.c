#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, ""); // Configura acentuação para português

    int valor1, valor2, valor3, maior, menor;

    printf("Digite o primeiro valor: ");
    scanf("%d", &valor1);
    
    printf("Digite o segundo valor: ");
    scanf("%d", &valor2);
    
    printf("Digite o terceiro valor: ");
    scanf("%d", &valor3);

    // Lógica para encontrar o MAIOR valor
    if (valor1 > valor2){
        if (valor1 > valor3){
            maior = valor1;
        }
        else {
            maior = valor3;
        }
    }
    else {
        if (valor2 > valor3){
            maior = valor2;
        }
        else {
            maior = valor3;
        }
    }
    
    // Lógica para encontrar o MENOR valor
    if (valor1 < valor2){
        if (valor1 < valor3){
            menor = valor1;
        }
        else {
            menor = valor3;
        }
    }
    else {
        if (valor2 < valor3){
            menor = valor2;
        }
        else {
            menor = valor3;
        }
    }

    // Exibição dos resultados
    printf("\nMaior valor: %d\n", maior);
    printf("Menor valor: %d\n", menor);

    return 0;
}








    