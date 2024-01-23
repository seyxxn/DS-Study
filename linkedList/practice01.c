/*
1. 단일 연결 리스트가 주어졌을 때, 링크드 리스트의 중간 지점을 찾는 프로그램을 작성하시오.
예를 들어, 주어진 연결 리스트가 1->2->3->4->5 인 경우, 출력은 3이어야 한다.
노드 수가 짝수이면 두 개의 중간 노드가 있을 것이므로 두번째 중간 요소를 출력해야한다.
예를 들어, 주어진 연결 리스트가 1->2->3->4->5->6 이면 출력은 4가 된다.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode{
    int data;
    struct listNode *next;
} listNode;

typedef struct listNode *listPointer;

void createNode(int data, listPointer *head){
    listPointer newNode = (listPointer)malloc(sizeof(listNode));
    newNode->data = data;
    newNode->next = NULL;

     // 첫번째 노드인 경우
    if(*head == NULL){
        *head = newNode;
    }
    else
    {   
        listPointer cur = *head;
        while(cur->next != NULL){
            cur = cur->next;  // cur이 가장 끝을 가리키게 함
        }
        cur->next = newNode;
    }
}

void printMid(listPointer head){
    if (head == NULL){
            printf("연결 리스트가 비어있습니다.\n");
        return ;
    }

    int len = 0;
    listPointer cur = head;

    while(cur != NULL){
        len++;
        cur = cur->next;
    }

    // len에 연결리스트 노드의 갯수가 담긴다.
    listPointer printPointer = head;
    for(int i = 0; i < len/2; i++){
        printPointer = printPointer->next;
    }
    
    printf("연결 리스트의 중간 지점 : %d\n", printPointer->data);

}

int main(){
    listPointer head = NULL;

       printf("연결 리스트에 넣을 원소들의 갯수를 입력해주세요.\n");
        int n;
    scanf("%d", &n);
    
    int enter;
      printf("연결 리스트에 넣을 원소들을 순서대로 입력해주세요.\n");
    while(n--){
        scanf("%d", &enter);
        createNode(enter, &head);
    }

    printMid(head);
    

    return 0;
}