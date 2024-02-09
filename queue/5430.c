#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int t; // 테스트케이스
char enterFunction[100001]; // 수행할 함수를 담을 배열
char input[7000000];
int numbers[100001];

typedef struct Node{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct Deque {
    int size;
    struct Node *head;
    struct Node *tail;
} Deque;

void pushFront(Deque *deque, int data);
void pushBack(Deque *deque, int data);
int popFront(Deque *deque);
int popBack(Deque *deque);
int isEmpty(Deque *deque);
void printDeque(Deque *deque);
void clearDeque(Deque *deque); // Deque를 비우는 함수 추가
void solve(Deque *deque, int n, int numbers[], char enterFunction[]);

int main(){
    scanf("%d", &t);
    for(int i = 0; i < t; i++){
        int n;
        int num_count = 0;

        Deque deque;
        deque.head = NULL;
        deque.tail = NULL;
        deque.size = 0;

        scanf("%s", enterFunction);
        scanf("%d", &n);

        fflush(stdin);
        fgets(input, sizeof(input), stdin);
        // printf("input : %s\n", input);

        char *token = strtok(input, "[],");
        while (token != NULL){
            numbers[num_count++] = atoi(token);
            token = strtok(NULL, "[],");
        }
        
        solve(&deque, n, numbers, enterFunction);

        clearDeque(&deque);
    }
}

void solve(Deque *deque, int n, int numbers[], char enterFunction[]){
    for(int i = 0; i < n; i++){
        pushBack(deque, numbers[i]);
        // printDeque(deque);
    }

    int functionLen = strlen(enterFunction);

    for(int i = 0; i < functionLen; i++)
    {
        if ( enterFunction[i] == 'R'){
            
            Deque newDeque;
            newDeque.head = NULL;
            newDeque.tail = NULL;
            newDeque.size = 0;
            
            while(deque->size != 0){
                pushBack(&newDeque, popBack(deque));
            }

            *deque = newDeque; 
        }
        else if (enterFunction[i] == 'D'){
            if (deque->size == 0){
                printf("error\n");
                return ;
            }else{
                popFront(deque);
            }
        }
    }

    printDeque(deque);
}

void pushFront(Deque *deque, int data){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;

    if (deque->head){
        newNode->next = deque->head;
        deque->head->prev = newNode;
    }else{
        newNode->next = NULL;
        deque->tail = newNode;
    }
    deque->head = newNode;
    deque->size++;
}

void pushBack(Deque *deque, int data){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if(deque->tail){
        deque->tail->next = newNode;
        newNode->prev = deque->tail;
    }else{
        newNode->prev = NULL;
        deque->head = newNode;
    }
    deque->tail = newNode;
    deque->size++;
}

int popFront(Deque *deque){
    if (isEmpty(deque)){
        return -1;
    }
    
    Node *deleteNode = deque->head;
    int deleteNum = deleteNode->data;
    
    if (deleteNode->next){
        deleteNode->next->prev = NULL;
        deque->head = deleteNode->next;
    }else{
        deque->head = NULL;
        deque->tail = NULL;
    }
    deque->size--;

    free(deleteNode);
    return deleteNum;
}

int popBack(Deque *deque){
    if (isEmpty(deque)){
        return -1;
    }

    Node *deleteNode = deque->tail;
    int deleteNum = deleteNode->data;

    if (deleteNode->prev){
        deleteNode->prev->next = NULL;
        deque->tail = deleteNode->prev;
    }else{
        deque->head = NULL;
        deque->tail = NULL;
    }
    deque->size--;

    free(deleteNode);
    return deleteNum;
}

int isEmpty(Deque *deque){
    if (deque->size == 0){
        return 1;
    }else{
        return 0;
    }
}

void printDeque(Deque *deque)
{
    Node *cur = deque->head;
    printf("[");
    while (cur) {
        if (cur->next)
            printf("%d,", cur->data);
        else
            printf("%d", cur->data);
        cur = cur->next;
    } printf("]\n");
}

void clearDeque(Deque *deque) {
    while (deque->size > 0) {
        popFront(deque);
    }
}