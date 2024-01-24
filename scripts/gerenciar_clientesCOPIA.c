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
    printf("\n=============================================\n");
    printf("Cadastro de clientes:\n");
    printf("=============================================\n");

    printf("Informe o nome do cliente:\n ");
    scanf("%s", nome);

    printf("Informe o CPF do cliente (XXX.XXX.XXX-XX):\n ");
    scanf("%s", cpf);
    getchar();
    while (!validar_cpf(cpf))
    {
        printf("CPF inválido. Informe novamente (XXX.XXX.XXX-XX):\n ");
        scanf("%s", cpf);
        getchar();
    }

    printf("Informe o RG do cliente:\n ");
    scanf("%s", rg);
    getchar();
    while (!validar_rg(rg))
    {
        printf("RG inválido. Informe novamente (XXXXXX):\n ");
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
        printf("Email inválido. Informe novamente: ");
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
    printf("Cliente hospede cadastrado com sucesso!\n");
    system("Pause");
}

int consultar_cliente()
{
    FILE *arquivo;
    char nome[50], consulta_nome[50], email[50], consulta_email[50];
    char cpf[50], consulta_cpf[50], rg[50], consulta_rg[50], telefone[50], consulta_telefone[50], endereco[100];
    int opcao_menu_consultar_clientes;
    int encontrado = 0;

    while (1)
    {
        system("clear || cls");
        printf("\n=============================================\n");
        printf("Consultar Clientes:\n");
        printf("=============================================\n");

        arquivo = fopen("db/clientes.txt", "r");

        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo para leitura.\n");
            return 1;
        }

        printf("Escolha uma opcao de busca:\n1 - Buscar por nome\n2 - Buscar por CPF\n3 - Buscar por RG\n4 - Buscar por Telefone\n5 - Buscar por Email\n6 - Sair\n");
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
                    printf("Cliente cadastrado!\n");
                    printf("CPF: %s\n", cpf);
                    printf("RG: %s\n", rg);
                    printf("Telefone: %s\n", telefone);
                    printf("Email: %s\n", email);
                    encontrado = 1;
                    system("pause");
                    break;
                }
            }
            break;

        case 2:
            printf("Informe o CPF do cliente para pesquisar (XXX.XXX.XXX-XX): ");
            scanf("%s", consulta_cpf);
            getchar();
            while (!validar_cpf(consulta_cpf))
            {
                printf("CPF inválido. Informe novamente (XXX.XXX.XXX-XX): ");
                scanf("%s", consulta_cpf);
                getchar();
            }

            while (fscanf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email) != EOF)
            {
                if (strcmp(consulta_cpf, cpf) == 0)
                {
                    printf("Cliente cadastrado!\n");
                    printf("Nome: %s\n", nome);
                    printf("RG: %s\n", rg);
                    printf("Telefone: %s\n", telefone);
                    printf("Email: %s\n", email);
                    encontrado = 1;
                    system("pause");
                    break;
                }
            }
            break;

        case 3:
            printf("Informe o RG do cliente para pesquisar (XXX.XXX): ");
            scanf("%s", consulta_rg);
            getchar();
            while (!validar_rg(consulta_rg))
            {
                printf("RG inválido. Informe novamente (XXX.XXX): ");
                scanf("%s", consulta_rg);
                getchar();
            }

            while (fscanf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email) != EOF)
            {
                if (strcmp(consulta_rg, rg) == 0)
                {
                    printf("Cliente cadastrado!\n");
                    printf("Nome: %s\n", nome);
                    printf("CPF: %s\n", cpf);
                    printf("Telefone: %s\n", telefone);
                    printf("Email: %s\n", email);
                    encontrado = 1;
                    system("pause");
                    break;
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
                    printf("Cliente cadastrado!\n");
                    printf("Nome: %s\n", nome);
                    printf("CPF: %s\n", cpf);
                    printf("RG: %s\n", rg);
                    printf("Email: %s\n", email);
                    encontrado = 1;
                    system("pause");
                    break;
                }
            }
            break;

        case 5:
            printf("Informe o Email do cliente para pesquisar: ");
            scanf("%s", consulta_email);
            getchar();
            while (!validar_email(consulta_email))
            {
                printf("Email inválido. Informe novamente: ");
                scanf("%s", consulta_email);
                getchar();
            }
            while (fscanf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email) != EOF)
            {
                if (strcmp(consulta_email, email) == 0)
                {
                    printf("Cliente cadastrado!\n");
                    printf("Nome: %s\n", nome);
                    printf("CPF: %s\n", cpf);
                    printf("RG: %s\n", rg);
                    printf("Telefone: %s\n", telefone);
                    encontrado = 1;
                    system("pause");
                    break;
                }
            }
            break;

        case 6:
            fclose(arquivo);
            return encontrado;
            break;
        }
    }
}


void pausar() {
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n');
    getchar();  // Capturar o Enter
}

void editar_clientes() {
    system("cls || clear");
    printf("\n=============================================\n");
    printf("Editar Clientes:\n");
    printf("=============================================\n");

    FILE *arquivo, *temporario;

    char nome[50], consulta_nome[50], email[50], consulta_email[50];
    char cpf[50], consulta_cpf[50], rg[50], consulta_rg[50], telefone[50], consulta_telefone[50], endereco[100];
    int menu_editar_clientes;

    arquivo = fopen("db/clientes.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    temporario = fopen("db/temporario.txt", "w");

    if (temporario == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    printf("Informe o Nome do Cliente que deseja editar: ");
    scanf("%s", consulta_nome);

    int encontrado = 0;

    while (fscanf(arquivo, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email) != EOF) {
        if (strcmp(consulta_nome, nome) == 0) {
            printf("Cliente encontrado\n");
            printf("Informe o que deseja editar:\n1 - Nome\n2 - CPF\n3 - RG\n4 - Telefone\n5 - Email\n6 - Voltar\n");
            scanf("%d", &menu_editar_clientes);

            switch (menu_editar_clientes) {
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
                printf("Informe o novo email do Cliente: ");
                scanf("%s", email);
                break;
            case 6:
                encontrado = 1;  // Marcar como encontrado para evitar a escrita do registro original
                break;
            }
        }
        fprintf(temporario, "%s %s %s %s %s %s\n", nome, cpf, rg, telefone, endereco, email);
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrado) {
        printf("Cliente não encontrado.\n");
        remove("db/temporario.txt");
    } else {
        remove("db/clientes.txt");
        rename("db/temporario.txt", "db/clientes.txt");
        printf("Cliente editado com sucesso!\n");
    }

    pausar();
}

void clientes()
{
    int opcao_menu_cliente, resultado_consulta;
    printf("Gerenciar Clientes \n");
    printf("Digite a opcao que deseja escolher:\n1 - Cadastrar Cliente\n2 - Consultar Cliente\n3 - Editar Cliente\n4 - Excluir Cliente\n ");
    scanf("%d", &opcao_menu_cliente);
    switch (opcao_menu_cliente)
    {
    case 1:
        cadastrar_cliente();
        printf("Cliente hóspede cadastrado com sucesso!\n");
        break;
    case 2:
        resultado_consulta = consultar_cliente();
        if (resultado_consulta == 0)
        {
            printf("Cliente não encontrado!");
            system("pause");
        }
        else if (resultado_consulta == 1)
        {
            printf("Cliente encontrado!");
            system("pause");
        }
        break;

    case 3:
        printf("Editar clientes: ");
        editar_clientes();
        break;
    }
}