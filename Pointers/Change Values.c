// Includes
#include <stdio.h>

// Função para trocar valor de variáveis
void changeValues(int* a, int* b) {
    // Declaração de variáveis
    int temp;

    // Realiza a troca dos valores
    temp = *a;
    *a = *b;
    *b = temp;
}

// Função principal (main)
int main() {
    // Declaração de variáveis
    int a, b;

    printf("\n---------- Troca por Referêcia ----------\n\n");
    // Captura os dois valores para troca
    printf("Insira os valores dois valores: ");
    scanf("%d %d", &a, &b);
    while(getchar() != '\n');
    // Realiza troca
    changeValues(&a, &b);
    // Exibe valores trocados
    printf(
        "\nValor 1: %d"
        "\nValor 2: %d\n\n",
        a, b
    );
    return 0;
}