// 수식 A*B-C/D 에 대한 이진 트리를 연결 자료구조를 사용하여 생성하고,
// 전위, 중위 및 후위 순회하는 예제 프로그램

#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode
{
    char data;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

typedef struct treeNode *treePointer;

treePointer makeRootNode(char data, treePointer leftNode, treePointer rightNode)
{
    treePointer root = (treePointer)malloc(sizeof(treeNode));
    root->data = data;
    root->left = leftNode;
    root->right = rightNode;
    return root;
}

void preorder(treePointer root)
{
    if (root)
    {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(treePointer root)
{
    if (root)
    {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
}

void postorder(treePointer root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}

int main(int argc, char *argv[])
{
    treePointer n7 = makeRootNode('D', NULL, NULL);
    treePointer n6 = makeRootNode('C', NULL, NULL);
    treePointer n5 = makeRootNode('B', NULL, NULL);
    treePointer n4 = makeRootNode('A', NULL, NULL);
    treePointer n3 = makeRootNode('/', n6, n7);
    treePointer n2 = makeRootNode('*', n4, n5);
    treePointer n1 = makeRootNode('-', n2, n3);

    printf("\npreorder : ");
    preorder(n1);

    printf("\ninorder : ");
    inorder(n1);

    printf("\npostorder : ");
    postorder(n1);
}