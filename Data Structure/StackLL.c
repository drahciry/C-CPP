// Includes
#include <stdio.h>
#include <stdlib.h>

// Tipo Nó
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Tipo Pilha
typedef struct {
    Node* top;
} StackLL;

// Mensagem de erro para alocação de memória
void MallocError() {
    fprintf(stderr, "Erro: falha ao alocar memória!\n");
    exit(1);
}

// Mensagem de erro para fila vazia
void EmptyStackError() {
    fprintf(stderr, "Erro: pilha está vazia!\n");
    exit(2);
}

// Inicializa pilha
StackLL* createStackLL() {
    // Declaração de variáveis
    StackLL* s = malloc(sizeof(StackLL));
    // Retorna erro caso alocação falhe
    if (!s) MallocError();

    // Inicializa nó
    s->top = NULL;
    // Retorna pilha
    return s;
}

// Função que verifica se pilha está vazia
int isEmpty(StackLL* s) {
    return (!s->top);
}

// Push na pilha
void pushStack(StackLL* s, int value) {
    // Declaração de variáveis
    Node* newNode = malloc(sizeof(Node));
    // Retorna erro caso alocação falhe
    if (!newNode) MallocError();

    // Inicializa o nó
    newNode->data = value;
    newNode->prev = NULL;
    // Verifica se pilha está vazia
    if (isEmpty(s)) {
        s->top = newNode;
        newNode->next = NULL;
        return;
    }
    // Conexão do novo nó
    newNode->next = s->top;
    s->top->prev = newNode;
    s->top = newNode;
}

// Pop na pilha
int popStack(StackLL* s) {
    // Declaração de variáveis
    Node* next;
    int value;

    // Verifica se pilha está vazia
    if (isEmpty(s)) EmptyStackError();
    // Salva dados a ser removido
    value = s->top->data;
    // Salva referência para próximo nó, que será o top
    next = s->top->next;
    // Libera memória
    free(s->top);
    // Novo top
    next->prev = NULL;
    s->top = next;
    // Retorna dado apagado
    return value;
}

// Função para deletar pilha
void deleteStack(StackLL* s) {
    // Declaração de variáveis
    Node* current = s->top;
    Node* next;

    // Percorre toda pilha desempilhando
    while (current) {
        // Salva referência para o próximo
        next = current->next;
        // Libera memória
        free(current);
        // Recupera referência para o próximo
        current = next;
    }
    // Libera memória da pilha
    free(s);
}