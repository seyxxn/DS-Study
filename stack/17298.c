#include <stdio.h>
#include <stdlib.h>
int n;

typedef struct stackNode
{
    int data;
    struct stackNode *link;
} stackNode;

void push(stackNode **top, int data);
int pop(stackNode **top);
int peek(stackNode *top);
void printStack(stackNode *top);
void solve(int n, int arr[]);

stackNode *top = NULL;

int main()
{
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    solve(n, arr);

    return 0;
}

void push(stackNode **top, int data)
{
    stackNode *newNode = (stackNode *)malloc(sizeof(stackNode));
    newNode->data = data;
    newNode->link = *top;
    *top = newNode;
}

int pop(stackNode **top)
{
    if (*top == NULL)
        return -1;
    stackNode *deleteNode = *top;
    int deleteNum = deleteNode->data;
    *top = (*top)->link;
    free(deleteNode);
    return deleteNum;
}

int peek(stackNode *top)
{
    if (top == NULL)
        return -1;
    return top->data;
}

void printStack(stackNode *top)
{
    for (; top; top = top->link)
        printf("%d -> ", top->data);
    printf("\n");
}

void solve(int n, int arr[])
{
    stackNode *top = NULL;
    int result[n];

    for (int i = n - 1; i >= 0; i--)
    {
        if (top == NULL)
        {
            result[i] = -1;
            push(&top, arr[i]);
            continue;
        }
        while (top != NULL && peek(top) <= arr[i])
        {
            pop(&top);
        }
        result[i] = peek(top);
        push(&top, arr[i]);
    }

    /* 조금 더 깔끔한 for문
    for (int i = n - 1; i >= 0; i--)
    {
        while (top != NULL && peek(top) <= arr[i])
        {
            pop(&top);
        }
        if (top == NULL)
            result[i] = -1;
        else
            result[i] = peek(top);
        push(&top, arr[i]);
    }
    */

    for (int i = 0; i < n; i++)
        printf("%d ", result[i]);
    printf("\n");
}