#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct Deque
{
    struct Node *head;
    struct Node *tail;
} Deque;

Deque deque;
int n, m;

void pushFront(Deque *deque, int n);
void pushBack(Deque *deque, int n);
int popFront(Deque *deque);
int popBack(Deque *deque);
int isEmpty(Deque *deque);
int front(Deque *deque);
int back(Deque *deque);
void printDeque(Deque *deque);
void solve(Deque *deque, int arr[]);

int main()
{
    deque.head = NULL;
    deque.tail = NULL;

    scanf("%d %d", &n, &m);
    int arr[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &arr[i]);
    }

    for (int i = 1; i <= n; i++)
    {
        pushBack(&deque, i);
    }
    solve(&deque, arr);
    return 0;
}

void pushFront(Deque *deque, int n)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = n;
    newNode->prev = NULL;

    if (deque->head != NULL)
    {
        newNode->next = deque->head;
        deque->head->prev = newNode;
    }
    else
    {
        newNode->next = NULL;
        deque->tail = newNode;
    }
    deque->head = newNode;
}

void pushBack(Deque *deque, int n)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = n;
    newNode->next = NULL;

    if (deque->tail != NULL)
    {
        deque->tail->next = newNode;
        newNode->prev = deque->tail;
    }
    else
    {
        newNode->prev = NULL;
        deque->head = newNode;
    }
    deque->tail = newNode;
}

int popFront(Deque *deque)
{
    Node *deleteNode = deque->head;
    int deleteNum = deleteNode->data;

    if (deleteNode == NULL)
        return -1;

    if (deleteNode->next == NULL)
    {
        deque->head = NULL;
        deque->tail = NULL;
    }
    else
    {
        deleteNode->next->prev = NULL;
        deque->head = deleteNode->next;
    }

    free(deleteNode);
    return deleteNum;
}

int popBack(Deque *deque)
{
    Node *deleteNode = deque->tail;
    int deleteNum = deleteNode->data;

    if (deleteNode == NULL)
        return -1;

    if (deleteNode->prev == NULL)
    {
        deque->head = NULL;
        deque->tail = NULL;
    }
    else
    {
        deleteNode->prev->next = NULL;
        deque->tail = deleteNode->prev;
    }

    free(deleteNode);
    return deleteNum;
}

int front(Deque *deque)
{
    Node *cur = deque->head;
    if (cur == NULL)
        return -1;
    return cur->data;
}

int back(Deque *deque)
{
    Node *cur = deque->tail;
    if (cur == NULL)
        return -1;
    return cur->data;
}

void printDeque(Deque *deque)
{
    Node *cur = deque->head;
    while (cur)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}


void solve(Deque *deque, int arr[])
{
    int check = 0;

    for(int i = 0; i < m; i++)
    {
        while(deque->head->data != arr[i])
        {
            check++;
            int headCnt = 0;
            int tailCnt = 0;
            Node *headTo = deque->head;
            Node *tailTo = deque->tail;
            while(headTo->data != arr[i]){
                headCnt++;
                headTo = headTo->next;
            }
            while(tailTo->data != arr[i]){
                tailCnt++;
                tailTo = tailTo->prev;
            }

            if (headCnt <= tailCnt +1)
            {
                pushBack(deque, popFront(deque));
            }else{
                pushFront(deque, popBack(deque));
            }
        }

        if (deque->head->data == arr[i]){
            popFront(deque);
        }
        
    }
    
    printf("%d", check);
}
