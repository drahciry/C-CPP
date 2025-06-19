// Includes
#include <stdio.h>
#include <stdlib.h>

// Tipo Nó
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Tipo Binary Search Tree
typedef struct {
    Node* root;
    int len;
} BST;

// Mensagem de erro para alocação de memória
void MallocError() {
    fprintf(stderr, "Erro: falha ao alocar memória!\n");
    exit(1);
}

// Mensagem de erro para fila vazia
void EmptyBSTError() {
    fprintf(stderr, "Erro: árvore está vazia!\n");
    exit(2);
}

// Mensagem de erro para quando valor já existe na árvore
void ConflitantDataError() {
    fprintf(stderr, "Erro: dado já existe na árvore!\n");
    exit(3);
}

// Inicializa a BST
BST* createBST() {
    // Declaração de variáveis
    BST* bst = malloc(sizeof(BST));
    // Retorna erro caso não seja alocado
    if (!bst) MallocError();

    // Inicializa a BST vazia
    bst->root = NULL;
    bst->len = 0;
    // Retorna a BST
    return bst;
}

// Verifica se a BST está vazia
int isEmptyBST(BST* bst) {
    return (!bst->root);
}

// Insere dados na BST
void insertBST(BST* bst, int value) {
    // Declaração de variáveis
    Node* newNode = malloc(sizeof(Node));
    // Retorna erro caso não seja alocado
    if (!newNode) MallocError();
    
    // Armazena dados no nó
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    // Incrementa tamanho da árvore
    bst->len++;
    // Verifica se BST está vazia
    if (isEmptyBST(bst)) {
        bst->root = newNode;
        return;
    }
    // Se for menor vai para a esquerda
    if (newNode->data < bst->root->data) {
        // Verifica se tem filho na esquerda
        if (!bst->root->left) {
            bst->root->left = newNode;
            return;
        }
        // Chamada de função recursiva
        _insertBST(bst->root->left, newNode);
    // Se for maior vai para direita
    } else if (newNode->data > bst->root->data) {
        // Verifica se tem filho na direita
        if (!bst->root->right) {
            bst->root->right = newNode;
            return;
        }
        // Chamada de função recursiva
        _insertBST(bst->root->right, newNode);
    // Se for igual, retorna erro
    } else {
        ConflitantDataError();
    }
}

// Função recursiva para adicionar dados à BST
void _insertBST(Node* nodeBST, Node* newNode) {
    // Se for menor vai para esquerda
    if (newNode->data < nodeBST->data) {
        // Verifica se tem filho na esquerda
        if (!nodeBST->left) {
            nodeBST->left = newNode;
            return;
        }
        // Chamada recursiva
        _insertBST(nodeBST->left, newNode);
    // Se for maior vai para direita
    } else if (newNode->data > nodeBST->data) {
        // Verifica se tem filho na direita
        if (!nodeBST->right) {
            nodeBST->right = newNode;
            return;
        }
        // Chamada recursiva
        _insertBST(nodeBST->right, newNode);
    // Se for igual, retorna erro
    } else {
        ConflitantDataError();
    }
}

// Função para realocar array
int* realocArray(int* arr, int* cap) {
    // Dobra capacidade
    *cap *= 2;
    // Utilzando array temporário
    int* temp = NULL;
    // Se realocação falhar, tentará até dar sucesso
    while (!temp) temp = realloc(arr, *cap * sizeof(int));
    // Copia o array
    arr = temp;
    // Retorna array realocado
    return arr;
}

// Pre-Order Traversse
int* preOrder(BST* bst) {
    // Declaração de variáveis
    int len = 0, cap = 2;
    int* elements = malloc(cap * sizeof(int));
    // Retorna erro caso alocação falhe
    if (!elements) MallocError();

    // Chama função recursiva
    _preOrder(bst->root, elements, &len, &cap);
    // Retorna array com elementos pre-order
    return elements;
}

// Função recursiva que realiza percurso pre-order
void _preOrder(Node* node, int* elements, int* len, int* cap) {
    // Verifica se nó é nulo
    if (node) {
        // Realoca array caso esteja cheio
        if (*len >= *cap - 1) elements = realocArray(elements, &cap);
        // Visita raíz
        elements[(*len)++] = node->data;
        // Visita sub-árvore da esquerda
        _preOrder(node->left, elements, len, cap);
        // Visita sub-árvore da direita
        _preOrder(node->right, elements, len, cap);
    }
}

// In-Order Traversse
int* inOrder(BST* bst) {
    // Declaração de variáveis
    int len = 0, cap = 2;
    int* elements = malloc(cap * sizeof(int));
    // Retorna erro caso alocação falhe
    if (!elements) MallocError();

    // Chama função recursiva
    _inOrder(bst->root, elements, &len, &cap);
    // Retorna array com elementos in-order
    return elements;
}

// Função recursiva que realiza percurso in-order
void _inOrder(Node* node, int* elements, int* len, int* cap) {
    // Verifica se nó é nulo
    if (node) {
        // Visita sub-árvore da esquerda
        _inOrder(node->left, elements, len, cap);
        // Realoca array caso esteja cheio
        if (*len >= *cap - 1) elements = realocArray(elements, &cap);
        // Visita raíz
        elements[(*len)++] = node->data;
        // Visita sub-árvore da direita
        _inOrder(node->right, elements, len, cap);
    }
}

// Post-Order Traversse
int* postOrder(BST* bst) {
    // Declaração de variáveis
    int len = 0, cap = 2;
    int* elements = malloc(cap * sizeof(int));
    // Retorna erro caso alocação falhe
    if (!elements) MallocError();

    // Chama função recursiva
    _postOrder(bst->root, elements, &len, &cap);
    // Retorna array com elementos in-order
    return elements;
}

// Função recursiva que realiza percurso post-order
void _postOrder(Node* node, int* elements, int* len, int* cap) {
    // Verifica se nó é nulo
    if (node) {
        // Visita sub-árvore da esquerda
        _postOrder(node->left, elements, len, cap);
        // Visita sub-árvore da direita
        _postOrder(node->right, elements, len, cap);
        // Realoca array caso esteja cheio
        if (*len >= *cap - 1) elements = realocArray(elements, &cap);
        // Visita raíz
        elements[(*len)++] = node->data;
    }
}

// Função para remover nó
int remove(BST* bst, int value) {
    // Verifica se BST está vazia
    if (isEmptyBST(bst)) EmptyBSTError();
    // Declaração de variáveis
    int search = 0;
    // Chamada de função recursiva
    bst->root = _removeBST(&bst->root, value, &search);
    // Verifica se removeu para diminuir tamanho
    if (search) bst->len--;
    // Retorna se removeu ou não
    return search;
}

// Função recursiva para deletar nó e reorganizar árvore
Node* _removeBST(Node* node, int value, int* search) {
    // Verifica se nó é nulo
    if (!node) return;
    // Compara chaves
    if (value < node->data) {
        node->left = _removeBST(node->left, value, search);
    } else if (value > node->data) {
        node->right = _removeBST(node->right, value, search);
    } else {
        // Nó encontrado
        *search = 1;
        // Nó não possui filhos
        if (!node->left && !node->right) {
            free(node);
            return NULL;
        }
        // Nó possui filho na direita
        if (!node->left) {
            Node* temp = node->right;
            free(node);
            return temp;
        }
        // Nó possui filho na direita
        if (!node->right) {
            Node* temp = node->left;
            free(node);
            return temp;
        }
        // Nó possui filhos na esquerda e direita
        Node* temp = node->left;
        // Busca o maior nó na sub-árvore da esquerda do nó
        while (temp->right) temp = temp->right;
        // Altera valor do nó
        node->data = temp->data;
        node->left = _removeBST(node->left, temp->data, search);
    }
    return node;
}

// Função para buscar dados
Node* search(BST* bst, int value) {
    // Verifica se árvore está vazia
    if (isEmptyBST(bst)) return NULL;
    // Chamada da função recursiva
    return _search(bst->root, value);
}

// Função recursiva que percorre árvore em busca dos dados
Node* _search(Node* node, int value) {
    // Verifica se nó é nulo
    if (!node) return NULL;
    // Compara chaves
    if (value < node->data) return _search(node->left, value);
    if (value > node->data) return _search(node->right, value);
    // Retorna o nó encontrado
    return node;
}

// Função que libera todos os nós da memória (post-order)
void deleteNodes(Node* node) {
    // Verifica se nó é nulo
    if (node) {
        deleteNodes(node->left);
        deleteNodes(node->right);
        // Libera nó da memória
        free(node);
    }
}

// Função que deleta toda BST
void deleteBST(BST* bst) {
    // Primeiro libera todos os nós
    deleteBST(bst->root);
    // Depois a BST
    free(bst);
}

// Função para exibir árvore formatada
void printTree(Node* node, int level) {
    if (node) {
        printTree(node->right, level + 1);
        for (int i = 0; i < level; i++) printf("    "); // Indentação
        printf("%d\n", node->data);
        printTree(node->left, level + 1);
    }
}

// Função principal (main)
int main() {
    return 0;
}