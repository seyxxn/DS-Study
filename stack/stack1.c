#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100 /* 스택의 최대 크기 */
#define TRUE 1
#define FALSE 0
#define ERROR_CODE -1

/* 스택 원소 정의 및 초기화 */
typedef struct
{
    int key;
    /* 다른 필드들 */
}element;

element stack[MAX_STACK_SIZE];
int top = -1 ; // top이 -1이면 비어있는 상태

/*  스택이 비어있는지 검사 */
int isEmpty(){
    if(top == -1) return TRUE;
    else return FALSE;
}

/* 스택이 가득차있는지 검사 */
int isFull(){
    if(top >= MAX_STACK_SIZE - 1)
        return TRUE;
    else
        return FALSE;
}

/* 스택에 원소 삽입 */
void push(element item){
    if(ifFull()) stackFull(); 
    else    
        stack[++top] = item;
}

/* 스택에 원소를 삭제 */
// 삭제 후 삭제한 원소를 반환하는 함수
element pop(){
    if(top == -1) return stackEmtpy();
    return stack[top--];
}

/* 스택이 가득 찼을 때 오류 처리 */
void stackFull(){
    fprintf(stderr, "Stack is full, cannot add element");
    exit(EXIT_FAILURE);
}

/* 스택이 비어있을 때 오류 처리 */
element stackEmtpy(){
    element temp;
    temp.key = ERROR_CODE;
    fprintf(stderr, "Stack is empty, cannor delete element");
    return temp;
}
