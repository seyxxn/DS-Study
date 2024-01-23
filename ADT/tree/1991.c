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

// 노드의 데이터 값을 받아, 노드를 생성해주는 함수
treePointer createNode(char data)
{
    treePointer root = (treePointer)malloc(sizeof(treeNode));
    root->data = data;
    root->left = NULL;
    root->right = NULL;

    return root;
}

// 노드 왼쪽 연결, 오른쪽 연결하는 함수
void connectNode(treePointer root, treePointer leftNode, treePointer rightNode)
{
    root->left = leftNode;
    root->right = rightNode;
}

// 전위 순회
void preorder(treePointer root)
{
    if (root)
    {
        printf("%c", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// 중위 순회
void inorder(treePointer root)
{
    if (root)
    {
        inorder(root->left);
        printf("%c", root->data);
        inorder(root->right);
    }
}

// 후위 순회
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
    scanf("%d", &n);    // 노드의 개수 입력받기
    treePointer tp[26]; // 이진트리 노드 최대의 개수를 가진 포인터를 담는 배열을 선언함

    // 반복문으로 배열에 노드를 생성하여 포인터를 넣음
    // 개수만큼 A부터 차례대로 노드의 이름이 지어지기 때문에
    for (int i = 0; i < n; i++)
    {
        tp[i] = createNode('A' + i);
        // tp[0] 에는 A, tp[1] 에는 B ...
    }

    // 노드의 개수만큼 왼쪽 자식, 오른쪽 자식에 대한 정보를 받아와야함
    for (int i = 0; i < n; i++)
    {
        char node, l, r;
        scanf(" %c %c %c", &node, &l, &r);
        // 기준이 되는 노드는 node로 받고, 왼쪽 노드는 l, 오른쪽노드는 r로 받음

        // 왼쪽노드를 가리키는 변수 선언
        // . 을 입력받으면 NULL, 그렇지 않으면 입력받은 문자열-'A'하여 해당하는 포인터를 찾음
        treePointer leftNode = (l == '.') ? NULL : tp[l - 'A'];

        // 오른쪽 노드를 가리키는 변수 선언
        // . 을 입력받으면 NULL, 그렇지 않으면 입력받은 문자열 - 'A'하여 해당하는 포인터를 찾음
        treePointer rightNode = (r == '.') ? NULL : tp[r - 'A'];

        // 노드를 연결하는 함수
        connectNode(tp[node - 'A'], leftNode, rightNode);
    }

    preorder(tp[0]);
    printf("\n");
    inorder(tp[0]);
    printf("\n");
    postorder(tp[0]);
    printf("\n");
}