#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct Node {
    int data;
    int count;
    int height;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct {
    Node* root;
} Tree;

bool empty(Tree* bst) {
    return (bst == NULL || bst->root == NULL);
}

void _insert(Node** node, int value) {
    Node** current = node;

    while (*current && (*current)->data != value)
        if (value < (*current)->data)
            current = &((*current)->left);
        else
            current = &((*current)->right);

    if (*current) {
        (*current)->count++;
        return;
    }

    *current = (Node*)malloc(sizeof(Node));
    if (!(*current)) return;
    (*current)->data = value;
    (*current)->count = 1;
    (*current)->left = NULL;
    (*current)->right = NULL;
}

void insert_bst(Tree* bst, int value) {
    if (!bst) return;
    _insert(&(bst->root), value);
}

void _remove(Node** node, int value) {
    Node** current = node;

    while (*current && (*current)->data != value)
        if (value < (*current)->data)
            current = &((*current)->left);
        else
            current = &((*current)->right);

    if (!(*current)) return;
    if ((--(*current)->count) > 0) return; 

    Node* target = *current;
    if (!(*current)->left) {
        *current = target->right;
        free(target);
    } else if (!(*current)->right) {
        *current = target->left;
        free(target);
    } else {
        Node** predecessor = &((*current)->left);
        while ((*predecessor)->right) predecessor = &((*predecessor)->right);

        target->data = (*predecessor)->data;
        target->count = (*predecessor)->count;

        Node* temp = *predecessor;
        *predecessor = (*predecessor)->left;
        free(temp);
    }
}

void remove_bst(Tree* bst, int value) {
    if (empty(bst)) return;
    _remove(&(bst->root), value);
}

bool search(Tree* bst, int value) {
    Node* current = bst->root;

    while (current && current->data != value)
        if (value < current->data)
            current = current->left;
        else
            current = current->right;

    return (current != NULL);
}

int _height(Node* node) {
    if (!node) return 0;
    return (1 + MAX(_height(node->left), _height(node->right)));
}

int height(Tree* bst) {
    return _height(bst->root);
}

void _in_order(Node* node) {
    if (node) {
        _in_order(node->left);
        printf("%d ", node->data);
        _in_order(node->right);
    }
}

void in_order(Tree* bst) {
    if (empty(bst)) {
        printf("Tree is empty!\n");
        return;
    }
    _in_order(bst->root);
    printf("\n");
}

void _pre_order(Node* node) {
    if (node) {
        printf("%d ", node->data);
        _pre_order(node->left);
        _pre_order(node->right);
    }
}

void pre_order(Tree* bst) {
    if (empty(bst)) {
        printf("Tree is empty!\n");
        return;
    }
    _pre_order(bst->root);
    printf("\n");
}

void _post_order(Node* node) {
    if (node) {
        _post_order(node->left);
        _post_order(node->right);
        printf("%d ", node->data);
    }
}

void post_order(Tree* bst) {
    if (empty(bst)) {
        printf("Tree is empty!\n");
        return;
    }
    _post_order(bst->root);
    printf("\n");
}

Tree* create_bst() {
    Tree* bst = (Tree*)malloc(sizeof(Tree));
    if (bst)
        bst->root = NULL;
    return bst;
}

void delete_node(Node* node) {
    if (node) {
        delete_node(node->left);
        delete_node(node->right);
        free(node);
    }
}

void delete_bst(Tree* bst) {
    delete_node(bst->root);
    free(bst);
}
