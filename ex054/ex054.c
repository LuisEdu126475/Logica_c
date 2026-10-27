#include<stdio.h>
int main(){
    int i, divisao;

    for (i = 7; i <=9999; i+=7)
    {
        divisao = i%7;
        if(divisao ==0){
            printf("%d\n",i);

        }
    }
    
 



    return 0;
}