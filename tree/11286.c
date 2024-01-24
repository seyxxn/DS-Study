#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100001

// 절대값이 작은 수가 맨 위에 존재하는 트리
// stdlib.h 헤더파일에 존재하는 abs 함수 이용하기

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

void push(heapType *h, int item)
{
    h->heapSize = h->heapSize + 1;
    int i = h->heapSize;

    while ((i != 1) && (abs(item) <= abs(h->heap[i / 2])))
    {
        if (abs(item) == abs(h->heap[i / 2]))
        {
            if (item < h->heap[i / 2])
            {
                h->heap[i] = h->heap[i / 2];
                i /= 2;
            }
            else
                break;
        }
        else
        {
            h->heap[i] = h->heap[i / 2];
            i /= 2;
        }
    }
    h->heap[i] = item;
}

void pop(heapType *h)
{
    if (h->heapSize == 0)
    {
        printf("0\n");
        return;
    }

    int parent = 1;
    int child = 2;
    int item = h->heap[1];
    int temp = h->heap[h->heapSize];
    h->heapSize = h->heapSize - 1;

    while (child <= h->heapSize)
    {
        if (child < h->heapSize && abs(h->heap[child]) > abs(h->heap[child + 1]))
        {
            child++; // 왼쪽 자식보다 오른쪽 자식이 더 작은 수라면 child++;
        }

        if (child < h->heapSize && abs(h->heap[child] == abs(h->heap[child+1])) && h->heap[child] > h->heap[child+1])
        {
            child++;
        }

        // 마지막수의 절대값보다 자식의 값이 더 작거나 같다면 반복문 탈출
        if (abs(temp) < abs(h->heap[child]))
        {
            break;
        }

        if (abs(temp) == abs(h->heap[child]) && temp <= h->heap[child]){
            break;
        }

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
        printf("[%d] : %d, ", i, h->heap[i]);
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
        printHeap(h);
    }
    return 0;
}