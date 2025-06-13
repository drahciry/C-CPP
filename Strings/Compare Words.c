// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    char word_1[64], word_2[64];
    int equal = 1;

    printf("\n---------- Comparação de Palavras ----------\n\n");
    // Captura das palavras para comparação
    printf("Insira a primeira palavra: ");
    scanf("%s", word_1);
    while (getchar() != '\n');
    printf("Insira a segunda palavra: ");
    scanf("%s", word_2);
    while (getchar() != '\n');
    // Comparação das duas palavras
    for (int i = 0; word_1[i] != '\0' || word_2[i] != '\0'; i++) {
        if (word_1[i] != word_2[i]) {
            equal = 0;
            break;
        }
    }
    // Exibição da comparação
    printf("\nAs palavras inseridas %s.\n\n", equal ? "são iguais" : "não são iguais");
    return 0;
}