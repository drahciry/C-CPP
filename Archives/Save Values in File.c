// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    int num;
    FILE* file = fopen("dados.txt", "w");
    if (!file) {
        fprintf(stderr, "\nErro: falha ao abrir arquivo!\n\n");
        return 1;
    }

    printf("\n---------- Básico de Arquivos ----------\n\n");
    // Captura 5 números e salva todos no arquivo de texto
    for (int i = 1; i < 6; i++) {
        printf("Insira o %dº valor para salvar no arquivo: ", i);
        scanf("%d", &num);
        fprintf(file, "%d\n", num);
    }
    printf("\nValores salvos com sucesso no arquivo.\n\n");
    // Fecha arquivo
    fclose(file);
    return 0;
}