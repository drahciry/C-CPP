// Includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    int* array;
    int len;

    printf("\n---------- Realloc Visual ----------\n\n");
    // Captura o tamanho do array para alocar na memória
    printf("Insira a quantidade de valores que serão registrados: ");
    scanf("%d", &len);
    printf("\n");
    // Aloca na memória
    array = malloc(len * sizeof(int));
    // Retorna erro caso não seja realizada a alocação
    if (!array) {
        fprintf(stderr, "Erro: falha ao alocar memória!\n\n");
        return 1;
    }
    // Captura os valores a serem armazenados
    for (int i = 0; i < len; i++) {
        printf("Insira o %dº valor a ser armazenado: ", i + 1);
        scanf("%d", &array[i]);
        getchar();
    }
    printf("\n");
    // Captura novo tamanho do array para realocar na memória
    printf("Insira a nova quantidade de valores: ");
    scanf("%d", &len);
    getchar();
    printf("\n");
    // Realoca na memória
    array = realloc(array, len * sizeof(int));
    // Retorna erro caso não seja realizada a realocação
    if (!array) {
        fprintf(stderr, "Erro: falha ao realocar memória!\n\n");
        return 2;
    }
    // Exibe o processo de realocação
    for (int i = 0; i < len; i++) {
        printf("Realocando - Endereço de Memória: %p | Índice de acesso linear: %d\n", array + i, i);
        #ifdef _WIN32
            Sleep(1500); // Windows
        #else
            usleep(1500000); // Linux/Unix
        #endif
    }
    printf("\n");
    // Libera memória
    free(array);
    return 0;
}