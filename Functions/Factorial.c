// Includes
#include <stdio.h>

// Função que calcula fatorial com recursão
int factorial(int n) {
    // Quando n for igual a 0, retorna 1 (caso base)
    if (!n) return 1;
    // Recursão
    return n * factorial(n - 1);
}

// Função principal (main)
int main() {
    // Declaração de variáveis
    int number;

    printf("\n---------- Fatorial ----------\n\n");
    // Captura número para calcular fatorial
    printf("Insira um valor para calcular fatorial: ");
    scanf("%d", &number);
    getchar();
    // Exibe o fatorial de n
    printf("%d! = %d\n\n", number, factorial(number));
    return 0;
}