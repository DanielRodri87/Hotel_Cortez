#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "scripts/functor.h"
#include "scripts/gerenciar_quartos.c"
#include "scripts/gerenciar_financas.c"

int main(void) {
    int opcao_menu1, opcao_menu_hotel;

    while (1) {
        system("clear || cls");
        printf("\n=============================================\n");
        printf("SEJA BEM-VINDO AO SISTEMA DO HOTEL CORTEZ\n");
        printf("=============================================\n");

        printf("Informe qual operação você deseja usar: \n1 - Gerenciar Hotel\n2 - Gerenciar Clientes\n");
        scanf("%d", &opcao_menu1);

        switch (opcao_menu1) {
            case 1:
                system("clear || cls");
                printf("Seja bem-vindo ao gerenciamento do Hotel\nEscolha a opção desejada:\n1 - Gerenciar Quartos\n2 - Gerenciar Finanças\n");
                scanf("%d", &opcao_menu_hotel);   
                switch (opcao_menu_hotel) {
                    case 1:
                        quartos();
                        break;
                    
                    case 2: 
                        financas();
                        break;

                    default:
                        break;
                }
                break;
            case 2:
                printf("Gerenciar Clientes\n");
                break;
        }
    }

    return 0;
}
