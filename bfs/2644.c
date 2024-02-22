// bfs : 너비우선함수
#include <stdio.h>
#include <stdlib.h>
int n, a, b, m;
int visited[101] = {0};
int graph[101][101] = {0};
int queue[101] = {0};
int front = -1, rear = -1, pop;
int bfs(int x, int y);

int main(){
    scanf("%d", &n);
    scanf("%d %d", &a, &b);
    scanf("%d", &m);

    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x][y] = 1;
        graph[y][x] = 1;
    }

    int result = bfs(a, b);
    printf("%d\n", result);

    return 0;
}

int bfs(int x, int y){
    int ans = 0;
    visited[x] = 1; // 시작정점 방문 표시
    queue[++rear] = x;

    while(front < rear) // 큐가 빌때까지 반복
    {
        pop = queue[++front]; // pop
        for(int i = 1; i <= n; i++){
            if (graph[pop][i] == 1 && visited[i] == 0){ // 인접해있고 방문하지 않은 노드라면
                ans++;
                visited[i] = 1; // 방문
                queue[++rear] = i; // 큐에 삽입
            }
        }
    }

    return ans;
}

