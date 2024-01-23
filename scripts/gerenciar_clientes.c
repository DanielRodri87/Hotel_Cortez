// #include <stdio.h>
// #include <stdlib.h>

#include <stdio.h>
#include <string.h>

void cadastrar_cliente() {
    char nome[50], email[50], cidade_estado[100];
    long int cpf, rg, telefone;

    system("clear || cls");
    printf("\n=============================================\n");
    printf("Cadastro de clientes:\n");
    printf("=============================================\n");

    printf("Informe o nome do cliente:\n ");
    scanf("%s", nome);

    printf("Informe o CPF do cliente:\n ");
    scanf("%ld", &cpf);
    getchar(); // Limpar o caractere de nova linha do buffer

    printf("Informe o RG do cliente:\n ");
    scanf("%ld", &rg);
    getchar(); // Limpar o caractere de nova linha do buffer

    printf("Informe o telefone do cliente:\n ");
    scanf("%ld", &telefone);
    getchar(); // Limpar o caractere de nova linha do buffer

    printf("Informe Cidade - Estado do cliente: (Ex: Picos-PI) ");
    scanf("%s", cidade_estado);
    getchar;

    printf("Informe o email do cliente: ");
    scanf("%s", email);
    getchar();

    // Abrir o arquivo para escrita em modo de adição (append)
    FILE *arquivo = fopen("db/clientes.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escrever as informações no arquivo
    fprintf(arquivo, "%s %ld %ld %ld %s %s\n", nome, cpf, rg, telefone, cidade_estado, email);

    // Fechar o arquivo
    fclose(arquivo);
    printf("Cliente hóspede cadastrado com sucesso!\n");
    system("Pause");
}


int consultar_cliente() {
    FILE *arquivo;
    char nome[50], consulta_nome[50], email[50], consulta_email[50], cidade_estado[50], consulta_cidade[50];
    int cpf, consulta_cpf, rg, consulta_rg, telefone, consulta_telefone;
    int opcao_menu_consultar_clientes;
    int encontrado = 0;

    while (1) {
        system("clear || cls");
        printf("\n=============================================\n");
        printf("Consultar Clientes:\n");
        printf("=============================================\n");

        arquivo = fopen("db/clientes.txt", "r");

        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo para leitura.\n");
            return 1;
        }

        printf("Escolha uma opção de busca:\n1 - Buscar por nome\n2 - Buscar por CPF\n3 - Buscar por RG\n4 - Buscar por Telefone\n5 - Buscar por Email\n6 - Sair\n");
        scanf("%d", &opcao_menu_consultar_clientes);

        fseek(arquivo, 0, SEEK_SET);

        switch (opcao_menu_consultar_clientes) {
            case 1:
                printf("Informe o Nome do cliente para pesquisar: ");
                scanf("%s", consulta_nome);

                while (fscanf(arquivo, "%s %d %d %d %s %s\n", nome, &cpf, &rg, &telefone, cidade_estado,email) != EOF) {
                    if (strcmp(consulta_nome, nome) == 0) {
                        printf("Cliente cadastrado!\n");
                        printf("CPF: %d\n", cpf);
                        printf("RG: %d\n", rg);
                        printf("Telefone: %d\n", telefone);
                        printf("Email: %s\n", email);
                        encontrado = 1;
                        system("pause");
                        break;
                    }
                }
                break;

            case 2:
                printf("Informe o CPF do cliente para pesquisar: ");
                scanf("%d", &consulta_cpf);

                while (fscanf(arquivo, "%s %d %d %d %s\n", nome, &cpf, &rg, &telefone, cidade_estado, email) != EOF) {
                    if (consulta_cpf == cpf) {
                        printf("Cliente cadastrado!\n");
                        printf("Nome: %s\n", nome);
                        printf("RG: %d\n", rg);
                        printf("Telefone: %d\n", telefone);
                        printf("Email: %s\n", email);
                        encontrado = 1;
                        system("pause");
                        break;
                    }
                }
                break;

            case 3:
                printf("Informe o RG do cliente para pesquisar: ");
                scanf("%d", &consulta_rg);

                while (fscanf(arquivo, "%s %d %d %d %s\n", nome, &cpf, &rg, &telefone, cidade_estado, email) != EOF) {
                    if (consulta_rg == rg) {
                        printf("Cliente cadastrado!\n");
                        printf("Nome: %s\n", nome);
                        printf("CPF: %d\n", cpf);
                        printf("Telefone: %d\n", telefone);
                        printf("Email: %s\n", email);
                        encontrado = 1;
                        system("pause");
                        break;
                    }
                }
                break;

            case 4:
                printf("Informe o Telefone do cliente para pesquisar: ");
                scanf("%d", &consulta_telefone);

                while (fscanf(arquivo, "%s %d %d %d %s\n", nome, &cpf, &rg, &telefone, cidade_estado, email) != EOF) {
                    if (consulta_telefone == telefone) {
                        printf("Cliente cadastrado!\n");
                        printf("Nome: %s\n", nome);
                        printf("CPF: %d\n", cpf);
                        printf("RG: %d\n", rg);
                        printf("Email: %s\n", email);
                        encontrado = 1;
                        system("pause");
                        break;
                    }
                }
                break;

            case 5:
                printf("Informe a Cidade-Estado do cliente para pesquisar: ");
                scanf("%s", consulta_cidade);

                while (fscanf(arquivo, "%s %d %d %d %s %s\n", nome, &cpf, &rg, &telefone, cidade_estado,email) != EOF) {
                    if (strcmp(consulta_cidade, cidade_estado) == 0) {
                        printf("Cliente cadastrado!\n");
                        printf("Nome: ", nome);
                        printf("CPF: %d\n", cpf);
                        printf("RG: %d\n", rg);
                        printf("Telefone: %d\n", telefone);
                        printf("Email: %s\n", email);
                        encontrado = 1;
                        system("pause");
                        break;
                    }
                }
                break;

            case 6:
                printf("Informe o Email do cliente para pesquisar: ");
                scanf("%s", consulta_email);

                while (fscanf(arquivo, "%s %d %d %d %s\n", nome, &cpf, &rg, &telefone, cidade_estado, email) != EOF) {
                    if (strcmp(consulta_email, email) == 0) {
                        printf("Cliente cadastrado!\n");
                        printf("Nome: %s\n", nome);
                        printf("CPF: %d\n", cpf);
                        printf("RG: %d\n", rg);
                        printf("Telefone: %d\n", telefone);
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
        } else if (resultado_consulta == 1)
        {
            printf("Cliente encontrado!");
        }
        break;
        
    default:
        break;
    }
}  
