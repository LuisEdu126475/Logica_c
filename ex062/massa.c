#include<stdio.h>
int main(){
    int tempo =0;
    float massa;

    printf("Digite a massa em gramas:");
    scanf("%f",&massa);
      printf("\t Massa:%f \t Tempo:%d\n",massa, tempo);

    while (massa>=0.05)
    {
        printf("\t Massa:%f \t Tempo:%d\n",massa, tempo);
        tempo +=50;
        massa = massa/2
    }
    printf("\t Tempo:%d\n",tempo);
}