// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    int min, max, arr[5];

    printf("\n---------- Máximo e Mínimo de um Array ----------\n\n");
    // Captura 5 elementos e armazena no array
    for (int i = 0; i < 5; i++) {
        printf("Insira o %dº elemento do array: ", i + 1);
        scanf("%d", &arr[i]);
        getchar();
        // O primeiro elemento é maior e menor elemento do array
        if (!i) {
            min = arr[i];
            max = arr[i];
        }
        // Realiza comparação 
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    // Exibe máximo e mínimo do array
    printf(
        "\nMaior valor inserido: %d\n"
        "Menor valor inserido: %d\n\n",
        max, min
    );
    return 0;
}