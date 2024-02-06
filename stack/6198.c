#include <stdio.h>
#include <stdlib.h>

typedef struct stackNode
{
    int height;
    struct stackNode *link;
} stackNode;

typedef struct Stack
{
    int size;
    struct stackNode *top;
} Stack;

void push(Stack *stack, int height);
void solve(int n, int heights[]);
void stackPrint(stackNode *top);
int pop(Stack *top);
int peek(Stack *top);

int main()
{
    int n;
    scanf("%d", &n);

    int heights[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &heights[i]);
    }
    solve(n, heights);
    return 0;
}

void push(Stack *stack, int height)
{
    stackNode *newNode = (stackNode *)malloc(sizeof(stackNode));
    newNode->height = height;
    newNode->link = stack->top;
    stack->top = newNode;
    stack->size++;
}

void stackPrint(stackNode *top)
{
    for (; top; top = top->link)
    {
        printf("%d -> ", top->height);
    }
    printf("\n");
}

int pop(Stack *stack)
{
    if (stack->top == NULL)
        return -1;

    stackNode *deleteNode = stack->top;
    int deleteNum = deleteNode->height;
    stack->top = stack->top->link;

    free(deleteNode);
    stack->size--;
    return deleteNum;
}

int peek(Stack *stack)
{
    if (stack->top == NULL)
        return -1;
    return stack->top->height;
}

void deleteNode(Stack *stack)
{
    stackNode *cur = stack->top;
    stackNode *next;

    while (cur != NULL)
    {
        next = cur->link;
        free(cur);
        cur = next;
    }
    stack->top = NULL;
    stack->size = 0;
}

void solve(int n, int heights[])
{
    Stack stack;
    stack.top = NULL;
    stack.size = 0;
    long long result = 0;

    for (int i = 0; i < n; i++)
    {
        while(stack.top != NULL && stack.top->height <= heights[i])
            pop(&stack);
        push(&stack, heights[i]);
        result += stack.size - 1;
    }
    printf("%lld\n", result);
}