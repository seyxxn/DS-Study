#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode
{
    char ch;
    struct listNode *llink;
    struct listNode *rlink;
} listNode;

typedef struct listNode * listPointer; 

void left(listPointer *first, listPointer *cursor){
    if(*first == NULL) return; // 빈 리스트일 때
    if((*cursor)->llink)
        *cursor = (*cursor)->llink;
}

void right(listPointer *first, listPointer *cursor){
    if(*first==NULL) return; // 빈 리스트일 때
    if((*cursor)->rlink)
        *cursor = (*cursor)->rlink;
}

// cursor 변수가 가리키는 곳 뒤에 삽입해야함
void createNode(listPointer *head, listPointer *first, listPointer *cursor, int data)
{
    listPointer newNode = (listPointer)malloc(sizeof(listNode));
    newNode->ch = data;
    newNode->llink = NULL;
    newNode->rlink = NULL;

    if (*first == NULL) // 비어있는 경우, 즉 처음 넣는 경우
    {
        *first = newNode;
        *cursor = newNode;
        return;
    }

    newNode->llink = *cursor;
    newNode->rlink = (*cursor)->rlink;
    if((*cursor)->rlink) 
        (*cursor)->rlink->llink = newNode;
    (*cursor)->rlink = newNode;
    *cursor = newNode;
}

void printNode(listPointer first)
{
    listPointer p = first;

    while (p != NULL)
    {
        printf("%c", p->ch);
        p = p->rlink;
    }
    printf("\n");
}

// 커서 왼쪽에 있는 문자를 삭제함 (cursor변수가 가리키고 있는 것을 삭제해야함)
void deleteNode(listPointer *head, listPointer *first, listPointer *cursor)
{
    listPointer temp = *cursor;
    if (temp == *head) // 커서가 문장의 맨 앞이면 무시됨
        return;

    temp->llink->rlink = temp->rlink;
    if (temp->rlink)
        temp->rlink->llink = temp->llink;
    *cursor = temp->llink;

    free(temp);
}

int main()
{
    char enter[100000];
    int M;

    // fgets로 한 줄 전체를 입력받음
    fgets(enter, sizeof(enter), stdin);
    // 개행 문자 제거
    enter[strcspn(enter, "\n")] = '\0';
    scanf("%d", &M);
    getchar();

    int stringLen = strlen(enter);

    listPointer first = NULL; 
    listPointer cursor = NULL;
    
    listPointer head = (listPointer)malloc(sizeof(listNode));
    head->ch = ' ';
    head->llink = NULL;
    head->rlink = first; // 변하지 않음


    for (int i = 0; i < stringLen; i++)
    {
        createNode(&head, &first, &cursor, enter[i]);
    }


    for(int i = 0; i < M; i++)
    {
        char menu[10];
        fgets(menu, sizeof(menu), stdin);
        // 개행 문자 제거
        menu[strcspn(menu, "\n")] = '\0';

        if (strcmp(menu, "L") == 0)
        {
            left(&first, &cursor);
        }
        else if (strcmp(menu, "D") == 0)
        {
           right(&first, &cursor);
        }
        else if (strcmp(menu, "B") == 0)
        {
            deleteNode(&head, &first, &cursor);
        }else{
            createNode(&head, &first, &cursor, menu[2]);
        }
         printNode(first);
    }

    printNode(first);

   return 0;
}