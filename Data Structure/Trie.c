#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct Node {
    struct Node* children[ALPHABET_SIZE];
    bool isEnd;
} Node;

typedef struct {
    Node* root;
} Trie;

Node* createNode() {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node) {
        node->isEnd = false;
        memset(node->children, 0, sizeof(node->children));
    }
    return node;
}

void insert(Trie* trie, char* word) {
    Node* current = trie->root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (current->children[index] == NULL) {
            Node* child = createNode();
            current->children[index] = child;
        }
        current = current->children[index];
    }
    current->isEnd = true;
}

bool search(Trie* trie, char* word) {
    if (word[0] == '\0') return false;
    
    Node* current = trie->root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (current->children[index] == NULL)
            return false;
        current = current->children[index];
    }
        
    return current->isEnd;
}

bool startsWith(Trie* trie, char* prefix) {
    if (prefix[0] == '\0') return true;

    Node* current = trie->root;

    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';

        if (current->children[index] == NULL)
            return false;
        current = current->children[index];
    }

    return true;
}

Trie* createTrie() {
    Trie* trie = (Trie*)malloc(sizeof(Trie));
    if (trie) trie->root = createNode();

    return trie;
}

void deleteNode(Node* node) {
    if (node == NULL) return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->children[i] != NULL)
            deleteNode(node->children[i]);

    free(node);
}

void deleteTrie(Trie* trie) {
    deleteNode(trie->root);
    free(trie);
}

int main() {
    return 0;
}
