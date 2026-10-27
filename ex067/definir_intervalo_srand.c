#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    int i , valores[50];
    srand(time(Null));

    for ( i = 0; i < 50; i++)
    {
       valores[i] = 100 + (rand()%900);
    }
    for ( i = 0; i < 50; i++)
    {
        printf("%d = %d\n",i ,valores[i]);
    }
    
}