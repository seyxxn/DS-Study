#include <stdio.h>
#include <stdlib.h>
int n;
int **arr;
void solve(int size, int row, int col);

int main()
{
    scanf("%d", &n);

    arr = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * n);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j] = 1; // 1로 초기화
        }
    }

    solve(n, 0, 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[i][j] == 1) // 1인 부분은 *로 출력
            {
                printf("*");
            }
            else if (arr[i][j] == 0)
            {
                printf(" "); // 0인 부분은 공백으로 출력
            }
        }
        printf("\n");
    }
}

void solve(int size, int row, int col)
{   
    // 여기 반복분 조건 주의 **
    for (int i = row + size / 3; i < row + 2 * (size / 3); i++)
    {
        for (int j = col + size / 3; j < col + 2 * (size / 3); j++)
        {
            arr[i][j] = 0;
        }
    }

    if (size == 3) // n == 3 인 패턴이 기본이므로 3에 도달하면 끝
        return;

    // 9개로 나눔
    // row, col 더해주는 것 주의 **
    solve(size / 3, row, col);
    solve(size / 3, row, col + size / 3);
    solve(size / 3, row, col + 2 * (size / 3));

    solve(size / 3, row + size / 3, col);
    solve(size / 3, row + size / 3, col + size / 3);
    solve(size / 3, row + size / 3, col + 2 * (size / 3));

    solve(size / 3, row + 2 * (size / 3), col);
    solve(size / 3, row + 2 * (size / 3), col + size / 3);
    solve(size / 3, row + 2 * (size / 3), col + 2 * (size / 3));
}