// 최대 힙 예제 프로그램
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 100

typedef struct
{
    int heap[MAX_ELEMENTS];
    int heapSize;
} heapType;

heapType *createHeap();
void push(heapType *h, int item);
int pop(heapType *h);
void printHeap(heapType *h);

int main(int argc, char *argv[])
{
    int i, n, item;
    heapType *heap = createHeap();

    push(heap, 10);
    push(heap, 45);
    push(heap, 19);
    push(heap, 11);
    push(heap, 96);

    printHeap(heap);
    n = heap->heapSize;

    for (i = 1; i <= n; i++)
    {
        item = pop(heap);
        fprintf(stdout, " \n delete : [%d] ", item);
    }
    return 0;
}

heapType *createHeap()
{
    heapType *h = (heapType *)malloc(sizeof(heapType));
    h->heapSize = 0;
    return h;
}

void push(heapType *h, int item)
{
    int i;
    h->heapSize = h->heapSize + 1;
    i = h->heapSize;

    while ((i != 1) && (item > h->heap[i / 2]))
    {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }

    h->heap[i] = item;
}

int pop(heapType *h)
{
    int parent, child;
    int item, temp;
    item = h->heap[1];
    temp = h->heap[h->heapSize];
    h->heapSize = h->heapSize - 1;
    parent = 1;
    child = 2;

    while (child <= h->heapSize)
    {
        if ((child < h->heapSize) && (h->heap[child]) < (h->heap[child + 1]))
            child++;
        if (temp >= h->heap[child])
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child = child * 2;
    }

    h->heap[parent] = temp;

    return item;
}

void printHeap(heapType *h)
{
    int i;
    fprintf(stdout, " Heap : ");
    for (i = 1; i <= h->heapSize; i++)
    {
        fprintf(stdout, " [%d] ", h->heap[i]);
    }
}