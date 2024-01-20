#include <stdio.h>
#include <stdlib.h>

void cadastrar_cliente() {
    char nome[50], email[50];
    int cpf, rg, telefone;

    system("clear || cls");
    printf("\n=============================================\n");
    printf("Cadastro de clientes:\n");
    printf("=============================================\n");

    printf("Informe o nome do cliente: ");
    scanf("%s", nome);

    printf("Informe o CPF do cliente: ");
    scanf("%d", &cpf);

    printf("Informe o RG do cliente: ");
    scanf("%d", &rg);

    printf("Informe o telefone do cliente: ");
    scanf("%d", &telefone);

    printf("Informe o email do cliente: ");
    scanf("%s", email);

    system("Pause");
}