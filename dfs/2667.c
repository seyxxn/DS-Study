#include <stdio.h>
#include <stdlib.h>
int n;
int graph[26][26];
int visited[26][26] = {0};
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int ans = 0;

void dfs(int x, int y)
{
    ans++;
    visited[x][y] = 1;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 1 || nx > n || ny < 1 || ny > n)
            continue;
        if (graph[nx][ny] == 0)
            continue;
        if (graph[nx][ny] == 1 && visited[nx][ny] == 0)
        {
            dfs(nx, ny);
        }
    }
}

void insertSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%1d", &graph[i][j]);
        }
    }

    // int ansNum[26];
    int *ansNum = malloc(n * n * sizeof(int)); // 동적으로 할당
    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (graph[i][j] == 1 && visited[i][j] == 0)
            {
                ans = 0;
                dfs(i, j);
                ansNum[count] = ans;
                count++;
            }
        }
    }

    printf("%d\n", count);

    insertSort(ansNum, count);

    for (int i = 0; i < count; i++)
    {
        printf("%d\n", ansNum[i]);
    }

    return 0;
}