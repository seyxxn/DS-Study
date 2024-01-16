#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} node;

void insert_node(node *head, const int index, const int data);
void delete_node(node *head, int index);
int search(node *head, int val);
int get_data(node *head, int index);
int size(node *head);
void print_ll(node *head);

int main()
{
    node *head = (node *)malloc(sizeof(node));
    head->data = 0;
    head->next = NULL;

    insert_node(head, 0, 3);
    print_ll(head);
    printf("현재 연결리스트의 크기 : %d\n", size(head));

    insert_node(head, 1, 5);
    print_ll(head);
    printf("현재 연결리스트의 크기 : %d\n", size(head));

    insert_node(head, 2, 7);
    print_ll(head);
    printf("현재 연결리스트의 크기 : %d\n", size(head));

    insert_node(head, 10, 2); // index 범위를 초과해서 삽입 안됨
    print_ll(head);
    printf("현재 연결리스트의 크기 : %d\n", size(head));

    insert_node(head, 1, 15);
    print_ll(head);
    printf("현재 연결리스트의 크기 : %d\n", size(head));

    delete_node(head, 2);
    print_ll(head);
    printf("현재 연결리스트의 크기 : %d\n", size(head));

    printf("원소 검색 : %d는 %d번째 인덱스에 존재합니다.\n", 15, search(head, 15));
    printf("원소 검색 : %d는 %d번째 인덱스에 존재합니다.\n", 7, search(head, 7));

    printf("값 추출 : %d번째 인덱스의 값은 %d입니다.\n", 1, get_data(head, 1));
    printf("값 추출 : %d번째 인덱스의 값은 %d입니다.\n", 2, get_data(head, 2));

}

void insert_node(node *head, int index, int data)
{
    int k = index;
    node *pre_node = head;
    node *insert = (node *)malloc(sizeof(node));
    insert->data = data;

    while (k-- && pre_node != NULL)
    {
        pre_node = pre_node->next;
    }

    if (pre_node == NULL)
    {
        free(insert);
        return;
    }

    insert->next = pre_node->next;
    pre_node->next = insert;
}

void delete_node(node *head, int index)
{
    int k = index;
    node *pre_node = head;
    node *garbage = NULL;

    while (k-- && pre_node != NULL)
    {
        pre_node = pre_node->next;
    }

    if (pre_node == NULL || pre_node->next == NULL)
        return;

    garbage = pre_node->next;
    pre_node->next = garbage->next;
    free(garbage);
}

int search(node *head, int val)
{
    if (head->next == NULL)
    {
        return -1;
    }

    int index = 0;
    node *temp = head->next;

    while (temp->data != val)
    {
        ++index;
        temp = temp->next;

        if (temp == NULL)
            return -1;
    }
    return index;
}

int get_data(node *head, int index)
{
    if (head->next == NULL)
    {
        return -1;
    }

    int k = index;
    node *temp = head->next;

    while (k--)
    {
        temp = temp->next;
    }

    return temp->data;
}

int size(node *head)
{
    if (head->next == NULL)
    {
        return 0;
    }

    node *temp = head->next;
    int len = 0;
    while (temp != NULL)
    {
        ++len;
        temp = temp->next;
    }
    return len;
}

void print_ll(node *head)
{
    if (head->next == NULL)
        return;

    node *temp = head->next;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}