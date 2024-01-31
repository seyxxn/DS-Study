// 배열을 사용한 큐 예제 프로그램
#include <stdio.h>

#define MAX_QUEUE_SIZE 100 // 배열로 큐를 만들기 때문에 큐의 최대크기 정의
typedef struct
{
    int key;
} element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

int isQueueFull()
{ // 큐가 가득차있는지 확인하는 함수
    return (rear == MAX_QUEUE_SIZE - 1);
}

int isQueueEmpty()
{
    // 큐가 비어있는지 확인하는 함수
    return (rear == front);
}

void enQueue(element item)
{
    // 원소를 추가하는 함수
    if (isQueueFull())
    {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    queue[++rear] = item; // 원소를 큐의 뒤에 추가
}

element deQueue()
{
    if (isQueueEmpty())
    {
        printf("Queue is empty. Cannot dequeue.\n");
        element emptyElement;
        emptyElement.key = -1; // 오류 값을 넣어준다.
        return emptyElement;
    }
    return queue[++front];
}

void printQueue()
{
    printf("Queue : ");
    for(int i = front + 1; i <= rear; i++)
    {
        printf("%d ", queue[i].key);
    }printf("\n");
}
int main()
{
    element item1, item2, item3;
    item1.key = 42;
    item2.key = 53;
    item3.key = 44;

    printQueue();
    if (!isQueueFull())
    {
        enQueue(item1);
        enQueue(item2);
        enQueue(item3);
    }

    printQueue();
    if (!isQueueEmpty())
    {
        element removedItem = deQueue();
        printf("Dequeued : %d\n", removedItem.key);
    }
    printQueue();

    return 0;
}