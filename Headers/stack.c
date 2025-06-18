// Includes
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/************************ ERROS ************************/

// Erro de alocação de memória
void MallocError() {
    fprintf(stderr, "Erro: falha ao alocar memória!\n");
    exit(1);
}

// Erro de pilha vazia
void EmptyStackError() {
    fprintf(stderr, "Erro: pilha está vazia!\n");
    exit(2);
}

// Erro de pilha cheia
void FullStackError() {
    fprintf(stderr, "Erro: pilha está cheia!\n");
    exit(3);
}

/******************* IMPLEMENTAÇÕES ********************/

// Função que inicializa pilha
Stack* createStack(int cap) {
    // Declaração de variáveis
    Stack* s = malloc(sizeof(Stack));
    // Retorna erro caso não seja alocado
    if (!s) MallocError();
    
    // Inicializa array com capacidade informada
    s->stack = malloc(cap * sizeof(int));
    // Retorna erro caso não seja alocado
    if (!s->stack) MallocError();
    s->cap = cap;
    s->top = -1;
    // Retorna a pilha
    return s;
}

// Função que verifica se pilha está vazia
int isEmpty(Stack* s) {
    if (s->top == -1) return 1;
    return 0;
}

// Função que verifica se pilha está cheia
int isFull(Stack* s) {
    if (s->top + 1 == s->cap) return 1;
    return 0;
}

// Função que empilha valor
void push(Stack* s, int value) {
    // Verifica se pilha está cheia
    if (isFull(s)) FullStackError();
    // Verifica se pilha está vazia
    if (isEmpty(s)) {
        s->top = 0;
        s->stack[s->top] = value;
        return;
    }
    // Adiciona valor à pilha
    s->stack[++s->top] = value;
}

// Função para desempilhar valor
int pop(Stack* s) {
    // Declaração de variáveis
    int value;

    // Verifica se pilha está vazia
    if (isEmpty(s)) EmptyStackError();
    // Remove valor da pilha
    value = s->stack[s->top];
    s->top--;
    // Retorna valor desempilhado
    return value;
}

// Função para retornar topo
int top(Stack* s) {
    return s->stack[s->top];
}

// Função para retornar tamanho da pilha
int lenStack(Stack* s) {
    return s->top + 1;
}

// Função para exibir a pilha
void displayStack(Stack* s) {
    // Verifica se pilha está vazia
    if (isEmpty(s)) EmptyStackError();
    // Percorre array para exibir dados
    for (int i = s->top; i >= 0; i--) {
        printf("%d; ", s->stack[i]);
    }
    printf("\n");
}

// Função para deletar pilha
void deleteStack(Stack* s) {
    free(s->stack);
    free(s);
}