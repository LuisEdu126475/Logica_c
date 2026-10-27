#include<stdio.h>
int main(){
    float n1,n2,media;
    

    do
    {
         printf("Informe a primeira nota tirada no semestre:");
    scanf("%f", &n1);
       
    } while (n1<0 || n1>10);
    
    do
    {
        printf("Informe a segunda nota tirada no semestre");
        scanf("%f",&n2);
    } while (n2<0 || n2>10);
    media = (n1 + n2)/2;

    printf("A media de %.1f e %.1f e:%.1f",n1,n2,media);

}