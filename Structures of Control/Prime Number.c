// Includes
#include <stdio.h>
#include <math.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    int value, limit, prime = 1;

    printf("\n---------- Verificador de Números Primos ----------\n\n");
    // Captura valor para verificar se é primo
    printf("Insira o número natural que deseja verificar se é primo: ");
    scanf("%d", &value);
    getchar();
    // Verifica se número é primo usando sua raiz quadrada inteira
    limit = sqrt(value) + 1;
    // For começa em 2 pois é o primeiro número natural considerado primo
    for (int i = 2; i < limit; i++) {
        if (!(value % i)) {
            prime = 0;
            break;
        }
    }
    // Exibe o resultado da verificação
    printf("O valor %d inserido %s!\n", value, prime ? "é primo" : "não é primo");
    return 0;
}