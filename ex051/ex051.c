#include<stdio.h>
int main(){
    int senhaCorreta=123456,senha;
    printf("Digite a sua senha:");
    scanf("%d",&senha);

    while (senha != senhaCorreta)
    {
        printf("Senha incorreta! Tente Novamente:\n");
        scanf("%d",&senha);
    }
    printf("Sua senha esta correta!Acesso liberado:\n");
















    return 0;
}