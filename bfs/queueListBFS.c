// 큐를 이용한 너비우선탐색(BFS) 프로그램
// 큐를 연결리스트로 구현

#include <stdio.h>
#include <stdlib.h>

// 정점을 나타내는 구조체
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 큐를 나타내는 구조체
typedef struct Queue
{
    Node *front;
    Node *rear;
} Queue;

// 새로운 노드 생성
Node *newNode(int data){
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// 새로운 큐 생성
Queue * createQueue(){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// 큐가 비었는지 확인
int isEmpty(Queue *queue){
    return (queue->front == NULL);
}

// 큐에 노드 추가
void enqueue(Queue *queue, int data){
    Node *node = newNode(data);

    if (isEmpty(queue)){
        queue->front = queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
}

// 큐에서 노드 제거 및 반환
int deque(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty.\n");
        return -1;
    }

    Node *temp = queue->front;
    int data =  temp->data;
    queue->front = queue->front->next;

    free(temp);
    return data;
}

// bfs 함수
void bfs(int **graph, int vertices, int start){
    // 방문할 노드를 표시할 배열 
    int *visited = (int *)malloc(vertices * sizeof(int));
    Queue *queue = createQueue(); // 큐 생성

    // visited 배열 초기화
    for (int i = 0; i < vertices; i++)
        visited[i] = 0;
    
    visited[start] = 1; // 시작 노드를 방문 처리
    enqueue(queue, start); // 시작 노드를 큐에 추가

    while(!isEmpty(queue)){
        int current = deque(queue); // 큐에서 노드를 하나 꺼내옴
        printf("%d ", current); // 노드 방문 순서를 출력

        // 현재 노드의 이웃 노드들을 탐색
        for(int i = 0; i < vertices; i++){
            if (graph[current][i] == 1 && !visited[i]) // 연결되어있고 아직 방문하지 않은 노드인 경우
            {
                visited[i] = 1; // 노드 방문 처리
                enqueue(queue, i); // 큐에 추가
            }
        }
    }

    free(visited);
    free(queue);
}

int main(){
    int vertices = 6; // 그래프 정점의 수
    int **graph = (int **)malloc(vertices * sizeof(int *)); // 그래프를 인접 행렬로 표현

    for(int i = 0; i < vertices; i++){
        graph[i] = (int *)malloc(vertices * sizeof(int));
    }

    int edges[6][6] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 0},
        {1, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 1},
        {0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 0}
    };

    // 인접행렬에 복사
    for(int i = 0 ;i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            graph[i][j] = edges[i][j];
        }
    }

    printf("BFS traversal starting from vertex 0 : ");
    bfs(graph, vertices, 0);

    for(int i = 0; i < vertices; i++){
        free(graph[i]);
    }
    free(graph);

    return 0;
}


