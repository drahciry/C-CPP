// Includes
#include <stdio.h>
#include <stdlib.h>

// Função que lê entrada dinamicamente do teclado
char* readline() {
    // Declaração de variáveis
    int ch, len = 0, cap = 10;
    char* line = malloc(cap);
    // Verifica se alocação foi bem sucedida
    if (!line) {
        fprintf(stderr, "Erro: falha ao alocar memória!\n\n");
        exit(1);
    }
    // Leitura caractere por caractere
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // Se estiver cheio, realoca memória
        if (len >= cap - 2) {
            cap *= 2;
            line = realloc(line, cap);
            if (!line) {
                fprintf(stderr, "Erro: falha ao realocar memória!\n\n");
                exit(2);
            }
        }
        // Adiciona o caractere ao ponteiro
        line[len++] = ch;
    }
    // Adiciona o '\0' para término da string
    line[len] = '\0';
    // Retorna a leitura;
    return line;
}

// Função principal (main)
int main() {
    // Declaração de variáveis
    char* book;

    printf("\n---------- Leitura de Nome de Livro ----------\n\n");
    // Captura o nome do livro sem saber o tamanho de forma dinâmica
    printf("Insira o nome do livro: ");
    book = readline();
    printf("\n");
    // Exibe o nome do livro capturado
    printf("Nome do livro: %s\n\n", book);
    // Libera espaço na memória
    free(book);
    return 0;
}