#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int t; // 테스트케이스
char enterFunction[100001]; // 수행할 함수를 담을 배열
char input[400001]; 
int numbers[100001]; 
int headOrTail = 0; 
// head부터시작하면 0, Tail부터 시작하면 1
// 실제로 뒤집어서 저장하는 것은 시간초과가 나서
// 뒤집지 않고, 출력하는 시작점을 바꾸는 방법으로 변경

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
void clearDeque(Deque *deque);
void solve(Deque *deque, int n, int numbers[], char enterFunction[]);

int main(){
    scanf("%d", &t);
    for(int i = 0; i < t; i++){
        int n;
        int num_count = 0;
        headOrTail = 0;

        Deque deque;
        deque.head = NULL;
        deque.tail = NULL;
        deque.size = 0;

        scanf("%s", enterFunction);
        scanf("%d", &n);

        while(getchar() != '\n');
        fgets(input, sizeof(input), stdin);

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
            if (headOrTail == 0)
                headOrTail = 1;
            else if (headOrTail == 1)
                headOrTail = 0;
        }
        else if (enterFunction[i] == 'D'){
            if (deque->size == 0){
                printf("error\n");
                return ;
            }else if (headOrTail == 0){
                popFront(deque);
            }else if (headOrTail == 1){
                popBack(deque);
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
    
    if (deque->size == 1){
        deque->head = NULL;
        deque->tail = NULL;
    }else{
        deque->head = deleteNode->next;
        deque->head->prev = NULL;
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

    if (deque->size == 1){
        deque->head = NULL;
        deque->tail = NULL;
    }else{
        deque->tail = deleteNode->prev;
        deque->tail->next = NULL;
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
    if (headOrTail == 0){
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
    else if (headOrTail == 1){
    Node *cur = deque->tail;
    printf("[");
        while (cur) {
            if (cur->prev)
                printf("%d,", cur->data);
            else
                printf("%d", cur->data);
            cur = cur->prev;
        } printf("]\n");
    }
}

void clearDeque(Deque *deque) {
    while (deque->size > 0) {
        popFront(deque);
    }
}