// 이중 연결 리스트를 활용한 프로그램
// 학생 정보를 저장하고 관리하는 프로그램

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct node
{
    struct node *prev;
    int roll_no;  // 학번
    char name[N]; // 이름
    float marks;  // 성적
    struct node *next;
} node;

void init(node *);          // 초기화 함수
void insertAfter(node *);   // 뒤에 삽입
node *insertBefore(node *); // 앞에 삽입
node *delete(node *);       // 삭제 함수
void search(node *);        // 검색
void display(node *);       // 출력 함수
void rollSrch(node *);      // 학번으로 검색하는 함수
void nameSrch(node *);      // 이름으로 검색하는 함수
void markSrch(node *);      // 성적으로 검색하는 함수

int main(int argc, char *argv[])
{
    node *head;
    char ch;             // 계속해서 명령을 실행할 것인지 입력받는 변수
    int opt;             // 사용자가 선택한 메뉴를 받는 번호
    static int flag = 0; // 노드가 생성이 되었는지 확인하는 변수(초기 0겂)
    system("clear");     // 터미널 화면 지우기
    head = (node *)malloc(sizeof(node));
    head->next = NULL;
    head->prev = NULL;

    // 사용자가 'y'혹은 'Y'를 입력하면 작업을 계속 수행함
    do
    {
    again:
        fprintf(stdout, "\nEnter your option\n");
        fprintf(stdout, "\n1. Initialize the node\n");            // 노드 초기화
        fprintf(stdout, "\n2. Insert before a specified node\n"); // 어떤 노드 앞에 삽입
        fprintf(stdout, "\n3. Insert after a specified node\n");  // 어떤 노드 뒤에 삽입
        fprintf(stdout, "\n4. Delete a particular node\n");       // 어떤 노드를 삭제
        fprintf(stdout, "\n5. Search the nodes\n");               // 노드를 검색
        fprintf(stdout, "\n6. Display all the nodes\n");          // 노드를 출력
        scanf("%d", &opt);
        getchar(); // 버퍼비우기

        // 노드 생성이 안되어있는 상태에서 1번이 아닌 다른 메뉴를 선택한 경우
        if (flag == 0 && opt != 1)
        {
            fprintf(stdout, "\nNo. You must first initialize at least one node\n");
            goto again;
        }

        // 이미 노드생성이 되어있는 상태에서 또 노드를 초기화 하려는 경우
        if (flag == 1 && opt == 1)
        {
            fprintf(stdout, "\nInitialisation can occur only once.\n");
            fprintf(stdout, "\nNow you can insert a node\n");
            goto again;
        }

        // 노드가 하나밖에 없는데 노드를 삭제하려는 경우
        if (opt == 4 && head->next == NULL)
        {
            fprintf(stdout, "\nYou cannot delete the one and only the single node\n");
            goto again;
        }

        if (flag == 0 && opt == 1)
            flag = 1;

        switch (opt)
        {
        case 1: // 노드 초기화
            init(head);
            break;
        case 2: // 어떤 노드 전에 삽입
            head = insertBefore(head);
            break;
        case 3: // 어떤 노드 뒤에 삽입
            insertAfter(head);
            break;
        case 4: // 어떤 노드 삭제
            head = delete (head);
            break;
        case 5: // 노드 검색
            search(head);
            break;
        case 6: // 노드 출력
            display(head);
            break;
        }
        fprintf(stdout, "\nDo you wish to continue[y/n]\n");

        ch = getchar();
        fprintf(stdout, "%c\n", ch);
    } while (ch == 'Y' || ch == 'y');

    fprintf(stdout, "\nDone by \"SHABBIR\"\n");
    fprintf(stdout, "\nPress any key to exit\n");

    return 0;
}

// 초기화 함수
void init(node *current)
{
    current->prev = NULL;
    fprintf(stdout, "\nEnter Roll number\n"); // 학번 입력
    scanf("%d", &current->roll_no);
    getchar();

    fprintf(stdout, "\nEnter the name\n"); // 이름 입력
    gets(current->name);

    fprintf(stdout, "\nEnter the marks\n"); // 성적 입력
    scanf("%f", &current->marks);
    getchar();

    current->next = NULL;
}

// 어떤 노드 그 다음(후)에 삽입하는 함수
void insertAfter(node *current)
{
    int rno;      // 기준이 되는 노드의 학번을 받는 변수
    int flag = 0; // 변경이 되었는지 확인하는 flag 변수
    node *newNode;
    newNode = (node *)malloc(sizeof(node));
    fprintf(stdout, "\nEnter the roll number after which you want to insert a node\n");
    scanf("%d", &rno);
    getchar();

    init(newNode);

    while (current->next != NULL) // 끝이 아니라면 계속 반복문 실행
    {
        if (current->roll_no == rno) // 해당학번 찾을 때 까지
        {
            newNode->next = current->next;
            current->prev->next = newNode;
            current->next = newNode;
            newNode->prev = current;
            flag = 1;
        }
        current = current->next;
    }

    // 가장 뒤에있는 노드의 뒤에 삽입하는 경우 (맨 뒤에 넣게되는 경우)
    if (flag == 0 && current->next == NULL && current->roll_no == rno)
    {
        newNode->next = current->next;
        current->next = newNode;
        // 추가해야한다고 생각..
        newNode->prev = current;
        flag = 1;
    }
    else if (flag == 0 && current->next == NULL) // 끝까지 찾았는데 해당하는 학번이 존재하지 않는 경우
    {
        fprintf(stdout, "\nNo match found\n");
    }
}

// 어떤 노드 그 앞에 삽입하는 함수
node *insertBefore(node *current)
{
    int rno;
    node *newNode, *temp;
    newNode = (node *)malloc(sizeof(node));
    fprintf(stdout, "\nEnter the roll number before which you want to insert a node\n");
    scanf("%d", &rno);
    getchar();

    init(newNode);

    // 첫번째 노드 앞에 넣고싶은 경우
    if (current->roll_no == rno)
    {
        newNode->next = current;
        current->prev = newNode;
        current = newNode;
        return (current);
    }
    temp = current;
    while (temp->next != NULL) // 끝이 아니라면 반복문 실행
    {
        if (temp->next->roll_no == rno) // 목표로 하는 앞 노드까지 온 경우
        {
            newNode->next = temp->next;
            temp->next->prev = newNode;
            newNode->prev = temp;
            temp->next = newNode;
            return (current);
        }
        temp = temp->next;
    }

    fprintf(stdout, "\nMatch not found\n");
    return (current);
}

// 삭제 함수
node *delete(node *current)
{
    int rno;
    node *newNode, *temp;
    fprintf(stdout, "\nEnter the roll number whose node you want to delete\n");
    scanf("%d", &rno);
    getchar();

    newNode = current;

    // 첫번째 노드를 삭제하는 경우
    if (current->roll_no == rno)
    {
        newNode = current; // Unnecessart step
        current = current->next;
        current->prev = NULL;
        free(newNode);
        return (current);
    }
    else // 첫번째 노드가 아니면 바로 else문 진입
    {
        while (newNode->next->next != NULL)
        {
            if (newNode->next->roll_no == rno)
            {
                newNode = current;
                temp = current->next;
                newNode->next = newNode->next->next;
                temp->next->prev = current;
                free(temp);
                return (current);
            }
            newNode = newNode->next;
        }
        // 마지막노드를 삭제하는 경우
        if (newNode->next->next == NULL && newNode->next->roll_no == rno)
        {
            temp = newNode->next;
            free(temp);
            newNode->next = NULL;
            return (current);
        }
        fprintf(stdout, "\nMatch not found\n");
        return (current);
    }
}

// 검색메뉴 실행함수
void search(node *current)
{
    int ch;
    fprintf(stdout, "\nEnter the criteria for search\n");
    fprintf(stdout, "\n1. Roll number\n");
    fprintf(stdout, "\n2. Name\n");
    fprintf(stdout, "\n3. Marks\n");
    scanf("%d", &ch);
    getchar();

    switch (ch)
    {
    case 1:
        rollSrch(current);
        break;
    case 2:
        nameSrch(current);
        break;
    case 3:
        markSrch(current);
        break;
    default:
        rollSrch(current);
    }
}

// 학번으로 검색
void rollSrch(node *current)
{
    int rno;
    fprintf(stdout, "\nEnter the roll number to search\n");
    scanf("%d", &rno);
    getchar();

    while (current->next != NULL) // 끝이 나올때까지 반복문으로 검색
    {
        if (current->roll_no == rno)
        {
            fprintf(stdout, "\n%d \t%s\t%f\n", current->roll_no, current->name, current->marks);
        }
        current = current->next;
    }
    // 끝에서 찾음
    if (current->next == NULL && current->roll_no == rno)
        fprintf(stdout, "\n%d \t%s\t%f\n", current->roll_no, current->name, current->marks);

    // 추가해야하는 것 아닌지?
    if (current->next == NULL && current->roll_no != rno)
        fprintf(stdout, "\n찾으려는 학번에 해당하는 노드가 존재하지 않습니다.\n");
}

// 이름으로 검색
void nameSrch(node *current)
{
    char arr[20];
    fprintf(stdout, "\nEnter the name to search\n");
    gets(arr);

    while (current->next != NULL) // 끝이 나올 때 까지
    {
        if (strcmp(current->name, arr) == NULL)
        {
            fprintf(stdout, "\n%d\t%s\t%f\n", current->roll_no, current->name, current->marks);
        }
        current = current->next;
    }
    // 끝에서 찾음
    if (current->next == NULL && strcmp(current->name, arr) == NULL)
        fprintf(stdout, "\n%d\t%s\t%f\n", current->roll_no, current->name, current->marks);

    // 추가해야하는 것 아닌지?
    if (current->next == NULL && strcmp(current->name, arr) != NULL)
        fprintf(stdout, "\n찾으려는 이름에 해당하는 노드가 존재하지 않습니다.\n");
}

// 성적으로 찾음
void markSrch(node *current)
{
    float marks;
    fprintf(stdout, "\nEnter the marks to search\n");
    scanf("%f", &marks);
    getchar();

    while (current->next != NULL) // 끝이 나올때까지
    {
        if (current->marks == marks)
            fprintf(stdout, "\n%d\t%s\t%f\n", current->roll_no, current->name, current->marks);
        current = current->next;
    }

    // 끝에서 찾음
    if (current->next == NULL && current->marks == marks)
        fprintf(stdout, "\n%d\t%s\t%f\n", current->roll_no, current->name, current->marks);

    // 추가해야하는 것 아닌지?
    if (current->next == NULL && current->marks != marks)
        fprintf(stdout, "\n찾으려는 성적에 해당하는 노드가 존재하지 않습니다.\n");
}

// 전체 출력
void display(node *current)
{
    fprintf(stdout, "\nroll no\tname\tmark");
    while (current != NULL)
    {
        fprintf(stdout, "\n%4d\t\t%s\t\t%f", current->roll_no, current->name, current->marks);
        current = current->next;
    }
}