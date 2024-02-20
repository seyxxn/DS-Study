// DFS : 깊이 우선 탐색
#include <stdio.h>
#include <stdlib.h>
int N, A, B, M;
int graph[101][101] = {0};
int visited[101] = {0};
int ans = 0;

void dfs(int a, int b);

int main()
{
    scanf("%d", &N);
    scanf("%d %d", &A, &B);
    scanf("%d", &M);

    for (int i = 0; i < M; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x][y] = 1;
        graph[y][x] = 1;
    }

    if (A <= B)
        dfs(A, B);
    else
        dfs(B, A);

    printf("%d\n", ans);

    return 0;
}

void dfs(int a, int b)
{
    int i;
    visited[a] = 1; // 시작 정점 방문표시

    for (i = 1; visited[b] == 0; i++)
    {
        if (i > N)
        {
            ans = -1;
            return;
        }

        if (graph[a][i] == 1 && visited[i] == 0)
        {
            ans++;
            printf("i : %d, ans : %d \n", i, ans);
            visited[i] = 1;
            dfs(i, b);
        }
    }
}