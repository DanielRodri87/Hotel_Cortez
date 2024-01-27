#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>

void checkout()
{
    int menu_opcao_1, menu_opcao_2, buscar_id_reserva, id, numero, total_dias, busca_id, metodo_pagamento, tipo_cartao, opcao_confirmar_pagamento, id_d, numero_d, id_q, numero_quarto;
    char nome_cliente[50], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20], status[20], tipo[20];
    float valor_total, valor_pago, valor_q, valor_total_d;

    system("clear || cls");
    printf("=============================================\n");
    printf("|               Tela de Check-Out           |\n");
    printf("|                                           |\n");
    printf("|              __   __  __   __   __        |\n");
    printf("|             |  | |  ||  | |  | |  |       |\n");
    printf("|             |__| |__||__| |__| |__|       |\n");
    printf("|                                           |\n");
    printf("=============================================\n");

    printf("Voce deseja realizar o Check-Out?\n1 - Sim\n2 - Nao\n");
    scanf("%d", &menu_opcao_1);

    if (menu_opcao_1 == 1)
    {
        printf("Informe o ID da reserva:\n");
        scanf("%d", &buscar_id_reserva);

        FILE *arquivoD = fopen("db/datas.txt", "r");
        FILE *arquivoQ = fopen("db/quartos.txt", "r");

        if (arquivoD == NULL || arquivoQ == NULL)
        {
            printf("Erro ao abrir os arquivos de datas e quartos.\n");
            return;
        }

        while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id, nome_cliente, &numero, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total) != EOF)
        {
            if (buscar_id_reserva == id)
            {
                printf("Reserva encontrada:\n");
                printf("ID: %d\n", id);
                printf("Cliente: %s\n", nome_cliente);
                printf("Numero do quarto: %d\n", numero);
                printf("Data de entrada: %s\n", data_entrada);
                printf("Data de saida: %s\n", data_saida);
                printf("Total de dias: %d\n", total_dias);
                printf("Hora de entrada: %s\n", hora_entrada);
                printf("Hora de saida: %s\n", hora_saida);
                printf("Status de pagamento: %s\n", status_pagamento);
                printf("Valor total: %.2f\n", valor_total);
                system("pause");

                if (strcmp(status_pagamento, "pago") == 0)
                {
                    printf("Check-Out realizado com sucesso!\n");
                    printf("Obrigado pela preferencia!\n");
                    fclose(arquivoD);
                    fclose(arquivoQ);
                    system("pause");
                }
                else
                {
                    fclose(arquivoD);
                    fclose(arquivoQ);
                    printf("O check-out nao pode ser realizado, pois o pagamento ainda nao foi efetuado!\n");
                    printf("Deseja realizar o pagamento agora?\n1 - Sim\n2 - Nao\n");
                    scanf("%d", &menu_opcao_2);
                    if (menu_opcao_2 == 1)
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

                                FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");

                                if (arquivoQ == NULL || arquivoQAtualizado == NULL)
                                {
                                    printf("Erro ao abrir os arquivos de quartos.\n");
                                    return;
                                }

                                int id_q, numero_quarto;
                                char tipo[20];
                                float valor_q;
                                char status[20];

                                while (fscanf(arquivoQ, "%d %d %s %f %s\n", &id_q, &numero_quarto, tipo, &valor_q, status) != EOF)
                                {
                                    if (numero_quarto == numero)
                                    {
                                        fprintf(arquivoQAtualizado, "%d %d %s %.2f livre\n", id_q, numero_quarto, tipo, valor_q);
                                    }
                                    else
                                    {
                                        fprintf(arquivoQAtualizado, "%d %d %s %.2f %s\n", id_q, numero_quarto, tipo, valor_q, status);
                                    }
                                }

                                fclose(arquivoQ);
                                fclose(arquivoQAtualizado);

                                if (remove("db/quartos.txt") != 0)
                                {
                                    printf("Erro ao excluir o arquivo quartos.txt\n");
                                    return;
                                }

                                if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                {
                                    printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                    return;
                                }

                                FILE *arquivoD = fopen("db/datas.txt", "r");
                                FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                {
                                    printf("Erro ao abrir os arquivos de datas.\n");
                                    return;
                                }

                                int id_d, numero_d;
                                char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                int total_dias;
                                float valor_total_d;

                                while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                {
                                    if (id_d == buscar_id_reserva)
                                    {
                                        fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s pago %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, valor_total_d);
                                    }
                                    else
                                    {
                                        fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s %s %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, status_pagamento, valor_total_d);
                                    }
                                }

                                fclose(arquivoD);
                                fclose(arquivoDAtualizado);

                                if (remove("db/datas.txt") != 0)
                                {
                                    printf("Erro ao excluir o arquivo datas.txt\n");
                                    system("pause");
                                    return;
                                }

                                if (rename("db/datas_atualizado.txt", "db/datas.txt") != 0)
                                {
                                    printf("Erro ao renomear o arquivo datas_atualizado.txt\n");
                                    system("pause");
                                    return;
                                }
                            }

                            else if (valor_pago > valor_total)
                            {
                                printf("Pagamento realizado com sucesso!\n");
                                printf("Troco: %.2f\n", valor_pago - valor_total);
                                printf("Check-out realizado com sucesso!\n");
                                system("pause");

                                FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");

                                if (arquivoQ == NULL || arquivoQAtualizado == NULL)
                                {
                                    printf("Erro ao abrir os arquivos de quartos.\n");
                                    return;
                                }

                                int id_q, numero_quarto;
                                char tipo[20];
                                float valor_q;
                                char status[20];

                                while (fscanf(arquivoQ, "%d %d %s %f %s\n", &id_q, &numero_quarto, tipo, &valor_q, status) != EOF)
                                {
                                    if (numero_quarto == numero)
                                    {
                                        fprintf(arquivoQAtualizado, "%d %d %s %.2f livre\n", id_q, numero_quarto, tipo, valor_q);
                                    }
                                    else
                                    {
                                        fprintf(arquivoQAtualizado, "%d %d %s %.2f %s\n", id_q, numero_quarto, tipo, valor_q, status);
                                    }
                                }

                                fclose(arquivoQ);
                                fclose(arquivoQAtualizado);

                                if (remove("db/quartos.txt") != 0)
                                {
                                    printf("Erro ao excluir o arquivo quartos.txt\n");
                                    return;
                                }

                                if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                {
                                    printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                    return;
                                }

                                FILE *arquivoD = fopen("db/datas.txt", "r");
                                FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                {
                                    printf("Erro ao abrir os arquivos de datas.\n");
                                    return;
                                }

                                int id_d, numero_d;
                                char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                int total_dias;
                                float valor_total_d;

                                while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                {
                                    if (id_d == buscar_id_reserva)
                                    {
                                        fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s pago %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, valor_total_d);
                                    }
                                    else
                                    {
                                        fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s %s %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, status_pagamento, valor_total_d);
                                    }
                                }

                                fclose(arquivoD);
                                fclose(arquivoDAtualizado);

                                if (remove("db/datas.txt") != 0)
                                {
                                    printf("Erro ao excluir o arquivo datas.txt\n");
                                    system("pause");
                                    return;
                                }

                                if (rename("db/datas_atualizado.txt", "db/datas.txt") != 0)
                                {
                                    printf("Erro ao renomear o arquivo datas_atualizado.txt\n");
                                    system("pause");
                                    return;
                                }
                            }
                            else
                            {
                                printf("Valor pago insuficiente!\n");
                                printf("Check-out cancelado!\n");
                                remove("db/datas_atualizado.txt");
                                system("pause");
                            }
                            break;

                        case 2:
                            printf("Pagamento em cartao!\n");
                            printf("O valor da reserva e: %.2f\n", valor_total);
                            printf("Escolha o tipo de cartao:\n1 - Credito\n2 - Debito\n");
                            scanf("%d", &tipo_cartao);

                            if (tipo_cartao == 1)
                            {
                                printf("Voce escolheu o cartao de credito!\n");
                                printf("Informe o valor pago: ");
                                scanf("%f", &valor_pago);

                                if (valor_pago == valor_total)
                                {
                                    printf("Pagamento realizado com sucesso!\n");

                                    FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                    FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");

                                    if (arquivoQ == NULL || arquivoQAtualizado == NULL)
                                    {
                                        printf("Erro ao abrir os arquivos de quartos.\n");
                                        return;
                                    }

                                    while (fscanf(arquivoQ, "%d %d %s %f %s\n", &id_q, &numero_quarto, tipo, &valor_q, status) != EOF)
                                    {
                                        if (numero_quarto == numero)
                                        {
                                            fprintf(arquivoQAtualizado, "%d %d %s %.2f livre\n", id_q, numero_quarto, tipo, valor_q);
                                        }
                                        else
                                        {
                                            fprintf(arquivoQAtualizado, "%d %d %s %.2f %s\n", id_q, numero_quarto, tipo, valor_q, status);
                                        }
                                    }

                                    fclose(arquivoQ);
                                    fclose(arquivoQAtualizado);

                                    if (remove("db/quartos.txt") != 0)
                                    {
                                        printf("Erro ao excluir o arquivo quartos.txt\n");
                                        return;
                                    }

                                    if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                    {
                                        printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                        return;
                                    }

                                    FILE *arquivoD = fopen("db/datas.txt", "r");
                                    FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                    if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                    {
                                        printf("Erro ao abrir os arquivos de datas.\n");
                                        return;
                                    }

                                    while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                    {
                                        if (id_d == buscar_id_reserva)
                                        {
                                            fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s pago %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, valor_total_d);
                                        }
                                        else
                                        {
                                            fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s %s %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, status_pagamento, valor_total_d);
                                        }
                                    }

                                    fclose(arquivoD);
                                    fclose(arquivoDAtualizado);

                                    if (remove("db/datas.txt") != 0)
                                    {
                                        printf("Erro ao excluir o arquivo datas.txt\n");
                                        return;
                                    }

                                    if (rename("db/datas_atualizado.txt", "db/datas.txt") != 0)
                                    {
                                        printf("Erro ao renomear o arquivo datas_atualizado.txt\n");
                                        return;
                                    }

                                    printf("Check-Out realizado com sucesso!\n");
                                    printf("Obrigado pela preferencia!\n");
                                    system("pause");
                                }
                                else if (valor_pago > valor_total)
                                {
                                    printf("Pagamento realizado com sucesso!\n");
                                    printf("Troco: %.2f\n", valor_pago - valor_total);
                                    printf("Check-in realizado com sucesso!\n");
                                    system("pause");

                                    FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                    FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");

                                    if (arquivoQ == NULL || arquivoQAtualizado == NULL)
                                    {
                                        printf("Erro ao abrir os arquivos de quartos.\n");
                                        return;
                                    }

                                    int id_q, numero_quarto;
                                    char tipo[20];
                                    float valor_q;
                                    char status[20];

                                    while (fscanf(arquivoQ, "%d %d %s %f %s\n", &id_q, &numero_quarto, tipo, &valor_q, status) != EOF)
                                    {
                                        if (numero_quarto == numero)
                                        {
                                            fprintf(arquivoQAtualizado, "%d %d %s %.2f livre\n", id_q, numero_quarto, tipo, valor_q);
                                        }
                                        else
                                        {
                                            fprintf(arquivoQAtualizado, "%d %d %s %.2f %s\n", id_q, numero_quarto, tipo, valor_q, status);
                                        }
                                    }

                                    fclose(arquivoQ);
                                    fclose(arquivoQAtualizado);

                                    if (remove("db/quartos.txt") != 0)
                                    {
                                        printf("Erro ao excluir o arquivo quartos.txt\n");
                                        return;
                                    }

                                    if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                    {
                                        printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                        return;
                                    }

                                    FILE *arquivoD = fopen("db/datas.txt", "r");
                                    FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                    if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                    {
                                        printf("Erro ao abrir os arquivos de datas.\n");
                                        return;
                                    }

                                    int id_d, numero_d;
                                    char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                    int total_dias;
                                    float valor_total_d;
                                    while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                    {
                                        if (id_d == buscar_id_reserva)
                                        {
                                            fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s pago %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, valor_total_d);
                                        }
                                        else
                                        {
                                            fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s %s %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, status_pagamento, valor_total_d);
                                        }
                                    }
                                    fclose(arquivoD);
                                    fclose(arquivoDAtualizado);

                                    if (remove("db/datas.txt") != 0)
                                    {
                                        printf("Erro ao excluir o arquivo datas.txt\n");
                                        system("pause");
                                        return;
                                    }

                                    if (rename("db/datas_atualizado.txt", "db/datas.txt") != 0)
                                    {
                                        printf("Erro ao renomear o arquivo datas_atualizado.txt\n");
                                        system("pause");
                                        return;
                                    }
                                }
                                else
                                {
                                    printf("Valor pago insuficiente!\n");
                                    printf("Check-in cancelado!\n");
                                    remove("db/datas_atualizado.txt");
                                    system("pause");
                                }
                            }
                            else if (tipo_cartao == 2)
                            {
                                printf("Voce escolheu o cartao de credito!\n");
                                printf("Informe o valor pago: ");
                                scanf("%f", &valor_pago);

                                if (valor_pago == valor_total)
                                {
                                    printf("Pagamento realizado com sucesso!\n");

                                    FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                    FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");

                                    if (arquivoQ == NULL || arquivoQAtualizado == NULL)
                                    {
                                        printf("Erro ao abrir os arquivos de quartos.\n");
                                        return;
                                    }

                                    while (fscanf(arquivoQ, "%d %d %s %f %s\n", &id_q, &numero_quarto, tipo, &valor_q, status) != EOF)
                                    {
                                        if (numero_quarto == numero)
                                        {
                                            fprintf(arquivoQAtualizado, "%d %d %s %.2f livre\n", id_q, numero_quarto, tipo, valor_q);
                                        }
                                        else
                                        {
                                            fprintf(arquivoQAtualizado, "%d %d %s %.2f %s\n", id_q, numero_quarto, tipo, valor_q, status);
                                        }
                                    }

                                    fclose(arquivoQ);
                                    fclose(arquivoQAtualizado);

                                    if (remove("db/quartos.txt") != 0)
                                    {
                                        printf("Erro ao excluir o arquivo quartos.txt\n");
                                        return;
                                    }

                                    if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                    {
                                        printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                        return;
                                    }

                                    FILE *arquivoD = fopen("db/datas.txt", "r");
                                    FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                    if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                    {
                                        printf("Erro ao abrir os arquivos de datas.\n");
                                        return;
                                    }

                                    while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                    {
                                        if (id_d == buscar_id_reserva)
                                        {
                                            fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s pago %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, valor_total_d);
                                        }
                                        else
                                        {
                                            fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s %s %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, status_pagamento, valor_total_d);
                                        }
                                    }

                                    fclose(arquivoD);
                                    fclose(arquivoDAtualizado);

                                    if (remove("db/datas.txt") != 0)
                                    {
                                        printf("Erro ao excluir o arquivo datas.txt\n");
                                        return;
                                    }

                                    if (rename("db/datas_atualizado.txt", "db/datas.txt") != 0)
                                    {
                                        printf("Erro ao renomear o arquivo datas_atualizado.txt\n");
                                        return;
                                    }

                                    printf("Check-Out realizado com sucesso!\n");
                                    printf("Obrigado pela preferencia!\n");
                                    system("pause");
                                }
                                else if (valor_pago > valor_total)
                                {
                                    printf("Pagamento realizado com sucesso!\n");
                                    printf("Troco: %.2f\n", valor_pago - valor_total);
                                    printf("Check-in realizado com sucesso!\n");
                                    system("pause");

                                    FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                    FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");

                                    if (arquivoQ == NULL || arquivoQAtualizado == NULL)
                                    {
                                        printf("Erro ao abrir os arquivos de quartos.\n");
                                        return;
                                    }

                                    int id_q, numero_quarto;
                                    char tipo[20];
                                    float valor_q;
                                    char status[20];

                                    while (fscanf(arquivoQ, "%d %d %s %f %s\n", &id_q, &numero_quarto, tipo, &valor_q, status) != EOF)
                                    {
                                        if (numero_quarto == numero)
                                        {
                                            fprintf(arquivoQAtualizado, "%d %d %s %.2f livre\n", id_q, numero_quarto, tipo, valor_q);
                                        }
                                        else
                                        {
                                            fprintf(arquivoQAtualizado, "%d %d %s %.2f %s\n", id_q, numero_quarto, tipo, valor_q, status);
                                        }
                                    }

                                    fclose(arquivoQ);
                                    fclose(arquivoQAtualizado);

                                    if (remove("db/quartos.txt") != 0)
                                    {
                                        printf("Erro ao excluir o arquivo quartos.txt\n");
                                        return;
                                    }

                                    if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                    {
                                        printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                        return;
                                    }

                                    FILE *arquivoD = fopen("db/datas.txt", "r");
                                    FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                    if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                    {
                                        printf("Erro ao abrir os arquivos de datas.\n");
                                        return;
                                    }

                                    int id_d, numero_d;
                                    char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                    int total_dias;
                                    float valor_total_d;

                                    while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                    {
                                        if (id_d == buscar_id_reserva)
                                        {
                                            fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s pago %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, valor_total_d);
                                        }
                                        else
                                        {
                                            fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s %s %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, status_pagamento, valor_total_d);
                                        }
                                    }

                                    fclose(arquivoD);
                                    fclose(arquivoDAtualizado);

                                    if (remove("db/datas.txt") != 0)
                                    {
                                        printf("Erro ao excluir o arquivo datas.txt\n");
                                        system("pause");
                                        return;
                                    }

                                    if (rename("db/datas_atualizado.txt", "db/datas.txt") != 0)
                                    {
                                        printf("Erro ao renomear o arquivo datas_atualizado.txt\n");
                                        system("pause");
                                        return;
                                    }
                                }
                                else
                                {
                                    printf("Valor pago insuficiente!\n");
                                    printf("Check-in cancelado!\n");
                                    remove("db/datas_atualizado.txt");
                                    system("pause");
                                }
                            }
                            break;

                        case 3:
                            break;

                        default:
                            break;
                        }
                    }
                    else if (menu_opcao_2 == 2)
                    {
                        printf("Check-Out cancelado!\n");
                        system("pause");
                    }
                    else
                    {
                        printf("Opcao invalida!\n");
                        system("pause");
                    }
                }
            }
        }
    }
    else if (menu_opcao_1 == 2)
    {
        printf("Check-Out cancelado!\n");
        system("pause");
    }
    else
    {
        printf("Opcao invalida!\n");
        system("pause");
    }
}
