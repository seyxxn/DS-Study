// 힙을 이용한 우선순위 큐 구현
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct
{
    int elements[MAX_SIZE];
    int size;
} MinHeap;

MinHeap *createMinHeap()
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    return minHeap;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *minHeap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < minHeap->size && minHeap->elements[left] < minHeap->elements[smallest])
    {
        smallest = left;
    }
    if (right < minHeap->size && minHeap->elements[right] < minHeap->elements[smallest])
    {
        smallest = right;
    }
    if (smallest != index)
    {
        swap(&minHeap->elements[index], &minHeap->elements[smallest]);
        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap *minHeap)
{
    return (minHeap->size == 0);
}

void insert(MinHeap *minHeap, int item)
{
    if (minHeap->size == MAX_SIZE)
    {
        fprintf(stderr, "Priority queue is full. Cannot insert.\n");
        return;
    }

    minHeap->elements[minHeap->size++] = item;
    int current = minHeap->size - 1;

    while (current > 0 && minHeap->elements[current] < minHeap->elements[(current - 1) / 2])
    {
        swap(&minHeap->elements[current], &minHeap->elements[(current - 1) / 2]);
        current = (current - 1) / 2;
    }
}

int deleteMin(MinHeap *minHeap)
{
    if (isEmpty(minHeap))
    {
        fprintf(stderr, "Priority queue is empty. Cannot delete.\n");
        exit(EXIT_FAILURE);
    }
    int minItem = minHeap->elements[0];
    minHeap->elements[0] = minHeap->elements[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return minItem;
}

int main()
{
    MinHeap *minHeap = createMinHeap();
    insert(minHeap, 10);
    insert(minHeap, 45);
    insert(minHeap, 19);
    insert(minHeap, 11);
    insert(minHeap, 96);
    printf("Deleted elements in ascending order : \n");
    while (!isEmpty(minHeap))
    {
        int item = deleteMin(minHeap);
        printf("%d ", item);
    }
    free(minHeap);
    return 0;
}