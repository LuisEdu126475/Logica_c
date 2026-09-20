#include <stdio.h>

int main() {
    // short economiza memória. Vai de -32.768 até 32.767 (e não apenas 2 casas).
    short valor = 10; 

    // CORREÇÃO: O especificador correto para short é %hd. 
    // CORREÇÃO: O operador sizeof retorna um tipo especial (size_t), o correto para ele é %zu.
    printf("\n \t Valor: %hd \t Tamanho: %zu bytes\n\n\n", valor, sizeof(valor));

    return 0;
}
