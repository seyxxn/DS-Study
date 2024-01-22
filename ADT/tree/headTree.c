// 힙 트리 노드 (최대힙)
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1) // 힙이 가득찼는지 확인하는 매크로
#define HEAP_EMPTY(n) (!n)                   // 힙이 비었는지 확인하는 매크로

typedef struct
{
    int key;
} element;

element heap[MAX_ELEMENTS];
int n = 0;

// item : 추가할 원소, n : 현재 힙의 크기
// *n : 포인터 사용 이유 ? n의 값을 변경하여 현재 힙의 크기를 업데이트해야해서
void push(element item, int *n)
{
    int i;
    if (HEAP_EMPTY(*n))
    { // 가득차있다면, 에러 메세지 출력
        fprintf(stdout, "The heap is full.\n");
        exit(EXIT_FAILURE);
    }

    i = ++(*n); // 크기를 증가시키는 동시에, 가장 끝 인덱스에 우선 추가함
    while ((i != 1) && (item.key > head[i / 2].key))
    {
        // 인덱스가 1이 될 때까지 (루트노드에 도달할 때 까지), 부모 값보다 지금 값이 크면
        heap[i] = heap[i / 2]; // 부모의 값을 현재 가리키는 곳에 저장
        i /= 2;                // 인덱스를 /2 하여 부모로 올라감
    }
    heap[i] = item;
    // 부모위치에 추가할 원소의 값을 저장
}

element pop(int *n)
{
    int parent, child;
    element item, temp; // item은 반환될 원소, temp는 임시 원소
    if (HEAP_EMPTY(*n))
    {
        fprintf(stdout, "The heap it empty.\n");
        exit(EXIT_FAILURE);
    }

    // 가장 큰 값을 저장하는 변수 (루트 노드 값을 반환하기 위해 할당하는 변수)
    item = heap[1];

    // 마지막 노드를 temp에 할당하고 힙 크기를 하나 감소시킨다.
    temp = heap[(*n)--];

    // 여기서부터는 재구성하기 위해서 .. 제일 위에서부터 비교하며 재구성 한다.
    parent = 1;
    child = 2;

    while (child <= *n)
    {
        // 현재 노드의 자식 노드 중 더 큰 자식 노드를 찾기(루트 노드의 왼쪽 자식노드의 인덱스는 2. 2부터 비교를 시작한다.)
        if ((child < *n) && (heap[child].key < heap[child + 1].key))
            child++;

        // 더 큰 자식노드보다 마지막 노드의 값이 더 크다면, while문 중지 (더 이상 재구성할 필요가 없음)
        if (temp.key >= heap[child].key)
        {
            break;
        }

        // 더 큰 자식노드보다 마지막 노드의 값이 더 작다면, 부모노드와 더 큰 자식 노드를 교환
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }

    heap[parent] = temp;
    return item; // 최대값 (루트노드 반환F)
}

/*
힙의 삭제
1. 최대힙에서 최대값은 루트노드이므로, 루트노드가 삭제된다.
2. 삭제된 루트노드에는 힙의 마지막 노드를 가져온다.
3. 힙을 재구성한다.
*/