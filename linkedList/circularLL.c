// 환형 연결 리스트

/* 마지막 노드가 항상 첫 번째 노드를 가리키는 연결리스트
장점 ) 어떤 노드든 다른 노드에서 출발하여 순회할 수 있음, 리스트의 끝을 나타내는 NULL 포인터가 필요하지 않으므로 모든 포인터가 유효한 주소를 가짐

기억하기 )
헤드 포인터 head는 항상 마지막 노드를 가리킨다.
head == 마지막 노드 주소
(*head)->next == 첫번째 노드 주소

 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 새로운 노드를 생성하고 값을 초기화 하는 함수
// insertNode함수를 통해 createNode 함수가 실행됨
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("메모리 할당 오류\n");
        exit(1);
    }
    newNode->data = data; // 값 넣고
    newNode->next = NULL; // 일단 null로 초기화
    return newNode;
}

// 환형 연결 리스트에 노드를 추가하는 함수(원형 리스트의 끝에 삽입하는 함수)
void insertNode(Node **head, int data)
{
    Node *newNode = createNode(data);

    if (*head == NULL) // 노드를 처음 추가하는 상황
    {
        // 빈 리스트인 경우
        *head = newNode;         // head가 새로 생성한 노드를 가리키게 함
        newNode->next = newNode; // 새로 삽입된 첫번째 노드의 next는 자기자신을 가리키게 함
    }
    else
    {
        // 빈 리스트가 아닌 경우
        newNode->next = (*head)->next;
        (*head)->next = newNode;
        *head = newNode; // 새로운 노드가 마지막 노드가 된다.
    }
}

// 환형 연결리스트를 출력하는 함수
void printCircularList(Node *head)
{
    //  빈 리스트일 때
    if (head == NULL)
    {
        printf("리스트가 비어 있다.\n");
        return;
    } 

    Node *current = head->next; // 첫번째 노드는 head->next에 존재. 가리키면서 순회할 포인터를 생성

    do
    {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != head->next);

    printf("...\n");
}

int main()
{
    Node *head = NULL; // 빈 환형 연결리스트 생성

    // 노드 추가
    insertNode(&head, 1);
    printCircularList(head);

    insertNode(&head, 2);
    printCircularList(head);

    insertNode(&head, 3);
    printCircularList(head);

    return 0;
}
