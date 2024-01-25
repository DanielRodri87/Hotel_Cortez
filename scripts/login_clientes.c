#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Data
{
    int dia;
    int mes;
    int ano;
};

int diferenca_dias(const char *data_entrada, const char *data_saida)
{
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

int validar_data(const char *data)
{
    struct tm tm_data = {0};
    if (sscanf(data, "%d/%d/%d", &tm_data.tm_mday, &tm_data.tm_mon, &tm_data.tm_year) != 3)
    {
        return 0;
    }

    tm_data.tm_mon -= 1;
    tm_data.tm_year -= 1900;

    time_t data_seconds = mktime(&tm_data);

    if (data_seconds == -1 || difftime(data_seconds, time(NULL)) < 0)
    {
        return 0;
    }

    return 1;
}

void obter_data_valida(const char *prompt, char *data)
{
    do
    {
        printf("%s", prompt);
        scanf("%s", data);

        if (!validar_data(data))
        {
            printf("Data inválida ou menor que a atual. Digite novamente.\n");
        }
    } while (!validar_data(data));
}

// Função para verificar se há sobreposição de datas
int verifica_sobreposicao(struct Data data_entrada, struct Data data_saida,
                          struct Data reserva_ini, struct Data reserva_fim)
{
    return (data_entrada.ano < reserva_fim.ano ||
            (data_entrada.ano == reserva_fim.ano && data_entrada.mes < reserva_fim.mes) ||
            (data_entrada.ano == reserva_fim.ano && data_entrada.mes == reserva_fim.mes && data_entrada.dia <= reserva_fim.dia)) &&
           (data_saida.ano > reserva_ini.ano ||
            (data_saida.ano == reserva_ini.ano && data_saida.mes > reserva_ini.mes) ||
            (data_saida.ano == reserva_ini.ano && data_saida.mes == reserva_ini.mes && data_saida.dia >= reserva_ini.dia));
}

void login_clientes()
{
    system("clear || cls");
    printf("\n=============================================\n");
    printf("Login dos Clientes:\n");
    printf("=============================================\n");

    char nome[50], email[50];
    int cpf, busca_cpf, rg, telefone;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char data[20];

    printf("Data atual: %d/%d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    int busca_quarto, id, numero;
    char tipo[20], status[20], hora_entrada[20], hora_saida[20], status_pagamento[20];
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
            printf("Informe o numero do quarto que deseja reservar: ");
            scanf("%d", &busca_quarto);

            rewind(arquivoQ);

            int quarto_encontrado = 0;

            while (fscanf(arquivoQ, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF)
            {
                if (busca_quarto == numero)
                {
                    quarto_encontrado = 1;

                    if (strcmp(status, "livre") == 0)
                    {
                        printf("Quarto reservado com sucesso!\n");

                        char data_entrada[20], data_saida[20];

                        obter_data_valida("Informe a data de entrada (formato DD/MM/YYYY): ", data_entrada);
                        printf("Informe a hora de entrada (formato HH:MM): ");
                        scanf("%s", hora_entrada);

                        obter_data_valida("Informe a data de saida (formato DD/MM/YYYY): ", data_saida);
                        printf("Informe a hora de saida (formato HH:MM): ");
                        scanf("%s", hora_saida);

                        int total_dias = diferenca_dias(data_entrada, data_saida);

                        printf("Total de dias: %d\n", total_dias);

                        FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");
                        if (arquivoQAtualizado == NULL)
                        {
                            printf("Erro ao abrir o arquivo para escrita.\n");
                            return;
                        }

                        rewind(arquivoQ);

                        while (fscanf(arquivoQ, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF)
                        {
                            if (busca_quarto == numero)
                            {
                                fprintf(arquivoQAtualizado, "%d %d %s %.2f %s\n", id, numero, tipo, valor, "reservado");
                            }
                            else
                            {
                                fprintf(arquivoQAtualizado, "%d %d %s %.2f %s\n", id, numero, tipo, valor, status);
                            }
                        }

                        fclose(arquivoQ);
                        fclose(arquivoQAtualizado);

                        remove("db/quartos.txt");
                        rename("db/quartos_atualizado.txt", "db/quartos.txt");

                        fprintf(arquivoD, "%d %s %d %s %s %d %s %s %s\n", id, nome, numero, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, "pendente");
                    }
                    else if (strcmp(status, "reservado") == 0)
                    {
                        printf("Quarto atualmente reservado.\n");

                        char data_entrada_atual[20], data_saida_atual[20];

                        while (fscanf(arquivoD, "%d %*s %d %s %s %*d %s %s %s\n", &id, &busca_quarto, data_entrada_atual, data_saida_atual, hora_entrada, hora_saida, status_pagamento) != EOF)
                        {
                            if (busca_quarto == numero)
                            {
                                printf("Período atual de reserva: %s a %s\n", data_entrada_atual, data_saida_atual);
                                break;
                            }
                        }

                        char nova_data_entrada[20], nova_data_saida[20];
                        int total_dias;

                        obter_data_valida("Informe a nova data de entrada (formato DD/MM/YYYY): ", nova_data_entrada);
                        printf("Informe a nova hora de entrada (formato HH:MM): ");
                        scanf("%s", hora_entrada);

                        obter_data_valida("Informe a nova data de saida (formato DD/MM/YYYY): ", nova_data_saida);
                        printf("Informe a nova hora de saida (formato HH:MM): ");
                        scanf("%s", hora_saida);

                        struct Data tm_entrada, tm_saida, reservaExistenteIni, reservaExistenteFim;

                        sscanf(nova_data_entrada, "%d/%d/%d", &tm_entrada.dia, &tm_entrada.mes, &tm_entrada.ano);
                        sscanf(nova_data_saida, "%d/%d/%d", &tm_saida.dia, &tm_saida.mes, &tm_saida.ano);
                        sscanf(data_entrada_atual, "%d/%d/%d", &reservaExistenteIni.dia, &reservaExistenteIni.mes, &reservaExistenteIni.ano);
                        sscanf(data_saida_atual, "%d/%d/%d", &reservaExistenteFim.dia, &reservaExistenteFim.mes, &reservaExistenteFim.ano);

                        if (verifica_sobreposicao(tm_entrada, tm_saida, reservaExistenteIni, reservaExistenteFim))
                        {
                            printf("Não é possível reservar neste período devido à sobreposição de datas.\n");
                            system("pause");
                        }
                        else
                        {
                            printf("Reserva atualizada com sucesso!\n");

                            FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "a");
                            if (arquivoDAtualizado == NULL)
                            {
                                printf("Erro ao abrir o arquivo de datas para escrita.\n");
                                system("pause");
                                return;
                            }

                            // Adicione a nova reserva como uma linha adicional ao final do arquivo
                            fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s %s\n", id, status, numero, nova_data_entrada, nova_data_saida, total_dias, hora_entrada, hora_saida, status_pagamento);

                            fclose(arquivoDAtualizado);

                            // Continue com o restante do seu código aqui...

                            system("pause");
                        }
                    }
                }
            }

            if (!quarto_encontrado)
            {
                printf("Quarto não encontrado!\n");
                system("pause");
            }

            break;
        }
    }

    fclose(arquivoC);
    fclose(arquivoQ);
    fclose(arquivoD);
}
