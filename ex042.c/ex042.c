#include <stdio.h>
#include <stdlib.h>

int main(){
    char letra;

    printf("Digite uma letra: ");
    scanf(" %c", &letra); // O espaço antes de %c limpa o buffer

    // Verifica tanto vogais minúsculas quanto maiúsculas
    if(letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u' ||
       letra == 'A' || letra == 'E' || letra == 'I' || letra == 'O' || letra == 'U'){
        printf("A letra '%c' e uma vogal!\n", letra);
    }
    else{
        printf("A letra '%c' nao e uma vogal.\n", letra);
    }

    return 0;
}