#include <stdio.h>
#include <stdlib.h>
int n;
int stack[500001];
int ansStack[500001];
int top = -1;
void push(int x);
int pop();
int peek(int idx);
void stackPrint(int arr[]);

int main()
{
    scanf("%d", &n); // 사용자로부터 n을 입력 받음

    // 높이를 입력받고, stack에 넣음
    for (int i = 0; i < n; i++)
    {
        int enter;
        scanf("%d", &enter);
        push(enter);
    }
    int breakOutLoop = 0;

    for (int i = n - 1; i >= 0 && !breakOutLoop; i--)
    {
        int popValue = pop(); // 우선 무조건 하나를 pop
        // pop된 값과 가장 상위 값을 비교
        // pop된 값보다 상위 값이 작으면 -> 그냥 지나침 -> pop
        // pop된 값보다 값이 큰 상위 값이 나올 때 까지 반복해야함
        int idx = top;
        while (popValue > peek(idx))
        {
            if (idx - 1 > 0)
            {
                idx--;
            }
            else
            {
                breakOutLoop = 1;
                break;
            }
        }
        // 반복문 탈출함 pop된 값보다 상위 값이 커짐
        ansStack[i] = idx + 1; // top은 -1부터 시작하지만, 출력할때는 1번째부터니까 +1
    }

    ansStack[0] = 0; // 가장 먼저 세워진 탑은 보낼 수 없음

    // 가장 높은 탑도 보낼 수 없음
    int max = 0;
    int maxIdx = 0;
    for (int i = 0; i < n; i++)
    {
        if (stack[i] >= max)
        {
            max = stack[i];
            maxIdx = i;
        }
    }
    ansStack[maxIdx] = 0;

    stackPrint(ansStack);
}

void push(int x)
{
    stack[++top] = x;
}
// 가장 위에있는 값을 삭제하는 함수
int pop()
{
    return stack[top--];
}
// 해당하는 인덱스의 값을 반환해주는 함수
int peek(int idx)
{
    return stack[idx];
}

void stackPrint(int arr[])
{
    for (int i = 0; i < n; i++)
    {
        printf("[%d] %d ", i, arr[i]);
    }
    printf("\n");
}