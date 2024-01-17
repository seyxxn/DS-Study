// 이중 원형 연결리스트

#include <stdio.h>
#include <stdlib.h>

// 이중 연결 리스트 노드 구조체
typedef struct Dnode
{
    struct Dnode *llink; // 이전노드
    int data;
    struct Dnode *rlink; // 다음노드
} node;

typedef node *nodePtr;
// Dnode * 타입을 DnodePtr로 정의함 -> Dnode 포인터를 나타내는 타입 별칭

void dinsert(nodePtr phead, int data);
void print_dll(nodePtr phead);
void init(nodePtr phead);

// 이중 원형 연결리스트에 노드를 삽입하는 프로그램 : 삽입할 노드의 바로 앞 노드만 알면 된다.
void dinsert(nodePtr phead, int data) // 인수로 받은 node는 바로 앞 노드
{
    nodePtr newNode = (nodePtr)malloc(sizeof(node));
    newNode->data = data;

    // node의 오른쪽에 newNode를 삽입
    newNode->llink = phead;        // 1. 새로운 노드의 llink를 이전 노드로
    newNode->rlink = phead->rlink; // 2. 새로운 노드의 rlink를 이전노드의 rlink로
    phead->rlink->llink = newNode; // 3. 이전노드의 다음노드의 llink를 새로운 노드로
    phead->rlink = newNode;        // 4. 이전노드의 rlink를 새로운 노드로
}

/* void insertNode(nodePtr* head, nodePtr prevNode, int data){
    // 1. 새로운 노드 생성
    nodePtr newNode = (nodePtr)malloc(sizeof(node));
    newNode->data = data;

    // 2. 새로운 노드의 연결 설정
    newNode->llink = prevNode;
    newNode->rlink = prevNode->rlink;

    // 3. 이전 노드와 다음 노드의 연결 설정
    prevNode->rlink = newNode;
    if(newNode->rlink != NULL){ // 새로운 노드의 다음 노드가 null이 아니라면
        newNode->rlink->llink = newNode;
    }

    // 4. 만약 새로운 노드가 리스트의 첫번째 노드라면 헤더 업데이트
    if(*head == NULL || prevNode == *head){
        *head = newNode;
    }
firstNode->data = 1;
    firstNode->llink = NULL;
    firstNode->rlink = NULL;

    head = firstNode; */

// 노드를 삭제하는 함수
void ddelete(nodePtr phead, nodePtr removed)
{
    if (removed == phead)
        return;
    // 헤드의 노드를 삭제하려는 경우, 이중 원형 연결 리스트의 특성상 리스트가 원형으로 연결되어있어 리스트의 무결성이 깨질 수 있어,
    // 헤드 노드를 삭제하는 것은 보통 예외처리 함
    else
    {
        removed->llink->rlink = removed->rlink;
        removed->rlink->llink = removed->llink;
        free(removed);
    }
}

// 이중연결리스트 초기화
void init(nodePtr phead)
{
    phead->llink = phead;
    phead->rlink = phead;
}

// 이중연결리스트 상태 출력
void print_dll(nodePtr phead)
{
    nodePtr current;
    for (current = phead->rlink; current != phead; current = current->rlink)
    {
        printf("%d ", current->data);
    }
    printf("\n");
}

int main()
{
    nodePtr phead = (node *)malloc(sizeof(node));
    init(phead);

    // 추가
    /*  dinsert(phead, 10);
        print_dll(phead);

        dinsert(phead->rlink, 23);
        print_dll(phead);

        dinsert(phead->rlink->rlink, 34);
        print_dll(phead);

        이렇게 넣으면 10 , 10 23, 10 23 34
        출력됨
        즉, 첫번째 인수의 오른쪽에  값이 들어감
    */
    dinsert(phead, 10);
    print_dll(phead);

    dinsert(phead, 23);
    print_dll(phead);

    dinsert(phead, 34);
    print_dll(phead);

    // 이렇게 넣으면 값이 계속해서 head의 오른쪽 (즉, 첫번째 위치)으로 들어가기 때문에
    // 10
    // 23 10
    // 34 23 10 이렇게 값이 출력됨

    // 삭제

    ddelete(phead, phead->rlink);
    print_dll(phead);

    ddelete(phead, phead->rlink);
    print_dll(phead);

    return 0;
}
