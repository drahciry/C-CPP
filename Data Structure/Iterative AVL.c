#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    int count;
    int height;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

typedef struct {
    Node* root;
} Tree;

static inline int MAX(int a, int b) {
    return (a > b) ? a : b;
}

static inline int GET_HEIGHT(Node* node) {
    return (node == NULL) ? -1 : node->height;
}

bool empty(Tree* avl) {
    return (avl == NULL || avl->root == NULL);
}

int get_balance(Node* node) {
    return (node == NULL) ? 0 : GET_HEIGHT(node->left) - GET_HEIGHT(node->right);
}

Node* create_node(Node* parent, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node) {
        new_node->data = value;
        new_node->count = 1;
        new_node->height = 0;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = parent;
    }
    return new_node;
}

void rotate_right(Tree* avl, Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;
    
    y->height = MAX(GET_HEIGHT(y->left), GET_HEIGHT(y->right)) + 1;
    x->height = MAX(GET_HEIGHT(x->left), GET_HEIGHT(x->right)) + 1;
    
    x->parent = y->parent;
    y->parent = x;

    if (T2 != NULL) T2->parent = y;

    if (x->parent != NULL)
        if (y == x->parent->left)
            x->parent->left = x;
        else
            x->parent->right = x;
    else avl->root = x;
}

void rotate_left(Tree* avl, Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = MAX(GET_HEIGHT(x->left), GET_HEIGHT(x->right)) + 1;
    y->height = MAX(GET_HEIGHT(y->left), GET_HEIGHT(y->right)) + 1;

    y->parent = x->parent;
    x->parent = y;

    if (T2 != NULL) T2->parent = x;

    if (y->parent != NULL)
        if (x == y->parent->left)
            y->parent->left = y;
        else
            y->parent->right = y;
    else avl->root = y;
}

void insert_avl(Tree* avl, int value) {
    if (avl == NULL) return;

    Node* current = avl->root;
    Node* parent = NULL;

    while (current && current->data != value) {
        parent = current;
        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current) {
        current->count++;
        return;
    }

    current = create_node(parent, value);

    if (parent == NULL)
        avl->root = current;
    else if (value < parent->data)
        parent->left = current;
    else
        parent->right = current;

    Node* walker = current;

    while (walker != NULL) {
        walker->height = MAX(GET_HEIGHT(walker->left), GET_HEIGHT(walker->right)) + 1;
        
        int balance = get_balance(walker);

        if (balance > 1 && value < walker->left->data)
            rotate_right(avl, walker);

        else if (balance < -1 && value > walker->right->data)
            rotate_left(avl, walker);
        
        else if (balance > 1 && value > walker->left->data) {
            rotate_left(avl, walker->left);
            rotate_right(avl, walker);
        }
        
        else if (balance < -1 && value < walker->right->data) {
            rotate_right(avl, walker->right);
            rotate_left(avl, walker);
        }
        
        walker = walker->parent;
    }
}

void remove_avl(Tree* avl, int value) {
    Node* current = avl->root;
    Node* parent = NULL;

    while (current && current->data != value) {
        parent = current;
        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL) return;
    if ((--current->count) > 0) return;

    Node* target = current;
    if (!target->left) {
        current = target->right;
        free(target);
    } else if (!target->right) {
        current = target->left;
        free(target);
    } else {
        Node* predecessor = current->left;
        while (predecessor->right) predecessor = predecessor->right;

        target->data = predecessor->data;
        target->count = predecessor->count;

        Node* temp = predecessor;
        predecessor = predecessor->left;
        free(temp);
    }
}

bool search(Tree* avl, int value) {
    Node* current = avl->root;

    while (current != NULL && current->data != value)
        if (value < current->data)
            current = current->left;
        else
            current = current->right;

    return (current != NULL);
}

void _in_order(Node* node) {
    if (node) {
        _in_order(node->left);
        printf("%d ", node->data);
        _in_order(node->right);
    }
}

void in_order(Tree* avl) {
    if (!empty(avl)) _in_order(avl->root);
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

void pre_order(Tree* avl) {
    if (!empty(avl)) _pre_order(avl->root);
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

void post_order(Tree* avl) {
    if (!empty(avl)) _post_order(avl->root);
    else printf("Tree is empty!");
    printf("\n");
}

Tree* create_avl() {
    Tree* avl = (Tree*)malloc(sizeof(Tree));
    if (avl) {
        avl->root = NULL;
    }
    return avl;
}

void delete_node(Node* node) {
    if (node) {
        delete_node(node->left);
        delete_node(node->right);
        free(node);
    }
}

void delete_avl(Tree* avl) {
    delete_node(avl->root);
    free(avl);
}

int main() {
    return 0;
}