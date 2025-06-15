// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    int x = 2;
    int* y = &x;

    printf("\n---------- Endereços de Memória e Ponteiros ----------\n\n");
    // Demonstração de conhecimento de endereços de memória, ponteiros e dados armazenados em variáveis
    printf(
        "Endereço da variável 'x': %p\n"
        "Valor da variável 'x': %d\n"
        "Endereço da variável 'y': %p\n"
        "Valor da variável 'y' (Endereço da variável 'x'): %p\n"
        "Valor da variável que 'y' está apontando (Valor da variável 'x'): %d\n\n",
        &x, x, &y, y, *y
    );
    return 0;
}