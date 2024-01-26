#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int opcao_menu_checkin, busca_cpf, busca_id;
char consuta_cpf[20];
// variaveis necessarias
int cpf, rg, telefone;
char nome[50], email[50];

void checkin()
{
    system("clear || cls");
    printf("=============================================\n");
    printf("|              Realize o Check-in           |\n");
    printf("|                                           |\n");
    printf("|              __   __  __   __   __        |\n");
    printf("|             |  | |  ||  | |  | |  |       |\n");
    printf("|             |__| |__||__| |__| |__|       |\n");
    printf("|                                           |\n");
    printf("|              Seja bem-vindo:              |\n");
    printf("|                                           |\n");
    printf("=============================================\n\n");

    printf("  =============================================\n");
    printf("  |  Escolha uma Opcao:                       |\n");
    printf("  |                             __   __       |\n");
    printf("  |  1 - Check-in              |  | |  |      |\n");
    printf("  |  2 - Realizar reserva      |__| |__|      |\n");
    printf("  |  3 - Consultar reservas                   |\n");
    printf("  |  4 - Voltar                |__| |__|      |\n");
    printf("  |                                           |\n");
    printf("  =============================================\n");
    printf("-> ");
    scanf("%d", &opcao_menu_checkin);

    switch (opcao_menu_checkin)
    {
    case 1:
        system("clear || cls");
        printf("=============================================\n");
        printf("|               Tela de Check-in            |\n");
        printf("|                                           |\n");
        printf("|              __   __  __   __   __        |\n");
        printf("|             |  | |  ||  | |  | |  |       |\n");
        printf("|             |__| |__||__| |__| |__|       |\n");
        printf("|                                           |\n");
        printf("=============================================\n");

        printf("Informe o CPF do cliente: ");
        scanf("%d", &busca_cpf);

        FILE *arquivoC = fopen("db/clientes.txt", "r");

        while (fscanf(arquivoC, "%s %d %d %d %s\n", nome, &cpf, &rg, &telefone, email) != EOF)
        {
            if (busca_cpf == cpf)
            {
                printf("Bem-vindo(a) %s!\n", nome);
                printf("Informe o ID da reserva: ");
                scanf("%d", &busca_id);

                int id, numero;
                char nome_cliente[50], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                int total_dias;
                float valor_total;

                // Open "datas.txt" for reading
                FILE *arquivoD = fopen("db/datas.txt", "r");
                if (arquivoD == NULL)
                {
                    printf("Erro ao abrir o arquivo de datas para leitura.\n");
                    return;
                }

                // Search for the reservation ID in "datas.txt"
                while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id, nome_cliente, &numero, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total) != EOF)
                {
                    if (busca_id == id)
                    {
                        printf("Reserva encontrada:\n");
                        printf("ID: %d\n", id);
                        printf("Cliente: %s\n", nome_cliente);
                        printf("Número do quarto: %d\n", numero);
                        printf("Data de entrada: %s\n", data_entrada);
                        printf("Data de saída: %s\n", data_saida);
                        printf("Total de dias: %d\n", total_dias);
                        printf("Hora de entrada: %s\n", hora_entrada);
                        printf("Hora de saída: %s\n", hora_saida);
                        printf("Status de pagamento: %s\n", status_pagamento);
                        printf("Valor total: %.2f\n", valor_total);
                        system("pause");

                        break;
                    }
                }

                fclose(arquivoD); 
                break;
            }
        }
        break;

    case 2:

        break;

    case 3:

        break;

    case 4:

        break;

    default:
        printf("Opcao invalida!\n");
        break;
    }
}
