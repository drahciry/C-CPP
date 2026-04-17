#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

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

int main() {
    return 0;
}