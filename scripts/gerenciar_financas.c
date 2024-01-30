#include <stdio.h>
#include <string.h>
#include <time.h>

int id, numero, total_dias;
float valor_total;
char nome[50], hora_entrada[10], hora_saida[10], data_entrada[20], data_saida[20], status[10];

void gerenciar_financas_pagas()
{
    FILE *arquivoD = fopen("db/datas.txt", "r");
    if (arquivoD == NULL) {
        printf("Erro ao abrir o arquivo de datas para leitura.\n");
        system("pause");
        return;
    }

    char data_entrada[20], data_saida[20], status[10];
    struct tm tm_reserva_entrada, tm_reserva_saida, tm_reserva_entrada_db, tm_reserva_saida_db;

    float valor_total_intervalo = 0.0;

    printf("Informe a data inicial (formato DD/MM/YYYY): ");
    scanf("%s", data_entrada);
    printf("Informe a data final (formato DD/MM/YYYY): ");
    scanf("%s", data_saida);

    sscanf(data_entrada, "%d/%d/%d", &tm_reserva_entrada.tm_mday, &tm_reserva_entrada.tm_mon, &tm_reserva_entrada.tm_year);
    sscanf(data_saida, "%d/%d/%d", &tm_reserva_saida.tm_mday, &tm_reserva_saida.tm_mon, &tm_reserva_saida.tm_year);

    tm_reserva_entrada.tm_mon -= 1;
    tm_reserva_entrada.tm_year -= 1900;

    tm_reserva_saida.tm_mon -= 1;
    tm_reserva_saida.tm_year -= 1900;

    while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id, nome, &numero, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status, &valor_total) != EOF) {
        sscanf(data_entrada, "%d/%d/%d", &tm_reserva_entrada_db.tm_mday, &tm_reserva_entrada_db.tm_mon, &tm_reserva_entrada_db.tm_year);
        sscanf(data_saida, "%d/%d/%d", &tm_reserva_saida_db.tm_mday, &tm_reserva_saida_db.tm_mon, &tm_reserva_saida_db.tm_year);

        tm_reserva_entrada_db.tm_mon -= 1;
        tm_reserva_entrada_db.tm_year -= 1900;

        tm_reserva_saida_db.tm_mon -= 1;
        tm_reserva_saida_db.tm_year -= 1900;

        if ((tm_reserva_entrada.tm_year < tm_reserva_saida_db.tm_year || (tm_reserva_entrada.tm_year == tm_reserva_saida_db.tm_year && tm_reserva_entrada.tm_mon < tm_reserva_saida_db.tm_mon) ||
             (tm_reserva_entrada.tm_year == tm_reserva_saida_db.tm_year && tm_reserva_entrada.tm_mon == tm_reserva_saida_db.tm_mon && tm_reserva_entrada.tm_mday <= tm_reserva_saida_db.tm_mday)) &&
            (tm_reserva_saida.tm_year > tm_reserva_entrada_db.tm_year || (tm_reserva_saida.tm_year == tm_reserva_entrada_db.tm_year && tm_reserva_saida.tm_mon > tm_reserva_entrada_db.tm_mon) ||
             (tm_reserva_saida.tm_year == tm_reserva_entrada_db.tm_year && tm_reserva_saida.tm_mon == tm_reserva_entrada_db.tm_mon && tm_reserva_saida.tm_mday >= tm_reserva_entrada_db.tm_mday)) &&
            strcmp(status, "pago") == 0) {
                valor_total_intervalo += valor_total;
        }
    }

    fclose(arquivoD);

    printf("O valor total das reservas no intervalo e: %.2f\n", valor_total_intervalo);
    system("pause");
}

void gerenciar_financas_pendentes()
{
    FILE *arquivoD = fopen("db/datas.txt", "r");
    if (arquivoD == NULL) {
        printf("Erro ao abrir o arquivo de datas para leitura.\n");
        system("pause");
        return;
    }

    char data_entrada[20], data_saida[20], status[10];
    struct tm tm_reserva_entrada, tm_reserva_saida, tm_reserva_entrada_db, tm_reserva_saida_db;

    float valor_total_intervalo = 0.0;

    printf("Informe a data inicial (formato DD/MM/YYYY): ");
    scanf("%s", data_entrada);
    printf("Informe a data final (formato DD/MM/YYYY): ");
    scanf("%s", data_saida);

    sscanf(data_entrada, "%d/%d/%d", &tm_reserva_entrada.tm_mday, &tm_reserva_entrada.tm_mon, &tm_reserva_entrada.tm_year);
    sscanf(data_saida, "%d/%d/%d", &tm_reserva_saida.tm_mday, &tm_reserva_saida.tm_mon, &tm_reserva_saida.tm_year);

    tm_reserva_entrada.tm_mon -= 1;
    tm_reserva_entrada.tm_year -= 1900;

    tm_reserva_saida.tm_mon -= 1;
    tm_reserva_saida.tm_year -= 1900;

    while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id, nome, &numero, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status, &valor_total) != EOF) {
        sscanf(data_entrada, "%d/%d/%d", &tm_reserva_entrada_db.tm_mday, &tm_reserva_entrada_db.tm_mon, &tm_reserva_entrada_db.tm_year);
        sscanf(data_saida, "%d/%d/%d", &tm_reserva_saida_db.tm_mday, &tm_reserva_saida_db.tm_mon, &tm_reserva_saida_db.tm_year);

        tm_reserva_entrada_db.tm_mon -= 1;
        tm_reserva_entrada_db.tm_year -= 1900;

        tm_reserva_saida_db.tm_mon -= 1;
        tm_reserva_saida_db.tm_year -= 1900;

        if ((tm_reserva_entrada.tm_year < tm_reserva_saida_db.tm_year || (tm_reserva_entrada.tm_year == tm_reserva_saida_db.tm_year && tm_reserva_entrada.tm_mon < tm_reserva_saida_db.tm_mon) ||
             (tm_reserva_entrada.tm_year == tm_reserva_saida_db.tm_year && tm_reserva_entrada.tm_mon == tm_reserva_saida_db.tm_mon && tm_reserva_entrada.tm_mday <= tm_reserva_saida_db.tm_mday)) &&
            (tm_reserva_saida.tm_year > tm_reserva_entrada_db.tm_year || (tm_reserva_saida.tm_year == tm_reserva_entrada_db.tm_year && tm_reserva_saida.tm_mon > tm_reserva_entrada_db.tm_mon) ||
             (tm_reserva_saida.tm_year == tm_reserva_entrada_db.tm_year && tm_reserva_saida.tm_mon == tm_reserva_entrada_db.tm_mon && tm_reserva_saida.tm_mday >= tm_reserva_entrada_db.tm_mday)) &&
            strcmp(status, "pendente") == 0) {
                valor_total_intervalo += valor_total;
        }
    }

    fclose(arquivoD);

    printf("O valor total das reservas no intervalo e: %.2f\n", valor_total_intervalo);
    system("pause");
}

void gerenciar_financas_totais() {
    FILE *arquivoD = fopen("db/datas.txt", "r");
    if (arquivoD == NULL) {
        printf("Erro ao abrir o arquivo de datas para leitura.\n");
        system("pause");
        return;
    }

    float valor_total_todas_reservas = 0.0;

    while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id, nome, &numero, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status, &valor_total) != EOF) {
        valor_total_todas_reservas += valor_total;
    }

    fclose(arquivoD);

    // Exibe o valor total de todas as reservas
    printf("O valor total de todas as reservas e: %.2f\n", valor_total_todas_reservas);
    system("pause");
}


void gerenciar_financas()
{
    int opcao;

    do {
        system("clear || cls");
        printf("  =============================================\n");
        printf("  |  Verificar:                               |\n");
        printf("  |                              __   __      |\n");
        printf("  |  1 - Lucros recebidos       |  | |  |     |\n");
        printf("  |  2 - Lucros futuros         |__| |__|     |\n");
        printf("  |  3 - Lucro total             _    _        |\n");
        printf("  |  4 - Voltar                 |  | |  |     |\n");
        printf("  |                                           |\n");
        printf("  =============================================\n");
        printf("-> ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                gerenciar_financas_pagas();
                break;
            case 2:
                gerenciar_financas_pendentes();
                break;
            case 3:
                gerenciar_financas_totais();
                break;
            case 4:
                break;
            default:
                printf("Opcao invalida!\n");
                system("pause");
                break;
        }
    } while (opcao != 4);

}