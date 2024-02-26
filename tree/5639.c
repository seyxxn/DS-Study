// 이진 검색 트리
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
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

treeNode *insert(treeNode * root, int data){
    if (root == NULL){
        return createNode(data);
    }

    if (data == root->data){
        return root;
    }

    if (data < root->data){
        root->left = insert(root->left, data);
    } else if (data > root->data){
        root->right = insert(root->right, data);
    }

    return root;
}

void postorder(treeNode *root){
    if (root != NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d\n", root->data);
    }
}

int main(){
    int data;
    treeNode *root = NULL;
    while(scanf("%d", &data) != EOF){
        root = insert(root, data);
    }
    postorder(root);
}