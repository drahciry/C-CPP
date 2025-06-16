// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    float mean;
    int num, sum = 0, len = 0;
    FILE* file = fopen("dados.txt", "r");
    if (!file) {
        fprintf(stderr, "\nErro: falha ao abrir arquivo!\n\n");
        return 1;
    }

    printf("\n---------- Média de Valores - Arquivo ----------\n\n");
    // Leitura até o fim do arquivo
    while (!feof(file)) {
        len++;
        fscanf(file, "%d", &num);
        printf("%d\n", num);
        sum += num;
    }
    // Corrige valor adicional por linha vazia
    sum -= num;
    len--;
    // Calcula média dos valores do arquivo
    mean = (float) sum / len;
    // Exibe a média calculada
    printf("Média dos valores no arquivo: %.2f\n\n", mean);
    // Fecha arquivo
    fclose(file);
    return 0;
}