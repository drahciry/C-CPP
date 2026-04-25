#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static inline int MAX(int a, int b) {
    return (a > b) ? a : b;
}

typedef struct Node {
    int data;
    int count;
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

    *current = create_node(value);
}

void insert_bst(Tree* bst, int value) {
    if (bst != NULL) _insert(&(bst->root), value);
}

void _remove(Node** node, int value) {
    Node** current = node;

    while (*current && (*current)->data != value)
        if (value < (*current)->data)
            current = &((*current)->left);
        else
            current = &((*current)->right);

    if (*current == NULL) return;
    if ((--(*current)->count) > 0) return;

    Node* target = *current;
    if (!target->left) {
        current = &(target->right);
        free(target);
    } else if (!target->right) {
        current = &(target->left);
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
    if (!empty(bst)) _remove(&(bst->root), value);
}

bool search(Tree* bst, int value) {
    Node* current = bst->root;

    while (current != NULL && current->data != value)
        if (value < current->data)
            current = current->left;
        else
            current = current->right;

    return (current != NULL);
}

int _height(Node* node) {
    return (node == NULL) ? -1 : MAX(_height(node->left), _height(node->right)) + 1;
}

int height(Tree* bst) {
    return (empty(bst)) ? -1 : _height(bst->root);
}

void _in_order(Node* node) {
    if (node) {
        _in_order(node->left);
        printf("%d ", node->data);
        _in_order(node->right);
    }
}

void in_order(Tree* bst) {
    if (!empty(bst)) _in_order(bst->root);
    else printf("Tree is empty!");
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
    if (!empty(bst)) _pre_order(bst->root);
    else printf("Tree is empty!");
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
    if (!empty(bst)) _post_order(bst->root);
    else printf("Tree is empty!");
    printf("\n");
}

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node) {
        new_node->data = value;
        new_node->count = 1;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

Tree* create_bst() {
    Tree* bst = (Tree*)malloc(sizeof(Tree));
    if (bst) {
        bst->root = NULL;
    }
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

int main() {
    return 0;
}