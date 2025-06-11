// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    float a, b, result;
    char option;

    printf("\n---------- Calculatora CLI ----------\n\n");
    // Captura os dois valores a serem utilizados na conta
    printf("Insira o primeiro valor da operação: ");
    scanf("%f", &a);
    getchar();
    printf("Insira o segundo valor da operação: ");
    scanf("%f", &b);
    getchar();
    // Menu "interativo" para escolher a operação a ser realizada
    printf(
        "\nOperações disponíveis:\n"
        "[+] Soma\n"
        "[-] Subtração\n"
        "[*] Multiplicação\n"
        "[/] Divisão\n\n"
        "Insira a operação desejada: "
    );
    scanf("%c", &option);
    getchar();
    printf("\n");
    // Verifica qual operação foi inserida
    switch (option) {
        // Soma
        case '+':
            result = a + b;
            break;
        // Subtração
        case '-':
            result = a - b;
            break;
        // Multiplicação
        case '*':
            result = a * b;
            break;
        // Divisão
        case '/':
            // Encerra programa com erro caso o segundo valor seja 0 na divisão
            if (!b) {
                printf("Não é possível realizar divisão por 0. Calculadora encerrada.\n\n");
                return 1;
            }
            result = a / b;
            break;
        // Operadores inválidos (retorna erro)
        default:
            printf("Operação inserida inválida. Calculadora encerrada.\n\n");
            return 2;
    }
    // Exibição do resultado
    printf(
        "Resultado da operação:\n"
        "%.5f %c %.5f = %.5f\n\n", a, option, b, result
    );
    return 0;
}