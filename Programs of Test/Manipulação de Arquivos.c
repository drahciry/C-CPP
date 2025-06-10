#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaração de variáveis globais
int g_matricula = 202500001;

// Tipo aluno da forma struct
typedef struct {
    int matricula;
    char* nome;
    float nota;
} Aluno;

// Realiza a leitura do teclado de forma dinâmica
char* readline() {
    // Declaração de variáveis
    int ch, len = 0, cap = 10;
    char* line = malloc(cap);
    // Encerra o programa caso a alocação falhe
    if (!line) {
        fprintf(stderr, "Erro: falha na alocação de memória!\n");
        exit(1);
    }
    
    // Leitura de caractere por caractere
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // Se lotar, realoca o dobro de espaço já alocado
        if (len >= cap) {
            cap *= 2;
            line = realloc(line, cap);
            // Encerra o programa caso a alocação falhe
            if (!line) {
                fprintf(stderr, "Erro: falha ao realocar memória!\n");
                exit(1);
            }
        }
        // Salva caractere por caractere no array de char
        line[len++] = ch;
    }
    // Adiciona o "\0" ao final da string
    line[len] = '\0';
    return line;
}

// Função que cria arquivo ou abre arquivo (excluindo tudo)
// E adiciona texto ao arquivo
void writeFile(char* text, char* path) {
    // Declaração de variáveis
    FILE* file = fopen(path, "w");
    // Encerra o programa caso falhe a abertura do arquivo
    if (!file) {
        fprintf(stderr, "Erro: falha ao abrir arquivo!\n");
        exit(1);
    }
    // Escreve no arquivo
    fprintf(file, "%s\n", text);
    // Fecha arquivo
    fclose(file);
}

// Função que abre um arquivo e adiciona texto ao final do arquivo
void appendFile(char* text, char* path) {
    // Declaração de variáveis
    FILE* file = fopen(path, "a");
    // Encerra o programa caso falhe a abertura do arquivo
    if (!file) {
        fprintf(stderr, "Erro: falha ao abrir arquivo!\n");
        exit(1);
    }
    // Escreve no arquivo
    fprintf(file, "%s\n", text);
    // Fecha o arquivo
    fclose(file);
}

// Função que lê conteúdo do arquivo
char* readFile(char* path) {
    // Declaração de variáveis
    int ch, len = 0, cap = 10;
    char* text = malloc(cap);
    // Encerra programa caso falhe a alocação de memória
    if (!text) {
        fprintf(stderr, "Erro: falha ao alocar memória!\n");
        exit(3);
    }
    FILE* file = fopen(path, "r");
    // Encerra o programa caso falhe a abertura do arquivo
    if (!file) {
        fprintf(stderr, "Erro: falha ao abrir arquivo!\n");
        exit(4);
    }
    // Lê caractere por caractere do arquivo
    while ((ch = fgetc(file)) != EOF) {
        // Se lotar, realoca o dobro de espaço já alocado
        if (len >= cap) {
            cap *= 2;
            text = realloc(text, cap);
            // Encerra o programa caso falhe a realocação de memória
            if (!text) {
                fprintf(stderr, "Erro: falha ao realocar memória!\n");
                exit(5);
            }
        }
        // Adiciona caractere no array de char
        text[len++] = ch;
    }
    // Adiciona o "\0" ao final da string
    text[len] = '\0';
    return text;
}

// Função que imprime texto
void displayText(char* text) {
    printf("%s\n", text);
}

// Função que cria um aluno e registra seus dados
Aluno cadastrarAluno() {
    Aluno a;
    a.matricula = g_matricula++;
    printf("Insira o nome do aluno: ");
    a.nome = readline();
    printf("Insira a nota do aluno: ");
    scanf("%f", &a.nota);
    while (getchar() != '\n');
    printf("Aluno cadastrado com sucesso!\n");
    return a;
}

// Função para exibir 
void exibirAluno(Aluno* a) {
    printf("Matrícula do aluno: %05d\n", a->matricula);
    printf("Nome do aluno: %s\n", a->nome);
    printf("Nota do aluno: %.2f\n", a->nota);
}

// Função que transforma toda string em lower case
void lower(char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] >= 65 && string[i] <= 90) {
            string[i] = (string[i] % 65) + 97;
        }
    }
}

// Busca binária
int binarySearch(Aluno* a, int len, int target) {
    // Declaração de variáveis
    int left = 0, right = len - 1, mid;

    while (left <= right) {
        mid = (left + right) / 2;
        if (target == a[mid].matricula) {
            return mid;
        } else if (target < a[mid].matricula) {
            right = mid - 1;
        } else if (target > a[mid].matricula) {
            left = mid + 1;
        }
    }
    // Retorna "-1" caso não ache
    return -1;
}

// Função para construir texto que será salvo em arquivo .txt
char* buildText(int matricula, char* nome, float nota) {
    // Declaração de variáveis
    char* result;
    int len;

    // Tamanho da linha que será salva
    len = 9 + strlen(nome) + 5 + 2; // 9 para a matrícula, strlen(nome) para tamanho do nome, 5 para nota e 2 para ';'
    result = malloc(len);
    // Encerra o programa caso falhe a alocação de memória
    if (!result) {
        fprintf(stderr, "Erro: falha ao alocar memória!\n");
        exit(6);
    }
    // Salva todas as informações em um ponteiro auxiliar que será retornado
    snprintf(result, len, "%d;%s;%.2f", matricula, nome, nota);
    return result;
}
 
int main() {
    // Declaração de variáveis
    char* path = "alunos.csv";
    char* text;
    int option, search, target;
    int index = 0, cap = 0, key = 1;
    Aluno alunos[100];

    // Inicializa o arquivo zerado
    writeFile("Matrícula;Nome;Nota", path);
    // Exibe menu CRUD enquanto não recebe entrada igual a "0"
    while (key) {
        printf(
            "\nOpções disponíveis:\n"
            "[1] Cadastrar aluno\n"
            "[2] Buscar aluno por matrícula\n"
            "[3] Salvar alunos\n"
            "[0] Encerrar programa\n"
            "\nInsira a ação desejada: "
        );
        scanf("%d", &option);
        printf("\n");
        while (getchar() != '\n');
        switch (option) {
            // Cadastra aluno
            case 1:
                alunos[cap++] = cadastrarAluno();
                break;
            // Exibe aluno
            case 2:
                printf("Insira a matrícula do aluno que deseja exibir: ");
                scanf("%d", &target);
                printf("\n");
                while (getchar() != '\n');
                // Busca binária por aluno
                search = binarySearch(alunos, cap, target);
                // Caso aluno não seja encontrado
                if (search == -1) {
                    printf("Aluno não encontrado.\n");
                    break;
                }
                exibirAluno(&alunos[search]);
                break;
            // Salva alunos em arquivo CSV de alunos
            case 3:
                // Percorre array de alunos a partir de onde parou
                for (; index < cap; index++) {
                    // Monta linha que será adicionada ao arquivo
                    text = buildText(alunos[index].matricula, alunos[index].nome, alunos[index].nota);
                    // Adiciona linha ao arquivo
                    appendFile(text, path);
                    free(text);
                }
                printf("Alunos salvos com sucesso!\n");
                break;
            // Encerra programa
            case 0:
                printf("Programa encerrado.\n\n");
                key = 0;
                break;
            // Entradas inválidas
            default:
                printf("Opção inserida inválida. Insira somente as opções listadas.\n");
        }
    }
    // Desaloca nome dos alunos da memória
    for (int i = 0; i < cap; i++) free(alunos[i].nome);
    return 0;
}