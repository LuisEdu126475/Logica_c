#include <stdio.h>
int main(){
    int n, valor,divisores,opcao;
    do
    {
        divisores =0;
        printf("1-Executar novamente\t 2-Sair:");
scanf("%d",&opcao);
    
    
do
{
   printf("Digite um valor maior que 1:");
scanf("%d",&n);

} while (valor<2);
printf("\t Divisores: ")

    for(i =1; i<= valor; i++){
        if(valor % i ==0){
            printf("%d",i);
            divisores ++;
        }
    }
    printf("\t Divisores:%d\n",divisores);

    if(divisores ==2 )
    printf("\t Eh primo\n");
    else
    printf("Nao e primo");
}while (opcao!=2);
}