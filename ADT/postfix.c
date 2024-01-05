#include <stdio.h>
#include <stdlib.h>
#define MAX_EXPR_SIZE 100
#define MAX_STACK_SIZE 100

typedef enum
{
    lparen,
    rparen,
    plus,
    minus,
    times,
    divide,
    mod,
    eos,
    operand
} precedence;

char expr[MAX_EXPR_SIZE] = {
    0,
};
char postexpr[MAX_EXPR_SIZE] = {
    0,
};
char *postfixExpr = postexpr;

precedence stack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];

int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

int top = -1;
int evalTop = -1;

void stackFull(const char *type)
{
    fprintf(stderr, "%s Stack is full cannot add elements\n", type);
    exit(EXIT_FAILURE);
}

void stackEmpty(const char *type)
{
    fprintf(stderr, "%s Stack is empty cannot delete elements\n", type);
    exit(EXIT_FAILURE);
}

void push(precedence item)
{
    if (top >= MAX_STACK_SIZE - 1)
        stackFull("token");
    stack[++top] = item;
}

void evalPush(int item)
{
    if (evalTop >= MAX_STACK_SIZE - 1)
        stackFull("eval");
    evalStack[++evalTop] = item;
}

precedence pop()
{
    if (top == -1)
        stackEmpty("token");
    return stack[top--];
}

int evalPop()
{
    if (evalTop == -1)
        stackEmpty("eval");
    return evalStack[evalTop--];
}

void printToken(precedence token)
{
    switch (token)
    {
    case 2:
        *postfixExpr++ = '+';
        break;
    case 3:
        *postfixExpr++ = '-';
        break;
    case 4:
        *postfixExpr++ = '*';
        break;
    case 5:
        *postfixExpr++ = '/';
        break;
    case 6:
        *postfixExpr++ = '%';
        break;
    }
}

/* 입력 스트링으로부터 토큰을 가져오는 함수 */
precedence getToken(char *symbol, int *n)
{
    /* 다음 토큰을 취함. symbol은 문자 표현이며, token은 그것의 열거된 값으로 표현되고, 함수 이름으로 변환 */
    *symbol = expr[(*n)++];
    switch (*symbol)
    {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '*':
        return times;
    case '%':
        return mod;
    case '\0':
        return eos;
    default:
        return operand; /* 에러 검사는 하지 않고 기본 값은 피연산자 */
    }
}

int getEvalToken(char *symbol, int *n)
{
    *symbol = postexpr[(*n)++];
    switch (*symbol)
    {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '*':
        return times;
    case '%':
        return mod;
    case '\0':
        return eos;
    default:
        return operand;
    }
}

void postfix()
{
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;
    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
    {
        if (token == operand)
            *postfixExpr++ = symbol;
        else if (token == rparen)
        {
            while (stack[top] != lparen)
                printToken(pop());
            pop();
        }
        else
        {
            while (isp[stack[top]] >= icp[token])
                printToken(pop());
            push(token);
        }
    }
    while ((token = pop()) != eos)
        printToken(token);
    printf("postfix : %s\n", postexpr);
}

/* 후위 표기식을 계산하는 함수 */

int eval(void)
{
    /*  전역변수로 되어있는 후휘 표기식 expr을 연산. '\0'은 수식의 끝을 나타냄. stack과 top은 전역변수.
        함수 getToken은 토큰의 타입과 문자 심벌을 반환. 피연산자는 한 문자로 된 숫자임을 가정 */
    precedence token;
    char symbol;
    int n = 0; // 수식 스트링을 위한 카운터
    evalTop = -1;
    int op1, op2;

    token = getToken(&symbol, &n);
    while (token != eos)
    {
        if (token == operand)
            evalPush(symbol - 0x30); // 스택 삽입
        else
        {
            /* 두 피연산자를 삭제하여 연산을 수행한 후, 그 결과를 스택에 삽입 */
            op2 = evalPop();
            op1 = evalPop();
            switch (token)
            {
            case 2:
                evalPush(op1 + op2);
                break;
            case 3:
                evalPush(op1 - op2);
                break;
            case 4:
                evalPush(op1 * op2);
                break;
            case divide:
                evalPush(op1 / op2);
                break;
            case mod:
                evalPush(op1 % op2);
            }
        }
        token = getToken(&symbol, &n);
    }
    return evalPop(); // 결과를 반환
}

int main(int argc, char *argv[])
{
    printf("input infix : ");
    scanf("%s", expr);
    postfix();
    printf("result : %d\n", eval());
}