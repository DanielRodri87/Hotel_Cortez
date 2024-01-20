#include "functor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    printf("Informe o valor do quarto: ");
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
