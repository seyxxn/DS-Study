// 큐를 이용한 너비우선탐색(BFS) 프로그램 
// 큐를 배열로 구현
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10

typedef int element;

typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

// 오류함수
void error(const char * message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 큐 초기화
void queue_init(QueueType *q){
    q->front = q->rear = 0;
}

// 공백 상태 검출
int is_empty(QueueType *q){
    return (q->front == q->rear);
}

// 포화 상태 검출
int is_full(QueueType *q){
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 큐 삽입
void enqueue(QueueType *q, element item)
{
    if(is_full(q)) error("Queue is full");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

// 큐 삭제
element dequeue(QueueType *q){
    if(is_empty(q)) error("Queue is empty");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

#define MAX_VERTICES 50

typedef struct GraphType
{
    int n;
    int adj_mat[MAX_VERTICES][MAX_QUEUE_SIZE];
} GraphType;

int visited[MAX_VERTICES];

// 그래프 초기화
void graph_init(GraphType *g)
{
    int r, c;
    g->n = 0;
    for(r = 0; r < MAX_VERTICES; r++)
        for(c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}

// 정점 삽입 연산
void insert_vertex(GraphType *g, int v)
{
    if(((g -> n) + 1) > MAX_VERTICES){
        fprintf(stderr, "graph : full vertices");
        return ;
    }
    g -> n++;
}

// 정점 u에 간선 (u,v)를 삽입하는 연산
void insert_edge(GraphType *g, int start, int end)
{
    if (start >= g->n || end >= g->n){
        fprintf(stderr, "graph : edge number error");
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

void bfs_mat(GraphType *g, int v)
{
    int w;
    QueueType q;

    queue_init(&q); // 큐 초기화

    visited[v] = TRUE; // 정점 v 방문 표시
    printf("%d visited -> ", v);
    enqueue(&q, v); // 시작 정점을 큐에 저장
    while(!is_empty(&q)){
        v = dequeue(&q); // 큐에 정점을 추출
        for(w = 0; w < g->n; w++) // 인접 정점 탐색
            if (g->adj_mat[v][w] && !visited[w]){
                visited[w] = TRUE; // 방문 표시
                printf("%d visited -> ", w);
                enqueue(&q, w); // 방문한 정점을 큐에 저장
            }
    }
}

int main(){
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));

    graph_init(g);
    for(int i = 0; i < 6; i++) insert_vertex(g, i);

    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 4);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 4);
    insert_edge(g, 2, 4);

    bfs_mat(g, 0);
    printf("\n");

    free(g);
    return 0;
}

