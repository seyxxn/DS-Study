#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define noisy(x) (puts(#x), x)

void printRangeIterative(int start, int stop);
void printRangeRecursive(int start, int stop);
void printRangeRecursiveReversed(int start, int stop);
void printRangeRecursiveSplit(int start, int stop);

int main(int argc, char **argv){
    noisy(printRangeIterative(0,10));
    noisy(printRangeRecursive(0,10));
    noisy(printRangeRecursiveReversed(0,10));
    noisy(printRangeRecursiveSplit(0,10));
    return 0;
}

void printRangeIterative(int start, int stop){ // 반복문 사용
    int i;
    for(i = start; i < stop; i++){
        printf("%d\n", i);
    }
}

void printRangeRecursive(int start, int stop){ // 재귀 사용
    if (start < stop){
        printf("%d\n", start); // 출력 먼저
        printRangeRecursive(start + 1, stop); // 재귀 나중에 
    }
}

void printRangeRecursiveReversed(int start, int stop){ // 재귀 사용
    if (start < stop){
        printRangeRecursiveReversed(start+1, stop); // 재귀 먼저
        printf("%d\n", start); // 출력 나중에
    }
}

void printRangeRecursiveSplit(int start, int stop){ // 재귀 사용 (분할 정복 방식 사용)
    int mid;
    if(start < stop){
        mid = (start + stop) / 2;
        printRangeRecursiveSplit(start, mid);
        printf("%d\n", mid);
        printRangeRecursiveSplit(mid+1,stop);
    }
}

/*  오류 버전 */
void printRangeRecursiveSplitBad(int start, int stop){
    int mid;

    if (start == stop){
        printf("%d\n", start);
    }else{
        mid = (start+stop)/2;
        printRangeRecursiveSplitBad(start, mid);
        printf("%d\n", mid);
        printRangeRecursiveSplitBad(mid, stop); // mid+1로 수정해야 올바르다
    }
}