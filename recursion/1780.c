#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n;
int cntM1 = 0;
int cnt1 = 0;
int cnt0 = 0;

double log_base_3(double x)
{
    return log(x) / log(3);
}

void solve(int **a, int row, int col);

int main()
{
    scanf("%d", &n);
    int **arr = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * n);
    }

    int num;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    solve(arr, n, n);
    printf("%d\n", cntM1);
    printf("%d\n", cnt0);
    printf("%d\n", cnt1);

    for (int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
    return 0;
}

void solve(int **a, int row, int col)
{
    int arrEqual = 1; // 같은지 확인하는 변수
    int firstElement = a[0][0];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (a[i][j] != firstElement)
            {
                arrEqual = 0;
                break;
            }
        }
    }

    if (arrEqual) // 배열의 값이 모두 같은 수로 되어있다면
    {
        switch (firstElement)
        {
        case -1:
            cntM1++;
            break;
        case 0:
            cnt0++;
            break;
        case 1:
            cnt1++;
            break;
        }
    } // 같은 수로 되어있지 않다면, 9개로 자르고 재귀함수 사용
    else
    {
        
    }
}
