// 중위식 표기를 후위식 표기로 변환하여 계산하는 예제 프로그램
#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPR_SIZE 100
#define MAX_STACK_SIZE 100

// 익명 열거형 정의
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
}; // 중위표기식을 입력받는 변수
char postexpr[MAX_EXPR_SIZE] = {
    0,
};                            // 후위표기식을 저장하는 배열 변수
char *postfixExpr = postexpr; // 후위표기식을 가리키고 있는 포인터 변수
precedence stack[MAX_STACK_SIZE];

int evalStack[MAX_STACK_SIZE];
// 우선순위
int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};  // 스택 맨위
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0}; // 들어오는 애 (나)
int top = -1;
int evalTop = -1;

void stackFull(const char *type);  // 스택이 가득찼을 때 에러처리하는 함수
void stackEmpty(const char *type); // 스택이 비었을 때 에러처리하는 함수

// 중위 표기식을 후위표기식으로 변환하는 데 필요한 함수
void push(precedence item);
precedence pop();
void printToken(precedence token);
precedence getToken(char *symbol, int *n);
void postfix(); // 중위 표기식 -> 후위 표기식 변환 실행 함수

// 변환한 후위표기식을 계산하는 데 필요한 함수
void evalPush(int item);
int evalPop();
int getEvalToken(char *symbol, int *n);
int eval(); // 바뀐 후위 표기식을 가지고 계산하는 실행 함수

int main(int argc, char *argv[])
{
    fprintf(stdout, "input infix : ");
    scanf("%s", expr);                        // 중위표기식을 입력받는다.
    postfix();                                // 후위표기식으로 변환하는 함수를 실행
    fprintf(stdout, "result : %d\n", eval()); // 후위표기식을 계산하는 함수 실행
}

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

// 중위표기식을 후위표기식으로 변환하는 데 필요한 함수들 먼저 작성
void push(precedence item)
{
    // 스택에 연산자를 넣는다.
    if (top >= MAX_STACK_SIZE - 1)
        stackFull("token");
    stack[++top] = item;
}

precedence pop()
{
    // 스택으로부터 연산자를 pop하고 pop한 연산자를 반환한다.
    if (top == -1)
        stackEmpty("token");
    return stack[top--];
}

void printToken(precedence token)
{
    // 토큰의 종류에 따라 알맞은 연산자로 출력하는 함수
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

// 문자열을 하나씩 돌면서 이름으로 반환하는 함수
precedence getToken(char *symbol, int *n)
{
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
    case '/':
        return divide;
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
    // 초기 설정

    // getToken함수로 토큰을 하나씩 입력받아서 이름으로 반환한 것을 token이 받는다
    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
    {
        if (token == operand)        // 피연산자라면
            *postfixExpr++ = symbol; // 문자열에 추가
        else if (token == rparen)    // 오른쪽 괄호라면
        {
            while (stack[top] != lparen) // 왼쪽 괄호가 나올 때 까지
                printToken(pop());       // pop하여 연산자들을 출력한다.
            pop();
        }
        else // 그 이외의 연산자라면 -> 우선순위를 확인해야함
        {
            while (isp[stack[top]] >= icp[token]) // 스택맨위에있는 애보다 들어오는애(나)가 우선순위가 높거나 같으면 pop하여 출력한다.
                printToken(pop());                // 스택 맨위꺼보다 내 우선순위가 더 높으면 push, 스택 맨위보다 내가 낮거나 같으면 pop하고나서 나를 push
            push(token);
        }
    }

    while ((token = pop()) != eos) // 스택이 빌때까지 pop 출력
        printToken(token);
    fprintf(stdout, "postfix : %s\n", postexpr);
}

// 바뀐 후위표기식을 계산하는 데 필요한 함수들
void evalPush(int item)
{
    if (evalTop >= MAX_STACK_SIZE - 1)
        stackFull("eval");
    evalStack[++evalTop] = item;
}

int evalPop()
{
    if (evalTop == -1)
        stackEmpty("eval");
    return evalStack[evalTop--];
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
    case '/':
        return divide;
    case '*' :
        return times;
    case '%':
        return mod;
    case '\0':
        return eos;
    default:
        return operand;
    }
}

int eval()
{
    precedence token;
    char symbol;
    int n = 0;
    evalTop = -1;
    int op1, op2;

    token = getEvalToken(&symbol, &n);
    while (token != eos)
    {
        if (token == operand)
            evalPush(symbol - 0x30);
        else
        {
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
        token = getEvalToken(&symbol, &n);
    }
    return evalPop();
}