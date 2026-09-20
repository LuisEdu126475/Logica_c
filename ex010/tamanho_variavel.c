#include<stdio.h>
int main(){
    int a;
    float b;
    char c;
    double d;
    printf("\n \t int=%d\n",sizeof(int));
    printf("\n \t int=%d\n",sizeof(char));
    printf("\n \t int=%d\n",sizeof(float));
    printf("\n \t int=%d\n",sizeof(double));

    printf("\n \t int =%d\n",sizeof a);
     printf("\n \t float =%d\n",sizeof b);
      printf("\n \t char =%d\n",sizeof c);
       printf("\n \t double =%d\n",sizeof d);




       //um byte equivale a 8 bits, sendo assim com esse codigo ele mostra quantos bytes consome a variavel.







    return 0;
}