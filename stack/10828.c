#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 10001
int stack[MAX_STACK_SIZE];
int top = -1;
int count =0;

int isEmpty()
{
    if (top < 0)
    {
        return 1;
    }
    return 0;
}

int isFull()
{
    if (top >= MAX_STACK_SIZE - 1)
    {
        return 1;
    }
    return 0;
}

void push(int x)
{
    if (isFull())
    {
        return;
    }
    stack[++top] = x;
    count ++;
}

int pop()
{
    if (isEmpty())
    {
        return -1;
    }
    count--;
    return stack[top--];
}

int size(){
    return count;
}

int peek(){
    if(isEmpty()){
        return -1;
    }
    return stack[top];
}

int main()
{
    int n;
    scanf("%d", &n);

    while(n--){
        char enter[10];
        scanf("%s", enter);

        if(strcmp(enter, "push") == 0){
            int x;
            scanf("%d", &x);
            push(x);
        }else if(strcmp(enter, "top") == 0){
            printf("%d\n", peek());
        }else if (strcmp(enter, "size") == 0){
            printf("%d\n", size());
        }else if (strcmp(enter, "empty") == 0){
            printf("%d\n", isEmpty());
        }else if (strcmp(enter, "pop") == 0){
            printf("%d\n", pop());
        }
    }

    return 0;
}
