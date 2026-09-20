#include <stdio.h>
#include <stdlib.h>

int main(){

    /*
    Tabela verdade
    a < b    c < d    a < b && c < d
      v        v            v
      v        f            f
      f        v            f
      f        f            f
    */

    int a, b, c, d;

    // --- Caso 1: Resultado Verdadeiro ---
    a = 1;
    b = 2;
    c = 3;
    d = 4;

    if(a < b && c < d){
        printf("Verdadeiro\n\n");
    }
    else{
        printf("Falso\n\n");
    }

    // --- Caso 2: Resultado Falso ---
    a = 1;
    b = 2;
    c = 30; // Alterado para 30 para que (c < d) seja falso
    d = 4;

    if(a < b && c < d){
        printf("Verdadeiro\n\n");
    }
    else{
        printf("Falso\n\n");
    }

    return 0; // O return deve ficar sempre ao final de tudo
}