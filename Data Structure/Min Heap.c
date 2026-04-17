#include <stdlib.h>

typedef struct {
    int* data;
    int size;
    int cap;
} MinHeap;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap* heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap->data[idx] < heap->data[parent]) {
            swap(&heap->data[idx], &heap->data[parent]);
            idx = parent;
        } else break;
    }
}

void heapify_down(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = idx * 2 + 1;
    int right = idx * 2 + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;
    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != idx) {
        swap(&heap->data[idx], &heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

void push(MinHeap* heap, int value) {
    if (heap->size == heap->cap) return;
    heap->data[heap->size++] = value;
    heapify_up(heap, heap->size - 1);
}

int pop(MinHeap* heap) {
    if (heap->size == 0) return -1; // Uses a sentinel value that makes sense for you
    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify_down(heap, 0);
    return root;
}

MinHeap* create_heap(int cap) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (heap == NULL) return NULL;

    heap->size = 0;
    heap->cap = cap;
    heap->data = (int*)malloc(heap->cap * sizeof(int));

    return heap;
}

void delete_heap(MinHeap* heap) {
    free(heap->data);
    free(heap);
}

int main() {
    return 0;
}