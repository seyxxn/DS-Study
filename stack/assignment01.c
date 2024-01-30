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
    Node *top; // ������ top�� ��Ÿ���� ������
    int size;
} Stack;

// ��ũ�帮��Ʈ ����
typedef struct listNode
{
    char *data;
    struct listNode *link;
} listNode;

listNode *headerInToPost;
listNode *tempInToPost;

listNode *headerInToPre;
listNode *tempInToPre;

listNode *headerInToPreReverse; // �������� �ٽ� �����ؾ���
listNode *tempInToPreReverse;

typedef enum _precedence
{
    lparen,
    rparen,
    plus,
    minus,
    times,
    divide,
    mod,
    power, // ^ (����)
    eos,
    operand
} precedence;

char expr[MAX_EXPR_SIZE];      // ����ڿ��� ǥ����� �Է¹޴� ����
char exprToken[MAX_EXPR_SIZE]; // ����ڿ��� ǥ����� �Է¹޾� ��ū�� �����Ͽ� ����
Stack exprInStack;             // ����ڿ��� ���� ���ڿ��� ������ ���� ����
Stack exprInStackOrigin;       // ����ڿ��� ���� ���ڿ��� ������ ���� -> ��ȸ�ϱ� ���� ���� ����
int continueCheck = 1;         // ����ڿ��� �Է��� ��� �޴� ���� �����ϴ� ����
int typeCheck[3] = {0, 0, 0};  // �������, ���� ���� ���� ǥ���� (ǥ������ �ش��ϸ� 1, �ش����� ������ 0)
                               // -> ���� �ٲ� �� ���� �ʱ�ȭ �ʿ�

// �켱����
// (, ), +, -, *, /, %, ^, eos ����
int isp[] = {0, 17, 12, 12, 13, 13, 13, 15, 0};
int icp[] = {20, 17, 12, 12, 13, 13, 13, 15, 0};

// ����->������ �ٲܶ��� �ڿ������� �б� ������ ���� ��ȣ�� �����ʰ�ȣ�� �켱������ �ٲ��.
int isp2[] = {17, 0, 12, 12, 13, 13, 13, 15, 0};
int icp2[] = {17, 20, 12, 12, 13, 13, 13, 15, 0};

void execute(); // �����ϴ� �Լ� ���� ��

void initialize(Stack *stack);       // ���� �ʱ�ȭ �Լ�
int isEmpty(Stack *stack);           // ������ ������� Ȯ���ϴ� �Լ�
void push(Stack *stack, char *data); // ���ÿ� ���ο� ��带 �����ϴ� �Լ�
char *pop(Stack *stack);             // ���� ���� �Լ�
char *top(Stack *stack);             // ���� �� �� ���� ���� �Լ�

void getTokenToStack(char *expr, Stack *stack); // ���ڿ����·� �Է¹��� ������ �и��Ͽ� ���ÿ� �����ؾ���
void printStack(Stack *stack);                  // ���� Ȯ�ο� ��� �Լ�
int isNumber(char *str);                        //  �������� �ƴ��� Ȯ���ϴ� �Լ�
int errorCheck(Stack *stack);                   // ��ū ���Է� ����ó�� �Լ�
void expressionType(Stack *stack);              // �������� �������� �������� Ȯ���ϴ� �Լ�

// ����-> ����, ����->����, ����->����, ���� ->���� (��ȯ�Լ� 4�� �ʿ�)
// ������ ����ϴ� �Լ� �ʿ� -> evalPost();

void printToken(precedence token); // ����� �ε����� ���ڷ� �޾�, ����ǥ��� ���ڿ��� ���ڸ� �߰��ϴ� �Լ�
precedence getToken(Stack *stack, char *symbol);
void infixToPostfix(); // ����->����

void expressionPush(Stack *stack, precedence item);
precedence expresstionPop(Stack *stack);

void insertNode(listNode **header, listNode **temp, char *data); // ���Ḯ��Ʈ�� ��带 �߰��ϴ� �Լ�
char *deleteNode(listNode **header, listNode **temp);            // ���Ḯ��Ʈ���� ��带 �����ϴ� �Լ�
void printNode(listNode *header);                                // ���Ḯ��Ʈ�� ����ϴ� �Լ�
void infixToPostfix();                                           // ����ǥ����� ����ǥ������� �ٲٴ� �Լ�
void evalPost();                                                  // ����ǥ����� ����ϴ� �Լ�

void infixToPrefix();  // ����ǥ����� ����ǥ������� �ٲٴ� �Լ�
void postfixToInfix(); // ����ǥ����� ����ǥ������� �ٲٴ� �Լ�
void prefixToInfix();  // ����ǥ����� ����ǥ������� �ٲٴ� �Լ�

char *infixExpr[MAX_EXPR_SIZE] = {
    0,
};
int infixExprLen = 0;
char postexpr[MAX_EXPR_SIZE] = {
    0,
};                            // ����ǥ����� �����ϴ� �迭 ����
char *postfixExpr = postexpr; //   ����ǥ����� ����Ű�� �ִ� �����ͺ���

int main(int argc, char *argv[])
{
    initialize(&exprInStack);
    initialize(&exprInStackOrigin);

    if (argc == 1) // ���α׷� ���� �� �����Է� �޴� ���
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
            // stack�� �ʱ�ȭ
            initialize(&exprInStack);
            typeCheck[0] = 0;
            typeCheck[1] = 0;
            typeCheck[2] = 0;
        }
    }
    else if (argc == 2) // ����� ���ڷ� ���� �Է¹��� ��� -> �ϳ��� ���� �м� �Ŀ� ���α׷� ����
    {
        strcpy(expr, argv[1]);
        execute();
    }

    return 0;
}

// �����Լ�
void execute()
{
    getTokenToStack(expr, &exprInStack);
    // ���ο� ������ ���� exprInStack�� ������ ����
    Stack tempStack;
    initialize(&tempStack);

    while (!isEmpty(&exprInStack))
    {
        push(&tempStack, pop(&exprInStack));
    }

    // tempStack�� ������ exprInStack�� exprInStackOrigin�� ����
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
    printf("infix : "); // ����ǥ����� ���
    if (typeCheck[1])
    {
        printf("possible\n");
        printf("IN : ");
        for (int i = 0; i < infixExprLen; i++)
            printf("%s ", infixExpr[i]);
        printf("\n");
        infixToPrefix();
        infixToPostfix();
        evalPost();

        headerInToPost = NULL;
        tempInToPost = NULL;

        headerInToPre = NULL;
        tempInToPre = NULL;
        headerInToPreReverse = NULL;
        tempInToPreReverse = NULL;

        // �ʱ�ȭ
        memset(infixExpr, 0, infixExprLen);
        memset(postfixExpr, 0, 100);
        infixExprLen = 0;
    }
    else
    {
        printf("impossible\n");
    }

    printf("prefix : "); // ����ǥ����� ���
    if (typeCheck[0])
    {
        printf("possible\n");
    }
    else
    {
        printf("impossible\n");
    }

    printf("postfix : "); // ����ǥ����� ���
    if (typeCheck[2])
    {
        printf("possible\n");
        postfixToInfix();
        evalPost();
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

// ���ÿ� ���ο� ��带 �����ϴ� �Լ�
void push(Stack *stack, char *data)
{
    Node *temp = (Node *)malloc(sizeof(Node)); // ��� ����
    strcpy(temp->data, data);                  // ��Ʈ�� �����Լ��� �̿��Ͽ� data���� temp->data�� ����
    temp->next = stack->top;                   // ����� ���� �����Ͱ� stack�� top�� ����Ű��
    stack->top = temp;                         // �ֱٿ� ���� ��带 top���� ������(Stack�� ����)
    stack->size = stack->size + 1;
}

// top�� ���ÿ��� �����ϰ� ��ȯ�ϴ� �Լ�
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

// ���ڿ��� ��ū���� �ɰ��� ���ÿ� push�ϴ� �Լ�
void getTokenToStack(char *expr, Stack *stack)
{
    char *ptr = strtok(expr, " \t");
    while (ptr != NULL)
    {
        push(stack, ptr);
        ptr = strtok(NULL, " ");
    }
}

// ���� ����ϴ� �Լ�
void printStack(Stack *stack)
{
    for (Node *p = stack->top; p != NULL; p = p->next)
        printf("%s -> ", p->data);
    printf("NULL\n");
    printf("size : %d\n", stack->size);
}

// ���ڿ��� ���ڰ� �´��� Ȯ���ϴ� �Լ�
int isNumber(char *str)
{
    int dotCnt = 0; // �Ҽ����� ������ ���� ����

    if (*str == '-')
    {
        str++; // '-'�� �����ϰ� ���� ���ڷ� �̵�
    }

    while (*str)
    {
        if (!isdigit(*str) && *str != '.')
        // ���ڰ� �ƴϰ� �Ҽ����� �ƴ� ���� ������ 0 ��ȯ
        {
            return 0;
        }
        // �Ҽ����� ������ �Ǹ� �Ҽ��� ī��Ʈ
        if (*str == '.')
        {
            dotCnt++;
            if (dotCnt > 1) // �Ҽ����� 1������ ������ ���ڰ� �ƴ� -> 0�� ��ȯ
                return 0;
        }
        str++;
    }
    return 1; // ��� �˻縦 ���� �������� Ȯ���ϰ� 1�� ��ȯ
}

// ��ū ���Է� ����ó�� �Լ�-> ���� ó���ؾ��ϸ� 1�� ��ȯ, ����ó�� ���ص� �Ǹ� 0�� ��ȯ
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

// �������� �������� �������� Ȯ���ϴ� �Լ�
// typeCheck �迭 ������ ������
void expressionType(Stack *stack)
{
    if (stack->size == 1) // stack�� ũ�Ⱑ 1�϶�
    {
        if (isdigit(top(stack)[0])) // �װ� ������ ���
        {
            typeCheck[0] = 1;
            typeCheck[1] = 1;
            typeCheck[2] = 1;
            return;
        }
        else
        {                                        // ���ڰ� �ƴѰ��
            printf("error : input is single\n"); // ���Ƿ� ����ó�� (������ ����)
            return;
        }
    }
    else if (stack->size == 2) // stack�� ũ�Ⱑ 2�϶�
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

        //  ù��°�� ��ȣ��� -> ����
        if (firstData[0] == '(')
        {
            typeCheck[1] = 1;
            // printf("first : %s secod : %s \n", firstData, secondData);
        }
        // ù��°�� �����ڶ�� -> ����
        else if (strchr("+-*/%^", firstData[0]) != NULL)
        {
            typeCheck[0] = 1;
            // printf("first : %s secod : %s \n", firstData, secondData);
        }
        // ù��°�� ���ڰ�, �ι�°�� �����ڶ�� -> ����
        else if (isNumber(firstData) && strchr("+-*/%^", secondData[0]) != NULL)
        {
            typeCheck[1] = 1;
            // printf("first : %s secod : %s \n", firstData, secondData);
        }
        // ù��°�� �ι�° ���� ��� ���ڶ�� -> ����
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

    if (pre == NULL) // ��尡 �ϳ� ���� ���
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

void infixToPostfix()
{
    precedence stack[MAX_STACK_SIZE];
    int top = -1;

    for (int i = 0; i < infixExprLen; i++)
    {
        char *symbol = infixExpr[i];

        // (�ǿ�����)�����ΰ�� (����ų� �����ų�)
        if (isdigit(symbol[0]) || (symbol[0] == '-' && isdigit(symbol[1]))) // �ǿ����ڶ��
        {
            insertNode(&headerInToPost, &tempInToPost, symbol);
        }
        else if (strcmp(symbol, ")") == 0) // ������ ��ȣ�϶�
        {
            while (stack[top] != lparen)
            {
                insertNode(&headerInToPost, &tempInToPost, getSymbolString(stack[top--]));
            }
            top--; // ���� ��ȣ pop
        }
        else if (strcmp(symbol, "(") == 0) // ���� ��ȣ�� ��
        {
            stack[++top] = lparen;
        }
        else // �������� ���
        {
            char op = symbol[0];
            while (top >= 0 && isp[stack[top]] >= icp[getTokenFromChar(op)])
            {
                insertNode(&headerInToPost, &tempInToPost, getSymbolString(stack[top]));
                top--;
            }
            stack[++top] = getTokenFromChar(symbol[0]); // �����ڸ� stack�� push
        }
    }

    while (top >= 0)
    {
        insertNode(&headerInToPost, &tempInToPost, getSymbolString(stack[top--]));
    }
    printf("PO : ");
    printNode(headerInToPost);
}

void evalPost()
{
    int result = 0;                 // ������� ������ ����
    listNode *p = headerInToPost;   // headerInToPost�� ����Ű�� ���Ḯ��Ʈ�� ���� ����ǥ����� ����Ǿ��ִ� ����
    listNode *evalPostStack = NULL; // ����ǥ��� ��꿡 �ʿ��� ������ ����Ű�� ���� ����
    listNode *evalPostTemp = NULL;  // ����ǥ��� ��꿡 �ʿ��� temp ���� ����
    char *op1, op2;
    char resultChar[100];

    if(p->link == NULL){ // �Է��� �ϳ��� �� -> segmentfault �ذ� �̿�
        printf("result : %s\n", p->data);
        return ;
    }

    while (p != NULL)
    {
        // �ǿ������ΰ�� (�����ΰ��) -> ���ÿ� �����Ѵ�.
        if (isdigit((p->data)[0]) || ((p->data)[0] == '-' && isdigit((p->data)[1])))
        {
            insertNode(&evalPostStack, &evalPostTemp, p->data);
            // rintf("Number case, \n");
            // printNode(evalPostStack);
        }
        else // �������� ���
        {
            char *op2 = deleteNode(&evalPostStack, &evalPostTemp);
            char *op1 = deleteNode(&evalPostStack, &evalPostTemp);

            // printf("After pop, \n");
            // printNode(evalPostStack);

            int op2int = atoi(op2); // ���ڿ��� �޾ƿ� ������ ���������� ��ȯ -> ����� �ؾ��ؼ�
            int op1int = atoi(op1);

            char opType = (p->data)[0]; // �����ڸ� ���� ����
            switch (opType)             // �����ڿ� ���� ����� �ϰ� ��� ���� ����
            {
            case '+':
                result = op1int + op2int;
                break;
            case '-':
                result = op1int - op2int;
                break;
            case '*':
                result = op1int * op2int;
                break;
            case '/':
                result = op1int / op2int;
                if (op1int == 0 || op2int == 0)
                {
                    printf("\nresult : Arithmetic error(cannot devide by zero)\n");
                }
                break;
            case '%':
                result = op1int % op2int;
                break;
            case '^':
                result = pow((double)op1int, (double)op2int);
                break;
            default:
                break;
            }

            // printf("op1 : %d, op2 : %d, result : %f \n", op1int, op2int, result);

            sprintf(resultChar, "%d", result);
            // printf("resultChar : %s \n", resultChar);

            insertNode(&evalPostStack, &evalPostTemp, resultChar);

            // printf("after result insert, \n");
            // printNode(evalPostStack);
        }

        p = p->link;
    }

    printf("\nresult : %d\n", result);
}

// ����ǥ����� ����ǥ������� �ٲٴ� �Լ�
void infixToPrefix()
{
    precedence stack[MAX_STACK_SIZE];
    int top = -1;

    // �迭�� ����� ����ǥ����� �ڿ������� �о����
    // ���� ) �ڿ������� �б� ������ ������ ��ȣ�� ���� ��ȣ���� ���� ����
    for (int i = infixExprLen - 1; i >= 0; i--)
    {
        char *symbol = infixExpr[i];

        // �ǿ������� ��� (����ų� �����ų�)
        if (isdigit(symbol[0]) || (symbol[0] == '-' && isdigit(symbol[1])))
        {
            insertNode(&headerInToPre, &tempInToPre, symbol); // �ٷ� ���Ḯ��Ʈ�� ����
        }
        else if (strcmp(symbol, ")") == 0) // ������ ��ȣ���
        {
            stack[++top] = rparen; // ���ÿ� ����
        }
        else if (strcmp(symbol, "(") == 0) // ���� ��ȣ���
        {
            while (stack[top] != rparen) // ������ ��ȣ�� ���� �� ���� ���Ḯ��Ʈ�� ����
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

    headerInToPreReverse = NULL;
    tempInToPreReverse = NULL;

    listNode *p = headerInToPre;

    while (headerInToPre != NULL)
    {
        char *data = deleteNode(&headerInToPre, &tempInToPre);
        insertNode(&headerInToPreReverse, &tempInToPreReverse, data);
        free(data);
    }

    printf("PR : ");
    printNode(headerInToPreReverse);
}

// ����ǥ����� ����ǥ������� �ٲٴ� �Լ�
void postfixToInfix()
{
}

// ����ǥ����� ����ǥ������� �ٲٴ� �Լ�
void prefixToInfix()
{
}