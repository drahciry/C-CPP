// Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função principal (main)
int main() {
    // Gerador de seed para aleatorizar número
    srand(time(NULL));
    // Declaração de variáveis
    int secret = rand() % 101;
    int choice = -1, attempts = 0;

    printf("\n---------- Jogo do Adivinha ----------\n\n");
    // Explicação breve ao usuário
    printf("Tente adivinhar em qual número estou pensando entre 0 e 100.\n\n");
    // Enquanto a escolha for diferente do número aleatorizado
    while (choice != secret) {
        // Captura palpite do usuário e incrementa tentativas
        printf("Palpite %d: ", ++attempts);
        scanf("%d", &choice);
        getchar();
        // Retorna feedback para usuário sobre sua tentativa
        if (choice > secret) {
            printf("Seu palpite é maior que o número que estou pensando... Tente novamente!\n\n");
        } else if (choice < secret) {
            printf("Seu palpite é menor que o número que estou pensando... Tente novamente!\n\n");
        }
    }
    // Exibe quantas tentativas foram feitas
    printf("Parabéns! Você acertou em %d tentativas.\n\n", attempts);
    return 0;
}