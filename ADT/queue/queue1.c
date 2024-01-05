#include <stdio.h>
#include <stdlib.h>
#define ERROR_CODE -1
/* 일반 배열을 사용한 큐 */

// 큐의 정의
#define MAX_QUEUE_SIZE 100
typedef struct{
    int key;
}element;

element queue[MAX_QUEUE_SIZE];
int rear = -1; // 뒤
int front = -1; // 앞

// 큐가 비어있는지 검사 -> front == rear

// 큐가 가득차있는지 검사 -> rear == MAX_QUEUE_SIZE - 1
// 위 조건식의 문제점은 배열의 앞부분이 비어있음에도 불구하고 큐가 가득 차있는 것으로 처리된다는 문제점이 있음 -> 원형 큐로 해결할 수 있음

void queueFull(){
    fprintf(stderr, "Queue is full\n"); 
    exit(1);
}

element queueEmpty(){
    element temp;
    temp.key = ERROR_CODE;
    fprintf(stderr, "Queue is empty\n");
    return temp;
}


// 큐에 원소를 삽입하는 함수
void addq(element item){
    if(rear == MAX_QUEUE_SIZE - 1){ // 가득차있는 상태
        queueFull();
    }else{
        queue[++rear] = item;
    }
}

//큐의 원소를 삭제하는 함수
element deleteq(){
    if(rear == front) {// 비어있는 상태
        return queueEmpty();
    }return queue[++front];
}

void printQueue(){
    int i;

    printf("front : %d rear : %d \n", front, rear);
    printf("Queue : ");
    if (front == rear){ // 비어있는 상태 
        printf("\n");
        return;
    }
    for(i = front + 1 ; i <= rear; i++){
        printf("[%d] %d ", i, queue[i].key);
    }

    printf("\n");
}

int main(void){
    element item1, item2, item3;

    item1.key = 10;
    item2.key = 20;
    item3.key = 30;

    addq(item1);
    printQueue();

    addq(item2);
    printQueue();

    addq(item3);
    printQueue();

    deleteq();
    printQueue();

    deleteq();
    printQueue();

    deleteq();
    printQueue();

    deleteq();
    printQueue();

    addq(item1);
    printQueue();

    addq(item2);
    printQueue();

    addq(item3);
    printQueue(); 

    addq(item1);
    printQueue();

    addq(item2);
    printQueue();

    return 0;

}