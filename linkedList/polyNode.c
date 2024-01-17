// 단일 연결 리스트를 활용한 다항식 프로그램
// 하나의 다항식은 하나의 연결 리스트로 표현되고,
// 각 노드는 다항식의 항을 나타내며, 계수와 지수를 저장하는 정보를 포함

#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

typedef struct polyNode
{
    int coef;  // 계수
    int expon; // 지수
    struct polyNode *next;
} polyNode;

void attach(int coefficient, int exponent, polyNode *head);
void print_ll(polyNode *head);
polyNode *padd(polyNode *a, polyNode *b);
polyNode *pmul(polyNode *a, polyNode *b);

int main()
{
    polyNode *a = (polyNode *)malloc(sizeof(polyNode));
    polyNode *b = (polyNode *)malloc(sizeof(polyNode));

    attach(4, 3, a);
    attach(3, 2, a);
    attach(5, 1, a);
    printf("A의 다항식 : ");
    print_ll(a);

    attach(3, 4, b);
    attach(1, 3, b);
    attach(2, 1, b);
    attach(1, 0, b);
    printf("B의 다항식 : ");
    print_ll(b);

    printf("다항식의 덧셈 결과 : ");
    print_ll(padd(a, b));

    printf("다항식의 곱셈 결과 : ");
    print_ll(pmul(a, b));
    // 12x^7 + 13X^6 + 18X^5 + 13X^4 + 10X^3 + 13X^2 + 5X^1

    return 0;
}

// 다항식 항 추가 함수
void attach(int coefficient, int exponent, polyNode *head)
{
    polyNode *temp = (polyNode *)malloc(sizeof(polyNode)); // 새로운 항
    polyNode *current = head;                              // 현재 연결 리스트의 끝을 찾기 위한 포인터

    // 새로운 항에 데이터 추가
    temp->coef = coefficient;
    temp->expon = exponent;
    temp->next = NULL; // 일단 NULL로

    // 연결리스트의 끝을 찾는 반복문
    while (current->next != NULL)
    {
        current = current->next;
    }

    // 끝을 찾으면, 새로운 노드 temp를 추가하여 다항식에 연결
    current->next = temp;
}

void print_ll(polyNode *head)
{
    if (head->next == NULL)
    {
        return;
    }

    polyNode *temp = head->next;
    while (temp != NULL)
    {
        if (temp->next == NULL)
        {
            printf("%dX^%d ", temp->coef, temp->expon);
        }
        else
        {
            printf("%dX^%d + ", temp->coef, temp->expon);
        }
        temp = temp->next;
    }
    printf("\n");
}

// a와 b가 합산된 다항식을 반환하는 함수
polyNode *padd(polyNode *a, polyNode *b)
{
    polyNode *c = (polyNode *)malloc(sizeof(polyNode));
    int sum;

    while (a && b)
    {
        switch (COMPARE(a->expon, b->expon))
        {
        case -1: // a의 지수 < b의 지수
            attach(b->coef, b->expon, c);
            b = b->next;
            break;
        case 0: // a의 지수 == b의 지수
            sum = a->coef + b->coef;
            if (sum)
                attach(sum, a->expon, c);
            a = a->next;
            b = b->next;
            break;
        case 1: // a의 지수 < b의 지수
            attach(a->coef, a->expon, c);
            a = a->next;
            break;
        }
    }

    // 리스트 a와 리스트 b의 나머지를 복사
    for (; a; a = a->next)
        attach(a->coef, a->expon, c);
    for (; b; b = b->next)
        attach(b->coef, b->expon, c);

    return c;
}

// a와 b가 곱해신 다항식을 반환하는 함수
polyNode *pmul(polyNode *a, polyNode *b)
{
    polyNode *c = (polyNode *)malloc(sizeof(polyNode));
    c->next = NULL;

    polyNode *currentA = a->next;
    polyNode *currentB = b->next;

    // 각 다항식은 내림차순으로 정리되므로 각 첫 항을 곱해주면 최고차항을 알 수 있음
    int highest = currentA->expon + currentB->expon;

    // 최고차항의 지수의 크기 만큼 동적 배열을 할당하여 0으로 초기화 (calloc함수 이용)
    int *multiply = calloc(highest + 1, sizeof(int));
    // 0승부터 시작해야하므로 + 1

    // a의 n번째 항과 b의 각 항을 곱한 뒤 a는 n+1(그 다음)로, b는 다시 처음으로 돌아가게 함
    while (currentA != NULL)
    {
        if (currentB != NULL)
        {
            multiply[currentA->expon + currentB->expon] += currentA->coef * currentB->coef;
            // printf("%dX^%d ", multiply[currentA->expon + currentB->expon], currentA->expon + currentB->expon);
            currentB = currentB->next;
        }
        else // b가 null이 되어 다 끝나면
        {
            currentA = currentA->next; // a는 그 다음으로 넘어감
            currentB = b->next;              // b는 다시 처음으로
        }
    }


    // 각 지수에 대응되는 배열 index에 0이 아닌 숫자가 있으면 결과식에 삽입함
    for (int i = highest; i >= 0; i--)
    {   
        if (multiply[i] != 0)
        {
            attach(multiply[i], i, c);
        }
    }

    return c;
}