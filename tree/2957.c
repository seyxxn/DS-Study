#include <stdio.h>
#include <stdlib.h>
int n;
typedef struct treeNode{
    int data;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

treeNode *createNode(int data){
    treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

treeNode* insert(int num, treeNode *root, int *count){
    if (root == NULL){
        return createNode(num);
    }

    (*count)++;
    if (num < root->data){
        if (root->left == NULL){
            root->left = createNode(num);
        }else {
            root->left = insert(num, root->left, count);
        }
    } else {
        if (root->right == NULL){
            root->right = createNode(num);
        }else {
            root->right = insert(num, root->right, count);
        }
    }
    return root;
}

int main(){
    treeNode *root = NULL;
    int count = 0;

    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        int num;
        scanf("%d", &num);
        root = insert(num, root, &count);
        printf("%d\n", count);
    }

    return 0;
}