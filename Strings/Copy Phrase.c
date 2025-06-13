// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    char phrase[256], copy[256];
    int len = 0;

    printf("\n---------- Copiador de String ----------\n\n");
    // Captura string para cópia
    printf("Insira a frase a ser copiada: ");
    fgets(phrase, sizeof(phrase), stdin);
    while (getchar() != '\n');
    // Realiza a cópia das strings
    for (; phrase[len] != '\n'; len++) copy[len] = phrase[len];
    phrase[len] = '\0';
    copy[len] = '\0';
    // Exibe cópia da string
    printf("\nFrase copiada: %s\n\n", copy);
    return 0;
}