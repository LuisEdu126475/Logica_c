#include<stdio.h>
int main(){
    int i,idade, somaIdade=0, totalIdades=0;
    float altura,somaAlturas=0, totalAlturas=0;

    for ( i = 1; i < =5, i++)
    {
        printf("Digite idade e altura em metros:");
        scanf("%d%f",&idade,&altura);
        /* code */
        if (altura <1.7)
        {
            somaIdade = somaIdade +idade;
            totalIdades++
        }
        if (idade >20)
        {
            somaAlturas = somaAlturas + altura;
            totalAlturas++;
        }
        
    }
    
}