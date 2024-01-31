// 링크드리스트를 활용한 스택 구현 프로그램 예제
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int key;
} element;
typedef struct stack *stackPointer;
typedef struct stack
{
    element data;
    stackPointer link;
} stack;

void push(stackPointer *top, element item);
int pop(stackPointer *top, element *item);
int peek(stackPointer top, element *item);
void printStack(stackPointer top);

int main(int argc, char *argv[])
{
    stackPointer top = NULL;
    element data1, data2, data3, data4;
    element temp;

    data1.key = 10;
    data2.key = 20;
    data3.key = 30;
    data4.key = 40;

    push(&top, data1);
    printf("push : %4d\n", data1.key);
    push(&top, data2);
    printf("push : %4d\n", data2.key);

    peek(top, &temp);
    printf("peek : %4d\n", temp.key);

    push(&top, data3);
    printf("push : %4d\n", data3.key);
    push(&top, data4);
    printf("push : %4d\n", data4.key);

    printStack(top);

    peek(top, &temp);
    printf("peek : %4d\n", temp.key);

    pop(&top, &temp);
    printf("pop : %4d\n", temp.key);
    pop(&top, &temp);
    printf("pop : %4d\n", temp.key);
    pop(&top, &temp);
    printf("pop : %4d\n", temp.key);
    pop(&top, &temp);
    printf("pop : %4d\n", temp.key);
    pop(&top, &temp);

    printStack(top);
}

void push(stackPointer *top, element item)
{
    stackPointer temp;
    temp = (stackPointer)malloc(sizeof(*temp));
    if (temp == NULL)
    {
        fprintf(stderr, "메모리 할당 에러\n");
        exit(1);
    }

    temp->data = item;
    temp->link = *top;
    *top = temp;
}

int pop(stackPointer *top, element *item)
{
    stackPointer temp = *top;

    item->key = -1;

    if (!temp) // 비어있는 경우
    {
        return 0;
    }

    *item = temp->data;
    *top = temp->link;
    free(temp);
    return 1;
}

int peek(stackPointer top, element *item)
{
    if (top == NULL)
    {
        return 0;
    }
    else
    {
        *item = top->data;
        return 1;
    }
}

void printStack(stackPointer top)
{
    printf("The stack contains : ");
    for (; top; top = top->link)
    {
        printf("%4d ", top->data.key);
    }
    printf("\n");
}