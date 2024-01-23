#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "scripts/functor.h"
#include "scripts/gerenciar_quartos.c"
#include "scripts/gerenciar_financas.c"
#include "scripts/gerenciar_clientes.c"
#include "scripts/login_clientes.c"
#include "scripts/checkin.c"

int main(void) {
    int opcao_menu1, opcao_menu_hotel, opcao_menu_cliente;

    while (1) {
        system("clear || cls");
        printf("\n=============================================\n");
        printf("SEJA BEM-VINDO AO SISTEMA DO HOTEL CORTEZ\n");
        printf("=============================================\n");

        printf("Informe qual operacao voce deseja usar: \n1 - Gerenciar Hotel\n2 - Gerenciar Clientes\n3 - Realizar Reserva\n4 - Realizar Check-in\n5 - Sair\n");
        scanf("%d", &opcao_menu1);

        switch (opcao_menu1) {
            case 1:
                system("clear || cls");
                printf("Seja bem-vindo ao gerenciamento do Hotel\nEscolha a op desejada:\n1 - Gerenciar Quartos\n2 - Gerenciar Financas\n3 - Voltar\n");
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
                clientes();
                break;
            case 3:
                login_clientes();
                break;
            
            case 4: 
                checkin();
                break;
            case 5:
                printf("Saindo do sistema...");
                exit(0);
                break;
        }
    }
    return 0;
}