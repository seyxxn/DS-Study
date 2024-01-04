#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define ERROR_CODE -1
#define MAX_STACK_SIZE 100

typedef struct
{
    int key;
}element;

element stack[MAX_STACK_SIZE];
int top = -1;

int isEmpty(){
    if(top == -1) return TRUE;
    else return FALSE;        
}

int isFull(){
    if(top >= MAX_STACK_SIZE -1) return TRUE;
    else return FALSE;
}

void stackFull(){
    fprintf(stderr, "Stack is full, cannot add element");
    exit(1);
}


element stackEmpty(){
    element temp;
    temp.key = ERROR_CODE;
    fprintf(stderr, "Stakc is empty, cannot delete element");
    return temp;
}

void push(element item){
    if(isFull()){
        stackFull();
    }else{
        stack[++top] = item;
    }
}

element pop(){
    if(isEmpty()){
        return stackEmpty();
    }return stack[top--];
}

void printStack(){
    int i;
    printf("Stack : ");

    for(i = 0; i <= top; i++){
        printf("%d ", stack[i].key);
    }
    printf("\n");
}

int main(void){
    element item1, item2, item3;
    
    item1.key = 10;
    item2.key = 22;
    item3.key = 55;

    printStack();

    push(item1);
    printStack();

    push(item2);
    printStack();

    push(item3);
    printStack();

    pop();
    printStack();

    pop();
    printStack();

    pop();
    printStack();
    
    return 0;
}