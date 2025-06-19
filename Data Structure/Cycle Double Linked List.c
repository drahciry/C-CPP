// Includes
#include <stdio.h>
#include <stdlib.h>

// Tipo Nó
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Mensagem de erro para alocação de memória falha
void MallocError() {
    fprintf(stderr, "Erro: falha ao alocar memória!\n");
    exit(1);
}

// Mensagem de erro para fila encadeada vazia
void EmptyLinkedListError() {
    fprintf(stderr, "Erro: lista encadeada está vazia!\n");
    exit(2);
}

// Mensagem de erro para índice fora do raio
void IndexOutRangeError() {
    fprintf(stderr, "Erro: índice informado fora do raio da lista!\n");
    exit(3);
}

// Lista Duplamente Encadeada Circular
typedef struct {
    Node* head;
    Node* tail;
} CycleDoubleLL;

// Inicializa lista
CycleDoubleLL* createLL() {
    // Declaração de variáveis
    CycleDoubleLL* ll = malloc(sizeof(CycleDoubleLL));
    if (!ll) MallocError();
    
    // Cabeça e rabo são nulos
    ll->head = NULL;
    ll->tail = NULL;
    // Retorna lista
    return ll;
}

// Função que verifica se lista está vazia
int isEmpty(CycleDoubleLL* ll) {
    return (!ll->head);
}

// Insere dado no início da lista
void insertStart(CycleDoubleLL* ll, int value) {
    // Declaração de variáveis
    Node* n = malloc(sizeof(Node));
    if (!n) MallocError();

    // Guarda valor no nó
    n->data = value;
    // Verifica se está vazia
    if (isEmpty(ll)) {
        ll->head = ll->tail = n;
        n->next = n->prev = n;
        return;
    }
    // Se não estiver vazia
    n->next = ll->head;
    n->prev = ll->tail;
    ll->head->prev = n;
    ll->tail->next = n; 
    ll->head = n;
}

// Insere dado no fim da lista
void insertEnd(CycleDoubleLL* ll, int value) {
    // Declaração de variáveis
    Node* n = malloc(sizeof(Node));
    if (!n) MallocError();

    // Guarda valor no nó
    n->data = value;
    // Verifica se está vazia
    if (isEmpty(ll)) {
        ll->head = ll->tail = n;
        n->next = n->prev = n;
        return;
    }
    // Se não estiver vazia
    n->next = ll->head;
    n->prev = ll->tail;
    ll->tail->next = n;
    ll->head->prev = n;
    ll->tail = n;
}

// Remove dado do início da lista
int removeStart(CycleDoubleLL* ll) {
    // Declaração de variáveis
    int value;
    Node* current;

    // Verifica se lista está vazia
    if (isEmpty(ll)) EmptyLinkedListError();
    // Armazena dado para retorno
    value = ll->head->data;
    // Verifica se há somente um dado na lista
    if (ll->head == ll->tail) {
        free(ll->head);
        ll->head = NULL;
        ll->tail = NULL;
        // Retorna dado
        return value;
    }
    // Armazena referência do próximo
    current = ll->head->next;
    // Libera memória do nó cabeça
    free(ll->head);
    // Recupera a referência
    ll->head = current;
    ll->head->prev = ll->tail;
    ll->tail->next = ll->head;
    // Retorna dado
    return value;
}

// Remove dado do fim da lista
int removeEnd(CycleDoubleLL* ll) {
    // Declaração de variáveis
    int value;
    Node* current;

    // Verifica se lista está vazia
    if (isEmpty(ll)) EmptyLinkedListError();
    // Armazena dado para retorno
    value = ll->tail->data;
    // Verifica se há somente um dado na lista
    if (ll->head == ll->tail) {
        free(ll->head);
        ll->head = NULL;
        ll->tail = NULL;
        // Retorna dado
        return value;
    }
    // Armazena referência do anterior
    current = ll->tail->prev;
    // Libera memória do nó rabo
    free(ll->tail);
    // Recupera referência
    ll->tail = current;
    ll->head->prev = ll->tail;
    ll->tail->next = ll->head;
    // Retorna dado
    return value;
}

// Insere em posição N
void insertPosition(CycleDoubleLL* ll, int value, int position) {
    // Declaração de variáveis
    int index = 0;
    Node* current = ll->head;
    Node* newNode = malloc(sizeof(Node));

    // Armazena novo dado
    newNode->data = value;
    // Percorre lista até posição indicada
    while (current->next != ll->head && index++ < position) current = current->next;
    // Verifica se o índice que parou é igual à posição requerida
    if (index != position) IndexOutRangeError();
    // Insere novo nó na posição N
    current->prev->next = newNode;
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev = newNode;
    // Se a posição for 0, é o novo cabeça
    if (!position) ll->head = newNode;
    // Se a posição for o tamanho da lista, é o novo rabo
    if (current == ll->head && position) ll->tail = newNode; 
}

// Remove da posição N
int removePosition(CycleDoubleLL* ll, int position) {
    // Declaração de variáveis
    int value, index = 0;
    Node* current = ll->head;

    // Verifica se lista está vazia
    if (isEmpty(ll)) EmptyLinkedListError();
    // Percorre lista até posição indicada
    while (current->next != ll->head && index++ < position) current = current->next;
    // Verifica se o índice que parou é igual a posição requerida
    if (index != position) IndexOutRangeError();
    // Armazena dado removido
    value = current->data;
    // Se tiver apenas 1 nó
    if (ll->head == ll->tail) {
        // Libera nó da memória
        free(current);
        // Torna a lista vazia
        ll->head = ll->tail = NULL;
        // Retorna dado removido
        return value;
    }
    // Se estiver removendo o cabeça
    if (current == ll->head) ll->head = current->next;
    // Se estiver removendo o rabo
    if (current == ll->tail) ll->tail = current->prev;
    // Remove nó na posição N
    current->prev->next = current->next;
    current->next->prev = current->prev;
    // Libera memória do nó removido
    free(current);
    // Retorna dado removido
    return value;
}

// Exibe lista encadadeada
void displayLL(CycleDoubleLL* ll) {
    // Declaração de variáveis
    Node* current = ll->head;

    // Verifica se a lista está vazia
    if (isEmpty(ll)) EmptyLinkedListError();
    // Percorre lista exibindo dados
    do {
        printf("%d <-> ", current->data);
        current = current->next;
    } while (current != ll->head);
    printf("(volta pro início)\n");
}

// Função para deletar lista encadeada
void deleteLL(CycleDoubleLL* ll) {
    // Declaração de variáveis
    Node* current = ll->head;
    Node* next;

    // Verifica se lista está vazia
    if (isEmpty(ll)) {
        // Libera memória da lista
        free(ll);
        return;
    }
    // Libera memória de cada nó
    do {
        next = current->next;
        free(current);
        current = next;
    }
    while (current != ll->head);
    // Libera memória da lista
    free(ll);
}

// Função principal (main) 
int main() {
    return 0;
}