#include <stdio.h>
#include <stdlib.h>

int main(){

    /* Aula 52 - Operador lógico de negação ! na linguagem C.
       Tabela verdade
       x < y   !(x < y)
         V   ->   F
         F   ->   V
    */

    if(!(10 < 15)){
        printf("Verdadeiro\n\n");
    }
    else{
        printf("Falso\n\n");
    }

    return 0;
}