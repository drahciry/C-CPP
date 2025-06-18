// Includes
#include <stdio.h>
#include <stdlib.h>
#include "cqueue.h"

// Tipo Fila
typedef struct {
    int size, cap, front, rear;
    int* queue;
} Queue;

/************************ ERROS ************************/

// Erro de alocação de memória
void MallocError() {
    fprintf(stderr, "Erro: falha ao alocar memória!\n");
    exit(1);
}

// Erro de fila vazia
void EmptyQueueError() {
    fprintf(stderr, "Erro: fila está vazia!\n");
    exit(2);
}

// Erro de fila cheia
void FullQueueError() {
    fprintf(stderr, "Erro: fila está cheia!\n");
    exit(3);
}

/******************* IMPLEMENTAÇÕES ********************/

// Função que inicializa fila
Queue* createQueue(int cap) {
    // Declaração de variáveis
    Queue* q = malloc(sizeof(Queue));
    // Retorna erro caso não seja alocado
    if (!q) MallocError();
    
    // Inicializa array com capacidade informada
    q->queue = malloc(cap * sizeof(int));
    // Retorna erro caso não seja alocado
    if (!q->queue) MallocError();
    q->cap = cap;
    q->size = 0;
    q->front = -1;
    q->rear = -1;
    // Retorna a fila
    return q;
}

// Função que verifica se fila está vazia
int isEmpty(Queue* q) {
    if (!q->size) return 1;
    return 0;
}

// Função que verifica se fila está cheia
int isFull(Queue* q) {
    if (q->size == q->cap) return 1;
    return 0;
}

// Função que enfila dados
void enqueue(Queue* q, int value) {
    // Verifica se fila está cheia
    if (isFull(q)) FullQueueError();
    // Verifica se fila está vazia
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
        q->queue[q->rear] = value;
        q->size++;
        return;
    }
    // Adiciona valor à fila
    q->rear = (q->rear + 1) % q->cap;
    q->queue[q->rear] = value;
    q->size++;
}

// Função que desenfila dados
int dequeue(Queue* q) {
    // Declaração de variáveis
    int value;

    // Verifica se fila está vazia
    if (isEmpty(q)) EmptyQueueError();
    // Remove valor da fila
    value = q->queue[q->front];
    q->front = (q->front + 1) % q->cap;
    q->size--;
    // Verifica se fila ficou vazia
    if (isEmpty(q)) {
        q->front = -1;
        q->rear = -1;
    }
    // Retorna valor desenfilado
    return value;
}

// Função para retornar tamanho da pilha
int lenQueue(Queue* q) {
    return q->size;
}

// Função que exibe fila
void displayQueue(Queue* q) {
    // Verifica se fila está vazia
    if (isEmpty(q)) EmptyQueueError();
    // Percorre array para exibir dados
    for (int i = q->front;; i = (i + 1) % q->cap) {
        printf("%d; ", q->queue[i]);
        if (i == q->rear) break;
    }
    printf("\n");
}

// Função para deletar fila
void deleteQueue(Queue* q) {
    free(q->queue);
    free(q);
}