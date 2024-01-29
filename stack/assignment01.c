#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_SIZE 100
#define MAX_STACK_SIZE 100

typedef struct Node
{
    char data[MAX_EXPR_SIZE];
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top; // 스택의 top을 나타내는 포인터
    int size;
} Stack;

typedef enum _precedence
{
    lparen,
    rparen,
    plus,
    minus,
    times,
    divide,
    mod,
    power, // ^ (제곱)
    eos,
    operand
} precedence;

char expr[MAX_EXPR_SIZE];      // 사용자에게 표기식을 입력받는 변수
char exprToken[MAX_EXPR_SIZE]; // 사용자에게 표기식을 입력받아 토큰을 구분하여 넣음
Stack exprInStack;             // 사용자에게 받은 문자열을 삽입한 스택 선언
Stack exprInStackOrigin;       // 사용자에게 받은 문자열을 삽입한 스택 -> 순회하기 위해 만든 스택
int continueCheck = 1;         // 사용자에게 입력을 계속 받는 것을 제어하는 변수
int typeCheck[3] = {0, 0, 0};  // 순서대로, 전위 중위 후위 표현법 (표현법에 해당하면 1, 해당하지 않으면 0)
                               // -> 수식 바뀔 때 마다 초기화 필요

// 우선순위
// (, ), +, -, *, /, %, ^, eos 순서
int isp[] = {0, 17, 12, 12, 13, 13, 13, 15, 0};
int icp[] = {20, 17, 12, 12, 13, 13, 13, 15, 0};

void execute(); // 실행하는 함수 따로 뺌

void initialize(Stack *stack);       // 스택 초기화 함수
int isEmpty(Stack *stack);           // 스택이 비었는지 확인하는 함수
void push(Stack *stack, char *data); // 스택에 새로운 노드를 삽입하는 함수
char *pop(Stack *stack);             // 스택 추출 함수
char *top(Stack *stack);             // 가장 맨 위 원소 추출 함수

void getTokenToStack(char *expr, Stack *stack); // 문자열형태로 입력받은 수식을 분리하여 스택에 저장해야함
void printStack(Stack *stack);                  // 스택 확인용 출력 함수
int isNumber(char *str);                        //  숫자인지 아닌지 확인하는 함수
int errorCheck(Stack *stack);                   // 토큰 오입력 예외처리 함수
void expressionType(Stack *stack);              // 전위인지 중위인지 후위인지 확인하는 함수

// 중위-> 후위, 중위->전위, 후위->중위, 전위 ->중위 (변환함수 4개 필요)
void printToken(precedence token); // 토근의 인덱스를 인자로 받아, 후위표기식 문자열에 문자를 추가하는 함수
precedence getToken(Stack *stack, char *symbol);
void infixToPostfix(); // 중위->후위

void expressionPush(Stack *stack, precedence item);
precedence expresstionPop(Stack *stack);

char *infixExpr[MAX_EXPR_SIZE] = {
    0,
};
int infixExprLen = 0;
char postexpr[MAX_EXPR_SIZE] = {
    0,
};                            // 후위표기식을 저장하는 배열 변수
char *postfixExpr = postexpr; //   후위표기식을 가리키고 있는 포인터변수

int main(int argc, char *argv[])
{
    initialize(&exprInStack);
    initialize(&exprInStackOrigin);

    if (argc == 1) // 프로그램 실행 후 수식입력 받는 경우
    {
        while (continueCheck)
        {
            printf("input expression : ");
            fgets(expr, sizeof(expr), stdin);
            expr[strcspn(expr, "\n")] = '\0';

            if (strcmp(expr, "exit") == 0)
            {
                printf("exit program..\n");
                continueCheck = 0;
                return 0;
            }
            else if (expr[0] == '\0')
            {
                continue;
            }
            else
            {
                execute();
            }
            // stack을 초기화
            initialize(&exprInStack);
            typeCheck[0] = 0;
            typeCheck[1] = 0;
            typeCheck[2] = 0;
        }
    }
    else if (argc == 2) // 명령행 인자로 수식 입력받은 경우 -> 하나의 수식 분석 후에 프로그램 종료
    {
        strcpy(expr, argv[1]);
        execute();
    }

    return 0;
}

// 실행함수
void execute()
{
    getTokenToStack(expr, &exprInStack);
    // 새로운 스택을 만들어서 exprInStack의 내용을 복사
    Stack tempStack;
    initialize(&tempStack);

    while (!isEmpty(&exprInStack))
    {
        push(&tempStack, pop(&exprInStack));
    }

    // tempStack의 내용을 exprInStack과 exprInStackOrigin에 복사
    while (!isEmpty(&tempStack))
    {
        char *data = pop(&tempStack);
        push(&exprInStack, data);
        push(&exprInStackOrigin, data);
        infixExpr[infixExprLen++] = data;
    }

    // printStack(&exprInStack);
    // printStack(&exprInStackOrigin);

    if (errorCheck(&exprInStack))
    {
        printf("error : wrong token input\n");
        initialize(&exprInStack);
        initialize(&exprInStackOrigin);
        return;
    }
    expressionType(&exprInStack);
    printf("infix : ");
    if (typeCheck[1])
    {
        printf("possible\n");
        infixToPostfix(); // 일단 임시로 여기서 테스트
        printf("%s\n", postfixExpr);
        memset(infixExpr, 0, infixExprLen);
        memset(postfixExpr, 0, 100);
        infixExprLen = 0;
    }
    else
    {
        printf("impossible\n");
    }

    printf("prefix : ");
    if (typeCheck[0])
    {
        printf("possible\n");
    }
    else
    {
        printf("impossible\n");
    }

    printf("postfix : ");
    if (typeCheck[2])
    {
        printf("possible\n");
    }
    else
    {
        printf("impossible\n");
    }
}
void initialize(Stack *stack)
{
    stack->top = NULL;
    stack->size = 0;
}

int isEmpty(Stack *stack)
{
    return (stack->top == NULL);
}

// 스택에 새로운 노드를 삽입하는 함수
void push(Stack *stack, char *data)
{
    Node *temp = (Node *)malloc(sizeof(Node)); // 노드 생성
    strcpy(temp->data, data);                  // 스트링 복사함수를 이용하여 data값을 temp->data에 복사
    temp->next = stack->top;                   // 노드의 다음 포인터가 stack의 top을 가리키게
    stack->top = temp;                         // 최근에 넣은 노드를 top으로 설정함(Stack의 성질)
    stack->size = stack->size + 1;
}

// top을 스택에서 추출하고 반환하는 함수
char *pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        fprintf(stderr, "Stack Underflow");
        exit(EXIT_FAILURE);
    }
    Node *temp = stack->top;
    char *data = (char *)malloc(sizeof(char) * MAX_EXPR_SIZE);
    strcpy(data, temp->data);
    stack->top = stack->top->next;
    stack->size = stack->size - 1;
    free(temp);
    return data;
}

char *top(Stack *stack)
{
    if (isEmpty(stack))
    {
        fprintf(stderr, "Stack is empty");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

// 문자열을 토큰으로 쪼개서 스택에 push하는 함수
void getTokenToStack(char *expr, Stack *stack)
{
    char *ptr = strtok(expr, " \t");
    while (ptr != NULL)
    {
        push(stack, ptr);
        ptr = strtok(NULL, " ");
    }
}

// 스택 출력하는 함수
void printStack(Stack *stack)
{
    for (Node *p = stack->top; p != NULL; p = p->next)
        printf("%s -> ", p->data);
    printf("NULL\n");
    printf("size : %d\n", stack->size);
}

// 문자열이 숫자가 맞는지 확인하는 함수
int isNumber(char *str)
{
    int dotCnt = 0; // 소수점의 개수를 세는 변수

    if (*str == '-')
    {
        str++; // '-'를 무시하고 다음 문자로 이동
    }

    while (*str)
    {
        if (!isdigit(*str) && *str != '.')
        // 숫자가 아니고 소수점이 아닌 것이 들어오면 0 반환
        {
            return 0;
        }
        // 소수점이 들어오게 되면 소수점 카운트
        if (*str == '.')
        {
            dotCnt++;
            if (dotCnt > 1) // 소수점이 1개보다 많으면 숫자가 아님 -> 0을 반환
                return 0;
        }
        str++;
    }
    return 1; // 모든 검사를 마쳐 숫자임을 확인하고 1을 반환
}

// 토큰 오입력 예외처리 함수-> 예외 처리해야하면 1을 반환, 예외처리 안해도 되면 0을 반환
int errorCheck(Stack *stack)
{
    for (Node *p = stack->top; p != NULL; p = p->next)
    {
        if (isNumber(p->data) ||
            strcmp(p->data, "+") == 0 || strcmp(p->data, "-") == 0 || strcmp(p->data, "*") == 0 ||
            strcmp(p->data, "/") == 0 || strcmp(p->data, "%") == 0 || strcmp(p->data, "^") == 0 ||
            strcmp(p->data, "(") == 0 || strcmp(p->data, ")") == 0)
        {
            continue;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

// 전위인지 중위인지 후위인지 확인하는 함수
// typeCheck 배열 변수를 조정함
void expressionType(Stack *stack)
{
    if (stack->size == 1) // stack의 크기가 1일때
    {
        if (isdigit(top(stack)[0])) // 그게 숫자인 경우
        {
            typeCheck[0] = 1;
            typeCheck[1] = 1;
            typeCheck[2] = 1;
            return;
        }
        else
        {                                        // 숫자가 아닌경우
            printf("error : input is single\n"); // 임의로 에러처리 (명세에는 없음)
            return;
        }
    }
    else if (stack->size == 2) // stack의 크기가 2일때
    {
        printf("error : input is two\n");
        return;
    }
    else
    {
        while (stack->size > 2)
            pop(stack);

        char secondData[MAX_EXPR_SIZE];
        strcpy(secondData, pop(stack));

        char firstData[MAX_EXPR_SIZE];
        strcpy(firstData, pop(stack));

        //  첫번째가 괄호라면 -> 중위
        if (firstData[0] == '(')
        {
            typeCheck[1] = 1;
            // printf("first : %s secod : %s \n", firstData, secondData);
        }
        // 첫번째가 연산자라면 -> 전위
        else if (strchr("+-*/%^", firstData[0]) != NULL)
        {
            typeCheck[0] = 1;
            // printf("first : %s secod : %s \n", firstData, secondData);
        }
        // 첫번째가 숫자고, 두번째가 연산자라면 -> 중위
        else if (isNumber(firstData) && strchr("+-*/%^", secondData[0]) != NULL)
        {
            typeCheck[1] = 1;
            // printf("first : %s secod : %s \n", firstData, secondData);
        }
        // 첫번째와 두번째 값이 모두 숫자라면 -> 후위
        else if (isNumber(firstData) && isNumber(secondData))
        {
            typeCheck[2] = 1;
            // printf("first : %s secod : %s \n", firstData, secondData);
        }

        return;
    }
}

void expressionPush(Stack *stack, precedence item)
{
    Node *temp = (Node *)malloc(sizeof(Node));

    switch (item)
    {
    case lparen:
        strcpy(temp->data, "(");
        break;
    case rparen:
        strcpy(temp->data, ")");
        break;
    case plus:
        strcpy(temp->data, "+");
        break;
    case minus:
        strcpy(temp->data, "-");
        break;
    case times:
        strcpy(temp->data, "*");
        break;
    case divide:
        strcpy(temp->data, "/");
        break;
    case mod:
        strcpy(temp->data, "%");
        break;
    case power:
        strcpy(temp->data, "^");
        break;
    case eos:
        strcpy(temp->data, "\0");
        break;
    case operand:
        break;
    }

    temp->next = stack->top;
    stack->top = temp;
    stack->size = stack->size + 1;
}

precedence expresstionPop(Stack *stack)
{
    if (isEmpty(stack))
    {
        fprintf(stderr, "Stack Underflow");
        exit(EXIT_FAILURE);
    }

    Node *temp = stack->top;
    stack->top = stack->top->next;
    stack->size = stack->size - 1;
    precedence data = getToken(stack, temp->data);
    free(temp);
    return data;
}

precedence getToken(Stack *stack, char *symbol)
{
    if (isEmpty(stack))
    {
        printf("empty\n");
        return eos;
    }

    switch (symbol[0])
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
    case '/':
        return divide;
    case '%':
        return mod;
    case '^':
        return power;
    case '\0':
        return eos;
    default:
        return operand;
    }
}

void printToken(precedence token)
{
    switch (token)
    {
    case plus:
        *postfixExpr++ = '+';
        break;
    case minus:
        *postfixExpr++ = '-';
        break;
    case times:
        *postfixExpr++ = '*';
        break;
    case divide:
        *postfixExpr++ = '/';
        break;
    case mod:
        *postfixExpr++ = '%';
        break;
    case power:
        *postfixExpr++ = '^';
        break;
    default:
        break;
    }
}

char *getSymbolString(precedence token)
{
    static char symbol[4];
    switch (token)
    {
    case plus:
        strcpy(symbol, "+");
        break;
    case minus:
        strcpy(symbol, "-");
        break;
    case times:
        strcpy(symbol, "*");
        break;
    case divide:
        strcpy(symbol, "/");
        break;
    case mod:
        strcpy(symbol, "%");
        break;
    case power:
        strcpy(symbol, "^");
        break;
    default:
        break;
    }
    return symbol;
}

precedence getTokenFromChar(char op)
{
    switch (op)
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
    case '/':
        return divide;
    case '%':
        return mod;
    case '^':
        return power;
    default:
        return operand;
    }
}

void infixToPostfix()
{
    precedence stack[MAX_STACK_SIZE];
    int top = -1;

    for (int i = 0; i < infixExprLen; i++)
    {
        char *symbol = infixExpr[i];
        // precedence token;

        // (피연산자)숫자인경우 (양수거나 음수거나)
        if (isdigit(symbol[0]) || (symbol[0] == '-' && isdigit(symbol[1]))) // 피연산자라면
        {
            strcat(postfixExpr, symbol); // 피연산자를 postfixExpr에 추가
            strcat(postfixExpr, " ");    // 토큰 사이에 공백 추가
        }
        else if (strcmp(symbol, ")") == 0)
        {
            while (stack[top] != lparen)
            {
                strcat(postfixExpr, getSymbolString(stack[top--])); // 연산자를 postfixExpr에 추가
                strcat(postfixExpr, " ");                           // 토큰 사이에 공백 추가
            }
            top--; // 왼쪽 괄호 pop
        }
        else if (strcmp(symbol, "(") == 0)
        {
            stack[++top] = lparen;
        }
        else
        {
            char op = symbol[0];
            while (top >= 0 && isp[stack[top]] >= icp[getTokenFromChar(symbol[0])])
            {
                strcat(postfixExpr, getSymbolString(stack[top])); // 연산자를 postfixExpr에 추가
                strcat(postfixExpr, " ");                         // 토큰 사이에 공백 추가
                top--;
            }
            stack[++top] = getTokenFromChar(symbol[0]); // 연산자를 stack에 push
        }
    }

    while (top >= 0)
    {
        strcat(postfixExpr, getSymbolString(stack[top--])); // 연산자를 postfixExpr에 추가
        strcat(postfixExpr, " ");                           // 토큰 사이에 공백 추가
    }
}
