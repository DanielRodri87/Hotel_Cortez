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

                        int opcao_confirmar_checkin, opcao_confirmar_pagamento, metodo_pagamento;
                        float valor_pago;

                        printf("Deseja confirmar o check-in:\n1 - Sim\n2 - Nao\n");
                        scanf("%d", &opcao_confirmar_checkin);

                        if (opcao_confirmar_checkin == 1)
                        {
                            printf("Deseja realizar o pagamento agora?:\n1 - Sim\n2 - Nao\n");
                            scanf("%d", &opcao_confirmar_pagamento);

                            if (opcao_confirmar_pagamento == 1)
                            {
                                printf("Informe o metodo de pagamento:\n1 - Dinheiro\n2 - Cartao\n3 - Pix\n");
                                scanf("%d", &metodo_pagamento);

                                switch (metodo_pagamento)
                                {
                                case 1:
                                    printf("Pagamento em cedulas!\n");
                                    printf("O valor da reserva e: %.2f\n", valor_total);
                                    printf("Informe o valor pago: ");
                                    scanf("%f", &valor_pago);

                                    if (valor_pago == valor_total)
                                    {
                                        printf("Pagamento realizado com sucesso!\n");

                                        // em quartos.txt, mudar o status do quarto para ocupado e em datas.txt, mudar o status de pagamento para pago
                                        FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                        FILE *arquivoQ2 = fopen("db/quartos2.txt", "w");
                                        if (arquivoQ == NULL)
                                        {
                                            printf("Erro ao abrir o arquivo de quartos para leitura.\n");
                                            return;
                                        }

                                        // db/quartos.txt
                                        // id numero tipo valor status
                                        // 851 666 suite 100.00 reservado
                                        // 615 302 simples 35.00 reservado
                                        // 680 654 duplo 60.00 ocupado
                                        // 573 407 simples 40.00 reservado

                                        // int id, numero;
                                        // char tipo[20], status[20];
                                        // float valor;
                                        int valor;
                                        char status[20], tipo[20];

                                        while (fscanf(arquivoQ, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF)
                                        {
                                            if (numero == busca_id)
                                            {
                                                fprintf(arquivoQ2, "%d %d %s %.2f ocupado\n", id, numero, tipo, valor);
                                            }
                                            else
                                            {
                                                fprintf(arquivoQ2, "%d %d %s %.2f %s\n", id, numero, tipo, valor, status);
                                            }
                                        }

                                        fclose(arquivoQ);
                                        fclose(arquivoQ2);

                                        remove("db/quartos.txt");
                                        rename("db/quartos2.txt", "db/quartos.txt");

                                        // db/datas.txt
                                        // id nome_cliente numero data_entrada data_saida total_dias hora_entrada hora_saida status_pagamento valor_total
                                        // 680 Rita 654 10/03/2024 15/03/2024 5 15:00 19:00 pendente 175.00
                                        // 573 Daniel 407 20/02/2024 23/02/2024 3 10:00 10:00 pendente 120.00

                                        // int id, numero, total_dias;
                                        // char nome_cliente[50], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                        // float valor_total;

                                        FILE *arquivoD = fopen("db/datas.txt", "r");
                                        FILE *arquivoD2 = fopen("db/datas2.txt", "w");

                                        if (arquivoD == NULL)
                                        {
                                            printf("Erro ao abrir o arquivo de datas para leitura.\n");
                                            return;
                                        }

                                        while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id, nome_cliente, &numero, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total) != EOF)
                                        {
                                            if (id == busca_id)
                                            {
                                                fprintf(arquivoD2, "%d %s %d %s %s %d %s %s pago %.2f\n", id, nome_cliente, numero, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, valor_total);
                                            }
                                            else
                                            {
                                                fprintf(arquivoD2, "%d %s %d %s %s %d %s %s %s %.2f\n", id, nome_cliente, numero, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, status_pagamento, valor_total);
                                            }
                                        }

                                        fclose(arquivoD);
                                        fclose(arquivoD2);

                                        remove("db/datas.txt");
                                        rename("db/datas2.txt", "db/datas.txt");

                                        printf("Check-in realizado com sucesso!\n");
                                        system("pause");
                                    }
                                    else if (valor_pago > valor_total)
                                    {
                                        printf("Pagamento realizado com sucesso!\n");
                                        printf("Troco: %.2f\n", valor_pago - valor_total);
                                        printf("Check-in realizado com sucesso!\n");
                                        system("pause");
                                    } else
                                    {
                                        printf("Valor pago insuficiente!\n");
                                        printf("Check-in cancelado!\n");
                                        system("pause");
                                    }

                                    break;
                                
                                default:
                                    break;
                                }

                            }
                            
                            // continuar o checkin
            
                        }
                        else
                        {
                            printf("Check-in cancelado!\n");
                            system("pause");
                        }


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
