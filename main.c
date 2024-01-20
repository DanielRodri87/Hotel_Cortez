// main.c
#include <stdio.h>
#include "scripts/functor.h"
#include <stdlib.h>
#include <conio.h> 

int main(void) {
        int opcao_menu1, opcao_menu_hotel;

    while (1)
    {
        system("cls");
        printf("\n=============================================\n");
        printf("SEJA BEM-VINDO AO SISTEMA DO HOTEL CORTEZ\n");
        printf("=============================================\n");

        printf("Informe qual operação você deseja usar: \n1 - Gerenciar Hotel\n2 - Gerenciar Clientes");
        scanf("%d", &opcao_menu1);

        switch (opcao_menu1)
        {
        case 1:
            system("cls");
            printf("Seja bem-vindo ao gerenciamento do Hotel\nEscolhar a opção desejada: 1- Gerenciar Quartos\n 2 - Gerenciar Finanças ");
            scanf("%d", &opcao_menu_hotel);   
            switch (opcao_menu_hotel)
            {
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
            printf("Gerenciar Clientes");
            break;
        
    }
    return 0;

}
