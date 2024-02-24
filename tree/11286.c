#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// 최소힙 구현
int n;

typedef struct minHeap {
    int *array;
    int capacity;
    int size;
} minHeap;

minHeap* heap;

// 최소힙 생성 함수
minHeap* createMinHeap(int capacity){
    minHeap *heap = (minHeap *)malloc(sizeof(minHeap));
    heap->array = (int *)malloc(sizeof(int) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

// 최소힙에서 부모노드의 인덱스를 반환하는 함수
int getParentIndex(int index){
    return (index - 1)/ 2;
}

// 최소힙에 원소를 삽입하는 함수
void insert(minHeap *heap, int value){
    // 힙이 가득 차있는 경우
    if (heap->size >= heap->capacity){
        return ;
    }

    int i = heap->size;
    heap->size++;
    heap->array[i] = value;

    // 힙을 재정렬하여 최소힙 성질을 유지
    while(i != 0 && abs(heap->array[i]) <= abs(heap->array[getParentIndex(i)])){

        // 절대값이 같은 경우 예외처리
        if (abs(heap->array[i]) == abs(heap->array[getParentIndex(i)]) && heap->array[i] > heap->array[getParentIndex(i)])
            break;

        int temp = heap->array[i];
        heap->array[i] = heap->array[getParentIndex(i)];
        heap->array[getParentIndex(i)] = temp;

        i = getParentIndex(i);
    }
}

// 최소힙에서 최솟값을 추출하는 함수
int extractMin(minHeap *heap){
    if (heap->size <= 0){
        return 0;
    }

    // 최솟값 추출
    int min = heap->array[0];

    // 마지막 노드를 루트로 옮기고 크기 감소 
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    // 최소힙 속성을 만족하도록 재정렬
    int i = 0; // 루트에서부터 재정렬

    while(1){
        int leftChildIndex = 2 * i + 1;
        int rightChildIndex = 2 * i + 2;

        int smallestIndex = i;

        // 왼쪽 자식과 비교 
        // 왼쪽 자식의 절대값이 현재 노드의 절대값보다 작은 경우, smallestIndex 갱신
        // 왼쪽 자식의 절대값과 현재 노드의 절대값이 같은 경우에는
        // 왼쪽 자식의 실제 값이 더 작은 경우에만 smallestIndex 갱신 (즉, 왼쪽자식이 음수)
        if (leftChildIndex < heap->size &&
            (abs(heap->array[leftChildIndex]) < abs(heap->array[i]) ||
            (abs(heap->array[leftChildIndex]) == abs(heap->array[i]) && heap->array[leftChildIndex] < heap->array[i]))) {
            smallestIndex = leftChildIndex;
        }

        // 오른쪽 자식과 비교 -> 조건 주의 **
        // i가 아닌 smallestIndex와 비교해야함
        if (rightChildIndex < heap->size &&
            (abs(heap->array[rightChildIndex]) < abs(heap->array[smallestIndex]) ||
            (abs(heap->array[rightChildIndex]) == abs(heap->array[smallestIndex]) && heap->array[rightChildIndex] < heap->array[smallestIndex]))) {
            
            smallestIndex = rightChildIndex;
        }

        // i가 최솟값의 인덱스와 같으면 힙 속성을 만족하므로 반복문 종료
        if (i == smallestIndex){
            break;
        }

        // 현재노드와 최솟값 노드 교환
        int temp = heap->array[i];
        heap->array[i] = heap->array[smallestIndex];
        heap->array[smallestIndex] = temp;

        i = smallestIndex;
    }
    return min;
}

void arrayPrint(minHeap * heap){
    printf("array print : ");
    for(int i = 0; i < heap->size; i++){
        printf("%d ", heap->array[i]);
    } printf("\n");
}

int main(){
    scanf("%d", &n);

    heap = createMinHeap(100001);

    for(int i = 0; i < n; i++){
        int enter;
        scanf("%d", &enter);
        if (enter == 0){
            printf("%d\n", extractMin(heap));
            // arrayPrint(heap);
        }else{
            insert(heap, enter);
            // arrayPrint(heap);
        }
    }
    return 0;
}
