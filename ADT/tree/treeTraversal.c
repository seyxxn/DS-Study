// 트리 순회
// https://yoongrammer.tistory.com/70 참고

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
void inorder(treePointer root)
{
    if (root)
    {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
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
    treePointer n11 = makeRootNode('K', NULL, NULL);
    treePointer n10 = makeRootNode('J', NULL, NULL);
    treePointer n9 = makeRootNode('I', NULL, NULL);
    treePointer n8 = makeRootNode('H', NULL, NULL);
    treePointer n7 = makeRootNode('G', NULL, n11);
    treePointer n6 = makeRootNode('F', NULL, NULL);
    treePointer n5 = makeRootNode('E', n9, n10);
    treePointer n4 = makeRootNode('D', n8, NULL);
    treePointer n3 = makeRootNode('C', n6, n7);
    treePointer n2 = makeRootNode('B', n4, n5);
    treePointer n1 = makeRootNode('A', n2, n3);

    printf("preorder (전위순회) : ");
    preorder(n1);

    printf("\ninorder (중위순회) : ");
    inorder(n1);

    printf("\npostorder (후위순회) : ");
    postorder(n1);
}