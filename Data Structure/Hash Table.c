#include <stdbool.h>
#include <stdlib.h>

#define EMPTY 0
#define OCCUPIED 1
#define DELETED 2

typedef struct {
    int *keys;
    int *items;
    char *status;
    int R;
    int length;
    int inserteds;
} HashTable;

bool is_prime(int num) {
    if (num == 1) return false;
    for (int divisor = 2; divisor * divisor <= num; divisor++)
        if (num % divisor == 0) return false;
    return true;
}

int first_prime_before(int size) {
    int prime = size - 1;

    while (prime >= 2) {
        if (is_prime(prime))
            return prime;
        prime--;
    }
    return 2;
}

int first_prime_after(int size) {
    int prime = size + 1;

    while (true) {
        if (is_prime(prime))
            return prime;
        prime++;
    }
}

HashTable* create_hash_table(int size) {
    HashTable *hash_table = malloc(sizeof(HashTable));

    hash_table->length = first_prime_after(size);
    hash_table->items = malloc(hash_table->length * sizeof(int));
    hash_table->keys = malloc(hash_table->length * sizeof(int));
    hash_table->status = calloc(hash_table->length, sizeof(char));
    hash_table->inserteds = 0;
    hash_table->R = first_prime_before(size);

    return hash_table;
}

int hash1(HashTable *hash_table, int key) {
    int k = key < 0 ? -key : key;
    return (k % hash_table->length);
}

int hash2(HashTable *hash_table, int key) {
    int k = key < 0 ? -key : key;
    return (hash_table->R - (k % hash_table->R));
}

int double_hash(HashTable *hash_table, int key, int attempt) {
    return ((hash1(hash_table, key) + attempt * hash2(hash_table, key)) % hash_table->length);
}

void insert_item(HashTable *hash_table, int key, int item) {
    if (hash_table->inserteds >= hash_table->length) {
        return;
    }

    int hash;
    int first_deleted_index = -1;

    for (int attempt = 0; attempt < hash_table->length; attempt++) {
        hash = double_hash(hash_table, key, attempt);
        if (hash_table->status[hash] == EMPTY)
            break;
        if (hash_table->status[hash] == OCCUPIED) {
            if (hash_table->keys[hash] == key) {
                hash_table->items[hash] = item;
                return;
            }
            continue;
        }
        if (hash_table->status[hash] == DELETED) {
            if (first_deleted_index == -1) {
                first_deleted_index = hash;
            }
        }
    }

    if (first_deleted_index != -1) {
        hash = first_deleted_index;
    }

    hash_table->inserteds++;
    hash_table->keys[hash] = key;
    hash_table->items[hash] = item;
    hash_table->status[hash] = OCCUPIED;
}

bool get_item(HashTable *hash_table, int key, int *out_item) {
    int hash;

    for (int attempt = 0; attempt < hash_table->length; attempt++) {
        hash = double_hash(hash_table, key, attempt);
        if (hash_table->status[hash] == EMPTY)
            return false;
        if ((hash_table->status[hash] == OCCUPIED) && (hash_table->keys[hash] == key)) {
            *out_item = hash_table->items[hash];
            return true;
        }
    }

    return false;
}

bool delete_item(HashTable *hash_table, int key) {
    int hash;

    for (int attempt = 0; attempt < hash_table->length; attempt++) {
        hash = double_hash(hash_table, key, attempt);
        if (hash_table->status[hash] == EMPTY)
            return false;
        if ((hash_table->status[hash] == OCCUPIED) && (hash_table->keys[hash] == key)) {
            hash_table->status[hash] = DELETED;
            hash_table->inserteds--;
            return true;
        }
    }

    return false;
}

void free_hash_table(HashTable *hash_table) {
    free(hash_table->keys);
    free(hash_table->items);
    free(hash_table->status);
    free(hash_table);
}

int main() {
  return 0;
}
