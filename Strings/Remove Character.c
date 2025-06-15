// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    char ch, phrase[256], new_phrase[256];
    int i, j = 0;

    printf("\n---------- Remoção de Caracter ----------\n\n");
    // Captura frase que deseja remover caracter
    printf("Insira uma frase: ");
    fgets(phrase, sizeof(phrase), stdin);
    printf("\n");
    // Captura caracter que deseja remover
    printf("Insira o caractere que deseja remover: ");
    scanf("%c", &ch);
    while (getchar() != '\n');
    // Faz a remoção do caracter 
    for (i = 0; phrase[i] != '\n'; i++) {
        if (phrase[i] != ch) { 
            new_phrase[j++] = phrase[i];
        }
    }
    // new_phrase[i] = '\0';
    // Exibe nova frase sem o caracter
    printf(
        "\nResultado da remoção:\n"
        "%s\n\n", new_phrase
    );
    return 0;
}