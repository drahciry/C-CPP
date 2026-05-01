#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* BUBBLE SORT */

void bubble_sort(int* arr, int left, int right) {
    for (int i = left; i <= right; i++) {
        int changed = 0;
        for (int j = left; j <= right - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                changed = 1;
            }
        }
        if (!changed) break;
    }
}

/* INSERTION SORT */

void insertion_sort(int* arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/* MERGE SORT */

void merge(int* arr, int* temp, int left, int mid, int right) {
    int i = left;
    int k = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (k = left; k <= right; k++)
        arr[k] = temp[k];
}

void merge_recursive(int* arr, int* temp, int left, int right) {
    if (left >= right) return;

    if (right - left + 1 <= 10) {
        insertion_sort(arr, left, right);
        return;
    }

    int mid = left + (right - left) / 2;
    merge_recursive(arr, temp, left, mid);
    merge_recursive(arr, temp, mid + 1, right);

    merge(arr, temp, left, mid, right);
}

void merge_sort(int* arr, int size) {
    int* temp = (int*)malloc(size * sizeof(int));
    if (temp == NULL) return;
    merge_recursive(arr, temp, 0, size - 1);
    free(temp);
}

/* HEAP SORT */

void heapify_down_iterative(int* arr, int size, int idx) {
    int largest;
    int left;
    int right;

    while (1) {
        largest = idx;
        left = idx * 2 + 1;
        right = idx * 2 + 2;

        if (left < size && arr[left] > arr[largest])
            largest = left;
        if (right < size && arr[right] > arr[largest])
            largest = right;

        if (largest == idx) break;

        swap(&arr[idx], &arr[largest]);
        idx = largest;
    }
}

void heap_sort(int* arr, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify_down_iterative(arr, size, i);

    for (int i = size - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify_down_iterative(arr, i, 0);
    }
}

/* CYCLE SORT */

void cycle_sort(int* arr, int left, int right) {
    int i = left;

    while (i < right) {
        if (arr[i] >= left && arr[i] <= right && arr[arr[i]] != arr[i])
            swap(&arr[i], &arr[arr[i]]);
        else i++;
    }
}

int main() {
    return 0;
}