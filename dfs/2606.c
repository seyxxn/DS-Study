// DFS로 풀이
#include <stdio.h>
#include <stdlib.h>

int n, edge;
int graph[101][101];
int visited[101] = {0};
int ans = 0;

void graphConnection(int x, int y){
    graph[x][y] = 1;
    graph[y][x] = 1;
}

void printGraph(){
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void dfs(int start){
    visited[start] = 1; // 시작 정점 방문 표시
    
    for(int i = 1; i <= n; i++){
        if (graph[start][i] == 1 && visited[i] == 0){
            ans++;
            dfs(i);
        }
    }
}

int main(){
    scanf("%d", &n);
    scanf("%d", &edge);
    
    for(int i = 0; i < edge; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        graphConnection(x, y);
    }

    dfs(1);
    printf("%d\n", ans);

    return 0;
}