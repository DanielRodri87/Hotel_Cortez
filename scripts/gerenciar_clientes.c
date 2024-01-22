// #include <stdio.h>
// #include <stdlib.h>

void cadastrar_cliente() {
    char nome[50], email[50], cidade_estado[100];
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

    printf("Informe Cidade - Estado do cliente: (Ex: Picos-PI) ");
    scanf("%s", cidade_estado);

    printf("Informe o email do cliente: ");
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

void consultar_cliente() {
   
}

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