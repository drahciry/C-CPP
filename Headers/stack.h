// stack.h
#ifndef STACK_H
#define STACK_H

// Struct Stack
typedef struct {
    int cap, top;
    int* stack;
} Stack;

// Protótipos
Stack* createStack(int cap);
int isEmpty(Stack* s);
int isFull(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int top(Stack* s);
int lenStack(Stack* s);
void displayStack(Stack* s);
void deleteStack(Stack* s);

#endif