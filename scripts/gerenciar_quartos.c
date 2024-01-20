#include "functor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

    printf("Informe o tipo do quarto: ");
    scanf("%s", tipo);

    printf("Informe o valor da diária do quarto: ");
    scanf("%f", &valor);

    printf("Informe o status do quarto: ");
    scanf("%s", status);

    // Abrir o arquivo para escrita em modo de adição (append)
    FILE *arquivo = fopen("db/quartos.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escrever as informações no arquivo
    fprintf(arquivo, "%d, %d, %s, %.2f, %s\n", id, numero, tipo, valor, status);

    // Fechar o arquivo
    fclose(arquivo);

    printf("Quarto cadastrado com sucesso!\n");
    system("pause");
}

void buscar_quartos() {
    int opcao_menu_busca_quartos;
    FILE *arquivo;
    int id, numero;
    float valor;
    char tipo[20], status[20];

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

        printf("Escolha uma opção de busca:\n1 - Buscar por número\n2 - Buscar por tipo\n3 - Buscar por valor\n4 - Buscar por status\n5 - Voltar\n");
        scanf("%d", &opcao_menu_busca_quartos);

        fseek(arquivo, 0, SEEK_SET);

        switch (opcao_menu_busca_quartos) {
            case 1:
                printf("Informe o Número para pesquisar: ");
                scanf("%d", &numero);

                while (fscanf(arquivo, "%d, %d, %s, %f, %s\n", &id, &numero, tipo, &valor, status) != EOF) {
                    if (numero == numero) {
                        printf("Quarto encontrado!\n");
                        printf("ID: %d\n", id);
                        printf("Número: %d\n", numero);
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
                scanf("%s", tipo);

                while (fscanf(arquivo, "%d, %d, %s, %f, %s\n", &id, &numero, tipo, &valor, status) != EOF) {
                    if (strcmp(tipo, tipo) == 0) {
                        printf("Quarto encontrado!\n");
                        printf("ID: %d\n", id);
                        printf("Número: %d\n", numero);
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
                scanf("%f", &valor);

                while (fscanf(arquivo, "%d, %d, %s, %f, %s\n", &id, &numero, tipo, &valor, status) != EOF) {
                    if (valor == valor) {
                        printf("Quarto encontrado!\n");
                        printf("ID: %d\n", id);
                        printf("Número: %d\n", numero);
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
                scanf("%s", status);

                while (fscanf(arquivo, "%d, %d, %s, %f, %s\n", &id, &numero, tipo, &valor, status) != EOF) {
                    if (strcmp(status, status) == 0) {
                        printf("Quarto encontrado!\n");
                        printf("ID: %d\n", id);
                        printf("Número: %d\n", numero);
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

void quartos() {
    while (1) {
        int opcao_menu_quartos;

        system("clear || cls");
        printf("\n=============================================\n");
        printf("Voce esta acessando o gerenciamento de quartos: ");
        printf("\n=============================================\n");

        printf("O que deseja fazer?\n1 - Cadastrar quarto\n2 - Consultar quarto\n3 - Editar quarto\n4 - Excluir quarto\n5 - Voltar\n");
        scanf("%d", &opcao_menu_quartos);

        switch (opcao_menu_quartos) {
            case 1:
                cadastrarQuarto();
                break;
                
            case 2:
                printf("Consultar quarto\n");
                buscar_quartos();
                break;
            case 3:
                printf("Editar quarto\n");
                break;
            case 4:
                printf("Excluir quarto\n");
                break;
            case 5:
                return;
                break;
        }
    }
}
