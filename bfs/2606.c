#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 101

int n, edge;
int graph[MAX_SIZE][MAX_SIZE] = {0}; // 그래프를 나타내는 변수
int visited[MAX_SIZE] = {0}; // 방문 여부
int queue[MAX_SIZE]; // bfs 구현을 위한 큐
int front = -1; 
int rear = -1;
int ans = 0; // 바이러스 걸리게 되는 컴퓨터의 수

void graphConnection(int x, int y){
    graph[x][y] = 1;
    graph[y][x] = 1;
}

void graphPrint(){
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int is_empty(){
    return (front == rear);
}

int is_full(){
    return (rear == MAX_SIZE - 1);
}

void enqueue(int x){
    if (is_full()) return ;
    rear = rear + 1;
    queue[rear] = x; 
}

int dequeue(){
    if (is_empty()) return -1;
    front = front + 1;
    return queue[front];
}

void printQueue(){
    printf("Queue : ");
    for(int i = front + 1; i <= rear; i++){
        printf("%d ", queue[i]);
    }
    printf("\n");
}

void bfs(int start){
    visited[start] = 1; // 시작 정정 방문
    enqueue(start); // 큐에 넣기
    // printf("initial Queue \n");
    // printQueue();

    while(!is_empty()){
        int dequeItem = dequeue();
        for(int i = 1; i <= n; i++){
            if (graph[dequeItem][i] == 1 && visited[i] == 0){
                visited[i] = 1;
                enqueue(i);
                // printQueue();
                ans++;
            }
        }
    }

    printf("%d\n", ans);
}

int main(){
    scanf("%d", &n); // 컴퓨터의 수
    scanf("%d", &edge); // 간선의 수
    
    for(int i = 0; i < edge; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        graphConnection(x, y);
    }
    // graphPrint();

    bfs(1);
    
    return 0;
}