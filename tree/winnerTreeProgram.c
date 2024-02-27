#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 승자트리를 구현한 구조체
typedef struct
{
    int *tree;     // 승자 트리를 저장하는 배열
    int numLeaves; // 단말 노드(리프)의 개수
} WinnerTree;

// 승자 트리 초기화
// 인수로 승자트리포인터, 단말개수, 런 을 받는다.
void initializeWinnerTree(WinnerTree *wt, int n, int *runs)
{
    wt->numLeaves = n;

    // 승자 트리의 크기를 계산한다.
    // 승자 트리는 완전 이진 트리이기 때문에 단말 노드의 개수를 기반으로 계산한다.
    int size = 1;
    while (size < n)
    {
        size *= 2; // 이진트리이므로 2배씩 늘린다.
    }

    wt->tree = (int *)malloc(sizeof(int) * (size * 2));
    // size * 2 인 이유 ?
    // 각 노드가 최대 두 개의 자식을 가질 수 있기 때문 (이해안됨)**
    for (int i = 0; i < size * 2; ++i)
    {
        wt->tree[i] = INT_MAX; // 초기값으로 무한대 설정 (가장 작은 값을 찾아야해서)
    }

    // 단말 노드에 초기값을 할당한다.
    for (int i = 0; i < n; ++i)
    {
        wt->tree[i + size] = runs[i];
    }

    // 승자 트리를 구성한다. (아래에서 부터)
    for (int i = size - 1; i >= 1; --i)
    {
        wt->tree[i] = (wt->tree[i * 2] < wt->tree[i * 2 + 1] ? wt->tree[i * 2] : wt->tree[i * 2 + 1]);
        // 왼쪽 자식 < 오른쪽 자식 ? 왼쪽 자식이 작은 경우 : 오른쪽 자식이 작은 경우
    }
}

// 최솟값 선택과 승자 트리 업데이트
int selectMin(WinnerTree *wt){
    int winner = wt->tree[1]; // 루트 노드에 저장된 최소값을 선택
    int index = wt->numLeaves + winner - 1; // 선택된 값의 인덱스
    // int index = wt->numLeaves + winner;
    // 선택된 값의 인덱스를 업데이트하고 해당 값은 무한대로 설정 => 트리에서 삭제하는 의미

    // 아래에서부터 승자 트리 구성
    while (index > 0){
        wt->tree[index] = INT_MAX; // 선택된 값
        index /= 2;
    }
    return winner;
}

// 승자 트리 메모리 해제
void freeWinnerTree(WinnerTree *wt){
    free(wt->tree);
}

int main(){
    // 임의의 런 3개
    int runs1[] = {1,4,7};
    int runs2[] = {2,5,8};
    int runs3[] = {3,6,9};
    int numLeaves = 3; // 단말노드개수 3개
    WinnerTree winnerTree; // 승자트리 선언
    initializeWinnerTree(&winnerTree, numLeaves, runs1); // 승자트리 초기화
    printf("Sorted Sequence : ");
    for(int i = 0; i < numLeaves; ++i){
        int minVal = selectMin(&winnerTree); // 최소값 찾기
        printf("%d ", minVal);
    }
    // **numLeaves = 3인데 어떻게 9개가 출력 ???**

    printf("\n");
    freeWinnerTree(&winnerTree);
    return 0;
}

// 올바른 출력 값 : 1 2 3 4 5 6 7 8 9
// 현재 출력 : 1 2147483647 2147483647 
// 코드 이상함 *****