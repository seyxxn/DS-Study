#include <stdio.h>
#include <stdlib.h>
int n;

typedef struct stackNode
{
    int data;
    struct stackNode *link;
} stackNode;

stackNode *top = NULL;
int size = 0;
int ansArr[500001] = {0, };
int ansIdx = 0;

int maxNum = 0; // 가장 큰 수를 담는 변수

void push(stackNode **top, int data);
void printStack(stackNode *top);
void pop(stackNode **top);
void solve(stackNode **top);

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int enter;
        scanf("%d", &enter);
        push(&top, enter);
        // printStack(top);
        if (enter >= maxNum)
            maxNum = enter;
    }
    solve(&top);
    // printf("max : %d \n", maxNum);
}
void push(stackNode **top, int data)
{
    stackNode *newNode = (stackNode *)malloc(sizeof(stackNode));
    newNode->data = data;
    newNode->link = *top;
    *top = newNode;

    size++;
}

void pop(stackNode **top)
{
    stackNode *deleteNode = *top;
    *top = (*top)->link;

    free(deleteNode);

    size--;
}

void printStack(stackNode *top)
{
    for (; top; top = top->link)
    {
        printf("%d -> ", top->data);
    }
    printf("\n");
}

void solve(stackNode **top)
{
    while (size > 1)
    {
        stackNode *cur = *top;
        int check = 0; // 몇번 넘어갔는지 변수
        if (cur->data == maxNum)
        {
            check = 0;
        }
        else
        {
            int num = cur->data;
            while (num >= cur->data)
            {
                cur = cur->link;
                check++;
            }
        }
        if (check == 0)
        {
            ansArr[size - 1] = 0;
        }
        else
        {
            ansArr[size - 1] = size - check;
        }
        pop(top);
    }

    for(int i = 0; i < n; i++)
    {
        printf("%d ", ansArr[i]);
    }
}
