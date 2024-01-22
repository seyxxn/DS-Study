#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode
{
    char data;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

typedef struct treeNode *treePointer;

treePointer createNode(char data, treePointer leftNode, treePointer rightNode)
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
        printf("%c", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(treePointer root)
{
    if (root)
    {
        inorder(root->left);
        printf("%c", root->data);
        inorder(root->right);
    }
}

void postorder(treePointer root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%c", root->data);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    treePointer root;

    while (n--)
    {
        char node, l, r;
        scanf(" %c %c %c", &node, &l, &r);

        treePointer leftNode  = (l == '.') ? NULL : createNode(l, NULL, NULL);
        treePointer rightNode = (r == '.') ? NULL : createNode(r, NULL, NULL);

        if (root == NULL)
        {
            root = createNode(node, leftNode, rightNode);
        }
        else
        {
            treePointer temp = createNode(node, leftNode, rightNode);
        }
    }

    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
}