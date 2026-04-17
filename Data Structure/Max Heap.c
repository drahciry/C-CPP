#include <stdlib.h>

typedef struct {
    int* data;
    int size;
    int cap;
} MaxHeap;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MaxHeap* heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap->data[idx] > heap->data[parent]) {
            swap(&heap->data[idx], &heap->data[parent]);
            idx = parent;
        } else break;
    }
}

void heapify_down(MaxHeap* heap, int idx) {
    int largest = idx;
    int left = idx * 2 + 1;
    int right = idx * 2 + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest])
        largest = left;
    if (right < heap->size && heap->data[right] > heap->data[largest])
        largest = right;

    if (largest != idx) {
        swap(&heap->data[idx], &heap->data[largest]);
        heapify_down(heap, largest);
    }
}

void push(MaxHeap* heap, int value) {
    if (heap->size >= heap->cap) return;
    heap->data[heap->size++] = value;
    heapify_up(heap, heap->size - 1);
}

int pop(MaxHeap* heap) {
    if (heap->size == 0) return -1;
    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify_down(heap, 0);
    return root;
}

MaxHeap* create_heap(int cap) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (heap) {
        heap->size = 0;
        heap->cap = cap;
        heap->data = (int*)malloc(heap->cap * sizeof(int));
    }
    return heap;
}

void delete_heap(MaxHeap* heap) {
    free(heap->data);
    free(heap);
}

int main() {
    return 0;
}