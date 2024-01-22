#include "functor.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>


void cadastrarQuarto() {
    int numero;
    float valor;
    char tipo[20], status[20];

    system("clear || cls");
    printf("\n=============================================\n");
    printf("Cadastro de quartos:\n");
    printf("=============================================\n");

    srand(time(NULL));
    int id = rand() % 1000;

    printf("Informe o numero do quarto: ");
    scanf("%d", &numero);

    printf("Informe o tipo do quarto: (simples, duplo ou suite) ");
    scanf("%s", tipo);

    printf("Informe o valor da diaria do quarto: ");
    scanf("%f", &valor);

    printf("Informe o status do quarto: (livre, ocupado ou reservado) ");
    scanf("%s", status);

    FILE *arquivo = fopen("db/quartos.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo, "%d %d %s %.2f %s\n", id, numero, tipo, valor, status);

    fclose(arquivo);

    printf("Quarto cadastrado com sucesso!\n");
    system("pause");
}

void buscar_quartos() {
    FILE *arquivo;
    int id, busca_id, numero, busca_numero;
    float valor, busca_valor;
    char tipo[20], busca_tipo[20], status[20], busca_status[20];
    int opcao_menu_busca_quartos;

    while (1) {
        system("clear || cls");
        printf("\n=============================================\n");
        printf("Buscar Quartos:\n");
        printf("=============================================\n");

        arquivo = fopen("db/quartos.txt", "r");

        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo para leitura.\n");
            return;
        }

        printf("Escolha uma opção de busca:\n1 - Buscar por numero\n2 - Buscar por tipo\n3 - Buscar por valor\n4 - Buscar por status\n5 - Voltar\n");
        scanf("%d", &opcao_menu_busca_quartos);

        fseek(arquivo, 0, SEEK_SET);

        switch (opcao_menu_busca_quartos) {
            case 1:
                printf("Informe o numero para pesquisar: ");
                scanf("%d", &busca_numero);

                while (fscanf(arquivo, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF) {
                    if (busca_numero == numero) {
                        printf("Quarto encontrado!\n");
                        printf("ID: %d\n", id);
                        printf("numero: %d\n", numero);
                        printf("Tipo: %s\n", tipo);
                        printf("Valor: %.2f\n", valor);
                        printf("Status: %s\n", status);
                        system("pause");
                        break;
                    }
                }
                break;

            case 2:
                printf("Informe o Tipo para pesquisar: ");
                scanf("%s", busca_tipo);

                while (fscanf(arquivo, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF) {
                    if (strcmp(busca_tipo, tipo) == 0) {
                        printf("Quarto encontrado!\n");
                        printf("ID: %d\n", id);
                        printf("numero: %d\n", numero);
                        printf("Tipo: %s\n", tipo);
                        printf("Valor: %.2f\n", valor);
                        printf("Status: %s\n", status);
                        system("pause");
                        break;
                    }
                }
                break;

            case 3:
                printf("Informe o Valor para pesquisar: ");
                scanf("%f", &busca_valor);

                while (fscanf(arquivo, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF) {
                    if (busca_valor == valor) {
                        printf("Quarto encontrado!\n");
                        printf("ID: %d\n", id);
                        printf("numero: %d\n", numero);
                        printf("Tipo: %s\n", tipo);
                        printf("Valor: %.2f\n", valor);
                        printf("Status: %s\n", status);
                        system("pause");
                        break;
                    }
                }
                break;

            case 4:
                printf("Informe o Status para pesquisar: ");
                scanf("%s", busca_status);

                while (fscanf(arquivo, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF) {
                    if (strcmp(busca_status, status) == 0) {
                        printf("Quarto encontrado!\n");
                        printf("ID: %d\n", id);
                        printf("numero: %d\n", numero);
                        printf("Tipo: %s\n", tipo);
                        printf("Valor: %.2f\n", valor);
                        printf("Status: %s\n", status);
                        system("pause");
                        break;
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

#include <stdio.h>
#include <stdlib.h>

void editar_quartos()
{
    system("clear || cls");
    printf("\n=============================================\n");
    printf("Editar Quartos:\n");
    printf("=============================================\n");

    FILE *arquivo, *temporario;

    int id, busca_id, numero;
    float valor;
    char tipo[20], status[20];
    int opcao_menu_busca_quartos;
    int menu_editar_quartos;

    // int contador_erros = 0;

    arquivo = fopen("db/quartos.txt", "r");

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

    printf("Informe o ID do quarto que deseja editar: ");
    scanf("%d", &busca_id);

    while (fscanf(arquivo, "%d %d %s %f %s\n", &id, &numero, tipo, &valor, status) != EOF) {
        if (busca_id == id) {
            printf("Quarto encontrado!\n");
            printf("Informe o que deseja editar:\n1 - Numero\n2 - Tipo\n3 - Valor\n4 - Status\n5 - Quantidade de Quartos\n6 - Voltar\n");
            scanf("%d", &menu_editar_quartos);

            switch (menu_editar_quartos) {
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
        else {
            fprintf(temporario, "%d %d %s %.2f %s\n", id, numero, tipo, valor, status);
        }
    }

    fclose(arquivo);
    fclose(temporario);

    remove("db/quartos.txt");
    rename("db/temporario.txt", "db/quartos.txt");

    system("pause");
}

void excluir_quarto() {
    system("clear || cls");
    printf("\n=============================================\n");
    printf("Excluir Quarto:\n");
    printf("=============================================\n");

    FILE *arquivo, *temporario;

    int id, busca_id;
    int encontrado = 0;

    arquivo = fopen("db/quartos.txt", "r");

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

    printf("Informe o ID do quarto que deseja excluir: ");
    scanf("%d", &busca_id);

    while (fscanf(arquivo, "%d", &id) != EOF) {
        if (busca_id == id) {
            printf("Quarto encontrado!\n");
            printf("Deseja realmente excluir o quarto? (1 - Sim / 2 - Não): ");
            int opcao_menu_busca_quartos;
            scanf("%d", &opcao_menu_busca_quartos);

            if (opcao_menu_busca_quartos == 1) {
                encontrado = 1;
                while (fgetc(arquivo) != '\n'); 
            } else {
                fprintf(temporario, "%d\n", id);
                char buffer[100];
                while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
                    fprintf(temporario, "%s", buffer);
                }
            }
        } else {
            fprintf(temporario, "%d\n", id);
            char buffer[100];
            while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
                fprintf(temporario, "%s", buffer);
            }
        }
    }

    fclose(arquivo);
    fclose(temporario);

    if (encontrado) {
        remove("db/quartos.txt");
        rename("db/temporario.txt", "db/quartos.txt");
        printf("Quarto excluído com sucesso!\n");
    } else {
        remove("db/temporario.txt");
        printf("Quarto não encontrado.\n");
    }

    system("pause");
}

void quantidade_quartos()
{
    system("clear || cls");
    printf("\n=============================================\n");
    printf("Quantidade de Quartos:\n");
    printf("=============================================\n");


    FILE *qtd_arquivo;
    int nova_quantidade, quantidade_atual, opcao_quantidade;
    
    qtd_arquivo = fopen("db/quantidade_quartos.txt", "r");

    if (qtd_arquivo == NULL) {
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

        if (qtd_arquivo == NULL) {
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


void quartos() {
    while (1) {
        int opcao_menu_quartos;

        system("clear || cls");
        printf("\n=============================================\n");
        printf("Voce esta acessando o gerenciamento de quartos: ");
        printf("\n=============================================\n");

        printf("O que deseja fazer?\n1 - Cadastrar quarto\n2 - Consultar quarto\n3 - Editar quarto\n4 - Excluir quarto\n5 - Quantidade de Quartos\n6 - Voltar\n");
        scanf("%d", &opcao_menu_quartos);

        switch (opcao_menu_quartos) {
            case 1:
                printf("Cadastrar quarto\n");
                cadastrarQuarto();
                break;
                
            case 2:
                printf("Consultar quarto\n");
                buscar_quartos();
                break;
            case 3:
                printf("Editar quarto\n");
                editar_quartos();    
                break;
            case 4:
                printf("Excluir quarto\n");
                excluir_quarto();
                break;
            case 5:
                printf("Quantidade de quartos\n");
                quantidade_quartos();
                break; 
            case 6:
                return;
                break;
        }
    }
}
