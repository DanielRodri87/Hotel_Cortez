
void checkin() {
    int opcao;
    char cpf[12], numero_quarto[4], data_entrada[11], data_saida[11], valor[10], dias[3];

    FILE *datasArquivo;  // Declaração única para datasArquivo

    while (1) {
        system("clear || cls");
        printf("\n=============================================\n");
        printf("Login dos Clientes:\n");
        printf("=============================================\n");

        printf("1 - Fazer Check-in\n");
        printf("2 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o CPF do cliente: ");
                scanf("%s", cpf);

                printf("Digite o numero do quarto: ");
                scanf("%s", numero_quarto);

                datasArquivo = fopen("datas.txt", "r"); 

                int encontrado = 0;

                while (fscanf(datasArquivo, "%*d %*s %s %*s %*s %*s", numero_quarto) == 1) {
                    if (strcmp(numero_quarto, numero_quarto) == 0) {
                        encontrado = 1;
                        break;
                    }
                }

                system("pause");
                fclose(datasArquivo);

                if (!encontrado) {
                    printf("Quarto não encontrado em datas.txt. Verifique o número do quarto.\n");
                    continue;
                }

                datasArquivo = fopen("datas.txt", "r");  // Apenas atribuição, sem redefinição
                FILE *tempArquivo = fopen("temp.txt", "w");

                while (fscanf(datasArquivo, "%*d %*s %s %s %s %s", numero_quarto, data_entrada, data_saida, dias) == 4) {
                    if (strcmp(numero_quarto, numero_quarto) == 0) {
                        printf("Quarto encontrado!\n");
                        printf("Data de entrada atual: %s\n", data_entrada);
                        printf("Data de saída atual: %s\n", data_saida);

                        printf("Deseja alterar as datas de entrada e saída? (1 - Sim, 0 - Não): ");
                        int escolha;
                        scanf("%d", &escolha);

                        if (escolha == 1) {
                            printf("Digite a nova data de entrada (formato: DD/MM/AAAA): ");
                            scanf("%s", data_entrada);

                            printf("Digite a nova data de saída (formato: DD/MM/AAAA): ");
                            scanf("%s", data_saida);
                        }
                    }

                    fprintf(tempArquivo, "%s %s %s %s\n", numero_quarto, data_entrada, data_saida, dias);
                }

                fclose(datasArquivo);
                fclose(tempArquivo);

                remove("datas.txt");
                rename("temp.txt", "datas.txt");

                FILE *quartosArquivo = fopen("quartos.txt", "r");
                float valor_diaria;

                while (fscanf(quartosArquivo, "%*d %s %*s %f %*s", numero_quarto, &valor_diaria) == 2) {
                    if (strcmp(numero_quarto, numero_quarto) == 0) {
                        printf("Valor da diária: %.2f\n", valor_diaria);

                        int num_dias = atoi(dias);
                        float valor_total = num_dias * valor_diaria;
                        printf("Valor total da estadia: %.2f\n", valor_total);

                        FILE *checkinArquivo = fopen("checkin.txt", "a");
                        fprintf(checkinArquivo, "%s %s %s %s %.2f\n", cpf, numero_quarto, data_entrada, data_saida, valor_total);
                        fclose(checkinArquivo);

                        break;
                    }
                }

                fclose(quartosArquivo);
                break;

            case 2:
                return;
        }
    }
}
