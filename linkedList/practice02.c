/*

아래 주어진 예와 같이 n개의 노드를 포함하고 있는 단일 연결 리스트의 첫번째 절반의 노드 값이 수정하는 프로그램을 작성하시오.
단, 첫번째 노드의 새로운 값은 마지막 노드의 값에서 첫번째 노드의 현재 값을 뺀 것과 같아야 하며,
두번째 노드의 새로운 값은 두 번째에서 마지막 노드의 값을 뺀 것과 같아야 한다.
이러한 방식으로 첫번째 절반의 노드 값이 수정되어야 한다. 
만약 n이 홀수이면 중간 노드의 값은 변경되지 않아야하며, 추가적인 메모리는 사용하지 않아야 한다.

예시 1)
Input : 10 -> 4 -> 5 -> 3 -> 6
Output : 4 -> 1 -> 5 -> 3 -> 6

예시 2)
Input : 2 -> 9 -> 8 -> 12 -> 7 -> 10
Output : -8 -> 2 -> -4 -> 12 -> 7 -> 10

*/

// 이중 연결리스트 사용하기

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode{
    struct listNode *prev;
    int data;
    struct listNode *next;
} listNode;

typedef struct listNode *listPointer;

int main(){
    
}