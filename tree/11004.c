#include <stdio.h>
#include <stdlib.h>
int n,k;
typedef struct minHeap{
    int *array;
    int capacity;
    int size;
} minHeap;

minHeap *heap;

minHeap * createHeap(int capacity){
    minHeap *heap = (minHeap *)malloc(sizeof(minHeap));
    heap->array = (int *)malloc(sizeof(int) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

int getParentIndex(int index){
    return (index -1)/2;
}

void insertHeap(minHeap *heap, int value){
    if (heap->size >= heap->capacity){
        return ;
    }

    int i = heap->size;
    heap->array[i] = value;
    heap->size++;

    while(i != 0 && heap->array[i] < heap->array[getParentIndex(i)]){
        int temp = heap->array[i];
        heap->array[i] = heap->array[getParentIndex(i)];
        heap->array[getParentIndex(i)] = temp;

        i = getParentIndex(i);
    }
}

int extractHeap(minHeap *heap){
    if (heap->size <= 0){
        return -1;
    }

    int min = heap->array[0];
    
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    int i = 0;
    while(1){
        int leftChildIndex = 2 * i + 1;
        int rightChildIndex = 2 * i + 2;
        int smallestIndex = i;

        if (leftChildIndex < heap->size && heap->array[i] > heap->array[leftChildIndex]){
            smallestIndex = leftChildIndex;
        }

        if (rightChildIndex < heap->size && heap->array[smallestIndex] > heap->array[rightChildIndex]){
            smallestIndex = rightChildIndex;
        }

        if (i == smallestIndex){
            break;
        }

        int temp = heap->array[i];
        heap->array[i] = heap->array[smallestIndex];
        heap->array[smallestIndex] = temp;

        i = smallestIndex;
    }

    return min;
}


int main(){
    scanf("%d %d", &n, &k);
    heap = createHeap(5000001);

    for(int i = 0; i < n; i++){
        int num;
        scanf("%d", &num);
        insertHeap(heap, num);
    }
    
    for(int i = 1; i <= k; i++){
        if(i == k){
            printf("%d", extractHeap(heap));
        }else{
            extractHeap(heap);
        }
    }

}