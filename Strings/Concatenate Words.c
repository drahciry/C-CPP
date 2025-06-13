// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    char word_1[64], word_2[64], concatenate[128];
    int len = 0;

    printf("\n---------- Concatenação de Palavras ----------\n\n");
    // Captura das palavras para concatenação
    printf("Insira a primeira palavra: ");
    scanf("%s", word_1);
    while (getchar() != '\n');
    printf("Insira a segunda palavra: ");
    scanf("%s", word_2);
    while (getchar() != '\n');
    // Concatenação das palavras
    for (int i = 0; word_1[i] != '\0'; i++, len++) concatenate[len] = word_1[i];
    for (int i = 0; word_2[i] != '\0'; i++, len++) concatenate[len] = word_2[i];
    concatenate[len] = '\0';
    // Exibição da concatenação
    printf("\nPalavras concatenadas: %s\n\n", concatenate);
    return 0;
}