// https://blog.naver.com/tipsware/221211999708 참고 **
// 배열을 이용한 스택 구현 (전역 변수)
// 가장 간단한 방법

#include <stdio.h>
#define MAX_STACK_SIZE 30 // 스택의 최대 크기를 임의로 지정

int stack[MAX_STACK_SIZE]; // 스택으로 사용할 메모리 공간
int top = -1;              // 스택에 저장된 데이터의 개수
                           // 0으로 초기화 해도 되는데 보통 -1로 하는 이유는 인덱스 오류 방지 .. 등. 사실 상관없음 내 마음임

// 스택이 비었는지 확인하는 함수
int isEmpty()
{
    if (top == -1)
    {
        return 1;
    }
    return 0;
}

// 스택이 꽉 찼는지 확인하는 함수
int isFull()
{
    if (top >= MAX_STACK_SIZE - 1)
    { // -1 반드시 기억. 주의하기 ** 배열의 인덱스는 0부터 시작하기 때문에
        // 배열의 유효한 인덱스는 MAX_STACK_SIZE에서 -1한 값이다.
        return 1;
    }
    return 0;
}

// 스택에 값을 넣는 함수
void push(int num)
{
    if (isFull())
    {
        printf("Stack이 가득차서 값을 더 이상 넣을 수 없습니다.\n");
        return;
    }
    stack[++top] = num; // 반드시 ++top (top을 먼저 증가시켜야함)
}

// 스택에서 마지막에 입력된 정수 값을 하나 가져오는 함수
int pop()
{
    if (isEmpty())
    {
        printf("Stack에 저장된 값이 없습니다.\n");
        return -1;
    }
    return stack[top--];
}

// 스택에 가장 위에있는 숫자를 가져오는 함수
int peek()
{
    return stack[top];
}

// 스택에 저장된 수의 개수를 반환하는 함수
int count()
{
    return top + 1;
}

// 스택에 있는 값들을 출력하는 함수
void printStack()
{
    if (isEmpty())
    {
        printf("Stack이 비어있습니다.\n");
        return;
    }
    printf("Stack에 저장된 값의 목록\n");
    for (int i = 0; i <= top; i++)
    {
        printf("[%03d] : %d ", i, stack[i]);
    }
    printf("\n총 %d개의 값이 저장되어 있습니다.\n", count());
}

int main(void)
{
    int select_index = 0, temp = 0;

    while (select_index != 9)
    {
        printf("\n\n1. Stack에 값 넣기 \n");
        printf("2. Stack에서 값 꺼내기\n");
        printf("3. Stack에서 가장 위에 있는 값 학인\n");
        printf("4. Stack에 저장된 값의 개수 확인\n");
        printf("5. Stack에 있는 값 모두 확인");
        printf("9. 프로그램 종료 \n\n");
        printf("선택 : ");
        scanf("%d", &select_index);

        switch (select_index)
        {
        case 1:
            printf("저장할 값을 입력하세요 : ");
            scanf("%d", &temp);
            push(temp);
            break;

        case 2:
            temp = pop();
            if (temp == -1)
                break;
            else
                printf("제거된 값 : %d\n", temp);
            break;
        case 3:
            printf("%d\n", peek());
            break;
        case 4:
            printf("저장된 값의 개수 : %d\n", count());
            break;
        case 5:
            printStack();
            break;
        }
    }
    return 0;
}
