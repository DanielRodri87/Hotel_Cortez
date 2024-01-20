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

    // Abrir o arquivo para escrita em modo de adição (append)
    FILE *arquivo = fopen("db/clientes.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escrever as informações no arquivo
    fprintf(arquivo, "%s, %d, %d, %d, %s\n", nome, cpf, rg, telefone, email);

    // Fechar o arquivo
    fclose(arquivo);
    printf("Cliente hóspede cadastrado com sucesso!");
    system("Pause");
} 

void consultar_cliente() {
   
}
  