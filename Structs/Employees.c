#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Captura entrada do teclado de forma dinâmica
char* read_line() {
    // Declaração de variáveis
    int ch, len = 0, cap = 10;
    char* line = malloc(cap);

    // Verifica alocação de memória
    if (!line) {
        fprintf(stderr, "Erro: falha na alocação de memória!\n");
        exit(1);
    }
    // Captura caractere por caractere
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // Realoca caso array esteja lotado
        if (len >= cap) {
            cap *= 2;
            line = realloc(line, cap);
            // Verifica realocação de memória
            if (!line) {
                fprintf(stderr, "Erro: falha na realocação de memória!\n");
                exit(2);
            }
        }
        // Guarda caractere no array
        line[len++] = ch;
    }
    // Determina o fim do array string
    line[len] = '\0';
    return line;
}

// Mensagem de erro e exit
void print_input_error_and_exit() {
    fprintf(stderr, "Erro: tipo da entrada é inválido!\n");
    exit(3);
}

// Verifica se a entrada é um integer
int is_int(const char* str) {
    // Declaração de variáveis
    char* end;
    const char* p = str;

    // Verifica se o primeiro caractere é um sinal
    if (*p == '+' || *p == '-') p++;
    // Captura o integer e o resto da entrada
    strtol(p, &end, 10);
    // Percorre o resto em busca de algo diferente de integer
    while (isspace(*end)) end++;
    // Retorna diferente de 0 caso seja integer
    if (*p != '\0' && *end == '\0') return 1;
    print_input_error_and_exit();
}

// Verifica se a entrada é um float
int is_float(const char* str) {
    // Declaração de variáveis
    char* end;
    const char* p = str;
    
    // Verifica se o primeiro caractere é um sinal
    if (*p == '+' || *p == '-') p++;
    // Captura o float e o resto da entrada
    strtof(p, &end);
    // Percorre o resto em busca de algo diferente de float
    while (isspace(*end)) end++;
    // Retorna diferente de 0 caso seja float
    if (*p != '\0' && *end == '\0') return 1;
    print_input_error_and_exit();
}

// Verifica se a entrada é um double
int is_double(const char* str) {
    // Declaração de variáveis
    char* end;
    const char* p = str;

    // Verifica se o primeiro caractere é um sinal
    if (*p == '+' || *p == '-') p++;
    // Captura o double e o resto da entrada
    strtod(str, &end);
    // Percorre o resto em busca de algo diferente de double
    while (isspace(*end)) end++;
    // Retorna diferente de 0 caso seja double
    if (*p != '\0' && *end == '\0') return 1;
    print_input_error_and_exit();
}

// Captura integer
int capture_int() {
    char* temp;
    int integer;
    if (is_int((temp = read_line()))) sscanf(temp, "%d", &integer);
    free(temp);
    return integer;
}

// Captura float
float capture_float() {
    char* temp;
    float floating;
    if (is_float((temp = read_line()))) sscanf(temp, "%f", &floating);
    free(temp);
    return floating;
}

// Struct para funcionários
struct Employee {
    int id;
    int active;
    char* name;
    char* position;
    float salary;
};

// Cria array de funcionários
struct Employee* createEmployees(int qtf) {
    // Aloca array de funcionários
    struct Employee* e = malloc(qtf * sizeof(struct Employee));
    // Verifica alocação de memória
    if (!e) {
        fprintf(stderr, "Erro: falha na alocação de memória!\n");
        exit(2);
    }
    return e;
}

// Realoca funcionários quando estiver cheio
void realocEmployees(struct Employee** e, int* qtf) {
    *qtf *= 2;
    // Realoca para o dobro da capacidade
    *e = realloc(*e, *qtf * sizeof(struct Employee));
    // Verifica realocação de memória
    if (!(*e)) {
        fprintf(stderr, "Erro: falha na realocação de memória!\n");
        exit(2);
    }
}

// Realiza cadastro de funcionário
void registerEmployee(struct Employee* e) {
    static int id = 0;
    e->id = ++id;
    e->active = 1;
    printf("Insira o nome do funcionário: ");
    e->name = read_line();
    printf("Insira o cargo do funcionário: ");
    e->position = read_line();
    printf("Insira o salário do funcionário (em R$): ");
    e->salary = capture_float();
    printf("Funcionário ID %d cadastrado com sucesso!\n", e->id);
}

// Exibe funcionário
void displayEmployee(struct Employee* e) {
    printf("\nFuncionário ID %d:\n", e->id);
    printf("\nNome: %s\n", e->name);
    printf("Cargo: %s\n", e->position);
    printf("Salário: R$ %.2f\n", e->salary);
}

// Realiza atualização de funcionário
void updateEmployee(struct Employee* e) {
    displayEmployee(e);
    printf("Atualize o nome: ");
    free(e->name);
    e->name = read_line();
    printf("Atualize o cargo: ");
    free(e->position);
    e->position = read_line();
    printf("Atualize o salário (em R$): ");
    e->salary = capture_float();
    printf("Funcionário ID %d atualizado com sucesso!\n", e->id);
}

// Função principal
int main() {
    // Declaração de variáveis
    struct Employee* e;
    int option, id, find = 0, len = 0, cap = 5;
    float salary;

    // Cria array de funcionários
    e = createEmployees(cap);
    // Menu de opções
    while (1) {
        printf("\nOpções disponíveis:\n"
               "[1] Cadastrar novo funcionário\n"
               "[2] Atualizar funcionário\n"
               "[3] Exibir todos os funcionários\n"
               "[4] Buscar funcionário pelo ID\n"
               "[5] Deletar funcionário\n"
               "[6] Filtrar por salário\n"
               "[7] Encerrar programa\n"
               "\nOpção selecionada: ");
        option = capture_int();
        // Cadastra novos funcionários
        if (option == 1) {
            if (len >= cap) {
                realocEmployees(&e, &cap);
            }
            registerEmployee(&e[len++]);
        // Atualiza funcionários
        } else if (option == 2) {
            while (1) {
                printf("\nInsira o ID do funcionário que deseja atualizar: ");
                id = capture_int();
                if (id <= 0) {
                    printf("ID inválido. Insira somente IDs a partir de 1.\n");
                    continue;
                }
                break;
            }
            if (id <= len) {
                updateEmployee(&e[id - 1]);
            } else {
                printf("Funcionário não encontrado.\n");
            }
        // Exibe todos os funcionários
        } else if (option == 3) {
            for (int i = 0; i < len; i++) {
                if (e[i].active) displayEmployee(&e[i]);
            }
        // Busca funcionário
        } else if (option == 4) {
            while (1) {
                printf("\nInsira o ID do funcionário que deseja buscar: ");
                id = capture_int();
                if (id <= 0) {
                    printf("ID inválido. Insira somente IDs a partir de 1.\n");
                    continue;
                }
                break;
            }
            if (id <= len) {
                if (e[id - 1].active) {
                    displayEmployee(&e[id - 1]);
                } else {
                    printf("Funcionário não encontrado.\n");
                }
            } else {
                printf("Funcionário não encontrado.\n");
            }
        // Deleta funcionário
        } else if (option == 5) {
            while (1) {
                printf("\nInsira o ID do funcionário que deseja deletar: ");
                id = capture_int();
                if (id <= 0) {
                    printf("ID inválido. Insira somente IDs a partir de 1.\n");
                    continue;
                }
                break;
            }
            if (id <= len) {
                if (e[id - 1].active) {
                    e[id - 1].active = 0;
                    printf("Funcionário deletado com sucesso!\n");
                } else {
                    printf("Funcionário não encontrado.\n");
                }
            } else {
                printf("Funcionário não encontrado.\n");
            }
        // Filtra funcionários por salário
        } else if (option == 6) {
            while (1) {
                printf("\nInsira o valor do salário pelo qual deseja filtrar: ");
                salary = capture_float();
                if (salary < 1509) {
                    printf("Salário inválido. O mínimo a ser inserido é R$ 1509.00.\n");
                    continue;
                }
                break;
            }
            find = 0;
            for (int i = 0; i < len; i++) {
                if (e[i].salary > salary) {
                    displayEmployee(&e[i]);
                    find = 1;
                }
            }
            if (!find) {
                printf("Nenhum funcionário ganha mais que R$ %.2f.\n", salary);
            }
        // Encerra o programa
        } else if (option == 7) {
            printf("Programa encerrado!\n");
            break;
        // Entrada inválida
        } else {
            printf("\nOpção inválida. Insira somente as opções listadas.\n");
        }
    }
    free(e);
    return 0;
}