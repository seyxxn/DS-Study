// 18258번 큐2
// 이중연결리스트로 구현 하는 큐
// 단일연결리스트 -> 시간초과 문제
// 이중연결리스트를 사용하며 순회하는 반복문같은 시간 오래걸리는 것들을 최소화 해야 해결가능함

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode
{
    int data;
    struct listNode *prev;
    struct listNode *next;
} listNode;

typedef struct listNode *listPointer;

listPointer head = NULL;
listPointer tail = NULL;
int cnt = 0;

// 정수 x를 큐에 넣는 연산으로 가장 뒤에 삽입됨
void push(listPointer *tail, int data)
{
    listPointer temp = (listPointer)malloc(sizeof(listNode));
    temp->data = data;
    temp->next = NULL;
    temp->prev = tail;

    (*tail)->next = temp;
    *tail = temp;

    cnt++;
}

// 가장 앞에 있는 정수를 빼고, 그 정수를 출력한다.
// 만약 큐가 비어있다면 -1을 출력한다.
void pop(listPointer *head, listPointer *tail)
{
    listPointer cur = (*head)->next;
    if (cnt == 0)
    {
        printf("-1\n");
        return;
    }

    printf("%d\n", cur->data);

    (*head)->next = cur->next;
    if (cur->next != NULL)
        cur->next->prev = *head;
    else
        *tail = *head;

    cnt--;

    free(cur);
}

void size()
{
    printf("%d\n", cnt);
}

void empty()
{
    if (cnt == 0)
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }
}

void front(listPointer *head)
{
    if (cnt == 0)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n", (*head)->next->data);
    }
}

void back(listPointer *tail)
{
    if (cnt == 0)
    {
        printf("-1\n");
        return;
    }

    printf("%d\n", (*tail)->data);
}

void printNode(listPointer head)
{
    printf("List : ");
    listPointer p = head->next;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    int n;
    scanf("%d", &n);

    listPointer head = (listPointer)malloc(sizeof(listNode));
    head->next = NULL;
    head->prev = NULL;
    tail = head;

    while (n--)
    {
        char enter[10];
        scanf("%s", enter);

        if (strcmp(enter, "push") == 0)
        {
            int num;
            scanf(" %d", &num);
            push(&tail, num);
        }
        else if (strcmp(enter, "pop") == 0)
        {
            pop(&head, &tail);
        }
        else if (strcmp(enter, "size") == 0)
        {
            size();
        }
        else if (strcmp(enter, "empty") == 0)
        {
            empty();
        }
        else if (strcmp(enter, "front") == 0)
        {
            front(&head);
        }
        else if (strcmp(enter, "back") == 0)
        {
            back(&tail);
        }

       // printNode(head);
    }
}