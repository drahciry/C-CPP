// Includes
#include <stdio.h>
#include <string.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    char phrase[256];
    int option, result = 0; 

    printf("\n---------- Analisador de Frase ----------\n\n");
    // Menu "interativo" de opções de análise
    printf(
        "Opções disponíveis:\n"
        "[1] Contar vogais\n"
        "[2] Contar espaços\n"
        "[3] Contar palavras\n\n"
        "Insira a opção desejada: "
    );
    scanf("%d", &option);
    getchar();
    // Captura frase a ser analisada
    printf("\nInsira a frase a ser analisada: ");
    fgets(phrase, sizeof(phrase), stdin);
    // Remove '\n' do fim da frase e troca por '\0'
    phrase[strcspn(phrase, "\n")] = '\0';
    switch (option) {
        // Conta vogais
        case 1:
            for (int i = 0; phrase[i] != '\0'; i++) {
                switch (phrase[i]) {
                case 'a':
                    result++;
                    break;
                case 'e':
                    result++;
                    break;
                case 'i':
                    result++;
                    break;
                case 'o':
                    result++;
                    break;
                case 'u':
                    result++;
                    break;                    
                }
            }
            break;
        // Conta espaços
        case 2:
            for (int i = 0; phrase[i] != '\0'; i++) {
                if (phrase[i] == ' ') {
                    result++;
                }
            }
            break;
        // Conta palavras
        case 3:
            for (int i = 0; phrase[i] != '\0'; i++) {
                if (phrase[i] == ' ') {
                    result++;
                }
            }
            // Por ter feito a contagem por espaços, precisa adicionar 1 caso tenha achado algum espaço
            if (result) result++;
            break;
        // Retorna erro para opções inválidas
        default:
            fprintf(stderr, "Opção inserida inválida. Analisador encerrado.\n");
            return 1;
    }
    // Exibe resultado da análise
    printf("\nResultado da análise: %d %s.\n\n", result, option == 1 ? "vogais" : option == 2 ? "espaços" : "palavras");
    return 0;
}