#include <stdio.h>
#include <stdlib.h>

int n, cnt = 0;
int *temp;

void nqueens(int col);

int main(void)
{
    scanf("%d", &n); // 사용자에게 N의 크기를 입력 받음
    temp = (int *)malloc(sizeof(int) * n); // 동적할당

    if (temp == NULL) // 메모리 할당 실패
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) 
    {
        temp[0] = i; // 0행 i열에 퀸을 놓고
        nqueens(1); // 1열부터 배치한다.
    }

    printf("%d\n", cnt);

    free(temp);

    return 0;
}

void nqueens(int col)
{
    if (col == n) // 모든 열에 퀸이 배치된 경우, 해를 찾은 경우이므로 cnt 증가
    {
        cnt += 1;
        return ;
    }

    for (int i = 0; i < n; i++) // 반복문을 통해 현재 열에 대해 가능한 퀸의 위치를 시도
    {
        int check = 1; // 퀸을 놓을 수 있는지 여부를 나타내는 변수
        for (int j = 0; j < col; j++) // 현재 열 이전의 열들에 대해 반복
        {
            temp[col] = i; // 현재 열에 퀸을 i번째 행에 놓는 시도
            if (temp[j] == temp[col] || abs(j-col) == abs(temp[j] - temp[col]))
            { // 현재 위치가 이전 열에 배치된 퀸들과 충돌하는지 확인 (같은 행에 퀸이 있는지, 대각선에 있는지)
                check = 0; // 충돌 발생시, check = 0으로 설정하고 반복문 탈출
                break;
            }
        }

        // 퀸을 계속 놓을 수 있다면, 다음 열로 넘어감
        if (check){
            nqueens(col + 1);
        }
    }
}