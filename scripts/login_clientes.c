#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void login_clientes()
{
    system("clear || cls");
    printf("\n=============================================\n");
    printf("Login dos Clientes:\n");
    printf("=============================================\n");

    char nome[50], email[50];
    int cpf, busca_cpf, rg, telefone;

    int busca_quarto;

    printf("Informe o CPF do cliente: ");
    scanf("%d", busca_cpf);

    FILE *arquivoC = fopen("db/clientes.txt", "r+");
    FILE *arquivoQ = fopen("db/quartos.txt", "r+");
    FILE *arquivoD = fopen("db/datas.txt", "w+");

    if (arquivoC == NULL || arquivoQ == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    while (fscanf(arquivoC, "%s, %d, %d, %d, %s\n", nome, cpf, rg, telefone, email) != EOF)
    {
        if (busca_cpf == cpf)
        {
            printf("Bem-vindo senhor(a) %s\n", nome);
            printf("Informe o número do quarto que deseja reservar: ");
            scanf("%d", busca_quarto);


            while (fscanf(arquivoQ, "%d, %d, %s, %d, %s\n", id, numero, tipo, valor, status) != EOF)
            {
                if (busca_quarto == numero)
                {

                    if (status == "livre")
                    {
                        printf("Quarto reservado com sucesso!\n");                        
                        fprintf(arquivoD, "%d, %s, %d, %s, %s\n", id, nome, numero, data_entrada, data_saida);
                        
                    }
                    else
                    {
                        printf("Quarto ocupado!\n");
                    }
                }
                else
                {
                    printf("Quarto não encontrado!\n");
                }
            }

        }
        else
        {
            printf("Cliente não encontrado!\n");
        }
    }

}