#include <stdio.h>
#include <stdlib.h>
#include "expressao.h"

int main() {
    char entrada[512];
    int opcao;
    printf("Avaliador de Expressoes Numericas\n");
    printf("1. Infixa para Pos-fixa\n");
    printf("2. Pos-fixa para Infixa\n");
    printf("3. Avaliar Pos-fixa\n");
    printf("4. Avaliar Infixa\n");
    printf("0. Sair\n");
    do {
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer
        switch(opcao) {
            case 1:
                printf("Digite a expressao infixa: ");
                fgets(entrada, 512, stdin);
                entrada[strcspn(entrada, "\n")] = 0;
                printf("Pos-fixa: %s\n", getFormaPosFixa(entrada));
                break;
            case 2:
                printf("Digite a expressao pos-fixa: ");
                fgets(entrada, 512, stdin);
                entrada[strcspn(entrada, "\n")] = 0;
                printf("Infixa: %s\n", getFormaInFixa(entrada));
                break;
            case 3:
                printf("Digite a expressao pos-fixa: ");
                fgets(entrada, 512, stdin);
                entrada[strcspn(entrada, "\n")] = 0;
                printf("Valor: %.2f\n", getValorPosFixa(entrada));
                break;
            case 4:
                printf("Digite a expressao infixa: ");
                fgets(entrada, 512, stdin);
                entrada[strcspn(entrada, "\n")] = 0;
                printf("Valor: %.2f\n", getValorInFixa(entrada));
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    return 0;
} 