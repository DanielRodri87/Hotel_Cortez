#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "functor.h"


#include <string.h>
#include <time.h>

int diferenca_dias(const char *data_entrada, const char *data_saida) {
    struct tm tm_entrada = {0};
    struct tm tm_saida = {0};

    sscanf(data_entrada, "%d/%d/%d", &tm_entrada.tm_mday, &tm_entrada.tm_mon, &tm_entrada.tm_year);
    sscanf(data_saida, "%d/%d/%d", &tm_saida.tm_mday, &tm_saida.tm_mon, &tm_saida.tm_year);

    tm_entrada.tm_mon -= 1; 
    tm_entrada.tm_year -= 1900; 

    tm_saida.tm_mon -= 1;
    tm_saida.tm_year -= 1900;

    time_t entrada_seconds = mktime(&tm_entrada);
    time_t saida_seconds = mktime(&tm_saida);

    int diferenca_segundos = difftime(saida_seconds, entrada_seconds);
    int diferenca_dias = diferenca_segundos / (60 * 60 * 24);

    return diferenca_dias;
}

void login_clientes()
{
    system("clear || cls");
    printf("\n=============================================\n");
    printf("Login dos Clientes:\n");
    printf("=============================================\n");

    char nome[50], email[50];
    int cpf, busca_cpf, rg, telefone;

    int busca_quarto, id, numero;
    char tipo[20], status[20];
    float valor;

    printf("Informe o CPF do cliente: ");
    scanf("%d", &busca_cpf);

    FILE *arquivoC = fopen("db/clientes.txt", "r");
    FILE *arquivoQ = fopen("db/quartos.txt", "r");
    FILE *arquivoD = fopen("db/datas.txt", "a");

    if (arquivoC == NULL || arquivoQ == NULL || arquivoD == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura ou escrita.\n");
        return;
    }

    while (fscanf(arquivoC, "%s %d %d %d %s\n", nome, &cpf, &rg, &telefone, email) != EOF)
    {
        if (busca_cpf == cpf)
        {
            printf("Bem-vindo senhor(a) %s\n", nome);
            printf("Informe o número do quarto que deseja reservar: ");
            scanf("%d", &busca_quarto);

            rewind(arquivoQ);  // Reinicia a leitura do arquivo de quartos

            while (fscanf(arquivoQ, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF)
            {
                if (busca_quarto == numero)
                {
                    if (strcmp(status, "livre") == 0)
                    {
                        printf("Quarto reservado com sucesso!\n");

                        // Adicione código para obter e processar datas
                        char data_entrada[20], data_saida[20];
                        printf("Informe a data de entrada (formato DD/MM/YYYY): ");
                        scanf("%s", data_entrada);
                        printf("Informe a data de saída (formato DD/MM/YYYY): ");
                        scanf("%s", data_saida);

                        // Adicione código para calcular total de dias
                        // (supondo que a estrutura da data seja conhecida)
                        // Exemplo: total_dias = calcular_total_dias(data_entrada, data_saida);

                        int total_dias;  // Substitua por seu cálculo real

                        printf("Total de dias: %d\n", total_dias);

                        fprintf(arquivoD, "%d %s %d %s %s %d\n", id, nome, numero, data_entrada, data_saida, total_dias);
                    }
                    else
                    {
                        printf("Quarto não está livre!\n");
                    }
                    break;  // Não é necessário continuar procurando quartos
                }
            }
            break;  // Não é necessário continuar procurando clientes
        }
    }

    fclose(arquivoC);
    fclose(arquivoQ);
    fclose(arquivoD);
}