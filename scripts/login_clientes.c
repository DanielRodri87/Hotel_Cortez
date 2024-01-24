#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
            printf("Informe o numero do quarto que deseja reservar: ");
            scanf("%d", &busca_quarto);

            rewind(arquivoQ);

            while (fscanf(arquivoQ, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF)
            {
                if (busca_quarto == numero)
                {
                    if (strcmp(status, "livre") == 0)
                    {
                        printf("Quarto reservado com sucesso!\n");

                        char data_entrada[20], data_saida[20];
                        obter_data_valida("Informe a data de entrada (formato DD/MM/YYYY): ", data_entrada);
                        obter_data_valida("Informe a data de saída (formato DD/MM/YYYY): ", data_saida);

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

                        fprintf(arquivoD, "%d %s %d %s %s %d\n", id, nome, numero, data_entrada, data_saida, total_dias);
                    }
                    else if (strcmp(status, "reservado") == 0)
                    {
                        char data_reserva_entrada[20], data_reserva_saida[20], data_entrada[20], data_saida[20];
                        int total_dias_reserva;

                        fscanf(arquivoD, "%*d %*s %*d %s %s %d\n", data_reserva_entrada, data_reserva_saida, &total_dias_reserva);

                        struct tm tm_reserva_entrada = {0};
                        struct tm tm_reserva_saida = {0};

                        sscanf(data_reserva_entrada, "%d/%d/%d", &tm_reserva_entrada.tm_mday, &tm_reserva_entrada.tm_mon, &tm_reserva_entrada.tm_year);
                        sscanf(data_reserva_saida, "%d/%d/%d", &tm_reserva_saida.tm_mday, &tm_reserva_saida.tm_mon, &tm_reserva_saida.tm_year);

                        tm_reserva_entrada.tm_mon -= 1;
                        tm_reserva_entrada.tm_year -= 1900;

                        tm_reserva_saida.tm_mon -= 1;
                        tm_reserva_saida.tm_year -= 1900;

                        struct tm tm_entrada_cliente = {0};
                        struct tm tm_saida_cliente = {0};

                        obter_data_valida("Informe a data de entrada (formato DD/MM/YYYY): ", data_entrada);
                        obter_data_valida("Informe a data de saída (formato DD/MM/YYYY): ", data_saida);

                        sscanf(data_entrada, "%d/%d/%d", &tm_entrada_cliente.tm_mday, &tm_entrada_cliente.tm_mon, &tm_entrada_cliente.tm_year);
                        sscanf(data_saida, "%d/%d/%d", &tm_saida_cliente.tm_mday, &tm_saida_cliente.tm_mon, &tm_saida_cliente.tm_year);

                        tm_entrada_cliente.tm_mon -= 1;
                        tm_entrada_cliente.tm_year -= 1900;

                        tm_saida_cliente.tm_mon -= 1;
                        tm_saida_cliente.tm_year -= 1900;

                        if ((difftime(mktime(&tm_saida_cliente), mktime(&tm_reserva_entrada)) > 0) &&
                            (difftime(mktime(&tm_reserva_saida), mktime(&tm_entrada_cliente)) > 0))
                        {
                            printf("O quarto já está reservado para o período solicitado.\n");
                            system("pause");
                            return;
                        }
                        else
                        {
                            printf("Quarto ocupado!\n");
                            system("pause");
                        }
                        break;
                    }
                }
            }
        }
        else
        {
            printf("Cliente nao encontrado!\n");
            system("pause");
        }
    }

    fclose(arquivoC);
    fclose(arquivoQ);
    fclose(arquivoD);
}