#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
int main (){
    setlocale(LC_ALL,"Portuguese");
    int segundos,horas,minutos,resto;
    printf("Digite uma quantidade de segundos:");
    scanf("%d",&segundos);
horas = segundos/3600;
resto = segundos%3600;
minutos = resto/60;
segundos = resto %60;


printf("\t%d:%d:%d\n", horas,minutos,segundos);





}