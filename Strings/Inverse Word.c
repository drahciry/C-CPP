// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    char word[64], inverse[64];
    int len = -1, i, j;

    printf("\n---------- Inversão de Palavra ----------\n\n");
    // Captura da palavra para inverter
    printf("Insira a palavra que deseja inverter: ");
    scanf("%s", word);
    while (getchar() != '\n');
    // Realiza inversão
    for (i = 0; word[i] != '\0'; i++, len++);
    for (j = 0; j < len; j++, i--) inverse[j] = word[i];
    inverse[j] = '\0';

    // Exibição da palavra invertida
    printf("\nPalavra invertida: %s\n\n", inverse);
    return 0;
}