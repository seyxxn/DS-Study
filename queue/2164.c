#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 1000001 // 500001로 했더니 계속 런타임 오류나서 두배늘렸더니 정답
int n;

typedef struct queue
{
    int front;
    int rear;
    int items[MAX_QUEUE_SIZE];
} QUEUE;

void enqueue(QUEUE *q, int data);
int dequeue(QUEUE *q);
int size(QUEUE q);
int isEmpty(QUEUE q);
int front(QUEUE *q);
void printQueue(QUEUE *q);

int main()
{
    scanf("%d", &n);
    QUEUE Q;
    Q.front = 0;
    Q.rear = 0;

    for (int i = 1; i <= n; i++)
    {
        enqueue(&Q, i);
    }

    while (size(Q) > 1)
    {
        dequeue(&Q); // 가장 위의 카드를 제거
        int data = dequeue(&Q);
        enqueue(&Q, data);
    }

    printf("%d\n", front(&Q));
}

int front(QUEUE *q)
{
    return q->items[q->front];
}

int isEmpty(QUEUE q)
{
    if (q.front == q.rear)
    {
        return 1;
    }
    return 0;
}

void enqueue(QUEUE *q, int data)
{
    q->items[q->rear++] = data;
}

int dequeue(QUEUE *q)
{
    if (isEmpty(*q))
        return -1;
    return q->items[q->front++];
}

int size(QUEUE q)
{
    return q.rear - q.front;
}

void printQueue(QUEUE *q)
{
    for (int i = q->front; i < q->rear; i++)
    {
        printf("[%d] %d ", i, q->items[i]);
    }
    printf("\n");
}