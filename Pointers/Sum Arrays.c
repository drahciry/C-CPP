// Includes
#include <stdio.h>

// Função para somar valores de dois arrays
int sumArrays(int* arr1, int* arr2, int len) {
    // Declaração de variáveis
    int sum = 0;

    // Realiza soma dos arrays
    for (int i = 0; i < len; i++) sum += *(arr1 + i) + *(arr2 + i);
    // Retorna a soma
    return sum;
}

// Função principal (main)
int main() {
    // Declaração de variáveis
    int arr1[] = {1, 5, 7, 9, 10}, arr2[] = {5, 6, 2, 11, 13, 7, 7, 2};
    int len1 = sizeof(arr1) / sizeof(arr1[0]), len2 = sizeof(arr2) / sizeof(arr2[0]);
    int sum;

    printf("\n---------- Soma de Arrays ----------\n\n");
    // Calcula a soma dos arrays
    sum = sumArrays(arr1, arr2, len1 > len2 ? len2 : len1);
    // Exibe soma dos arrays
    printf("Soma: %d\n\n", sum);
    return 0;
}