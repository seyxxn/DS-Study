#include <stdio.h>
#include <stdlib.h>

// 자식의 입장에서 부모는 하나임

typedef struct treeNode
{
    int data;
    struct treeNode *parent;
} treeNode;

typedef struct treeNode *treePointer;

treePointer createNode(int data)
{
    treePointer newNode = (treePointer)malloc(sizeof(treeNode));
    newNode->data = data;
    newNode->parent = NULL;

    return newNode;
}

void connectNode(treePointer p, treePointer c)
{
    c->parent = p;
}

void printParent(treePointer c)
{
    if (c->parent)
    {
        printf("null\n");
    }
    else
        printf("%d\n", c->parent->data);
}

int main()
{
    int n;
    scanf("%d", &n);
    treePointer tp[100001];

    for (int i = 0; i < n; i++)
    {
        tp[i] = createNode(i + 1);
    }

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        if (b == 1)
        {
            connectNode(tp[0], tp[a - 1]);
        }
        else
        {
            connectNode(tp[a - 1], tp[b - 1]);
        }

        printf("부모 출력 : 자식 %d 부모 ", tp[b - 1]->data);
        printParent(tp[b - 1]);
    }

    /*  for (int i = 0; i < n; i++)
    {
        printParent(tp[i]);
     } */
}