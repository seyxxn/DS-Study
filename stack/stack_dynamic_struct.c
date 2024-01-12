// 구조체 + 동적할당을 이용한 스택 구현
#include <stdio.h>
#include <stdlib.h>
// 최대 크기 지정한거 삭제
// 최대크기 변수모두 capacity 로 변경
typedef struct
{
    int key;
} element;

element *stack;
int top = -1;
int capacity = 1;
// 메모리 공간 변수 추가

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
    if (top >= capacity - 1)
    {
        return 1;
    }
    return 0;
}

// 스택이 가득 찼을 때 오류처리 추가
void stackFull()
{
    // 더 많은 원소를 저장하기 위해 크기를 두배로 늘린다.
    stack = realloc(stack, 2 * capacity * sizeof(*stack));
    capacity *= 2;
    printf("Stack의 크기를 늘렸습니다. 현재 크기 : %d\n", capacity);
}

void push(element num)
{
    if (isFull())
    {
        stackFull();
    }
    stack[++top] = num;
}

element stackEmpty()
{
    element temp;
    temp.key = -1;
    return temp;
}

element pop()
{
    if (isEmpty())
    {
        printf("Stack에 저장된 값이 없습니다.\n");
        return stackEmpty();
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
    // 초기 스택 메모리 할당 **
    stack = malloc(capacity * sizeof(*stack));
    
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
    free(stack);
    return 0;
}
