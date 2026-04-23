#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define GET_HEIGHT(n) ((n) == NULL ? -1 : (n)->height)

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

bool empty(Tree* avl) {
    return (avl == NULL || avl->root == NULL);
}

int get_balance(Node* node) {
    if (node == NULL) return 0;
    return GET_HEIGHT(node->left) - GET_HEIGHT(node->right);
}

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->data = value;
        new_node->count = 1;
        new_node->height = 0;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

Node* rotate_right(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = MAX(GET_HEIGHT(y->left), GET_HEIGHT(y->right)) + 1;
    x->height = MAX(GET_HEIGHT(x->left), GET_HEIGHT(x->right)) + 1;

    return x;
}

Node* rotate_left(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = MAX(GET_HEIGHT(x->left), GET_HEIGHT(x->right)) + 1;
    y->height = MAX(GET_HEIGHT(y->left), GET_HEIGHT(y->right)) + 1;

    return y;
}

Node* _insert(Node* node, int value) {
    if (node == NULL) return create_node(value);

    if (value < node->data)
        node->left = _insert(node->left, value);
    else if (value > node->data)
        node->right = _insert(node->right, value);
    else {
        node->count++;
        return node;
    }

    node->height = MAX(GET_HEIGHT(node->left), GET_HEIGHT(node->right)) + 1;

    int balance = get_balance(node);

    if (balance > 1 && value < node->left->data)
        return rotate_right(node);

    if (balance < -1 && value > node->right->data)
        return rotate_left(node);

    if (balance > 1 && value > node->left->data) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (balance < -1 && value < node->left->data) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

void insert_avl(Tree* avl, int value) {
    if (avl != NULL) avl->root = _insert(avl->root, value);
}

Node* get_predecessor(Node* node) {
    Node* current = node;
    while (current->right) current = current->right;
    return current;
}

Node* _remove(Node* node, int value) {
    if (node == NULL) return node;

    if (value < node->data)
        node->left = _remove(node->left, value);
    else if (value > node->data)
        node->right = _remove(node->right, value);
    else {
        if (node->count > 1) {
            node->count--;
            return node;
        }

        if ((node->left == NULL) || (node->right == NULL)) {
            Node* temp = node->left ? node->left : node->right;

            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else {
                *node = *temp;
            }
            free(temp);
        } else {
            Node* temp = get_predecessor(node->left);

            node->data = temp->data;
            node->data = temp->count;
            
            temp->count = 1;
            node->left = _remove(node->left, temp->data);
        }
    }

    if (node == NULL) return node;

    node->height = MAX(GET_HEIGHT(node->left), GET_HEIGHT(node->right)) + 1;
    
    int balance = get_balance(node);

    if (balance > 1 && get_balance(node->left) >= 0)
        return rotate_right(node);

    if (balance < -1 && get_balance(node->left) < 0)
        return rotate_left(node);

    if (balance > 1 && get_balance(node->right) <= 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (balance < -1 && get_balance > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

void remove_avl(Tree* avl, int value) {
    if (!empty(avl)) avl->root = _remove(avl->root, value);
}

bool search(Tree* avl, int value) {
    Node* current = avl->root;

    while (current && current->data != value)
        if (value < current->data)
            current = current->left;
        else
            current = current->right;

    return (current != NULL);
}

int height(Tree* avl) {
    return avl->root->height;
}

void _in_order(Node* node) {
    if (node) {
        _in_order(node->left);
        printf("%d ", node->data);
        _in_order(node->right);
    }
}

void in_order(Tree* avl) {
    if (empty(avl)) {
        printf("Tree is empty!\n");
        return;
    }
    _in_order(avl->root);
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
    if (empty(avl)) {
        printf("Tree is empty!\n");
        return;
    }
    _pre_order(avl->root);
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
    if (empty(avl)) {
        printf("Tree is empty!\n");
        return;
    }
    _post_order(avl->root);
    printf("\n");
}

Tree* create_avl() {
    Tree* avl = (Tree*)malloc(sizeof(Tree));
    if (avl) avl->root = NULL;
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
