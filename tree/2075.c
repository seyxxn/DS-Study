// 최대힙으로 구현해보기
// n번째 큰 수

#include <stdio.h>
#include <stdlib.h>
int n;

typedef struct maxHeap{
    int *array;
    int capacity;
    int size;
} maxHeap;

maxHeap *heap;

maxHeap *createHeap(int capacity){
    maxHeap *heap = (maxHeap *)malloc(sizeof(maxHeap));
    heap->array = (int *)malloc(sizeof(int) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

int getParentIndex(int index){
    return (index - 1)/ 2;
}

void insertHeap(maxHeap *heap, int value){
    if(heap->size >= heap->capacity){
        return ;
    }

    int i = heap->size;
    heap->array[i] = value;
    heap->size++;

    while(i != 0 && heap->array[i] > heap->array[getParentIndex(i)]){
        int temp = heap->array[i];
        heap->array[i] = heap->array[getParentIndex(i)];
        heap->array[getParentIndex(i)] = temp;

        i = getParentIndex(i);
    }
}

int extractMax(maxHeap *heap){
    if(heap->size <= 0){
        return -1;
    }

    int max = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    int i = 0;
    while(1){
        int leftChildIndex = 2 * i + 1;
        int rightChildIndex = 2 * i + 2;
        int largestIndex = i;

        if (leftChildIndex < heap->size && heap->array[leftChildIndex] > heap->array[i]){
            largestIndex = leftChildIndex;
        }

        if (rightChildIndex < heap->size && heap->array[rightChildIndex] > heap->array[largestIndex]){
            largestIndex = rightChildIndex;
        }

        if (i == largestIndex){
            break;
        }

        int temp = heap->array[i];
        heap->array[i] = heap->array[largestIndex];
        heap->array[largestIndex] = temp;
        i = largestIndex;
    }

    return max;
}

void printHeap(maxHeap *heap){
    printf("printHeap : ");
    for(int i = 0; i < heap->size; i++){
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}



int main(){
    scanf("%d", &n);
    heap = createHeap(1501 * 1501);
    int num;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &num);
            insertHeap(heap, num);
            // printHeap(heap);
        }
    }


    for(int i = 1; i <= n; i++){
        if (i == n){
            printf("%d", extractMax(heap));
            // printHeap(heap);
        }else{
            extractMax(heap);
            // printHeap(heap);
        }
    }

}