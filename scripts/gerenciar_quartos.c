#include "functor.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>

void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void cadastrarQuarto()
{
    int numero, quantidade_livre;
    float valor;
    char tipo[20], status[20];
    system("clear || cls");
    printf("=============================================\n");
    printf("|                Cadastro de quartos        |\n");
    printf("|                                           |\n");
    printf("|               __   __  __   __   __       |\n");
    printf("|              |  | |  ||  | |  | |  |      |\n");
    printf("|              |__| |__||__| |__| |__|      |\n");
    printf("|                                           |\n");
    printf("|               Preencha os dados:          |\n");
    printf("|                                           |\n");
    printf("=============================================\n\n");

    FILE *qtd_arquivo;
    qtd_arquivo = fopen("db/quantidade_quartos.txt", "r");

    if (qtd_arquivo == NULL)
    {
        printf("=============================================\n");
        printf("|             ERRO DE LEITURA!               |\n");
        printf("=============================================\n");
        return;
    }

    fscanf(qtd_arquivo, "%d", &quantidade_livre);

    fclose(qtd_arquivo);

    if (quantidade_livre > 0)
    {
        srand(time(NULL));
        int id = rand() % 1000;

        do
        {
            printf("Informe o numero do quarto: ");
            if (scanf("%d", &numero) != 1 || numero <= 0)
            {
                printf("Por favor, digite um número de quarto válido.\n");
                limparBufferEntrada();
            }

        } while (numero <= 0);

        do
        {
            printf("Informe o tipo do quarto: (simples, duplo ou suite) ");
            if (scanf("%19s", tipo) != 1)
            {
                printf("Por favor, digite um tipo de quarto válido.\n");
                limparBufferEntrada();
            }
        } while (!(strcmp(tipo, "simples") == 0 || strcmp(tipo, "duplo") == 0 || strcmp(tipo, "suite") == 0));

        do
        {
            printf("Informe o valor da diaria do quarto: ");
            if (scanf("%f", &valor) != 1 || valor <= 0)
            {
                printf("Por favor, digite um valor de diária válido.\n");
                limparBufferEntrada();
            }
        } while (valor <= 0);

        do
        {
            printf("Informe o status do quarto: (livre, ocupado ou reservado) ");
            if (scanf("%19s", status) != 1)
            {
                printf("Por favor, digite um status de quarto válido.\n");
                limparBufferEntrada();
            }
        } while (!(strcmp(status, "livre") == 0 || strcmp(status, "ocupado") == 0 || strcmp(status, "reservado") == 0));

        FILE *arquivo = fopen("db/quartos.txt", "a");

        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return;
        }

        fprintf(arquivo, "%d %d %s %.2f %s\n", id, numero, tipo, valor, status);
        fclose(arquivo);

        printf("Quarto cadastrado com sucesso!\n");

        qtd_arquivo = fopen("db/quantidade_quartos.txt", "w");

        if (qtd_arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return;
        }

        fprintf(qtd_arquivo, "%d", quantidade_livre - 1);

        fclose(qtd_arquivo);

        system("pause");
    }
    else
    {
        printf("Não é possível cadastrar mais quartos.\n");
        system("pause");
    }
}

void buscar_quartos()
{
    FILE *arquivo;
    int id, busca_id, numero, busca_numero;
    float valor, busca_valor;
    char tipo[20], busca_tipo[20], status[20], busca_status[20];
    int opcao_menu_busca_quartos;

    while (1)
    {
        system("clear || cls");
        printf("=============================================\n");
        printf("|                Colsutar quartos           |\n");
        printf("|                                           |\n");
        printf("|             __   __  __   __   __         |\n");
        printf("|            |  | |  ||  | |  | |  |        |\n");
        printf("|            |__| |__||__| |__| |__|        |\n");
        printf("|                                           |\n");
        printf("|               Pesquise os dados:          |\n");
        printf("|                                           |\n");
        printf("=============================================\n\n");

        arquivo = fopen("db/quartos.txt", "r");

        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo para leitura.\n");
            return;
        }

        system("clear || cls");
        printf("  =============================================\n");
        printf("  |  Buscar por:                              |\n");
        printf("  |                             __   __       |\n");
        printf("  |  1 - Numero                |  | |  |      |\n");
        printf("  |  2 - Tipo                  |__| |__|      |\n");
        printf("  |  3 - Valor                  __   __       |\n");
        printf("  |  4 - Status                |  | |  |      |\n");
        printf("  |  5 - Voltar                |__| |__|      |\n");
        printf("  |                                           |\n");
        printf("  =============================================\n");
        printf("-> ");
        scanf("%d", &opcao_menu_busca_quartos);

        fseek(arquivo, 0, SEEK_SET);

        switch (opcao_menu_busca_quartos)
        {
        case 1:
            printf("Informe o numero para pesquisar: ");
            scanf("%d", &busca_numero);

            while (fscanf(arquivo, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF)
            {
                if (busca_numero == numero)
                {
                    system("clear || cls");

                    printf("============================================================================\n");
                    printf("|                                  QUARTO ENCONTRADO                            |\n");
                    printf("============================================================================\n");
                    printf("| %-15s | %-10s | %-10s | %-15s | %-10s |\n", "ID", "Numero", "Tipo", "Valor", "Status");
                    printf("|-----------------|------------|------------|-----------------|------------|\n");
                    printf("| %-15d | %-10d | %-10s | %-15.2f | %-10s |\n", id, numero, tipo, valor, status);
                    printf("============================================================================\n");
                    system("pause");
                }
            }
            break;

        case 2:
            printf("Informe o Tipo para pesquisar: ");
            scanf("%s", busca_tipo);

            while (fscanf(arquivo, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF)
            {
                if (strcmp(busca_tipo, tipo) == 0)
                {
                    system("clear || cls");
                    printf("============================================================================\n");
                    printf("|                                  QUARTO ENCONTRADO                            |\n");
                    printf("============================================================================\n");
                    printf("| %-15s | %-10s | %-10s | %-15s | %-10s |\n", "ID", "Numero", "Tipo", "Valor", "Status");
                    printf("|-----------------|------------|------------|-----------------|------------|\n");
                    printf("| %-15d | %-10d | %-10s | %-15.2f | %-10s |\n", id, numero, tipo, valor, status);
                    printf("============================================================================\n");
                    system("pause");
                }
            }
            break;
            
        case 3:
            printf("Informe o Valor para pesquisar: ");
            scanf("%f", &busca_valor);

            while (fscanf(arquivo, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF)
            {
                if (busca_valor == valor)
                {
                    system("clear || cls");
                    printf("============================================================================\n");
                    printf("|                                  QUARTO ENCONTRADO                            |\n");
                    printf("============================================================================\n");
                    printf("| %-15s | %-10s | %-10s | %-15s | %-10s |\n", "ID", "Numero", "Tipo", "Valor", "Status");
                    printf("|-----------------|------------|------------|-----------------|------------|\n");
                    printf("| %-15d | %-10d | %-10s | %-15.2f | %-10s |\n", id, numero, tipo, valor, status);
                    printf("============================================================================\n");
                    system("pause");
                }
            }
            break;

        case 4:
            printf("Informe o Status para pesquisar: ");
            scanf("%s", busca_status);

            while (fscanf(arquivo, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF)
            {
                if (strcmp(busca_status, status) == 0)
                {
                    system("clear || cls");
                    printf("============================================================================\n");
                    printf("|                                  QUARTO ENCONTRADO                            |\n");
                    printf("============================================================================\n");
                    printf("| %-15s | %-10s | %-10s | %-15s | %-10s |\n", "ID", "Numero", "Tipo", "Valor", "Status");
                    printf("|-----------------|------------|------------|-----------------|------------|\n");
                    printf("| %-15d | %-10d | %-10s | %-15.2f | %-10s |\n", id, numero, tipo, valor, status);
                    printf("============================================================================\n");
                    system("pause");
                }
            }
            break;

        case 5:
            fclose(arquivo);
            return;
            break;
        }
        fclose(arquivo);
    }
}

void editar_quartos()
{
    system("clear || cls");
    printf("=============================================\n");
    printf("|                Editar quartos             |\n");
    printf("|                                           |\n");
    printf("|             __   __  __   __   __         |\n");
    printf("|            |  | |  ||  | |  | |  |        |\n");
    printf("|            |__| |__||__| |__| |__|        |\n");
    printf("|                                           |\n");
    printf("|       Edite os dados à sua escolha:       |\n");
    printf("|                                           |\n");
    printf("=============================================\n\n");

    FILE *arquivo, *temporario;

    int id, busca_id, numero;
    float valor;
    char tipo[20], status[20];
    int opcao_menu_busca_quartos;
    int menu_editar_quartos;

    // int contador_erros = 0;

    arquivo = fopen("db/quartos.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    temporario = fopen("db/temporario.txt", "w");

    if (temporario == NULL)
    {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    printf("Informe o ID do quarto que deseja editar: ");
    scanf("%d", &busca_id);

    while (fscanf(arquivo, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF)
    {
        if (busca_id == id)
        {
            system("clear || cls");
            printf("  =============================================\n");
            printf("  |  Editar:                                  |\n");
            printf("  |                             __   __       |\n");
            printf("  |  1 - Numero                |  | |  |      |\n");
            printf("  |  2 - Tipo                  |__| |__|      |\n");
            printf("  |  3 - Valor                  __   __       |\n");
            printf("  |  4 - Status                |  | |  |      |\n");
            printf("  |  5 - Voltar                |__| |__|      |\n");
            printf("  |                                           |\n");
            printf("  =============================================\n");
            printf("-> ");
            scanf("%d", &menu_editar_quartos);

            switch (menu_editar_quartos)
            {
            case 1:
                printf("Informe o novo numero do quarto: ");
                scanf("%d", &numero);
                break;
            case 2:
                printf("Informe o novo tipo do quarto: ");
                scanf("%s", tipo);
                break;
            case 3:
                printf("Informe o novo valor da diária do quarto: ");
                scanf("%f", &valor);
                break;
            case 4:
                printf("Informe o novo status do quarto: ");
                scanf("%s", status);
                break;
            case 5:
                fclose(arquivo);
                fclose(temporario);
                remove("db/temporario.txt");
                return;
            }
            fprintf(temporario, "%d %d %s %.2f %s\n", id, numero, tipo, valor, status);
        }
        else
        {
            fprintf(temporario, "%d %d %s %.2f %s\n", id, numero, tipo, valor, status);
        }
    }

    fclose(arquivo);
    fclose(temporario);

    remove("db/quartos.txt");
    rename("db/temporario.txt", "db/quartos.txt");

    system("pause");
}

void excluir_quarto()
{
    system("clear || cls");
    printf("=============================================\n");
    printf("|                Excluir quartos            |\n");
    printf("|                                           |\n");
    printf("|              __   __  __   __   __        |\n");
    printf("|             |  | |  ||  | |  | |  |       |\n");
    printf("|             |__| |__||__| |__| |__|       |\n");
    printf("|                                           |\n");
    printf("|              Excluir quartos:             |\n");
    printf("|                                           |\n");
    printf("=============================================\n\n");

  
}

void quantidade_quartos()
{
    system("clear || cls");
    printf("=============================================\n");
    printf("|       Verificar quartos  Disponíveis      |\n");
    printf("|                                           |\n");
    printf("|            __   __  __   __   __          |\n");
    printf("|           |  | |  ||  | |  | |  |         |\n");
    printf("|           |__| |__||__| |__| |__|         |\n");
    printf("|                                           |\n");
    printf("|  Descubra se existem quartos disponíveis: |\n");
    printf("|                                           |\n");
    printf("=============================================\n\n");

    FILE *qtd_arquivo;
    int nova_quantidade, quantidade_atual, opcao_quantidade;

    qtd_arquivo = fopen("db/quantidade_quartos.txt", "r");

    if (qtd_arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    printf("O que você deseja fazer?\n1 - Ver a quantidade atual de quartos\n2 - Alterar a quantidade de quartos\n3 - Voltar\n");
    scanf("%d", &opcao_quantidade);

    switch (opcao_quantidade)
    {
    case 1:
        fscanf(qtd_arquivo, "%d", &quantidade_atual);
        printf("A quantidade atual de quartos é: %d\n", quantidade_atual);
        system("pause");
        break;

    case 2:
        printf("Informe a nova quantidade de quartos: ");
        scanf("%d", &nova_quantidade);

        FILE *qtd_arquivo;
        qtd_arquivo = fopen("db/quantidade_quartos.txt", "w");

        if (qtd_arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return;
        }

        fprintf(qtd_arquivo, "%d", nova_quantidade);

        fclose(qtd_arquivo);

        printf("Quantidade de quartos alterada com sucesso!\n");
        system("pause");
        break;

    default:
        break;
    }
}

void quartos()
{
    while (1)
    {
        int opcao_menu_quartos;
        system("clear || cls");
        printf("  =============================================\n");
        printf("  |  Escolha uma operacao:                    |\n");
        printf("  |                             __   __       |\n");
        printf("  |  1 - Cadastrar Quarto      |  | |  |      |\n");
        printf("  |  2 - Consultar Quarto      |__| |__|      |\n");
        printf("  |  3 - Editar Quarto          __   __       |\n");
        printf("  |  4 - Exluir de Quarto      |  | |  |      |\n");
        printf("  |  5 - Quantidade de Quarto  |__| |__|      |\n");
        printf("  |  6 - Sair                                 |\n");
        printf("  |                                           |\n");
        printf("  =============================================\n");
        printf("-> ");
        scanf("%d", &opcao_menu_quartos);

        switch (opcao_menu_quartos)
        {
        case 1:
            cadastrarQuarto();
            break;

        case 2:
            buscar_quartos();
            break;
        case 3:
            editar_quartos();
            break;
        case 4:
            excluir_quarto();
            break;
        case 5:
            quantidade_quartos();
            break;
        case 6:
            return;
            break;
        }
    }
}