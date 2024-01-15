#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 10001

typedef struct queue
{
    int front;
    int rear;
    int items[MAX_QUEUE_SIZE];
} QUEUE;

int n;
int isEmpty(QUEUE);           // 큐가 비었는지 확인하는 함수
int isFull(QUEUE);            // 큐가 가득찼는지 확인하는 함수
int size(QUEUE);              // 큐의 크기를 반환하는 함수
void enqueue(QUEUE *, int x); // 큐의 앞에 원소를 삽입하는 함수
int dequeue(QUEUE *);         // 큐의 뒤에서 원소를 삭제하는 함수
int frontQueue(QUEUE *);      // 가장 앞 원소를 반환하는 함수
int backQueue(QUEUE *);       // 가장 뒤 원소를 반환하는 함수

// void printQueue(QUEUE *);

int isEmpty(QUEUE q)
{
    if (q.front == q.rear)
    {
        return 1;
    }
    return 0;
}

int isFull(QUEUE q)
{
    if (q.rear == MAX_QUEUE_SIZE - 1)
        return 1;
    return 0;
}

int size(QUEUE q)
{
    return (q.rear - q.front);
}

void enqueue(QUEUE *q, int x)
{
    if (isFull(*q))
    {
        return;
    }
    q->items[q->rear++] = x;
}

int dequeue(QUEUE *q)
{
    if (isEmpty(*q))
    {
        return -1;
    }
    return q->items[q->front++];
}

int frontQueue(QUEUE *q)
{
    if (isEmpty(*q))
    {
        return -1;
    }
    return q->items[q->front];
}

int backQueue(QUEUE *q)
{
    if (isEmpty(*q))
    {
        return -1;
    }
    return q->items[q->rear-1];
}

/* void printQueue(QUEUE *q)
{
    for (int i = q->front; i < q->rear; i++)
    {
        printf("[%d] %d ", i, q->items[i]);
    }
    printf("\n");
} */

int main()
{
    QUEUE Q;
    Q.front = 0;
    Q.rear = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        char enter[10];
        scanf("%s", enter);

        if (strcmp(enter, "push") == 0)
        {
            int num;
            scanf("%d", &num);
            enqueue(&Q, num);
        }
        else if (strcmp(enter, "pop") == 0)
        {
            printf("%d\n", dequeue(&Q));
        }
        else if (strcmp(enter, "size") == 0)
        {
            printf("%d\n", size(Q));
        }
        else if (strcmp(enter, "empty") == 0)
        {
            printf("%d\n", isEmpty(Q));
        }
        else if (strcmp(enter, "front") == 0)
        {
            printf("%d\n", frontQueue(&Q));
        }
        else if (strcmp(enter, "back") == 0)
        {
            printf("%d\n", backQueue(&Q));
        }
        //printQueue(&Q);
    }
    return 0;
}