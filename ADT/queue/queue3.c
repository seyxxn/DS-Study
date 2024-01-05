#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memcpy
#define ERROR_CODE -1

typedef struct
{
    char key;
} element;

element *queue;
int front = -1;
int rear = -1;
int capacity = 3;

void queueFull()
{
    element *newQueue;                                           // 새로 할당하는 큐
    newQueue = (element *)malloc(2 * capacity * sizeof(*queue)); // 용량을 늘림

    int start = (front + 1) % capacity; // 복사를 시작할 인덱스를 계산함
    if (start < 2)                      // 큐의 시작 위치가 배열의 앞 부분인 경우
    {
        memcpy(newQueue, queue + start, sizeof(element) * (capacity - start));
        // copy(queue+start, queue+start+capacity-1, newQueue);
        // 현재 큐 내용을 새 큐로 복사함
    }
    else // 큐가 배열의 중간에서 시작해서 끝까지 이어지고 다시 배열 시작 부분으로 가는 경우
    {
        // copy(queue+start, queue+capacity, newQueue);
        // copy(queue, queue+rear+1, newQueue+capacity-start);
        // 큐의 첫 부분을 새 큐로 복사함
        memcpy(newQueue, queue + start, sizeof(element) * (capacity - start));
        // 큐의 나머지 부분을 새 큐의 이어지는 부분으로 복사함
        memcpy(newQueue + capacity - start, queue, sizeof(element) * (rear + 1));
    }

    front = 2 * capacity - 1; // 2배 늘리니까 곱하기 2, front는 한 칸 앞이므로 -1
    rear = capacity - 2;      // 기존 크기의 -2 (-1은 한칸 무조건 남기기 때문에, -1은 인덱스는 0부터고 크기는 아니니까..)
    capacity *= 2;            // 크기는 2배로 확장
    free(queue);
    queue = newQueue; // 업데이트
}

element queueEmpty()
{
    element temp;
    temp.key = ERROR_CODE;
    fprintf(stderr, "Queue is Empty\n");
    return temp;
}

void addq(element item)
{
    rear = (rear + 1) % capacity;
    if (front == rear)
    {
        queueFull();
    }
    queue[rear] = item;
}

element deleteq()
{
    if (front == rear)
    {
        return queueEmpty();
    }
    front = (front + 1) % capacity;
    return queue[front];
}

void printQueue()
{
    int i;

    printf("front : %d rear : %d\n", front, rear);
    printf("Queue : ");
    if (front == rear)
    {
        printf("\n");
        return;
    }
    i = front;
    while (1)
    {
        i = (i + 1) % capacity;
        printf("[%d] %c ", i, queue[i].key);
        if (i == rear)
        {
            break;
        }
    }
    printf("\n");
}

int main()
{
    element item1, item2, item3, item4, item5, item6, item7;
    queue = (element *)malloc(sizeof(*queue));

    // 요소 초기화
    item1.key = 'A';
    item2.key = 'B';
    item3.key = 'C';
    item4.key = 'D';
    item5.key = 'E';
    item6.key = 'F';
    item7.key = 'G';

    addq(item1);
    printQueue();

    addq(item2);
    printQueue();

    addq(item3);
    printQueue();

    addq(item4);
    printQueue();

    addq(item5);
    printQueue();

    addq(item6);
    printQueue();

    addq(item7);
    printQueue();

    return 0;
}