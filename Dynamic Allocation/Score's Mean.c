// Includes
#include <stdio.h>
#include <stdlib.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    float* score;
    float mean, totalSum = 0;
    int len;

    printf("\n---------- Calcula Média de Notas ----------\n\n");
    // Captura a quantidade de notas
    printf("Insira a quantidade total de notas: ");
    scanf("%d", &len);
    printf("\n");
    if (!len) {
        printf("Quantidade total de notas é igual a zero. Não há média a calcular.\n\n");
        return 0;
    }
    // Aloca espaço na memória de acordo com total
    score = malloc(len * sizeof(float));
    // Verifica se foi alocado na memória
    if (!score) {
        fprintf(stderr, "Erro: falha ao alocar na memória!\n\n");
        return 1;
    }
    // Captura notas
    for (int i = 0; i < len; i++) {
        printf("Insira a nota %d: ", i + 1);
        scanf("%f", &score[i]);
        getchar();
        totalSum += score[i];
    }
    // Cálculo da média
    mean = totalSum / len;
    // Exibe a média das notas
    printf("\nMédia das notas inseridas: %.2f\n\n", mean);
    // Libera espaço na memória
    free(score);
    return 0;
}