#include <stdio.h>
#include <stdlib.h>
int **arr;
int n;
void solve(int **a, int size);
int **copyArr(int **a, int row, int col, int size);

int main()
{
    scanf("%d", &n);
    arr = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        arr[i] = (int *)malloc(sizeof(int) * n);

    char line[n+1];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", line);
        for (int j = 0; j < n; j++)
        {
            arr[i][j] = line[j] - '0';
        }
    }

    solve(arr, n);
    printf("\n");
    return 0;
}

int **copyArr(int **a, int row, int col, int size)
{
    int **tempArr;
    tempArr = (int **)malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++)
        tempArr[i] = (int *)malloc(sizeof(int) * size);

    for (int i = 0, x = row; i < size; i++, x++)
        for (int j = 0, y = col; j < size; j++, y++)
            tempArr[i][j] = a[x][y];

    return tempArr;
}

void solve(int **a, int size)
{
    int firstElement = a[0][0];
    int arrEqual = 1;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (a[i][j] != firstElement)
            {
                arrEqual = 0;
                break;
            }

    if (arrEqual)
    {
        switch (firstElement)
        {
        case 0:
            printf("0");
            break;
        case 1:
            printf("1");
            break;
        }
    }
    else
    {
        printf("(");
        int **temp1 = copyArr(a, 0, 0, size / 2);
        solve(temp1, size / 2);

        int **temp2 = copyArr(a, 0, size / 2, size / 2);
        solve(temp2, size / 2);

        int **temp3 = copyArr(a, size / 2, 0, size / 2);
        solve(temp3, size / 2);

        int **temp4 = copyArr(a, size / 2, size / 2, size / 2);
        solve(temp4, size / 2);

        for (int i = 0; i < size / 2; i++)
        {
            free(temp1[i]);
            free(temp2[i]);
            free(temp3[i]);
            free(temp4[i]);
        }

        free(temp1);
        free(temp2);
        free(temp3);
        free(temp4);
        printf(")");
    }
}