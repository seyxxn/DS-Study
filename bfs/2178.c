#include <stdio.h>
#include <stdlib.h>
int n, m;
int graph[101][101] = {0};
int visited[101][101] = {0};
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int ans = 0;

typedef struct QueuePoint
{
    int x;
    int y;
} QueuePoint;

typedef struct QueueType
{
    QueuePoint queue[10001];
    int front, rear;
} QueueType;

void queue_init(QueueType *q)
{
    q->front = q->rear = 0;
}

int is_empty(QueueType *q)
{
    return (q->front == q->rear);
}

int is_full(QueueType *q)
{
    return ((q->rear + 1) == q->front);
}

void enqueue(QueueType *q, QueuePoint item)
{
    if (is_full(q)) return ;
    q->rear = q->rear + 1;
    q->queue[q->rear] = item;
}

void error(const char * message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

QueuePoint dequeue(QueueType *q)
{
    if (is_empty(q)) error("Queue is empty");
    q->front = q->front + 1;
    return q->queue[q->front];
}

// 프린트 테스트 함수
void graphPrint(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int bfs(int x, int y)
{
    QueueType q;   // 큐 생성
    queue_init(&q); // 큐 초기화

    visited[x][y] = 1; // 시작 정점을 방문 표시
    printf("%d %d visited -> \n", x, y);

    QueuePoint item;
    item.x = x;
    item.y = y;
    enqueue(&q, item); // 시작 정점을 큐에 저장
    // graphPrint();

    while (!is_empty(&q))
    {
        QueuePoint dequeItem;
        dequeItem = dequeue(&q);
        x = dequeItem.x;
        y = dequeItem.y;

        // 인접 정점 탐색
        for (int w = 0; w < 4; w++){
            int nx = x + dx[w];
            int ny = y + dy[w];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (graph[nx][ny] == 0) continue;
            if (graph[nx][ny] == 1 && visited[nx][ny] == 0){
                visited[nx][ny] = 1; // 방문 표시
                printf("%d %d visited -> \n", nx, ny);
                graph[nx][ny] = graph[x][y] + 1; // 현재까지의 거리
                // graphPrint();

                QueuePoint enqueItem;
                enqueItem.x = nx;
                enqueItem.y = ny;
                enqueue(&q, enqueItem);
            }
        }
    }
    
    return graph[n-1][m-1];
}

int main()
{
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%1d", &graph[i][j]);
        }
    }

    printf("%d\n", bfs(0,0));

    return 0;
}