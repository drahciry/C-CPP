#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Realiza a leitura do teclado de forma dinâmica
char* read_line() {
    // Declaração de variáveis
    int ch, len = 0, cap = 10;
    char* line = malloc(cap);
    if (!line) {
        fprintf(stderr, "Erro: falha na alocação de memória!\n");
        exit(1);
    }
    
    // Leitura de caractere por caractere
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (len >= cap) {
            cap *= 2;
            line = realloc(line, cap);
            if (!line) {
                fprintf(stderr, "Erro: falha ao realocar memória!\n");
                exit(1);
            }
        }
        line[len++] = ch;
    }
    line[len] = '\0';
    return line;
}

// Verifica se é integer
int is_int(const char* str) {
    // Declarações de variáveis
    char* end;
    const char* p = str;
    
    // Verifica se o primeiro caractere é um sinal
    if (*p == '+' || *p == '-') p++;
    // Captura o integer e vê se tem mais algo na string
    strtol(p, &end, 10);
    while (isspace(*end)) end++;
    // Retorna diferente de 0 caso seja integer
    return *p != '\0' && *end == '\0';
}

// Verifica se é float
int is_float(const char* str) {
    // Declarações de variáveis
    char* end;
    const char* p = str;
    
    // Verifica se o primeiro caractere é um sinal
    if (*p == '+' || *p == '-') p++;
    // Captura o float e vê se tem mais algo na string
    strtof(p, &end);
    while (isspace(*end)) end++;
    // Retorna diferente de 0 caso seja float
    return *p != '\0' && *end == '\0';
}

// Verifica se é double
int is_double(const char* str) {
    // Declarações de variáveis
    char* end;
    const char* p = str;
    
    // Verifica se o primeiro caractere é um sinal
    if (*p == '+' || *p == '-') p++;
    // Captura o double e vê se tem mais algo na string
    strtod(p, &end);
    while (isspace(*end)) end++;
    // Retorna diferente de 0 caso seja double
    return *p != '\0' && *end == '\0';
}