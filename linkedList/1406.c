#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char enter[100000];
int M;
// 연결리스트 문제
// 이중 연결리스트 ?
typedef struct Node
{
    char ch;
    struct Node *llink;
    struct Node *rlink;
} Node;

void createNode(Node **head, Node **tail, char data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->ch = data;
    newNode->llink = NULL;
    newNode->rlink = NULL;

    if (*head == NULL) // 비어있는 경우, 즉 처음 넣는 경우
    {
        *head = newNode;
        *tail = newNode;
        return;
    }

    // 가장 끝에 삽입해야함
    Node *p = *tail;
    while (p->rlink != NULL)
        p = p->rlink;

    newNode->rlink = p->rlink;
    newNode->llink = p;
    p->rlink = newNode;
    tail = &newNode;
}

void printNode(Node *head)
{
    Node *current = head;

    while (current != NULL)
    {
        printf("%c", current->ch);
        current = current->rlink;
    }
    printf("\n");
}

// 커서 왼쪽에 있는 문자를 삭제함 (tail이 가리키고 있는 것을 삭제해야함)
void deleteNode(Node **tail)
{
    Node *temp = *tail;
    if (temp-> llink == NULL)
        return;

    temp->llink->rlink = temp->rlink;
    temp->rlink->llink = temp->llink;
    *tail = temp->llink;

    free(temp);
}

int main()
{
    scanf("%s", enter);
    scanf("%d", &M);

    int stringLen = strlen(enter);
    Node *word = (Node *)malloc(sizeof(Node));
    Node *head = NULL;
    Node *tail = NULL;

    head = word;
    tail = word;

    for (int i = 0; i < stringLen; i++)
    {
        createNode(&head, &tail, enter[i]);
    }

    printNode(word);

    while (M--)
    {
        char menu[10];
        scanf("%s", menu);
        if (strcmp(menu, "L") == 0)
        {
            if (tail->llink != NULL)
            {
                tail = tail->llink;
            }
        }
        else if (strcmp(menu, "D") == 0)
        {
            if (tail->rlink != NULL)
            {
                tail = tail->rlink;
            }
        }
        else if (strcmp(menu, "B") == 0)
        {
            deleteNode(&tail);
        }
        printNode(word);
    }
}