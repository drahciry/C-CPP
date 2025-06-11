// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    int option;

    // Apenas lógica de switch-case
    printf("\n---------- Exibição de Switch-Case ----------\n\n");
    printf(
        "Opções válidas:\n"
        "[1] Opção 1\n"
        "[2] Opção 2\n"
        "[3] Opção 3\n"
        "[4] Opção 4\n"
        "[5] Opção 5\n\n"
        "Insira a opção desejada: "
    );
    scanf("%d", &option);
    getchar();
    printf("\n");
    switch (option) {
        case 1:
            printf("Você selecionou a opção 1.\n\n");
            break;
        case 2:
            printf("Você selecionou a opção 2.\n\n");
            break;
        case 3:
            printf("Você selecionou a opção 3.\n\n");
            break;
        case 4:
            printf("Você selecionou a opção 4.\n\n");
            break;
        case 5:
            printf("Você selecionou a opção 5.\n\n");
            break;
        default:
            printf("Opção inserida inválida. Programa encerrado.\n\n");
            return 1;
    }
    printf("Programa encerrado.\n\n");
    return 0;
}