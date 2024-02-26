// 이진 탐색 트리에서의 삽입

// 이진 탐색 트리를 구성할 노드의 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode * left;
    struct TreeNode * right;
} TreeNode;

// 이진 탐색 트리에 노드 삽입 함수 -> 재귀 사용
TreeNode *insert(TreeNode *root, int data){
    // 빈 트리인 경우, 새 노드를 생성하여 반환
    if (root == NULL){
        return createNode(data); // 여기에서 새 노드 생성
    }

    // 데이터가 현재 노드의 데이터와 같다면, 아무 작업도 하지 않음 -> 데이터가 중복되는 경우
    if (data == root->data){
        return root;
    }

    // 데이터가 현재 노드의 데이터보다 작으면 왼쪽 서브 트리에 삽입
    if (data < root->data){
        root->left = insert(root->left, data);
    }

    // 데이터가 현재 노드의 데이터보다 크면 오른쪽 서브 트리에 삽입
    else {
        root->right = insert(root->right, data);
    }

    return root;
    // 이 문장은 함수의 모든 조건문을 통과한 후에 실행됨.
    // insert() 함수는 재귀적으로 호출되어 새로운 노드를 삽입하고, 그 삽입된 노드를 가리키는 포인터를 반환한다.
    // 따라서 모든 재귀 호출이 완료되고 제어가 함수의 마지막 부분으로 돌아왔을 때, 삽입 작업이 완료되었고 변경된 트리의 루트 노드를 반환해야한다.
    // 이때 반환되는 것이 root 포인터인데 이는 삽입 작업이 완료된 후의 트리의 루트노드를 가리킨다.
}