#include <stdio.h>
#include<stdlib.h>

void cadastrar_cliente(char nome[50], int cpf, int rg, int telefone, char email[20]){

    printf("Digite o nome do Cliente:\n ");
    scanf("%s", nome);
    printf("Digite o CPF do Cliente:\n ");
    scanf("%d", &cpf);
    printf("Digite o rg do Cliente:\n ");
    scanf("%d", &rg);
    printf("Digite o telefone do Cliente:\n ");
    scanf("%d", &telefone);
    printf("Digite o email do Cliente:\n ");
    scanf("%s", &email);
    
    system("Pause");
}