// 다항식 덧셈의 구현
#include <stdio.h>
#include <stdlib.h>

// 연결리스트 노드의 구조
typedef struct listNode
{
    int coef;
    int expon;
    struct listNode *link;
} listNode;

// 연결리스트의 헤더
typedef struct listHeader
{
    int length;
    listNode *head; // 가장 처음을 가리킴
    listNode *tail; // 가장 끝을 가리킴
} listHeader;

void init(listHeader *plist);
void insertNodeLast(listHeader *plist, int coef, int expon);
void polyAdd(listHeader *plist1, listHeader *plist2, listHeader *plist3);
void polyPrint(listHeader *plist);
void polyDelete(listHeader *plist);

int main(int argc, char *argv[])
{
    listHeader list1, list2, list3; // 리스트 변수 선언

    // 연결리스트 초기화
    init(&list1);
    init(&list2);
    init(&list3);

    // 다항식 1을 생성
    insertNodeLast(&list1, 3, 5);
    insertNodeLast(&list1, 2, 3);
    insertNodeLast(&list1, 2, 2);

    // 다항식 2를 생성
    insertNodeLast(&list2, 8, 6);
    insertNodeLast(&list2, 3, 4);
    insertNodeLast(&list2, 10, 2);

    // 다항식 3 = 다항식 1 + 다항식 2
    polyAdd(&list1, &list2, &list3);

    fprintf(stdout, "A의 다항식 : ");
    polyPrint(&list1);

    fprintf(stdout, "B의 다항식 : ");
    polyPrint(&list2);

    fprintf(stdout, "------------------------------------\n");

    fprintf(stdout, "결과 다항식 : ");
    polyPrint(&list3);

    polyDelete(&list1);
    polyDelete(&list2);
    polyDelete(&list3);

    return 0;
}

// 초기화 함수
void init(listHeader *plist)
{
    plist->length = 0;
    plist->head = plist->tail = NULL;
}

// 리스트의 끝에 노드를 삽입하는 함수
// plist는 연결 리스트의 헤더를 가르키는 포인터
void insertNodeLast(listHeader *plist, int coef, int expon)
{
    listNode *temp = (listNode *)malloc(sizeof(listNode));

    if (temp == NULL)
    {
        fprintf(stdout, "메모리 할당 에러");
    }

    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;

    if (plist->tail == NULL)
    { // 빈 리스트 였다면 (첫번째 노드로 삽입하는 경우)
        plist->head = plist->tail = temp;
    }
    else // 첫번째노드가 아니라면
    {
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->length++;
}

// 다항식 덧셈 함수
void polyAdd(listHeader *plist1, listHeader *plist2, listHeader *plist3)
{
    listNode *a = plist1->head;
    listNode *b = plist2->head;

    int sum;
    while (a && b)
    {
        if (a->expon == b->expon)
        {
            sum = a->coef + b->coef;
            if (sum != 0)
                insertNodeLast(plist3, sum, a->expon);
            a = a->link;
            b = b->link;
        }
        else if (a->expon > b->expon)
        {
            insertNodeLast(plist3, a->coef, a->expon);
            a = a->link;
        }
        else
        {
            insertNodeLast(plist3, b->coef, b->expon);
            b = b->link;
        }
    }

    // a와 b식중 하나가 먼저 끝나게 되면 남아있는 항들을 모두 결과식으로 넣는다.
    for (; a; a = a->link)
    {
        insertNodeLast(plist3, a->coef, a->expon);
    }
    for (; b; b = b->link)
    {
        insertNodeLast(plist3, b->coef, b->expon);
    }
}

void polyPrint(listHeader *plist)
{
    listNode *p = plist->head;

    for (; p; p = p->link)
    {
        fprintf(stdout, "%dX^%d", p->coef, p->expon);
        if (p->link != NULL)
            fprintf(stdout, " + ");
    }
    fprintf(stdout, "\n");
}

// 연결리스트의 모든 노드를 순회하면서 메모리를 해제하는 함수
// 앞에서부터 순차적으로 삭제함
void polyDelete(listHeader *plist)
{
    listNode *temp = plist->head;
    listNode *del;
    while (temp->link != NULL) // temp 포인터로 head(처음)부터 끝까지 돈다
    {
        del = temp;         // 삭제할 노드를 del 포인터로 가리킴
        temp = del->link;   // temp 노드를 다음 노드로 이동시킴
        plist->head = temp; // head가 그 다음노드인 temp를 가리키게 함
        free(del);
    }
    free(temp);
}