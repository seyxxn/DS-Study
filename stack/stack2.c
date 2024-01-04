#define TRUE 1
#define FALSE 0
#define ERROR_CODE -1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 동적 배열을 사용하는 스택 */
// 매크로상수 MAX_STACK_SIZE를 capacity 변수로 변경
typedef struct 
{
    int key;
    /* 다른 변수들 */
}element;

element *stack;
int capacity = 1;
int top = -1;

/* Stack이 가득 찼을 때 오류 처리 */
void stackFull(){
    stack = realloc(stack, 2 * capacity * sizeof(*stack));
    capacity *= 2;
}

/* 스택이 비어있을 때 오류 처리 */
element stackEmtpy(){
    element temp;
    temp.key = ERROR_CODE;
    fprintf(stderr, "Stack is empty, cannot delete element\n");
    return temp;
}

/* 스택이 비어있는 지 확인 */
int isEmpty(){
    if(top == -1) return TRUE;
    else return FALSE;
}

/* 스택이 가득 차 있는지 확인 */
int isFull(){
    if (top >= capacity -1) return TRUE;
    else return FALSE;
}

/* 스택에 원소 삽입 */
void push(element item){
    if(isFull()) stackFull();
    stack[++top] = item;
}

/* 원소 삭제 */
element pop(){
    if(isEmpty()){
        return stackEmtpy();
    }
    return stack[top--];
}

/* 스택 출력 */
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
    stack = (element*)malloc(sizeof(*stack));

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