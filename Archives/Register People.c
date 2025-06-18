// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tipo 'Person' do tipo struct
typedef struct {
    char name[50];
    int age;
} Person;

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

// Função que abre arquivo binário e salva Person
void writeFile(char* path, Person* p, int cap) {
    // Declaração de variáveis
    FILE* file = fopen(path, "wb");
    // Retorna erro caso não seja possível abrir arquivo
    if (!file) {
        fprintf(stderr, "Erro: falha ao abrir arquivo!\n\n");
        exit(3);
    }

    // Salva a quantidade de pessoas que serão salvas no arquivo
    fwrite(&cap, sizeof(int), 1, file);
    // Salva pessoas do tipo Person no arquivo aberto
    fwrite(p, sizeof(Person), cap, file);
    // Fecha arquivo
    fclose(file);
}

// Função que inicializa array de Person
Person* createPeople(int cap) {
    // Inicializa array de Person
    Person* p = malloc(cap * sizeof(Person));
    if (!p) {
        fprintf(stderr, "Erro: falha ao alocar memória!\n\n");
        exit(2);
    }
    // Zera a memória
    memset(p, 0, cap * sizeof(Person));
    // Retorna array de Person
    return p;
}

// Função que cadastra pessoa (Person)
void registerPerson(Person* p) {
    printf("Insira o nome da pessoa a ser registrada: ");
    fgets(p->name, sizeof(p->name), stdin);
    p->name[strcspn(p->name, "\n")] = '\0';
    printf("Insira a idade da pessoa: ");
    scanf("%d", &p->age);
    printf(
        "\nPessoa registrada com sucesso:\n"
        "Nome: %s | Idade: %d\n\n",
        p->name, p->age
    );
}

// Realoca array de Person
void reallocPerson(Person** p, int* cap) {
    // Declaração de variáveis
    Person* temp;

    // Dobra a capacidade do array
    *cap *= 2;
    // Realoca no array temporário
    temp = realloc(*p, *cap * sizeof(Person));
    // Caso a realocação falhe, tenta reallocar até não falhar
    while (!temp) temp = realloc(*p, *cap * sizeof(Person));
    // Zera a memória
    memset(temp + (*cap / 2), 0, (*cap / 2) * sizeof(Person));
    // Copia o array realocado
    *p = temp;
}

// Função principal (main)
int main() {
    // Declaração de variáveis
    int option = -1, len = 0, cap = 2;
    char* path;
    char* temp;
    Person* p = createPeople(cap);

    printf("\n---------- Registro de Pessoas - Arquivo Binário ----------\n\n");
    // Menu "Interativo"
    while (option != 0) {
        printf(
            "Opções disponíveis:\n"
            "[1] Registrar pessoa\n"
            "[0] Encerrar programa\n\n"
            "Opção desejada: "
        );
        scanf("%d", &option);
        while(getchar() != '\n');
        printf("\n");
        switch (option) {
            // Registra pessoa no sistema
            case 1:
                // Realoca memória caso esteja cheio
                if (len >= cap - 1) {
                    reallocPerson(&p, &cap);
                }
                registerPerson(&p[len++]);
                break;
            // Encerra programa
            case 0:
                break;
            // Opções inválidas
            default:
                printf("\nOpção inserida inválida. Insira uma opção válida.\n");
        }
    }
    // Captura nome do arquivo que deseja salvar dados
    printf("Insira o nome do arquivo que deseja salvar pessoas registradas: ");
    path = readline();
    // Salva array de Person em arquivo binário
    writeFile(path, p, len);
    // Feedback
    printf("\nPessoas salvas com sucesso!\n\n");
    // Libera memória
    free(p);
    free(path);
    return 0;
}