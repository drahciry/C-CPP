// Includes
#include <stdlib.h>

// Bubble Sort
void BubbleSort(int* arr, int len) {
    int changed, temp;
    for (int i = 0; i < len; i++) {
        changed = 0;
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                changed = 1;
            }
        }
        if (!changed) break;
    }
}

// Insertion Sort
void InsertionSort(int* arr, int len) {
    int key, j;
    for (int i = 1; i < len; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort
void Merge(int* arr, int* aux, int left, int mid, int right) { 
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) aux[k++] = arr[i++];
        else aux[k++] = arr[j++];
    }

    while (i <= mid) aux[k++] = arr[i++];

    while (j <= right) aux[k++] = arr[j++];

    for (int l = left; l <= right; l++) arr[l] = aux[l];
}

void MergeSortRec(int* arr, int* aux, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    MergeSortRec(arr, aux, left, mid);
    MergeSortRec(arr, aux, mid + 1, right);
    Merge(arr, aux, left, mid, right);
}

void MergeSort(int* arr, int len) {
    int* aux = malloc(len * sizeof(int));
    if (!aux) return;
    MergeSortRec(arr, aux, 0, len - 1);
    free(aux);
}

// Função principal (main)
int main() {
    return 0;
}