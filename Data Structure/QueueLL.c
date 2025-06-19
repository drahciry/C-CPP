// Includes
#include <stdio.h>
#include <stdlib.h>

// Tipo nó
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Tipo Fila (lista encadeada)
typedef struct {
    Node* front;
    Node* rear;
} QueueLL;

// Mensagem de erro para alocação de memória
void MallocError() {
    fprintf(stderr, "Erro: falha ao alocar memória!\n");
    exit(1);
}

// Mensagem de erro para fila vazia
void EmptyQueueError() {
    fprintf(stderr, "Erro: fila está vazia!\n");
    exit(2);
}

// Inicializa fila com lista encadeada
QueueLL* createQueueLL() {
    // Declaração de variáveis
    QueueLL* q = malloc(sizeof(QueueLL));
    // Retorna erro caso alocação falhe
    if (!q) MallocError();

    // Inicializa nós
    q->front = NULL;
    q->rear = NULL;
    // Retorna fila
    return q;
}

// Função que verifica se fila está vazia
int isEmpty(QueueLL* q) {
    return (!q->front);
}

// Função para enfilar dados
void enqueue(QueueLL* q, int value) {
    // Declaração de variáveis
    Node* n = malloc(sizeof(Node));
    // Retorna erro caso alocação falhe
    if (!n) MallocError();

    // Armazena dado
    n->data = value;
    // Verifica se fila está vazia para preencher fila
    if (isEmpty(q)) {
        q->front = q->rear = n;
        n->next = NULL;
        n->prev = NULL;
        return;
    }
    // Se fila não estiver vazia
    q->rear->next = n;
    n->prev = q->rear;
    q->rear = n;
    n->next = NULL;
}

// Função para desenfilar dados
int dequeue(QueueLL* q) {
    // Declaração de variáveis
    int value;
    Node* prev = q->front;

    // Verifica se fila está vazia
    if (isEmpty(q)) EmptyQueueError();
    // Armazena dados
    value = q->front->data;
    // Remove o nó da frente
    q->front = q->front->next;
    // Libera memória
    free(prev);
    // Verifica se fila ficou vazia
    if (isEmpty(q)) q->rear = NULL;
    // Retorna dados
    return value;
}

// Função para deletar fila
void deleteQueue(QueueLL* q) {
    // Declaração de variáveis
    Node* current = q->front;
    Node* next;

    // Verifica se fila está vazia
    if (isEmpty(q)) {
        free(q);
        return;
    }
    // Percorre fila inteira para liberar nó por nó
    while (current) {
        // Salva referência do próximo
        next = current->next;
        // Libera memória do atual
        free(current);
        // Recupera referência do próximo
        current = next;
    }
    // Libera memória da fila
    free(q);
}