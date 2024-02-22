// DFS : 깊이 우선 탐색
#include <stdio.h>
#include <stdlib.h>
int N, A, B, M;
int graph[101][101] = {0};
int visited[101] = {0};
int ans = 0;

void dfs(int a, int b);
void graphPrint();
void visitedPrint();

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

    dfs(A, B);

    printf("%d\n", ans);

    return 0;
}

void dfs(int a, int b)
{
    int i;
    visited[a] = 1; // 시작 정점 방문표시

    for (i = 1; i <= N; i++)
    {
        if (graph[a][i] == 1 && visited[i] == 0)
        {
            ans++;
            visited[i] = 1;
            dfs(i, b);
        }
    }

    if (visited[b] == 0){
        ans = -1;
    }
}

void graphPrint(){
    printf("graphPrint \n");
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void visitedPrint(){
    printf("visitedPrint \n");
    for(int i = 1; i <= N; i++){
        printf("%d ", visited[i]);
    }
    printf("\n");
}