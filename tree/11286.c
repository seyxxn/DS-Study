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
    // 이렇게하면 절대값이 가장 작은 값을 item이 가지게 됨 (제일 위에 오는 수를 저장하는 변수라고 생각)
    int temp = h->heap[h->heapSize];
    h->heapSize = h->heapSize - 1;

    // 위에서부터 재구성
    while (child <= h->heapSize)
    {
        if (child < h->heapSize)
        {
            // 자식들의 절대값이 같을 때를 따로 처리해야함 -> 절대값이 작다면, 더 작은 수를 위로 올린다
            if ((abs(h->heap[child]) == abs(h->heap[child + 1])) && (h->heap[child] > h->heap[child + 1]))
            {
                child++;
            }
            if (abs(h->heap[child]) > abs(h->heap[child + 1]))
            {
                child++;
            }
        }

        if (abs(temp) == abs(h->heap[child]) && temp <= h->heap[child]) // temp <= 부등호가 들어가도되는지 생각해보세요
            break;
        else if (abs(temp) < abs(h->heap[child]))
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
        // printHeap(h);
    }
    return 0;
}