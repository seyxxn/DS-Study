// 이중 연결리스트를 활용한 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} Node;

Node *createNode(int data);
void insert(int pos, int data, Node **start);
void deleteByPosition(int pos, Node **start);
void deleteByValue(int value, Node **start);
void traverse(Node *x);
void traverseInReverse(Node *x);
int menu(void);

int main(int argc, char *argv[])
{
    Node *start = NULL;
    char input[10];
    int pos;

    while (1)
    {
        switch (menu())
        {
        case 1:
            puts("Enter numbers, blank line to stop");
            while (gets(input) && input[0] != 0) // 사용자 입력이 존재하고, 공백이 아니면 계속 값을 받는다
                insert(INT_MAX, atoi(input), &start);
            break;
        case 2:
            fprintf(stdout, "Enter number : ");
            insert(1, atoi(gets(input)), &start);
            break;
        case 3:
            fprintf(stdout, "Enter position : ");
            pos = atoi(gets(input));
            fprintf(stdout, "Enter number : ");
            insert(pos, atoi(gets(input)), &start);
            break;
        case 4:
            fprintf(stdout, "Enter position : ");
            deleteByPosition(atoi(gets(input)), &start);
            break;
        case 5:
            fprintf(stdout, "Enter value : ");
            deleteByValue(atoi(gets(input)), &start);
            break;
        case 6:
            traverse(start);
            break;
        case 7:
            traverseInReverse(start);
            break;
        case 8:
            exit(0);
        }
    }
    return 0;
}

// 노드 생성 함수
Node *createNode(int data)
{
    Node *p = malloc(sizeof(Node));
    p->data = data;
    return p;
}

// 삽입 함수
void insert(int pos, int data, Node **start)
{
    // 오류 처리 (잘못된 수를 받았을 때)
    if (pos < 1)
    {
        puts("Invalid position");
        return;
    }

    // 가장 맨 처음에 값을 삽입할 때 (비어있을 때)
    if (*start == NULL)
    {
        *start = createNode(data);
        (*start)->prev = NULL;
        (*start)->next = NULL;
    }
    else
    {
        Node *curr = *start; // 가리키는 포인터 선, 우선 가장 처음을 가리킴

        // 반복문으로 pos에 해당하는 노드를 curr이 가리키게 되었음
        for (; curr->next && pos > 1; pos--)
        {
            curr = curr->next;
        }
        // curr->next이 존재할 때까지 pos-- 를 해주는데
        // pos > 1이라는 것은 맨뒤에 넣겠다는 것 (위에서 맨 뒤에 넣을 때 pos에 int형의 최대값을 인자로 넘김)

        if (pos > 1) // 끝에 삽입하는 경우
        {
            Node *newNode = createNode(data);
            newNode->prev = curr;
            newNode->next = curr->next;
            curr->next = newNode;
        }
        else if (curr == *start) // 맨앞에 삽입하는 경우
        {
            Node *newNode = createNode(data);
            newNode->prev = curr->prev;
            newNode->next = curr;
            curr->prev = newNode;
            *start = newNode;
        }
        else
        {
            Node *newNode = createNode(data);
            newNode->prev = curr->prev;
            newNode->next = curr;
            curr->prev->next = newNode;
            curr->prev = newNode;
        }
    }
}

// 위치를 입력받아 삭제시키는 함수
void deleteByPosition(int pos, Node **start)
{
    if (pos < 1 || *start == NULL) // 이상한 값을 입력 받았거나, 비어있거나
    {
        puts("Invalid position");
    }
    else if (pos == 1) // 첫번째 노드를 삭제하는 경우
    {
        Node *temp = *start;
        *start = (*start)->next; // 시작 노드를 그 다음 노드로 변경
        free(temp);
    }
    else // 위치를 찾음
    {
        Node *temp = *start;
        for (; temp && pos > 1; pos--)
            temp = temp->next;
        if (temp == NULL)
            puts("Invalid position");
        else
        {
            temp->prev->next = temp->next;
            if (temp->next)
                temp->next->prev = temp->prev;
            free(temp);
        }
    }
}

// 값을 입력받아 해당하는 값의 노드를 삭제시키는 함수
void deleteByValue(int value, Node **start)
{
    if ((*start)->data == value) // 삭제하려는 값이 첫번째 값인 경우
    {
        Node *temp = *start;
        *start = (*start)->next;
        free(temp);
    }
    else // 첫번째가 아니면, 해당하는 노드를 찾으러 감
    {
        Node *temp = *start;
        for (; temp && temp->data != value; temp = temp->next)
            ;
        if (temp == NULL) // 해당하는 값이 없음
            puts("Element not found");
        else
        {
            temp->prev->next = temp->next;
            if (temp->next)
            {
                temp->next->prev = temp->prev;
            }
            free(temp);
        }
    }
}

void traverse(Node *x)
{
    int cnt = 1;
    while (x)
    {
        fprintf(stdout, "%d: %d\t", cnt++, x->data);
        x = x->next;
    }
    fprintf(stdout, "\n");
}

void traverseInReverse(Node *x)
{
    int cnt = 1;
    if (x)
    {
        while (x->next)
        { // 끝으로 감
            x = x->next;
            cnt++;
        }
        while (x)
        {
            fprintf(stdout, "%d: %d\t", cnt--, x->data);
            x = x->prev;
        }
    }
    fprintf(stdout, "\n");
}

int menu(void)
{
    int choice;
    puts("1-insert data at end");
    puts("2-insert at beginning");
    puts("3-insert at position");
    puts("4-delete by position");
    puts("5-delete be element");
    puts("6-Display");
    puts("7-Display in reverse");
    puts("8-Exit");
    fprintf(stdout, "Enter choice : ");
    scanf("%d", &choice);
    getchar();

    return choice;
}