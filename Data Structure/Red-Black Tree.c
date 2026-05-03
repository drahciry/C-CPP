#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    RED,
    BLACK
} NodeColor;

typedef struct Node {
    int data;
    int count;
    NodeColor color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

typedef struct {
    Node* root;
    Node* NIL;
} RBTree;

bool empty(RBTree* tree) {
    return (tree == NULL || tree->root == tree->NIL);
}

Node* create_nil() {
    Node* NIL = (Node*)malloc(sizeof(Node));
    if (NIL) {
        NIL->data = 0;
        NIL->color = BLACK;
    }
    return NIL;
}

Node* create_node(RBTree* tree, int value) {
    if (tree == NULL) return NULL;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) return tree->NIL;

    new_node->data = value;
    new_node->count = 1;
    new_node->color = RED;
    new_node->left = tree->NIL;
    new_node->right = tree->NIL;
    new_node->parent = tree->NIL;

    return new_node;
}

void right_rotate(RBTree* tree, Node* y) {
    Node* x = y->left;

    y->left = x->right;
    if (y->left != tree->NIL)
        y->left->parent = y;

    x->parent = y->parent;
    if (y->parent == tree->NIL)
        tree->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void left_rotate(RBTree* tree, Node* x) {
    Node* y = x->right;

    x->right = y->left;
    if (x->right != tree->NIL)
        x->right->parent = x;

    y->parent = x->parent;
    if (x->parent == tree->NIL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void insert_fixup(RBTree* tree, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* uncle = z->parent->parent->right;

            if (uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }

            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(tree, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(tree, z->parent->parent);
            }
        }

        else {
            Node* uncle = z->parent->parent->left;

            if (uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }

            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(tree, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(tree, z->parent->parent);
            }
        }
    }

    tree->root->color = BLACK;
}

void insert_rbt(RBTree* tree, int value) {
    if (tree == NULL) return;

    Node* current = tree->root;
    Node* parent = tree->NIL;

    while (current != NULL && current != tree->NIL && current->data != value) {
        parent = current;
        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current != NULL && current != tree->NIL) {
        current->count++;
        return;
    }

    Node* z = create_node(tree, value);
    if (z == tree->NIL) return;

    z->parent = parent;
    if (parent == tree->NIL)
        tree->root = z;
    else if (value < parent->data)
        parent->left = z;
    else
        parent->right = z;

    insert_fixup(tree, z);
}

Node* search_node(RBTree* tree, int value) {
    if (empty(tree)) return tree->NIL;

    Node* current = tree->root;

    while (current != NULL && current != tree->NIL && current->data != value)
        if (value < current->data)
            current = current->left;
        else
            current = current->right;

    return current;
}

Node* get_predecessor(RBTree* tree, Node* node) {
    Node* current = node;
    while (current->right != NULL && current->right != tree->NIL)
        current = current->right;
    return current;
}

void transplant_rbt(RBTree* tree, Node* u, Node* v) {
    if (u->parent == tree->NIL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

void remove_fixup(RBTree* tree, Node* x) {
    Node* bro;

    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            bro = x->parent->right;

            if (bro->color == RED) {
                bro->color = BLACK;
                x->parent->color = RED;
                left_rotate(tree, x->parent);
                bro = x->parent->right;
            }

            if (bro->left->color == BLACK && bro->right->color == BLACK) {
                bro->color = RED;
                x = x->parent;
            }

            else {
                if (bro->right->color == BLACK) {
                    bro->color = RED;
                    bro->left->color = BLACK;
                    right_rotate(tree, bro);
                    bro = x->parent->right;
                }

                bro->color = x->parent->color;
                x->parent->color = BLACK;
                bro->right->color = BLACK;
                left_rotate(tree, x->parent);
                x = tree->root;
            }
        }

        else {
            bro = x->parent->left;

            if (bro->color == RED) {
                bro->color = BLACK;
                x->parent->color = RED;
                right_rotate(tree, x->parent);
                bro = x->parent->left;
            }

            if (bro->left->color == BLACK && bro->right->color == BLACK) {
                bro->color = RED;
                x = x->parent;
            }

            else {
                if (bro->left->color == BLACK) {
                    bro->color = RED;
                    bro->right->color = BLACK;
                    left_rotate(tree, bro);
                    bro = x->parent->left;
                }

                bro->color = x->parent->color;
                x->parent->color = BLACK;
                bro->left->color = BLACK;
                right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }

    x->color = BLACK;
}

void remove_rbt(RBTree* tree, Node* z) {
    Node* y = z;
    Node* x;
    NodeColor y_original_color = y->color;

    if (z->left == tree->NIL) {
        x = z->right;
        transplant_rbt(tree, z, x);
    } else if (z->right == tree->NIL) {
        x = z->left;
        transplant_rbt(tree, z, x);
    } else {
        y = get_predecessor(tree, z->left);
        y_original_color = y->color;
        x = y->left;

        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant_rbt(tree, y, x);
            y->left = z->left;
            y->left->parent = y;
        }

        transplant_rbt(tree, z, y);
        y->right = z->right;
        y->right->parent = y;
        y->color = z->color;
    }

    free(z);

    if (y_original_color == BLACK)
        remove_fixup(tree, x);
}

void remove_value(RBTree* tree, int value) {
    if (empty(tree)) return;

    Node* target = search_node(tree, value);

    if (target == tree->NIL) return;

    if (target->count > 1) {
        target->count--;
        return;
    }

    remove_rbt(tree, target);
}

void _in_order(RBTree* tree, Node* node) {
    if (node != NULL && node != tree->NIL) {
        _in_order(tree, node->left);
        printf("%d ", node->data);
        _in_order(tree, node->right);
    }
}

void in_order(RBTree* tree) {
    if (empty(tree)) printf("Tree is empty!");
    else _in_order(tree, tree->root);
    printf("\n");
}

void _pre_order(RBTree* tree, Node* node) {
    if (node != NULL && node != tree->NIL) {
        printf("%d ", node->data);
        _pre_order(tree, node->left);
        _pre_order(tree, node->right);
    }
}

void pre_order(RBTree* tree) {
    if (empty(tree)) printf("Tree is empty!");
    else _pre_order(tree, tree->root);
    printf("\n");
}

void _post_order(RBTree* tree, Node* node) {
    if (node != NULL && node != tree->NIL) {
        _post_order(tree, node->left);
        _post_order(tree, node->right);
        printf("%d ", node->data);
    }
}

void post_order(RBTree* tree) {
    if (empty(tree)) printf("Tree is empty!");
    else _post_order(tree, tree->root);
    printf("\n");
}

RBTree* create_rbt() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    if (tree == NULL) return NULL;

    tree->NIL = create_nil();
    if (tree->NIL == NULL) {
        free(tree);
        return NULL;
    }

    tree->root = tree->NIL;

    return tree;
}

void delete_node(RBTree* tree, Node* node) {
    if (node != NULL && node != tree->NIL) {
        delete_node(tree, node->left);
        delete_node(tree, node->right);
        free(node);
    }
}

void delete_rbt(RBTree* tree) {
    if (tree != NULL) {
        delete_node(tree, tree->root);
        free(tree->NIL);
        free(tree);
    }
}

int main() {
    return 0;
}