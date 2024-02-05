#include <stdio.h>
#include <stdlib.h>
int n, cnt = 0;
int *temp;

void nqueens(int col);

int main()
{
    scanf("%d", &n);

    temp = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        temp[0] = i;
        nqueens(1);
    }

    printf("%d\n", cnt);
    free(temp);

    return 0;
}

void nqueens(int col)
{
    if (col == n)
    {
        cnt += 1;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        int check = 1;
        for (int j = 0; j < col; j++)
        {
            temp[col] = i;
            if (temp[j] == temp[col] || abs(j - col) == abs(temp[j] - temp[col]))
            {
                check = 0;
                break;
            }
        }

        if (check)
        {
            nqueens(col + 1);
        }
    }
}
