// #include <stdio.h>
// #include <stdlib.h>

void cadastrar_cliente() {
    char nome[50], email[50], cidade_estado[100];
    int cpf, rg, telefone;

    system("clear || cls");
    printf("\n=============================================\n");
    printf("Cadastro de clientes:\n");
    printf("=============================================\n");

    printf("Informe o nome do cliente:\n ");
    scanf("%s", nome);

    printf("Informe o CPF do cliente:\n ");
    scanf("%d", &cpf);

    printf("Informe o RG do cliente:\n ");
    scanf("%d", &rg);

    printf("Informe o telefone do cliente:\n ");
    scanf("%d", &telefone);

<<<<<<< HEAD
    printf("Informe o email do cliente:\n ");
=======
    printf("Informe Cidade - Estado do cliente: (Ex: Picos-PI) ");
    scanf("%s", cidade_estado);

    printf("Informe o email do cliente: ");
>>>>>>> 180ab82f7f40f000697df201be9ef86264904bb2
    scanf("%s", email);

    // Abrir o arquivo para escrita em modo de adição (append)
    FILE *arquivo = fopen("db/clientes.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escrever as informações no arquivo
    fprintf(arquivo, "%s %d %d %d %s %s\n", nome, cpf, rg, telefone, cidade_estado, email);

    // Fechar o arquivo
    fclose(arquivo);
    printf("Cliente hóspede cadastrado com sucesso!\n");
    system("Pause");
} 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int consultar_cliente() {
    FILE *arquivo;
    char nome[50], consulta_nome[50], email[50], consulta_email[50];
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

                while (fscanf(arquivo, "%s %d %d %d %s\n", nome, &cpf, &rg, &telefone, email) != EOF) {
                    if (strcmp(consulta_nome, nome) == 0) {
                        printf("Cliente cadastrado!\n");
                        printf("CPF: %d\n", cpf);
                        printf("RG: %d\n", rg);
                        printf("Telefone: %d\n", telefone);
                        printf("Email: %s\n", email);
                        encontrado = 1;
                        break;
                    }
                }
                break;

            case 2:
                printf("Informe o CPF do cliente para pesquisar: ");
                scanf("%d", &consulta_cpf);

                while (fscanf(arquivo, "%s %d %d %d %s\n", nome, &cpf, &rg, &telefone, email) != EOF) {
                    if (consulta_cpf == cpf) {
                        printf("Cliente cadastrado!\n");
                        printf("Nome: %s\n", nome);
                        printf("RG: %d\n", rg);
                        printf("Telefone: %d\n", telefone);
                        printf("Email: %s\n", email);
                        encontrado = 1;
                        break;
                    }
                }
                break;

            case 3:
                printf("Informe o RG do cliente para pesquisar: ");
                scanf("%d", &consulta_rg);

                while (fscanf(arquivo, "%s %d %d %d %s\n", nome, &cpf, &rg, &telefone, email) != EOF) {
                    if (consulta_rg == rg) {
                        printf("Cliente cadastrado!\n");
                        printf("Nome: %s\n", nome);
                        printf("CPF: %d\n", cpf);
                        printf("Telefone: %d\n", telefone);
                        printf("Email: %s\n", email);
                        encontrado = 1;
                        break;
                    }
                }
                break;

            case 4:
                printf("Informe o Telefone do cliente para pesquisar: ");
                scanf("%d", &consulta_telefone);

                while (fscanf(arquivo, "%s %d %d %d %s\n", nome, &cpf, &rg, &telefone, email) != EOF) {
                    if (consulta_telefone == telefone) {
                        printf("Cliente cadastrado!\n");
                        printf("Nome: %s\n", nome);
                        printf("CPF: %d\n", cpf);
                        printf("RG: %d\n", rg);
                        printf("Email: %s\n", email);
                        encontrado = 1;
                        break;
                    }
                }
                break;

            case 5:
                printf("Informe o Email do cliente para pesquisar: ");
                scanf("%s", consulta_email);

                while (fscanf(arquivo, "%s %d %d %d %s\n", nome, &cpf, &rg, &telefone, email) != EOF) {
                    if (strcmp(consulta_email, email) == 0) {
                        printf("Cliente cadastrado!\n");
                        printf("Nome: %s\n", nome);
                        printf("CPF: %d\n", cpf);
                        printf("RG: %d\n", rg);
                        printf("Telefone: %d\n", telefone);
                        encontrado = 1;
                        break;
                    }
                }
                break;    
            
                if (encontrado == 0) {
                      printf("Cliente não cadastrado/encontrado!\n");
                } else if (encontrado == 1) {
                printf("Cliente cadastrado ou encontrado!\n");
                }
                fclose(arquivo);
                return encontrado;
        }
    }
}

<<<<<<< HEAD
=======
void clientes()
{
    int opcao_menu_cliente;
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
        consultar_cliente();
        break;
        
    default:
        break;
    }
}  
>>>>>>> 180ab82f7f40f000697df201be9ef86264904bb2
