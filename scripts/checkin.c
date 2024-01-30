#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int opcao_menu_checkin, busca_cpf, busca_id;
char consuta_cpf[20];
// variaveis necessarias
int cpf, rg, telefone;
char nome[50], email[50];

void apagarReservaPorId(const char *arquivo, int id)
{
    FILE *arquivoOriginal = fopen(arquivo, "r");
    FILE *arquivoTemporario = fopen("temporario.txt", "w");

    if (arquivoOriginal == NULL || arquivoTemporario == NULL)
    {
        perror("Erro ao abrir os arquivos");
        exit(EXIT_FAILURE);
    }

    char linha[256];

    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL)
    {
        int idLinha;
        sscanf(linha, "%d", &idLinha);

        if (idLinha != id)
        {
            fputs(linha, arquivoTemporario);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    if (remove(arquivo) != 0)
    {
        perror("Erro ao remover o arquivo original");
        exit(EXIT_FAILURE);
    }

    if (rename("temporario.txt", arquivo) != 0)
    {
        perror("Erro ao renomear o arquivo temporário");
        exit(EXIT_FAILURE);
    }
}

void listarReservas(const char *arquivo)
{
    FILE *arquivoReservas = fopen(arquivo, "r");

    if (arquivoReservas == NULL)
    {
        perror("Erro ao abrir o arquivo de reservas");
        exit(EXIT_FAILURE);
    }

    printf("=================================================================================================================================\n");
    printf("|                                               LISTA DE RESERVAS                                                                |\n");
    printf("==================================================================================================================================\n");
    printf("| %-5s | %-15s | %-10s | %-12s | %-12s | %-4s | %-8s | %-8s | %-10s | %-15s |\n",
           "ID", "Nome", "Numero", "Data Entrada", "Data Saida", "Dias", "Hora Entrada", "Hora Saida", "Status", "Valor");
    printf("|--------------------------------------------------------------------------------------------------------------------------------|\n");

    int id, numero, dias;
    char nome[20], data_entrada[12], data_saida[12], hora_entrada[8], hora_saida[8], status[20];
    float valor;

    while (fscanf(arquivoReservas, "%d %s %d %s %s %d %s %s %s %f",
                  &id, nome, &numero, data_entrada, data_saida, &dias, hora_entrada, hora_saida, status, &valor) != EOF)
    {
        printf("| %-5d | %-15s | %-10d | %-12s | %-12s | %-4d | %-8s | %-8s | %-10s | %-15.2f |\n",
               id, nome, numero, data_entrada, data_saida, dias, hora_entrada, hora_saida, status, valor);
    }

    printf("==================================================================================================================================\n");

    fclose(arquivoReservas);
}

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
    printf("  |  2 - Excluir reserva       |__| |__|      |\n");
    printf("  |  3 - Consultar reservas    |  | |  |      |\n");
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
                int total_dias, tipo_cartao;
                float valor_total;

                // Open "datas.txt" for reading
                FILE *arquivoD = fopen("db/datas.txt", "r");
                if (arquivoD == NULL)
                {
                    printf("Erro ao abrir o arquivo de datas para leitura.\n");
                    fclose(arquivoC);
                    return;
                }

                // Open "datas_atualizado.txt" for writing
                FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");
                if (arquivoDAtualizado == NULL)
                {
                    printf("Erro ao abrir o arquivo de datas_atualizado.txt para escrita.\n");
                    fclose(arquivoD);
                    fclose(arquivoC);
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
                        printf("Numero do quarto: %d\n", numero);
                        printf("Data de entrada: %s\n", data_entrada);
                        printf("Data de saida: %s\n", data_saida);
                        printf("Total de dias: %d\n", total_dias);
                        printf("Hora de entrada: %s\n", hora_entrada);
                        printf("Hora de saida: %s\n", hora_saida);
                        printf("Status de pagamento: %s\n", status_pagamento);
                        printf("Valor total: %.2f\n", valor_total);
                        system("pause");

                        int opcao_confirmar_checkin, opcao_confirmar_pagamento, metodo_pagamento;
                        float valor_pago;

                        printf("Deseja confirmar o check-in:\n1 - Sim\n2 - Nao\n");
                        scanf("%d", &opcao_confirmar_checkin);

                        if (opcao_confirmar_checkin == 1)
                        {
                            printf("Deseja realizar o pagamento agora?\n1 - Sim\n2 - Nao\n");
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

                                        FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                        FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");

                                        if (arquivoQ == NULL || arquivoQAtualizado == NULL)
                                        {
                                            printf("Erro ao abrir os arquivos de quartos.\n");
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            fclose(arquivoC);
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
                                                fprintf(arquivoQAtualizado, "%d %d %s %.2f ocupado\n", id_q, numero_quarto, tipo, valor_q);
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
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            fclose(arquivoC);
                                            return;
                                        }

                                        if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                        {
                                            printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            fclose(arquivoC);
                                            return;
                                        }

                                        fclose(arquivoD);
                                        fclose(arquivoDAtualizado);

                                        FILE *arquivoD = fopen("db/datas.txt", "r");
                                        FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                        if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                        {
                                            printf("Erro ao abrir os arquivos de datas.\n");
                                            fclose(arquivoC);
                                            return;
                                        }

                                        int id_d, numero_d;
                                        char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                        int total_dias;
                                        float valor_total_d;

                                        while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                        {
                                            if (id_d == busca_id)
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
                                        printf("Check-in realizado com sucesso!\n");
                                        system("pause");

                                        FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                        FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");

                                        if (arquivoQ == NULL || arquivoQAtualizado == NULL)
                                        {
                                            printf("Erro ao abrir os arquivos de quartos.\n");
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            fclose(arquivoC);
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
                                                fprintf(arquivoQAtualizado, "%d %d %s %.2f ocupado\n", id_q, numero_quarto, tipo, valor_q);
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
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            fclose(arquivoC);
                                            return;
                                        }

                                        if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                        {
                                            printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            fclose(arquivoC);
                                            return;
                                        }

                                        fclose(arquivoD);
                                        fclose(arquivoDAtualizado);

                                        FILE *arquivoD = fopen("db/datas.txt", "r");
                                        FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                        if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                        {
                                            printf("Erro ao abrir os arquivos de datas.\n");
                                            fclose(arquivoC);
                                            return;
                                        }

                                        int id_d, numero_d;
                                        char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                        int total_dias;
                                        float valor_total_d;

                                        while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                        {
                                            if (id_d == busca_id)
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
                                        fclose(arquivoD);
                                        fclose(arquivoDAtualizado);
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
                                                fclose(arquivoD);
                                                fclose(arquivoDAtualizado);
                                                fclose(arquivoC);
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
                                                    fprintf(arquivoQAtualizado, "%d %d %s %.2f ocupado\n", id_q, numero_quarto, tipo, valor_q);
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
                                                fclose(arquivoD);
                                                fclose(arquivoDAtualizado);
                                                fclose(arquivoC);
                                                return;
                                            }

                                            if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                            {
                                                printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                                fclose(arquivoD);
                                                fclose(arquivoDAtualizado);
                                                fclose(arquivoC);
                                                return;
                                            }

                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);

                                            FILE *arquivoD = fopen("db/datas.txt", "r");
                                            FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                            if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                            {
                                                printf("Erro ao abrir os arquivos de datas.\n");
                                                fclose(arquivoC);
                                                return;
                                            }

                                            int id_d, numero_d;
                                            char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                            int total_dias;
                                            float valor_total_d;

                                            while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                            {
                                                if (id_d == busca_id)
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
                                            printf("Check-in realizado com sucesso!\n");
                                            system("pause");

                                            FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                            FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");

                                            if (arquivoQ == NULL || arquivoQAtualizado == NULL)
                                            {
                                                printf("Erro ao abrir os arquivos de quartos.\n");
                                                fclose(arquivoD);
                                                fclose(arquivoDAtualizado);
                                                fclose(arquivoC);
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
                                                    fprintf(arquivoQAtualizado, "%d %d %s %.2f ocupado\n", id_q, numero_quarto, tipo, valor_q);
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
                                                fclose(arquivoD);
                                                fclose(arquivoDAtualizado);
                                                fclose(arquivoC);
                                                return;
                                            }

                                            if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                            {
                                                printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                                fclose(arquivoD);
                                                fclose(arquivoDAtualizado);
                                                fclose(arquivoC);
                                                return;
                                            }

                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);

                                            FILE *arquivoD = fopen("db/datas.txt", "r");
                                            FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                            if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                            {
                                                printf("Erro ao abrir os arquivos de datas.\n");
                                                fclose(arquivoC);
                                                return;
                                            }

                                            int id_d, numero_d;
                                            char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                            int total_dias;
                                            float valor_total_d;

                                            while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                            {
                                                if (id_d == busca_id)
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
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
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
                                                fclose(arquivoD);
                                                fclose(arquivoDAtualizado);
                                                fclose(arquivoC);
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
                                                    fprintf(arquivoQAtualizado, "%d %d %s %.2f ocupado\n", id_q, numero_quarto, tipo, valor_q);
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
                                                fclose(arquivoD);
                                                fclose(arquivoDAtualizado);
                                                fclose(arquivoC);
                                                return;
                                            }

                                            if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                            {
                                                printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                                fclose(arquivoD);
                                                fclose(arquivoDAtualizado);
                                                fclose(arquivoC);
                                                return;
                                            }

                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);

                                            FILE *arquivoD = fopen("db/datas.txt", "r");
                                            FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                            if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                            {
                                                printf("Erro ao abrir os arquivos de datas.\n");
                                                fclose(arquivoC);
                                                return;
                                            }

                                            int id_d, numero_d;
                                            char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                            int total_dias;
                                            float valor_total_d;

                                            while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                            {
                                                if (id_d == busca_id)
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
                                            printf("Check-in realizado com sucesso!\n");
                                            system("pause");

                                            FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                            FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");

                                            if (arquivoQ == NULL || arquivoQAtualizado == NULL)
                                            {
                                                printf("Erro ao abrir os arquivos de quartos.\n");
                                                fclose(arquivoD);
                                                fclose(arquivoDAtualizado);
                                                fclose(arquivoC);
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
                                                    fprintf(arquivoQAtualizado, "%d %d %s %.2f ocupado\n", id_q, numero_quarto, tipo, valor_q);
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
                                                fclose(arquivoD);
                                                fclose(arquivoDAtualizado);
                                                fclose(arquivoC);
                                                return;
                                            }

                                            if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                            {
                                                printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                                fclose(arquivoD);
                                                fclose(arquivoDAtualizado);
                                                fclose(arquivoC);
                                                return;
                                            }

                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);

                                            FILE *arquivoD = fopen("db/datas.txt", "r");
                                            FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                            if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                            {
                                                printf("Erro ao abrir os arquivos de datas.\n");
                                                fclose(arquivoC);
                                                return;
                                            }

                                            int id_d, numero_d;
                                            char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                            int total_dias;
                                            float valor_total_d;

                                            while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                            {
                                                if (id_d == busca_id)
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
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            remove("db/datas_atualizado.txt");
                                            system("pause");
                                        }
                                    }
                                    break;

                                case 3:
                                    printf("Pagamento em pix!\n");
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
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            fclose(arquivoC);
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
                                                fprintf(arquivoQAtualizado, "%d %d %s %.2f ocupado\n", id_q, numero_quarto, tipo, valor_q);
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
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            fclose(arquivoC);
                                            return;
                                        }

                                        if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                        {
                                            printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            fclose(arquivoC);
                                            return;
                                        }

                                        fclose(arquivoD);
                                        fclose(arquivoDAtualizado);

                                        FILE *arquivoD = fopen("db/datas.txt", "r");
                                        FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                        if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                        {
                                            printf("Erro ao abrir os arquivos de datas.\n");
                                            fclose(arquivoC);
                                            return;
                                        }

                                        int id_d, numero_d;
                                        char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                        int total_dias;
                                        float valor_total_d;

                                        while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                        {
                                            if (id_d == busca_id)
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
                                        printf("Check-in realizado com sucesso!\n");
                                        system("pause");

                                        FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                        FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");

                                        if (arquivoQ == NULL || arquivoQAtualizado == NULL)
                                        {
                                            printf("Erro ao abrir os arquivos de quartos.\n");
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            fclose(arquivoC);
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
                                                fprintf(arquivoQAtualizado, "%d %d %s %.2f ocupado\n", id_q, numero_quarto, tipo, valor_q);
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
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            fclose(arquivoC);
                                            return;
                                        }

                                        if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                        {
                                            printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                            fclose(arquivoD);
                                            fclose(arquivoDAtualizado);
                                            fclose(arquivoC);
                                            return;
                                        }

                                        fclose(arquivoD);
                                        fclose(arquivoDAtualizado);

                                        FILE *arquivoD = fopen("db/datas.txt", "r");
                                        FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                        if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                        {
                                            printf("Erro ao abrir os arquivos de datas.\n");
                                            fclose(arquivoC);
                                            return;
                                        }

                                        int id_d, numero_d;
                                        char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                        int total_dias;
                                        float valor_total_d;

                                        while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                        {
                                            if (id_d == busca_id)
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
                                        fclose(arquivoD);
                                        fclose(arquivoDAtualizado);
                                        remove("db/datas_atualizado.txt");
                                        system("pause");
                                    }

                                default:
                                    break;
                                }
                            }
                            else
                            {
                                printf("O pagamento continuara como pendente, realize no check-out!\n");
                                // mudar apenas o status do quartos.txt para ocupado
                                FILE *arquivoQ = fopen("db/quartos.txt", "r");
                                FILE *arquivoQAtualizado = fopen("db/quartos_atualizado.txt", "w");

                                if (arquivoQ == NULL || arquivoQAtualizado == NULL)
                                {
                                    printf("Erro ao abrir os arquivos de quartos.\n");
                                    fclose(arquivoD);
                                    fclose(arquivoDAtualizado);
                                    fclose(arquivoC);
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
                                        fprintf(arquivoQAtualizado, "%d %d %s %.2f ocupado\n", id_q, numero_quarto, tipo, valor_q);
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
                                    fclose(arquivoD);
                                    fclose(arquivoDAtualizado);
                                    fclose(arquivoC);
                                    return;
                                }

                                if (rename("db/quartos_atualizado.txt", "db/quartos.txt") != 0)
                                {
                                    printf("Erro ao renomear o arquivo quartos_atualizado.txt\n");
                                    fclose(arquivoD);
                                    fclose(arquivoDAtualizado);
                                    fclose(arquivoC);
                                    return;
                                }

                                // mudar o status do pagamento para pendente
                                // id nome numero data_entrada data_saida total_dias hora_entrada hora_saida status_pagamento valor_total
                                fclose(arquivoD);
                                fclose(arquivoDAtualizado);

                                FILE *arquivoD = fopen("db/datas.txt", "r");
                                FILE *arquivoDAtualizado = fopen("db/datas_atualizado.txt", "w");

                                if (arquivoD == NULL || arquivoDAtualizado == NULL)
                                {
                                    printf("Erro ao abrir os arquivos de datas.\n");
                                    fclose(arquivoC);
                                    return;
                                }

                                int id_d, numero_d;
                                char nome_cliente[100], data_entrada[11], data_saida[11], hora_entrada[6], hora_saida[6], status_pagamento[20];
                                int total_dias;
                                float valor_total_d;

                                while (fscanf(arquivoD, "%d %s %d %s %s %d %s %s %s %f\n", &id_d, nome_cliente, &numero_d, data_entrada, data_saida, &total_dias, hora_entrada, hora_saida, status_pagamento, &valor_total_d) != EOF)
                                {
                                    if (id_d == busca_id)
                                    {
                                        fprintf(arquivoDAtualizado, "%d %s %d %s %s %d %s %s pendente %.2f\n", id_d, nome_cliente, numero_d, data_entrada, data_saida, total_dias, hora_entrada, hora_saida, valor_total_d);
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

                                printf("Check-in realizado com sucesso!\n");
                                system("pause");
                            }
                            fclose(arquivoD);
                            fclose(arquivoDAtualizado);
                            remove("db/datas_atualizado.txt");
                        }
                        else
                        {
                            printf("Check-in cancelado!\n");
                            fclose(arquivoD);
                            fclose(arquivoDAtualizado);
                            remove("db/datas_atualizado.txt");
                            system("pause");
                        }
                        break;
                    }
                }

                fclose(arquivoD);
                fclose(arquivoDAtualizado);
                break;
            }
        }
        fclose(arquivoC);
        break;

    case 2:
        system("clear || cls");
        printf("=============================================\n");
        printf("|               Apagar Reserva              |\n");
        printf("|                                           |\n");
        printf("|              __   __  __   __   __        |\n");
        printf("|             |  | |  ||  | |  | |  |       |\n");
        printf("|             |__| |__||__| |__| |__|       |\n");
        printf("|                                           |\n");
        printf("=============================================\n");

        printf("Digite o ID da reserva a ser apagada: ");
        scanf("%d", &busca_id);

        apagarReservaPorId("db/datas.txt", busca_id);

        printf("Reserva apagada com sucesso.\n");
        system("pause");

        break;

    case 3:
        listarReservas("db/datas.txt");
        system("pause");
        break;

    case 4:
        printf("saindo...\n");
        break;

    default:
        printf("Opcao invalida!\n");
        system("pause");
        break;
    }
}