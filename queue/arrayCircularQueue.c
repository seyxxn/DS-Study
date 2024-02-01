// 배열을 기반으로 한 원형 큐 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 5 // 원형 큐의 최대 크기
#define ERROR_CODE -1

typedef struct
{
    int key;
} element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void queueFull();
element queueEmpty();
void addQueue(element item);
element deleteQueue();
void printQueue();

int main(int argc, char *argv[])
{
    element item1, item2, item3;

    item1.key = 10;
    item2.key = 20;
    item3.key = 30;

    addQueue(item1);
    printQueue();
    addQueue(item2);
    printQueue();
    addQueue(item3);
    printQueue();

    deleteQueue();
    printQueue();
    deleteQueue();
    printQueue();
    deleteQueue();
    printQueue();
    deleteQueue();
    printQueue();

    addQueue(item1);
    printQueue();
    addQueue(item2);
    printQueue();
    addQueue(item3);
    printQueue();
    addQueue(item1);
    printQueue();
    addQueue(item2);
    printQueue();

    return 0;
}

// 큐가 가득차있을 때 호출하여 에러를 처리하는 함수
void queueFull()
{
    fprintf(stderr, "Queue is full, cannot add element.\n");
    exit(EXIT_FAILURE);
}

// 큐가 비어있을 때 호출하여 오류를 처리하는 함수
element queueEmpty()
{
    element temp;
    temp.key = ERROR_CODE;
    fprintf(stderr, "Queue is empty, cannot delete element.\n");
    return temp;
}

void addQueue(element item)
{
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if (rear == front)
        queueFull();
    queue[rear] = item;
}

element deleteQueue()
{
    if (rear == front)
        return queueEmpty();
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}

void printQueue()
{
    int i;

    fprintf(stdout, "front : %d, rear : %d\n", front, rear);
    fprintf(stdout, "Queue : ");

    if (front == rear)
    {
        printf("\n");
        return;
    }

    i = front;
    while (1)
    {
        i = (i + 1) % MAX_QUEUE_SIZE;
        fprintf(stdout, "[%d]%d ", i, queue[i].key);
        if (i == rear)
            break;
    }
    fprintf(stdout, "\n");
}
