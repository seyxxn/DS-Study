// BFS와 DFS
#include <stdio.h>
#include <stdlib.h>
int graph[1001][1001] = {0};
int visitedDFS[1001] = {0};
int visitedBFS[1001] = {0};
int queue[1001];

void BFS(int v, int n);
void DFS(int v, int n);

int main(){
    int n, m, v; // n : 정점의 개수, m : 간선의 개수, v : 시작 정점의 번호
    int x, y;

    scanf("%d %d %d", &n, &m, &v);

    // m개의 간선의 연결 정보를 graph 배열에 저장
    for(int i = 0; i < m; i++){
        scanf("%d %d", &x, &y);
        graph[x][y] = 1;
        graph[y][x] = 1;
    }

    DFS(v, n);
    printf("\n");
    BFS(v, n);

    return 0;
}

// 깊이 우선 탐색 -> 재귀함수 이용
void DFS(int v, int n){
    visitedDFS[v] = 1; // 정점에 방문했음을 표시
    printf("%d ", v); // 방문 후 출력
    
    // n번 반복 (정점의 개수만큼 출력해야하니까. 모두 방문해야하니까)
    for(int i = 1; i <= n; i++){
        // 정점이 존재하고 && 방문한 적이 없는 경우
        if (graph[v][i] == 1 && visitedDFS[i] == 0)
            DFS(i, n);
    }
    return ; 
}

// 너비 우선 탐색 -> 큐 이용
void BFS(int v, int n){
    int front = 0, rear = 0;
    int pop; 

    // 시작정점을 방문하고, 방문표시하고, 해당 정점을 큐에 넣음
    printf("%d ", v); 
    queue[0] = v;
    rear++;
    visitedBFS[v] = 1;

    // 큐가 비어있지 않은 동안 반복 (큐가 빌때까지 반복한다는 뜻)
    while(front < rear){
        // 큐에서 정점을 꺼낸다.
        pop = queue[front];
        front++;
        // 꺼낸 정점과 연결된 모든 인접 정점을 방문한다.
        for(int i = 1; i <= n; i++){
            // 꺼낸 정점과 인접해 있고 && 방문하지 않았던 노드라면 
            if (graph[pop][i] == 1 && visitedBFS[i] == 0){
                // 해당 정점을 방문하고 큐에 넣음
                printf("%d ", i);
                queue[rear] = i;
                rear++;
                visitedBFS[i] = 1;
            }
        }
    }
    return;
}