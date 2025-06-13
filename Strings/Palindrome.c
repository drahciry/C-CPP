// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    char word[64];
    int i, j, isPalindrome = 1, len = -1;

    printf("\n---------- Verificação de Palíndromo ----------\n\n");
    // Captura da palavra para verificar se é palíndromo
    printf("Insira uma palavra: ");
    scanf("%s", word);
    while (getchar() != '\n');
    // Realiza comparação entre início e fim
    for (i = 0; word[i] != '\0'; i++, len++);
    for (j = 0; j <= len; j++, len--) {
        if (word[j] != word[len]) {
            isPalindrome = 0;
            break;
        }
    }
    // Exibe resultado da compação
    printf("\nA palavra inserida %s.\n\n", isPalindrome ? "é palíndroma" : "não é palíndroma");
    return 0;
}