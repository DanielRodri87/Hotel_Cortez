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

    // Aqui vou logar os clientes já cadastrados no banco de dados, e realizar as reservas dos quartos
    printf("Informe o CPF do cliente: ");
    scanf("%d", busca_cpf);

    // Aqui vou verificar se o cliente existe no banco de dados
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

            while (fscanf(arquivoQ, "%d, %d, %d, %d, %d, %d, %d, %d\n", numero, status, andar, camas, banheiros, ar, frigobar, tv) != EOF)
            {
                if (busca_quarto == numero)
                {
                    if (status == 0)
                    {
                        printf("Quarto reservado com sucesso!\n");
                        fprintf(arquivoQ, "%d, %d, %d, %d, %d, %d, %d, %d\n", numero, 1, andar, camas, banheiros, ar, frigobar, tv);
                        fprintf(arquivoD, "%d, %d, %d, %d, %d, %d, %d, %d\n", numero, 1, andar, camas, banheiros, ar, frigobar, tv);
                    }
                    else
                    {
                        printf("Quarto ocupado, escolha outro quarto!\n");
                    }
                }
            }

        }
        else
        {
            printf("Cliente não encontrado!\n");
        }
    }

}