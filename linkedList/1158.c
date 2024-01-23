#include <stdio.h>
#include <stdlib.h>
int n, k;
//  원형 이중 연결리스트 구현

typedef struct listNode
{
    int data;
    struct listNode *prev;
    struct listNode *next;
} listNode;

typedef struct listNode *listPointer;

listPointer createNode(int data)
{
    listPointer newNode = (listPointer)malloc(sizeof(listNode));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertNode(listPointer *head, int data)
{
    listPointer newNode = createNode(data);

    if (*head == NULL)
    {
        *head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    else
    {
        newNode->next = (*head)->next;
        newNode->prev = (*head);
        (*head)->next = newNode;
        newNode->next->prev = newNode;
        *head = newNode;
    }
}

void deleteNode(listPointer *head, int k)
{
    if (*head == NULL)
        return;

    listPointer del = *head;
    for (int i = k; i > 0; i--)
    {
        del = del->next;
    }

    if (del->next == del)
    {
        // 마지막 남은 것을 삭제하는 경우
        printf("%d", del->data);
        free(del);
        *head = NULL;
    }
    else
    {
        printf("%d, ", del->data);
        del->prev->next = del->next;
        del->next->prev = del->prev;

        *head = del->prev;
        free(del);
    }
}

void printCircularList(listPointer head)
{
    if (head == NULL)
    {
        printf("empty\n");
        return;
    }

    listPointer cur = head;

    do
    {
        printf("%d -> ", cur->data);
        cur = cur->prev;
    } while (cur != head);

    printf("\n");
}

int main()
{
    listPointer head = NULL;

    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++)
    {
        insertNode(&head, i);
    }

    // printCircularList(head);

    printf("<");
    while (head != NULL)
    {
        deleteNode(&head, k);
        // printCircularList(head);
    }
    printf(">\n");
    return 0;
}