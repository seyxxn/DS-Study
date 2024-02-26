// 이진 탐색 트리 예제 프로그램
#include <stdio.h>
#include <stdlib.h>

// 이진 탐색 트리 노드 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode *left; // 왼쪽 자식
    struct TreeNode *right; // 오른쪽 자식
} treeNode;

// 새 노드 삽입 함수
treeNode *createNode(int data){
    treeNode *newNode = (treeNode *)malloc(sizeof(treeNode)); // 동적할당

    // 초기화
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// 이진 탐색 트리에서 가장 작은 값을 가지는 노드를 찾는 함수
// 가장 왼쪽에 있는 값이 가장 작은 값임 (이진 탐색 트리의 특징에 의해)
treeNode *findMin(treeNode *node){
    while(node->left != NULL){
        node = node->left;
    }
    return node;
}

// 이진 탐색 트리에 노드를 삽입하는 함수
treeNode *insert(treeNode *root, int data){
    if (root == NULL){ // 빈 트리인 경우
        return createNode(data);
    }

    // 넣으려는 값 < 현재 루트 노드의 값 -> 왼쪽으로 가야함
    if (data < root->data){
        root->left = insert(root->left, data);
    }
    // 넣으려는 값 > 현재 루트 노드의 값 -> 오른쪽으로 가야함
    else if (data > root->data){
        root->right = insert(root->right, data);
    }
    return root;
}

// 이진 탐색 트리에서 노드 삭제 함수
treeNode *deleteNode(treeNode *root, int key){
    //  빈 트리인 경우
    if (root == NULL){
        return root;
    }
    // 삭제할 노드를 찾는 과정
    if (key < root->data){ // 삭제하려는 값 < 루트 노드의 값 -> 왼쪾으로 가야함
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data){ // 삭제하려는 값 > 루트 노드의 값 -> 오른쪽으로 가야함
        root->right = deleteNode(root->right, key);
    }
    else {
        // 삭제할 노드를 찾았을 때
        // CASE 1 : 리프노드인 경우(자식이 없는 경우)
        if (root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
        }
        // CASE 2 : 하나의 자식 노드를 가지는 경우
        else if (root->left == NULL){
            // 오른쪽 자식 노드만 가진 경우
            treeNode *temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL){
            // 왼쪽 자식 노드만 가진 경우
            treeNode *temp = root;
            root = root->left;
            free(temp);
        }
        // CASE 3 : 두 개의 자식 노드를 가지는 경우
        else {
            // 오른쪽 서브 트리에서 가장 작은 값을 가진 노드를 찾음
            treeNode *temp = findMin(root->right);
            // 찾은 노드의 값을 삭제할 노드로 복사
            root->data = temp->data;
            // 오른쪽 서브 트리에서 복사한 값을 가진 노드를 삭제
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

// 이진 탐색 트리를 중위 순회하여 툴력하는 함수
// 이진 탐색 트리를 중휘 순회하면 정렬된 순서로 출력된다. (오름차순)
void inorder(treeNode *root){
    if (root != NULL){
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main(){
    treeNode *root = NULL;
    // 이진 탐색트리에 노드를 삽입
    root = insert(root, 12);
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 25);
    root = insert(root, 22);

    // 초기 출력
    printf("Inorder Traversal (Original Tree) : ");
    inorder(root);
    printf("\n");

    // 노드 삭제
    int keyToDelete = 20;
    root = deleteNode(root, keyToDelete);
    
    // 노드 삭제 후 출력
    printf("Inorder Traversal (After Deleting %d) : ", keyToDelete);
    inorder(root);
    printf("\n");

    // 노드 추가
    int keyToInsert = 30;
    root = insert(root, keyToInsert);

    // 노드 추가 후 출력
    printf("Inorder Traversal (After Inserting %d) : ", keyToInsert);
    inorder(root);
    printf("\n");

    // 중위 순회를 통해 트리의 내용을 출력한다.

    return 0;
    
}



