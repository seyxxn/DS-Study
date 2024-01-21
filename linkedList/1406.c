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

void createNode(listPointer *cur, char data)
{
    listPointer newNode = (listPointer)malloc(sizeof(listNode));
    newNode->ch = data;
    newNode->llink = *cur;

    if ((*cur)->rlink)
    {
        newNode->rlink = (*cur)->rlink;
        (*cur)->rlink->llink = newNode;
    }else{
        newNode->rlink = NULL;
    }

    (*cur)->rlink = newNode;
    *cur = (*cur)->rlink;
}

void printNode(listPointer head)
{
    listPointer p = head;
    p = p-> rlink;
    while (p)
    {
        printf("%c", p->ch);
        p = p->rlink;
    }
    printf("\n");
}

// 커서 왼쪽에 있는 문자를 삭제함 (cursor변수가 가리키고 있는 것을 삭제해야함)
void deleteNode(listPointer *cur)
{
    if((*cur)->llink == NULL) return;

    listPointer p = *cur;
    *cur = p->llink;

    if (p->rlink){
        (*cur)->rlink = p->rlink;
        p->rlink->llink = *cur;
        // p->llink = NULL;
    }else{
        (*cur)->rlink = NULL;
    }

    free(p);
}

int main()
{
    listPointer head = (listPointer)malloc(sizeof(listNode));
    head->ch = ' ';
    head->llink = NULL;
    head->rlink = NULL;

    listPointer cur = head;
    char enter;

    while((enter = getchar())!= '\n'){
        listPointer newNode = (listPointer)malloc(sizeof(listNode));
        newNode->ch = enter;
        newNode->llink = cur;
        newNode->rlink = NULL;
        cur->rlink = newNode;
        cur = newNode;
    }

    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; i++)
    {
        char menu;
        scanf(" %c", &menu);

        switch(menu){
            case 'L' :
            {
                if (cur->llink) cur = cur->llink;
                break;
            }
            case 'D' :
            {
                if (cur->rlink) cur = cur->rlink;
                break;
            }
            case 'B':
            {
                deleteNode(&cur);
                break;
            }
            case 'P':
            {
                char ch;
                scanf(" %c", &ch);
                createNode(&cur, ch);
                break;
            }
        }
    }
    printNode(head);
   return 0;
}