#include <stdio.h>
#include <stdlib.h>
char **arr;
int n;
void solve(int row, int col, int size);

int main()
{
    scanf("%d", &n);                           // 가로 길이 n 입력받음
    arr = (char **)malloc(sizeof(char *) * n); // n행

    for (int i = 0; i < n; i++)
    {
        arr[i] = (char *)malloc(sizeof(char) * (2 * n - 1)); // 열은 2*n - 1
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 2 * n - 1; j++)
        {
            arr[i][j] = ' '; // 공백으로 초기화
        }
    }

    // 0, n-1 기준
    solve(0, n - 1, n);

    // 출력
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 2 * n - 1; j++)
        {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }

    // 메모리 해제
    for (int i = 0; i < n; i++)
    {
        free(arr[i]);
    }

    free(arr);

    return 0;
}

// 해당하는 부분만 * 로 변경하기
// 하나의 큰 삼각형을 3개의 삼각형으로 나눔
// row, col은 기준이 되는 좌표
// 가장 작은 삼각형 기준으로 가운데 맨 위 좌표를 기준으로 함
void solve(int row, int col, int size)
{
    // 가장 기본 패턴인 size == 3
    if (size == 3)
    {
        arr[row][col] = '*';
        arr[row + 1][col - 1] = '*';
        arr[row + 1][col + 1] = '*';
        for (int i = -2; i <= 2; i++)
        {
            arr[row + 2][col + i] = '*';
        }
        return;
    }

    solve(row, col, size / 2);
    solve(row + size / 2, col - size / 2, size / 2);
    solve(row + size / 2, col + size / 2, size / 2);
}