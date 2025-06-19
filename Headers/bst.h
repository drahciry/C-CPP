#ifndef BST_H
#define BST_H

// Struct Node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Struct BST
typedef struct {
    Node* root;
    int len;
} BST;

// Protótipos
BST* createBST();
int isEmptyBST(BST* bst);
void insertBST(BST* bst, int value);
void _insertBST(Node* nodeBST, Node* newNode);
int* realocArray(int* arr, int* cap);
int* preOrder(BST* bst);
void _preOrder(Node* node, int* elements, int* len, int* cap);
int* inOrder(BST* bst);
void _inOrder(Node* node, int* elements, int* len, int* cap);
int* postOrder(BST* bst);
void _postOrder(Node* node, int* elements, int* len, int* cap);
int remove(BST* bst, int value);
Node* _removeBST(Node* node, int value, int* search);
Node* search(BST* bst, int value);
Node* _search(Node* node, int value);
void deleteNodes(Node* node);
void deleteBST(BST* bst);
void printTree(Node* node, int level);

#endif