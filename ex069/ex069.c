#include<stdio.h>
int main(){
    int v1[25], v2[25],v3[25],i;

    for ( i = 0; i < 25; i++)
    {
        printf("Digite 25 valores:",i);
        scanf("%d", &v1[i]);
    }
    for ( i = 0; i < 25; i++)
    {
        printf("Digite agora outros 25 valores:",i);
        scanf("%d", &v2[i]);
    }
    for ( i = 0; i < 25; i++)
    {
        v3[i] = v1[i] + v2[i];
    }
    
    for ( i = 0; i < 25; i++)
    {
       printf("\t\nO valor do vetor 3 é de:%d", v3[i]);
    }
    printf("\nOs primeiros valores que digitou do primeiro vetor foi:");
    for ( i = 0; i < 25; i++)
    {
        printf("\n\t%d",v1[i]); 
}
     printf("\nOs segundos valores que digitou do primeiro vetor foi:");
    for ( i = 0; i < 25; i++)
    {
        printf("\t\n%d",v2[i]); 
}
}