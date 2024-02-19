#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n;

typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct Deque
{
    int size;
    struct Node *head;
    struct Node *tail;
} Deque;

void pushFront(Deque *deque, int x);
void pushBack(Deque *deque, int x);
int popFront(Deque *deque);
int popBack(Deque *deque);
int size(Deque *deque);
int empty(Deque *deque);
int front(Deque *deque);
int back(Deque *deque);
void printDeque(Deque *deque);

int main(void)
{
    Deque deque;
    deque.head = NULL;
    deque.tail = NULL;
    deque.size = 0;

    scanf("%d", &n);
    getchar();

    while (n--)
    {
        char enter[100];
        int num;
        scanf("%s", enter);
        if (strcmp(enter, "push_front") == 0)
        {
            scanf("%d", &num);
            pushFront(&deque, num);
        }
        else if (strcmp(enter, "push_back") == 0)
        {
            scanf("%d", &num);
            pushBack(&deque, num);
        }
        else if (strcmp(enter, "pop_front") == 0)
        {
            printf("%d\n", popFront(&deque));
        }
        else if (strcmp(enter, "pop_back") == 0)
        {
            printf("%d\n", popBack(&deque));
        }
        else if (strcmp(enter, "size") == 0)
        {
            printf("%d\n", size(&deque));
        }
        else if (strcmp(enter, "empty") == 0)
        {
            printf("%d\n", empty(&deque));
        }
        else if (strcmp(enter, "front") == 0)
        {
            printf("%d\n", front(&deque));
        }
        else if (strcmp(enter, "back") == 0)
        {
            printf("%d\n", back(&deque));
        }
        // printDeque(&deque);
    }
    return 0;
}

void pushFront(Deque *deque, int x)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = x;
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
    deque->size++;
}

void pushBack(Deque *deque, int x)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = x;
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
    deque->size++;
}

int popFront(Deque *deque)
{
    if (deque->size == 0)
        return -1;

    Node *deleteNode = deque->head;
    int deleteNum = deleteNode->data;
    if (deleteNode->next != NULL)
    {
        deleteNode->next->prev = NULL;
        deque->head = deleteNode->next;
    }
    else
    {
        deque->head = NULL;
        deque->tail = NULL;
    }
    deque->size--;
    free(deleteNode);
    return deleteNum;
}

int popBack(Deque *deque)
{
    if (deque->size == 0)
        return -1;

    Node *deleteNode = deque->tail;
    int deleteNum = deleteNode->data;
    if (deleteNode->prev != NULL)
    {
        deleteNode->prev->next = NULL;
        deque->tail = deleteNode->prev;
    }
    else
    {
        deque->head = NULL;
        deque->tail = NULL;
    }
    deque->size--;
    free(deleteNode);
    return deleteNum;
}

int size(Deque *deque)
{
    return deque->size;
}

int empty(Deque *deque)
{
    if (deque->size == 0)
        return 1;
    else
        return 0;
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