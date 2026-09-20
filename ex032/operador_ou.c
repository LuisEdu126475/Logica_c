#include <stdio.h>
#include <stdlib.h>

int main(){

    /* Aula 54 - Operador lógico ou (||) na linguagem C (Disjunção).
       Tabela verdade
       a < b    c < d    a < b || c < d
         v        v            v
         v        f            v
         f        v            v
         f        f            f
    */

    int a, b, c, d;

    a = 1;
    b = 2;
    c = 30;
    d = 4;

    if(a < b || c < d){
        printf("Verdadeiro\n\n");
    }
    else{
        printf("Falso\n\n");
    }


    /* Aula 54 - Operador lógico ou (||) na linguagem C (Disjunção).
       Tabela verdade
       a < b    c < d    a < b || c < d
         v        v            v
         v        f            v
         f        v            v
         f        f            f
    */

    int a, b, c, d;

    a = 10;
    b = 2;
    c = 30;
    d = 4;

    if(a < b || c < d){
        printf("Verdadeiro\n\n");
    }
    else{
        printf("Falso\n\n");
    }

    return 0;
}