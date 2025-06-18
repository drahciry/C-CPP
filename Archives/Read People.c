// Includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

// Tipo 'Person' do tipo struct
typedef struct {
    char name[50];
    int age;
} Person;

// Função que exibe os dados da pessoa do tipo Person
void displayPerson(Person* p) {
    printf("Nome: %s\n", p->name);
    printf("Idade: %d\n\n", p->age);
}

// Função que realiza leitura dinâmica do teclado
char* readline() {
    // Declaração de variáveis
    int ch, len = 0, cap = 10;
    char* temp;
    char* line = malloc(cap);
    // Retorna erro se não alocar
    if (!line) {
        fprintf(stderr, "Erro: falha ao alocar memória!\n\n");
        exit(1);
    }

    // Leitura de caracter por caracter
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // Realoca caso esteja cheio
        if (len >= cap - 2) {
            cap *= 2;
            temp = realloc(line, cap);
            while (!temp) temp = realloc(line, cap);
            line = temp;
        }
        line[len++] = ch;
    }
    // Adiciona terminador no fim da string
    line[len] = '\0';
    // Retorna a leitura feita
    return line;
}

// Função que lê arquivo binário
void readFile(char* path) {
    // Declaração de variáveis
    Person* p;
    int cap;
    FILE* file = fopen(path, "rb");
    // Retorna erro caso arquivo não seja aberto
    if (!file) {
        fprintf(stderr, "Erro: falha ao abrir arquivo!\n\n");
        exit(1);
    }

    // Realiza a leitura de quantos dados estão armazenados
    fread(&cap, sizeof(int), 1, file);
    p = malloc(cap * sizeof(Person));
    // Retorna erro caso alocação falhe
    if (!p) {
        fprintf(stderr, "Erro: falha ao alocar memória!\n\n");
        exit(2);
    }
    // Captura todos os dados de pessoas salvos no arquivo
    fread(p, sizeof(Person), cap, file);
    // Exibe todas as pessoas salvas no arquivo
    for (int i = 0; i < cap; i++) {
        printf("Pessoa %d:\n", i + 1);
        displayPerson(p + i);
        #ifdef _WIN32
            Sleep(1500);    // Windows
        #else
            usleep(1500000); // Linux/Unix
        #endif
    }
    // Libera memória
    free(p);
    // Fecha arquivo
    fclose(file);
}

// Função que realiza leitura da n-ésima pessoa
void readNperson(int n_th, char* path) {
    // Declaração de variáveis
    long int bytes;
    int cap;
    Person p;
    FILE* file = fopen(path, "rb");
    // Retorna erro caso arquivo não abra
    if (!file) {
        fprintf(stderr, "Erro: falha ao abrir arquivo!\n\n");
        exit(2);
    }
    // Verifica se a n-ésima pessoa existe
    fread(&cap, sizeof(int), 1, file);
    if (n_th > cap) {
        printf("Há somente %d pessoas salvas. Não é possível exiber Pessoa %d.\n\n", cap, n_th);
        // Fecha arquivo
        fclose(file);
        return;
    }
    // Reinicia cursor
    rewind(file);
    // Posiciona o cursor antes da n-ésima pessoa do arquivo
    fseek(file, sizeof(int) + (n_th - 1) * sizeof(Person), SEEK_SET);
    // Realiza a leitura da pessoa
    fread(&p, sizeof(Person), 1, file);
    // Exibe pessoa
    printf("Pessoa %d:\n", n_th);
    displayPerson(&p);
    // Exibe quantos bytes foram lidos após exibir pessoa
    printf("Foram lidos até o momento %ld bytes.\n\n", ftell(file));
    // Fecha arquivo
    fclose(file);
}

// Função principal (main)
int main() {
    // Declaração de variáveis
    int option = -1, n_th;
    char* path;

    printf("\n---------- View de Pessoas - Arquivo Binário ----------\n\n");
    // Menu "interativo" para o usuário
    while (option) {
        // Reinicia opção
        option = -1;
        // Captura da opção do usuário
        printf(
            "Opções disponíveis:\n"
            "[1] Exibir pessoas salvas\n"
            "[2] Pular para n-ésima pessoa\n"
            "[0] Encerrar programa\n\n"
            "Opção desejada: "
        );
        scanf("%d", &option);
        while (getchar() != '\n');
        switch (option) {
            // Exibe pessoas salvas
            case 1:
                // Captura nome do arquivo binário que armazena pessoas
                printf("\nInsira o nome do arquivo que deseja exibir pessoas: ");
                path = readline();
                printf("\n");
                // Lê arquivo e exibe pessoas
                readFile(path);
                // Libera memória
                free(path);
                break;
            // Pula para a n-ésima pessoa
            case 2:
                // Captura nome do arquivo binário que armazena pessoas
                printf("\nInsira o nome do arquivo que deseja exibir pessoas: ");
                path = readline();
                printf("\n");
                // Captura qual pessoa deseja exibir
                printf("Insira o número da pessoa que deseja exibir: ");
                scanf("%d", &n_th);
                while (getchar() != '\n');
                printf("\n");
                // Lê arquivo e exibe n-ésima pessoa
                readNperson(n_th, path);
                // Libera memória
                free(path);
                break;
            // Encerra programa
            case 0:
                break;
            // Exibe mensagem para opção inválida
            default:
                printf("\nOpção inválida. Insira a opção desejada novamente.\n\n");
        }
    }
    // Exibe mensagem de encerramento do programa
    printf("\nPrograma encerrado.\n\n");
    return 0;
}