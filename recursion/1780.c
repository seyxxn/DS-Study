#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n;
int cntM1 = 0;
int cnt1 = 0;
int cnt0 = 0;
int **arr;

void solve(int **a, int size);
int **copyArr(int **arr, int row, int col, int size);

int main()
{
    scanf("%d", &n);
    arr = (int **)malloc(sizeof(int *) * n);
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

    solve(arr, n);
    printf("%d\n", cntM1);
    printf("%d\n", cnt0);
    printf("%d\n", cnt1);

    for (int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
    return 0;
}

int **copyArr(int **arr, int row, int col, int size)
{
    int **tempArr = (int **)malloc(sizeof(int *) * size);

    for (int i = 0; i < size; i++)
    {
        tempArr[i] = (int *)malloc(sizeof(int) * size);
    }

    for(int i = 0, x = row; i < size; i++, x++){
        for(int j = 0, y = col; j < size; j++, y++){
            tempArr[i][j] = arr[x][y];
        }
    }

    return tempArr;
}

void solve(int **a, int size)
{
    int arrEqual = 1; // 같은지 확인하는 변수
    int firstElement = a[0][0];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
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
        int **temp1 = copyArr(a, 0, 0, size / 3);
        solve(temp1, size / 3);

        int **temp2 = copyArr(a, 0, size / 3, size / 3);
        solve(temp2, size / 3);

        int **temp3 = copyArr(a, 0, 2 * (size / 3), size / 3);
        solve(temp3, size / 3);

        int **temp4 = copyArr(a, size / 3, 0, size / 3);
        solve(temp4, size / 3);

        int **temp5 = copyArr(a, size / 3, size / 3, size / 3);
        solve(temp5, size / 3);

        int **temp6 = copyArr(a, size / 3, 2 * (size / 3), size / 3);
        solve(temp6, size / 3);

        int **temp7 = copyArr(a, 2 * (size / 3), 0, size / 3);
        solve(temp7, size / 3);

        int **temp8 = copyArr(a, 2 * (size / 3), size / 3, size / 3);
        solve(temp8, size / 3);

        int **temp9 = copyArr(a, 2 * (size / 3), 2 * (size / 3), size / 3);
        solve(temp9, size / 3);

        for (int i = 0; i < size / 3; i++)
        {
            free(temp1[i]);
            free(temp2[i]);
            free(temp3[i]);
            free(temp4[i]);
            free(temp5[i]);
            free(temp6[i]);
            free(temp7[i]);
            free(temp8[i]);
            free(temp9[i]);
        }

        free(temp1);
        free(temp2);
        free(temp3);
        free(temp4);     
        free(temp5);
        free(temp6);
        free(temp7);
        free(temp8);
        free(temp9);
    }
}
