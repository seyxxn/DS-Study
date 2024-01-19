// 다항식 곱셈의 구현
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode
{
    int coef;
    int expon;
    struct listNode *link;
} listNode;

typedef struct listHeader
{
    int length;
    listNode *head;
    listNode *tail;
} listHeader;

void init(listHeader *plist);
void insertNodeLast(listHeader *plist, int coef, int expon);
void polyMul(listHeader *plist1, listHeader *plist2, listHeader *plist3);
void polyPrint(listHeader *plist);
void polyDelete(listHeader *plist);

int main(int argc, char *argv[])
{
    listHeader list1, list2, list3;

    init(&list1);
    init(&list2);
    init(&list3);

    insertNodeLast(&list1, 3, 3);
    insertNodeLast(&list1, 2, 2);
    insertNodeLast(&list1, 2, 1);

    insertNodeLast(&list2, 8, 3);
    insertNodeLast(&list2, 3, 2);
    insertNodeLast(&list2, 10, 0);

    polyMul(&list1, &list2, &list3);

    fprintf(stdout, "A의 다항식 : ");
    polyPrint(&list1);

    fprintf(stdout, "B의 다항식 : ");
    polyPrint(&list2);

    fprintf(stdout, "------------------------------------\n");

    fprintf(stdout, "다항식 곱셈 : ");
    polyPrint(&list3);

    polyDelete(&list1);
    polyDelete(&list2);
    polyDelete(&list3);

    return 0;
}

void init(listHeader *plist)
{
    plist->length = 0;
    plist->head = plist->tail = NULL;
}

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

    if (plist->head == NULL)
        plist->head = plist->tail = temp;
    else
    {
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->length++;
}

void polyMul(listHeader *plist1, listHeader *plist2, listHeader *plist3)
{
    listNode *a = plist1->head;
    listNode *b = plist2->head;
    int *multiply, i, highest;

    highest = a->expon + b->expon;

    multiply = calloc(highest + 1, sizeof(int));

    while (a != NULL)
    {
        if (b != NULL)
        {
            if (multiply[(a->expon + b->expon)] == 0)
                multiply[(a->expon + b->expon)] = a->coef * b->coef;
            else
                multiply[(a->expon + b->expon)] += a->coef * b->coef;
            b = b->link;
        }
        else
        {
            a = a->link;
            b = plist2->head;
        }
    }

    for (i = highest; i >= 0; i--)
    {
        if (multiply[i] != 0)
        {
            insertNodeLast(plist3, multiply[i], i);
        }
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

void polyDelete(listHeader *plist)
{
    listNode *temp = plist->head;
    listNode *del;
    while (temp->link != NULL)
    {
        del = temp;         // 처음에는 같은 곳을 가리키게하고
        temp = del->link;   // temp를 다음으로 옮김
        plist->head = temp; // temp를 head로 지정 (가장 처음을 temp로 옮김)
        free(del);          // del을 메모리 해제
    }
    free(temp);
}