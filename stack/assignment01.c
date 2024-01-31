#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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

// 링크드리스트 선언
typedef struct listNode
{
    char *data;
    struct listNode *link;
} listNode;

listNode *headerInToPost;
listNode *tempInToPost;

listNode *headerInToPre;
listNode *tempInToPre;

listNode *headerInToPreReverse; // 역순으로 다시 저장해야함
listNode *tempInToPreReverse;

listNode *headerPostToIn;
listNode *tempPostToIn;

listNode *headerPost;
listNode *tempPost;

listNode *headerPreToIn;
listNode *tempPreToIn;

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

char expr[MAX_EXPR_SIZE];     // 사용자에게 표기식을 입력받는 배열 변수
Stack exprInStack;            // 사용자에게 받은 문자열을 공백 단위로 쪼개 삽입할 스택 선언
int continueCheck = 1;        // 사용자에게 입력을 계속 받는 것을 제어하는 변수
int typeCheck[3] = {0, 0, 0}; // 순서대로, 전위 중위 후위 표현법 (표현법에 해당하면 1, 해당하지 않으면 0)

// 우선순위 (, ), +, -, *, /, %, ^, eos 순서
int isp[] = {0, 17, 12, 12, 13, 13, 13, 15, 0};
int icp[] = {20, 17, 12, 12, 13, 13, 13, 15, 0};

// 중위->전위로 바꿀때는 뒤에서부터 읽기 때문에 왼쪽 괄호와 오른쪽괄호의 우선순위가 바뀐다.
int isp2[] = {17, 0, 12, 12, 13, 13, 13, 15, 0};
int icp2[] = {17, 20, 12, 12, 13, 13, 13, 15, 0};

void execute(); // 실행하는 함수 따로 뺌

void initialize(Stack *stack);       // 스택 초기화 함수
int isEmpty(Stack *stack);           // 스택이 비었는지 확인하는 함수
void push(Stack *stack, char *data); // 스택에 새로운 노드를 삽입하는 함수
char *pop(Stack *stack);             // 스택 추출 함수
char *top(Stack *stack);             // 가장 맨 위 원소 추출 함수

void getTokenToStack(char *expr, Stack *stack); // 문자열형태로 입력받은 수식을 분리하여 스택에 저장하는 함수
void printStack(Stack *stack);                  // 스택 확인용 출력 함수
int isNumber(char *str);                        //  숫자인지 아닌지 확인하는 함수
int errorCheck(Stack *stack);                   // 토큰 오입력 예외처리 함수 -> 예외처리 해야하면 1 반환, 안해도 되면 0 반환
void expressionType(Stack *stack);              // 전위인지 중위인지 후위인지 확인하는 함수

precedence getToken(Stack *stack, char *symbol); // 연산자 문자를 받아서, 열거형 precedence로 반환해주는 함수
void printToken(precedence token);               // 열거형 precedence 형태의 토근을 인자로 받아,
                                                 // 후위표기식 문자열(postfixExpr)에 연산자를 추가하는 함수
char *getSymbolString(precedence token);         // 열거형 precedence 형태의 토큰을 인자로 받아, 해당 연산자 문자를 반환하는 함수
precedence getTokenFromChar(char op);            // 연산자를 문자로 받아서, 열거형 precedence로 반환하는 함수 -> 그냥 getToken과 무슨차이?

void insertNode(listNode **header, listNode **temp, char *data); // 연결리스트에 노드를 추가하는 함수
char *deleteNode(listNode **header, listNode **temp);            // 연결리스트에서 노드를 삭제하는 함수
void printNode(listNode *header);                                // 연결리스트를 출력하는 함수

// 프로그램 주요 함수
void infixToPostfix();           // 중위표기법을 후위표기법으로 바꾸는 함수
void infixToPrefix();            // 중위표기법을 전위표기법으로 바꾸는 함수
void postfixToInfix();           // 후위표기법을 중위표기법으로 바꾸는 함수
void prefixToInfix();            // 전위표기법을 중위표기법으로 바꾸는 함수
void evalPost(listNode *header); // 후위표기식을 계산하는 함수

char *infixExpr[MAX_EXPR_SIZE] = {
    0,
};
int infixExprLen = 0;

char postexpr[MAX_EXPR_SIZE] = {
    0,
};                            // 후위표기식을 저장하는 배열 변수
char *postfixExpr = postexpr; //   후위표기식을 가리키고 있는 포인터변수

// 사용자에게 입력받은 후위표기법을 저장하는 변수
char *postfixExprOrigin[MAX_EXPR_SIZE] = {
    0,
};
int postfixExprOriginLen = 0;

// 사용자에게 입력받은 전위표기법을 저장하는 변수
char *prefixExprOrigin[MAX_STACK_SIZE] = {
    0,
};
int prefixExprOriginLen = 0;

int main(int argc, char *argv[])
{
    initialize(&exprInStack);

    if (argc == 1) // 프로그램 실행 후 수식입력 받는 경우
    {
        while (continueCheck)
        {
            // 초기화
            initialize(&exprInStack);
            typeCheck[0] = 0;
            typeCheck[1] = 0;
            typeCheck[2] = 0;

            headerInToPost = NULL;
            tempInToPost = NULL;

            headerInToPre = NULL;
            tempInToPre = NULL;
            headerInToPreReverse = NULL;
            tempInToPreReverse = NULL;

            headerPostToIn = NULL;
            tempPostToIn = NULL;

            headerPreToIn = NULL;
            tempPreToIn = NULL;

            memset(infixExpr, 0, infixExprLen);
            memset(postfixExprOrigin, 0, postfixExprOriginLen);
            memset(prefixExprOrigin, 0, prefixExprOriginLen);
            memset(postfixExpr, 0, 100);
            infixExprLen = 0;
            postfixExprOriginLen = 0;
            prefixExprOriginLen = 0;

            printf("input expression : ");
            fgets(expr, sizeof(expr), stdin);
            expr[strcspn(expr, "\n")] = '\0';

            if (strcmp(expr, "exit") == 0) // exit 입력시에 프로그램 종료
            {
                printf("exit program..\n");
                continueCheck = 0;
                return 0;
            }
            else if (expr[0] == '\0') // 엔터 입력시 다시 압력하도록
            {
                continue;
            }
            else
            {
                execute(); // 실행함수
            }
        }
    }
    else if (argc == 2) // 명령행 인자로 수식 입력받은 경우 -> 하나의 수식 분석 후에 프로그램 종료
    {
        strcpy(expr, argv[1]); // 1번째 인자로 받은 문자열을 expr에 저장
        execute();
    }

    return 0;
}

void execute()
{
    getTokenToStack(expr, &exprInStack); // 사용자에게 받은 문자열을 공백 단위로 exprInStack에 삽입

    Stack tempStack;
    initialize(&tempStack);

    while (!isEmpty(&exprInStack))
    {
        push(&tempStack, pop(&exprInStack));
    }

    while (!isEmpty(&tempStack))
    {
        char *data = pop(&tempStack);
        push(&exprInStack, data);
        infixExpr[infixExprLen++] = data;
        postfixExprOrigin[postfixExprOriginLen++] = data;
        prefixExprOrigin[prefixExprOriginLen++] = data;
    }

    /*     while (!isEmpty(&exprInStack))
        {
            char *data = pop(&exprInStack);
            printf("data : %s\n", data);
            infixExpr[infixExprLen++] = data;
            postfixExprOrigin[postfixExprOriginLen++] = data;
            prefixExprOrigin[prefixExprOriginLen++] = data;
        }
        -> 그냥 이렇게 단순하게 하면 안되는 이유 :
        배열에 저장하기 위해 while문을 돌면서 pop을 하는데 이때 이렇게 작성하면 원본인 exprInStack의 노드가 삭제되기 때문이다.
        원본유지를 위해 tempStack을 선언해서 역순으로 저장한 뒤에 pop을 하며 배열에 저장하고 exprInStack의 값은 유지된다.
    */

    if (errorCheck(&exprInStack))
    {
        printf("error : wrong token input\n");
        initialize(&exprInStack);
        return;
    }

    expressionType(&exprInStack); // 전위인지, 중위인지, 후위인지 확인하는 함수 실행

    printf("infix : "); // 중위표기식인 경우
    if (typeCheck[1])
    {
        printf("possible\n");
        printf("- IN : ");
        for (int i = 0; i < infixExprLen; i++)
            printf("%s ", infixExpr[i]);
        printf("\n");
        infixToPrefix();  // 중위표기식 -> 전위표기식 변환
        infixToPostfix(); // 중위표기식 -> 후위표기식 변환
    }
    else
    {
        printf("impossible\n");
    }

    printf("prefix : "); // 전위표기식인 경우
    if (typeCheck[0])
    {
        printf("possible\n");
        prefixToInfix(); // 전위표기식 -> 중위표기식 변환
        printf("- PR : ");
        for (int i = 0; i < prefixExprOriginLen; i++)
        {
            printf("%s ", prefixExprOrigin[i]);
        }
        printf("\n");
        infixToPostfix(); // 위에서 변환한 중위표기식 -> 후위표기식 변환
    }
    else
    {
        printf("impossible\n");
    }

    printf("postfix : "); // 후위표기식인 경우
    if (typeCheck[2])
    {
        printf("possible\n");
        postfixToInfix(); // 후위표기식 -> 중위표기식 변환
        infixToPrefix();  // 위에서 변환한 중위표기식 -> 전위표기식 변환
        printf("- PO : ");
        for (int i = 0; i < postfixExprOriginLen; i++)
        {
            printf("%s ", postfixExprOrigin[i]);
            insertNode(&headerPost, &tempPost, postfixExprOrigin[i]);
        }
        printf("\n");
    }
    else
    {
        printf("impossible\n");
    }

    // 결과 출력 -> 계산은 항상 후위표기식으로 함
    if (typeCheck[1]) // 중위표기식
    {
        evalPost(headerInToPost); // 중위->후위표기식으로 바꾼 값을 넘겨줌
    }
    else if (typeCheck[0]) // 전위표기식
    {
        evalPost(headerInToPost); // 전위->중위->후위표기식으로 바꾼 값을 넘겨줌
    }
    else if (typeCheck[2]) // 후위표기식
    {
        evalPost(headerPost); // 바로 후위표기식을 넘겨줌
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

void push(Stack *stack, char *data)
{
    Node *temp = (Node *)malloc(sizeof(Node)); // 노드 생성
    strcpy(temp->data, data);                  // 스트링 복사함수를 이용하여 data값을 temp->data에 복사
    temp->next = stack->top;                   // 노드의 다음 포인터가 stack의 top을 가리키게
    stack->top = temp;                         // 최근에 넣은 노드를 top으로 설정함(Stack의 성질)
    stack->size = stack->size + 1;
}

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

void getTokenToStack(char *expr, Stack *stack)
{
    char *ptr = strtok(expr, " \t");
    while (ptr != NULL)
    {
        push(stack, ptr);
        ptr = strtok(NULL, " ");
    }
}

void printStack(Stack *stack)
{
    for (Node *p = stack->top; p != NULL; p = p->next)
        printf("%s -> ", p->data);
    printf("NULL\n");
    printf("size : %d\n", stack->size);
}

int isNumber(char *str)
{
    int dotCnt = 0; // 소수점의 개수를 세는 변수

    if (*str == '-')
    {
        str++; // '-'를 무시하고 다음 문자로 이동
    }

    while (*str)
    {
        if (!isdigit(*str) && *str != '.') // 숫자가 아니고 소수점이 아닌 것이 들어오면 0 반환
        {
            return 0;
        }
        if (*str == '.') // 소수점이 들어오면 소수점 카운트
        {
            dotCnt++;
            if (dotCnt > 1) // 소수점이 1개보다 많으면 숫자가 아님 -> 0을 반환
                return 0;
        }
        str++;
    }
    return 1; // 모든 검사를 마쳐 숫자임을 확인하고 1을 반환
}

int errorCheck(Stack *stack)
{
    // 스택을 돌면서 연산자가 아니거나 숫자가 아니면 에러처리 (연산자와 숫자가 붙어있는 경우도 에러 처리)
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
        while (stack->size > 2) // 첫번째와 두번째 값으로 중위, 후위, 전위를 판별하기 위해 크기가 2가 될때까지 pop 한다.
            pop(stack);

        char secondData[MAX_EXPR_SIZE]; // 먼저 pop하는 것이 두번째 값이 된다.
        strcpy(secondData, pop(stack));

        char firstData[MAX_EXPR_SIZE];
        strcpy(firstData, pop(stack));

        // 이때 if 조건문의 순서도 유의해야함 !!
        // 첫번째가 괄호라면 -> 중위
        if (firstData[0] == '(')
        {
            typeCheck[1] = 1;
        }
        // 첫번째가 숫자고, 두번째가 연산자라면 -> 중위
        else if (isNumber(firstData) && strchr("+-*/%^", secondData[0]) != NULL)
        {
            typeCheck[1] = 1;
        }
        // 첫번째와 두번째 값이 모두 숫자라면 -> 후위
        else if (isNumber(firstData) && isNumber(secondData))
        {
            typeCheck[2] = 1;
        }
        // 첫번째가 연산자라면 -> 전위
        else if (strchr("+-*/%^", firstData[0]) != NULL)
        {
            typeCheck[0] = 1;
        }

        return;
    }
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

void insertNode(listNode **header, listNode **temp, char *data)
{
    listNode *newNode = (listNode *)malloc(sizeof(listNode));
    newNode->data = strdup(data);

    if (*header == NULL)
    {
        newNode->link = NULL;
        *header = newNode;
        *temp = newNode;
    }
    else
    {
        newNode->link = NULL;
        (*temp)->link = newNode;
        *temp = newNode;
    }
}

char *deleteNode(listNode **header, listNode **temp)
{
    char *data;
    if (*header == NULL)
    {
        printf("Node is empty");
        return NULL;
    }

    listNode *cur = *header;
    listNode *pre = NULL;

    while (cur->link != NULL)
    {
        pre = cur;
        cur = cur->link;
    }

    data = strdup(cur->data);

    if (pre == NULL) // 노드가 하나 남은 경우
    {
        free(*header);
        *header = NULL;
        *temp = NULL;
    }
    else
    {
        pre->link = NULL;
        *temp = pre;
        free(cur);
    }

    return data;
}

void printNode(listNode *header)
{
    listNode *p = header;
    while (p != NULL)
    {
        printf("%s ", p->data);
        p = p->link;
    }
    printf("\n");
}

void infixToPostfix() // 중위표기법 -> 후위표기법
{
    precedence stack[MAX_STACK_SIZE];
    int top = -1;

    headerInToPost = NULL;
    tempInToPost = NULL;

    for (int i = 0; i < infixExprLen; i++)
    {
        char *symbol = infixExpr[i]; // 중위표기법을 하나씩 읽어옴 (문자열로)

        // (피연산자)숫자인경우 (양수거나 음수거나) -> 노드에 삽입
        if (isdigit(symbol[0]) || (symbol[0] == '-' && isdigit(symbol[1]))) // 피연산자라면
        {
            insertNode(&headerInToPost, &tempInToPost, symbol);
        }
        else if (strcmp(symbol, ")") == 0) // 오른쪽 괄호일때
        {
            while (stack[top] != lparen) // 왼쪽 괄호 나올때까지 pop
            {
                insertNode(&headerInToPost, &tempInToPost, getSymbolString(stack[top--]));
            }
            top--; // 왼쪽 괄호 pop
        }
        else if (strcmp(symbol, "(") == 0) // 왼쪽 괄호일 때
        {
            stack[++top] = lparen; // 스택에 넣기
        }
        else // 연산자인 경우
        {
            char op = symbol[0];                                             // 연산자를 char 문자에 담음 (무조건 1글자라서)
            while (top >= 0 && isp[stack[top]] >= icp[getTokenFromChar(op)]) // 스택에 있는 연산자의 우선순위보다 넣으려고 하는 연산자의 우선순위가 높아질때까지 반복문
            {
                insertNode(&headerInToPost, &tempInToPost, getSymbolString(stack[top])); // stack에 있는 것을 하나씩 꺼내서 노드에 삽입
                top--; // stack에서 꺼내니까 top--;
            }
            stack[++top] = getTokenFromChar(symbol[0]); // 연산자(넣으려고 하는 연산자)를 stack에 push
        }
    }

    while (top >= 0) // 위의 과정이 끝나고, 아직 stack에 연산자가 남아있다면 pop하여 노드에 삽입함
    {
        insertNode(&headerInToPost, &tempInToPost, getSymbolString(stack[top--]));
    }

    printf("- PO : ");
    printNode(headerInToPost);
}

void infixToPrefix() // 중위표기법 -> 전위표기법
{
    precedence stack[MAX_STACK_SIZE];
    int top = -1;

    headerInToPre = NULL;
    tempInToPre = NULL;

    // 배열에 저장된 중위표기법을 뒤에서부터 읽어야함
    // 주위 ) 뒤에서부터 읽기 때문에 오른쪽 괄호가 왼쪽 괄호보다 먼저 읽힘 -> 따라서 우선순위도 달라짐 (isp2, icp2 사용)
    for (int i = infixExprLen - 1; i >= 0; i--)
    {
        char *symbol = infixExpr[i]; // symbol로 뒤에서부터 읽어온다.

        // 피연산자인 경우 (양수거나 음수거나)
        if (isdigit(symbol[0]) || (symbol[0] == '-' && isdigit(symbol[1])))
        {
            insertNode(&headerInToPre, &tempInToPre, symbol); // 바로 연결리스트에 넣음
        }
        else if (strcmp(symbol, ")") == 0) // 오른쪽 괄호라면
        {
            stack[++top] = rparen; // 스택에 넣음
        }
        else if (strcmp(symbol, "(") == 0) // 왼쪽 괄호라면
        {
            while (stack[top] != rparen) // 오른쪽 괄호가 나올 때 까지 연결리스트에 넣음
            {
                insertNode(&headerInToPre, &tempInToPre, getSymbolString(stack[top--]));
            }
            top--;
        }
        else
        {
            char op = symbol[0];
            while (top >= 0 && isp2[stack[top]] > icp2[getTokenFromChar(op)])
            {
                insertNode(&headerInToPre, &tempInToPre, getSymbolString(stack[top--]));
            }
            stack[++top] = getTokenFromChar(op);
        }
    }

    while (top >= 0)
    {
        insertNode(&headerInToPre, &tempInToPre, getSymbolString(stack[top--]));
    }
    // 이런 과정을 거치고 나면, 예를 들어 2 + 3 인 중위식이 있을 때, 3부터 읽어서 headerInToPre가 가리키는 연결리스트에는 3 2 + 이렇게 저장됨
    // 즉, 완벽한 전위식은 3 2 + 의 역순인 + 2 3 를 저장하고 있어야함. 따라서 역순을 저장하는 연결리스트를 더 선언해야하고 headerInToPre를 뒤에서부터 pop하면서 저장한다.

    headerInToPreReverse = NULL;
    tempInToPreReverse = NULL;

    listNode *p = headerInToPre;

    while (headerInToPre != NULL)
    {
        char *data = deleteNode(&headerInToPre, &tempInToPre);
        insertNode(&headerInToPreReverse, &tempInToPreReverse, data);
        free(data);
    }

    printf("- PR : ");
    printNode(headerInToPreReverse);
}

void postfixToInfix() // 후위표기법 -> 중위 표기법
{
    headerPostToIn = NULL;
    tempPostToIn = NULL;

    for (int i = 0; i <= postfixExprOriginLen - 1; i++)
    {
        char *symbol = postfixExprOrigin[i];
        // 숫자라면 -> 연결리스트에 새로운 노드로 삽입
        if (isdigit(symbol[0]) || (symbol[0] == '-' && isdigit(symbol[1])))
        {
            insertNode(&headerPostToIn, &tempPostToIn, symbol);
        }
        else // 연산자라면 피연산자 2개를 pop하여 가져옴
        {
            char *op2 = deleteNode(&headerPostToIn, &tempPostToIn); 
            char *op1 = deleteNode(&headerPostToIn, &tempPostToIn);

            char *temp = malloc(sizeof(char) * 100);
            temp[0] = '\0';

            if (i == postfixExprOriginLen - 1)
            {
                strcat(temp, op1);
                strcat(temp, " ");
                strcat(temp, symbol);
                strcat(temp, " ");
                strcat(temp, op2);
            }
            else
            {
                strcat(temp, "(");
                strcat(temp, " ");

                strcat(temp, op1);
                strcat(temp, " ");

                strcat(temp, symbol);
                strcat(temp, " ");

                strcat(temp, op2);
                strcat(temp, " ");

                strcat(temp, ")");
            }

            insertNode(&headerPostToIn, &tempPostToIn, temp);
        }
    }

    printf("- IN : ");
    printNode(headerPostToIn);

    // insertExpr에 넣기
    // 초기화
    memset(infixExpr, 0, infixExprLen);
    infixExprLen = 0;

    listNode *p = headerPostToIn;
    for (int i = 0; p != NULL; i++)
    {
        char *data = p->data;
        char *token = strtok(data, " ");

        while (token != NULL)
        {
            infixExpr[infixExprLen] = strdup(token);
            infixExprLen++;

            token = strtok(NULL, " ");
        }

        p = p->link;
    }
}

void prefixToInfix() // 전위표기법 -> 중위표기법
{
    headerPreToIn = NULL;
    tempPreToIn = NULL;
    // 저장된 전위표기법을 역순으로 읽어야함
    for (int i = prefixExprOriginLen - 1; i >= 0; i--)
    {
        char *symbol = prefixExprOrigin[i];
        // 피연산자인 경우 (양수거나 음수거나)
        if (isdigit(symbol[0]) || (symbol[0] == '-' && isdigit(symbol[1])))
        {
            insertNode(&headerPreToIn, &tempPreToIn, symbol); // 바로 연결리스트에 넣음
        }
        else // 연산자인 경우
        {
            char *op1 = deleteNode(&headerPreToIn, &tempPreToIn);
            char *op2 = deleteNode(&headerPreToIn, &tempPreToIn);

            char *temp = malloc(sizeof(char) * 100);
            temp[0] = '\0';

            if (i == 0)
            {
                strcat(temp, op1);
                strcat(temp, " ");
                strcat(temp, symbol);
                strcat(temp, " ");
                strcat(temp, op2);
            }
            else
            {
                strcat(temp, "(");
                strcat(temp, " ");

                strcat(temp, op1);
                strcat(temp, " ");

                strcat(temp, symbol);
                strcat(temp, " ");

                strcat(temp, op2);
                strcat(temp, " ");

                strcat(temp, ")");
            }

            insertNode(&headerPreToIn, &tempPreToIn, temp);
        }
    }

    printf("- IN : ");
    printNode(headerPreToIn);

    // insertExpr에 넣기
    // 초기화
    memset(infixExpr, 0, infixExprLen);
    infixExprLen = 0;

    listNode *p = headerPreToIn;
    for (int i = 0; p != NULL; i++)
    {
        char *data = p->data;
        char *token = strtok(data, " ");

        while (token != NULL)
        {
            infixExpr[infixExprLen] = strdup(token);
            infixExprLen++;

            token = strtok(NULL, " ");
        }

        p = p->link;
    }
}

void evalPost(listNode *header)
{
    float result = 0;               // 결과값을 저장할 변수
    listNode *p = header;           // headerInToPost가 가리키는 연결리스트에 지금 후위표기식이 저장되어있는 상태
    listNode *evalPostStack = NULL; // 후위표기식 계산에 필요한 스택을 가리키는 변수 선언
    listNode *evalPostTemp = NULL;  // 후위표기식 계산에 필요한 temp 변수 선언
    char *op1, op2;
    char resultChar[100];

    if (p->link == NULL)
    { // 입력이 하나일 때 -> segmentfault 해결 미완
        printf("\nresult : %s\n", p->data);
        return;
    }

    while (p != NULL)
    {
        // 피연산자인경우 (숫자인경우) -> 스택에 삽입한다.
        if (isdigit((p->data)[0]) || ((p->data)[0] == '-' && isdigit((p->data)[1])))
        {
            insertNode(&evalPostStack, &evalPostTemp, p->data);
        }
        else // 연산자인 경우
        {
            char *op2 = deleteNode(&evalPostStack, &evalPostTemp);
            char *op1 = deleteNode(&evalPostStack, &evalPostTemp);

            float op2float = atof(op2); // 문자열로 받아온 값들을 정수형으로 변환 -> 계산을 해야해서
            float op1float = atof(op1);

            char opType = (p->data)[0]; // 연산자를 받을 변수
            switch (opType)             // 연산자에 따라 계산을 하고 결과 값을 받음
            {
            case '+':
                result = op1float + op2float;
                break;
            case '-':
                result = op1float - op2float;
                break;
            case '*':
                result = op1float * op2float;
                break;
            case '/':
                result = op1float / op2float;
                if (op2float == 0)
                {
                    printf("\nresult : Arithmetic error(cannot devide by zero)\n");
                    return;
                }
                break;
            case '%':
                result = (int)op1float % (int)op2float;
                break;
            case '^':
                result = pow((double)op1float, (double)op2float);
                break;
            default:
                break;
            }

            sprintf(resultChar, "%f", result);

            insertNode(&evalPostStack, &evalPostTemp, resultChar);
        }

        p = p->link;
    }

    printf("\nresult : %f\n", result);
}