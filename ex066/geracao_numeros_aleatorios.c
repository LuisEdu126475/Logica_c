#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){

    int i,valores[50];
    srand(time(NULL));

    for (i = 0; i < 50; i++)
    {
        valores[i] =rand();

    }
       for (i = 0; i < 50; i++)
    {
        printf("%d = %d\n",i,valores[i]);
        
    }
    









}