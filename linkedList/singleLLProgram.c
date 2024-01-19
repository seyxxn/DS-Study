// 간단한 연결리스트 예제 프로그램
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode
{
    int data;
    listPointer link;
} listNode;

listPointer createNode(int data, listPointer link);
void insertHead(listPointer *first, listPointer newNode);
void insert(listPointer *first, listPointer x, listPointer newNode);
void delete(listPointer *first, listPointer trail, listPointer removeNode);
void printList(listPointer first);
listPointer search(listPointer first, int x);

int main(int argc, char *argv[])
{
    listPointer list = NULL;
    listPointer temp = NULL;

    insertHead(&list, createNode(10, NULL));
    printList(list);

    insertHead(&list, createNode(20, NULL));
    printList(list);

    insertHead(&list, createNode(30, NULL));
    printList(list);

    insertHead(&list, createNode(40, NULL));
    printList(list);

    insertHead(&list, createNode(50, NULL));
    printList(list);

    temp = search(list, 30);

    insert(&list, temp, createNode(25, NULL));
    printList(list);

    delete (&list, temp, temp->link);
    printList(list);

    delete (&list, NULL, list);
    printList(list);

    return 0;
}

// 새로운 노드를 생성하는 함수
listPointer createNode(int data, listPointer link)
{
    listPointer newNode;

    newNode = (listPointer)malloc(sizeof(listNode));

    if (newNode == NULL)
    {
        fprintf(stderr, "메모리 할당 에러");
        exit(1);
    }

    newNode->data = data;
    newNode->link = link;

    return newNode;
}

// 새로운 노드를 헤더(맨 앞)에 삽입하는 함수
void insertHead(listPointer *first, listPointer newNode)
{
    newNode->link = *first;
    *first = newNode;
}

// 새로운 노드를 x의 뒤에 삽입하는 함수
void insert(listPointer *first, listPointer x, listPointer newNode)
{
    if (*first)
    {
        newNode->link = x->link;
        x->link = newNode;
    }
    else // 리스트가 비어있는 상태(노드가 없는 상태)
    {
        newNode->link = NULL;
        *first = newNode;
    }
}

// 노드를 삭제하는 함수
// tail은 삭제될 removeNode의 선행 노드
void delete(listPointer *first, listPointer trail, listPointer removeNode)
{
    if (trail)
        trail->link = removeNode->link;
    else // trail이 NULL이면 가장 앞 노드 삭제
        *first = (*first)->link;
    free(removeNode);
}

// 리스트를 출력하는 함수
void printList(listPointer first)
{
    fprintf(stdout, "The list contains : ");
    for (; first; first = first->link)
        fprintf(stdout, "%4d ", first->data);
    fprintf(stdout, "\n");
}

// 노드를 탐색하는 함수
listPointer search(listPointer first, int x)
{
    for (; first; first = first->link)
    {
        if (first->data == x)
        {
            return first;
        }
    }

    return NULL;
}
