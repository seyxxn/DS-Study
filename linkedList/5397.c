#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode{
    char data;
    struct listNode *prev;
    struct listNode *next;
} listNode;

typedef struct listNode * listPointer;

void left(listPointer *head, listPointer *cursor){
    if((*cursor)->prev){
        *cursor = (*cursor)->prev;
    }
}

void right(listPointer *head, listPointer *cursor){
    if ((*cursor)->next){
        *cursor = (*cursor)->next;
    }
}

void insertNode(char ch, listPointer *head, listPointer *cursor){
    listPointer newNode = (listPointer)malloc(sizeof(listNode));
    newNode->data = ch;
    newNode->prev = NULL; 
    newNode->next = NULL;

    // 노드를 가장 앞에 삽입할 때
    if(*head == *cursor){
        newNode->prev = *head;
        if ((*head)->next){
            newNode->next = (*head)->next;
            (*head)->next->prev = newNode;
        }
        (*head)->next = newNode;
        *cursor = newNode;
    }
    else{
        newNode->prev = *cursor;
        newNode->next = (*cursor)->next;
        if ((*cursor)->next){
            (*cursor)->next->prev = newNode;
        }
        (*cursor)->next = newNode;
        *cursor = newNode;
    }
}

void deleteNode(listPointer *head, listPointer *cursor){
    
    if (*head == *cursor){
        return ;
    }

    listPointer del = *cursor; 

    // 가장 앞에것을 삭제하는 경우
    if (del->prev == *head){
       (*head)->next = del->next;
       if (del->next){
        del->next->prev = *head;
       }
       *cursor = *head;
       free(del); 
    }
    else{
        del->prev->next = del->next;
        if(del->next){
            del->next->prev = del->prev;
        }

        *cursor = (*cursor)->prev;
        free(del);
    }
}

void printNode(listPointer head){
    listPointer temp = head->next;
    while(temp){
        printf("%c", temp->data);
        temp = temp->next;
    }printf("\n");
}

void solve(char ch, listPointer *head, listPointer *cursor){
    switch (ch)
    {
    case '<':
        left(head, cursor);
        break;
    case '>':
        right(head, cursor);
        break;
    case '-':
        deleteNode(head, cursor);
        break;
    default :
        insertNode(ch, head, cursor);
        break;
    }
}


int main(){
    int n;
    scanf("%d", &n);
    char enter[1000001]; // 사용자 입력 문자열

    // 헤드 더미노드 생성
    listPointer head = (listPointer)malloc(sizeof(listNode));
    head->data = '\0';
    head->next = NULL;
    head->prev = NULL;

    listPointer cursor = head;

    for(int i = 0; i < n; i++){
        scanf("%s", enter);
        int enterLen = strlen(enter);

        for(int j = 0; j < enterLen; j++){
            solve(enter[j], &head, &cursor);
            // printNode(head);
        }

        printNode(head);

        // 노드해제
        listPointer current = head->next;
        while(current){
            free(current);
            current = current->next;
        }
        
        head->next = NULL;
        cursor = head;
    }

    free(head);
    
    return 0;
}