#include <stdio.h>
#include <stdlib.h>
int n;
int **a;
void solve(int **arr, int size);
int cnt0; // 하얀색
int cnt1; // 파란색
int **copyArr(int **arr, int row, int col, int size);

int main()
{
    scanf("%d", &n);
    a = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        a[i] = (int *)malloc(sizeof(int) * n);

    int num;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    solve(a, n);

    printf("%d\n", cnt0);
    printf("%d\n", cnt1);

    for (int i = 0; i < n; i++)
        free(a[i]);
    free(a);

    return 0;
}

// 2차원 배열을 복사하는 함수
int **copyArr(int **arr, int row, int col, int size)
{
    int **tempArr = (int **)malloc(sizeof(int *) * size);

    for (int i = 0; i < size; i++)
        tempArr[i] = (int *)malloc(sizeof(int) * size);

    for (int i = 0, x = row; i < size; i++, x++)
    {
        for (int j = 0, y = col; j < size; j++, y++)
        {
            tempArr[i][j] = arr[x][y];
        }
    }

    return tempArr;
}

void solve(int **arr, int size)
{
    int arrEqual = 1; // 배열 내의 값이 같은지 확인하는 변수
    int firstNum = arr[0][0];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (arr[i][j] != firstNum)
            {
                arrEqual = 0;
                break;
            }

    if (arrEqual)
    {
        switch (firstNum)
        {
        case 1:
            cnt1++;
            break;

        case 0:
            cnt0++;
            break;
        }
    }
    else // 같은수로 되어있지 않다면, 4개로 자르고 재귀함수 사용
    {
        int **temp1 = copyArr(arr, 0, 0, size / 2);
        solve(temp1, size / 2);

        int **temp2 = copyArr(arr, 0, size / 2, size / 2);
        solve(temp2, size / 2);

        int **temp3 = copyArr(arr, size / 2, 0, size / 2);
        solve(temp3, size / 2);

        int **temp4 = copyArr(arr, size / 2, size / 2, size / 2);
        solve(temp4, size / 2);

        for(int i = 0; i < size / 2; i++){
            free(temp1[i]);
            free(temp2[i]);
            free(temp3[i]);
            free(temp4[i]);
        }

        free(temp1);
        free(temp2);
        free(temp3);
        free(temp4);
    }
}