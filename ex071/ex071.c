#include<stdio.h>
int main(){
    int i, vendas[10],maisVendido=0,indiceMaisVendido=0 ;
    float valores[10],total=0.0;

    for(i=0;i<10;i++){
        printf("\t\n Informe a quantidade vendida e o valor unitario do objeto %d:",i);
        scanf("%d%f",&vendas[i],&valores[i]);
    }
    for(i=0;i<10;i++){
        total+=vendas[i]*valores[i];
        printf("Quantidade v.:%d\tV. unitario R$%.2f\t. total R$%.2f\n", vendas[i],valores[i],vendas[i]*valores[i]);
        if(vendas[i]>maisVendido){
            maisVendido =vendas[i];
            indiceMaisVendido =i;
        }
    }
    printf("Vendas R$%.2f\tComissao R$%.2f\n",total,total*0.05);
    printf("Mais vendido:%d\tR$.2f\tPos:%d\n",maisVendido,valores[indiceMaisVendido],indiceMaisVendido);
}