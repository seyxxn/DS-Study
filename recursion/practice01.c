#include <stdio.h>
#include <stdlib.h>

int n;
int *arr; // 1차원 배열 사용 (하나의 이진 수열을 저장하는 1차원 배열 사용)

// 배열을 출력하는 함수를 선언
void printArray(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d", array[i]);
    }
    printf("\n");
}

// 재귀함수
// index : 현재 출력하고 있는 인덱스
// size : 이진 순열의 길이
// sumLeft : 왼쪽 순열의 합
// sumRight : 오른쪽 순열의 합
void solve(int index, int size, int sumLeft, int sumRight)
{
    // 현재 출력하고 있는 인덱스와 크기가 같아졌다면, 끝까지 다 출력한 것임
    if (index == size)
    {
        if (sumLeft == sumRight)
        {                          // 이때 왼쪽 순열과 오른쪽 순열의 합이 같아면, 출력해야하는 순열에 속함
            printArray(arr, size); // 출력
        }
        return;
        // 조건이 만족되면 배열의 내용을 출력한 후 함수를 종료하고, 만족되지 않으면 함수를 종료해야하므로
        // return 반드시 필요
    }

    // 이진수열에서 가능한 선택 (0 혹은 1 이다.)

    // 첫번째, 현재 위치에 0을 설정
    arr[index] = 0;
    solve(index + 1, size, sumLeft + (index < n ? arr[index] : 0), sumRight + (index >= n ? arr[index] : 0));
    // solve 함수로 다음 인덱스로 넘어감
    // 다음 인덱스로 넘어가기 때문에 index + 1
    // size는 동일

    // 여기서 n은 중간의 기준이 되는 인덱스
    // sumLeft는 왼쪽 순열의 합.
    // index < n -> 참이면, 현재 출력하고 있는 인덱스는 왼쪽 순열에 속함. 그러므로, sumLeft에 arr[index]를 더함
    //           -> 거짓이면, 현재 출력하고 있는 인덱스는 오른쪽 순열에 속함. 그러므로, sumLeft에 0을 더함
    // sumRight는 오른쪽 순열의 합
    // index >= n -> 참이면, 현재 출력하고 있는 인덱스는 오른쪽 순열에 속함. 그러므로, sumRight에 arr[index]를 더함
    //            -> 거짓이면, 현재 출력하고 있는 인덱스는 왼쪽 순열에 속함. 그러므로, sumRight에 0을 더함

    // 어차피 arr[index] = 0; 이기 때문에 사실상 이 코드는
    // solve(index+1, size, sumLeft, sumRight); 로 써도 무방하다.
    // 하지만 코드의 이해를 위해 풀어씀

    // 두번째, 현재 위치에 1을 설정
    arr[index] = 1;
    solve(index + 1, size, sumLeft + (index < n ? arr[index] : 0), sumRight + (index >= n ? arr[index] : 0));
    // index < n -> 참이면, 현재 출력하고 있는 인덱스는 왼쪽 순열에 속함. 그러므로, sumleft에 arr[index]를 더함
    //           -> 거짓이면, 현재 출력하고 있는 인덱스는 오른쪽 순열에 속함. 그러므로, sumleft에 0을 더함
    // index >= n -> 참이면, 현재 출력하고 있는 인덱스는 오른쪽 순열에 속함. 그러므로, sumRight에 arr[index]를 더함
    //            -> 거짓이면, 현재 출력하고 있는 인덱스는 왼쪽 순열에 속함. 그러므로, sumRight에 0을 더함

    // arr[index] = 1; 이기에
    // solve(index+1, size, sumLeft + (index < n ? 1 : 0), sumRight + (index >= n ? 1 : 0)); 로 써도 같은 코드다.
}

int main()
{
    printf("Input\n");
    printf("N = "); // 사용자에게 n의 값 입력받기
    scanf("%d", &n);

    printf("Output\n");

    // 1차원 배열 동적 할당 (길이는 2n)
    arr = (int *)malloc(sizeof(int) * 2 * n);
    solve(0, 2 * n, 0, 0);
    free(arr); // 메모리 해제

    return 0;
}
