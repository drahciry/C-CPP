// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    int n_th, prev_1 = 1, prev_2 = 0; // Casos base: n0 = 0 e n1 = 1

    printf("\n---------- Sequência de Fibonacci ----------\n\n");
    // Captura valor de n para retornar o n-ésimo termo da Sequência de Fibonacci
    printf("Insira o valor de n para retornar o n-ésimo termo da Sequência de Fibonacci: ");
    scanf("%d", &n_th);
    getchar();
    printf("\n");
    // Verifica qual é o n-ésimo termo da sequência por meio dos casos bases
    if (n_th == 0) n_th = 0;
    if (n_th == 1) n_th = 1;
    for (int i = 2; i <= n_th; i++) {
        prev_1 += prev_2;
        prev_2 = prev_1 - prev_2;
    }
    // Exibe n-ésimo termo da Sequência de Fibonacci
    printf("%dº termo da Sequência de Fibonacci: %d\n\n", n_th, prev_1);
    return 0;
}