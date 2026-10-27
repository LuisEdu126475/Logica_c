#include<stdio.h>
int main(){
    int i,soma=0;

   for (i = 1; i <= 1000; i += 2) {
        soma += i; // Adiciona o número ímpar atual à variável soma (soma = soma + i)
    }
    printf("A soma dos numeros impares de 1 a 1000 e: %d\n", soma);
    
    //ou for (i = 1; i <= 1000; i++) {
    //if (i % 2 != 0) { // Se o resto da divisão por 2 for diferente de 0, é ímpar
       //soma += i;
   // }
//}




    return 0;
}