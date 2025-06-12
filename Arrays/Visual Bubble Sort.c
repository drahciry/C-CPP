// Includes
#include <stdio.h>
#include <unistd.h> 
#include <windows.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    int arr[] = {12, 2, 69, 8, 97, 0};
    int temp, change, len = sizeof(arr) / sizeof(arr[0]);

    printf("\n---------- Bubble Sort 'Animado' ----------\n\n");
    // Exibição antes da ordenação
    printf("Array inicializado:\n");
    for (int i = 0; i < len; i++) {
        printf("%d; ", arr[i]);
    }
    printf("\n\nIniciando ordenação...\n\n");
    // Bubble Sort
    for (int i = 0; i < len; i ++) {
        change = 0;
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                printf("Troca realizada: %d ~ %d -> %d ~ %d\n", arr[j], arr[j + 1], arr[j + 1], arr[j]);
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                change = 1;
                #ifdef _WIN32
                    Sleep(1500); // Windows
                #else
                    usleep(1500000); // Linux/Unix
                #endif
            }
        }
        if (!change) break; 
    }
    // Exibição depois da ordenação
    printf("\nArray ordenado:\n");
    for (int i = 0; i < len; i++) {
        printf("%d; ", arr[i]);
    }
    printf("\n\n");
    return 0;
}