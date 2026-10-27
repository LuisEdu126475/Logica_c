#include<stdio.h>
int main(){
int n_funcionarios,i;
    float salario, soma_salario;
    float media,maior_salario, menor_salario;

    printf("Digite a quantidade de funcionarios (ou 0 para sair)");
    scanf("%d",&n_funcionarios);

    while (n_funcionarios!=0)
    {
        soma_salario= 0.0;

        for ( i = 1; i <=n_funcionarios; i++)
        {
            printf("Digite o salario do funcionario %d:",i);
            scanf("%f",&salario);

            soma_salario +=salario;
            if (i==1)
            {
                maior_salario=salario;
                menor_salario=salario;
                /* code */
            }
            else{
                
                if (salario>maior_salario)
                
                {
                    maior_salario = salario;
                }
                if (salario<menor_salario)
                {
                    menor_salario = salario;
                }
                
                
            }
            
        }
        media = soma_salario / n_funcionarios;

        printf("\n--- Resultados da Empresa ---\n");
        printf("Media dos salarios: R$ %.2f\n", media);
        printf("Salario mais alto: R$ %.2f\n", maior_salario);
        printf("Salario mais baixo: R$ %.2f\n\n", menor_salario);

        // Pede novamente para continuar ou sair
        printf("Digite a quantidade de funcionarios (ou 0 para sair): ");
        scanf("%d", &n_funcionarios);
    }
            printf("Programa encerrado com sucesso.\n");
    return 0;
    
}