// 최대 힙을 이용한 내림차순 정렬 예제 프로그램
#include <stdio.h>
#include <stdlib.h>

// 최대 힙 구조체 정의
typedef struct {
    int *array; // 힙을 구현할 배열
    int capacity; // 힙의 최대 크기
    int size; // 힙의 현재 크기
} maxHeap;

// 최대 힙 생성 함수
maxHeap *createMaxHeap(int capacity){
    maxHeap *heap = (maxHeap*)malloc(sizeof(maxHeap));
    heap->array = (int *)malloc(sizeof(int) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

// 최대 힙에서 부모 노드의 인덱스를 반환하는 함수
int getParentIndex(int index){
    return (index - 1) / 2;
}

// 최대 힙에 원소를 삽입하는 함수
void insert(maxHeap *heap, int value){
    // 힙이 가득 차 있는 경우
    if (heap->size >= heap->capacity){
        fprintf(stderr, "Heap is full. Cannot insert.\n");
        return ;
    }

    int i = heap->size;
    heap->size++;
    heap->array[i] = value;
    // 힙을 재정렬하여 최대 힙 속성 유지
    while(i != 0 && heap->array[i] > heap->array[getParentIndex(i)]){
        // 부모 노드와 현재 노드를 교환
        int temp = heap->array[i];
        heap->array[i] = heap->array[getParentIndex(i)];
        heap->array[getParentIndex(i)] = temp;
        i = getParentIndex(i);
    }
}

// 최대 힙에서 최댓값을 추출하는 함수
int extractMax(maxHeap *heap){
    // 힙이 비어있는 경우
    if (heap->size <= 0){
        fprintf(stderr, "Heap is empty. Cannot extract maximum.\n");
        exit(EXIT_FAILURE);
    }

    // 최댓값 추출
    int max = heap->array[0];
    // 마지막 노드를 루트로 옮기고 크기 감소
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    // 최대 힙 속성을 만족하도록 재정렬
    int i = 0;
    while (1){
        int leftChildIndex = 2 * i + 1;
        int rightChildIndex = 2 * i + 2;
        int largestIndex = i;
        // 왼쪽 자식과 비교
        if (leftChildIndex < heap->size && heap->array[leftChildIndex] > heap->array[i]){
            largestIndex = leftChildIndex;
        }
        // 오른쪽 자식과 비교
        if (rightChildIndex < heap->size && heap->array[rightChildIndex] > heap->array[i]){
            largestIndex = rightChildIndex;
        }
        // i가 최댓값의 인덱스와 같으면 힙 속성을 만족하므로 종료
        if (i == largestIndex){
            break;
        }
        // 현재 노드와 최댓값 노드 교환
        int temp = heap->array[i];
        heap->array[i] = heap->array[largestIndex];
        heap->array[largestIndex] = temp;
        i = largestIndex;
    }
    return max;
}

// 최대 힙 정렬 함수
void heapSort(int arr[], int size){
    // 최대 힙 생성
    maxHeap *heap = createMaxHeap(size);
    // 배열의 모든 원소를 최대 힙에 삽입
    for(int i = 0; i < size; i++){
        insert(heap, arr[i]);
    }
    // 최대 힙에서 원소 추출
    for(int i = size - 1; i >= 0; i--){
        arr[i] = extractMax(heap);
    }
}

int main(){
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Original Array : \n");
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    heapSort(arr, size);
    printf("\n\nSorted Array (Descending Order): \n");
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}