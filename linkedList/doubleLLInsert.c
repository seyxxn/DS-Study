// 이중 연결리스트에서의 노드의 삽입
#include <stdio.h>
#include <stdlib.h>

// 이중 연결 리스트 노드 구조체
typedef struct Node
{
    int data;
    struct Node *llink;
    struct Node *rlink;
} Node;

// 이중 연결리스트에 노드를 삽입하는 함수
// prevNode 이후(뒤)에 노드가 삽입된다
void insertNode(Node **head, Node *prevNode, int data)
{
    // 1. 새로운 노드 생성
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;

    // 2. 새로운 노드의 연결 설정
    newNode->llink = prevNode;
    newNode->rlink = prevNode->rlink;

    // 3. 이전노드와 다음노드의 연결 설정
    prevNode->rlink = newNode;
    if (newNode->rlink != NULL)
        prevNode->rlink->llink = newNode;

    // 4. 만약 새로운 노드가 리스트의 첫 번째 노드라면 헤더 업데이트
    if (*head == NULL)
    {
        *head = newNode;
    }
}

// 가장 앞에 추가하는 함수
void insertHead(Node **head, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;

    newNode->rlink = *head;
    newNode->rlink->llink = newNode;
    *head = newNode;
}

void printNode(Node *node)
{
    Node *currentNode = node;
    while (currentNode != NULL)
    {
        printf("%d ", currentNode->data);
        currentNode = currentNode->rlink;
    }
    printf("\n");
}

int main()
{
    Node *head = NULL;

    // 리스트 초기화
    Node *firstNode = (Node *)malloc(sizeof(Node));
    firstNode->data = 1;
    firstNode->llink = NULL;
    firstNode->rlink = NULL;

    head = firstNode;

    insertNode(&head, firstNode, 2);
    printNode(head); // 1 2

    insertNode(&head, firstNode, 3);
    printNode(head); // 1 3 2

    insertNode(&head, firstNode->rlink, 5);
    printNode(head); // 1 3 5 2

    // 맨 처음에 넣어보려 시도 -> segmentfault. 가장 앞 노드로 추가하는 함수를 따로 만들어야함
    // insertNode(&head, firstNode->llink, 9);
    // printNode(head);

    insertHead(&head, 9);
    printNode(head);

    insertHead(&head, 7);
    printNode(head);

    return 0;
}