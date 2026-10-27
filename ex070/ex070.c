#include<stdio.h>
int main(){


        int i, vet[20],a=0, f=19, copia;

        for(i =0; i<20 ; i++){
            printf("\n Digite um valor %d:",i);
            scanf("%d",&vet[i]);
        }
        printf("\n")
        for(i=0; i<20;i++)
        printf("%d",vet[i]);
        printf("\n");
        
        while (a<f)
        {
            copia = vet[a];
            vet[a] = vet[f];
            vet[f] = copia;
            a++;
            f--;
        }
        printf("\n")
        for(i=0;i<20;i++)
        printf("%d",vet[i]);
}