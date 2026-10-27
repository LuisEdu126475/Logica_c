#include<stdio.h>
int main(){
    int i,num;
    printf("Digite um numero.");
    scanf("%d",&num);

    for (i = 0; i <=10; i++)
    {
    printf("\t %d*%d=%d\n", num, i, num*i);
     printf("\t %d+%d=%d\n", num, i, num+i);
      printf("\t %d/%d=%d\n", num, i, num/i);
       printf("\t %d-%d=%d\n", num, i, num-i);
    
    }
    






    return 0;
}