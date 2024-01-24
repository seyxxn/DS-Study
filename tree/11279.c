#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100000

typedef struct heapType
{
    int heap[MAX_ELEMENT];
    int heapSize;
} heapType;

heapType *createHeap()
{
    heapType *h = (heapType *)malloc(sizeof(heapType));
    h->heapSize = 0;
    return h;
}

void push(heapType *h, int data)
{
    h->heapSize = h->heapSize + 1;
    int i = h->heapSize;

    while ((i != 1) && (data > h->heap[i / 2]))
    {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = data;
}

void pop(heapType *h)
{
    if (h->heapSize == 0)
    {
        printf("0\n");
        return;
    }
    int item, temp;
    int parent = 1;
    int child = 2;

    item = h->heap[1]; // 가장 큰 값 저장
    temp = h->heap[h->heapSize];
    h->heapSize = h->heapSize - 1;

    while (child <= h->heapSize)
    {
        if ((child < h->heapSize) && (h->heap[child]) < (h->heap[child + 1]))
            child++;
        if (h->heap[child] <= temp)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    printf("%d\n", item);
}

void printHeap(heapType *h)
{
    for (int i = 1; i <= h->heapSize; i++)
    {
        printf("[%d] : %d ", i, h->heap[i]); // 1부터 값을 저장함
    }
    printf("\n");
}

int main()
{
    int n;
    scanf("%d", &n);

    heapType *h = createHeap();

    while (n--)
    {
        int enter;
        scanf("%d", &enter);

        switch (enter)
        {
        case 0:
            pop(h);
            break;
        default:
            push(h, enter);
            break;
        }

        // printHeap(h);
    }
}