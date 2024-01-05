/* 원형 큐의 구현 */
/*
1. 배열의 끝과 처음을 연결하여 일직선 배열을 원형처럼 사용할 수 있음
2. 직선 형태의 배열로표현하면 rear가 MAX_QUEUE_SIZE -1 에 도달할 경우, 큐가 가득찬 것으로 되어 배열의 앞부분이 비어있어도 큐가 가득찬 것으로 처리됨
3. front는 첫 번째 요소로부터 시계방향으로 하나 앞(하나 전을 가리킨다는 뜻), rear은 마지막 요소를 가리킴
4. 삽입을 할 때는 rear를 무조건 먼저 하나 증가시키고, 증가된 위치에 삽입함. (선증가후 원소를 삽입한다는 것이 중요)
5. 삭제를 할 때는 먼저 front를 증가시킨 후, 그 위치에서 데이터를 꺼냄 (왜냐면, front는 첫번째 요소의 하나 전(앞)을 가리키고 있기 때문에 증가시킨후에 데이터를 꺼내야함)
6. 공백 상태 검출은 front와 rear이 같으면 공백 상태로 판단함.
7. 포화 상태 검출은 (rear + 1) % MAX_QUEUE_SIZE이 front와 같으면 포화상태로 판단함
8. 큐가 가득 찼을 떄와 비어있을 때를 구분하기 위해서 큐의 마지막 원소를 비워둠
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 5
#define ERROR_CODE -1

typedef struct{
    int key;
}element;

element queue[MAX_QUEUE_SIZE];
int rear = -1; 
int front = -1;

// 큐가 꽉 찼을 때 에러처리
void queueFull(){
    fprintf(stderr, "Queue is Full\n");
    exit(1);
}

// 큐가 비었을 때 에러처리
element queueEmpty(){
    element temp;
    temp.key = ERROR_CODE;
    fprintf(stderr, "Queue is Empty\n");
    return temp;
}

// 큐 삽입
void addq(element item){
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if(front == rear){
        queueFull();
    }else{
        queue[rear] = item;
    }
}

// 큐 삭제
element deleteq(){
    if (front == rear){
        return queueEmpty();
    }else{
        front = (front + 1)% MAX_QUEUE_SIZE;
        return queue[front];
    }
}

// 큐 출력
void printQueue(){
    int i;

    printf("front : %d rear : %d\n", front, rear);
    printf("Queue : ");
    if (front == rear){
        printf("\n");
        return;
    }
    else{
        i = front;
        while(1){
            i = (i+1) % MAX_QUEUE_SIZE;
            printf("[%d] %d ", i, queue[i].key);
            if(i == rear){
                break;
            }
        }
        printf("\n");
    }
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