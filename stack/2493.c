#include <stdio.h>
#include <stdlib.h>
int n;

typedef struct stackNode
{
    int index;  // 탑의 번호
    int height; // 탑의 높이
    struct stackNode *link;
} stackNode;

void push(stackNode **top, int index, int height);
int pop(stackNode **top);
int peek(stackNode *top);
void solve(int n, int heights[]);
void printStack(stackNode *top);

int main()
{
    scanf("%d", &n);

    int heights[n]; // 사용자가 입력할 높이들을 저장할 배열 선언
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &heights[i]);
    }
    solve(n, heights);
    return 0;
}

// 노드 삽입 함수
void push(stackNode **top, int index, int height)
{
    stackNode *newNode = (stackNode *)malloc(sizeof(stackNode));
    newNode->index = index;
    newNode->height = height;
    newNode->link = *top;
    *top = newNode;
}

// 노드 삭제 함수 (가장 위에있는 노드를 삭제하며 그 노드의 인덱스를 반환함)
int pop(stackNode **top)
{
    if (*top == NULL)
        return -1;

    stackNode *deleteNode = *top;
    int index = deleteNode->index;
    *top = (*top)->link;

    free(deleteNode);
    return index;
}

// 가장 위에있는 수를 반환하는 함수
int peek(stackNode *top)
{
    if (top == NULL)
        return -1;
    return top->height;
}

void printStack(stackNode *top)
{
    for (; top; top = top->link)
        printf("[%d] %d -> ", top->index, top->height);
    printf("\n");
}

// 풀이 함수
void solve(int n, int heights[])
{
    // top을 가리키는 포인터 선언
    stackNode *top = NULL;
    int result[n]; // 결과 값을 저장할 배열 선언

    // n번 반복문 실행
    for (int i = 0; i < n; i++)
    {
        while (top != NULL && heights[i] >= peek(top))
        {
            pop(&top);
        }

        if (top == NULL)
            result[i] = 0;
        else
            result[i] = top->index;

        push(&top, i + 1, heights[i]);
        // printStack(top);
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", result[i]);
    }
}
