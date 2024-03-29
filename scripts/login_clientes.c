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
        scanf(" %s", data); 

        if (!validar_data(data))
        {
            printf("Data invalida ou menor que atual. Digite novamente.\n");
        }
    } while (!validar_data(data));
}

void mostrar_quartos_livres()
{
    printf("\n=============================================\n");
    printf("|              Quartos Disponiveis          |\n");
    printf("|                                           |\n");
    printf("|              __   __  __   __   __        |\n");
    printf("|             |  | |  ||  | |  | |  |       |\n");
    printf("|             |__| |__||__| |__| |__|       |\n");
    printf("|                                           |\n");
    printf("|                                           |\n");
    printf("=============================================\n\n");
    FILE *arquivoQ = fopen("db/quartos.txt", "r");

    if (arquivoQ == NULL)
    {
        printf("Erro ao abrir o arquivo de quartos para leitura.\n");
        return;
    }

    int id, numero;
    char tipo[20], status[20];
    float valor;

    printf("%-5s %-10s %-15s %-10s\n", "ID", "Numero", "Tipo", "Valor");
    printf("=============================================\n");

    while (fscanf(arquivoQ, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF)
    {
        if (strcmp(status, "livre") == 0)
        {
            printf("%-5d %-10d %-15s %.2f\n", id, numero, tipo, valor);
        }
    }
    printf("=============================================\n");

    fclose(arquivoQ);
}

void login_clientes()
{
    system("clear || cls");
    printf("=============================================\n");
    printf("|              Realizar Reservaa            |\n");
    printf("|                                           |\n");
    printf("|            __   __  __   __   __          |\n");
    printf("|           |  | |  ||  | |  | |  |         |\n");
    printf("|           |__| |__||__| |__| |__|         |\n");
    printf("|                                           |\n");
    printf("|                                           |\n");
    printf("=============================================\n\n");

    char nome[50], email[50];
    int cpf, busca_cpf, rg, telefone;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char data[20];

    printf("Data atual: %d/%d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    int busca_quarto, id, numero;
    char tipo[20], status[20], hora_entrada[20], hora_saida[20];
    float valor, valor_total;

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
            system("clear || cls");
            printf("======================================================\n");
            printf("|                     Bem-vindo(a) %s                |\n", nome);
            printf("|   De acordo com a tabela de quartos disponiveis,   |\n");
            printf("|    digite o numero do quarto que deseja reservar:  |\n");
            printf("|                                                    |\n");
            printf("======================================================\n");
            mostrar_quartos_livres();
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
                        system("clear || cls");
                        printf("Quarto reservado com sucesso!\n");

                        char data_entrada[20], data_saida[20];
                        obter_data_valida("Informe a data de entrada (formato DD/MM/YYYY): ", data_entrada);
                        printf("Informe a hora de entrada (formato HH:MM): ");
                        scanf("%s", hora_entrada);

                        obter_data_valida("Informe a data de saida (formato DD/MM/YYYY): ", data_saida);
                        printf("Informe a hora de saida (formato HH:MM): ");
                        scanf("%s", hora_saida);

                        int total_dias = diferenca_dias(data_entrada, data_saida);
                        valor_total = total_dias * valor;

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
                                fprintf(arquivoD, "%d %s %d %s %s %d %s %s %s %.2f\n", id, nome, numero, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, "reservado", valor_total);
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
                        printf("Reserva cadastrada com sucesso!\n");
                        system("pause");
                    }
                    else if (strcmp(status, "reservado") == 0)
                    {
                        struct tm tm_reserva_entrada = {0};
                        struct tm tm_reserva_saida = {0};
                        struct tm tm_reserva_entrada_db = {0};
                        struct tm tm_reserva_saida_db = {0};

                        char data_entrada[20], data_saida[20];
                        int total_dias;
                        system("clear || cls");
                        printf("O quarto ja se encontra reservado.\nPor favor, informe datas diferentes para a reserva.\n");
                        printf("Informe a data de entrada (formato DD/MM/YYYY): ");
                        scanf("%s", data_entrada);
                        printf("Informe a data de saida (formato DD/MM/YYYY): ");
                        scanf("%s", data_saida);

                        sscanf(data_entrada, "%d/%d/%d", &tm_reserva_entrada.tm_mday, &tm_reserva_entrada.tm_mon, &tm_reserva_entrada.tm_year);
                        sscanf(data_saida, "%d/%d/%d", &tm_reserva_saida.tm_mday, &tm_reserva_saida.tm_mon, &tm_reserva_saida.tm_year);

                        tm_reserva_entrada.tm_mon -= 1;
                        tm_reserva_entrada.tm_year -= 1900;

                        tm_reserva_saida.tm_mon -= 1;
                        tm_reserva_saida.tm_year -= 1900;

                        char data_entrada_bd[20], data_saida_bd[20];
                        FILE *arquivoD = fopen("db/datas.txt", "r");
                        if (arquivoD == NULL)
                        {
                            printf("Erro ao abrir o arquivo de datas para leitura.\n");
                            system("pause");
                            return;
                        }

                        while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id, nome, &numero, data_entrada_bd, data_saida_bd, &total_dias, hora_entrada, hora_saida, status, &valor_total) != EOF)
                        {
                            if (busca_quarto == numero)
                            {
                                sscanf(data_entrada_bd, "%d/%d/%d", &tm_reserva_entrada_db.tm_mday, &tm_reserva_entrada_db.tm_mon, &tm_reserva_entrada_db.tm_year);
                                sscanf(data_saida_bd, "%d/%d/%d", &tm_reserva_saida_db.tm_mday, &tm_reserva_saida_db.tm_mon, &tm_reserva_saida_db.tm_year);

                                tm_reserva_entrada_db.tm_mon -= 1;
                                tm_reserva_entrada_db.tm_year -= 1900;

                                tm_reserva_saida_db.tm_mon -= 1;
                                tm_reserva_saida_db.tm_year -= 1900;
                            }
                        }

                        fclose(arquivoD);

                        if ((tm_reserva_entrada.tm_year < tm_reserva_saida_db.tm_year || (tm_reserva_entrada.tm_year == tm_reserva_saida_db.tm_year && tm_reserva_entrada.tm_mon < tm_reserva_saida_db.tm_mon) ||
                             (tm_reserva_entrada.tm_year == tm_reserva_saida_db.tm_year && tm_reserva_entrada.tm_mon == tm_reserva_saida_db.tm_mon && tm_reserva_entrada.tm_mday <= tm_reserva_saida_db.tm_mday)) &&
                            (tm_reserva_saida.tm_year > tm_reserva_entrada_db.tm_year || (tm_reserva_saida.tm_year == tm_reserva_entrada_db.tm_year && tm_reserva_saida.tm_mon > tm_reserva_entrada_db.tm_mon) ||
                             (tm_reserva_saida.tm_year == tm_reserva_entrada_db.tm_year && tm_reserva_saida.tm_mon == tm_reserva_entrada_db.tm_mon && tm_reserva_saida.tm_mday >= tm_reserva_entrada_db.tm_mday)))
                        {
                            system("clear || cls");
                            printf("Erro: O quarto ja se encontra reservado nesse periodo\n");
                            printf("Aqui esta uma lista de quartos disponiveis para reserva:\n");
                            system("pause");
                            mostrar_quartos_livres();
                            system("pause");
                        }

                        else
                        {
                            system("clear || cls");
                            printf("Quarto reservado com sucesso!\n");

                            total_dias = diferenca_dias(data_entrada, data_saida);
                            valor_total = total_dias * valor;

                            printf("Informe a hora de entrada (formato HH:MM): ");
                            scanf("%s", hora_entrada);
                            printf("Informe a hora de saida (formato HH:MM): ");
                            scanf("%s", hora_saida);

                            FILE *arquivoReserva = fopen("db/datas.txt", "a");
                            if (arquivoReserva == NULL)
                            {
                                printf("Erro ao abrir o arquivo de reservas para escrita.\n");
                                return;
                            }

                            id = id + 1;
                            fprintf(arquivoReserva, "%d %s %d %s %s %d %s %s %s %.2f\n", id, nome, numero, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, "reservado", valor_total);
                            fclose(arquivoReserva);

                            printf("Reserva realizada com sucesso!\n");
                        }
                    } else {
                        system("clear || cls");
                        printf("Erro: O quarto ja se encontra ocupado\n");
                        printf("Aqui esta uma lista de quartos disponiveis para reserva:\n ");
                        mostrar_quartos_livres();
                        system("pause");
                    }
                }
            }

            if (!quarto_encontrado)
            {
                printf("=============================\n");
                printf("Quarto nao encontrado!\n");
                printf("=============================\n");
                system("pause");
            }

            break;
        }
    }

    fclose(arquivoC);
    fclose(arquivoQ);
    fclose(arquivoD);
}