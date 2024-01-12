// 구조체를 이용한 스택 구현
// 배열을 사용한 스택 구현에서 부분부분 수정해야하는 곳 많음 
// 반환 형식 주의하여 작성해야 함

#include <stdio.h>
#define MAX_STACK_SIZE 30 

// 구조체 정의
typedef struct {
    int key;
} element;

// 스택 생성
element stack[MAX_STACK_SIZE];
int top = -1;

int isEmpty()
{
    if (top == -1)
    {
        return 1;
    }
    return 0;
}

int isFull()
{
    if (top >= MAX_STACK_SIZE - 1)
    { 
        return 1;
    }
    return 0;
}

// 매개변수 형식 수정
void push(element num)
{
    if (isFull())
    {
        printf("Stack이 가득차서 값을 더 이상 넣을 수 없습니다.\n");
        return;
    }
    stack[++top] = num; 
}

// 오류상태를 나타내는 element 객체를 반환하는 함수
element stackEmpty(){
    element temp;
    temp.key = -1;
    return temp;
}

// 반환값 형식 수정
element pop()
{
    if (isEmpty())
    {
        printf("Stack에 저장된 값이 없습니다.\n");
        return stackEmpty(); // 오류처리하는 함수를 새로 만들어서 그걸로 반환
    }
    return stack[top--];
}

element peek()
{
    return stack[top];
}

int count()
{
    return top + 1;
}

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
        printf("[%03d] : %d ", i, stack[i].key);
    }
    printf("\n총 %d개의 값이 저장되어 있습니다.\n", count());
}

int main(void)
{
    int select_index = 0;
    element temp;

    while (select_index != 9)
    {
        printf("\n\n1. Stack에 값 넣기 \n");
        printf("2. Stack에서 값 꺼내기\n");
        printf("3. Stack에서 가장 위에 있는 값 학인\n");
        printf("4. Stack에 저장된 값의 개수 확인\n");
        printf("5. Stack에 있는 값 모두 확인\n");
        printf("9. 프로그램 종료 \n\n");
        printf("선택 : ");
        scanf("%d", &select_index);

        switch (select_index)
        {
        case 1:
            printf("저장할 값을 입력하세요 : ");
            scanf("%d", &temp.key);
            push(temp);
            break;

        case 2:
            temp = pop();
            if (temp.key == -1)
                break;
            else
                printf("제거된 값 : %d\n", temp.key);
            break;
        case 3:
            printf("%d\n", peek().key);
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
