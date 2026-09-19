#include<stdio.h>
int main(){
    char sexo = 'a';

    printf("\n Digite f para feminino ou m para masculino:");
    sexo = fgetc(stdin);
    //outra leitura de caracteres sendo chamada standart input sexo = getc(stdin); 
    //scanf("%c", &sexo);
    printf("\n Sexo digitado:%c", sexo);






}