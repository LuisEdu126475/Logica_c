#include<stdio.h>
#include<stdlib.h>
int main(){
    int num, positivo, negativo, zeros;
    positivo =0;
    negativo = 0;
    zeros = 0;

    printf("Digite um numero:");
    scanf("%d",&num);

    if(num>0){
        positivo ++;
        printf("Seu numero e positivo");
    }
    else if(num<0){
        negativo++;
        printf("Seu numero e negativo");
    }
    else{
        zeros++;
    }
     printf("\nDigite um numero:");
    scanf("%d",&num);

    if(num>0){
        positivo ++;
        printf("Seu numero e positivo");
    }
    else if(num<0){
        negativo++;
        printf("Seu numero e negativo");
    }
    else{
        zeros++;
    }
     printf("\nDigite um numero:");
    scanf("%d",&num);

    if(num>0){
        positivo ++;
        printf("Seu numero e positivo");
    }
    else if(num<0){
        negativo++;
        printf("Seu numero e negativo");
    }
    else{
        zeros++;
    }
     printf("\nDigite um numero:");
    scanf("%d",&num);

    if(num>0){
        positivo ++;
        printf("Seu numero e positivo");
    }
    else if(num<0){
        negativo++;
        printf("Seu numero e negativo");
    }
    else{
        zeros++;
    }
     printf("\nDigite um numero:");
    scanf("%d",&num);

    if(num>0){
        positivo ++;
        printf("\nSeu numero e positivo");
    }
    else if(num<0){
        negativo++;
        printf("\nSeu numero e negativo");
    }
    else{
        zeros++;
    }
    printf("\nPositivos:%d\tNegativos:%d\tZeros:%d",positivo,negativo,zeros);




}