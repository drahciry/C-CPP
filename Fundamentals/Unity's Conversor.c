// Includes
#include <stdio.h>

// Função principal (main)
int main() {
    // Declaração de variáveis
    float measure, result;
    int option;
    char unity[3];

    printf("\n---------- Conversor de unidades ----------\n\n");
    // Menu "interativo" para escolher a conversão a ser realizada
    printf(
        "Opções de conversão:\n"
        "[1] Conversão de temperatura\n"
        "[2] Conversão de comprimento\n"
        "[3] Conversão de volume\n\n"
        "Insira a opção desejada: "
    );
    scanf("%d", &option);
    getchar();
    printf("\n");
    switch (option) {
        // Conversão de temperatura
        case 1:
            // Menu "interativo" para escolher qual unidade deseja converter
            printf(
                "Deseja converter:\n"
                "[1] de Celsius para Fahrenheit\n"
                "[2] de Fahrenheit para Celsius\n\n"
                "Insira a opção desejada: "
            );
            scanf("%d", &option);
            getchar();
            printf("\n");
            // Captura valor da medida
            printf("Insira a medida (%s): ", option == 1 ? "°C" : "°F");
            scanf("%f", &measure);
            // Realiza a conversão de acordo com a opção selecionada ou retorna erro
            if (option == 1) {
                result = ((measure * 9) / 5) + 32;
                sscanf("°F", "%s", unity);
            } else if (option == 2) {
                result = ((measure - 32) * 5) / 9;
                sscanf("°C", "%s", unity);
            } else {
                printf("Opção inserida inválida. Conversor de unidades encerrado.\n\n");
                return 1;
            }
            getchar();
            break;
        case 2:
            // Menu "interativo" para escolher qual unidade deseja converter
            printf(
                "Deseja converter:\n"
                "[1] de metro para milha\n"
                "[2] de milha para metro\n\n"
                "Insira a opção desejada: "
            );
            scanf("%d", &option);
            getchar();
            printf("\n");
            // Captura valor da medida
            printf("Insira a medida (%s): ", option == 1 ? "m" : "mi");
            scanf("%f", &measure);
            // Realiza a conversão de acordo com a opção selecionada ou retorna erro
            if (option == 1) {
                result = measure * 0.00062137; 
                sscanf("mi", "%s", unity);
            } else if (option == 2) {
                result = measure * 1609.34;
                sscanf("m", "%s", unity);
            } else {
                printf("Opção inserida inválida. Conversor de unidades encerrado.\n\n");
                return 2;
            }
            getchar();
            break;
        case 3:
            // Menu "interativo" para escolher qual unidade deseja converter
            printf(
                "Deseja converter:\n"
                "[1] de metro cúbico para litro\n"
                "[2] de litro para metro cúbico\n\n"
                "Insira a opção desejada: "
            );
            scanf("%d", &option);
            getchar();
            printf("\n");
            // Captura valor da medida
            printf("Insira a medida (%s): ", option == 1 ? "m³" : "L");
            scanf("%f", &measure);
            // Realiza a conversão de acordo com a opção selecionada ou retorna erro
            if (option == 1) {
                result = measure * 1000; 
                sscanf("L", "%s", unity);
            } else if (option == 2) {
                result = measure * 0.001;
                sscanf("m³", "%s", unity);
            } else {
                printf("Opção inserida inválida. Conversor de unidades encerrado.\n\n");
                return 3;
            }
            getchar();
            break;
        // Encerra o programa caso a entrada não seja válida
        default:
            printf("Opção inserida inválida. Conversor de unidades encerrado.\n\n");
            return 4;
    }
    // Exibe resultado da conversão
    printf("Resultado da conversão: %.2f %s\n\n", result, unity);
    return 0;
}