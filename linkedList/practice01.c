/*
1. ���� ���� ����Ʈ�� �־����� ��, ��ũ�� ����Ʈ�� �߰� ������ ã�� ���α׷��� �ۼ��Ͻÿ�.
���� ���, �־��� ���� ����Ʈ�� 1->2->3->4->5 �� ���, ����� 3�̾�� �Ѵ�.
��� ���� ¦���̸� �� ���� �߰� ��尡 ���� ���̹Ƿ� �ι�° �߰� ��Ҹ� ����ؾ��Ѵ�.
���� ���, �־��� ���� ����Ʈ�� 1->2->3->4->5->6 �̸� ����� 4�� �ȴ�.
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

     // ù��° ����� ���
    if(*head == NULL){
        *head = newNode;
    }
    else
    {   
        listPointer cur = *head;
        while(cur->next != NULL){
            cur = cur->next;  // cur�� ���� ���� ����Ű�� ��
        }
        cur->next = newNode;
    }
}

void printMid(listPointer head){
    if (head == NULL){
            printf("���� ����Ʈ�� ����ֽ��ϴ�.\n");
        return ;
    }

    int len = 0;
    listPointer cur = head;

    while(cur != NULL){
        len++;
        cur = cur->next;
    }

    // len�� ���Ḯ��Ʈ ����� ������ ����.
    listPointer printPointer = head;
    for(int i = 0; i < len/2; i++){
        printPointer = printPointer->next;
    }
    
    printf("���� ����Ʈ�� �߰� ���� : %d\n", printPointer->data);

}

int main(){
    listPointer head = NULL;

       printf("���� ����Ʈ�� ���� ���ҵ��� ������ �Է����ּ���.\n");
        int n;
    scanf("%d", &n);
    
    int enter;
      printf("���� ����Ʈ�� ���� ���ҵ��� ������� �Է����ּ���.\n");
    while(n--){
        scanf("%d", &enter);
        createNode(enter, &head);
    }

    printMid(head);
    

    return 0;
}