#include <stdio.h>
#include <stdlib.h>

// 환형 큐의 구조체 정의
typedef struct {
    int *data; // 데이터 배열
    int front; // 큐의 앞 포인터
    int rear; // 큐의 뒷 포인터
    int size; // 큐의 현재 크기
    int capacity; // 큐의 최대 용량
} CircularQueue;

// 환형 큐 초기화 함수
CircularQueue* initializeQueue(int capacity)
{
    CircularQueue *queue = (CircularQueue *)malloc(sizeof(CircularQueue));
    queue->data = (int *)malloc(capacity * sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// 큐가 비어있는지 확인하는 함수 
int isEmpty(CircularQueue *queue)
{
    return queue->size == 0;
}

// 큐가 가득찼는지 확인하는 함수
int isFull(CircularQueue *queue)
{
    return queue->size == queue->capacity;
}

// 큐에 원소를 삽입하는 함수
void enQueue(CircularQueue * queue, int item)
{
    if (isFull(queue))
    {
        // 큐가 가득 찬 경우, 큐 확장 필요
        int newCapacity = queue->capacity * 2;
        int *newData = (int *)malloc(newCapacity * sizeof(int));

        int i,j;
        // 기존 큐의 데이터를 새로운 큐로 복사
        for (i = 0, j = queue->front; i < queue->size; i++)
        {
            newData[i] = queue->data[j];
            j = (j + 1) % queue ->capacity;
        }

        free(queue->data); // 이전데이터 배열 해제
        queue->data = newData;
        queue->front = 0;
        queue->rear = queue->size - 1;
        queue->capacity = newCapacity;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = item;
    queue->size++;
}

// 큐에서 원소를 삭제하고 반환하는 함수
int deQueue(CircularQueue *queue)
{
    if(isEmpty(queue))
    {
        printf("Queue is Empty.\n");
        return -1;
    }

    int item = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

// 큐 출력 함수
void displayQueue(CircularQueue * queue)
{
    int i, j;
    printf("Queue : ");
    for(i = 0, j = queue->front; i < queue->size; i++)
    {
        printf("%d ", queue->data[j]);
        j = (j + 1) % queue->capacity;
    }
    printf("\n");
}

int main(){
    CircularQueue *queue = initializeQueue(5);

    enQueue(queue, 1);
    enQueue(queue, 2);
    enQueue(queue, 3);

    displayQueue(queue); // 1 2 3

    deQueue(queue);

    displayQueue(queue); // 2 3

    enQueue(queue, 4);
    enQueue(queue, 5);

    displayQueue(queue); // 2 3 4 5

    enQueue(queue, 6); // 큐가 가득차서 큐 확장 
    enQueue(queue, 7);
    enQueue(queue, 8);

    displayQueue(queue); // 2 3 4 5 6 7 8

    free(queue->data);
    free(queue);
    return 0;
}