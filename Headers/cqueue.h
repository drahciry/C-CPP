#ifndef QUEUE_H
#define QUEUE_H

// Struct Queue
typedef struct {
    int size, cap, front, rear;
    int* queue;
} Queue;

// Protótipos
Queue* createQueue(int cap);
int isEmpty(Queue* q);
int isFull(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int lenQueue(Queue* q);
void displayQueue(Queue* q);
void deleteQueue(Queue* q);

#endif