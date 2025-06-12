// Includes
#include <stdio.h>
#include <math.h>

// Função booleana para verificar se um número é primo
int isPrime(int number) {
    // Declaração de variáveis
    int limit = sqrt(number) + 1;

    // Tratamento do valor 1
    if (number == 1) return 0;
    // i começa em 2 pois é o primeiro número natural considerado primo.
    // O limite é a raiz quadrada inteira do número pois se a raiz quadrada inteira não o divide,
    // mais nenhum número o dividirá. Adiciona-se mais 1 para que aumente a margem.
    for (int i = 2; i < limit; i++) {
        // Se o número for dividido, será composto
        if (!(number % i)) return 0;
    }
    // Retorna verdadeiro para ser primo
    return 1;
}

// Função principal (main)
int main() {
    // Declaração de variáveis
    int number;

    printf("\n---------- Verificação de Número Primo ----------\n\n");
    // Captura número para verificar se é primo
    printf("Insira um valor para verificar se é primo: ");
    scanf("%d", &number);
    getchar();
    // Exibe se é primo utilizando operador ternário
    printf("\nO valor %d %s.\n\n", number, isPrime(number) ? "é primo" : "não é primo");
    return 0;
}