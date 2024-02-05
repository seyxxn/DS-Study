// 정적 배열을 이용한 우선순위 큐 구현
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct
{
    int heap[MAX_SIZE];
    int size;
} priorityQueue;

priorityQueue *createPriorityQueue()
{
    priorityQueue *pq = (priorityQueue *)malloc(sizeof(priorityQueue));
    pq->size = 0;
    return pq;
}

void enqueue(priorityQueue *pq, int item)
{
    if (pq->size >= MAX_SIZE)
    {
        fprintf(stderr, "Queue is full. Cannot enqueue.\n");
        return;
    }

    int i = ++pq->size;
    while (i > 1 && item > pq->heap[i / 2])
    {
        pq->heap[i] = pq->heap[i / 2];
        i /= 2;
    }
    pq->heap[i] = item;
}

int dequeue(priorityQueue *pq)
{
    if (pq->size == 0)
    {
        fprintf(stderr, "Queue is empty. Cannot dequeue.\n");
        exit(EXIT_FAILURE);
    }
    int parent = 1, child = 2;
    int item = pq->heap[1];
    int temp = pq->heap[pq->size--];
    while (child <= pq->size)
    {
        if (child < pq->size && pq->heap[child] < pq->heap[child + 1])
        {
            child++;
        }
        if (temp >= pq->heap[child])
        {
            break;
        }
        pq->heap[parent] = pq->heap[child];
        parent = child;
        child *= 2;
    }
    pq->heap[parent] = temp;
    return item;
}

int main()
{
    priorityQueue *pq = createPriorityQueue();
    enqueue(pq, 10);
    enqueue(pq, 45);
    enqueue(pq, 19);
    enqueue(pq, 11);
    enqueue(pq, 96);
    printf("Dequeue elements in descending order : \n");
    while (pq->size > 0)
    {
        int item = dequeue(pq);
        printf("%d ", item);
    }
    free(pq);
    return 0;
}