#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define EMPTY 0
#define OCCUPIED 1
#define DELETED 2

typedef struct {
    char** keys;
    int* items;
    char* status;
    unsigned long long R;
    unsigned long long size;
    unsigned long long inserteds;
} HashTable;

bool isPrime(unsigned long long num) {
    if (num == 1) return false;
    for (unsigned long long divisor = 0; divisor * divisor <= num; divisor++)
        if (num % divisor == 0) return false;
    return true;
}

unsigned long long primeBefore(unsigned long long size) {
    unsigned long long prime = size - 1;
    while (prime > 2) {
        if (isPrime(prime))
            return prime;
        prime--;
    }
    return 2;
}

unsigned long long primeAfter(unsigned long long size) {
    unsigned long long prime = size + 1;
    while (true) {
        if (isPrime(prime))
            return prime;
        prime++;
    }
}

unsigned long long djb2(unsigned char* str) {
    unsigned long long hash = 5381;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

unsigned long long hash1(HashTable* hash_table, char* key) {
    unsigned long long k = djb2((unsigned char*)key);
    return (k % hash_table->size);
}

unsigned long long hash2(HashTable* hash_table, char* key) {
    unsigned long long k = djb2((unsigned char*)key);
    return (hash_table->R - (k % hash_table->R));
}

unsigned long long doubleHash(HashTable* hash_table, char* key, unsigned long long attempt) {
    return ((hash1(hash_table, key) + attempt * hash2(hash_table, key)) % hash_table->size);
}

HashTable* createHashTable(unsigned long long size) {
    HashTable* hash_table = (HashTable*)malloc(sizeof(HashTable));
    if (hash_table) {
        hash_table->inserteds = 0;
        hash_table->size = primeAfter(size);
        hash_table->R = primeBefore(hash_table->size);
        hash_table->keys = (char**)calloc(hash_table->size, sizeof(char*));
        hash_table->items = (int*)malloc(hash_table->size * sizeof(int));
        hash_table->status = (char*)calloc(hash_table->size, sizeof(char));
    }
    return hash_table;
}

void deleteHashTable(HashTable* hash_table) {
    for (unsigned long long i = 0; i < hash_table->size; i++)
        if (hash_table->keys[i] != NULL)
            free(hash_table->keys[i]);
    free(hash_table->keys);
    free(hash_table->items);
    free(hash_table->status);
    free(hash_table);
}

void insertItemInternal(HashTable* hash_table, char* key, int item, bool isRehashing);

void rehash(HashTable* hash_table) {
    unsigned long long old_size = hash_table->size;
    unsigned long long new_size = primeAfter(old_size * 2);

    char** old_keys = hash_table->keys;
    int* old_items = hash_table->items;
    char* old_status = hash_table->status;

    hash_table->size = new_size;
    hash_table->R = primeBefore(hash_table->size);
    hash_table->inserteds = 0;

    hash_table->keys = (char**)calloc(hash_table->size, sizeof(char*));
    hash_table->items = (int*)malloc(hash_table->size * sizeof(int));
    hash_table->status = (char*)calloc(hash_table->size, sizeof(char));

    for (unsigned long long i = 0; i < old_size; i++) {
        if (old_status[i] == OCCUPIED)
            insertItemInternal(hash_table, old_keys[i], old_items[i], true);
        else if (old_status[i] == DELETED)
            free(old_keys[i]);
    }

    free(old_keys);
    free(old_items);
    free(old_status);
}

void insertItemInternal(HashTable* hash_table, char* key, int item, bool isRehashing) {
    double loadFactor = (double)hash_table->inserteds / hash_table->size;
    if (loadFactor >= 0.75)
        rehash(hash_table);

    unsigned long long hash;
    unsigned long long deletedHash;
    bool findDeletedHash = false;
    for (unsigned long long attempt = 0; attempt < hash_table->size; attempt++) {
        hash = doubleHash(hash_table, key, attempt);
        if (hash_table->status[hash] == EMPTY) {
            break;
        } else if (hash_table->status[hash] == OCCUPIED) {
            if (strcmp(key, hash_table->keys[hash]) == 0) {
                hash_table->items[hash] = item;
                if (isRehashing) free(key);
                return;
            }
        } else {
            if (!findDeletedHash) {
                findDeletedHash = true;
                deletedHash = hash;
            }
        }
    }

    if (findDeletedHash) {
        hash = deletedHash;
        free(hash_table->keys[hash]);
    }

    if (isRehashing)
        hash_table->keys[hash] = key;
    else
        hash_table->keys[hash] = strdup(key);

    hash_table->inserteds++;
    hash_table->items[hash] = item;
    hash_table->status[hash] = OCCUPIED;
}

void insertItem(HashTable* hash_table, char* key, int item) {
    insertItemInternal(hash_table, key, item, false);
}

bool getItem(HashTable* hash_table, char* key, int* out_item) {
    for (unsigned long long attempt = 0; attempt < hash_table->size; attempt++) {
        unsigned long long hash = doubleHash(hash_table, key, attempt);
        if (hash_table->status[hash] == EMPTY) {
            return false;
        } else if ((hash_table->status[hash] == OCCUPIED) && (strcmp(key, hash_table->keys[hash]) == 0)) {
            *out_item = hash_table->items[hash];
            return true;
        }
    }
    return false;
}

bool deleteItem(HashTable* hash_table, char* key) {
    for (unsigned long long attempt = 0; attempt < hash_table->size; attempt++) {
        unsigned long long hash = doubleHash(hash_table, key, attempt);
        if (hash_table->status[hash] == EMPTY) {
            return false;
        } else if ((hash_table->status[hash] == OCCUPIED) && (strcmp(key, hash_table->keys[hash]) == 0)) {
            hash_table->status[hash] == DELETED;
            hash_table->inserteds--;
            return true;
        }
    }
    return false;
}
