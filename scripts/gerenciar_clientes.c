#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool validar_cpf(char cpf[])
{
    int i, j, digito1 = 0, digito2 = 0;
    if (strlen(cpf) != 11)
        return false;
    for (i = 0, j = 10; i < strlen(cpf) - 2; i++, j--)
        digito1 += (cpf[i] - '0') * j;
    digito1 %= 11;
    if (digito1 < 2)
        digito1 = 0;
    else
        digito1 = 11 - digito1;
    if (digito1 != cpf[9] - '0')
        return false;
    for (i = 0, j = 11; i < strlen(cpf) - 1; i++, j--)
        digito2 += (cpf[i] - '0') * j;
    digito2 %= 11;
    if (digito2 < 2)
        digito2 = 0;
    else
        digito2 = 11 - digito2;
    if (digito2 != cpf[10] - '0')
        return false;
    return true;
}

bool validar_rg(char rg[])
{
    return (strlen(rg) == 7);
}

bool validar_email(char email[])
{
    int i, arroba = 0, ponto = 0;
    for (i = 0; i < strlen(email); i++)
    {
        if (email[i] == '@')
        {
            arroba++;
        }
        if (email[i] == '.')
        {
            ponto++;
        }
    }
    return (arroba == 1 && ponto >= 1);
}

void cadastrar_cliente()
{
    char nome[50], email[50], cidade_estado[100];
    char cpf[50], rg[50], telefone[50];

    system("clear || cls");
    printf("=============================================\n");
    printf("|             Cadastrar Clientes            |\n");
    printf("|                                           |\n");
    printf("|            __   __  __   __   __          |\n");
    printf("|           |  | |  ||  | |  | |  |         |\n");
    printf("|           |__| |__||__| |__| |__|         |\n");
    printf("|                                           |\n");
    printf("|                                           |\n");
    printf("=============================================\n\n");
    printf("Informe o nome do cliente:\n ");
    scanf("%s", nome);

    printf("Informe o CPF do cliente (Somente numeros):\n ");
    scanf("%s", cpf);
    getchar();
    while (!validar_cpf(cpf))
    {
        printf("CPF invalido. Informe novamente (somente numeros):\n ");
        scanf("%s", cpf);
        getchar();
    }

    printf("Informe o RG do cliente:\n ");
    scanf("%s", rg);
    getchar();
    while (!validar_rg(rg))
    {
        printf("RG invalido. Informe novamente (XXXXXX):\n ");
        scanf("%s", rg);
        getchar();
    }

    printf("Informe o telefone do cliente:\n ");
    scanf("%s", telefone);
    getchar();

    printf("Informe Cidade - Estado do cliente: (Ex: Picos-PI) ");
    scanf("%s", cidade_estado);
    getchar();

    printf("Informe o email do cliente: ");
    scanf("%s", email);
    while (!validar_email(email))
    {
        printf("Email invalido. Informe novamente: ");
        scanf("%s", email);
        getchar();
    }
    getchar();

    FILE *arquivo = fopen("db/clientes.txt", "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, cidade_estado, email);

    fclose(arquivo);
    printf("Cliente cadastrado com sucesso!\n");
    system("Pause");
}

int consultar_cliente()
{
    FILE *arquivo;
    char nome[50], consulta_nome[50], email[50], consulta_email[50], consulta_endereco[100];
    char cpf[50], consulta_cpf[50], rg[50], consulta_rg[50], telefone[50], consulta_telefone[50], endereco[100];
    int opcao_menu_consultar_clientes;
    int encontrado = 0;

    while (1)
    {
        system("clear || cls");
        printf("=============================================\n");
        printf("|             Consultar Clientes            |\n");
        printf("|                                           |\n");
        printf("|            __   __  __   __   __          |\n");
        printf("|           |  | |  ||  | |  | |  |         |\n");
        printf("|           |__| |__||__| |__| |__|         |\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("=============================================\n\n");
        arquivo = fopen("db/clientes.txt", "r");

        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo para leitura.\n");
            system("pause");
            return 1;
        }

        system("clear || cls");
        printf("  =============================================\n");
        printf("  |  Buscar Por:                              |\n");
        printf("  |                              __   __      |\n");
        printf("  |  1 - Nome                   |  | |  |     |\n");
        printf("  |  2 - CPF                    |__| |__|     |\n");
        printf("  |  3 - RG                      __   __      |\n");
        printf("  |  4 - Telefone               |  | |  |     |\n");
        printf("  |  5 - Endereco               |__| |__|     |\n");
        printf("  |  6 - Email                                |\n");
        printf("  |  7 - Voltar                               |\n");
        printf("  |                                           |\n");
        printf("  =============================================\n");
        printf("-> ");
        scanf("%d", &opcao_menu_consultar_clientes);

        fseek(arquivo, 0, SEEK_SET);

        switch (opcao_menu_consultar_clientes)
        {
        case 1:
            printf("Informe o Nome do cliente para pesquisar: ");
            scanf("%s", consulta_nome);

            while (fscanf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email) != EOF)
            {
                if (strcmp(consulta_nome, nome) == 0)
                {
                    printf("=============================================================================================================\n");
                    printf("|                                           INFORMACOES DO CLIENTE                                          |\n");
                    printf("=============================================================================================================\n");
                    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "Nome", "CPF", "RG", "Telefone", "Endereco", "Email");
                    printf("|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|\n");
                    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", nome, cpf, rg, telefone, endereco, email);
                    printf("=============================================================================================================\n");
                    system("pause");
                }
            }
            break;

        case 2:
            printf("Informe o CPF do cliente para pesquisar (somente numeros): ");
            scanf("%s", consulta_cpf);
            getchar();
            while (!validar_cpf(consulta_cpf))
            {
                printf("CPF invalido. Informe novamente (somente numeros): ");
                scanf("%s", consulta_cpf);
                getchar();
            }

            while (fscanf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email) != EOF)
            {
                if (strcmp(consulta_cpf, cpf) == 0)
                {
                    printf("=============================================================================================================\n");
                    printf("|                                           INFORMACOES DO CLIENTE                                          |\n");
                    printf("=============================================================================================================\n");
                    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "Nome", "CPF", "RG", "Telefone", "Endereco", "Email");
                    printf("|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|\n");
                    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", nome, cpf, rg, telefone, endereco, email);
                    printf("=============================================================================================================\n");
                    system("pause");
                }
            }
            break;

        case 3:
            printf("Informe o RG do cliente para pesquisar: ");
            scanf("%s", consulta_rg);
            getchar();
            while (!validar_rg(consulta_rg))
            {
                printf("RG invalido. Informe novamente (XXXXXXX): ");
                scanf("%s", consulta_rg);
                getchar();
            }

            while (fscanf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email) != EOF)
            {
                if (strcmp(consulta_rg, rg) == 0)
                {
                    printf("=============================================================================================================\n");
                    printf("|                                           INFORMACOES DO CLIENTE                                          |\n");
                    printf("=============================================================================================================\n");
                    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "Nome", "CPF", "RG", "Telefone", "Endereco", "Email");
                    printf("|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|\n");
                    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", nome, cpf, rg, telefone, endereco, email);
                    printf("=============================================================================================================\n");
                    system("pause");
                }

            }
            break;

        case 4:
            printf("Informe o Telefone do cliente para pesquisar: ");
            scanf("%s", consulta_telefone);
            getchar();
            while (fscanf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email) != EOF)
            {
                if (strcmp(consulta_telefone, telefone) == 0)
                {
                    printf("=============================================================================================================\n");
                    printf("|                                           INFORMACOES DO CLIENTE                                          |\n");
                    printf("=============================================================================================================\n");
                    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "Nome", "CPF", "RG", "Telefone", "Endereco", "Email");
                    printf("|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|\n");
                    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", nome, cpf, rg, telefone, endereco, email);
                    printf("=============================================================================================================\n");
                    system("pause");
                }

            }
            break;

        case 5:
            printf("Informe o Endereco do cliente para pesquisar: ");
            scanf("%s", consulta_endereco);
            getchar();
            while (fscanf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email) != EOF)
            {
                if (strcmp(consulta_endereco, endereco) == 0)
                {
                    printf("=============================================================================================================\n");
                    printf("|                                           INFORMACOES DO CLIENTE                                          |\n");
                    printf("=============================================================================================================\n");
                    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "Nome", "CPF", "RG", "Telefone", "Endereco", "Email");
                    printf("|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|\n");
                    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", nome, cpf, rg, telefone, endereco, email);
                    printf("=============================================================================================================\n");
                    system("pause");
                }

            }
            break;

        case 6:
            printf("Informe o Email do cliente para pesquisar: ");
            scanf("%s", consulta_email);
            getchar();
            while (!validar_email(consulta_email))
            {
                printf("Email invalido. Informe novamente: ");
                scanf("%s", consulta_email);
                getchar();
            }
            while (fscanf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email) != EOF)
            {
                if (strcmp(consulta_email, email) == 0)
                {
                    printf("=============================================================================================================\n");
                    printf("|                                           INFORMACOES DO CLIENTE                                          |\n");
                    printf("=============================================================================================================\n");
                    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "Nome", "CPF", "RG", "Telefone", "Endereco", "Email");
                    printf("|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|\n");
                    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", nome, cpf, rg, telefone, endereco, email);
                    printf("=============================================================================================================\n");
                    system("pause");
                }

            }
            break;

        case 7:
            fclose(arquivo);
            return encontrado;
            break;
        }
    }
}

void pausar()
{
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n')
        ;
    getchar();
}

void editar_clientes()
{
    system("clear || cls");
    printf("=============================================\n");
    printf("|               Edtar Clientes              |\n");
    printf("|                                           |\n");
    printf("|            __   __  __   __   __          |\n");
    printf("|           |  | |  ||  | |  | |  |         |\n");
    printf("|           |__| |__||__| |__| |__|         |\n");
    printf("|                                           |\n");
    printf("|                                           |\n");
    printf("=============================================\n\n");
    FILE *arquivo, *temporario;

    char nome[50], consulta_nome[50], email[50], consulta_email[50];
    char cpf[50], consulta_cpf[50], rg[50], consulta_rg[50], telefone[50], consulta_telefone[50], endereco[100];
    int menu_editar_clientes;

    arquivo = fopen("db/clientes.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        system("pause");
        return;
    }

    temporario = fopen("db/temporario.txt", "w");

    if (temporario == NULL)
    {
        printf("Erro ao criar o arquivo temporario.\n");
        fclose(arquivo);
        return;
    }

    printf("Informe o Nome do Cliente que deseja editar: ");
    scanf("%s", consulta_nome);

    int encontrado = 0;

    while (fscanf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email) != EOF)
    {
        if (strcmp(consulta_nome, nome) == 0)
        {

            system("clear || cls");
            printf("  =============================================\n");
            printf("  |  Editar:                                  |\n");
            printf("  |                              __   __      |\n");
            printf("  |  1 - Nome                   |  | |  |     |\n");
            printf("  |  2 - CPF                    |__| |__|     |\n");
            printf("  |  3 - RG                      __   __      |\n");
            printf("  |  4 - Telefone               |  | |  |     |\n");
            printf("  |  5 - Endereco               |__| |__|     |\n");
            printf("  |  6 - Email                                |\n");
            printf("  |  7 - Voltar                               |\n");
            printf("  |                                           |\n");
            printf("  =============================================\n");
            printf("-> ");
            scanf("%d", &menu_editar_clientes);

            switch (menu_editar_clientes)
            {
            case 1:
                printf("Informe o novo Nome do Cliente: ");
                scanf("%s", nome);
                break;
            case 2:
                printf("Informe o novo CPF do Cliente: ");
                scanf("%s", cpf);
                break;
            case 3:
                printf("Informe o novo RG do Cliente: ");
                scanf("%s", rg);
                break;
            case 4:
                printf("Informe o novo telefone do Cliente: ");
                scanf("%s", telefone);
                break;
            case 5:
                printf("Informe o novo endereco do Cliente: ");
                scanf("%s", endereco);
                break;
            case 6:
                printf("Informe o novo email do Cliente: ");
                scanf("%s", email);
                break;
            case 7:
            default:
                break;
            }
            encontrado = 1; // Cliente encontrado, atualiza a flag
        }
        fprintf(temporario, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email);
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrado)
    {
        printf("Cliente nao encontrado.\n");
        remove("db/temporario.txt");
        system("pause");
    }
    else
    {
        remove("db/clientes.txt");
        rename("db/temporario.txt", "db/clientes.txt");
        printf("Cliente editado com sucesso!\n");
        system("pause");
    }

    pausar();
}

void excluir_cliente()
{

    system("clear || cls");
    printf("=============================================\n");
    printf("|              Excluir Clientes             |\n");
    printf("|                                           |\n");
    printf("|            __   __  __   __   __          |\n");
    printf("|           |  | |  ||  | |  | |  |         |\n");
    printf("|           |__| |__||__| |__| |__|         |\n");
    printf("|                                           |\n");
    printf("|                                           |\n");
    printf("=============================================\n\n");
    FILE *arquivo, *temporario;

    char nome[50], cpf[50], rg[50], telefone[50], endereco[100], email[50];
    char consulta[50];

    int encontrado = 0;

    arquivo = fopen("db/clientes.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        system("pause");
        return;
    }

    temporario = fopen("db/temporario.txt", "w");

    if (temporario == NULL)
    {
        printf("Erro ao criar o arquivo temporario.\n");
        fclose(arquivo);
        return;
    }

    printf("Informe o Nome, CPF, RG, Telefone, Endereco ou Email do Cliente que deseja excluir: ");
    scanf("%s", consulta);

    while (fscanf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email) != EOF)
    {
        if (strcmp(consulta, nome) == 0 ||
            strcmp(consulta, cpf) == 0 ||
            strcmp(consulta, rg) == 0 ||
            strcmp(consulta, telefone) == 0 ||
            strcmp(consulta, endereco) == 0 ||
            strcmp(consulta, email) == 0)
        {

            printf("=============================================================================================================\n");
            printf("|                                           INFORMACOES DO CLIENTE                                          |\n");
            printf("=============================================================================================================\n");
            printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "Nome", "CPF", "RG", "Telefone", "Endereco", "Email");
            printf("|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|\n");
            printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", nome, cpf, rg, telefone, endereco, email);
            printf("=============================================================================================================\n");
            printf("Deseja realmente excluir o cliente? (1 - Sim / 2 - Nao): ");
            int opcao_menu_busca_clientes;
            scanf("%d", &opcao_menu_busca_clientes);
            while (getchar() != '\n')
                ;

            if (opcao_menu_busca_clientes == 1)
            {
                encontrado = 1;
            }
        }
        else
        {
            fprintf(temporario, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email);
        }
    }

    fclose(arquivo);
    fclose(temporario);

    if (encontrado)
    {
        remove("db/clientes.txt");
        rename("db/temporario.txt", "db/clientes.txt");
        printf("\nCliente excluído com sucesso!\n");
    }
    else
    {
        remove("db/temporario.txt");
        printf("\nCliente nao encontrado.\n");
    }
}

void clientes()
{
    int opcao_menu_cliente, resultado_consulta;

    system("clear || cls");
    printf("  =============================================\n");
    printf("  |  Escolha uma operacao:                    |\n");
    printf("  |                              __   __      |\n");
    printf("  |  1 - Cadastrar Cliente      |  | |  |     |\n");
    printf("  |  2 - Consultar Cliente      |__| |__|     |\n");
    printf("  |  3 - Editar Cliente          __   __      |\n");
    printf("  |  4 - Excluir Cliente        |  | |  |     |\n");
    printf("  |  5 - Voltar                 |__| |__|     |\n");
    printf("  |                                           |\n");
    printf("  =============================================\n");
    printf("-> ");
    scanf("%d", &opcao_menu_cliente);
    switch (opcao_menu_cliente)
    {
    case 1:
        cadastrar_cliente();
        break;
    case 2:
        resultado_consulta = consultar_cliente();
        if (resultado_consulta == 0)
        {
            system("pause");
        }
        else if (resultado_consulta == 1)
        {
            system("pause");
        }
        break;

    case 3:
        editar_clientes();
        break;

    case 4:
        excluir_cliente();
        system("pause");
        break;

    case 5:
        printf("Sair.");
        return;
        break;
    }
}