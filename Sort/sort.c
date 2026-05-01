#include <stdlib.h>

/* Auxiliary functions */

/*
 * Algorithm: Swap integers
 * Time Complexity: O(1)
 * Memory Complexity: O(1)
 */

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Algorithm: Floor of log2
 * Time Complexity: O(N) - N is number of bits until most significant bit
 * Memory Complexity: O(1)
 */

int log2_int(unsigned int n) {
    int log = 0;
    if (n == 0) return -1;
    while (n >>= 1) log++;
    return log;
}

/*
 * Algorithm: Merge left side of array with right side
 * Time Complexity: O(N)
 * Memory Complexity: O(1)
 */

void merge(int* arr, int* temp, int left, int mid, int right) {
    int i = left;
    int k = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
        if (arr[i] <= arr[j])
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

/*
 * Algorithm: Heapify Down in Array
 * Time Complexity: O(log N)
 * Memory Complexity: O(1)
 */

void heapify_arr(int* arr, int size, int idx) {
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

/*
 * Algorithm: Median of Three Numbers
 * Time Complexity: O(1)
 * Memory Complexity: O(1)
 */

void median_of_three(int* arr, int left, int right) {
    if (right - left < 2) return;

    int mid = left + (right - left) / 2;

    if (arr[left] > arr[mid]) swap(&arr[left], &arr[mid]);
    if (arr[left] > arr[right]) swap(&arr[left], &arr[right]);
    if (arr[mid] > arr[right]) swap(&arr[mid], &arr[right]);

    swap(&arr[mid], &arr[left]);
}

/*
 * Algorithm: Partition Array
 * Time Complexity: O(N)
 * Memory Complexity: O(1)
 */

int partition(int* arr, int left, int right) {
    median_of_three(arr, left, right);

    int pivot = arr[left];

    int i = left - 1;
    int j = right + 1;

    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) return j;

        swap(&arr[i], &arr[j]);
    }
}

/* Sort Functions */

/*
 * Algorithm: Bubble Sort
 * Time Complexity: O(N²) in worse case | O(N) in best case
 * Memory Complexity: O(1)
 */

void _bubble_sort(int* arr, int left, int right) {
    for (int i = left; i <= right; i++) {
        char changed = 0;
        for (int j = left; j <= right - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                changed = 1;
            }
        }
        if (!changed) break;
    }
}

void bubble_sort(int* arr, int size) {
    if (size > 1) _bubble_sort(arr, 0, size - 1);
}

/*
 * Algorithm: Insertion Sort
 * Time Complexity: O(N²) in worse case | O(N) in best case
 * Memory Complexity: O(1)
 */

void _insertion_sort(int* arr, int left, int right) {
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

void insertion_sort(int* arr, int size) {
    if (size > 1) _insertion_sort(arr, 0, size - 1);
}

/*
 * Algorithm: Merge Sort
 * Time Complexity: O(N log N)
 * Memory Complexity: O(N)
 */

void merge_recursive(int* arr, int* temp, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    merge_recursive(arr, temp, left, mid);
    merge_recursive(arr, temp, mid + 1, right);

    merge(arr, temp, left, mid, right);
}

void _merge_sort(int* arr, int left, int right) {
    int* temp = (int*)malloc((right - left + 1) * sizeof(int));
    if (temp == NULL) return;
    merge_recursive(arr, temp, left, right);
    free(temp);
}

void merge_sort(int* arr, int size) {
    if (size > 1) _merge_sort(arr, 0, size - 1);
}

/*
 * Algorithm: Heap Sort
 * Time Complexity: O(N log N)
 * Memory Complexity: O(1)
 */

void heap_sort_iterative(int* arr, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify_down_iterative(arr, size, i);

    for (int i = size - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify_down_iterative(arr, i, 0);
    }
}

void _heap_sort(int* arr, int left, int right) {
    int partition_size = right - left + 1;
    heap_sort_iterative(arr + left, partition_size);
}

void heap_sort(int* arr, int size) {
    if (size > 1) _heap_sort(arr, 0, size - 1);
}

/*
 * Algorithm: Quick Sort
 * Time Complexity: O(N²) in worse case | O(N log N) in best case
 * Memory Complexity: O(N)
 */

void _quick_sort(int* arr, int left, int right) {
    if (left < right) {
        int split_index = partition(arr, left, right);
        _quick_sort(arr, left, split_index);
        _quick_sort(arr, split_index + 1, right);
    }
}

/*
 * Algorithm: Intro Sort
 * Time Complexity: O(N log N)
 * Memory Complexity: O(log N)
 */

void _intro_sort(int* arr, int left, int right, int depth) {
    while (left < right) {
        if (right - left < 10) {
            _insertion_sort(arr, left, right);
            return;
        }

        if (depth == 0) {
            _heap_sort(arr, left, right);
            return;
        }

        int split_index = partition(arr, left, right);
        int left_size = split_index - left;
        int right_size = right - split_index;

        if (left_size < right_size) {
            _intro_sort(arr, left, split_index, depth - 1);
            left = split_index + 1;
        } else {
            _intro_sort(arr, split_index + 1, right, depth - 1);
            right = split_index;
        }
    }
}

void intro_sort(int* arr, int size) {
    if (size > 1) _intro_sort(arr, 0, size - 1, log2_int(size));
}

/*
 * Algorithm: Hybrid Sort
 * Time Complexity: O(N log N)
 * Memory Complexity: O(N)
 */

void hybrid_recursive(int* arr, int* temp, int left, int right) {
    if (left >= right) return;

    if (right - left < 10) {
        _insertion_sort(arr, left, right);
        return;
    }

    int mid = left + (right - left) / 2;
    hybrid_recursive(arr, temp, left, mid);
    hybrid_recursive(arr, temp, mid + 1, right);

    merge(arr, temp, left, mid, right);
}

void _hybrid_sort(int* arr, int left, int right) {
    int* temp = (int*)malloc((right - left + 1) * sizeof(int));
    if (temp == NULL) return;
    hybrid_recursive(arr, temp, left, right);
    free(temp);
}

void hybrid_sort(int* arr, int size) {
    if (size > 1) _hybrid_sort(arr, 0, size - 1);
}

/*
 * Algorithm: Cycle Sort
 * Time Complexity: O(N)
 * Memory Complexity: O(1)
 */

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