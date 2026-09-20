#include<stdio.h>
//Aprendizado de limpeza de buffer
int main(){

char a,b;
printf("\t\n Digite dois caracteres:");
//scanf("%c %c", &a, &b); // esse espacamento e a limpeza de buffer do teclado
//podemos fazer tambem a limpeza com o getchar
scanf("%c",&a);
getchar();
scanf("%c",&b);
printf("\n\t a=%c\t b=%c\n", a, b);
printf("\n\t b=%d\t b=%d\n", a, b);










    return 0;
}