#include <stdio.h>
#include <stdlib.h>
int n; // 사용자에게 입력받는 수
typedef struct stackNode
{
    int data;
    struct stackNode *link;
} stackNode;

stackNode *top = NULL; // 숫자를 넣는 스택
char ans[2 * 100001];  // 정답을 저장할 배열
int ansIdx = 0;        // 정답을 저장할 배열의 인덱스

void push(stackNode **top, int data);
void pop(stackNode **top);
int peek(stackNode *top);

void ansPrint(char *arr);        // 정답 배열 출력 함수
void arrayPrint(stackNode *top); // 스택 출력 함수 (확인용)

int num = 0;      // 1부터 n까지의 수를 push하기 위한 변수
int isEndNum = 0; // 마지막 숫자를 입력받았는지 확인하는 변수
int possible = 1; // 순열을 만들 수 있는지 확인하는 변수 (초기값 1)

int main()
{
    scanf("%d", &n); // 사용자에게 첫줄에 n을 입력 받음

    for (int i = 0; i < n; i++)
    {
        // n개의 수를 차례로 사용자에게 입력 받음
        int enter;
        scanf("%d", &enter);

        // 마지막 숫자를 입력했다면,
        // 그 이후부터는 이제 입력한 순서대로 pop만 되어야하지 때문에
        // 입력한 숫자와 가장 위에 있는 숫자가 다르면 순열을 만들 수 없음
        if (possible && isEndNum && (enter != peek(top)))
        {
            possible = 0;
            // 마지막 숫자를 입력받았는데 가장 위의 숫자와 같지 않다면 possible을 0으로 변경
            // 불가능한 상황이더라도 사용자에게 n개의 수를 끝까지 입력 받아야하기 때문에 return 하지 않음
        }

        // 사용자가 입력한 수와 가장 위의 수가 같지 않으면 push 해줌
        while (possible && enter != peek(top))
        {
            // 만약 사용자가 입력한 수가 가장 마지막 수 라면 isEndNum를 1로 변경
            if (enter == n)
                isEndNum = 1;

            // 차례로 넣어줄 num은 n보다 작을때까지만 추가한다. (이 안에서 전위증감하기 때문에 등호는 들어가지 않음)
            if (num < n)
            {
                push(&top, ++num);
                ans[ansIdx++] = '+'; // push 했다면 정답 배열에 + 삽입
            }
            else // num이 n보다 커지게 되면 불가능한 순열이므로 possible을 0으로 변경 후에 반복문을 탈출
            {
                possible = 0;
                break;
            }
        }

        // 사용자가 입력한 값과 가장 위의 값이 같다면 pop한다
        if (possible && enter == peek(top))
        {
            pop(&top);
            ans[ansIdx++] = '-'; // pop 했다면 정답 배열에 - 삽입
        }
    }

    if (possible)
        ansPrint(ans);
    else
        printf("NO\n");

    return 0;
}

void push(stackNode **top, int data)
{
    stackNode *newNode = (stackNode *)malloc(sizeof(stackNode));
    newNode->data = data;
    newNode->link = *top;
    *top = newNode;
}

void pop(stackNode **top)
{
    if (*top == NULL)
        return;

    stackNode *cur = *top;
    (*top) = (*top)->link;

    free(cur);
}

int peek(stackNode *top)
{
    if (top == NULL)
    {
        return 0;
    }
    else
    {
        return top->data;
    }
}

void ansPrint(char *arr)
{
    for (int i = 0; i < ansIdx; i++)
    {
        printf("%c\n", arr[i]);
    }
}

void arrayPrint(stackNode *top)
{
    printf("The stack contains : ");
    for (; top; top = top->link)
    {
        printf("%4d ", top->data);
    }
    printf("\n");
}