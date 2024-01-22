#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "scripts/functor.h"
#include "scripts/gerenciar_quartos.c"
#include "scripts/gerenciar_financas.c"
#include "scripts/gerenciar_clientes.c"

int main(void) {
    int opcao_menu1, opcao_menu_hotel, opcao_menu_cliente;
    int resultado_consulta;

    while (1) {
        system("clear || cls");
        printf("\n=============================================\n");
        printf("SEJA BEM-VINDO AO SISTEMA DO HOTEL CORTEZ\n");
        printf("=============================================\n");

        printf("Informe qual operacao voce deseja usar: \n1 - Gerenciar Hotel\n2 - Gerenciar Clientes\n3 - Sair\n");
        scanf("%d", &opcao_menu1);

        switch (opcao_menu1) {
            case 1:
                system("clear || cls");
                printf("Seja bem-vindo ao gerenciamento do Hotel\nEscolha a op desejada:\n1 - Gerenciar Quartos\n2 - Gerenciar Finanças\n3 - Voltar\n");
                scanf("%d", &opcao_menu_hotel);
                switch (opcao_menu_hotel) {
                    case 1:
                        quartos();
                        break;

                    case 2:
                        financas();
                        break;

                    case 3:
                        printf("Voltando ao menu principal...");
                    default:
                        break;
                }
                break;
            case 2:
                printf("Gerenciar Clientes \n");
                printf("Digite a opção que deseja escolher:\n1 - Cadastrar Cliente\n2 - Consultar Cliente\n3 - Editar Cliente\n4 - Excluir Cliente\n ");
                scanf("%d", &opcao_menu_cliente);
                switch (opcao_menu_cliente)
                {
                case 1:
                    cadastrar_cliente();
                    printf("Cliente hóspede cadastrado com sucesso!");
                    break;
                case 2:  
                    consultar_cliente();
                    break;
            case 3:
                printf("Saindo do sistema...");
                exit(0);
                break;
        }
    }

    return 0;
}