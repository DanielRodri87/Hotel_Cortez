#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RESERVAS 100

struct Reserva
{
    int id;
    char nome[50];
    int numero;
    char data_entrada[11];
    char data_saida[11];
    int qtd_dias;
    char hora_entrada[6];
    char hora_saida[6];
    char status[10];
    float valor_pago;
};

// Função para calcular o lucro total dentro de um intervalo de datas
float calcular_lucro(struct Reserva reservas[], int num_reservas, const char *data_inicio, const char *data_fim)
{
    float lucro_total = 0.0;

    for (int i = 0; i < num_reservas; i++)
    {
        if (strcmp(reservas[i].status, "pago") == 0 &&
            strcmp(reservas[i].data_entrada, data_inicio) >= 0 &&
            strcmp(reservas[i].data_saida, data_fim) <= 0)
        {
            lucro_total += reservas[i].valor_pago;
        }
    }

    return lucro_total;
}

void gerenciar_financas()
{
    FILE *arquivo;
    char linha[200];
    struct Reserva reservas[MAX_RESERVAS];
    int num_reservas = 0;

    // Abrir o arquivo de reservas
    arquivo = fopen("db/datas.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de reservas.\n");
        return;
    }

    // Ler as reservas do arquivo
    while (fgets(linha, sizeof(linha), arquivo))
    {
        sscanf(linha, "%d %s %d %s %s %d %s %s %s %f",
               &reservas[num_reservas].id,
               reservas[num_reservas].nome,
               &reservas[num_reservas].numero,
               reservas[num_reservas].data_entrada,
               reservas[num_reservas].data_saida,
               &reservas[num_reservas].qtd_dias,
               reservas[num_reservas].hora_entrada,
               reservas[num_reservas].hora_saida,
               reservas[num_reservas].status,
               &reservas[num_reservas].valor_pago);

        num_reservas++;
    }

    fclose(arquivo);

    // Intervalo de datas fornecido pelo usuário
    char data_inicio[11];
    char data_fim[11];

    printf("Informe a data de início (formato DD/MM/YYYY): ");
    scanf("%s", data_inicio);
    printf("Informe a data de fim (formato DD/MM/YYYY): ");
    scanf("%s", data_fim);

    // Calcular o lucro total dentro do intervalo de datas
    float lucro_total = calcular_lucro(reservas, num_reservas, data_inicio, data_fim);

    printf("O lucro total no período de %s a %s é: R$%.2f\n", data_inicio, data_fim, lucro_total);
    system("pause");
}
