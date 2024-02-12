#include <stdio.h>
#include <stdlib.h>
int graph[1001][1001] = {0};
int visitedBFS[1001] = {0};
int visitedDFS[1001] = {0};
int queue[1001];

void dfs(int v, int n);
void bfs(int v, int n);

int main(){
    int N, M, V;
    scanf("%d %d %d", &N, &M, &V);
    for(int i = 0; i < M; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x][y] = 1;
        graph[y][x] = 1;
    }

    dfs(V, N);
    printf("\n");
    bfs(V, N);

    return 0;
}

void dfs(int v, int n){
    visitedDFS[v] = 1;
    printf("%d ", v);

    for(int i = 1; i <= n; i++){
        if(graph[v][i] == 1 && visitedDFS[i] == 0){
            dfs(i, n);
        }
    }
    return ;
}

void bfs(int v, int n){
    int front = 0, rear = 0, pop;

    printf("%d ", v);
    visitedBFS[v] = 1;
    queue[0] = v;
    rear++;

    while(front < rear){
        pop = queue[front];
        front++;
        for(int i = 1; i <= n; i++){
            if (graph[pop][i] == 1 && visitedBFS[i] == 0){
                printf("%d ", i);
                visitedBFS[i] = 1;
                queue[rear] = i;
                rear++;
            }
        }
    }
    return ;
}