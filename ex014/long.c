#include<stdio.h>
#include<stdlib.h>
int main(){
    long long int valor; //uso do long para aumentar a capacidade de memoria no int, visto que depois de completar totalmente ele fica negativo.
  long long int a,b,c;
  a = 2147483647;
  b = 1;
  c = a+b;

    printf("\n\t a=%lld\n\t b=%lld\n\t c=%lld\n\n\n", a,b,c);
    printf("\n\t Tamanho:%lld\n\n", sizeof valor);







    return 0;
}