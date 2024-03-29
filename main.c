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
#include "scripts/checkout.c"

int main(void)
{
    int opcao_menu1, opcao_menu_hotel, opcao_menu_cliente;

    while (1)
    {
        system("clear || cls");
        printf("                       =====                      \n");
        printf("               ====================               \n");
        printf("          =============================           \n");
        printf("      =====================================       \n");
        printf("==================================================\n");
        printf("  |                                            |  \n");
        printf("  |     SEJA BEM-VINDO AO SISTEMA DO HOTEL     |  \n");
        printf("  |                                            |  \n");
        printf("  |          H O T E L   C O R T E Z           |  \n");
        printf("  |                                            |  \n");
        printf("  |            __   __   __   __   __          |  \n");
        printf("  |           |  | |  | |  | |  | |  |         |  \n");
        printf("  |           |__| |__| |__| |__| |__|         |  \n");
        printf("  |            __   __   __   __   __          |  \n");
        printf("  |           |  | |  | |  | |  | |  |         |  \n");
        printf("  |           |__| |__| |__| |__| |__|         |  \n");
        printf("  |                                            |  \n");
        printf("  ==============================================\n\n");

        printf("  =============================================\n");
        printf("  |  Escolha uma operacao:                    |\n");
        printf("  |                              __   __      |\n");
        printf("  |  1 - Gerenciar Hotel        |  | |  |     |\n");
        printf("  |  2 - Gerenciar Clientes     |__| |__|     |\n");
        printf("  |  3 - Realizar Reserva        __   __      |\n");
        printf("  |  4 - Realizar Check-in      |  | |  |     |\n");
        printf("  |  5 - Realizar Check-Out     |__| |__|     |\n");
        printf("  |  6 - Sair                                 |\n");
        printf("  |                                           |\n");
        printf("  =============================================\n");
        printf("-> ");
        scanf("%d", &opcao_menu1);

        switch (opcao_menu1)
        {
        case 1:
            system("clear || cls");
            printf("=============================================\n");
            printf("|  Seja bem-vindo ao gerenciamento do Hotel  |\n");
            printf("|  Escolha a opcao desejada:                 |\n");
            printf("|                                __   __     |\n");
            printf("|                               |  | |  |    |\n");
            printf("|  1 - Gerenciar Quartos        |__| |__|    |\n");
            printf("|  2 - Gerenciar Financas        __   __     |\n");
            printf("|  3 - Voltar                   |  | |  |    |\n");
            printf("|                               |__| |__|    |\n");
            printf("=============================================\n");
            printf("-> ");
            scanf("%d", &opcao_menu_hotel);
            switch (opcao_menu_hotel)
            {
            case 1:
                quartos();
                break;
            case 2:
                gerenciar_financas();
                break;
            case 3:
                printf("=============================================\n");
                printf("|        Voltando ao menu principal...      |\n");
                printf("=============================================\n");
                break;
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
            checkout();
            break;
        case 6:
            printf("=============================================\n");
            printf("|          Encerrando Aplicacao...          |\n");
            printf("=============================================\n");
            exit(0);
            break;
        }
    }
    return 0;
}