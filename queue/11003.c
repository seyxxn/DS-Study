#include <stdio.h>
#include <stdlib.h>
int N, L;

typedef struct Node{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct Deque{
    int size;
    struct Node *head;
    struct Node *tail;
} Deque;

Deque deque;

void pushFront(Deque *deque, int data);
void pushBack(Deque *deque, int data);
int popFront(Deque *deque);
int popBack(Deque *deque);
int isEmpty(Deque *deque);
void printDeque(Deque *deque);
void clearDeque(Deque *deque);
void solve(Deque *deque);

int main(){
    scanf("%d %d", &N, &L);

    int *arr = (int *)malloc(sizeof(int) * N);
    for(int i = 0; i < N; i++)
        scanf("%d", &arr[i]);
    
    deque.head = NULL;
    deque.tail = NULL;
    deque.size = 0;
    
    for(int i = 0; i < N; i++){
        clearDeque(&deque);
        
        for(int j = i, check = 0; j >= 0 && check < L; j--, check++){
            pushFront(&deque, arr[j]);
        }
        solve(&deque);
    }

    clearDeque(&deque);
    return 0;
}

void solve(Deque *deque){
    // printDeque(deque);
    int minNum = 1000000000;
    Node *cur = deque->head;
    while(cur){
        if (cur->data < minNum)
            minNum = cur->data;
        cur = cur->next;
    }
    printf("%d ", minNum);
}

void pushFront(Deque *deque, int data){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;

    if (deque->head){
        deque->head->prev = newNode;
        newNode->next = deque->head;
    }else{
        deque->tail = newNode;
        newNode->next = NULL;
    }
    deque->head = newNode;
    deque->size++;
}

void pushBack(Deque *deque, int data){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (deque->tail){
        deque->tail->next = newNode;
        newNode->prev = deque->tail;
    }else{
        deque->head = newNode;
        newNode->prev = NULL;
    }
    deque->tail = newNode;
    deque->size++;
}

int popFront(Deque *deque){
    if(isEmpty(deque))
        return -1;
    
    Node *deleteNode = deque->head;
    int deleteNum = deleteNode->data;

    if(deque->size == 1){
        deque->head = NULL;
        deque->tail = NULL;
    }else{
        deleteNode->next->prev = NULL;
        deque->head = deleteNode->next;
    }
    deque->size--;
    free(deleteNode);
    return deleteNum;
}

int popBack(Deque *deque){
    if (isEmpty(deque))
        return -1;
    
    Node *deleteNode = deque->tail;
    int deleteNum = deleteNode->data;

    if (deque->size == 1){
        deque->head = NULL;
        deque->tail = NULL;
    }else{
        deleteNode->prev->next = NULL;
        deque->tail = deleteNode->prev;
    }
    deque->size--;
    free(deleteNode);
    return deleteNum;
}

int isEmpty(Deque *deque)
{
    if (deque->size == 0){
        return 1;
    }else 
        return 0;
}

void printDeque(Deque *deque){
    Node *cur = deque->head;
    while(cur){
        printf("%d ", cur->data);
        cur = cur->next;
    }printf("\n");
}

void clearDeque(Deque *deque){
    while (deque->size > 0)
    {
        popFront(deque);
    }
}